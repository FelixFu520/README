# 🍭理论篇

### 🍀数学

### 🍀语言

# 🍭环境篇

### 🍀系统



# 🍭训练篇&部署篇

## 1⃣️ 检查数据

## 2⃣️训练模型--train e ↓

### 🍀数据预处理

- #### 🎋数据集介绍
  - 🐾[VOC](train/preprocess/voc.md)
  - 🐾[COCO](train/preprocess/coco.md)
  - 🐾[Cityscapaces](https://github.com/mcordts/cityscapesScripts)

- #### 🎋特征缩放[🐾](train/preprocess/featurescale.md)

- #### 🎋Pytorch数据读取

  - 🐾[加速训练 —提高 GPU 利用率](train/preprocess/loaddata.md)
  - 🐾[加速训练—节约显存](train/preprocess/save_mem.md)
  
- #### 🎋Python读取图片

  - 🐾 [计算图片均值](train/preprocess/mean_cal.md)
  - 🐾[opencv读取数据--segmentation fault](train/preprocess/sefgmentationfault.md)
  - 🐾[直方图处理](train/preprocess/histogram.md)

### 🍀网络模型

- #### 🎋 NN

  - 🐾 [NN发展史]
  - 🐾 [45分钟理解深度神经网络和深度学习-拟合角度](http://staff.ustc.edu.cn/~lgliu/Resources/DL/What_is_DeepLearning.html) 

- #### 🎋CNN

  - 🐾 [CNN介绍](train/cnn/introduce_cnn.md)
  - 🐾 [LeNet, AlexNet, VGG](train/cnn/lenet_alexnet_vgg.md)
  - 🐾 [DSC理解](train/cnn/dsc.md)
  - 🐾 [Inception](train/cnn/inception.md)
  - 🐾 [ResNet](train/cnn/resnet.md)
  - 🐾 [DenseNet](train/cnn/densenet.md)
  - 🐾 [MobileNet](train/cnn/mobilenet.md)
  - 🐾 [SENet](train/cnn/senet.md)
  -  🐾[conv 1* 1的作用](train/cnn/conv1.md)

- #### 🎋RNN/NLP

  - 🐾 [NLP学习路线](train/rnn/introduce_rnn.md)
  - 🐾 [Attention]
  - 🐾 [Transformer]

- #### 🎋GAN

- #### 🎋Detection

- #### 🎋Segmentation

  - 🐾UNet

### 🍀损失函数

### 🍀优化器

### 🍀评价指标

- mAP
- IOU

### 🍀网络可视化

### 🍀梯度消失与爆炸/欠拟合[🐾](train/fit/grad.md)

1. 预训练加微调
2. [权重初始化](train/fit/init.md)
3. 梯度剪切、权重正则（针对梯度爆炸）
4. 使用不同的激活函数
5. 使用batchnorm
6. 使用残差结构
7. 使用LSTM网络


### 🍀Tips

- 🐾 [深度学习训练流程](tips/train_flow.md)
- 🐾 [提高性能的4个角度](train/tips/improve_performence.md)
- 🐾 [固定种子](train/tips/random_seed.md)

## 3⃣️测试模型--train e↔︎test e ↓

### 🍀过拟合

- [正则化1](regularization.md) [2](../models/dl/notes/network-bn.md) [3](../models/dl/notes/network-dnnnorm.md)
- early stop
- 数据增强
- dropout
- ……

## 4⃣️ 微调/迁移学习

- 随机网格搜索
- 超参数优化

## 5⃣️ 压缩&部署

### 🍀 数据后处理

### 🍀 部署框架

- ####  🎋ONNX

- ####  🎋 TVM

- ####  🎋TensorRT

# 🍭项目篇



