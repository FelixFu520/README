# Ubuntu下TVM的编译安装

2020年11月26日

---



官方安装文档地址：https://docs.tvm.ai/install/index.html
系统环境：Ubuntu 18.04 LTS 64-bit，其他环境或需求可参考官方文档。



## 1. LLVM部分

虽然LLVM对于TVM是可选项，但是如果要部署到CPU端，那么LLVM几乎是必须的，所以建议安装LLVM。本次安装LLVM6.0。
**第一步，添加相关源**
编辑`/etc/apt/sources.list`，将以下源加入：

```
deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial-6.0 main
deb-src http://apt.llvm.org/xenial/ llvm-toolchain-xenial-6.0 main     
```

加入完成后需取得数字证书

```
wget -O - http://llvm.org/apt/llvm-snapshot.gpg.key|sudo apt-key add -
```

然后务必进行`apt-get update`
**第二步，安装LLVM**

```
apt-get install clang-6.0 lldb-6.0
```

其他操作系统和LLVM版本参考：https://apt.llvm.org/

## 2. TVM部分

**第一步，从GitHub克隆TVM的repo**

```
# 1. Clone the project
git clone --recursive https://github.com/apache/incubator-tvm tvm
```

注意此处的`--recursive`是必须的，否则在编译时会出错。
**第二步，安装前准备**

```
# 2. Install Linux dependencies
sudo apt-get update
sudo apt-get install -y python3 python3-pip python3-dev python3-setuptools gcc libtinfo-dev zlib1g-dev build-essential cmake libedit-dev libxml2-dev

```

**第三步，修改config.cmake配置**
建立build文件夹，复制`config.cmake`。

> 配置信息解释
>
> 编辑build/config.cmake文件，里面有一些功能开关，这些配置有：
>
> ```text
> USE_CUDA，NVIDIA的GPU计算；
> USE_ROCM，通用的GPU计算，AMD提出，目的很显然...；
> USE_SDACCEL，FPGA计算；
> USE_AOCL，Intel FPGA SDK for OpenCL (AOCL) runtime；
> USE_OPENCL，异构平台编写程序的框架，异构平台可由CPU、GPU、DSP、FPGA或其他类型的处理器与硬件加速器所组成；
> USE_METAL，iOS上的GPU计算；
> USE_VULKAN，新一代的openGL，Android 7.x开始支持（iOS不支持，因为有自己的metal2）；
> USE_OPENGL，2D/3D渲染库标准，显卡厂家负责实现和支持；
> USE_SGX， Intel SGX ; 
> USE_RPC，远程调用，电脑和手机可以通过网络联调；
> USE_STACKVM_RUNTIME，embed stackvm into the runtime；
> USE_GRAPH_RUNTIME，enable tiny embedded graph runtime；
> USE_GRAPH_RUNTIME_DEBUG，enable additional graph debug functions；
> USE_LLVM，llvm support；
> USE_BLAS，API标准，规范发布基础线性代数操作的数值库（如矢量或矩阵乘法），不同的实现有openblas, mkl, atlas, apple
> USE_RANDOM，contrib.random运行时；
> USE_NNPACK，
> USE_CUDNN，
> USE_CUBLAS，
> USE_MIOPEN，
> USE_MPS，
> USE_ROCBLAS，
> USE_SORT，使用contrib sort；
> USE_ANTLR，
> USE_VTA_TSIM，
> USE_RELAY_DEBUG，Relay debug模式
> ```
>
> 只打开了set(USE_LLVM ON)、USE_SORT、USE_GRAPH_RUNTIME、USE_RPC。其它的都没开启，为什么？因为有些用不到，有些还不知道是啥意思。

```
# 3. Build the shared library
mkdir build
cp cmake/config.cmake build # change settings in cmake file
```

然后修改LLVM配置，将`set(USE_LLVM OFF)`改为`set(USE_LLVM ON)`
**第四步，启动编译**

```
# for cpu and gpu, need to install LLVM first
# i) Download LLVM pre-built version 9.0 from http://releases.llvm.org/download.html
# 2) set (USE_LLVM /path/to/llvm/bin/llvm-config) in config.cmake

cd build
cmake ..
make -j4
```

如果顺利完成，即可进入Python包安装

