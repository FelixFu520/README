# CGAN

⌚️: 2021年8月30日

📚参考

- [GAN、CGAN、ACGAN](https://www.bilibili.com/video/BV1n54115773?from=search&seid=11723640036137669478)



----

## 一、CGAN

### 1、网络结构

#### 1.1 GAN的弊端

![2](imgs/2.png)

![image-20210830151441831](imgs/image-20210830151441831.png)

G网络无关注点，把所有特征进行融合。

#### 1.2 CGAN(Conditional Generative Adversarial Nets)

![image-20210830151725361](imgs/image-20210830151725361.png)

![image-20210830151759082](imgs/image-20210830151759082.png)



### 2、损失函数

![image-20210830151854097](imgs/image-20210830151854097.png)

## 二、 InfoGAN

![image-20210830153156136](imgs/image-20210830153156136.png)

![image-20210830153344136](imgs/image-20210830153344136.png)

C向量，每个数值表示一个特征

InfoGAN可以从原始数据中分离出特征。

![image-20210830153555049](imgs/image-20210830153555049.png)

![image-20210830153635409](imgs/image-20210830153635409.png)

![image-20210830153955298](imgs/image-20210830153955298.png)

## 三、ACGAN

![image-20210830154236085](imgs/image-20210830154236085.png)

![image-20210830154340442](imgs/image-20210830154340442.png)