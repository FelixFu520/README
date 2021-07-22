# Inception Net/GoogLeNet

⌚️: 2021-07-21

📚参考

---

## **Inception Net V1 (GoogLeNet)**

> 论文链接：[Going Deeper with Convolutions](https://link.zhihu.com/?target=https%3A//arxiv.org/pdf/1409.4842.pdf), 发表时间：2014.09

2014 年，Google 提出了 Inception 网络结构，并以此构建了 GoogLeNet（之所以这样命名，是为了向LeNet致敬；此外，GoogLeNet 也经常被称为 Inception Net V1，而该论文经常被称为 Inception V1），从而在同年的 ImageNet Challenge 的分类与检测（Detection）任务上夺得第一名。

与 VGG 不同，Inception 结构虽然也倾向于加“深”网络结构，从而提高模型的表达能力，但是作者充分考虑到现实中计算资源的限制，所以对模型中局部结构进行了精心设计，并且抛弃全连接层（虽然 GoogLeNet 最后加了一层全连接层，但这是作者为了其他人能更方便的利用模型进行微调（Finetune））。

![img](imgs\v2-7694e6d9a0d20d6c0da53bc81d6a2e34_720w.jpg)

作者在文中指出，提高模型表达能力的最直接的办法就是增加模型的“大小”，而这又会导致两个问题的产生：

- **模型越大，其网络参数也就越大，就越容易产生过拟合现象，所以就需要更大的数据集，然而大型数据集的构建成本是很高昂的；**
- **模型越大，对于计算资源的需求就越大，这在现实任务中是难以接受的**。

而作者认为解决这两个问题的基本方法是**将全连接层，甚至是卷积层改为稀疏的网络结构**。（作者还在文中指出，GoogLeNet 的参数仅有 AlexNet 的 1/12，而 AlexNet 的全连接层的参数量甚至占到了自身参数量的 90% 以上）

![img](imgs\v2-efdcd0a43a6ae33a27d8c3238df0f8c7_720w.jpg)

受到 [Network In Network](https://link.zhihu.com/?target=https%3A//arxiv.org/pdf/1312.4400.pdf) 以及 HeHebbian Principle 的启发，**作者通过增加网络的宽度，从而提高网络的表达能力，并尝试找到卷积神经网络中的最优局部稀疏结构，即 Inception Module（如上图所示）**。

作者所设计的 Inception Module 与常见的网络结构不同，打破了常规的卷积层串联的设计思路，选择将卷积核大小为 1 × 1，3 × 3，5 × 5 的卷积层和池化核大小为 3 × 3 的池化层进行并联，并将各自所得到的特征图进行 Concatenate 操作合并在一起，作为后续的输入。

之所以 Inception Module 由上图左侧发展被改进为上图右侧，是因为：作者希望希望模型中深层的 Inception Module 可以捕捉到 Higher Abstraction，所以作者认为深层的 Inception Module中的卷积层的空间集中度应该逐渐降低，以此捕捉更大面积的特征。故，作者令越深层的 Inception Module 中，卷积核大小为 3 × 3 和 5 × 5 这两个卷积层的输出通道数占比越多。但这又将导致计算量增加，所以为了解决这个问题，作者在原有 Inception Module 的基础上，利用卷积核大小为 1 × 1 的卷积层进行降维操作，从而减小计算量（这建立在一个假设之上：即使是低维的映射也可能包含关于相关图像区域的大量信息）。

![img](imgs\v2-668d760126735d2e61542e78864ea1b0_720w.jpg)

由于 Inception Module 保持了输入输出的尺寸一致，故 GoogLeNet 可以由 Inception Module 进行模块化搭建。仔细观察 GoogLeNet 的结构，你会发现作者在 Inception Module (4a) 和 (4d) 设置了额外的辅助 Loss，用以增加向后传导的梯度，缓解梯度消失问题，同时增加额外的正则化操作。在文章中，作者指出这样操作的目的主要是使得模型中低层的特征也具备很好的区分能力。（文章中，这两个额外的 Loss 会乘上衰减系数 0.3，与最后的 Loss 相加，作为整个模型的 Loss）

## **Inception Net V2**

> 论文链接：[Batch Normalization: Accelerating Deep Network Training by Reducing Internal Covariate Shift](https://link.zhihu.com/?target=https%3A//arxiv.org/pdf/1502.03167.pdf), 发表时间：2015.02

2015 年，谷歌提出了 Batch Normalization 操作，将其添加在之前的 GoogLeNet，并修改了一定的结构与实验设置，得到了 Inception Net V2，在 ImageNet 上达到分类任务超过 GoogLeNet。（关于 BN 的详细笔记，可以参考这篇博文：[[笔记\] 神经网络中 Normalization 的发展历程](https://link.zhihu.com/?target=https%3A//blog.csdn.net/Code_Mart/article/details/92715180)）

![img](imgs\v2-0d338ef9828cdb5f5663612579383873_720w.jpg)



![img](imgs\v2-88a558d30837860a5fb4210473533091_720w.jpg)

**网络结构：**

- 将 Inception Module 中卷积核大小为 5 × 5 的卷积层用两个相连的卷积核大小为 3 × 3 的卷积层进行替换。作者指出，这一操作是的模型参数增加了 25%，计算成本提高了 30%。
- 将输出大小为 28 × 28 的 Inception Module 的个数由两个提升到三个，即增加 Inception Module (3c)。
- 在 Inception Module 中进行池化操作（有时为平均池化（Average Pooling），有时为最大池化（Max Pooling））
- 两个 Inception Module 之间不再进行池化操作，仅在 Inception Module (3c) 和 (4e) 前添加 stride-2 conv/pooling layer。
- 将网络第一层的卷积层替换为深度乘子为 8 的可分离卷积（Separable Convolution，关于这个概念，可以参考：[卷积神经网络中的Separable Convolution](https://link.zhihu.com/?target=https%3A//yinguobing.com/separable-convolution/) 和 [CNN中千奇百怪的卷积方式大汇总](https://zhuanlan.zhihu.com/p/29367273)）。

**其他细节：**

- 作者在文中指出，他们并不是直接简单的将 BN 添加到网络中的，还做了如下的改动：增大学习率，移除 Dropout，减小 L2 正则化项，加速学习率衰减，移除 LRN，更彻底的打乱训练数据，减少光学畸变（ Photometric Distortion，关于这个概念，可以参考这篇文章：[SSD中的数据增强细节](https://link.zhihu.com/?target=https%3A//nicehuster.github.io/2019/05/11/ssd-dataaug/)）。下图为作者关于学习率的对比实验：

![img](imgs\v2-218e2b57587b0988fea27eed4100eaa9_720w.jpg)

![img](F:/GitHub/README-1/notes/models/imgs/v2-016ecefaf217771b75b2f74eb959b518_720w.jpg)

## **Inception Net V3**

> 论文链接：[Rethinking the Inception Architecture for Computer Vision](https://link.zhihu.com/?target=https%3A//arxiv.org/pdf/1512.00567.pdf), 发表时间：2015.12

时隔将近一年，谷歌又发了篇论文对之前提出的 Inception Module 进行了思考。在这篇论文中，作者首先四条设计神经网络的原则，接着提出如何分解大卷积核的卷积层，接着反思辅助分类器（Auxiliary Classifier）的作用，接着按照自己所提的第一条原则对常见的 Size Reduction 做了改进，最后将以上改进添加进之前的网络结构中。

![img](imgs\v2-7694e6d9a0d20d6c0da53bc81d6a2e34_as720w.jpg)

**关于四条设计神经网络的原则：**（没能完全理解，直接放原文吧）

- Avoid representational bottlenecks, especially early in the network.
- Higher dimensional representations are easier to process locally within a network.
- Spatial aggregation can be done over lower dimensional embeddings without much or any loss in representational power.
- Balance the width and depth of the network.

**关于如何分解大卷积核的卷积层：**

作者提出两种解决办法：利用连续的两层小卷积核的卷积层代替大卷积核的卷积层（下图左侧所示）；利用连续的两层非对称的卷积层（卷积核大小为 n × 1 和 1 × n）代替原有卷积层（卷积核大小为 n × n）（下图右侧所示）。

这样做的好处自然是减少参数量以及计算量。此外，作者对于这两种操作都做了相应的实验并发现：使用第一种操作时，添加在卷积层后的激活函数都为 ReLU 比 Linear+ReLU 好；使用第二种操作，最好在模型的中间层使用（适用的FeatureMap大小范围为 12~20）。



![img](imgs\v2-3109834abbe28b9978c887950d096e7f_720w.jpg)

![img](imgs\v2-efa22aa4fbe717387cf9f32395228d3c_720w.jpg)

**关于辅助分类器的作用：**

GoogLeNet 曾在 Inception Module (4a) 和 (4d) 设置了额外的辅助 Loss，即设置了辅助分类器，当时作者对其的理解是：使梯度更好的回传到低层，避免梯度消失问题，提高模型的收敛速度与最终表现。但是作者通过实验发现：在训练初期，有无辅助分类器并无区别；在训练后期，有辅助分类器将提高模型的最终表现；此外，作者去掉 GoogLeNet 中较低的辅助分类器的分支，发现此举并不会导致模型性能有明显的降低。最后，作者认为：辅助分类器起到的作用更像是正则化。

**关于如何有效减少特征图尺寸：**

在分类任务中，许多模型都会随着深度的整长不断通过池化操作缩小特征图尺寸，以此减小模型的“体积”。由于池化操作会导致特征图中的许多信息丢失，许多模型都习惯在特征图的宽与高缩小一半的同时，利用卷积核为 1 × 1 的卷积层使得特征图的通道数量翻倍（即 C × W × H -> 2C × W/2 × H/2），以此减少池化操作所带来的信息丢失。

这样操作有两种选择：先进行升维操作，再进行池化操作；先进行池化操作，再进行升维操作。作者指出，根据原则一，我们应先进行升维操作，再进行池化操作。（我觉得挺好理解的，本来升维就是为了避免池化操作带来的信息丢失，但是在已经池化后的特征图上做升维的效果肯定不如在未池化的特征图上做升维的效果好）

当然，这样做会导致计算量增加，于是作者提出了另一种做法，如下图所示：



![img](imgs\v2-0dbde0fed06f948df5ec85c74917b336_720w.jpg)

## **Inception Net V4**

> 论文链接：[Inception-v4, Inception-ResNet and the Impact of Residual Connections on Learning](https://link.zhihu.com/?target=https%3A//arxiv.org/pdf/1602.07261.pdf), 发表时间：2016.02

![img](imgs\v2-6d8ec104636817b5ea155714d92ea3f6_720w.jpg)

在 Inception-v4 中，作者将 Inception 和 ResNet 结合在一起，推出了 Inception-ResNet-v1，Inception-ResNet-v2，Inception-v4。其中，Inception-v4 的总体结构如上图所示，各个模块细节如下图所示。

![img](imgs\v2-b9ad008a91ecfebf2e1c7b6296f74af7_720w.jpg)

可以看得出来，Inception-v4 的结构设计非常复杂，需要大量的实验验证以及工程经验，一般只有大厂才有能力做这样的工作，这也是为什么最近 NAS 这么火的原因吧。

## **Xception**

> 论文链接：[Xception: Deep Learning with Depthwise Separable Convolutions ](https://link.zhihu.com/?target=https%3A//arxiv.org/pdf/1610.02357.pdf), 发表时间：2016.10
>

在这篇论文中，Google 利用 Depthwise Separable Convolution 对 Inception V3 进行了改进，并结合 Residual Connection 设计了新的网络：Xception（含有 Extreme Inception 的意味）。

![image-20210331163506463](imgs\image-20210331163506463.png)

## 总结

- **Inception-v1**

  从VGG中我们了解到，网络层数越深效果越好。但是随着模型**越深参数越来越多，这就导致网络比较容易过拟合**，需要提供更多的训练数据；另外，复杂的网络意味更多的计算量，更大的模型存储，需要更多的资源，且速度不够快。GoogLeNet就是从减少参数的角度来设计网络结构的。

  GoogLeNet通过**增加网络宽度的方式来增加网络复杂度，让网络可以自己去应该如何选择卷积核**。这种设计减少了参数 ，同时提高了网络对多种尺度的适应性。使用了1×1卷积可以使网络在不增加参数的情况下增加网络复杂度。

- **Inception-v2**

  在v1的基础上加入batch normalization技术，在tensorflow中，使用BN在激活函数之前效果更好；

  将5×5卷积替换成两个连续的3×3卷积，使网络更深，参数更少

- **Inception-v3**

  核心思想是将卷积核分解成更小的卷积，如将7×7分解成1×7和7×1两个卷积核，使网络参数减少，深度加深

- **Inception-v4** 

  引入了ResNet，使训练加速，性能提升。但是当滤波器的数目过大（>1000）时，训练很不稳定，可以加入activate scaling因子来缓解

- **Xception**

  在Inception-v3的基础上提出，基本思想是通道分离式卷积，但是又有区别。模型参数稍微减少，但是精度更高。Xception先做1×1卷积再做3×3卷积，即先将通道合并，再进行空间卷积。depthwise正好相反，先进行空间3×3卷积，再进行通道1×1卷积。核心思想是遵循一个假设：卷积的时候要将通道的卷积与空间的卷积进行分离。而MobileNet-v1用的就是depthwise的顺序，并且加了BN和ReLU。Xception的参数量与Inception-v3相差不大，其增加了网络宽度，旨在提升网络准确率，而MobileNet-v1旨在减少网络参数，提高效率。



Inception 是神经网络结构的一大神作，其提出的**「多尺寸卷积」**和**「多个小卷积核替代大卷积核」**等概念是现如今许多优秀网络架构的基石。也正是如此，基于此的 Xception 横空出世，作者称其为 Extreme Inception，提出的 Depthwise Separable Conv 也是让人眼前一亮。

本文不详细讲解论文内容，只探讨提出的这几个基础概念和结构，并按照时间顺序来探讨。首先探讨的是 Inception 的 多尺寸卷积核 和 卷积核替换，然后到 Bottleneck，最后到 Xception 的 Depthwise Separable Conv 。

### 01 多尺寸卷积核(V1)

Inception 最初提出的版本，其核心思想就是**使用多尺寸卷积核去观察输入数据**。

举个例子，我们看某个景象由于远近不同，同一个物体的大小也会有所不同，那么不同尺度的卷积核观察的特征就会有这样的效果。于是就有了如下的网络结构图：

![640?wx_fmt=png](imgs\12s.png)

于是我们的网络就变胖了，增加了网络的宽度，同时也提高了对于不同尺度的适应程度。

### 02 Pointwise Conv(V1)

但是我们的网络变胖了的同时，计算量也变大了，所以我们就要想办法减少参数量来减少计算量，于是在 Inception v1 中的最终版本加上了 1x1 卷积核。

![640?wx_fmt=png](imgs\11a.png)

**使用 1x1 卷积核对输入的特征图进行降维处理，这样就会极大地减少参数量，从而减少计算。**

举个例子，输入数据的维度是 256 维，经过 1x1 卷积之后，我们输出的维度是 64 维，参数量是原来的 1414 。

这就是 Pointwise Convolution，俗称叫做 1x1 卷积，简写为 PW，主要用于数据降维，减少参数量。

也有使用 PW 做升维的，在 MobileNet v2 中就使用 PW 将 3 个特征图变成 6 个特征图，丰富输入数据的特征。

想深入了解 MobileNet v2 的可以看看原文 MobileNet V2 - arxiv.org ，再对照地读这篇MobileNet V2 论文初读 - Michael Yuan。

### 03 卷积核替换(V3)


就算有了 PW ，由于 5x5 和 7x7 卷积核直接计算参数量还是非常大，训练时间还是比较长，我们还要再优化。

人类的智慧是无穷的，于是就想出了 使用多个小卷积核替代大卷积核 的方法，这就是 Inception v3，如图所示：

![640?wx_fmt=png](imgs\12a.png)

使用两个 3x3 卷积核来代替 5x5 卷积，效果上差不多，但参数量减少很多，达到了优化的目的。不仅参数量少，层数也多了，深度也变深了。

除了规整的的正方形，我们还有分解版本的 3x3 = 3x1 + 1x3，这个效果在深度较深的情况下比规整的卷积核更好。

![640?wx_fmt=png](imgs\13a.png)

我们假设输入 256 维，输出 512 维，计算一下参数量：

5x5 卷积核

256∗5∗5∗512=3276800

两个 3x3 卷积核

256∗3∗3∗256+256∗3∗3∗512=589824+1179648=1769472

结果对比

`17694723276800=0.54`

我们可以看到参数量对比，两个 3x3 的卷积核的参数量是 5x5 一半，可以大大加快训练速度。

### 04 Bottleneck(v4)


我们发现就算用了上面的结构和方法，我们的参数量还是很大，于是乎我们结合上面的方法创造出了 Bottleneck 的结构降低参数量。

Bottleneck 三步走是先 PW 对数据进行降维，再进行常规卷积核的卷积，最后 PW 对数据进行升维。我们举个例子，方便我们了解：

![640?wx_fmt=jpeg](imgs\14a.png)

根据上图，我们来做个对比计算，假设输入 feature map 的维度为 256 维，要求输出维度也是 256 维。有以下两种操作：

直接使用 3x3 的卷积核。256 维的输入直接经过一个 3×3×256 的卷积层，输出一个 256 维的 feature map ，那么参数量为：256×3×3×256 = 589,824 。

先经过 1x1 的卷积核，再经过 3x3 卷积核，最后经过一个 1x1 卷积核。 256 维的输入先经过一个 1×1×64 的卷积层，再经过一个 3x3x64 的卷积层，最后经过 1x1x256 的卷积层，则总参数量为：256×1×1×64 + 64×3×3×64 + 64×1×1×256 = 69,632 。

经过两种方式的对比，我们可以很明显的看到后者的参数量远小于前者的。Bottleneck 的核心思想还是利用多个小卷积核替代一个大卷积核，利用 1x1 卷积核替代大的卷积核的一部分工作。

### 05 Depthwise Separable Conv


我们发现参数量还是很多，于是人们又想啊想，得出了 Depthwise Separable Conv 。这个注意最早是来自这篇论文 Design of Efficient Convolutional Layers using Single Intra-channel Convolution, Topological Subdivisioning and Spatial “Bottleneck” Structure ，后面被 Google 用在 MobileNet 和 Xception 中发扬光大。

这个卷积的的大致意思是对每一个深度图分别进行卷积再融合，步骤是先 Depthwise Conv 再 Pointwise Conv，大大减少了参数量。下图是 Xception 模块的结构：

![640?wx_fmt=png](imgs\15a.png)

大致的步骤是这样的：

分别按不同通道进行一次卷积（生成 输入通道数 张 Feature Maps）- DW

再将这些 Feature Maps 一起进行第二次卷积 - PW

文字看起来有点抽象，我们用栗子来理解一下。

输入的是 2 维的数据，我们要进行 3x3 卷积并输出 3 维的数据，与正常卷积对比：

### 06 Summary


从 Inception 到 Xception 的发展一路看来，每一次创新都让人啧啧称赞，精巧的结构设计和理念思想，让人佩服。

- 多个不同尺寸的卷积核，提高对不同尺度特征的适应能力。

- PW 卷积，降维或升维的同时，提高网络的表达能力。

- 多个小尺寸卷积核替代大卷积核，加深网络的同时减少参数量。

- 精巧的 Bottleneck 结构，大大减少网络参数量。

- 精巧的 Depthwise Separable Conv 设计，再度减少参数量。


了解了这些基础结构的思想，我们就可以站在巨人的肩膀上更好地向前看，走向更优秀的方向。