> 最终链接出以下so库：
>
> ```text
> [  5%] Linking CXX shared library libvta.so
> [ 12%] Linking CXX shared library libtvm_runtime.so
> [ 86%] Linking CXX shared library libtvm.so
> [ 94%] Linking CXX shared library libtvm_topi.so
> [100%] Linking CXX shared library libnnvm_compiler.so
> ```
>
> 简单介绍下这几个共享库：
>
> 1，libvta.so （VTA，Versatile Tensor Accelerator的缩写），参考[https://docs.tvm.ai/vta/index.html](https://link.zhihu.com/?target=https%3A//docs.tvm.ai/vta/index.html)，由以下这几个编译单元生成。
>
> ```text
> vta/src/device_api.cc 
> vta/src/runtime.cc 
> vta/src/sim/sim_driver.cc
> ```
>
> 2，libtvm_runtime.so
>
> 顾名思义，tvm的运行时，实际上，这个库是TVM运行时的一个最小化库，由“Minimum runtime related codes”编译而成——也即下面的这些源文件：
>
> ```text
> src/runtime/builtin_fp16.cc
> src/runtime/c_dsl_api.cc
> src/runtime/c_runtime_api.cc
> src/runtime/cpu_device_api.cc
> src/runtime/dso_module.cc
> src/runtime/file_util.cc
> src/runtime/module.cc
> src/runtime/module_util.cc
> src/runtime/ndarray.cc
> src/runtime/registry.cc
> src/runtime/system_lib_module.cc
> src/runtime/thread_pool.cc
> src/runtime/threading_backend.cc
> src/runtime/vm/memory_manager.cc
> src/runtime/vm/object.cc
> src/runtime/vm/vm.cc
> src/runtime/workspace_pool.cc
> 3rdparty/bfloat16/bfloat16.cc
> src/runtime/rpc/*.cc
> src/runtime/graph/graph_runtime.cc
> src/contrib/sort/sort.cc
> ```
>
> 3，libtvm.so
>
> 完整的tvm，由编译时、运行时、rpc部分等组成：
>
> ```text
> common: Internal common utilities.
> api: API function registration.
> lang: The definition of DSL related data structure.
> arithmetic: Arithmetic expression and set simplification.
> op: The detail implementations about each operation(compute, scan, placeholder).
> schedule: The operations on the schedule graph before converting to IR.
> pass: The optimization pass on the IR structure.
> codegen: The code generator.
> runtime: Minimum runtime related codes.
> autotvm: The auto-tuning module.
> relay: Implementation of Relay. The second generation of NNVM, a new IR for deep learning frameworks.
> contrib: Contrib extension libraries.
> ```
>
> 这个库比较大，有200多个编译单元：
>
> ```text
> src/api/*.cc
> src/arithmetic/*.cc
> src/autotvm/*.cc
> src/codegen/*.cc
> src/lang/*.cc
> src/op/*.cc
> src/pass/*.cc
> src/schedule/*.cc
> src/relay/backend/*.cc
> src/relay/ir/*.cc
> src/relay/op/*.cc
> src/relay/pass/*.cc
> 3rdparty/HalideIR/src/*.cpp
> src/runtime/stackvm/*.cc
> src/codegen/opt/*.cc
> src/codegen/llvm/*.cc
> src/runtime/*.cc
> src/contrib/hybrid/codegen_hybrid.cc
> 3rdparty/bfloat16/bfloat16.cc
> src/contrib/sort/sort.cc
> ```
>
> 4，libtvm_topi.so
>
> TOPI（TVM OP Inventory），is the operator collection library for TVM intended at sharing the effort of crafting and optimizing tvm generated kernels。由下面的编译单元生成：
>
> ```text
> topi/src/topi.cc
> ```
>
> 5，libnnvm_compiler.so
>
> NNVM编译器，由以下编译单元生成：
>
> ```text
> nnvm/src/c_api/*.cc
> nnvm/src/compiler/*.cc
> nnvm/src/core/*.cc
> nnvm/src/pass/*.cc
> nnvm/src/top/nn/*.cc
> nnvm/src/top/tensor/*.cc
> nnvm/src/top/vision/nms.cc
> nnvm/src/top/vision/ssd/mutibox_op.cc
> nnvm/src/top/vision/yolo/reorg.cc
> nnvm/src/top/image/resize.cc
> ```

## 3. Python包安装

此处使用官方文档推荐的**第一种方法**进行Python包安装。这种方法可以使我们更改源代码并重新编译后，无需对Python端进行任何更改。
**第一步，编辑`~/.bashrc`，在文件末尾添加：**

```
# 方式一（推荐）
# 4. Python package installation
# Recommended for developers, no need to call setup!
# It would be better if adding them to ~/.bashrc
export TVM_HOME=/path/to/tvm
export PYTHONPATH=TVM_HOME/python:TVM_HOME/topi/python:TVM_HOME/nnvm/python:{PYTHONPATH}

# 方式二
#install tvm package for the current user
#NOTE: if you installed python via homebrew, --user is not needed during installaiton
#it will be automatically installed to your user directory.
#providing --user flag may trigger error during installation in such case.
export MACOSX_DEPLOYMENT_TARGET=10.9  # This is required for mac to avoid symbol conflicts with libstdc++
cd python; python setup.py install --user; cd ..
cd topi/python; python setup.py install --user; cd ../..
cd nnvm/python; python setup.py install --user; cd ../..


```

其中`/path/to/tvm`为tvm目录。
**第二步，使修改立即生效**

```
source ~/.bashrc
```

**最后安装其他Python依赖**
必须的依赖：

```
pip install --user numpy decorator attrs
```

事实证明官方教程讲得很清晰，之后就可以顺利在Python里`import tvm`啦！



如果需要RPC Tracker：

```
pip install --user tornado
```

如果需要auto-tuning模块：

```
pip install --user tornado psutil xgboost
```

解析Relay text format程序必须使用Python 3并安装：

```
pip install --user mypy orderedset antlr4-python3-runtime
```



 安装onnx

```console
 pip3 install onnx
```

## 

## 参考

> https://blog.csdn.net/u014448054/article/details/101352550
>
> https://zhuanlan.zhihu.com/p/58995914