# 🍭理论篇

## 1⃣️ 数学

## 2⃣️ 语言

### 🎋C++[🐾](theory/cpp/README.md)

### 🎋Python[🐾](theory/python/README.md)

#### 🐾 深度之眼👀

- [第二章  Python基本语法元素.ipynb](theory/python/eyes/02.ipynb)
- [第三章 基本数据类型.ipynb](theory/python/eyes/3.ipynb)
- [第四章 组合数据类型.ipynb](theory/python/eyes/4.ipynb)
- [第五章 程序控制结构.ipynb](theory/python/eyes/5.ipynb)
- [第六章 函数.ipynb](theory/python/eyes/6.ipynb)
- [第七章 类——面向对象的编程.ipynb](theory/python/eyes/7.ipynb)
- [第八章 文件、异常和模块.ipynb](theory/python/eyes/8.ipynb)
- [第九章 有益的探索.ipynb](theory/python/eyes/9.ipynb)
- [第十章   Python标准库.ipynb](theory/python/eyes/10.ipynb)
- [第十一章 Numpy库.ipynb](theory/python/eyes/11.ipynb)
- [第十二章   Pandas 库.ipynb](theory/python/eyes/12.ipynb)
- [第十三章 Matplotlib库.ipynb](theory/python/eyes/13.ipynb)
- [第十四章 scikit-learn 库.ipynb](theory/python/eyes/14.ipynb)
- [第十五章 再谈编程.ipynb](theory/python/eyes/15.ipynb)

#### 🐾 Numpy

- [Axis](theory/python/numpy_axis.md)
- [argmax、...、11个函数](theory/python/numpy_funs.md)
- [控制流程](theory/python/numpy_control.md)

#### 🐾 Python函数

