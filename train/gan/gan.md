# 生成对抗网络 – Generative Adversarial Networks | GAN

⌚️: 2021年8月30日

📚参考

- [龙良曲 入门视频](https://www.bilibili.com/video/BV1RU4y1h74n?p=1)
-  [GAN原理](https://www.bilibili.com/video/BV16a4y157sC?from=search&seid=11723640036137669478) 

----

## 1、 GAN网络组成

![image-20210830133115198](imgs/image-20210830133115198.png)



一个例子🌰



![image-20210830133353228](imgs/image-20210830133353228.png)

![image-20210830133450490](imgs/image-20210830133450490.png)

## 2. 损失函数 & 优化过程



![](imgs/gan.png)

![image-20210830133922802](imgs/image-20210830133922802.png)

![image-20210830133949489](imgs/image-20210830133949489.png)

![image-20210830134001885](imgs/image-20210830134001885.png)

## 3. 为什么优化V(G,D)可以Pg分布与Pdata分类接近？



![image-20210830135241601](imgs/image-20210830135241601.png)

> 解释第2步到第3步：
>
> ![image-20210830135440694](imgs/image-20210830135440694.png)（1) 与![image-20210830135500809](imgs/image-20210830135500809.png)（2)变换，表示看待数据的角度不同，（1)是z变量服从Pz分布，而（2)是对（1)进行了G（生成器)得到，Pg分布。
>
> ![image-20210830135704016](imgs/image-20210830135704016.png)

![image-20210830135948516](imgs/image-20210830135948516.png)

![image-20210830140048976](imgs/image-20210830140048976.png)

![image-20210830140528114](imgs/image-20210830140528114.png)