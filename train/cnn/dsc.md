# 深度可分离卷积（Depthwise Separable Convolution）

⌚️: 2021-07-21

📚参考

- [卷积神经网络（CNN）之ResBlock与Inception](https://zhuanlan.zhihu.com/p/161639679)
- [卷积神经网络（CNN）之深度可分离卷积（Depthwise Separable Convolution）](https://zhuanlan.zhihu.com/p/166736637/)

---

本文分成三个部分：

**PART I：深度可分离卷积**

- **1.1 深度可分离卷积的详细结构**
- **1.2 深度可分离卷积与Inception的关系**

**PART II：以深度可分离卷积作为building block的著名网络**

- **2.1 Xception**
- **2.2 MobileNet**
- **2.3 ResNet with Depthwise Separable Convolution**

**PART III：介绍与深度可分离卷积关系密切的其它改进工作**

- **3.1****PydMobileBlock**
- **3.2 Efficient Spatial Pyramid**
- **3.3 Blueprint Separable Convolution**

**注意：后文中将只使用深度可分离卷积的缩写DSC**

------------------------------------------分割线-------------------------------------------

## PART I

### 1.1DSC的详细结构

![img](imgs\v2-c8e2ab6758468adc146bbd9bd1a620af_720w.jpg)

图1.1 DSC详细结构示意图



深度可分离卷积（Depthwise Separable Convolution，DSC）最早出现在一篇名为“Rigid-motion scattering for image classification”的博士学位论文中。但让大家对DSC熟知的则是两个著名的模型，Xception[1]和MobileNet[2]。Xception和MobileNet是同一时期出自Google团队的两个重要成果。DSC的详细结构如图1.1所示。DSC由Depthwise Convolution和Pointwise Convolution两部分构成。Depthwise Convolution的计算非常简单，它对输入feature map的每个通道分别使用一个卷积核，然后将所有卷积核的输出再进行拼接得到它的最终输出，如图1.1中的Depthwise Convolution部分所示。

因为卷积操作的输出通道数等于卷积核的数量，而Depthwise Convolution中对每个通道只使用一个卷积核，所以单个通道在卷积操作之后的输出通道数也为1。那么如果输入feature map的通道数为N（如图1.1所示），对N个通道分别单独使用一个卷积核之后便得到N个通道为1的feature map。再将这N个feature map按顺序拼接便得到一个通道为N的输出feature map。可以将Depthwise Convolution与普通卷积做一下对比，如图1.2所示。

![img](imgs\v2-0d8c4b890b6b4fe92700979979a9b0ab_720w.jpg)

图1.2 普通卷积与Depthwise Convolution对比示意图



Pointwise Convolution实际为1×1卷积，在DSC中它起两方面的作用。第一个作用是让DSC能够自由改变输出通道的数量；第二个作用是对Depthwise Convolution输出的feature map进行通道融合。第一个作用比较容易理解，这因为单独的Depthwise Convolution无法改变输出通道数量，因而采用1×1卷积来改变输出通道数量是比较直观和简单的做法。为理解Pointwise Convolution的第二点作用，可以考虑在只使用Depthwise Convolution来堆叠网络时会发生什么情况。假设输入为IN，它的第i个通道记为IN_i；第一层Depthwise Convolution的输出记为DC1，它的第i个通道记为DC1_i；第二层Depthwise Convolution的输出记为DC2，它的第i个通道记为DC2_i。

由Depthwise Convolution的工作机理可知，DC1_i只与IN_i有关，DC2_i只与DC1_i有关，进而DC2_i也只与IN_i有关。简单来说，输入、输出各不同通道间没有任何计算将它们联系起来。而1×1卷积本身就具有通道融合的能力，因此在Depthwise Convolution之后接Pointwise Convolution能够有效解决上述问题。

接下来分析一下普通卷积和DSC的计算性能。假设输入特征图的尺寸为 ![[公式]](https://www.zhihu.com/equation?tex=D_k+%5Ctimes+D_k+%5Ctimes+M) ，卷积核的尺寸为 ![[公式]](https://www.zhihu.com/equation?tex=D_F+%5Ctimes+D_F+%5Ctimes+M) ，其数量为 ![[公式]](https://www.zhihu.com/equation?tex=N) 。假设对应特征图空间位置中的每一个点都会进行一次卷积操作，那么可知单个卷积共需要进行 ![[公式]](https://www.zhihu.com/equation?tex=D_k+%5Ctimes+D_k+%5Ctimes+D_F+%5Ctimes+D_F+%5Ctimes+M) 次计算。这是因为特征图空间维度共包含 ![[公式]](https://www.zhihu.com/equation?tex=D_k+%5Ctimes+D_k) 个点，而对每个点进行卷积操作的计算量与卷积核的尺寸一致，即 ![[公式]](https://www.zhihu.com/equation?tex=D_F+%5Ctimes+D_F+%5Ctimes+M) ，所以对单个卷积而言，其总计算量为：

（1） ![[公式]](https://www.zhihu.com/equation?tex=D_k+%5Ctimes+D_k+%5Ctimes+D_F+%5Ctimes+D_F+%5Ctimes+M)

那么对 ![[公式]](https://www.zhihu.com/equation?tex=N) 个卷积，其总计算量就为：

（2）![[公式]](https://www.zhihu.com/equation?tex=D_k+%5Ctimes+D_k+%5Ctimes+D_F+%5Ctimes+D_F+%5Ctimes+M+%5Ctimes+N)

对DSC采用类似分析可知，Depthwise Convolution计算总量为 ：

（3）![[公式]](https://www.zhihu.com/equation?tex=D_k+%5Ctimes+D_k+%5Ctimes+D_F+%5Ctimes+D_F+%5Ctimes+M)

Pointwise Convolution的计算总量为：

（4）![[公式]](https://www.zhihu.com/equation?tex=M+%5Ctimes+N+%5Ctimes+D_K+%5Ctimes+D_K)

所以DSC的计算总量为：

（5）![[公式]](https://www.zhihu.com/equation?tex=D_k+%5Ctimes+D_k+%5Ctimes+D_F+%5Ctimes+D_F+%5Ctimes+M+%2B+M++%5Ctimes+N+%5Ctimes+D_K+%5Ctimes+D_K)

那么相对于普通卷积，DSC的计算量与普通卷积的比值为：

（6） ![[公式]](https://www.zhihu.com/equation?tex=%5Cfrac%7B1%7D%7BN%7D+%2B+%5Cfrac%7B1%7D%7BD_F%5E%7B2%7D%7D)

由上可知，DSC的计算效率远远优于普通卷积。

关于DSC的一个小细节是在Depthwise Convolution之后是否有必要加入激活函数和BatchNorm。一些研究从增加网络整体非线性表达能力的角度出发，认为在Depthwise Convolution之后加入激活函数和BatchNorm有助于提高网络的非线性表达能力，进而使网络有更强大的能力去拟合更加复杂的函数。但从近期的一些研究结果来看，在Depthwise Convolution之后不加入激活函数和BatchNorm是更优的选择，因此这也逐步成为了使用DSC的一种最佳实践。

简单总结一下，DSC作为普通卷积的一种替代品，它的最大优点是**计算效率非常高**。因此使用DSC构建轻量级模型是当下非常常见的做法。不过DSC的这种**高效性是以低精度作为代价的**。目前看来，设计高效率、高精度的DSC变体模块仍然是非常热点的研究方向之一。

### 1.2 DSC与Inception的关系

> 不感兴趣的同学可以跳过这一部分

![img](imgs\v2-8709a97054c74e808e57c877c3174780_720w.jpg)

图1.3 Inception的典型结构示意图



![img](imgs\v2-b0804630feb66715d4707edf31538bcf_720w.jpg)图1.4 简化版Inception结构示意图



Inception是Google早期用于图像分类的网络结构，但它同时也指在该网络中使用的building block。Inception在之前的文章中有详细介绍（[卷积神经网络（CNN）之ResBlock与Inception](https://zhuanlan.zhihu.com/p/161639679)），此处不再复述。为了方便表述，后续用“Inception网络”和“Inception”分别指代网络名称和building block的名称。

Inception的典型结构如图1.3所示。直观理解Inception的方式是将它看作是普通卷积的替代品，它的主要目的是希望能够提取比普通卷积更加复杂、有效的特征。为了达到这样的目的，Inception采取的是使用多条分支提取不同的特征，然后再融合的策略。如果我们假设Inception各条分支采用的卷积相同（例如都只包含一个1×1卷积和一个3×3卷积），那么可以得到图1.4的结构，我们将其称为简化版的Inception。简化版的Inception提供了一种有趣的视角，如图1.5所示。

![img](imgs\v2-3dce3d39d7c0cb15c45cfa178b121b5a_720w.jpg)

图1.5 对简化版的Inception的另一种视角



在图1.5的新视角下，我们人为地将这三个1×1卷积的输入映射为一个输出，且该输出的通道被分为三组，每一组对应于一个1×1卷积的输出。更进一步，我们可以将三个1×1卷积合并为一个1×1卷积，然后把1×1卷积后的输出通道进行分组，再分别送进三条分支，如图1.6所示。

![img](imgs\v2-63a38b07b8c247dccd69fc08e9f6309c_720w.jpg)图1.6 将图1.5中三个1×1卷积合并为一个1×1卷积示意图



举个简单例子，假设图1.5中的三个1×1卷积输出通道数分别为（从左到右）10，20，30。那么我们可以将这三个1×1卷积替换为一个输出通道数为60的1×1卷积。然后将该卷积输出的前10个通道数据送给分支一，中间的20个通道数据送给分支二，最后的30个通道数据送给分支三。

虽然在得到图1.6的结构过程中我们对Inception进行了种种修改，但它们大体思路和整体结构仍然具有极高的相似性。结合图1.6，我们可以猜测：Inception实际上是一种对通道“先分段，后融合”的处理方法。这可以从图1.4清晰地看出，我们将1×1卷积的输出人为分为3段，然后分别送入3个分支处理，最后再通过通道拼接融合在一起。当然，通过通道拼接并无法实现通常意义上的“融合”效果，因为通道拼接仅仅是物理上将几个特征图在通道维度上堆叠，没有任何逻辑上的计算。但如果以图1.4中的模块去堆叠网络，真正实现融合效果的是1×1卷积，因为这样一个模块的输出在送入下一个同样的模块时，会首先经过一次1×1卷积操作，从而实现对不同通道的融合。

如果记图1.6中1×1卷积输出特征图的通道数为N，在该特征图上的分组数为K，K的取值区间为[1, N]，那么图1.6示例中K的取值为3。像图1.6中这种基于分组的卷积（不含图中1×1卷积部分）称为“Group convolution”，即分组卷积。分组卷积中的K有两个极端值，一个是1，一个是N。当K取1时，分组卷积退化为普通卷积；当K取N时，分组卷积等价于前文介绍的Depthwise Convolution。同时我们也可以看到图1.6的结构和DSC其实非常相似（当k取N时）。

上面的整个分析主要从结构的角度来分析Inception和DSC的关系，但整个分析过程其实并不太自然，因为强加了很多“假设”。多次阅读应该能够帮助我们更好的理解这种关系。

Inception和DSC在研究动机上的关系是：

- Inception的假设是：图像的空间特征关系和通道间特征关系可以**在一定程度上**独立地计算；


- DSC的假设是：图像的空间特征关系和通道间特征关系可以**完全独立**地计算。


> Inception、DSC以及基于DSC的最著名的两个网络Xception和MobileNet均来自Google团队，所以它们之间存在非常密切的关系。关于Inception和DSC的动机，Xception这篇文章中有过介绍。不过考虑到Xception时间比较晚，所以不排除马后炮解释。

## PART II

这部分主要介绍以DSC作为building block的著名网络。

### 2.1 Xception[1]

论文传送门：

[Chollet F. Xception: Deep learning with depthwise separable convolutions. Proceedings of the IEEE conference on computer vision and pattern recognition. 2017: 1251-1258.openaccess.thecvf.com](https://link.zhihu.com/?target=https%3A//openaccess.thecvf.com/content_cvpr_2017/papers/Chollet_Xception_Deep_Learning_CVPR_2017_paper.pdf)

![img](imgs\v2-2013e2c157b98f79949fc9517d17fe5d_720w.jpg)

图2.1 Xception网络结构示意图



完整的Xception网络结构如图2.1所示。图2.1中的SeparableConv即本文介绍的DSC。Xception包含三个部分：Entry flow，Middle flow和Exit flow，网络总共有36个卷积层。Xception中大量使用了跳跃连接。跳跃连接一侧没有使用激活函数和BatchNorm，并且它通过1×1卷积来对齐通道数量。除此之外，整个Xception的网络结构没有其它值得特别关注的地方。

Xception的实验主要验证了以下三点：

1）Xception在参数量与InceptionV3大致相同的情况下，在ImageNet验证集上的结果优于InceptionV3。该结果可见于表2.1。但需要注意的是，作者在实现InceptionV3时删除了原本存在的辅助分类分支。所以和Xception对比的实际是有一点点“残疾”的InceptionV3；

2）Xception中采用的跳跃连接对模型效果具有至关重要的作用，如图2.2所示。这个结果与现在普遍认为“跳跃连接的主要作用是加快模型收敛速度”的观点有一些差异。所以在实践中，仍应考虑引入ResNet的跳跃连接结构。**在我们团队的实践中，普遍存在的情况是：相比于plain convolution结构，带ResNet形式的跳跃连接的网络一般表现的会略好；但当网络中引入的构建方式和策略变得复杂时，跳跃连接在多数情况下没有作用；**

3）在Depthwise Convolution和Pointwise Convolution之间引入激活函数对网络没有任何帮助，如图2.3的结果所示。

![img](imgs\v2-200720e90b9c3af287d16b39211d2661_720w.jpg)表2.1 Xception在ImageNet验证集上的实验结果



![img](imgs\v2-03c694d7ea557454dae87603f23df140_720w.jpg)

图2.2 跳跃连接对Xception精度影响



![img](imgs\v2-db3905ad06ee1b828f42f3d969b18962_720w.jpg)

图2.3 Depthwise Convolution和Pointwise Convolution之间增加（改变）激活函数对模型精度的影响

### 2.2 MobileNet[2]

论文传送门：

[Howard A G, Zhu M, Chen B, et al. Mobilenets: Efficient convolutional neural networks for mobile vision applications. arXiv preprint arXiv:1704.04861, 2017.arxiv.org](https://link.zhihu.com/?target=https%3A//arxiv.org/pdf/1704.04861.pdf)

![img](imgs\v2-c829695797146ee0030c0ce03f70320d_720w.jpg)

表2.2 MobileNet网络结构示意图

MobileNet的详细结构如表2.2所示，它将Depthwise Convolution与Pointwise Convolution分开表示，其中dw表示Depthwise Convolution，1×1即为Pointwise Convolution。相比于Xception，MobileNet更是纯靠DSC堆叠而成，并且MobileNet使用的DSC中在Depthwise Convolution与Pointwise Convolution之间加入了BatchNorm和Relu。

MobileNet的实验结果实际上非常中规中矩。在几乎所有的MobileNet实验中，它都刻意避开了那些性能明显优于MobileNet的网络，例如ResNet和Xception。所以本文不再介绍它的实验。简而言之，MobileNet给出了一种轻量级的深度神经网络解决方案，虽然在精度上差强人意，但至少提出了构建小网络的一种方法。

### 2.3 ResNet with Depthwise Separable Convolution [3]

论文传送门：

[Guo Y, Li Y, Wang L, et al. Depthwise convolution is all you need for learning multiple visual domains. Proceedings of the AAAI Conference on Artificial Intelligence. 2019, 33: 8368-8375.www.aaai.org](https://link.zhihu.com/?target=https%3A//www.aaai.org/ojs/index.php/AAAI/article/download/4851/4724)

![img](imgs\v2-b4a807be7a00ef38bac84860d710b33f_720w.jpg)

图2.4 ResNet with DSC

AAAI2019的文章，它的网络结构如图2.4所示。因为图太长，所以手动拆成了三块，其中middle的首尾是重复的。图中SeparableConv即本文介绍的DSC。从结构上看，这个网络显得更加没有新意，它仅仅是一个将普通卷积替换为DSC的ResNet。但它的假设比较有趣。为方便表述，我们将该网络命名为ResDSC。

ResDSC被设计用来解决multi-domain learning的图像分类问题。简单来讲，就是用一个统一的网络结构来解决不同domain的图像分类。此外，仅仅是统一的网络结构还不够，它还要求网络中的参数要尽可能共享。举个简单例子，假设我们有一个可用的网络A（例如ResNet101）和N个Domain的图像数据集D1，D2，...。我们可以用A在这N个数据集上分别训练得到相应模型来解决每个Domain的图像分类问题，但此时这N个模型的参数并没有共享。如果我们用A在D1上训练出一个模型，然后固定住该模型的大部分参数，再让A在剩余数据集上去训练余下模型参数，那么此时这N个模型的大部分参数都是一样的。我们将模型这些相同的参数称为“共享参数”，而将模型不同的参数称为“私有参数”。multi-domain learning的目的就是希望不同Domain上的模型具有更多的共享参数和各自更好的模型效果。multi-domain learning是面向实际问题的重要研究方向，所以它不会将这N个数据集扔到一起去训练。因为在实际中，我们希望的是针对未来的某些domain（当前不可见），模型仍然可用。

作者的假设是：不同Domain的特有特征体现在空间特征上，而所有Domain在通道间的相关性则是相似的。将这个假设与DSC联系起来，我们可以得到如下结论：DSC中的Depthwise Convolution可以负责对不同Domain特有特征的提取，因此不同Domain的网络的Depthwise Convolution的参数是不可以共享的；而因为不同通道间的相关性在所有Domain是相似的，所以Pointwise Convolution的参数是可以共享的。

这个假设与前文介绍的DSC的假设（图像的空间特征关系和通道间特征关系可以完全独立地计算）具有一定的相似性。可以这样理解：正是因为DSC的Depthwise Convolution和Pointwise Convolution负责不同方面的特征提取，所以它们才能独立地计算。

遵循这个假设，作者们首先将ResDSC在ImageNet上训练，然后固定住网络中所有的Pointwise Convolution的参数，再在其它数据集上进行Finetuning。Finetuning的参数对象主要包括Depthwise Convolution、BatchNorm和全连层。

实验基于Visual Decathlon Challenge ，其中包括十个图像分类数据集，榜单和详细评分介绍可以看这里[https://www.robots.ox.ac.uk/~vgg/decathlon/](https://link.zhihu.com/?target=https%3A//www.robots.ox.ac.uk/~vgg/decathlon/)。截止到目前为止，ResDSC依然霸榜。

作者在原文中通过可视化的方法发现，Depthwise Convolution能够检测高层级特征（如轮子），而Pointwise Convolution只能检测低层级特征（如点、线）。作者进一步提到，不同Domain之间的高层级特征应该是无法共享的（例如高层级特征“车轮”对于一个猫狗数据集多半是无用的），而诸如点、线这种低层级特征则可以共享。从这个角度来看，ResDSC的设计就非常合理了。

但是，我们也不应该忽视Depthwise Convolution与Pointwise Convolution在空间尺寸上的差异，这种差异也有可能是导致它们学到不同“层级”特征的重要原因。不过作者没有就这个问题进行讨论。

除了标准的DSC，作者们还抛出了另外一个问题：有没有可能让Depthwise Convolution与Pointwise Convolution的参数在不同domain的模型上都共享，而不仅仅是共享Pointwise Convolution的参数。为此，他们设计了一种称为soft sharing的结构，如图2.5所示。

![img](imgs\v2-04e498df93d66917382a7e1b967669bc_720w.jpg)

图2.5 soft sharing结构示意图

soft sharing将DSC中的Depthwise Convolution部分作了修改，所以它本质上也是一种building block。它的具体工作方式首先用图2.4的结构在ImageNet上训练。然后将该模型中的所有DSC替换为soft sharing block。在替换过程中，所有Pointwise Convolution直接保留不变，而Depthwise Convolution部分则变化图2.5所示的结构。具体来讲，soft sharing block对每个输入通道（假设又C个通道）使用全局平均池化得到一个长度为C的向量。然后将该向量送入全连层后再经过softmax得到一个概率分布。全连层和概率分布的大小等于在ImageNet上训练得到的**模型中所有Depthwise Convolution的数量**。然后以该分布中的概率作为权重，对所有Depthwise Convolution的输出进行加权求和，得到输出。该输出作为下一个Pointwise Convolution的输入。

根据实验结果来看，soft sharing在少量的数据集上取得了细微的提升。但它能否作为一种更普适化的参数共享方法则还有待进一步研究。

## PART III

这部分主要介绍针对DSC的一些改进算法。

### 3.1 PydMobileBlock[4]

论文传送门：

[Hoang V T, Jo K H. PydMobileNet: Pyramid Depthwise Separable Convolution Networks for Image Classification. 2019 IEEE 28th International Symposium on Industrial Electronics (ISIE). IEEE, 2019: 1430-1434.arxiv.org](https://link.zhihu.com/?target=https%3A//arxiv.org/pdf/1811.07083.pdf)

![img](imgs\v2-c7aeb13987356deb75f9191fe8985704_720w.jpg)图3.1 左图：基于“特征相加”的PydMobileBlock示意图；右图：基于“特征拼接”的PydMobileBlock示意图



Inception的相关研究表明在网络的同一层中使用具有不同空间尺寸的卷积核仍是有价值的。而DSC中的Depthwise Convolution通常只使用具有相同空间尺寸的卷积核。因此一种改进方法是将Depthwise Convolution设计为具有不同空间尺寸的卷积核，如图3.1所示，这样的结构称为PydMobileBlock。

PydMobileBlock的结构非常直观。首先使用1×1卷积对通道降维，然后在新的特征图上分别使用三个不同尺寸的卷积核，然后再融合，并对融合后的特征图再使用1×1卷积对通道进行缩放。同时PydMobileBlock本身也是一个ResBlock结构。作者提出的基于PydMobileBlock的网络结构如表3.1所示，其中Residual Block替换为PydMobileBlock。

![img](data:image/svg+xml;utf8,<svg xmlns='http://www.w3.org/2000/svg' width='958' height='301'></svg>)表3.1 基于PydMobileBlock的网络结构

文章仅仅在CIFAR-10和CIFAR-100上进行充足实验，因此比较缺乏说服力。简单来说，在CIFAR-10数据集上，PydMobileNet的表现差强人意。而在在CIFAR-100数据集上，PydMobileNet在参数量远小于DenseNet、ResNext等网络的情况下，取得了最优结果，error rate为14.6%。

### 3.2 Efficient Spatial Pyramid[5]

论文传送门：

[Mehta S, Rastegari M, Caspi A, et al. Espnet: Efficient spatial pyramid of dilated convolutions for semantic segmentation. Proceedings of the european conference on computer vision (ECCV). 2018: 552-568.openaccess.thecvf.com](https://link.zhihu.com/?target=https%3A//openaccess.thecvf.com/content_ECCV_2018/papers/Sachin_Mehta_ESPNet_Efficient_Spatial_ECCV_2018_paper.pdf)

![img](imgs\v2-834c7be3d839e890da1d9ed4f6b5ce09_720w.jpg)

图3.2 ESP结构示意图



ESP是一种轻量级语义分割网络的building block，它的设计核心目的是为提高feature resampling的效率，以便网络中能够频繁使用这种策略。feature resampling简单来说，就是对同一特征图采用不同的卷积核或池化或其它手段来以更复杂的手段提取特征。例如Inception也可以看作是采用了feature resampling方法。ESP的结构如图3.2所示。

作者将ESP这种主体结构称为Reduce-Split-Transform-Merge范式。Reduce指对输入使用1×1卷积进行通道降维；Split指多条分支；Transform指卷积运算；Merge指最后的Concat拼接。ESP中的每条分支中的卷积核大小都是3×3，但他们的空洞率不一致，因此感受野也不一致。图中各条分支卷积核的大小指的它们的“Effective Size”。

在特征拼接之前，ESP对各条分支的输出使用了Hierarchical Feature Fusion（HFF）。ESP中各条分支的空洞率从左到右通常是递增的关系，例如最左侧分支的空洞率为1，第二条分支的空洞率2以此类推。因此HFF从最小空洞率分支开始，将其输出与下一条分支进行相加融合，最后再将各分支结果进行拼接。HFF能够有效解决空洞卷积导致的“gridding artifact”问题，如图3.3所示，其中中图和右图是不加HFF和加HFF时的特征图。

ESP的实验比较平淡，有点像yolo单纯地追求快，而放弃了精度。

![img](imgs\v2-017399a234f69bbae392fecd1dedf915_720w.jpg)

图3.3 gridding artifact（中图）示意图

### 3.3 Blueprint Separable Convolution [6]

论文传送门：

[Haase D, Amthor M. Rethinking Depthwise Separable Convolutions: How Intra-Kernel Correlations Lead to Improved MobileNets. Proceedings of the IEEE/CVF Conference on Computer Vision and Pattern Recognition. 2020: 14600-14609.openaccess.thecvf.com](https://link.zhihu.com/?target=https%3A//openaccess.thecvf.com/content_CVPR_2020/papers/Haase_Rethinking_Depthwise_Separable_Convolutions_How_Intra-Kernel_Correlations_Lead_to_Improved_CVPR_2020_paper.pdf)

![img](imgs\v2-4bf5b05baa154857ada1f5c7336bba04_720w.jpg)

图3.4卷积核可视化示意图

Blueprint Separable Convolution（BSC）的设计出发点是基于卷积核在通道间的相关性。这种相关性可以由图3.4体现。图3.4给出了三个主流网络中的一个128×3×3卷积的可视化效果，其中128是卷积核的通道数。这三个网络都由ImageNet训练得到。从图3.4可以清晰看到，同一卷积核不同通道间的“形态”非常相似，因此我们可以假设每个卷积核都存在一个Blueprint，而该卷积核的每个通道都由一个系数与Blueprint相乘得到。这就是BSC的研究出发点。

为了将尺寸为 ![[公式]](https://www.zhihu.com/equation?tex=%28M%2CY%2CX%29)的输入U变换至尺寸为![[公式]](https://www.zhihu.com/equation?tex=%28N%2CY%2CX%29)的输出V，需要N个尺寸为 ![[公式]](https://www.zhihu.com/equation?tex=%28M%2CK%2CK%29) 的普通卷积核![[公式]](https://www.zhihu.com/equation?tex=F%5E%7B%281%29%7D%2CF%5E%7B%282%29%7D%2C...%2CF%5E%7B%28N%29%7D) ,其计算可描述为：

(7) ![[公式]](https://www.zhihu.com/equation?tex=V_%7Bn.%3A.%3A%7D%3DU%2AF%5E%7B%28n%29%7D)

其中 ![[公式]](https://www.zhihu.com/equation?tex=%2A) 表示卷积运算。公式（7）表示“输出V的第n个通道由输入与第n个卷积核计算得到”。对于BSC，其计算过程也由公式（7）表述，但与普通卷积的区别在于每个BSC卷积核 ![[公式]](https://www.zhihu.com/equation?tex=F%5E%7B%28n%29%7D) 是由一个Blueprint和一组系数构成。将BSC卷积核 ![[公式]](https://www.zhihu.com/equation?tex=F%5E%7B%28n%29%7D)的Blueprint记为 ![[公式]](https://www.zhihu.com/equation?tex=B%5E%7B%28n%29%7D) ，其对应的系数为 ![[公式]](https://www.zhihu.com/equation?tex=w_%7Bn%2C1%7D%2Cw_%7Bn%2C2%7D%2C...%2Cw_%7Bn%2CM%7D) ，那么BSC卷积核 ![[公式]](https://www.zhihu.com/equation?tex=F%5E%7B%28n%29%7D)为：

(8) ![[公式]](https://www.zhihu.com/equation?tex=F_%7Bm%2C%3A%2C%3A%7D%5E%7B%28n%29%7D%3Dw_%7Bn%2Cm%7D%5Ccdot+B%5E%7B%28n%29%7D)

BSC与普通卷积的对比可以由图3.5更加直观地看出。

![img](imgs\v2-0049d8e646f36a81047a9c8bdeb392c8_720w.jpg)

图3.5 普通卷积与BSC对比示意图

结合图3.5，我们可以看到单个普通卷积核的参数量为 ![[公式]](https://www.zhihu.com/equation?tex=M+%5Ctimes+K+%5Ctimes+K+) ，而单个BSC的参数量则仅为 ![[公式]](https://www.zhihu.com/equation?tex=K+%5Ctimes+K+%2B+M) 。接下来我们推导一个有趣的结论。我们首先将公式（7）进一步展开如下：

![img](imgs\v2-025947bdab03c4fe1504e95987a3bf7b_720w.png)

公式（9）实际上是将卷积核的每个通道的计算进行了展开，可以这样理解：输出V的第n个通道由一个求和项计算得到，这个求和项中的每一项为输入的某个通道（m）与卷积核对应通道的计算结果。简而言之，就是在公式（7）的基础上把卷积计算进一步略微说详细了一点。在公式（9）的展开结果中，我们可以将公式（7）代入公式（9），得到：

![img](imgs\v2-cc3def89be391c202ccc5b6a6ab20e85_720w.png)

注意到 ![[公式]](https://www.zhihu.com/equation?tex=B%5E%7B%28n%29%7D) 与M无关，且 ![[公式]](https://www.zhihu.com/equation?tex=w_%7Bn%2Cm%7D) 是一个标量，因此公式（10）可进一步改写为：

![img](imgs\v2-4e82f1ef60a895988feb220a9319925e_720w.jpg)

抛开 ![[公式]](https://www.zhihu.com/equation?tex=B%5E%7B%28n%29%7D) 部分，仔细观察公式（11）中括号内的部分，我们可以将其描述为：输出 ![[公式]](https://www.zhihu.com/equation?tex=V_%7Bn%2C%3A%2C%3A%7D%27) 的第n个通道是由输入U的所有通道加权求和得到，这个权重由 ![[公式]](https://www.zhihu.com/equation?tex=w_%7Bn%2C1%7D%2Cw_%7Bn%2C2%7D%2C...%2Cw_%7Bn%2CM%7D) 构成。而这恰好等价于对输入U使用一个1×1卷积，该卷积的输入通道数是M，输出通道数是N。对于 ![[公式]](https://www.zhihu.com/equation?tex=B%5E%7B%28n%29%7D) ，它的尺寸实际是 ![[公式]](https://www.zhihu.com/equation?tex=%281%2C1%2CK%2CK%29) ，因此它等价于一个Depthwise卷积。由此，我们看到一个BSC实际上是由一个Pointwise卷积和一个Depthwise卷积构成，它的Pointwise卷积和Depthwise卷积的顺序正好与DSC相反，如图3.6所示。

![img](imgs\v2-d376d02abc30aa464a8279d68f9281d8_720w.jpg)

图3.6 DSC与BSC结构示意图

这个结果还是比较有趣的，从一个我们并不太熟悉的现象出发（卷积核通道间的相关性），提出了依靠BSC来进一步优化网络设计，这个看似思路新奇的BSC在最后实现上竟与DSC高度相似。

前文提到，BSC中的1×1卷积尺寸为 ![[公式]](https://www.zhihu.com/equation?tex=%28N%2CM%2C1%2C1%29) ，因此它的参数实际表示为一个大小为 ![[公式]](https://www.zhihu.com/equation?tex=N+%5Ctimes+M) 的矩阵 ![[公式]](https://www.zhihu.com/equation?tex=W) 。此外，矩阵 ![[公式]](https://www.zhihu.com/equation?tex=W) 的行之间相关性比较大，因此可以考虑对列进行压缩来进一步降低网络参数量。行相关，为什么压缩列？如果把行当做样本，列当做特征，这个就容易理解了，类似于特征的压缩降维。为此引入矩阵 ![[公式]](https://www.zhihu.com/equation?tex=W%5EA) 和 ![[公式]](https://www.zhihu.com/equation?tex=W%5EB) ，使得：

(12) ![[公式]](https://www.zhihu.com/equation?tex=W%3DW%5EA+W%5EB)

其中矩阵 ![[公式]](https://www.zhihu.com/equation?tex=W%5EA) 的大小为 ![[公式]](https://www.zhihu.com/equation?tex=N+%5Ctimes+M%27) ，矩阵 ![[公式]](https://www.zhihu.com/equation?tex=W%5EB) 的大小为 ![[公式]](https://www.zhihu.com/equation?tex=M%27+%5Ctimes+M) , ![[公式]](https://www.zhihu.com/equation?tex=M%27+%3C+M) 。如果以线性变换的角度来理解公式（12），那么 ![[公式]](https://www.zhihu.com/equation?tex=W) 定义了一个复合变换，由 ![[公式]](https://www.zhihu.com/equation?tex=W%5EA) 和 ![[公式]](https://www.zhihu.com/equation?tex=W%5EB) 构成，且 ![[公式]](https://www.zhihu.com/equation?tex=W%5EB) 可以看作为一个基。对于基而言，我们通常希望它的坐标轴是正交的，因此可以引入一个正则项：

![img](imgs\v2-3741535ce448236f2bec323182728ae5_720w.png)

最后采用类似于推导BSC实现方式的方法，可以得到改进后的BSC，为了区分，将原始的BSC称为BSC-U，改进后的称为BSC-S，U表示Unconstrained，S表示Subspace。Unconstrained可以理解为对BSC中的参数没有任何限制，而Subspace可以理解为将BSC中的 ![[公式]](https://www.zhihu.com/equation?tex=W) 映射至了一个新的空间，并对这个空间进行了一定的限制（坐标轴正交）。示意如图3.7所示。

![img](imgs\v2-027f5fe2b459f79bcaa671c13516f673_720w.jpg)

图3.7 BSC-U与BSC-S结构示意图

可以看到，BSC-S最终的实现可以由两个Pointwise卷积加一个Depthwise卷积构成。如果不去看整个推导过程，这两个结构都足以让人感到绝望。

在实验中，参与对比的算法主要是MobileNet系列，采取的对比方法是将MobileNet中的DSC直接替换为BSC。实验比较丰富，从结论来看BSC有非常明显的优势。