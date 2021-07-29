# TVM模型部署

⌚️:2020年11月30日

📚参考

---



* [搭建TVM开发环境](#develop-env)
  * [编译LLVM](#build-llvm)
  * [编译TVM](#build-tvm)
* [模型编译参数讲解](#build-parmas)
  * target
  * layout
  * 编译器
  * 示例代码
* [不同模型的编译](#build)
  * [编译Tensorflow模型](#build-tensorflow)
  * [编译ONNX模型](#build-onnx)
  * [编译MXNet模型](#build-mxnet)
  
* [模型部署](#deploy)
  * [部署到PC CPU](#deploy-pc-cpu)
  * [部署到ARM CPU](#deploy-arm-cpu)
  * [部署到Android CPU](#deploy-android-cpu)
  
* [其他](#others)

TVM目前有个缺陷就是不支持dynamic input shapes，有dynamic input shapes 需求的选择其他框架。（读者看到这里时可能已经支持了,这里只是提醒一下。）

TVM包含两个主要部分：
1、TVM编译器，用来做编译和优化。
2、TVM运行环境，用来在目标设备上运行。
还可以使用RPC进行远程测试和优化。

<span id="develop-env">
<b>一、搭建TVM开发环境</b>
</span>

这部分讲如何在PC搭建TVM的开发环境，就是TVM编译器。

最小编译依赖：
支持C++ 11的c++编译器（g++4.8或更高版本）
CMake 3.5 或更高版本
强烈建议使用LLVM编译以打开所有特性
如果只用CUDA/OpenCL，可以不依赖LLVM
如果使用NNVM编译器，需要LLVM


需要编译的主要有两部分LLVM和TVM。这里展示如何在Linux上编译，Windows的编译方式可能稍有差异。
TVMM并不是一定依赖LLVM，但是由于大多数CPU上的部署都依赖LLVM，所以这里会添加LLVM。

<span id="build-llvm">
<b>1、编译LLVM</b>
</span>

  从官网[LLVM Download Page](http://releases.llvm.org/download.html)下载源码
  解压源码，在和源码平级的目录下建目录llvm-build（不允许在源码内编译）
  进入目录llvm-build
  执行命令

  ```
  cmake ../llvm-8.0.0.src
  ```
  如果报错说gcc版本过低，需要加上参数` DLLVM_TEMPORARILY_ALLOW_OLD_TOOLCHAIN=ON`
  ```
  cmake -DLLVM_TEMPORARILY_ALLOW_OLD_TOOLCHAIN=ON ../llvm-8.0.0.src
  ```
  这一步执行完成后会生成Makefile文件，执行命令
  ```
  make
  ```
  编译完成.

<span id="build-tvm">
<b>2、编译TVM</b>
</span>

  clone代码 `git clone --recursive https://github.com/dmlc/tvm`
  进入源码目录执行以下命令：
  ```
  mkdir build
  cp cmake/config.cmake build
  ```
  编辑build/config.cmake定制编译选项：
  (1). 在macOS,对于一些版本呢的Xcode,需要在LDFLAGS中添加 `-lc++abi`，否则会有链接错误。
  (2). 修改 `set(USE_CUDA OFF)` 为 `set(USE_CUDA ON)` 打开CUDA后端。其他后端和库（OpenCL、RCOM、METAL、VULKAN等）也是如此。
  根据某些选项TVM会依赖LLVM。有些CPU平台的编译会需要LLVM。
  (1).如果依赖LLVM，需要 4.0 或者更高版本。记住默认的LLVM版本可能低于4.0。
  (2).因为源码编译LLVM会花费很多时间，可以从[LLVM Download Page](http://releases.llvm.org/download.html)下载预编译版本。
    (a).解压到指定目录，修改`build/config.cmake`添加`set(USE_LLVM /path/to/your/llvm/bin/llvm-config)`
    (b).也可以直接设置`set(USE_LLVM ON)`让cmake搜索可用的LLVM。
  (3).也可以使用[LLVM Nightly Ubuntu Build](https://apt.llvm.org/),注意apt包要在`llvm-config`后面跟上版本号。比如，`set(LLVM_CONFIG llvm-config-4.0)`
  接下来执行
  ```
  cd build
  cmake ..
  make all
  ```
  安装Python包：
  python包位于tvm/python，直接设置环境变量：
  ```
  export TVM_HOME=/path/to/tvm
  export PYTHONPATH=$TVM_HOME/python:$TVM_HOME/topi/python:$TVM_HOME/nnvm/python:${PYTHONPATH}
  ```

<span id="build-parmas">
<b>一、模型编译参数讲解</b>
</span>

这一部分讲解模型编译时的一些关键参数，然后展示如何将Tensorlow模型编译生成动态库，再加载动态库模型进行推理。

* 1.指定编译参数target
  这个参数在编译生成object文件(.o文件)时用到，这个文件会放到/tmp目录下，如果想要得到这个文件，可以执行`lib.save(path) `。
  target 中的字符串选项：
  llvm, 大多数CPU 都需要LLVM
  target, 目标硬件平台，比如 -target=armv7l-linux-gnueabi
  mfloat-abi, 软硬浮点选项，这里只支持soft,hard两个选项，默认hard。Android已经关闭了VFP支持，所以需要在这里指定soft
  其他选项详见TVM代码，在 llvm_common.cc ParseLLVMTargetOptions函数。 

  示例：
  ```
  target = "llvm" #部署到PC CPU上
  target = "llvm -target=armv7l-linux-gnueabi -mfloat-abi=soft" #部署到arm cpu上，并选择软浮点
  target = tvm.target.create('llvm -device=arm_cpu -target=arm-linux-androideabi -mattr=+neon -mfloat-abi=soft') #部署到Android CPU
  ```
* 2.指定layout
  有些平台只支持"NCHW"通道顺序, 默认顺序是"NHWC"。
* 3.指定编译器
  ```
  lib.export_library(libpath, cc="/data/proj/FaceLandmark/tvm/gcc-linaro-4.8-2015.06-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++")
  ```
  通过参数cc指定编译器，默认是gcc，如果target是PC则使用默认编译器即可。
  arm linux gcc 交叉编译器可以在linaro下载，新版本地址：https://releases.linaro.org/components/toolchain/binaries/  ，老版本地址：http://releases.linaro.org/archive/14.04/components/toolchain/gcc-linaro/
  如果要部署到Android平台，需要使用NDK编译。需要先下载NDK，下载地址https://developer.android.com/ndk/downloads ,然后设置NDK C++编译器到环境变量TVM_NDK_CC 中。新版本的NDK编译器已更换为clang,示例：
  ```
  export TVM_NDK_CC=YOUR_NDK_PATH/android-ndk-r19c/toolchains/llvm/prebuilt/linux-x86_64/bin/armv7a-linux-androideabi24-clang++
  ```
  编译代码：
  ```
  lib.export_library(libpath, ndk.create_shared, options=["-shared", "-fPIC"])
  ```

* 4.完整的编译、加载、推理示例代码如下：
  ```
  import tensorflow  as tf
  import tvm.relay.testing.tf as tf_testing
  from tvm.contrib import graph_runtime
  import tvm
  import tvm.relay as relay
  import cv2
  import os
  import numpy as np
  
  img_dir = "../test/lala"
  img_name = "img_414.jpg"
  img_path = os.path.join(img_dir, img_name)
  img = cv2.imread(img_path)
  img = (img-127.5)/128
  x = img[np.newaxis, :]
  x = np.array(x).astype("float32")
  print(x.shape)
  target = "llvm"
  # target = "llvm -target=armv7l-linux-gnueabihf"
  # target =  tvm.target.arm_cpu("pynq") 
  # target = "llvm -target=armv7l-linux-gnueabi -mfloat-abi=soft"
  # target = tvm.target.create('llvm')
  
  layout="NCHW"
  ctx = tvm.cpu(0)
  
  tf_model = "../graph/pnet_frozen_model.pb"
  
  with tf.gfile.FastGFile(tf_model, 'rb') as f:
      graph_def = tf.GraphDef()
      graph_def.ParseFromString(f.read())
      graph = tf.import_graph_def(graph_def, name='')
      # Call the utility to import the graph definition into default graph.
      # graph_def = tf_testing.ProcessGraphDefParam(graph_def)
      # # Add shapes to the graph.
      # with tf.Session() as sess:
      #     graph_def = tf_testing.AddShapesToGraphDef(sess, 'softmax')
  
  shape_dict = {"input_image": x.shape}
  outputs=["cls_prob", "bbox_pred", "landmark_pred"]
  sym, params = relay.frontend.from_tensorflow(graph_def, layout=layout, shape=shape_dict, outputs=outputs)
  
  with relay.build_config(opt_level=3):
      graph, lib, params = relay.build(sym, target=target, params=params)   
   dtype = 'float32'
  
    libpath = "./libpnet.so"
  
  
    # lib.save("lib.o")
  
    lib.export_library(libpath)
    graph_json_path = "pnet.json"
    with open(graph_json_path, 'w') as f:
        f.write(graph)
  
    param_path = "pnet.params"
    with open(param_path, 'wb') as f:
        f.write(relay.save_param_dict(params))
  
  
    loaded_json = open(graph_json_path).read()
    loaded_lib = tvm.module.load(libpath)
    loaded_params = bytearray(open(param_path, "rb").read())
  
    m = graph_runtime.create(loaded_json, loaded_lib, ctx)
    m.load_params(loaded_params)
  
    # set inputs
  
    m.set_input('input_image', tvm.nd.array(x.astype(dtype)))
  
    # execute
  
    m.run()
  
    # get outputs
  
    print("get_num_outputs: ",m.get_num_outputs())
  
    # cls_prob = m.get_output(0, tvm.nd.empty(((220, 151, 2)), 'float32'))
  
    cls_prob = m.get_output(0).asnumpy()
    bbox_pred = m.get_output(1).asnumpy()
    landmark_pred = m.get_output(2).asnumpy()
  
    print(cls_prob.shape)
    print(bbox_pred.shape)
    print(landmark_pred.shape)
  ```

 <span id="build">
<b>二、模型编译</b>
</span>

这部分描述如何将训练好的模型编译为TVM模型，TVM模型由三个文件组成 deploy.so、deploy.json、deploy.params。

<span id="build-tensorflow">
<b>1、编译Tensorflow模型</b>
</span>

Tensorflow模型要首先转换为frozen model或者 tf-lite模型才能进行编译，这里只展示如何转换为frozen model。转换为frozen model的方法也不唯一，这里只展示最简单的方法。
转换代码：

    import numpy as np
    import tensorflow as tf
    import sys
    sys.path.append("../")
    from train_models.MTCNN_config import config
    from train_models.fast_mtcnn import P_Net_predict
    
    graph = tf.Graph()
    with graph.as_default():
    input_image = tf.placeholder(tf.float32, shape=[1, 12, 12, 3] , name="input_image")
    
    cls_prob, bbox_pred, _ = P_Net_predict(input_image)
    
    model_path = "../checkpoint/MTCNN_model/PNet_landmark-Adam/PNet-2"
    model_dict = '/'.join(model_path.split('/')[:-1])
    
    sess = tf.Session()
    saver = tf.train.Saver()
    
    ckpt = tf.train.get_checkpoint_state(model_dict)
    readstate = ckpt and ckpt.model_checkpoint_path
    assert  readstate, "the params dictionary is not valid"
    print ("restore models' param")
    saver.restore(sess, model_path)
    
    frozen_graphdef = tf.graph_util.convert_variables_to_constants(sess, sess.graph_def, ["input_image","cls_prob","bbox_pred","landmark_pred"]) 
    with open('pnet_frozen_model.pb', 'wb') as f:
          f.write(frozen_graphdef.SerializeToString())
    #tflite_model = tf.contrib.lite.toco_convert(frozen_graphdef, [image_reshape], [cls_prob, bbox, landmark])
    #open("model.tflite", "wb").write(tflite_model)
```
然后就可以将frozen model 编译为TVM model。
编译代码：
```
```
import tensorflow  as tf
import tvm.relay.testing.tf as tf_testing
from tvm.contrib import graph_runtime
import tvm
import tvm.relay as relay
import cv2
import os
import numpy as np

img_dir = "../test/lala"
img_name = "img_414.jpg"
img_path = os.path.join(img_dir, img_name)
img = cv2.imread(img_path)
img = (img-127.5)/128
x = img[np.newaxis, :]
x = np.array(x).astype("float32")
print(x.shape)
target = "llvm"

# target = "llvm -target=armv7l-linux-gnueabihf"

# target =  tvm.target.arm_cpu("pynq") 

# target = "llvm -target=armv7l-linux-gnueabi -mfloat-abi=soft"

# target = tvm.target.create('llvm')

layout="NCHW"
ctx = tvm.cpu(0)

tf_model = "../graph/pnet_frozen_model.pb"

with tf.gfile.FastGFile(tf_model, 'rb') as f:
    graph_def = tf.GraphDef()
    graph_def.ParseFromString(f.read())
    graph = tf.import_graph_def(graph_def, name='')
    # Call the utility to import the graph definition into default graph.
    # graph_def = tf_testing.ProcessGraphDefParam(graph_def)
    # # Add shapes to the graph.
    # with tf.Session() as sess:
    #     graph_def = tf_testing.AddShapesToGraphDef(sess, 'softmax')

shape_dict = {"input_image": x.shape}
outputs=["cls_prob", "bbox_pred", "landmark_pred"]
sym, params = relay.frontend.from_tensorflow(graph_def, layout=layout, shape=shape_dict, outputs=outputs)

with relay.build_config(opt_level=3):
    graph, lib, params = relay.build(sym, target=target, params=params)         


dtype = 'float32'

libpath = "./libpnet.so"

# lib.save("lib.o")

lib.export_library(libpath)
graph_json_path = "pnet.json"
with open(graph_json_path, 'w') as f:
    f.write(graph)

param_path = "pnet.params"
with open(param_path, 'wb') as f:
    f.write(relay.save_param_dict(params))
```

<span id="build-onnx">
<b>2、编译ONNX模型</b>
</span>

参考：https://docs.tvm.ai/tutorials/frontend/from_onnx.html
<span id="build-mxnet">
<b>3、编译MXNet模型</b>
</span>

参考：https://docs.tvm.ai/tutorials/frontend/from_mxnet.html
<span id="deploy">
<b>三、模型部署</b>
</span>

这部分讲TVM模型在不同平台的部署。

<span id="deploy-pc-cpu">
<b>1、部署到PC CPU</b>
</span>

要将TVM模型部署到PC CPU上需要在编译模型时指定 `target=llvm`。
Python 示例代码：

```

from tvm.contrib import graph_runtime
import tvm
import cv2
import os
import numpy as np
loaded_json = open(graph_json_path).read()
loaded_lib = tvm.module.load(libpath)
loaded_params = bytearray(open(param_path, "rb").read())

m = graph_runtime.create(loaded_json, loaded_lib, ctx)
m.load_params(loaded_params)

# set inputs

m.set_input('input_image', tvm.nd.array(x.astype(dtype)))

# execute

m.run()

get outputs

print("get_num_outputs: ",m.get_num_outputs())

cls_prob = m.get_output(0, tvm.nd.empty(((220, 151, 2)), 'float32'))

cls_prob = m.get_output(0).asnumpy()
bbox_pred = m.get_output(1).asnumpy()
landmark_pred = m.get_output(2).asnumpy()

print(cls_prob.shape)
print(bbox_pred.shape)
print(landmark_pred.shape)
```
<span id="deploy-arm-cpu">
<b>2、部署到ARM CPU</b>
</span>

部署到ARM CPU需要在编译模型时在targt中指定目标平台，比如 
`target = "llvm -target=armv7l-linux-gnueabi -mfloat-abi=soft"` ，同时还要指定交叉编译器。
在目标平台上需要搭建运行环境，包括tvm_runtim和llvm。
llvm可以使用编译好的库，下载地址:http://releases.llvm.org/download.html
tvm_runtime需要在ARM上编译:

```
git clone --recursive https://github.com/dmlc/tvm
cd tvm
mkdir build
cp cmake/config.cmake build   # 这里修改config.cmake使其支持llvm,配置上llvm的路径
cd build
cmake ..
make runtime

```
搭建好环境之后可以运行代码了。
C++代码示例(来自官方：https://docs.tvm.ai/deploy/nnvm.html)：

    #include <dlpack/dlpack.h>
    #include <tvm/runtime/module.h>
    #include <tvm/runtime/registry.h>
    #include <tvm/runtime/packed_func.h>
    
    #include <fstream>
    #include <iterator>
    #include <algorithm>
    
    int main()
    {
        // tvm module for compiled functions
        tvm::runtime::Module mod_syslib = tvm::runtime::Module::LoadFromFile("deploy.so");
    // json graph
    std::ifstream json_in("deploy.json", std::ios::in);
    std::string json_data((std::istreambuf_iterator<char>(json_in)), std::istreambuf_iterator<char>());
    json_in.close();
    
    // parameters in binary
    std::ifstream params_in("deploy.params", std::ios::binary);
    std::string params_data((std::istreambuf_iterator<char>(params_in)), std::istreambuf_iterator<char>());
    params_in.close();
    
    // parameters need to be TVMByteArray type to indicate the binary data
    TVMByteArray params_arr;
    params_arr.data = params_data.c_str();
    params_arr.size = params_data.length();
    
    int dtype_code = kDLFloat;
    int dtype_bits = 32;
    int dtype_lanes = 1;
    int device_type = kDLCPU;
    int device_id = 0;
    
    // get global function module for graph runtime
    tvm::runtime::Module mod = (*tvm::runtime::Registry::Get("tvm.graph_runtime.create"))(json_data, mod_syslib, device_type, device_id);
    
    DLTensor* x;
    int in_ndim = 4;
    int64_t in_shape[4] = {1, 3, 224, 224};
    TVMArrayAlloc(in_shape, in_ndim, dtype_code, dtype_bits, dtype_lanes, device_type, device_id, &x);
    // load image data saved in binary
    std::ifstream data_fin("cat.bin", std::ios::binary);
    data_fin.read(static_cast<char*>(x->data), 3 * 224 * 224 * 4);
    
    // get the function from the module(set input data)
    tvm::runtime::PackedFunc set_input = mod.GetFunction("set_input");
    set_input("data", x);
    
    // get the function from the module(load patameters)
    tvm::runtime::PackedFunc load_params = mod.GetFunction("load_params");
    load_params(params_arr);
    
    // get the function from the module(run it)
    tvm::runtime::PackedFunc run = mod.GetFunction("run");
    run();
    
    DLTensor* y;
    int out_ndim = 2;
    int64_t out_shape[2] = {1, 1000, };
    TVMArrayAlloc(out_shape, out_ndim, dtype_code, dtype_bits, dtype_lanes, device_type, device_id, &y);
    
    // get the function from the module(get output data)
    tvm::runtime::PackedFunc get_output = mod.GetFunction("get_output");
    get_output(0, y);
    
    // get the maximum position in output vector
    auto y_iter = static_cast<float*>(y->data);
    auto max_iter = std::max_element(y_iter, y_iter + 1000);
    auto max_index = std::distance(y_iter, max_iter);
    std::cout << "The maximum position in output vector is: " << max_index << std::endl;
    
    TVMArrayFree(x);
    TVMArrayFree(y);
    
    return 0;
}

<span id="deploy-android-cpu">
<b>2、部署到Android CPU</b>
</span>

部署到Android端需要在编译时指定target为androideabi，软浮点，比如: 
```target = tvm.target.create('llvm -device=arm_cpu -target=arm-linux-androideabi -mattr=+neon -mfloat-abi=soft')```
同时编译时不能使用arm linux交叉编译器，要使用ndk。详见[模型编译参数讲解](#build-parmas)。
下面讲的是用TVM C++ API部署，用Java API部署参考 [TVM4J](https://github.com/dmlc/tvm/blob/master/apps/android_deploy/README.md#build-and-installation)
使用NDK编译出的deploy.so会依赖libc++_shared.so，这个文件在NDK编译器中，找到这个文件和deploy.so一起放到Android 代码的jniLibs目录中。deploy.params和deploy.json作为资源文件放到assets文件夹中使用时copy到SDCard中使用。
运行时环境同样包括llvm和tvm_runtim。由于新版本的Andrid Studio已经使用clang+llvm编译器，所以Android中会自带llvm环境，我们只需要编译出tvm_runtime。
编译tvm_runtime只需要将TVM源码放入Android Studio的jni代码目录，在CMakeLists.txt中加入编译tvm/apps/howto_deploy/tvm_runtime_pack.ccd的命令即可编译得到tvm_runtime。

编译命令：
`
add_library(tvm_runtime SHARED  src/main/cpp/tvm/apps/howto_deploy/tvm_runtime_pack.cc)
`

编译后可以在build/intermediates/cmake（后面还有子目录，找一下）目录下找到 libtvm_rumtime.so，将libtvm_rumtime.so和deploy.so放到一起。
到这里环境也部署好了，推理代码可参考[部署到ARM CPU](#deploy-arm-cpu)中的C++代码。


<span id="others">
<b>四、其他</b>
</span>

* 1、线程安全
关于tvm_runtime的线程安全：[https://discuss.tvm.ai/t/is-tvmruntime-thread-safe/84](https://discuss.tvm.ai/t/is-tvmruntime-thread-safe/84)