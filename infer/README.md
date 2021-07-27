# 嵌入式Linux平台部署AI神经网络模型Inference的方案

⌚️:2020年11月30日

📚参考

---

## ONNX

- 简述
  ONNX是一种AI神经网络模型的通用中间文件保存方法(可以理解成AI世界的XML)，各种AI框架，Inference引擎，甚至OpenCV里面的dnn onnx相关的模块都可以解析ONNX文件并生成特定平台和运行框架所支持的神经网络模型。ONNX本身不是AI神经网络运行框架，只是AI神经网络模型通用中间描述文件格式
- GitHub链接
  [https://github.com/onnx/onnx](https://links.jianshu.com/go?to=https%3A%2F%2Fgithub.com%2Fonnx%2Fonnx)
- 编程语言
  C++ / Python
- 热度
  5星

## TensorRT

- 简述
  TensorRT是NVIDIA家的开源AI神经网络Inference引擎，支持解析和转换ONNX格式的神经网络模型部署到支持CUDA的GPU上运行。目前TensorRT仅支持在NVIDIA家的产品部署AI神经网络模型，支持的平台有NVIDIA各种支持CUDA 9.0以上的显卡，嵌入式SOC平台(Jetson TX1/TX2/Nano/Xavier 等)
- GitHub链接
  [https://github.com/NVIDIA/TensorRT](https://links.jianshu.com/go?to=https%3A%2F%2Fgithub.com%2FNVIDIA%2FTensorRT)
- 编程语言
  C++
- 热度
  3星

## MNN

- 简述
  MNN是阿里家开源的一款嵌入式Linux/Android平台的嵌入式AI神经网络Inference引擎。它在系统底层对ARM CPU代码进行系统级优化，可以调配ARM CPU + GPU的算力资源进行AI神经网络Inference运算。由于后发优势，加上贾扬清大神入职阿里的加成，目前业界评价MNN对很多AI神经网络在性能上的优化目前要优于ncnn, 这是后发优势，也许ncnn会进一步升级赶上。目前由于MNN开源时间还不长，star数目小于ncnn
- GitHub链接
  [https://github.com/alibaba/MNN](https://links.jianshu.com/go?to=https%3A%2F%2Fgithub.com%2Falibaba%2FMNN)
- 编程语言
  C++ / 少量 C语言
- 热度
  4星

## ncnn

- 简述
  ncnn是腾讯家开源的一款嵌入式跨平台平台的嵌入式AI神经网络Inference引擎。它在系统底层对ARM CPU代码进行系统级优化，可以调配ARM CPU + GPU的算力资源进行AI神经网络Inference运算。ncnn比MNN开源更早，不过它看起来更专注于Android平台，对Android系统平台优化得更好
- GitHub链接
  [https://github.com/Tencent/ncnn](https://links.jianshu.com/go?to=https%3A%2F%2Fgithub.com%2FTencent%2Fncnn)
- 编程语言
  三分之二 C++ / 三分之一 C语言
- 热度
  5星

## TVM

- 简述
  TVM是青年学者陈天奇主导的跨平台基于编译方法部署的AI神经网络部署的方法。TVM项目的想法是做AI神经网络界的LLVM神经网络编译器，通过跨平台交叉编译的方法，将AI神经网络编译成目标平台的运行库，然后在tvm runtime运行。tvm runtime本身不依赖其它第三方库。
- GitHub链接
  [https://github.com/dmlc/tvm](https://links.jianshu.com/go?to=https%3A%2F%2Fgithub.com%2Fdmlc%2Ftvm)
- 编程语言
  C++ / Python
- 热度
  4星半

## TensorFlow Lite

- 简述
  TensorFlow Lite是一款用于部署在移动设备上基于TensorFlow框架训练的的AI神经网络模型的一个工具。由于Android TensorFlow TensorFlow Lite都是Google家的产品，所以TensorFlow对Google家的Android设备有天然兼容性和生态，目前在Android平台使用比较多
- 链接
  [https://www.tensorflow.org/lite](https://links.jianshu.com/go?to=https%3A%2F%2Fwww.tensorflow.org%2Flite)
  [https://github.com/tensorflow/tensorflow/tree/master/tensorflow/lite](https://links.jianshu.com/go?to=https%3A%2F%2Fgithub.com%2Ftensorflow%2Ftensorflow%2Ftree%2Fmaster%2Ftensorflow%2Flite)
- 编程语言
  C++ / Python
- 热度
  6星

## ArmNN

- 简述
  ArmNN是Arm公司开源的基于arm嵌入式设备的inference框架，在Arm Cortex-A CPUs、Arm Mali GPUs、Arm Machine Learning processor都可以达到很高的加速效果。不过可惜的是，由于缺乏文档及教程，该框架在国内推广的程度不高，目前Github的更新迭代速度也不快。相对于其他AI神经网络Inference框架如NCNN、Tengine、MNN等等，ArmNN的知名度显得很小。不过有用户反馈ArmNN对ARM芯片上的算力进行统一管理和加速的效果很好，是一个被低估的框架
- GitHub链接
  [https://github.com/ARM-software/armnn](https://links.jianshu.com/go?to=https%3A%2F%2Fgithub.com%2FARM-software%2Farmnn)
- 编程语言
  C++
- 热度
  2星

## Tengine

- 简述
  Tengine 是OPEN AI LAB公司开发的针对ARM公司中高端应用级CPU Cortex-A系列(参考CPU Cortex-A72) 开发的AI神经网络Inference引擎。同时支持Linux和Android系统，目前项目更新迭代速度并不快
- GitHub链接
  [https://github.com/OAID/Tengine](https://links.jianshu.com/go?to=https%3A%2F%2Fgithub.com%2FOAID%2FTengine)
- 编程语言
  C++ / 少量 C语言
- 热度
  2星半

## Tengine-lite

- 简述
  Tengine 是OPEN AI LAB公司开发的针对ARM公司中低端实时控制级 Cortex-M 开发的AI神经网络Inference引擎，纯C语言打造，支持RTOS系统，是目前少有的支持嵌入式裸机和RTOS系统的AI神经网络Inference引擎
- GitHub链接
  [https://github.com/OAID/Tengine-lite](https://links.jianshu.com/go?to=https%3A%2F%2Fgithub.com%2FOAID%2FTengine-lite)
- 编程语言
  C语言
- 热度
  1星

## Mace

- 简述
  Mace是小米公司开发的一款支持ARM Cortex-A 系列手机级CPU的神经网络AI Inference引擎。能够同时管理调度CPU 和 GPU的算力，支持Windows, Linux, Android等多个系统，对高通手机开发平台的支持和优化做得比较出色。
- 编程语言
  C++ / 少量 Python和C语言
- GitHub链接
  [https://github.com/XiaoMi/mace](https://links.jianshu.com/go?to=https%3A%2F%2Fgithub.com%2FXiaoMi%2Fmace)
- 热度
  3星半

## Paddle-Mobile

- 简述
  Paddle-Mobile是百度家的一款嵌入式AI神经网络Infrence框架， 中文名叫飞桨，高性能支持ARM CPU，支持Mali GPU， 支持Andreno GPU， 支持苹果设备的GPU Metal实现，支持ZU5、ZU9等FPGA开发板，支持树莓派等arm-linux开发板。目前在中文开源资料比较丰富
- GitHub链接
  [https://github.com/PaddlePaddle/paddle-mobile](https://links.jianshu.com/go?to=https%3A%2F%2Fgithub.com%2FPaddlePaddle%2Fpaddle-mobile)
- 编程语言
  C++ / 少量 C语言
- 热度
  4星

## OpenCV dnn

- 简述
  dnn 是opencv里面用于deep learning AI神经网络inference的一个模块(据说有training的功能，但是一般不用)。dnn模块从opencv 3.1开始就在opencv_contrib库里面，在3.3版中，它被提到了主仓库中。新版OpenCV dnn模块目前支持Caffe、TensorFlow、Torch、PyTorch等深度学习框架。从3.4开始，dnn模块开始支持onnx格式的AI神经网络模型部署。
  opencv dnn模块相比于其它AI神经网络 Inference引擎优点在于它依托于Opencv这个传统的计算机视觉库，有大量的传统视觉，图像预处理和后处理相关的api函数可以用，并且格式兼容。另外dnn只依赖于opencv, 不依赖其它的库，所以可以和opencv一起部署的嵌入式Linux(不是Ubuntu, Debian, Android这种发行版系统)最小系统上，可以运用到各种更细分的领域。
  当然opencv dnn赶上时代潮流，进入opencv主仓库的时间比较晚，支持的AI神经网络模型并不算多，速度和计算精度性能优化不是特别好，版本迭代速度也不快，相比于其它家互联网公司主推的AI Inference引擎，其对gpu, cpu统一计算资源管理优化程度可能也不算特别好。不过从Opencv 4.x以后的版本看，dnn模块越来越受官方重视，建议大家尝试4.x以后的版本。
- GitHub链接
  [https://github.com/opencv/opencv/tree/master/modules/dnn](https://links.jianshu.com/go?to=https%3A%2F%2Fgithub.com%2Fopencv%2Fopencv%2Ftree%2Fmaster%2Fmodules%2Fdnn)
- 编程语言
  C++ / 少量 C语言
- 热度
  3星半

## Dlib

- 简述
  Dlib是一个现代C++语言编写的工具包，包含机器学习算法和工具，用于用C++创建复杂的软件来解决现实世界中的问题。它被广泛应用于工业和学术界，包括机器人、嵌入式设备、移动电话和大型高性能计算环境。
  Dlib 在传统机器学习领域的算法库非常丰富，但是深度学习领域进入比较晚，支持的模型不算最新。不过Dlib在人脸识别领域，关键点识别做得还是不错，并且可以和OpenCV的Mat格式进行转换兼容，这样配合Opencv做人脸识别应该是不错的选择。不过Dlib的中文资料略少。
- GitHub链接
  [https://github.com/davisking/dlib](https://links.jianshu.com/go?to=https%3A%2F%2Fgithub.com%2Fdavisking%2Fdlib)
- 编程语言
  C++
- 热度
  3星半

