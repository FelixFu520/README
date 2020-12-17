# Pytorch2ONNX2TVM

2020年12月17日

https://oldpan.me/archives/the-first-step-towards-tvm-1



---



## 1. 前言

这是一个TVM教程系列，计划从TVM的使用说明，再到TVM的内部源码，为大家大致解析一下TVM的基本工作原理。因为TVM的中文资料比较少，也希望贡献一下自己的力量，如有描述方面的错误，请及时指出。

那啥是TVM？

简单来说，TVM可以称为许多工具集的集合，其中这些工具可以组合起来使用，来实现我们的一些神经网络的加速和部署功能。这也是为什么叫做**TVM Stack**了。TVM的使用途径很广，几乎可以支持市面上大部分的神经网络权重框架(ONNX、TF、Caffe2等)，也几乎可以部署在任何的平台，例如Windows、Linux、Mac、ARM等等。

以下面一张图来形容一下：

![《一步一步解读神经网络编译器TVM(一)——一个简单的例子》](imgs/stack_tvmlang.png)



乍看这么多感觉非常地复杂，但我们只需要知道TVM的核心功能就可以：**TVM可以优化的训练好的模型，并将你的模型打包好，然后你可以将这个优化好的模型放在任何平台去运行**，可以说是与落地应用息息相关。

TVM包含的东西和知识概念都有很多，不仅有神经网络优化量化op融合等一系列步骤，还有其他更多细节技术的支持(Halide、LLVM)，从而使TVM拥有很强大的功能…好了废话不说了，再说就憋不出来了，如果想多了解TVM的可以在知乎上直接搜索TVM关键字，那些大佬有很多关于TVM的介绍文章，大家可以去看看。

其实做模型优化这一步骤的库已经出现很多了，不论是Nvidia自家的TensorRT还是Pytorch自家的`torch.jit`模块，都在做一些模型优化的工作，这里就不多说了，感兴趣的可以看看以下文章：