- [Python下划线](https://blog.spoock.com/2016/09/23/python-underline-note/)
- [查看类型、内存地址、占用空间大小；...;等15个函数](theory/python/funs.md)
- [Python 类](theory/python/class.md)
- [pdb调试工具](theory/python/pdb.md)
- [OS模块](theory/python/os.md)
- [SYS模块](theory/python/sys.md)
- [Argparse模块](theory/python/argparse.md)
- [logging 模块](theory/python/logging.md)
- [多进程&多线程](theory/python/multi_proccess.md) --> [处理库futures](theory/python/futures.md)
- [类型转换](theory/python/change_type.md)
- [collections模块](https://www.liaoxuefeng.com/wiki/1016959663602400/1017681679479008)
- [Map | Reduce](https://www.liaoxuefeng.com/wiki/1016959663602400/1017329367486080)

- [如何计算topk](theory/python/topk.md)

# 🍭环境篇

## 1⃣️ 安装篇

### 🎋 GPU知识

- 🐾 [深入GPU硬件架构及运行机制](https://www.cnblogs.com/timlly/p/11471507.html)
- 🐾 [gpustat](https://github.com/wookayin/gpustat)
- 🐾 [nvidia-smi命令](envs/gpus/nvidia_smi.md)
- 🐾 [NUMA & GPU](envs/gpus/numa.md)
- 🐾 [GPU Direct](envs/gpus/gpudirect.md)

### 🎋 GPUs训练环境安装

### 🎋 推理环境安装

### 🎋 IDE&Tools安装

## 2⃣️ Pytorch

### 🎋Pytorch分布式[🐾](https://github.com/FelixFu-TD/Parallel-Pytorch)

### 🎋Pytorch1.4学习[📒](https://github.com/TD-4/Pytorch1.4)

### 🎋Pytorch函数学习

- 🐾 [clone、detached、copy](envs/pytorch/clone_detache.md)
- 🐾 [expand & repeat](envs/pytorch/expand_repeat.md)
- 🐾 [cat & stack](envs/pytorch/cat_stack.md)
- 🐾 [transpose & permute](envs/pytorch/transpose_permute.md)
- 🐾 [contiguous](envs/pytorch/contiguous.md)
- 🐾 [squeeze & unsqueeze](envs/pytorch/squeeze_unsqueeze.md)
- 🐾 [max, argmax, size, clamp, sum, topk](envs/pytorch/max_argmax.md)
- 🐾 [train、eval](envs/pytorch/train_eval.md)
- 🐾 [权重加载修改名称](envs/pytorch/load_weights.md)
- 🐾 [上采样：interpolate、PixelShuffle](envs/pytorch/upsample.md)
- [scatter](envs/pytorch/scatter.md)

## 3⃣️ 工具

### 🎋 图像预处理

- 🐾 [图像标注工具labelme](https://github.com/wkentaro/labelme)
- 🐾 [图像去重工具imagededup](https://github.com/idealo/imagededup)
- 🐾 [图像增强工具imgaug](https://github.com/aleju/imgaug)

# 🍭训练篇&部署篇

## 1⃣️ 检查数据

## 2⃣️训练模型--train e ↓

### 🎋数据预处理

#### 🐰 数据集介绍
- 🐾 [VOC](train/preprocess/voc.md)
- 🐾 [COCO](train/preprocess/coco.md)
- 🐾 [Cityscapaces](https://github.com/mcordts/cityscapesScripts)

#### 🐰 特征缩放[🐾](train/preprocess/featurescale.md)

#### 🐰 Pytorch数据读取

- 🐾 [加速训练 —提高 GPU 利用率](train/preprocess/loaddata.md)
- 🐾 [加速训练—节约显存](train/preprocess/save_mem.md)

#### 🐰 Python读取图片

- 🐾 [计算图片均值](train/preprocess/mean_cal.md)
- 🐾 [opencv读取数据--segmentation fault](train/preprocess/sefgmentationfault.md)
- 🐾 [直方图处理](train/preprocess/histogram.md)
- 🐾 [python读取图片的几种方式](train/preprocess/open_image.md)

### 🎋 网络模型

#### 🐰 机器学习

- 🐾 [最小二乘法](train/ml/least_square.md)
- 🐾 [kmeans](train/ml/kmeans.md)

#### 🐰 NN

- 🐾  [NN发展史](train/nn/history.md)
- 🐾  [45分钟理解深度神经网络和深度学习-拟合角度](http://staff.ustc.edu.cn/~lgliu/Resources/DL/What_is_DeepLearning.html) 
- 🐾 零基础入门深度学习- [感知器](https://www.zybuluo.com/hanbingtao/note/433855)-[线性单元和梯度下降](https://www.zybuluo.com/hanbingtao/note/448086)-[神经网络和反向传播算法](https://www.zybuluo.com/hanbingtao/note/476663)-[卷积神经网络](https://www.zybuluo.com/hanbingtao/note/485480)-[循环神经网络](https://zybuluo.com/hanbingtao/note/541458)-[长短时记忆网络(LSTM)](https://zybuluo.com/hanbingtao/note/581764)-[递归神经网络](https://zybuluo.com/hanbingtao/note/626300)

#### 🐰CNN

- 🐾  [CNN介绍](train/cnn/introduce_cnn.md) --[🐾CNN网络代码讲解](https://github.com/WZMIAOMIAO/deep-learning-for-image-processing)
- 🐾  [LeNet, AlexNet, VGG](train/cnn/lenet_alexnet_vgg.md)
- 🐾  [DSC理解](train/cnn/dsc.md)
- 🐾  [Inception](train/cnn/inception.md)
- 🐾  [ResNet](train/cnn/resnet.md)
- 🐾  [DenseNet](train/cnn/densenet.md)
- 🐾  [MobileNet](train/cnn/mobilenet.md)
- 🐾  [SENet](train/cnn/senet.md)
- 🐾 [EfficientNet](train/cnn/efficientnet.md)
- 🐾  [conv 1* 1的作用](train/cnn/conv1.md)
- 🐾 [上采样](train/cnn/up.md)

#### 🐰RNN/NLP

- 🐾  [NLP学习路线](train/rnn/introduce_rnn.md)
- 🐾  [Attention]
- 🐾  [Transformer]

#### 🐰GAN

#### 🐰Detection

- 🐾 [RCNNs](train/detection/rcnns.md)
- 🐾 YOLO
  - [yolo v1](train/detection/yolov1.md)
  - [yolo v2](train/detection/yolov2.md)
  - [yolo v3](train/detection/yolov3.md)
  - [yolo v4](train/detection/yolov4.md)

#### 🐰Segmentation

- 🐾 [分割综述(2020)](train/segmentation/introduce.md)
- 🐾 [UNet Family](https://github.com/ShawnBIT/UNet-family)
  - [unet](train/segmentation/unet.md)
  - [UNet++](train/segmentation/unetpp.md)
- 🐾 [PSPNet](train/segmentation/pspnet.md)
- 🐾 [DUC & HDC](train/segmentation/duc_hdc.md)

### 🎋 损失函数

- 🐾 [交叉墒](train/loss/entropy.md)
- 🐾 [Pytorch的损失函数](train/loss/losses_pytorch.md)
- Lovasz-Softmax Loss
- Exponential Logarithmic loss
- Focal Loss + Dice Loss
- BCE + Dice Loss
- Generalized Dice loss
- Tversky Loss
- IOU Loss
- Dice Loss
- Focal Loss

### 🎋 优化器

- 🐾 [优化器整理](train/optim/introduce.md)
- 🐾 [一阶梯度下降](train/optim/sgd.md)

#### 🐰 BP求导

- [矩阵向量求导](train/optim/matrix_bp.md)
- [深度神经网络（DNN）模型与前向/反向传播算法](train/optim/bpdnn.md)---->[DNN - 反向传播算法(特详细)](train/optim/bp.md)---->[手动实现DNN](https://github.com/FelixFu-TD/dl-by-hand)
- [深度神经网络（CNN）模型与前向/反向传播算法](train/optim/bpcnn1.md)---->[CNN-反向传播算法](train/optim/bpcnn.md) ---->[手动实现CNN](https://github.com/FelixFu-TD/dl-by-hand)

### 🎋 评价指标

- [语义分割评价指标](train/assessment/seg_metris.md)
- [mAP](train/assessment/map.md) [code](https://github.com/TD-4/mAP)
- IOU

### 🎋 网络可视化

#### 🐰权重、梯度、特征图可视化

- 🐾 [网络中间层显示工具CAM](https://github.com/frgfm/torch-cam)  🐾 [blog](https://cloud.tencent.com/developer/article/1674200)
- 🐾 [模型权重理解DeepDream](https://github.com/TD-4/Pytorch-Deep-Dream)
- 🐾 [网络结构显示工具权重/梯度/特征图/混淆矩阵tensorboard](https://github.com/TD-4/PyTorch_Tutorial)
- 🐾 [网络显示工具visdon](https://github.com/fossasia/visdom)

#### 🐰网络结构

- 🐾 [网络结构显示工具torchsuammary](https://github.com/sksq96/pytorch-summary)  🐾 [debug](train/visual/torchsummary.md)
- 🐾 [网络结构显示工具Netron](https://github.com/lutzroeder/netron)

### 🎋 梯度消失与爆炸/欠拟合[🐾](train/fit/grad.md)

1. 预训练加微调
2. 🐾 [权重初始化](train/fit/init.md)
3. 梯度剪切、权重正则（针对梯度爆炸）
4. 🐾 使用不同的[激活函数](train/fit/activation.md)
5. 🐾 使用[batchnorm](train/fit/batchnorm.md)
6. 使用残差结构
7. 使用LSTM网络


### 🎋 Tips

- 🐾  [深度学习训练流程](train/tips/train_flow.md)
- 🐾  [提高性能的4个角度](train/tips/improve_performence.md)
- 🐾  [固定种子](train/tips/random_seed.md)
- 🐾 [混合精度训练](train/tips/apex.md), 🐾 [apex](https://github.com/NVIDIA/apex) 🐾 [apex+tensorcore+ngc](https://developer.nvidia.com/automatic-mixed-precision)
- 🐾 [TensorCore](train/tips/tensorcore.md)
- 🐾 [DeepLearningExamples NVIDIA-各种加速和demo](https://github.com/NVIDIA/DeepLearningExamples)
- 🐾 [学习率调整策略](train/tips/scheduler.md)

## 3⃣️测试模型--train e↔︎test e ↓

### 🎋 过拟合[🐾](train/overfitting/introduce_overfitting.md)

- 🐾 [正则化](train/overfitting/regularization.md)
- early stop
- 数据增强
- dropout
- ...

## 4⃣️ 微调/迁移学习

- 随机网格搜索
- 超参数优化

## 5⃣️ 压缩&部署

### 🎋 数据后处理

### 🎋 部署框架 [🐾](infer/README.md)

####  🐰ONNX

- [ONNX介绍](infer/onnx/introduce.md) 
- [ONNX API Python](infer/onnx/python_api.md) | [ONNX Tutorials](https://github.com/TD-4/onnx-tutorial)
- [ONNX支持框架有哪些](https://onnx.ai/supported-tools.html)

####  🐰 TVM

####  🐰TensorRT

# 🍭项目篇

### 🎋分类

- #### 🐾 [classification](https://github.com/FelixFu520/classification)

### 🎋语义分割

- #### 🐾 [segmentation](https://github.com/FelixFu520/segmentation)

### 🎋目标检测

- #### 🐾 [detection](https://github.com/FelixFu520/detection)

### 🎋[小样本](notes/fsl/README.md)

- 🐾 PANet-[🐙](https://github.com/FelixFu520/PANet) [📒](notes/fsl/panet.md)

### 🎋[图像质量评价](notes/iqa/README.md)

- 🐾 hyperIQA-[🐙](https://github.com/FelixFu520/hyperIQA)[📒](notes/iqa/hypernet.md)



