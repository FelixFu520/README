# 利用TensorRT对深度学习进行加速
## 一、前言
TensorRT是什么，TensorRT是英伟达公司出品的高性能的推断C++库，专门应用于边缘设备的推断，TensorRT可以将我们训练好的模型分解再进行融合，融合后的模型具有高度的集合度。例如卷积层和激活层进行融合后，计算速度可以就进行提升。当然，TensorRT远远不止这个：
![](../imgs/trt-info.png)  
我们平时所见到了深度学习落地技术：模型量化、动态内存优化以及其他的一些优化技术TensorRT都已经有实现，更主要的，其推断代码是直接利用cuda语言在显卡上运行的，所有的代码库仅仅包括C++和cuda，当然也有python的包装,我们在利用这个优化库运行我们训练好的代码后，运行速度和所占内存的大小都会大大缩减。
![](../imgs/trt-workflow.png)   
总之，这个库是所有需要部署同志需要理解并精通的一项技能，毕竟Nvidia自己开发的，性能相比其他类似产品当然是最好的(目前该库貌似并不开源)。   
## 二、TensorRT
那我们开始使用它吧，之后TensorRT简称为TRT。

其实类似TensorRT具体工作的有很多，例如[TVM](https://github.com/dmlc/tvm/)、[TC(Tensor Comprehensions)](https://github.com/facebookresearch/TensorComprehensions)，都做了一些类似于TensorRT的工作，将训练好的模型转化为运行在特定端(例如GPU)的进行模型优化等一系列操作后的代码，从而达到快速预测的效果。

那么为什么要选择TensorRT呢？很简单，因为我们目前主要使用的还是Nvidia的计算设备，在Nvidia端的话肯定要用Nvidia亲儿子了。

## Reference
[1] https://oldpan.me/archives/use-tensorrt-speed-up-deep-learning-1