[利用Pytorch的C++前端(libtorch)读取预训练权重并进行预测](https://oldpan.me/archives/pytorch-c-libtorch-inference)

[利用TensorRT实现神经网络提速(读取ONNX模型并运行)](https://oldpan.me/archives/tensorrt-code-toturial-1)

[利用TensorRT对深度学习进行加速](https://oldpan.me/archives/use-tensorrt-speed-up-deep-learning-1)

## 2. 开始使用

说到这里了，感觉有必要说下：**我们为什么要使用TVM**？

如果你想将你的训练模型移植到Window端、ARM端(树莓派、其他一系列使用该内核的板卡)或者其他的一些平台，利用其中的CPU或者GPU来运行，并且希望可以通过优化模型来使模型在该平台运算的速度更快(这里与模型本身的算法设计无关)，实现落地应用研究，那么TVM就是你的不二之选。另外TVM源码是由C++和Pythoh共同搭建，阅读相关源码也有利于我们程序编写方面的提升。

### 2.1 安装

安装其实没什么多说的，官方的[例子说明](https://docs.tvm.ai/install/from_source.html#build-the-shared-library)的很详细。大家移步到那里按照官方的步骤一步一步来即可。

不过有两点需要注意下：

- 建议安装LLVM，虽然LLVM对于TVM是可选项，但是如果我们想要部署到CPU端，那么llvm几乎是必须的
- 因为TVM是python和C++一起的工程，python可以说是C++的前端，安装官方教程编译好C++端后，这里建议选择官方中的**Method 1**来进行python端的设置，这样我们就可以随意修改源代码，再重新编译，而Python端就不需要进行任何修改就可以直接使用了。

### 2.2 利用Pytorch导出Onnx模型

说了这么多，演示一个例子才能更好地理解TVM到底是做什么的，所以我们这里以一个简单的例子来演示一下TVM是怎么使用的。

首先我们要做的是，得到一个已经训练好的模型，这里我选择这个[github](https://github.com/FelixFu520/pytorch2onnx2tvm)仓库中的**mobilenet-v2**，model代码和在ImageNet上训练好的权重都已经提供。好，我们将github中的模型代码移植到本地，然后调用并加载已经训练好的权重：

```python
import torch
import time
from MobileNetV2 import mobilenet_v2


model = mobilenet_v2(pretrained=True)
example = torch.rand(1, 3, 224, 224)   

with torch.no_grad():
    model.eval()
    since = time.time()
    for i in range(4000):
        model(example)
    time_elapsed = time.time() - since
    print('Time elapsed is {:.0f}m {:.0f}s'.
          format(time_elapsed // 60, time_elapsed % 60))
```

这里我们加载训练好的模型权重，并设定了输入，在python端连续运行了4000次，这里我们所花的时间为：1m 24s。

然后我们将Pytorch模型导出为ONNX模型：

```python
import torch
from MobileNetV2 import mobilenet_v2


model = mobilenet_v2(pretrained=True)
example = torch.rand(1, 3, 224, 224)   

torch_out = torch.onnx.export(model,
                              example,
                              "mobilenetv2.onnx",
                              verbose=True,
                              export_params=True   # 带参数输出
                              )
```

这样我们就得到了`mobilenetv2.onnx`这个onnx格式的模型权重。注意这里我们要带参数输出，因为我们之后要直接读取ONNX模型进行预测。

导出来之后，建议使用[Netron](https://github.com/lutzroeder/netron)来查看我们模型的结构，可以看到这个模型由Pytorch-1.0.1导出，共有152个op，以及输入id和输入格式等等信息，我们可以拖动鼠标查看到更详细的信息:

![《一步一步解读神经网络编译器TVM(一)——一个简单的例子》](imgs/mobilenetv2-test.png)

好了，至此我们的**mobilenet-v2**模型已经顺利导出了。

### 2.3 利用TVM读取并预测ONNX模型

在我们成功编译并且可以在Python端正常引用TVM后，我们首先导入我们的onnx格式的模型。这里我们准备了一张飞机的图像：

![《一步一步解读神经网络编译器TVM(一)——一个简单的例子》](imgs/tvm_plane.png)

这个图像在ImageNet分类中属于`404: 'airliner'`，也就是航空客机。

下面我们将利用TVM部署onnx模型并对这张图像进行预测。

```python
import onnx
import time
import tvm
import numpy as np
import tvm.relay as relay
from PIL import Image

onnx_model = onnx.load('mobilenetv2.onnx')  # 导入模型

mean = [123., 117., 104.]                   # 在ImageNet上训练数据集的mean和std
std = [58.395, 57.12, 57.375]


def transform_image(image):                # 定义转化函数，将PIL格式的图像转化为格式维度的numpy格式数组
    image = image - np.array(mean)
    image /= np.array(std)
    image = np.array(image).transpose((2, 0, 1))
    image = image[np.newaxis, :].astype('float32')
    return image

img = Image.open('./plane.jpg').resize((224, 224)) # 这里我们将图像resize为特定大小
x = transform_image(img)
```

这样我们得到的`x`为`[1,3,224,224]`维度的`ndarray`。这个符合NCHW格式标准，也是我们通用的张量格式。

接下来我们设置目标端口`llvm`，也就是部署到CPU端，而这里我们使用的是TVM中的[Relay IR](https://docs.tvm.ai/dev/relay_intro.html)，这个IR简单来说就是可以读取我们的模型并按照模型的顺序搭建出一个可以执行的计算图出来，当然，我们可以对这个计算图进行一系列优化。(现在TVM主推Relay而不是NNVM，Relay可以称为二代NNVM)。

```python
target = 'llvm'

input_name = '0'  # 注意这里为之前导出onnx模型中的模型的输入id，这里为0
shape_dict = {input_name: x.shape}
# 利用Relay中的onnx前端读取我们导出的onnx模型
sym, params = relay.frontend.from_onnx(onnx_model, shape_dict)
```

上述代码中导出的`sym`和`params`是我们接下来要使用的核心的东西，其中params就是导出模型中的权重信息，在python中用dic表示：



![《一步一步解读神经网络编译器TVM(一)——一个简单的例子》](imgs/12wer.png)

而`sym`就是表示计算图结构的功能函数，这个函数中包含了计算图的流动过程，以及一些计算中需要的各种参数信息，Relay IR之后对网络进行优化就是主要对这个`sym`进行优化的过程：

```c
fn (%v0: Tensor[(1, 3, 224, 224), float32],
    %v1: Tensor[(32, 3, 3, 3), float32],
    %v2: Tensor[(32,), float32],
    %v3: Tensor[(32,), float32],
    %v4: Tensor[(32,), float32],
    %v5: Tensor[(32,), float32],
    ...
    %v307: Tensor[(1280, 320, 1, 1), float32],
    %v308: Tensor[(1280,), float32],
    %v309: Tensor[(1280,), float32],
    %v310: Tensor[(1280,), float32],
    %v311: Tensor[(1280,), float32],
    %v313: Tensor[(1000, 1280), float32],
    %v314: Tensor[(1000,), float32]) {
  %0 = nn.conv2d(%v0, %v1, strides=[2, 2], padding=[1, 1], kernel_size=[3, 3])
  %1 = nn.batch_norm(%0, %v2, %v3, %v4, %v5, epsilon=1e-05)
  %2 = %1.0
  %3 = clip(%2, a_min=0, a_max=6)
  %4 = nn.conv2d(%3, %v7, padding=[1, 1], groups=32, kernel_size=[3, 3])
  ...
  %200 = clip(%199, a_min=0, a_max=6)
  %201 = mean(%200, axis=[3])
  %202 = mean(%201, axis=[2])
  %203 = nn.batch_flatten(%202)
  %204 = multiply(1f, %203)
  %205 = nn.dense(%204, %v313, units=1000)
  %206 = multiply(1f, %v314)
  %207 = nn.bias_add(%205, %206)
  %207
}
```

好了，接下来我们需要对这个计算图模型进行优化，这里我们选择优化的等级为3：

```python
with relay.build_config(opt_level=3):
    intrp = relay.build_module.create_executor('graph', sym, tvm.cpu(0), target)

dtype = 'float32'
func = intrp.evaluate(sym)
```

最后我们得到可以直接运行的`func`。

其中优化的等级分这几种：

```python
OPT_PASS_LEVEL = {
    "SimplifyInference": 0,
    "OpFusion": 1,
    "FoldConstant": 2,
    "CombineParallelConv2D": 3,
    "FoldScaleAxis": 3,
    "AlterOpLayout": 3,
    "CanonicalizeOps": 3,
}
```

最后，我们将之前已经转化格式后的图像`x`数组和模型的参数输入到这个`func`中，并且返回这个输出数组中的最大值

```python
output = func(tvm.nd.array(x.astype(dtype)), **params).asnumpy()
print(output.argmax())
```

这里我们得到的输出为`404`，与前文描述图像在ImageNet中的分类标记一致，说明我们的TVM正确读取onnx模型并将其应用于预测阶段。

我们另外单独测试一下模型优化后运行的速度和之前直接利用pytorch运行速度之间比较一下，可以发现最后的运行时间为：3m20s，相较之前的6m2s快了将近一倍。

```python
since = time.time()
for i in range(10000):
    output = func(tvm.nd.array(x.astype(dtype)), **params).asnumpy()
time_elapsed = time.time() - since
print('Time elapsed is {:.0f}m {:.0f}s'.
      format(time_elapsed // 60, time_elapsed % 60))  # 打印出来时间
```

当然，这个比较并不是很规范，不过我们可以大概分析出TVM的一些可用之处了。

整体日志

```
root@0e8554287189:~/pytorch2onnx2tvm# python pytorch2onnx2tvm.py 
Time elapsed is 3m 28s
graph(%input.1 : Float(1:150528, 3:50176, 224:224, 224:1, requires_grad=0, device=cpu),
      %classifier.weight : Float(1000:1280, 1280:1, requires_grad=1, device=cpu),
      %classifier.bias : Float(1000:1, requires_grad=1, device=cpu),
      %468 : Float(32:27, 3:9, 3:3, 3:1, requires_grad=0, device=cpu),
      %469 : Float(32:1, requires_grad=0, device=cpu),
      %471 : Float(32:9, 1:9, 3:3, 3:1, requires_grad=0, device=cpu),
      %472 : Float(32:1, requires_grad=0, device=cpu),
      %474 : Float(16:32, 32:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %475 : Float(16:1, requires_grad=0, device=cpu),
      %477 : Float(96:16, 16:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %478 : Float(96:1, requires_grad=0, device=cpu),
      %480 : Float(96:9, 1:9, 3:3, 3:1, requires_grad=0, device=cpu),
      %481 : Float(96:1, requires_grad=0, device=cpu),
      %483 : Float(24:96, 96:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %484 : Float(24:1, requires_grad=0, device=cpu),
      %486 : Float(144:24, 24:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %487 : Float(144:1, requires_grad=0, device=cpu),
      %489 : Float(144:9, 1:9, 3:3, 3:1, requires_grad=0, device=cpu),
      %490 : Float(144:1, requires_grad=0, device=cpu),
      %492 : Float(24:144, 144:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %493 : Float(24:1, requires_grad=0, device=cpu),
      %495 : Float(144:24, 24:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %496 : Float(144:1, requires_grad=0, device=cpu),
      %498 : Float(144:9, 1:9, 3:3, 3:1, requires_grad=0, device=cpu),
      %499 : Float(144:1, requires_grad=0, device=cpu),
      %501 : Float(32:144, 144:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %502 : Float(32:1, requires_grad=0, device=cpu),
      %504 : Float(192:32, 32:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %505 : Float(192:1, requires_grad=0, device=cpu),
      %507 : Float(192:9, 1:9, 3:3, 3:1, requires_grad=0, device=cpu),
      %508 : Float(192:1, requires_grad=0, device=cpu),
      %510 : Float(32:192, 192:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %511 : Float(32:1, requires_grad=0, device=cpu),
      %513 : Float(192:32, 32:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %514 : Float(192:1, requires_grad=0, device=cpu),
      %516 : Float(192:9, 1:9, 3:3, 3:1, requires_grad=0, device=cpu),
      %517 : Float(192:1, requires_grad=0, device=cpu),
      %519 : Float(32:192, 192:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %520 : Float(32:1, requires_grad=0, device=cpu),
      %522 : Float(192:32, 32:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %523 : Float(192:1, requires_grad=0, device=cpu),
      %525 : Float(192:9, 1:9, 3:3, 3:1, requires_grad=0, device=cpu),
      %526 : Float(192:1, requires_grad=0, device=cpu),
      %528 : Float(64:192, 192:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %529 : Float(64:1, requires_grad=0, device=cpu),
      %531 : Float(384:64, 64:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %532 : Float(384:1, requires_grad=0, device=cpu),
      %534 : Float(384:9, 1:9, 3:3, 3:1, requires_grad=0, device=cpu),
      %535 : Float(384:1, requires_grad=0, device=cpu),
      %537 : Float(64:384, 384:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %538 : Float(64:1, requires_grad=0, device=cpu),
      %540 : Float(384:64, 64:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %541 : Float(384:1, requires_grad=0, device=cpu),
      %543 : Float(384:9, 1:9, 3:3, 3:1, requires_grad=0, device=cpu),
      %544 : Float(384:1, requires_grad=0, device=cpu),
      %546 : Float(64:384, 384:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %547 : Float(64:1, requires_grad=0, device=cpu),
      %549 : Float(384:64, 64:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %550 : Float(384:1, requires_grad=0, device=cpu),
      %552 : Float(384:9, 1:9, 3:3, 3:1, requires_grad=0, device=cpu),
      %553 : Float(384:1, requires_grad=0, device=cpu),
      %555 : Float(64:384, 384:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %556 : Float(64:1, requires_grad=0, device=cpu),
      %558 : Float(384:64, 64:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %559 : Float(384:1, requires_grad=0, device=cpu),
      %561 : Float(384:9, 1:9, 3:3, 3:1, requires_grad=0, device=cpu),
      %562 : Float(384:1, requires_grad=0, device=cpu),
      %564 : Float(96:384, 384:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %565 : Float(96:1, requires_grad=0, device=cpu),
      %567 : Float(576:96, 96:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %568 : Float(576:1, requires_grad=0, device=cpu),
      %570 : Float(576:9, 1:9, 3:3, 3:1, requires_grad=0, device=cpu),
      %571 : Float(576:1, requires_grad=0, device=cpu),
      %573 : Float(96:576, 576:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %574 : Float(96:1, requires_grad=0, device=cpu),
      %576 : Float(576:96, 96:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %577 : Float(576:1, requires_grad=0, device=cpu),
      %579 : Float(576:9, 1:9, 3:3, 3:1, requires_grad=0, device=cpu),
      %580 : Float(576:1, requires_grad=0, device=cpu),
      %582 : Float(96:576, 576:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %583 : Float(96:1, requires_grad=0, device=cpu),
      %585 : Float(576:96, 96:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %586 : Float(576:1, requires_grad=0, device=cpu),
      %588 : Float(576:9, 1:9, 3:3, 3:1, requires_grad=0, device=cpu),
      %589 : Float(576:1, requires_grad=0, device=cpu),
      %591 : Float(160:576, 576:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %592 : Float(160:1, requires_grad=0, device=cpu),
      %594 : Float(960:160, 160:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %595 : Float(960:1, requires_grad=0, device=cpu),
      %597 : Float(960:9, 1:9, 3:3, 3:1, requires_grad=0, device=cpu),
      %598 : Float(960:1, requires_grad=0, device=cpu),
      %600 : Float(160:960, 960:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %601 : Float(160:1, requires_grad=0, device=cpu),
      %603 : Float(960:160, 160:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %604 : Float(960:1, requires_grad=0, device=cpu),
      %606 : Float(960:9, 1:9, 3:3, 3:1, requires_grad=0, device=cpu),
      %607 : Float(960:1, requires_grad=0, device=cpu),
      %609 : Float(160:960, 960:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %610 : Float(160:1, requires_grad=0, device=cpu),
      %612 : Float(960:160, 160:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %613 : Float(960:1, requires_grad=0, device=cpu),
      %615 : Float(960:9, 1:9, 3:3, 3:1, requires_grad=0, device=cpu),
      %616 : Float(960:1, requires_grad=0, device=cpu),
      %618 : Float(320:960, 960:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %619 : Float(320:1, requires_grad=0, device=cpu),
      %621 : Float(1280:320, 320:1, 1:1, 1:1, requires_grad=0, device=cpu),
      %622 : Float(1280:1, requires_grad=0, device=cpu)):
  %467 : Float(1:401408, 32:12544, 112:112, 112:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[3, 3], pads=[1, 1, 1, 1], strides=[2, 2]](%input.1, %468, %469)
  %317 : Float(1:401408, 32:12544, 112:112, 112:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%467) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %470 : Float(1:401408, 32:12544, 112:112, 112:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=32, kernel_shape=[3, 3], pads=[1, 1, 1, 1], strides=[1, 1]](%317, %471, %472)
  %320 : Float(1:401408, 32:12544, 112:112, 112:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%470) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %473 : Float(1:200704, 16:12544, 112:112, 112:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%320, %474, %475)
  %476 : Float(1:1204224, 96:12544, 112:112, 112:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%473, %477, %478)
  %325 : Float(1:1204224, 96:12544, 112:112, 112:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%476) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %479 : Float(1:301056, 96:3136, 56:56, 56:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=96, kernel_shape=[3, 3], pads=[1, 1, 1, 1], strides=[2, 2]](%325, %480, %481)
  %328 : Float(1:301056, 96:3136, 56:56, 56:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%479) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %482 : Float(1:75264, 24:3136, 56:56, 56:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%328, %483, %484)
  %485 : Float(1:451584, 144:3136, 56:56, 56:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%482, %486, %487)
  %333 : Float(1:451584, 144:3136, 56:56, 56:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%485) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %488 : Float(1:451584, 144:3136, 56:56, 56:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=144, kernel_shape=[3, 3], pads=[1, 1, 1, 1], strides=[1, 1]](%333, %489, %490)
  %336 : Float(1:451584, 144:3136, 56:56, 56:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%488) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %491 : Float(1:75264, 24:3136, 56:56, 56:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%336, %492, %493)
  %339 : Float(1:75264, 24:3136, 56:56, 56:1, requires_grad=1, device=cpu) = onnx::Add(%482, %491) # /root/pytorch2onnx2tvm/MobileNetV2.py:62:0
  %494 : Float(1:451584, 144:3136, 56:56, 56:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%339, %495, %496)
  %342 : Float(1:451584, 144:3136, 56:56, 56:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%494) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %497 : Float(1:112896, 144:784, 28:28, 28:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=144, kernel_shape=[3, 3], pads=[1, 1, 1, 1], strides=[2, 2]](%342, %498, %499)
  %345 : Float(1:112896, 144:784, 28:28, 28:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%497) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %500 : Float(1:25088, 32:784, 28:28, 28:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%345, %501, %502)
  %503 : Float(1:150528, 192:784, 28:28, 28:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%500, %504, %505)
  %350 : Float(1:150528, 192:784, 28:28, 28:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%503) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %506 : Float(1:150528, 192:784, 28:28, 28:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=192, kernel_shape=[3, 3], pads=[1, 1, 1, 1], strides=[1, 1]](%350, %507, %508)
  %353 : Float(1:150528, 192:784, 28:28, 28:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%506) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %509 : Float(1:25088, 32:784, 28:28, 28:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%353, %510, %511)
  %356 : Float(1:25088, 32:784, 28:28, 28:1, requires_grad=1, device=cpu) = onnx::Add(%500, %509) # /root/pytorch2onnx2tvm/MobileNetV2.py:62:0
  %512 : Float(1:150528, 192:784, 28:28, 28:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%356, %513, %514)
  %359 : Float(1:150528, 192:784, 28:28, 28:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%512) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %515 : Float(1:150528, 192:784, 28:28, 28:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=192, kernel_shape=[3, 3], pads=[1, 1, 1, 1], strides=[1, 1]](%359, %516, %517)
  %362 : Float(1:150528, 192:784, 28:28, 28:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%515) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %518 : Float(1:25088, 32:784, 28:28, 28:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%362, %519, %520)
  %365 : Float(1:25088, 32:784, 28:28, 28:1, requires_grad=1, device=cpu) = onnx::Add(%356, %518) # /root/pytorch2onnx2tvm/MobileNetV2.py:62:0
  %521 : Float(1:150528, 192:784, 28:28, 28:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%365, %522, %523)
  %368 : Float(1:150528, 192:784, 28:28, 28:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%521) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %524 : Float(1:37632, 192:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=192, kernel_shape=[3, 3], pads=[1, 1, 1, 1], strides=[2, 2]](%368, %525, %526)
  %371 : Float(1:37632, 192:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%524) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %527 : Float(1:12544, 64:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%371, %528, %529)
  %530 : Float(1:75264, 384:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%527, %531, %532)
  %376 : Float(1:75264, 384:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%530) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %533 : Float(1:75264, 384:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=384, kernel_shape=[3, 3], pads=[1, 1, 1, 1], strides=[1, 1]](%376, %534, %535)
  %379 : Float(1:75264, 384:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%533) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %536 : Float(1:12544, 64:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%379, %537, %538)
  %382 : Float(1:12544, 64:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Add(%527, %536) # /root/pytorch2onnx2tvm/MobileNetV2.py:62:0
  %539 : Float(1:75264, 384:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%382, %540, %541)
  %385 : Float(1:75264, 384:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%539) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %542 : Float(1:75264, 384:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=384, kernel_shape=[3, 3], pads=[1, 1, 1, 1], strides=[1, 1]](%385, %543, %544)
  %388 : Float(1:75264, 384:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%542) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %545 : Float(1:12544, 64:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%388, %546, %547)
  %391 : Float(1:12544, 64:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Add(%382, %545) # /root/pytorch2onnx2tvm/MobileNetV2.py:62:0
  %548 : Float(1:75264, 384:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%391, %549, %550)
  %394 : Float(1:75264, 384:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%548) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %551 : Float(1:75264, 384:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=384, kernel_shape=[3, 3], pads=[1, 1, 1, 1], strides=[1, 1]](%394, %552, %553)
  %397 : Float(1:75264, 384:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%551) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %554 : Float(1:12544, 64:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%397, %555, %556)
  %400 : Float(1:12544, 64:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Add(%391, %554) # /root/pytorch2onnx2tvm/MobileNetV2.py:62:0
  %557 : Float(1:75264, 384:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%400, %558, %559)
  %403 : Float(1:75264, 384:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%557) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %560 : Float(1:75264, 384:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=384, kernel_shape=[3, 3], pads=[1, 1, 1, 1], strides=[1, 1]](%403, %561, %562)
  %406 : Float(1:75264, 384:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%560) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %563 : Float(1:18816, 96:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%406, %564, %565)
  %566 : Float(1:112896, 576:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%563, %567, %568)
  %411 : Float(1:112896, 576:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%566) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %569 : Float(1:112896, 576:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=576, kernel_shape=[3, 3], pads=[1, 1, 1, 1], strides=[1, 1]](%411, %570, %571)
  %414 : Float(1:112896, 576:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%569) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %572 : Float(1:18816, 96:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%414, %573, %574)
  %417 : Float(1:18816, 96:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Add(%563, %572) # /root/pytorch2onnx2tvm/MobileNetV2.py:62:0
  %575 : Float(1:112896, 576:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%417, %576, %577)
  %420 : Float(1:112896, 576:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%575) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %578 : Float(1:112896, 576:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=576, kernel_shape=[3, 3], pads=[1, 1, 1, 1], strides=[1, 1]](%420, %579, %580)
  %423 : Float(1:112896, 576:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%578) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %581 : Float(1:18816, 96:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%423, %582, %583)
  %426 : Float(1:18816, 96:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Add(%417, %581) # /root/pytorch2onnx2tvm/MobileNetV2.py:62:0
  %584 : Float(1:112896, 576:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%426, %585, %586)
  %429 : Float(1:112896, 576:196, 14:14, 14:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%584) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %587 : Float(1:28224, 576:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=576, kernel_shape=[3, 3], pads=[1, 1, 1, 1], strides=[2, 2]](%429, %588, %589)
  %432 : Float(1:28224, 576:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%587) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %590 : Float(1:7840, 160:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%432, %591, %592)
  %593 : Float(1:47040, 960:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%590, %594, %595)
  %437 : Float(1:47040, 960:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%593) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %596 : Float(1:47040, 960:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=960, kernel_shape=[3, 3], pads=[1, 1, 1, 1], strides=[1, 1]](%437, %597, %598)
  %440 : Float(1:47040, 960:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%596) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %599 : Float(1:7840, 160:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%440, %600, %601)
  %443 : Float(1:7840, 160:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Add(%590, %599) # /root/pytorch2onnx2tvm/MobileNetV2.py:62:0
  %602 : Float(1:47040, 960:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%443, %603, %604)
  %446 : Float(1:47040, 960:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%602) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %605 : Float(1:47040, 960:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=960, kernel_shape=[3, 3], pads=[1, 1, 1, 1], strides=[1, 1]](%446, %606, %607)
  %449 : Float(1:47040, 960:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%605) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %608 : Float(1:7840, 160:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%449, %609, %610)
  %452 : Float(1:7840, 160:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Add(%443, %608) # /root/pytorch2onnx2tvm/MobileNetV2.py:62:0
  %611 : Float(1:47040, 960:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%452, %612, %613)
  %455 : Float(1:47040, 960:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%611) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %614 : Float(1:47040, 960:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=960, kernel_shape=[3, 3], pads=[1, 1, 1, 1], strides=[1, 1]](%455, %615, %616)
  %458 : Float(1:47040, 960:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%614) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %617 : Float(1:15680, 320:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%458, %618, %619)
  %620 : Float(1:62720, 1280:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Conv[dilations=[1, 1], group=1, kernel_shape=[1, 1], pads=[0, 0, 0, 0], strides=[1, 1]](%617, %621, %622)
  %463 : Float(1:62720, 1280:49, 7:7, 7:1, requires_grad=1, device=cpu) = onnx::Clip[max=6., min=0.](%620) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1186:0
  %464 : Float(1:8960, 1280:7, 7:1, requires_grad=1, device=cpu) = onnx::ReduceMean[axes=[3], keepdims=0](%463) # /root/pytorch2onnx2tvm/MobileNetV2.py:110:0
  %465 : Float(1:1280, 1280:1, requires_grad=1, device=cpu) = onnx::ReduceMean[axes=[2], keepdims=0](%464) # /root/pytorch2onnx2tvm/MobileNetV2.py:110:0
  %466 : Float(1:1000, 1000:1, requires_grad=1, device=cpu) = onnx::Gemm[alpha=1., beta=1., transB=1](%465, %classifier.weight, %classifier.bias) # /usr/local/lib/python3.6/dist-packages/torch/nn/functional.py:1690:0
  return (%466)

Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('dense_nopack.x86', ('TENSOR', (1, 1280), 'float32'), ('TENSOR', (1000, 1280), 'float32'), None, 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('conv2d_NCHWc.x86', ('TENSOR', (1, 320, 7, 7), 'float32'), ('TENSOR', (1280, 320, 1, 1), 'float32'), (1, 1), (0, 0, 0, 0), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('conv2d_NCHWc.x86', ('TENSOR', (1, 960, 7, 7), 'float32'), ('TENSOR', (320, 960, 1, 1), 'float32'), (1, 1), (0, 0, 0, 0), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('depthwise_conv2d_NCHWc.x86', ('TENSOR', (1, 960, 7, 7), 'float32'), ('TENSOR', (960, 1, 3, 3), 'float32'), (1, 1), (1, 1, 1, 1), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('conv2d_NCHWc.x86', ('TENSOR', (1, 160, 7, 7), 'float32'), ('TENSOR', (960, 160, 1, 1), 'float32'), (1, 1), (0, 0, 0, 0), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('conv2d_NCHWc.x86', ('TENSOR', (1, 960, 7, 7), 'float32'), ('TENSOR', (160, 960, 1, 1), 'float32'), (1, 1), (0, 0, 0, 0), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('conv2d_NCHWc.x86', ('TENSOR', (1, 576, 7, 7), 'float32'), ('TENSOR', (160, 576, 1, 1), 'float32'), (1, 1), (0, 0, 0, 0), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('depthwise_conv2d_NCHWc.x86', ('TENSOR', (1, 576, 14, 14), 'float32'), ('TENSOR', (576, 1, 3, 3), 'float32'), (2, 2), (1, 1, 1, 1), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('conv2d_NCHWc.x86', ('TENSOR', (1, 96, 14, 14), 'float32'), ('TENSOR', (576, 96, 1, 1), 'float32'), (1, 1), (0, 0, 0, 0), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('conv2d_NCHWc.x86', ('TENSOR', (1, 576, 14, 14), 'float32'), ('TENSOR', (96, 576, 1, 1), 'float32'), (1, 1), (0, 0, 0, 0), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('conv2d_NCHWc.x86', ('TENSOR', (1, 384, 14, 14), 'float32'), ('TENSOR', (96, 384, 1, 1), 'float32'), (1, 1), (0, 0, 0, 0), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('depthwise_conv2d_NCHWc.x86', ('TENSOR', (1, 384, 14, 14), 'float32'), ('TENSOR', (384, 1, 3, 3), 'float32'), (1, 1), (1, 1, 1, 1), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('conv2d_NCHWc.x86', ('TENSOR', (1, 64, 14, 14), 'float32'), ('TENSOR', (384, 64, 1, 1), 'float32'), (1, 1), (0, 0, 0, 0), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('conv2d_NCHWc.x86', ('TENSOR', (1, 384, 14, 14), 'float32'), ('TENSOR', (64, 384, 1, 1), 'float32'), (1, 1), (0, 0, 0, 0), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('conv2d_NCHWc.x86', ('TENSOR', (1, 192, 14, 14), 'float32'), ('TENSOR', (64, 192, 1, 1), 'float32'), (1, 1), (0, 0, 0, 0), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('depthwise_conv2d_NCHWc.x86', ('TENSOR', (1, 192, 28, 28), 'float32'), ('TENSOR', (192, 1, 3, 3), 'float32'), (2, 2), (1, 1, 1, 1), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('conv2d_NCHWc.x86', ('TENSOR', (1, 32, 28, 28), 'float32'), ('TENSOR', (192, 32, 1, 1), 'float32'), (1, 1), (0, 0, 0, 0), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('conv2d_NCHWc.x86', ('TENSOR', (1, 192, 28, 28), 'float32'), ('TENSOR', (32, 192, 1, 1), 'float32'), (1, 1), (0, 0, 0, 0), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('conv2d_NCHWc.x86', ('TENSOR', (1, 144, 28, 28), 'float32'), ('TENSOR', (32, 144, 1, 1), 'float32'), (1, 1), (0, 0, 0, 0), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('depthwise_conv2d_NCHWc.x86', ('TENSOR', (1, 144, 56, 56), 'float32'), ('TENSOR', (144, 1, 3, 3), 'float32'), (2, 2), (1, 1, 1, 1), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('conv2d_NCHWc.x86', ('TENSOR', (1, 24, 56, 56), 'float32'), ('TENSOR', (144, 24, 1, 1), 'float32'), (1, 1), (0, 0, 0, 0), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('conv2d_NCHWc.x86', ('TENSOR', (1, 144, 56, 56), 'float32'), ('TENSOR', (24, 144, 1, 1), 'float32'), (1, 1), (0, 0, 0, 0), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('conv2d_NCHWc.x86', ('TENSOR', (1, 96, 56, 56), 'float32'), ('TENSOR', (24, 96, 1, 1), 'float32'), (1, 1), (0, 0, 0, 0), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('depthwise_conv2d_NCHWc.x86', ('TENSOR', (1, 96, 112, 112), 'float32'), ('TENSOR', (96, 1, 3, 3), 'float32'), (2, 2), (1, 1, 1, 1), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('conv2d_NCHWc.x86', ('TENSOR', (1, 16, 112, 112), 'float32'), ('TENSOR', (96, 16, 1, 1), 'float32'), (1, 1), (0, 0, 0, 0), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('conv2d_NCHWc.x86', ('TENSOR', (1, 32, 112, 112), 'float32'), ('TENSOR', (16, 32, 1, 1), 'float32'), (1, 1), (0, 0, 0, 0), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('depthwise_conv2d_NCHWc.x86', ('TENSOR', (1, 32, 112, 112), 'float32'), ('TENSOR', (32, 1, 3, 3), 'float32'), (1, 1), (1, 1, 1, 1), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('conv2d_NCHWc.x86', ('TENSOR', (1, 3, 224, 224), 'float32'), ('TENSOR', (32, 3, 3, 3), 'float32'), (2, 2), (1, 1, 1, 1), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('depthwise_conv2d_NCHWc.x86', ('TENSOR', (1, 144, 56, 56), 'float32'), ('TENSOR', (144, 1, 3, 3), 'float32'), (1, 1), (1, 1, 1, 1), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('depthwise_conv2d_NCHWc.x86', ('TENSOR', (1, 192, 28, 28), 'float32'), ('TENSOR', (192, 1, 3, 3), 'float32'), (1, 1), (1, 1, 1, 1), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
Cannot find config for target=llvm -keys=cpu -link-params=0, workload=('depthwise_conv2d_NCHWc.x86', ('TENSOR', (1, 576, 14, 14), 'float32'), ('TENSOR', (576, 1, 3, 3), 'float32'), (1, 1), (1, 1, 1, 1), (1, 1), 'NCHW', 'NCHW', 'float32'). A fallback configuration is used, which may bring great performance regression.
404
Time elapsed is 3m 1s
```



### 2.4 后记

这一篇仅仅是带大家了解一下什么是TVM以及一个简单例子的使用，在接下来的文章中会涉及到部分TVM设计结构和源码的解析。可能涉及到的知识点有：

- 简单编译器原理
- C++特殊语法以及模板元编程
- 神经网络模型优化过程
- 代码部署

等等，随时可能会进行变化。

人工智能已经开始进入嵌入式时代，各式各样的AI芯片即将初始，将复杂的网络模型运行在廉价低功耗的板子上可能也不再是遥不可及的幻想，不知道未来会是怎么样，但TVM这个框架已经开始走了一小步。