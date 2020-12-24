**21.r-cnn，fast-r-cnn、faster-r-cnn三者的区别？**

CNN流行之后，Szegedy做过将detection问题作为回归问题的尝试（Deep Neural Networks for Object Detection），但是效果差强人意，在VOC2007上mAP只有30.5%。既然回归方法效果不好，而CNN在分类问题上效果很好，那么为什么不把detection问题转化为分类问题呢？

RBG的RCNN使用region proposal（具体用的是Selective Search Koen van de Sande: Segmentation as Selective Search for Object Recognition）来得到有可能得到是object的若干（大概10^3量级）图像局部区域，然后把这些区域分别输入到CNN中，得到区域的feature，再在feature上加上分类器，判断feature对应的区域是属于具体某类object还是背景。当然，RBG还用了区域对应的feature做了针对boundingbox的回归，用来修正预测的boundingbox的位置。 RCNN在VOC2007上的mAP是58%左右。

RCNN存在着重复计算的问题（proposal的region有几千个，多数都是互相重叠，重叠部分会被多次重复提取feature），于是RBG借鉴Kaiming He的SPP-net的思路单枪匹马搞出了Fast-RCNN，跟RCNN最大区别就是Fast-RCNN将proposal的region映射到CNN的最后一层conv layer的feature map上，这样一张图片只需要提取一次feature，大大提高了速度，也由于流程的整合以及其他原因，在VOC2007上的mAP也提高到了68%。 探索是无止境的。

Fast-RCNN的速度瓶颈在Region proposal上，于是RBG和Kaiming He一帮人将Region proposal也交给CNN来做，提出了Faster-RCNN。Fater-RCNN中的region proposal netwrok实质是一个Fast-RCNN，这个Fast-RCNN输入的region proposal的是固定的（把一张图片划分成n\*n个区域，每个区域给出9个不同ratio和scale的proposal），输出的是对输入的固定proposal是属于背景还是前景的判断和对齐位置的修正（regression）。Region proposal network的输出再输入第二个Fast-RCNN做更精细的分类和Boundingbox的位置修正。

Fater-RCNN速度更快了，而且用VGG net作为feature extractor时在VOC2007上mAP能到73%。个人觉得制约RCNN框架内的方法精度提升的瓶颈是将dectection问题转化成了对图片局部区域的分类问题后，不能充分利用图片局部object在整个图片中的context信息。

**22.神经网络中，哪些方法可以防止过拟合？**

① Dropout ② 加L1/L2正则化 ③ BatchNormalization

**23.CNN关键层有哪些？**

① 输入层，对数据去均值，做data augmentation等工作 ② 卷积层，局部关联抽取feature ③ 激活层，非线性变化 ④ 池化层，下采样 ⑤ 全连接层，增加模型非线性 ⑥ 高速通道，快速连接 ⑦ BN层，缓解梯度弥散

**24.GRU是什么？GRU对LSTM做了哪些改动？**

GRU是Gated Recurrent Units，是循环神经网络的一种。 GRU只有两个门（update和reset），LSTM有三个门（forget，input，output），GRU直接将hidden state 传给下一个单元，而LSTM用memory cell 把hidden state 包装起来。

**25.IOU评价函数**

在目标检测的评价体系中，有一个参数叫做 IoU ，简单来讲就是模型产生的目标窗口和原来标记窗口的交叠率。 具体我们可以简单的理解为：即检测结果DetectionResult与真实值Ground Truth的交集比上它们的并集，即为检测的准确率 IoU :
![](https://julyedu-img-public.oss-cn-beijing.aliyuncs.com/Public/Image/Question/1525494665_290.png)

举个例子，下面是一张原图 ![](https://julyedu-img-public.oss-cn-beijing.aliyuncs.com/Public/Image/Question/1525495290_937.png)

然后我们对其做下目标检测，其DR = DetectionResult，GT = GroundTruth。 ![](https://julyedu-img-public.oss-cn-beijing.aliyuncs.com/Public/Image/Question/1525494780_911.png) 

黄色边框框起来的是： DR⋂GT 绿色框框起来的是： DR⋃GT 不难看出，最理想的情况就是DR与GT完全重合，即IoU = 1。

**26.当神经网络调参效果不好时，应该从哪几个方面考虑？**

1）是否找到合适的损失函数？（不同问题适合不同的损失函数）（理解不同损失函数的适用场景）

2）batch size是否合适？batch size太大 -> loss很快平稳，batch size太小 -> loss会震荡（理解mini-batch）

3）是否选择了合适的激活函数？（各个激活函数的来源和差异） 4）学习率，学习率小收敛慢，学习率大loss震荡（怎么选取合适的学习率） 5）是否选择了合适的优化算法？（比如adam）（理解不同优化算法的适用场景） 6）是否过拟合？(深度学习拟合能力强，容易过拟合)（理解过拟合的各个解决方案） a. Early Stopping b. Regularization（正则化） c. Weight Decay（收缩权重） d. Dropout（随机失活）e. 调整网络结构
