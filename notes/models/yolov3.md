## 一、Yolov3网络架构

- backbone：Darknet-53

![img](https://pic2.zhimg.com/80/v2-8385e8c24d95ababae443bd4db85a33f_720w.jpg)图一 Darknet-53

backbone部分由Yolov2时期的Darknet-19进化至Darknet-53，加深了网络层数，引入了Resnet中的跨层加和操作。原文列举了Darknet-53与其他网络的对比：

![img](https://pic4.zhimg.com/80/v2-5ca215d18725d4dce3dfd34fb3e8f4a6_720w.jpg)图二 Darknet精度性能对比

Darknet-53处理速度每秒78张图，比Darknet-19慢不少，但是比同精度的ResNet快很多。Yolov3依然保持了高性能。

（这里解释一下Top1和Top5：模型在ImageNet数据集上进行推理，按照置信度排序总共生成5个标签。按照第一个标签预测计算正确率，即为Top1正确率；前五个标签中只要有一个是正确的标签，则视为正确预测，称为Top5正确率）



- Yolov3网络结构全貌

Yolov3使用Darknet-53作为整个网络的分类骨干部分。在Yolov3论文中并未给出全部网络结构。根据代码，整理数据流图如下（参考多份Yolov3代码，正确性可以保证）：

![img](https://pic1.zhimg.com/80/v2-d2596ea39974bcde176d1cf4dc99705e_720w.jpg)图三 Yolov3数据流程图

网络结构解析：

1. Yolov3中，只有卷积层，通过**调节卷积步长控制输出特征图的尺寸**。所以对于输入图片尺寸没有特别限制。流程图中，输入图片以256*256作为样例。
2. Yolov3借鉴了**金字塔特征图**思想，**小尺寸特征图用于检测大尺寸物体**，而**大尺寸特征图检测小尺寸物体**。特征图的输出维度为 ![[公式]](https://www.zhihu.com/equation?tex=N%5Ctimes+N+%5Ctimes+%5B3+%5Ctimes+%284+%2B+1+%2B+80%29%5D) ， ![[公式]](https://www.zhihu.com/equation?tex=N%5Ctimes+N) 为输出特征图格点数，一共3个Anchor框，每个框有4维预测框数值 ![[公式]](https://www.zhihu.com/equation?tex=t_x+%2Ct_y+%2Ct_w%2C+t_h) ，1维预测框置信度，80维物体类别数。所以第一层特征图的输出维度为 ![[公式]](https://www.zhihu.com/equation?tex=8+%5Ctimes+8+%5Ctimes+255) 。
3. Yolov3总共输出3个特征图，第一个特征图下采样32倍，第二个特征图下采样16倍，第三个下采样8倍。输入图像经过Darknet-53（无全连接层），再经过Yoloblock生成的特征图被当作两用，第一用为经过3*3卷积层、1*1卷积之后生成特征图一，第二用为经过1*1卷积层加上采样层，与Darnet-53网络的中间层输出结果进行拼接，产生特征图二。同样的循环之后产生特征图三。
4. concat操作与加和操作的区别：加和操作来源于ResNet思想，将输入的特征图，与输出特征图对应维度进行相加，即 ![[公式]](https://www.zhihu.com/equation?tex=y+%3D+f%28x%29%2Bx) ；而concat操作源于DenseNet网络的设计思路，将特征图按照通道维度直接进行拼接，例如8*8*16的特征图与8*8*16的特征图拼接后生成8*8*32的特征图。
5. 上采样层(upsample)：作用是将小尺寸特征图通过插值等方法，生成大尺寸图像。例如使用最近邻插值算法，将8*8的图像变换为16*16。上采样层不改变特征图的通道数。

Yolo的整个网络，吸取了Resnet、Densenet、FPN的精髓，可以说是融合了目标检测当前业界最有效的全部技巧。



## 二、Yolo输出特征图解码（前向过程）

根据不同的输入尺寸，会得到不同大小的输出特征图，以图二中输入图片256 × 256 × 3为例，输出的特征图为8 × 8 × 255、16 × 16 × 255、32 × 32 × 255。在Yolov3的设计中，每个特征图的每个格子中，都配置3个不同的先验框，所以最后三个特征图，这里暂且reshape为8 × 8 × 3 × 85、16 × 16 × 3 × 85、32 × 32 × 3 × 85，这样更容易理解，在代码中也是reshape成这样之后更容易操作。

三张特征图就是整个Yolo输出的检测结果，检测框位置（4维）、检测置信度（1维）、类别（80维）都在其中，加起来正好是85维。特征图最后的维度85，代表的就是这些信息，而特征图其他维度N × N × 3，N × N代表了检测框的参考位置信息，3是3个不同尺度的先验框。下面详细描述怎么将检测信息解码出来：



- 先验框

在Yolov1中，网络直接回归检测框的宽、高，这样效果有限。所以在Yolov2中，改为了回归基于先验框的变化值，这样网络的学习难度降低，整体精度提升不小。Yolov3沿用了Yolov2中关于先验框的技巧，并且使用k-means对数据集中的标签框进行聚类，得到类别中心点的9个框，作为先验框。在COCO数据集中（原始图片全部resize为416 × 416），九个框分别是 (10×13)，(16×30)，(33×23)，(30×61)，(62×45)，(59× 119)， (116 × 90)， (156 × 198)，(373 × 326) ，顺序为w × h。

注：先验框只与检测框的w、h有关，与x、y无关。



- 检测框解码

有了先验框与输出特征图，就可以解码检测框 x，y，w，h。

![[公式]](https://www.zhihu.com/equation?tex=b_x%3D%5Csigma+%28t_x%29+%2B+c_x+%5C%5C+b_y%3D%5Csigma+%28t_y%29+%2B+c_y+%5C%5C+b_w%3Dp_we%5E%7Bt_w%7D++%5C%5C+b_h%3Dp_he%5E%7Bt_h%7D+%5C%5C)

如下图所示， ![[公式]](https://www.zhihu.com/equation?tex=%5Csigma%28t_x%29%2C+%5Csigma%28t_y%29) 是基于矩形框中心点左上角格点坐标的偏移量， ![[公式]](https://www.zhihu.com/equation?tex=%5Csigma) 是**激活函数**，论文中作者使用**sigmoid**。 ![[公式]](https://www.zhihu.com/equation?tex=p_w%2C+p_h) 是先验框的宽、高，通过上述公式，计算出实际预测框的宽高 ![[公式]](https://www.zhihu.com/equation?tex=%28b_w%2C+b_h%29) 。

![img](https://pic1.zhimg.com/80/v2-758b1df9132a9f4b4e0c7def735e9a11_720w.jpg)图三 检测框解码

举个具体的例子，假设对于第二个特征图16 × 16 × 3 × 85中的第[5，4，2]维，上图中的 ![[公式]](https://www.zhihu.com/equation?tex=c_y) 为5， ![[公式]](https://www.zhihu.com/equation?tex=+c_x) 为4，第二个特征图对应的先验框为(30×61)，(62×45)，(59× 119)，prior_box的index为2，那么取最后一个59，119作为先验w、先验h。这样计算之后的 ![[公式]](https://www.zhihu.com/equation?tex=b_x%2Cb_y) 还需要乘以特征图二的采样率16，得到真实的检测框x，y。



- 检测置信度解码

物体的检测置信度，在Yolo设计中非常重要，关系到算法的检测正确率与召回率。

置信度在输出85维中占固定一位，由sigmoid函数解码即可，解码之后数值区间在[0，1]中。



- 类别解码

COCO数据集有80个类别，所以类别数在85维输出中占了80维，每一维独立代表一个类别的置信度。使用sigmoid激活函数替代了Yolov2中的softmax，取消了类别之间的互斥，可以使网络更加灵活。



三个特征图一共可以解码出 8 × 8 × 3 + 16 × 16 × 3 + 32 × 32 × 3 = 4032 个box以及相应的类别、置信度。这4032个box，在训练和推理时，使用方法不一样：

1. 训练时4032个box全部送入打标签函数，进行后一步的标签以及损失函数的计算。
2. 推理时，选取一个置信度阈值，过滤掉低阈值box，再经过nms（非极大值抑制），就可以输出整个网络的预测结果了。



## 三、训练策略与损失函数（反向过程）

Yolov3的训练策略尤为重要，笔者也是在亲手复现代码之后，才算领悟了八九成。

- 训练策略

> YOLOv3 predicts an objectness score for each bounding box using logistic regression. This should be 1 if the bounding box prior overlaps a ground truth object by more than any other bounding box prior. If the bounding box prior is not the best but does overlap a ground truth object by more than some threshold we ignore the prediction, following [17]. We use the threshold of .5. Unlike [17] our system only assigns one bounding box prior for each ground truth object. If a bounding box prior is not assigned to a ground truth object it incurs no loss for coordinate or class predictions, only objectness. 

以上是Yolov3论文中的训练策略。说实话，最后一句“一个没有被分配ground truth的预测框，只产生置信度loss“，有一定的歧义。深刻理解Yolov3之后，训练策略总结如下：

1. 预测框一共分为三种情况：正例（positive）、负例（negative）、忽略样例（ignore）。
2. 正例：任取一个ground truth，与4032个框全部计算IOU，IOU最大的预测框，即为正例。并且一个预测框，只能分配给一个ground truth。例如第一个ground truth已经匹配了一个正例检测框，那么下一个ground truth，就在余下的4031个检测框中，寻找IOU最大的检测框作为正例。ground truth的先后顺序可忽略。正例产生置信度loss、检测框loss、类别loss。预测框为对应的ground truth box标签（需要反向编码，使用真实的x、y、w、h计算出 ![[公式]](https://www.zhihu.com/equation?tex=t_x+%2Ct_y+%2Ct_w%2C+t_h)）；类别标签对应类别为1，其余为0；置信度标签为1。
3. 忽略样例：正例除外，与任意一个ground truth的IOU大于阈值（论文中使用0.5），则为忽略样例。忽略样例不产生任何loss。
4. 负例：正例除外（与ground truth计算后IOU最大的检测框，但是IOU小于阈值，仍为正例），与全部ground truth的IOU都小于阈值（0.5），则为负例。负例只有置信度产生loss，置信度标签为0。



- Loss函数

特征图1的Yolov3的损失函数抽象表达式如下：

![[公式]](https://www.zhihu.com/equation?tex=loss_%7BN_1%7D+%3D+%5Clambda_%7Bbox%7D%5Csum_%7Bi%3D0%7D%5E%7BN_1%5Ctimes+N_1%7D%5Csum_%7Bj%3D0%7D%5E%7B3%7D%7B1_%7Bij%7D%5E%7Bobj%7D%5B%28t_x+-+t_x%27%29%5E2+%2B+%28t_y+-+t_y%27%29%5E2%5D%7D+%5C%5C+%2B%5Clambda_%7Bbox%7D%5Csum_%7Bi%3D0%7D%5E%7BN_1%5Ctimes+N_1%7D%5Csum_%7Bj%3D0%7D%5E%7B3%7D%7B1_%7Bij%7D%5E%7Bobj%7D%5B%28t_w+-+t_w%27%29%5E2+%2B+%28t_h+-+t_h%27%29%5E2%5D%7D++%5C%5C+-+%5Clambda_%7Bobj%7D%5Csum_%7Bi%3D0%7D%5E%7BN%5Ctimes+N%7D%5Csum_%7Bj%3D0%7D%5E%7B3%7D%7B1_%7Bij%7D%5E%7Bobj%7Dlog%28c_%7Bij%7D%29%7D+%5C%5C+-%5Clambda_%7Bnoobj%7D%5Csum_%7Bi%3D0%7D%5E%7BN_1%5Ctimes+N_1%7D%5Csum_%7Bj%3D0%7D%5E%7B3%7D%7B1_%7Bij%7D%5E%7Bnoobj%7Dlog%281-c_%7Bij%7D%29%7D+%5C%5C+-%7B%5Clambda%7D_%7Bclass%7D%5Csum_%7Bi%3D0%7D%5E%7BN_1%5Ctimes+N_1%7D%5C%5C%5Csum_%7Bj%3D0%7D%5E%7B3%7D%7B1_%7Bij%7D%5E%7Bobj%7D+%5Csum_%7Bc+%5Cin+classes+%7D%5Bp_%7Bij%7D%27%28c%29log%28p_%7Bij%7D%28c%29%29%2B%281-p_%7Bij%7D%27%28c%29%29log%281-p_%7Bij%7D%28c%29%29%5D+%7D+)

Yolov3 Loss为三个特征图Loss之和：

![[公式]](https://www.zhihu.com/equation?tex=Loss%3Dloss_%7BN_1%7D++%2Bloss_%7BN_2%7D+%2Bloss_%7BN_3%7D++%5C%5C)

1. ![[公式]](https://www.zhihu.com/equation?tex=%5Clambda) 为权重常数，控制检测框Loss、obj置信度Loss、noobj置信度Loss之间的比例，通常负例的个数是正例的几十倍以上，可以通过权重超参控制检测效果。
2. ![[公式]](https://www.zhihu.com/equation?tex=1_%7Bij%7D%5E%7Bobj%7D) 若是正例则输出1，否则为0； ![[公式]](https://www.zhihu.com/equation?tex=1_%7Bij%7D%5E%7Bnoobj%7D) 若是负例则输出1，否则为0；忽略样例都输出0。
3. x、y、w、h使用MSE作为损失函数，也可以使用smooth L1 loss（出自Faster R-CNN）作为损失函数。smooth L1可以使训练更加平滑。置信度、类别标签由于是0，1二分类，所以使用交叉熵作为损失函数。



- 训练策略解释：

1. ground truth为什么不按照中心点分配对应的预测box？

（1）在Yolov3的训练策略中，不再像Yolov1那样，每个cell负责中心落在该cell中的ground truth。原因是Yolov3一共产生3个特征图，3个特征图上的cell，中心是有重合的。训练时，可能最契合的是特征图1的第3个box，但是推理的时候特征图2的第1个box置信度最高。所以Yolov3的训练，不再按照ground truth中心点，严格分配指定cell，而是根据预测值寻找IOU最大的预测框作为正例。

（2）笔者实验结果：第一种，ground truth先从9个先验框中确定最接近的先验框，这样可以确定ground truth所属第几个特征图以及第几个box位置，之后根据中心点进一步分配。第二种，全部4032个输出框直接和ground truth计算IOU，取IOU最高的cell分配ground truth。第二种计算方式的IOU数值，往往都比第一种要高，这样wh与xy的loss较小，网络可以更加关注类别和置信度的学习；其次，在推理时，是按照置信度排序，再进行nms筛选，第二种训练方式，每次给ground truth分配的box都是最契合的box，给这样的box置信度打1的标签，更加合理，最接近的box，在推理时更容易被发现。

\2. Yolov1中的置信度标签，就是预测框与真实框的IOU，Yolov3为什么是1？

（1）置信度意味着该预测框是或者不是一个真实物体，是一个二分类，所以标签是1、0更加合理。

（2）笔者实验结果：第一种：置信度标签取预测框与真实框的IOU；第二种：置信度标签取1。第一种的结果是，在训练时，有些预测框与真实框的IOU极限值就是0.7左右，置信度以0.7作为标签，置信度学习有一些偏差，最后学到的数值是0.5，0.6，那么假设推理时的激活阈值为0.7，这个检测框就被过滤掉了。但是IOU为0.7的预测框，其实已经是比较好的学习样例了。尤其是coco中的小像素物体，几个像素就可能很大程度影响IOU，所以第一种训练方法中，置信度的标签始终很小，无法有效学习，导致检测召回率不高。而检测框趋于收敛，IOU收敛至1，置信度就可以学习到1，这样的设想太过理想化。而使用第二种方法，召回率明显提升了很高。

\3. 为什么有忽略样例？

（1）忽略样例是Yolov3中的点睛之笔。由于Yolov3使用了多尺度特征图，不同尺度的特征图之间会有重合检测部分。比如有一个真实物体，在训练时被分配到的检测框是特征图1的第三个box，IOU达0.98，此时恰好特征图2的第一个box与该ground truth的IOU达0.95，也检测到了该ground truth，如果此时给其置信度强行打0的标签，网络学习效果会不理想。

（2）笔者实验结果：如果给全部的忽略样例置信度标签打0，那么最终的loss函数会变成 ![[公式]](https://www.zhihu.com/equation?tex=Loss_%7Bobj%7D) 与 ![[公式]](https://www.zhihu.com/equation?tex=Loss_%7Bnoobj%7D) 的拉扯，不管两个loss数值的权重怎么调整，或者网络预测趋向于大多数预测为负例，或者趋向于大多数预测为正例。而加入了忽略样例之后，网络才可以学习区分正负例。



- 优化器

作者在文中没有提及优化器，Adam，SGD等都可以用，github上Yolov3项目中，大多使用Adam优化器。



## 四、精度与性能

![img](https://pic4.zhimg.com/80/v2-393baa73310f62d60d72b85bda7d0ff5_720w.jpg)图五 精度对比图(on coco)

![img](https://picb.zhimg.com/80/v2-7353c6f6f8bfc45271a4af99470ff617_720w.jpg)图六 性能对比图(on coco)

直接说结论：Yolov3精度与SSD相比略有小优，与Faster R-CNN相比略有逊色，几乎持平，比RetinaNet差。但是速度是SSD、RetinaNet、Faster R-CNN至少2倍以上。输入尺寸为320*320的Yolov3，单张图片处理仅需22ms，简化后的Yolov3 tiny可以更快。



## 五、参考

文章：

[https://blog.csdn.net/qq_34795071/article/details/92803741](https://link.zhihu.com/?target=https%3A//blog.csdn.net/qq_34795071/article/details/92803741)

[https://blog.csdn.net/leviopku/article/details/82660381](https://link.zhihu.com/?target=https%3A//blog.csdn.net/leviopku/article/details/82660381)

代码：

[https://pjreddie.com/darknet/](https://link.zhihu.com/?target=https%3A//pjreddie.com/darknet/)

[https://github.com/qqwweee/keras-yolo3](https://link.zhihu.com/?target=https%3A//github.com/qqwweee/keras-yolo3)

[https://github.com/wizyoung/YOLOv3_TensorFlow](https://link.zhihu.com/?target=https%3A//github.com/wizyoung/YOLOv3_TensorFlow)

------

好不容易写完了Yolo三篇文章，我找到圈内知名设计师JF同学：

我：帮忙设计个文章的封面行不行啊？没什么要求，好看就行。

JF：最烦你这样的甲方，好歹是什么方面的内容，得告诉我啊。

我：Yolo呢，就是You only look once的意思，具体内容就不解释了，差不多就这意思，你看着弄吧。

两天后...

JF：我帮你直接放上去了哈，你一会上去看看。

我：好的，多谢！

等我看完以后...

![img](https://pic1.zhimg.com/80/v2-50016bb6c8597eaeabf8498e6176000e_720w.jpg)

------

Yolo三部曲完，欢迎留言讨论与指正。

编辑于 06-29

[计算机视觉](https://www.zhihu.com/topic/19590195)

[神经网络](https://www.zhihu.com/topic/19607065)

[物体检测](https://www.zhihu.com/topic/20190959)

赞同 299180 条评论

分享

喜欢收藏