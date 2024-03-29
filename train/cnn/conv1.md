# 1*1卷积的作用

⌚️: 2021-07-21

📚参考

---



## **1、降维（减少参数）**

**例子1 : GoogleNet中的3a模块**



![img](imgs\asdf.png)





**例子2：ResNet中的残差模块**

![img](imgs\asdfads.png)



## **2、升维（用最少的参数拓宽网络channal）**

**例子：**上一个例子中，不仅在输入处有一个`1*1`卷积核，在输出处也有一个卷积核，`3*3`，64的卷积核的channel是64，只需添加一个`1*1`，256的卷积核，只用64*256个参数就能把网络channel从64拓宽四倍到256。

## **3、跨通道信息交互（channal 的变换）**

例子：使用`1*1`卷积核，实现降维和升维的操作其实就是channel间信息的线性组合变化，`3*3`，64channels的卷积核后面添加一个`1*1`，28channels的卷积核，就变成了3*3，28channels的卷积核，原来的64个channels就可以理解为跨通道线性组合变成了28channels，这就是通道间的信息交互。

注意：只是在channel维度上做线性组合，W和H上是共享权值的sliding window

## **4、增加非线性特性**

1*1卷积核，可以在保持feature map尺度不变的（即不损失分辨率）的前提下大幅增加非线性特性（利用后接的非线性激活函数），把网络做的很deep。

**备注：**一个filter对应卷积后得到一个feature map，不同的filter(不同的weight和bias)，卷积以后得到不同的feature map，提取不同的特征，得到对应的specialized neuro。