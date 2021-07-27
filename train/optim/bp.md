# BP算法讲解

⌚️: 2021年4月1日

📚参考

- [神经网络之BP算法(图说神经网络+BP算法理论推导+例子运用+代码)](https://blog.csdn.net/weixin_39441762/article/details/80446692)

---

## 1.    5字诀搞定BP反向传播算法推导

> [哔哩哔哩视频](https://www.bilibili.com/video/BV13J41157Wq?p=4)
>
> 鸡鸡踢连长

### 1.1 计算图

![](imgs/计算图.png)

### 1.2 激活函数

![](imgs/激活函数.png)

### 1.3 梯度求导

![](imgs/梯度下降.png)

### 1.4 链式求导

略，见视频

### 1.5 张量求导

![](imgs/张量求导1.png)

“YX拉伸术”是Y垂直拉开，X水平拉开。



![](imgs/张量求导2.png)

![](imgs/张量求导3.png)

![](imgs/张量求导4.png)

"求导升阶"，1阶张量对2阶矩阵求导，结果是3阶张量。

### 1.6 BP推导

![](imgs/bp1.png)

![](imgs/bp2.jpeg)

![](imgs/bp3.png)



## 2. 神经网络之BP算法

原文地址见末尾。   

原文写于2018年5月。修改于2019年11月17。 

最近在学习《Deep Learning》这本书，书中在前馈神经网络、全连接神经网络以及卷积神经网络等内容中，都有提到反向传播算法，这一算法可以说是神经网络中**求解参数**比较核心的部分了。为了更好地理解神经网络工作的原理，认识反向传播在神经网络中的运算机制，在综合《Deep Learning》书中的有关部分并且学习了b站讲解神经网络的相关视频及一些有关于BP算法的博客文章之后，笔者将自己的理解写下来，希望能为初学者理解反向传播算法起到一定的帮助。在此，对已为BP算法提供了学习思路的各位前辈表示敬意，特别是帮助我思考和理解BP算法的三位博主。

关于反向传播算法，我们首先需要清楚它的应用途径；其次,做一些神经网络知识的前期储备；之后，学习BP算法的工作原理；最后，认识到BP算法的局限性,了解改进方法。因此，本文从这4个点来讲解，划分为6部分：

### **2.1  反向传播算法应用领域**

 反向传播算法应用较为广泛，从字面意思理解，与前向传播相互对应。在简单的神经网络中，反向传播算法，可以理解为最优化损失函数过程，求解每个参与运算的参数的梯度的方法。在前馈神经网络中，反向传播从求解损失函数偏导过程中，步步向前求解每一层的参数梯度。在卷积神经网络中，反向传播可以求解全连接层的参数梯度。在循环神经网络中，反向传播算法可以求解每一个时刻t或者状态t的参数梯度（在RNN\LSTM\GRU中，反向传播更多是BPTT）。笔者如今对于BP的理解，认为是在优化损失函数或者目标函数过程中，求解参与运算的参数的梯度方法，是一种比较普遍的说法。

### **2.2 准备知识--**反向传播(BP)算法应用于神经网络

反向传播(BP)算法在深度学习中，应用广泛。这里仅以前馈神经网络中的BP算法作为介绍。神经网络是一个由输入层、隐藏层、输出层三部分组成的网络：数据从输入层，经过权重值和偏置项的线性变换处理，再通过激活层，得到隐藏层的输出，也即下一层的输入；隐藏层到输出层之间是，经过权重值和偏置项的线性变换，之后通过激活层，得到输出层。

​    

![img](imgs/59.png)

图2表示一个网络层为2的前馈神经网络：一个隐藏层，一个输出层；隐藏单元为5，记输入层到隐藏层的权重值为W，偏置项为b1,激活函数为g1，隐藏层到输出层的权重值为V,偏置项为b2，激活函数为g2，则图2的模型即为：

  ![\hat{Y}=g_{2}(V^{T}g_{1}(W^{T}X+b_{1})+b_{2})](https://private.codecogs.com/gif.latex?%5Chat%7BY%7D%3Dg_%7B2%7D%28V%5E%7BT%7Dg_%7B1%7D%28W%5E%7BT%7DX&plus;b_%7B1%7D%29&plus;b_%7B2%7D%29)

图2是一个比较简单的神经网络，通常，我们见到的神经网络，是具有多个隐藏层的网络，如图3：这是一个隐藏层个数为N个，每层隐藏单元数为5的神经网络。（PS：隐藏层设计，可以考虑层数设计和隐藏单元设计，可根据自己的需要自行设计。)

   

![img](imgs/61.png)

从输入层到隐藏层再到输出层，这一向前传递的过程，我们称之为前向传播。前向传播过程，往往是我们设定模型的过程，也可以理解为设定数学表达式或者列方程的过程。



### **2.3 BP算法原理及其实施步骤**

BP算法的核心思想：使用梯度下降来搜索可能的权向量的假设空间，以找到最佳的拟合样例的权向量。具体而言，即利用损失函数，每次向损失函数负梯度方向移动，直到损失函数取得最小值。

或者说，反向传播算法，是根据损失函数，求出损失函数关于每一层的权值及偏置项的偏导数，也称为梯度，用该值更新初始的权值和偏置项，一直更新到损失函数取得最小值或是设置的迭代次数完成为止。以此来计算神经网络中的最佳的参数。

由此，正式介绍BP算法前，我们需要知道前向传播过程，确定网络的设计。为此先设定一个只有一层的神经网络，作为讲解，如图4.

​                                      

![img](imgs/62.png)

设定：从输入层数据为X，输入层到隐藏层参数为w,b1，隐藏层到输出层参数为v,b2，激活函数用为g1,g2。于是模型设定为：

​                                 ![net_{1} = w^{T}x+b_{1},h=g_{1}(net_{1})](https://private.codecogs.com/gif.latex?net_%7B1%7D%20%3D%20w%5E%7BT%7Dx&plus;b_%7B1%7D%2Ch%3Dg_%7B1%7D%28net_%7B1%7D%29)                      （3-1）

隐藏层到输出层：

​                                ![net_{2} = v^{T}h+b_{2},\hat{y}=g_{2}(net_{2})](https://private.codecogs.com/gif.latex?net_%7B2%7D%20%3D%20v%5E%7BT%7Dh&plus;b_%7B2%7D%2C%5Chat%7By%7D%3Dg_%7B2%7D%28net_%7B2%7D%29)                        （3-2）

模型：

​                  ![\hat{y}=g_{2}(net_{2})=g_{2}(v^{T}g_{1}(net_{1})+b_{2})=g_{2}(v^{T}g_{1}(w^{T}x+b_{1})+b_{2})](https://private.codecogs.com/gif.latex?%5Chat%7By%7D%3Dg_%7B2%7D%28net_%7B2%7D%29%3Dg_%7B2%7D%28v%5E%7BT%7Dg_%7B1%7D%28net_%7B1%7D%29&plus;b_%7B2%7D%29%3Dg_%7B2%7D%28v%5E%7BT%7Dg_%7B1%7D%28w%5E%7BT%7Dx&plus;b_%7B1%7D%29&plus;b_%7B2%7D%29)         （3-3）

损失函数：

​                                    ![E(\theta )=\frac{1}{2}\sum_{i=1}^{2} (y_{i}-\hat{y_{i}})^2](https://private.codecogs.com/gif.latex?E%28%5Ctheta%20%29%3D%5Cfrac%7B1%7D%7B2%7D%5Csum_%7Bi%3D1%7D%5E%7B2%7D%20%28y_%7Bi%7D-%5Chat%7By_%7Bi%7D%7D%29%5E2)                          （3-4）

其中：

​               ![x =\begin{pmatrix} x_{1}\\ x_{2}\\ x_{3}\\ x_{4} \end{pmatrix},w=\begin{pmatrix} w_{11} &w_{12} &... &w_{15} \\ w_{21}&w_{22} &... &w_{25} \\ w_{31}&w_{32} &... &w_{35} \\ w_{41} &w_{42} &... &w_{45} \end{pmatrix},b_{1}=\begin{pmatrix} b_{11}\\ b_{12}\\ ...\\ b_{14} \end{pmatrix},net_{1}=\begin{pmatrix} net_{11}\\ net_{12}\\ ...\\ net_{14} \end{pmatrix}](https://private.codecogs.com/gif.latex?x%20%3D%5Cbegin%7Bpmatrix%7D%20x_%7B1%7D%5C%5C%20x_%7B2%7D%5C%5C%20x_%7B3%7D%5C%5C%20x_%7B4%7D%20%5Cend%7Bpmatrix%7D%2Cw%3D%5Cbegin%7Bpmatrix%7D%20w_%7B11%7D%20%26w_%7B12%7D%20%26...%20%26w_%7B15%7D%20%5C%5C%20w_%7B21%7D%26w_%7B22%7D%20%26...%20%26w_%7B25%7D%20%5C%5C%20w_%7B31%7D%26w_%7B32%7D%20%26...%20%26w_%7B35%7D%20%5C%5C%20w_%7B41%7D%20%26w_%7B42%7D%20%26...%20%26w_%7B45%7D%20%5Cend%7Bpmatrix%7D%2Cb_%7B1%7D%3D%5Cbegin%7Bpmatrix%7D%20b_%7B11%7D%5C%5C%20b_%7B12%7D%5C%5C%20...%5C%5C%20b_%7B14%7D%20%5Cend%7Bpmatrix%7D%2Cnet_%7B1%7D%3D%5Cbegin%7Bpmatrix%7D%20net_%7B11%7D%5C%5C%20net_%7B12%7D%5C%5C%20...%5C%5C%20net_%7B14%7D%20%5Cend%7Bpmatrix%7D)

​                   ![h =\begin{pmatrix} h_{1}\\ h_{2}\\ ...\\ h_{5} \end{pmatrix},v=\begin{pmatrix} v_{11} &v_{12} \\ v_{21} &v_{22} \\ ... &... \\ v_{51} &v_{52} \end{pmatrix},b_{2}=\begin{pmatrix} b_{21}\\ b_{22} \end{pmatrix},net_{2}=\begin{pmatrix} net_{21}\\ net_{22} \end{pmatrix}](https://private.codecogs.com/gif.latex?h%20%3D%5Cbegin%7Bpmatrix%7D%20h_%7B1%7D%5C%5C%20h_%7B2%7D%5C%5C%20...%5C%5C%20h_%7B5%7D%20%5Cend%7Bpmatrix%7D%2Cv%3D%5Cbegin%7Bpmatrix%7D%20v_%7B11%7D%20%26v_%7B12%7D%20%5C%5C%20v_%7B21%7D%20%26v_%7B22%7D%20%5C%5C%20...%20%26...%20%5C%5C%20v_%7B51%7D%20%26v_%7B52%7D%20%5Cend%7Bpmatrix%7D%2Cb_%7B2%7D%3D%5Cbegin%7Bpmatrix%7D%20b_%7B21%7D%5C%5C%20b_%7B22%7D%20%5Cend%7Bpmatrix%7D%2Cnet_%7B2%7D%3D%5Cbegin%7Bpmatrix%7D%20net_%7B21%7D%5C%5C%20net_%7B22%7D%20%5Cend%7Bpmatrix%7D)

​                                   ![\hat{y}=\begin{pmatrix} \hat{y_{1}}\\ \hat{y_{2}} \end{pmatrix},y=\begin{pmatrix} y_{1}\\ y_{2}\end{pmatrix}](https://private.codecogs.com/gif.latex?%5Chat%7By%7D%3D%5Cbegin%7Bpmatrix%7D%20%5Chat%7By_%7B1%7D%7D%5C%5C%20%5Chat%7By_%7B2%7D%7D%20%5Cend%7Bpmatrix%7D%2Cy%3D%5Cbegin%7Bpmatrix%7D%20y_%7B1%7D%5C%5C%20y_%7B2%7D%5Cend%7Bpmatrix%7D)    

以上述的模型设定为例，下面介绍BP算法步骤，通过BP算法的步骤，了解反向传播，是如何实现模型的参数更新。



#### 2.3.1 **实施步骤：**

  **1）**初始化网络中的权值和偏置项，分别记为

  **![w^{(0)},b_{1}^{(0)},v^{(0)},b_{2}^{(0)}](https://private.codecogs.com/gif.latex?w%5E%7B%280%29%7D%2Cb_%7B1%7D%5E%7B%280%29%7D%2Cv%5E%7B%280%29%7D%2Cb_%7B2%7D%5E%7B%280%29%7D)**                             （3-5）



  **2）**激活前向传播，得到各层输出和损失函数的期望值

**![E(\theta )=\frac{1}{2}\sum_{i=1}^{2}(y_{i}-\hat{y_{i}})^{2}](https://private.codecogs.com/gif.latex?E%28%5Ctheta%20%29%3D%5Cfrac%7B1%7D%7B2%7D%5Csum_%7Bi%3D1%7D%5E%7B2%7D%28y_%7Bi%7D-%5Chat%7By_%7Bi%7D%7D%29%5E%7B2%7D)**                          （3-6）

  其中，**![\theta](https://private.codecogs.com/gif.latex?%5Ctheta)**表示参数集合，![y](https://private.codecogs.com/gif.latex?y)表示真实值**，![\hat{y}](https://private.codecogs.com/gif.latex?%5Chat%7By%7D)**表示预测值，![\frac{1}{2}](https://private.codecogs.com/gif.latex?%5Cfrac%7B1%7D%7B2%7D)表示对总的误差值取平均，所以一般情况下，输出单元多少维，误差值求平均就除以多少；本模型设定中，输出值为2维列数据，故用误差值除以2。**一般情况下，损失函数的期望值表示为：**

​                                 **![E(\theta )=\frac{1}{n}\sum_{i=1}^{n}(y_{i}-\hat{y_{i}})^{2}](https://private.codecogs.com/gif.latex?E%28%5Ctheta%20%29%3D%5Cfrac%7B1%7D%7Bn%7D%5Csum_%7Bi%3D1%7D%5E%7Bn%7D%28y_%7Bi%7D-%5Chat%7By_%7Bi%7D%7D%29%5E%7B2%7D)**                         （3-6-1）

​    这是一组n维数据的输出，若是有m组这样的数据，损失函数的期望值为：

​                               **![E(\theta )=\frac{1}{m}\frac{1}{n}\sum_{j=1}^{m}\sum_{i=1}^{n}(y_{ji}-\hat{y}_{ji})^{2}](https://private.codecogs.com/gif.latex?E%28%5Ctheta%20%29%3D%5Cfrac%7B1%7D%7Bm%7D%5Cfrac%7B1%7D%7Bn%7D%5Csum_%7Bj%3D1%7D%5E%7Bm%7D%5Csum_%7Bi%3D1%7D%5E%7Bn%7D%28y_%7Bji%7D-%5Chat%7By%7D_%7Bji%7D%29%5E%7B2%7D)**                   （3-6-2）

​    若真实值与输出值表示为![y_{n\times m},\hat{y}_{n\times m}](https://private.codecogs.com/gif.latex?y_%7Bn%5Ctimes%20m%7D%2C%5Chat%7By%7D_%7Bn%5Ctimes%20m%7D)，上式可表示为：

​                                 ![E(\theta )=\frac{1}{mn}(y-\hat{y})^T(y-\hat{y})](https://private.codecogs.com/gif.latex?E%28%5Ctheta%20%29%3D%5Cfrac%7B1%7D%7Bmn%7D%28y-%5Chat%7By%7D%29%5ET%28y-%5Chat%7By%7D%29)                    （3-6-3）

​    一般情况下，输出数据为1维或是2维，输出的数据有多组。

  

**3）**根据损失函数，计算输出单元的误差项和隐藏单元的误差项

输出单元的误差项，即计算损失函数关于输出单元的梯度值或偏导数，根据链式法则有：

​                              **![\bigtriangledown _{(k)}v=\frac{\partial E}{\partial v}=\frac{\partial net_{2}}{\partial v}\frac{\partial \hat{y}}{\partial net_{2}}\frac{\partial E}{\partial \hat{y}}](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B%28k%29%7Dv%3D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20v%7D%3D%5Cfrac%7B%5Cpartial%20net_%7B2%7D%7D%7B%5Cpartial%20v%7D%5Cfrac%7B%5Cpartial%20%5Chat%7By%7D%7D%7B%5Cpartial%20net_%7B2%7D%7D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20%5Chat%7By%7D%7D)**    

​                             ![\bigtriangledown _{(k)}b_{2}=\frac{\partial E}{\partial b_{2}}=\frac{\partial net_{2}}{\partial b_{2}}\frac{\partial \hat{y}}{\partial net_{2}}\frac{\partial E}{\partial \hat{y}}](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B%28k%29%7Db_%7B2%7D%3D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20b_%7B2%7D%7D%3D%5Cfrac%7B%5Cpartial%20net_%7B2%7D%7D%7B%5Cpartial%20b_%7B2%7D%7D%5Cfrac%7B%5Cpartial%20%5Chat%7By%7D%7D%7B%5Cpartial%20net_%7B2%7D%7D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20%5Chat%7By%7D%7D)                    （3-7）

隐藏单元的误差项，即计算损失函数关于隐藏单元的梯度值或偏导数，根据链式法则有：

​                          **![\bigtriangledown _{(k)}w=\frac{\partial E}{\partial w}=\frac{\partial net_{1}}{\partial w}\frac{\partial h}{\partial net_{1}}\frac{\partial net_{2}}{\partial h}\frac{\partial \hat{y}}{\partial net_{2}}\frac{\partial E}{\partial \hat{y}}](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B%28k%29%7Dw%3D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20w%7D%3D%5Cfrac%7B%5Cpartial%20net_%7B1%7D%7D%7B%5Cpartial%20w%7D%5Cfrac%7B%5Cpartial%20h%7D%7B%5Cpartial%20net_%7B1%7D%7D%5Cfrac%7B%5Cpartial%20net_%7B2%7D%7D%7B%5Cpartial%20h%7D%5Cfrac%7B%5Cpartial%20%5Chat%7By%7D%7D%7B%5Cpartial%20net_%7B2%7D%7D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20%5Chat%7By%7D%7D)**            

​                          **![\bigtriangledown _{(k)}b_{1}=\frac{\partial E}{\partial b_{1}}=\frac{\partial net_{1}}{\partial b_{1}}\frac{\partial h}{\partial net_{1}}\frac{\partial net_{2}}{\partial h}\frac{\partial \hat{y}}{\partial net_{2}}\frac{\partial E}{\partial \hat{y}}](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B%28k%29%7Db_%7B1%7D%3D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20b_%7B1%7D%7D%3D%5Cfrac%7B%5Cpartial%20net_%7B1%7D%7D%7B%5Cpartial%20b_%7B1%7D%7D%5Cfrac%7B%5Cpartial%20h%7D%7B%5Cpartial%20net_%7B1%7D%7D%5Cfrac%7B%5Cpartial%20net_%7B2%7D%7D%7B%5Cpartial%20h%7D%5Cfrac%7B%5Cpartial%20%5Chat%7By%7D%7D%7B%5Cpartial%20net_%7B2%7D%7D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20%5Chat%7By%7D%7D)**            （3-8）

 **PS:** 对于复合函数中的向量或矩阵求偏导，复合函数内部函数的偏导总是左乘；对于复合函数中的标量求偏导，复合函数内部函数的偏导左乘或者右乘都可以。



 **4）** 更新神经网路中的权值和偏置项

 输出单元参数更新：       ![v^{(k)}=v^{(k-1)}-\eta \bigtriangledown _{(k)}v=v^{(k-1)}-\eta \frac{\partial E}{\partial v}, b_{2}^{(k)}=b_{2}^{(k-1)}-\eta \frac{\partial E}{\partial b_{2}}](https://private.codecogs.com/gif.latex?v%5E%7B%28k%29%7D%3Dv%5E%7B%28k-1%29%7D-%5Ceta%20%5Cbigtriangledown%20_%7B%28k%29%7Dv%3Dv%5E%7B%28k-1%29%7D-%5Ceta%20%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20v%7D%2C%20b_%7B2%7D%5E%7B%28k%29%7D%3Db_%7B2%7D%5E%7B%28k-1%29%7D-%5Ceta%20%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20b_%7B2%7D%7D)             （3-9）

 隐藏单元参数更新：       ![w^{(k)}=w^{(k-1)}-\eta \bigtriangledown _{(k)}w=w^{(k-1)}-\eta \frac{\partial E}{\partial w}, b_{1}^{(k)}=b_{1}^{(k-1)}-\eta \frac{\partial E}{\partial b_{1}}](https://private.codecogs.com/gif.latex?w%5E%7B%28k%29%7D%3Dw%5E%7B%28k-1%29%7D-%5Ceta%20%5Cbigtriangledown%20_%7B%28k%29%7Dw%3Dw%5E%7B%28k-1%29%7D-%5Ceta%20%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20w%7D%2C%20b_%7B1%7D%5E%7B%28k%29%7D%3Db_%7B1%7D%5E%7B%28k-1%29%7D-%5Ceta%20%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20b_%7B1%7D%7D)            （3-10）   

 其中，![\eta](https://private.codecogs.com/gif.latex?%5Ceta)表示学习率**，**k=1,2,...,n表示更新次数或迭代次数，k=1表示第一次更新，以此类推。此处可能和别处博客不太一样，但实质是一样的，此处的'+'或者'-'主要取决于损失函数.

如何定义损失函数或者定义参数更新均可，但参数的更新一定是向参数的负梯度方向。

 

**5）** 重复步骤2-4，直到损失函数小于事先给定的阈值或迭代次数用完为止，输出此时的参数即为目前最佳参数。



#### 2.3.2 详细步骤

**这便是BP算法的一个具体步骤，下面我们详细介绍BP算法步骤中的每一步**：



#####  **步骤1）**

初始化参数值(输出单元权值、偏置项和隐藏单元权值、偏置项均为模型的参数)，是为激活前向传播，得到每一层元素的输出值，进而得到损失函数的值。参数初始化，可以自己设定，也可以选择随机生成；一般情况下，自己写代码或者调用tensorflow或keras时，都是随机生成参数。因为初始参数对最终的参数影响不大，只会影响迭代的次数。



##### **步骤2）**

在步骤1的基础上，激活前向传播，得到![net_{1},h,net_{2},\hat{y}](https://private.codecogs.com/gif.latex?net_%7B1%7D%2Ch%2Cnet_%7B2%7D%2C%5Chat%7By%7D)的值，进而得到的值；其中的计算，根据前面模型设定中的公式计算。计算这些值是为计算步骤3中的误差项。



#####  **步骤3）**

计算各项误差，即计算参数关于损失函数的梯度或偏导数，之所以称之为误差，是因为损失函数本身为真实值与预测值之间的差异。计算参数的偏导数，根据的是微积分中的链式法则。具体推导如下：

###### **输出单元的误差项**

**输出单元的误差项**：输出单元v与损失函数E，不是直接相关，而是通过复合函数的形式关联，以设定的模型为例：

  ![E(v,b_{2})=\frac{1}{2}\sum_{i=1}^{2}(y_{i}-\hat{y_{i}})^{2}=\frac{1}{2}(y-\hat{y})^T(y-\hat{y})](https://private.codecogs.com/gif.latex?E%28v%2Cb_%7B2%7D%29%3D%5Cfrac%7B1%7D%7B2%7D%5Csum_%7Bi%3D1%7D%5E%7B2%7D%28y_%7Bi%7D-%5Chat%7By_%7Bi%7D%7D%29%5E%7B2%7D%3D%5Cfrac%7B1%7D%7B2%7D%28y-%5Chat%7By%7D%29%5ET%28y-%5Chat%7By%7D%29)   

​                                  ![=\frac{1}{2}(y-\hat{y}(net_{2}(v,b_{2})))^T(y-\hat{y}(net_{2}(v,b_{2}))](https://private.codecogs.com/gif.latex?%3D%5Cfrac%7B1%7D%7B2%7D%28y-%5Chat%7By%7D%28net_%7B2%7D%28v%2Cb_%7B2%7D%29%29%29%5ET%28y-%5Chat%7By%7D%28net_%7B2%7D%28v%2Cb_%7B2%7D%29%29)      （3-11）

其中![E(v,b_{2})](https://private.codecogs.com/gif.latex?E%28v%2Cb_%7B2%7D%29)表示损失函数化为与参数v，b2相关的表达式。

根据链式法则，输出单元v与损失函数E的误差项为：                

​                              **![\bigtriangledown _{(k)}v=\frac{\partial E}{\partial v}=\frac{\partial net_{2}}{\partial v}\frac{\partial \hat{y}}{\partial net_{2}}\frac{\partial E}{\partial \hat{y}}](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B%28k%29%7Dv%3D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20v%7D%3D%5Cfrac%7B%5Cpartial%20net_%7B2%7D%7D%7B%5Cpartial%20v%7D%5Cfrac%7B%5Cpartial%20%5Chat%7By%7D%7D%7B%5Cpartial%20net_%7B2%7D%7D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20%5Chat%7By%7D%7D)**

​                              ![\bigtriangledown _{(k)}b_{2}=\frac{\partial E}{\partial b_{2}}=\frac{\partial net_{2}}{\partial b_{2}}\frac{\partial \hat{y}}{\partial net_{2}}\frac{\partial E}{\partial \hat{y}}](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B%28k%29%7Db_%7B2%7D%3D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20b_%7B2%7D%7D%3D%5Cfrac%7B%5Cpartial%20net_%7B2%7D%7D%7B%5Cpartial%20b_%7B2%7D%7D%5Cfrac%7B%5Cpartial%20%5Chat%7By%7D%7D%7B%5Cpartial%20net_%7B2%7D%7D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20%5Chat%7By%7D%7D)                     （3-12）

求出上式中每一个偏导：

​                    ![\frac{\partial E}{\partial \hat{y}}=\frac{1}{2\partial \hat{y}}\partial ((y-\hat{y})^T(y-\hat{y}))=\frac{1}{2\partial \hat{y}}\partial (y^Ty-y^T\hat{y}-\hat{y}^Ty+\hat{y}^T\hat{y})](https://private.codecogs.com/gif.latex?%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20%5Chat%7By%7D%7D%3D%5Cfrac%7B1%7D%7B2%5Cpartial%20%5Chat%7By%7D%7D%5Cpartial%20%28%28y-%5Chat%7By%7D%29%5ET%28y-%5Chat%7By%7D%29%29%3D%5Cfrac%7B1%7D%7B2%5Cpartial%20%5Chat%7By%7D%7D%5Cpartial%20%28y%5ETy-y%5ET%5Chat%7By%7D-%5Chat%7By%7D%5ETy&plus;%5Chat%7By%7D%5ET%5Chat%7By%7D%29)

​                        ![=\frac{1}{2}(-y-y+\hat{y}+\hat{y})=\hat{y}-y](https://private.codecogs.com/gif.latex?%3D%5Cfrac%7B1%7D%7B2%7D%28-y-y&plus;%5Chat%7By%7D&plus;%5Chat%7By%7D%29%3D%5Chat%7By%7D-y)                              （3-13）

​                                   ![\frac{\partial \hat{y}}{\partial net_{2}}=\frac{\partial g_{2}(net_{2})}{\partial net_{2}}](https://private.codecogs.com/gif.latex?%5Cfrac%7B%5Cpartial%20%5Chat%7By%7D%7D%7B%5Cpartial%20net_%7B2%7D%7D%3D%5Cfrac%7B%5Cpartial%20g_%7B2%7D%28net_%7B2%7D%29%7D%7B%5Cpartial%20net_%7B2%7D%7D)                            （3-14）

​                                ![\frac{\partial net_{2}}{\partial v}=\frac{\partial (v^Th+b_{2})}{\partial v}=h](https://private.codecogs.com/gif.latex?%5Cfrac%7B%5Cpartial%20net_%7B2%7D%7D%7B%5Cpartial%20v%7D%3D%5Cfrac%7B%5Cpartial%20%28v%5ETh&plus;b_%7B2%7D%29%7D%7B%5Cpartial%20v%7D%3Dh)                         （3-15）

​                              ![\frac{\partial net_{2}}{\partial b_{2}}=\frac{\partial (v^Th+b_{2})}{\partial b_{2}}=\begin{pmatrix} 1\\ 1\end{pmatrix}^T](https://private.codecogs.com/gif.latex?%5Cfrac%7B%5Cpartial%20net_%7B2%7D%7D%7B%5Cpartial%20b_%7B2%7D%7D%3D%5Cfrac%7B%5Cpartial%20%28v%5ETh&plus;b_%7B2%7D%29%7D%7B%5Cpartial%20b_%7B2%7D%7D%3D%5Cbegin%7Bpmatrix%7D%201%5C%5C%201%5Cend%7Bpmatrix%7D%5ET)                        (3-16)

其中，![net_{2}](https://private.codecogs.com/gif.latex?net_%7B2%7D)关于激活函数![g_{2}](https://private.codecogs.com/gif.latex?g_%7B2%7D)求偏导，需要根据具体的激活函数而定，每一层的激活函数可以选择不同的函数，一般情况下，为简单化模型设计和求导方便，会设定为同一个函数。此处假设选择激活函数为sigmoid函数，那么有： 

​         ![\frac{\partial \hat{y}}{\partial net_{2}}=\frac{\partial g_{2}(net_{2})}{\partial net_{2}}=\begin{pmatrix} \partial sigmoid(net_{21})/\partial net_{21}\\ \partial sigmoid(net_{22})/\partial net_{22}\end{pmatrix}](https://private.codecogs.com/gif.latex?%5Cfrac%7B%5Cpartial%20%5Chat%7By%7D%7D%7B%5Cpartial%20net_%7B2%7D%7D%3D%5Cfrac%7B%5Cpartial%20g_%7B2%7D%28net_%7B2%7D%29%7D%7B%5Cpartial%20net_%7B2%7D%7D%3D%5Cbegin%7Bpmatrix%7D%20%5Cpartial%20sigmoid%28net_%7B21%7D%29/%5Cpartial%20net_%7B21%7D%5C%5C%20%5Cpartial%20sigmoid%28net_%7B22%7D%29/%5Cpartial%20net_%7B22%7D%5Cend%7Bpmatrix%7D)

​              ![=\begin{pmatrix} \frac{1}{1+exp(-net_{21})}\times(1-\frac{1}{1+exp(-net_{21})}) \\ \frac{1}{1+exp(-net_{22})}\times(1-\frac{1}{1+exp(-net_{22})})\end{pmatrix}=\begin{pmatrix} \hat{y}_{1}(1-\hat{y}_1)\\ \hat{y}_{2}(1-\hat{y}_2)\end{pmatrix}=\hat{y}\bigodot (1-\hat{y})](https://private.codecogs.com/gif.latex?%3D%5Cbegin%7Bpmatrix%7D%20%5Cfrac%7B1%7D%7B1&plus;exp%28-net_%7B21%7D%29%7D%5Ctimes%281-%5Cfrac%7B1%7D%7B1&plus;exp%28-net_%7B21%7D%29%7D%29%20%5C%5C%20%5Cfrac%7B1%7D%7B1&plus;exp%28-net_%7B22%7D%29%7D%5Ctimes%281-%5Cfrac%7B1%7D%7B1&plus;exp%28-net_%7B22%7D%29%7D%29%5Cend%7Bpmatrix%7D%3D%5Cbegin%7Bpmatrix%7D%20%5Chat%7By%7D_%7B1%7D%281-%5Chat%7By%7D_1%29%5C%5C%20%5Chat%7By%7D_%7B2%7D%281-%5Chat%7By%7D_2%29%5Cend%7Bpmatrix%7D%3D%5Chat%7By%7D%5Cbigodot%20%281-%5Chat%7By%7D%29)   (3-17)

**PS：因为sigmoid(z)中z是标量，对z求偏导，有：**

​        ![\frac{\partial sigmoid(z)}{\partial z}=\frac{\partial (1/(1+exp(-z))}{\partial z}=\frac{exp(-z)}{(1+exp(-z))^2}](https://private.codecogs.com/gif.latex?%5Cfrac%7B%5Cpartial%20sigmoid%28z%29%7D%7B%5Cpartial%20z%7D%3D%5Cfrac%7B%5Cpartial%20%281/%281&plus;exp%28-z%29%29%7D%7B%5Cpartial%20z%7D%3D%5Cfrac%7Bexp%28-z%29%7D%7B%281&plus;exp%28-z%29%29%5E2%7D)

​                    ![=\frac{1}{1+exp(-z)}\times \frac{exp(-z)}{1+exp(-z)}=\frac{1}{1+exp(-z)}\times (1-\frac{1}{1+exp(-z)})](https://private.codecogs.com/gif.latex?%3D%5Cfrac%7B1%7D%7B1&plus;exp%28-z%29%7D%5Ctimes%20%5Cfrac%7Bexp%28-z%29%7D%7B1&plus;exp%28-z%29%7D%3D%5Cfrac%7B1%7D%7B1&plus;exp%28-z%29%7D%5Ctimes%20%281-%5Cfrac%7B1%7D%7B1&plus;exp%28-z%29%7D%29)   



**本文定义了z为向量，对于向量就有了式(3-17)的逐元素相乘的式子。**

于是，为简化后面的计算，记

​                           ![\delta ^{(k)}=\frac{\partial \hat{y}}{\partial net_{2}}\frac{\partial E}{\partial \hat{y}}=\hat{y}\odot (1-\hat{y})\odot (\hat{y}-y)](https://private.codecogs.com/gif.latex?%5Cdelta%20%5E%7B%28k%29%7D%3D%5Cfrac%7B%5Cpartial%20%5Chat%7By%7D%7D%7B%5Cpartial%20net_%7B2%7D%7D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20%5Chat%7By%7D%7D%3D%5Chat%7By%7D%5Codot%20%281-%5Chat%7By%7D%29%5Codot%20%28%5Chat%7By%7D-y%29)                 (3-18)

其中，![\delta ^{(k)}](https://private.codecogs.com/gif.latex?%5Cdelta%20%5E%7B%28k%29%7D)表示第k次求损失函数关于![net_{2}](https://private.codecogs.com/gif.latex?net_%7B2%7D)的偏导；![\odot](https://private.codecogs.com/gif.latex?%5Codot)表示逐元素相乘，即两个向量或两个矩阵对应的元素相乘，例如：   

​                          ![\begin{pmatrix} a_{11} &a_{12} \\ a_{21} &a_{22}} \end{pmatrix}\odot \begin{pmatrix} b_{11} &b_{12} \\ b_{21} &b_{22}} \end{pmatrix}=\begin{pmatrix} a_{11}b_{11} &a_{12}b_{12} \\ a_{21}b_{21} &a_{22}b_{22}} \end{pmatrix}](https://private.codecogs.com/gif.latex?%5Cbegin%7Bpmatrix%7D%20a_%7B11%7D%20%26a_%7B12%7D%20%5C%5C%20a_%7B21%7D%20%26a_%7B22%7D%7D%20%5Cend%7Bpmatrix%7D%5Codot%20%5Cbegin%7Bpmatrix%7D%20b_%7B11%7D%20%26b_%7B12%7D%20%5C%5C%20b_%7B21%7D%20%26b_%7B22%7D%7D%20%5Cend%7Bpmatrix%7D%3D%5Cbegin%7Bpmatrix%7D%20a_%7B11%7Db_%7B11%7D%20%26a_%7B12%7Db_%7B12%7D%20%5C%5C%20a_%7B21%7Db_%7B21%7D%20%26a_%7B22%7Db_%7B22%7D%7D%20%5Cend%7Bpmatrix%7D)

于是，**输出单元的误差项**为：

​                                   ![\bigtriangledown _{(k)}v=\frac{\partial E}{\partial v}=h\cdot \delta ^{(k)T}](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B%28k%29%7Dv%3D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20v%7D%3Dh%5Ccdot%20%5Cdelta%20%5E%7B%28k%29T%7D)                      (3-19)

​                                ![\bigtriangledown _{(k)}b_{2}=\frac{\partial E}{\partial b_{2}}=\begin{pmatrix} 1\\ 1\end{pmatrix}\odot \delta ^{(k)}=\delta ^{(k)}](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B%28k%29%7Db_%7B2%7D%3D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20b_%7B2%7D%7D%3D%5Cbegin%7Bpmatrix%7D%201%5C%5C%201%5Cend%7Bpmatrix%7D%5Codot%20%5Cdelta%20%5E%7B%28k%29%7D%3D%5Cdelta%20%5E%7B%28k%29%7D)                (3-20)

**此处说明**：若遇式(3-15)的偏导(对权值求偏导)，链式法则处理方式均如式(3-19)；若遇式(3-16)的偏导(对偏置项求偏导)，链式法则处理方式均如式(3-20)。



###### 隐藏单元的误差项

**隐藏单元的误差项：**隐藏单元w与损失函数E，通过复合函数的形式关联，以设定的模型整理为：

​     **![E(w,b_{1})=\frac{1}{2}(y-\hat{y})^{T}(y-\hat{y})](https://private.codecogs.com/gif.latex?E%28w%2Cb_%7B1%7D%29%3D%5Cfrac%7B1%7D%7B2%7D%28y-%5Chat%7By%7D%29%5E%7BT%7D%28y-%5Chat%7By%7D%29)**

​             **![=\frac{1}{2}(y-\hat{y}(net_{2}(h(net_{1}(w,b_{1}),b_{2}))))^T(y-\hat{y}(net_{2}(h(net_{1}(w,b_{1}),b_{2})))))](https://private.codecogs.com/gif.latex?%3D%5Cfrac%7B1%7D%7B2%7D%28y-%5Chat%7By%7D%28net_%7B2%7D%28h%28net_%7B1%7D%28w%2Cb_%7B1%7D%29%2Cb_%7B2%7D%29%29%29%29%5ET%28y-%5Chat%7By%7D%28net_%7B2%7D%28h%28net_%7B1%7D%28w%2Cb_%7B1%7D%29%2Cb_%7B2%7D%29%29%29%29%29)** （3-21）

根据链式法则，隐藏单元w与损失函数E的误差项为：

​                        **![\bigtriangledown _{(k)}w=\frac{\partial E}{\partial w}=\frac{\partial net_{1}}{\partial w}\frac{\partial h}{\partial net_{1}}\frac{\partial net_{2}}{\partial h}\frac{\partial \hat{y}}{\partial net_{2}}\frac{\partial E}{\partial \hat{y}}](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B%28k%29%7Dw%3D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20w%7D%3D%5Cfrac%7B%5Cpartial%20net_%7B1%7D%7D%7B%5Cpartial%20w%7D%5Cfrac%7B%5Cpartial%20h%7D%7B%5Cpartial%20net_%7B1%7D%7D%5Cfrac%7B%5Cpartial%20net_%7B2%7D%7D%7B%5Cpartial%20h%7D%5Cfrac%7B%5Cpartial%20%5Chat%7By%7D%7D%7B%5Cpartial%20net_%7B2%7D%7D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20%5Chat%7By%7D%7D)**

​                       **![\bigtriangledown _{(k)}b_{1}=\frac{\partial E}{\partial b_{1}}=\frac{\partial net_{1}}{\partial b_{1}}\frac{\partial h}{\partial net_{1}}\frac{\partial net_{2}}{\partial h}\frac{\partial \hat{y}}{\partial net_{2}}\frac{\partial E}{\partial \hat{y}}](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B%28k%29%7Db_%7B1%7D%3D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20b_%7B1%7D%7D%3D%5Cfrac%7B%5Cpartial%20net_%7B1%7D%7D%7B%5Cpartial%20b_%7B1%7D%7D%5Cfrac%7B%5Cpartial%20h%7D%7B%5Cpartial%20net_%7B1%7D%7D%5Cfrac%7B%5Cpartial%20net_%7B2%7D%7D%7B%5Cpartial%20h%7D%5Cfrac%7B%5Cpartial%20%5Chat%7By%7D%7D%7B%5Cpartial%20net_%7B2%7D%7D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20%5Chat%7By%7D%7D)**            （3-22）

同样的求导法则，得到**隐藏单元的误差项**为：

​                      ![\bigtriangledown _{(k)}w=\frac{\partial E}{\partial w}=x\cdot (h\odot (1-h)\odot (v-\delta ^{(K)}))^T](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B%28k%29%7Dw%3D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20w%7D%3Dx%5Ccdot%20%28h%5Codot%20%281-h%29%5Codot%20%28v-%5Cdelta%20%5E%7B%28K%29%7D%29%29%5ET)            （3-23）

​          ![\bigtriangledown _{(k)}b_{1}=\frac{\partial E}{\partial b_{1}}=\begin{pmatrix} 1\\ 1\\ ...\\ 1 \end{pmatrix}\odot (h\odot (1-h)\odot (v\cdot \delta ^{(k)}))=h\odot (1-h)\odot (v\cdot \delta ^{(k)}))](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B%28k%29%7Db_%7B1%7D%3D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20b_%7B1%7D%7D%3D%5Cbegin%7Bpmatrix%7D%201%5C%5C%201%5C%5C%20...%5C%5C%201%20%5Cend%7Bpmatrix%7D%5Codot%20%28h%5Codot%20%281-h%29%5Codot%20%28v%5Ccdot%20%5Cdelta%20%5E%7B%28k%29%7D%29%29%3Dh%5Codot%20%281-h%29%5Codot%20%28v%5Ccdot%20%5Cdelta%20%5E%7B%28k%29%7D%29%29)（3-24）

   其中：

​                                   ![\frac{\partial net_{2}}{\partial h}=\frac{\partial (v^{T}h+b_{2})}{\partial h}=v](https://private.codecogs.com/gif.latex?%5Cfrac%7B%5Cpartial%20net_%7B2%7D%7D%7B%5Cpartial%20h%7D%3D%5Cfrac%7B%5Cpartial%20%28v%5E%7BT%7Dh&plus;b_%7B2%7D%29%7D%7B%5Cpartial%20h%7D%3Dv)                 （3-25）

​                             ![\frac{\partial h}{\partial net_{1}}=\frac{\partial (sigmoid(net_{1}))}{\partial net_{1}}=h\odot (1-h)](https://private.codecogs.com/gif.latex?%5Cfrac%7B%5Cpartial%20h%7D%7B%5Cpartial%20net_%7B1%7D%7D%3D%5Cfrac%7B%5Cpartial%20%28sigmoid%28net_%7B1%7D%29%29%7D%7B%5Cpartial%20net_%7B1%7D%7D%3Dh%5Codot%20%281-h%29)          (3-26)

​                                  ![\frac{\partial net_{1}}{\partial w}=\frac{(w^Tx+b_{1})}{\partial w}=x](https://private.codecogs.com/gif.latex?%5Cfrac%7B%5Cpartial%20net_%7B1%7D%7D%7B%5Cpartial%20w%7D%3D%5Cfrac%7B%28w%5ETx&plus;b_%7B1%7D%29%7D%7B%5Cpartial%20w%7D%3Dx)                   (3-27)

​                                 ![\frac{\partial net_{1}}{\partial b_{1}}=\frac{\partial (w^Tx+b)}{\partial b_{1}}=\begin{pmatrix} 1\\ 1\\... \\ 1 \end{pmatrix}^T](https://private.codecogs.com/gif.latex?%5Cfrac%7B%5Cpartial%20net_%7B1%7D%7D%7B%5Cpartial%20b_%7B1%7D%7D%3D%5Cfrac%7B%5Cpartial%20%28w%5ETx&plus;b%29%7D%7B%5Cpartial%20b_%7B1%7D%7D%3D%5Cbegin%7Bpmatrix%7D%201%5C%5C%201%5C%5C...%20%5C%5C%201%20%5Cend%7Bpmatrix%7D%5ET)                (3-28)

 **说明**：若遇式(3-25)(对隐藏单元求偏导)，链式法则处理如式(3-23)；式(3-15)和(3-26)同，故有相同的处理方式；式(3-16)和(3-27)同，故有相同的处理方式。

 **补充**：若有多个隐藏层时，逐步计算隐藏层的权值和偏置项误差，推导的规则同上。例如：一个隐藏层为2，隐藏单元为5的神经网络：

​                        

![img](imgs/63a.png)

输出层到隐藏层2的误差项同式(3-19)

隐藏层2到隐藏层1的误差项为：

​                        ![\bigtriangledown _{(k)}w2=\frac{\partial E}{\partial w2}=h_{1}\cdot (h_{2}\odot (1-h_{2})\odot (v\cdot \delta ^{(k)}))^T](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B%28k%29%7Dw2%3D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20w2%7D%3Dh_%7B1%7D%5Ccdot%20%28h_%7B2%7D%5Codot%20%281-h_%7B2%7D%29%5Codot%20%28v%5Ccdot%20%5Cdelta%20%5E%7B%28k%29%7D%29%29%5ET)              (3-29)

记：              

​                                ![\delta _{1}^{(k)}=h_{2}\odot (1-h_{2})\odot (v\cdot \delta ^{(k)})^T](https://private.codecogs.com/gif.latex?%5Cdelta%20_%7B1%7D%5E%7B%28k%29%7D%3Dh_%7B2%7D%5Codot%20%281-h_%7B2%7D%29%5Codot%20%28v%5Ccdot%20%5Cdelta%20%5E%7B%28k%29%7D%29%5ET)                      (3-30)

隐藏层1到输入层的误差项为：

​                        ![\bigtriangledown _{(k)}w1=\frac{\partial E}{\partial w1}=x\cdot (h_{1}\odot (1-h_{1})\odot (w2\cdot \delta _{1}^{(k)}))^T](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B%28k%29%7Dw1%3D%5Cfrac%7B%5Cpartial%20E%7D%7B%5Cpartial%20w1%7D%3Dx%5Ccdot%20%28h_%7B1%7D%5Codot%20%281-h_%7B1%7D%29%5Codot%20%28w2%5Ccdot%20%5Cdelta%20_%7B1%7D%5E%7B%28k%29%7D%29%29%5ET)            (3-31)

从上述中，容易看出，无论多少层隐藏层，其误差项都是同样的结构。

##### 步骤4）

 更新神经网路中的权值和偏置项。学习率自己设定，学习率太大，容易跳过最佳的参数；学习率太小，容易陷入局部极小值。

##### 步骤5） 

设定阈值e或者设定迭代次数，当损失函数值小于阈值e时，或当迭代次数用完时，输出最终参数。



### **2.4 实例运用**

 为能更好理解BP算法和知道如何运用BP算法，下面以一个实际的例子来说明运用BP算法的具体操作。

有一组数据![X=\begin{bmatrix} 0.05\\ 0.10\end{bmatrix},Y=\begin{bmatrix} 0\\ 1\end{bmatrix}](https://private.codecogs.com/gif.latex?X%3D%5Cbegin%7Bbmatrix%7D%200.05%5C%5C%200.10%5Cend%7Bbmatrix%7D%2CY%3D%5Cbegin%7Bbmatrix%7D%200%5C%5C%201%5Cend%7Bbmatrix%7D)，目的是训练这两组数据，找到输入X计算得到Y的预测值尽可能接近于真实值的参数。设定模型：设计一个隐藏层为1，隐藏单元数为2，激活函数为sigmod函数的模型，运用反向传播算法，得到参数。网络如图5：

​                        

![img](imgs/64a.png)

于是有：

​                          ![x=\begin{bmatrix}x_{1}\\ x_{2}\end{bmatrix}, w=\begin{bmatrix}w_{11} &w_{12} \\ w_{21}&w_{22} \end{bmatrix}, b_{1}=\begin{bmatrix}b_{11}\\ b_{12}\end{bmatrix}, h=\begin{bmatrix}h_{1}\\ h_{2}\end{bmatrix}](https://private.codecogs.com/gif.latex?x%3D%5Cbegin%7Bbmatrix%7Dx_%7B1%7D%5C%5C%20x_%7B2%7D%5Cend%7Bbmatrix%7D%2C%20w%3D%5Cbegin%7Bbmatrix%7Dw_%7B11%7D%20%26w_%7B12%7D%20%5C%5C%20w_%7B21%7D%26w_%7B22%7D%20%5Cend%7Bbmatrix%7D%2C%20b_%7B1%7D%3D%5Cbegin%7Bbmatrix%7Db_%7B11%7D%5C%5C%20b_%7B12%7D%5Cend%7Bbmatrix%7D%2C%20h%3D%5Cbegin%7Bbmatrix%7Dh_%7B1%7D%5C%5C%20h_%7B2%7D%5Cend%7Bbmatrix%7D)

​                             ![v=\begin{bmatrix}v_{11} &v_{12} \\ v_{21}&v_{22} \end{bmatrix}, b_{2}=\begin{bmatrix}b_{21}\\ b_{22}\end{bmatrix}, \hat{y}=\begin{bmatrix}\hat{y}_{1}\\ \hat{y}_{2}\end{bmatrix}](https://private.codecogs.com/gif.latex?v%3D%5Cbegin%7Bbmatrix%7Dv_%7B11%7D%20%26v_%7B12%7D%20%5C%5C%20v_%7B21%7D%26v_%7B22%7D%20%5Cend%7Bbmatrix%7D%2C%20b_%7B2%7D%3D%5Cbegin%7Bbmatrix%7Db_%7B21%7D%5C%5C%20b_%7B22%7D%5Cend%7Bbmatrix%7D%2C%20%5Chat%7By%7D%3D%5Cbegin%7Bbmatrix%7D%5Chat%7By%7D_%7B1%7D%5C%5C%20%5Chat%7By%7D_%7B2%7D%5Cend%7Bbmatrix%7D)

​                            ![net_{1}=w^Tx+b_{1},h=sigmoid(net_{1})](https://private.codecogs.com/gif.latex?net_%7B1%7D%3Dw%5ETx&plus;b_%7B1%7D%2Ch%3Dsigmoid%28net_%7B1%7D%29)

​                            ![net_{2}=v^Tx+b_{2},h=sigmoid(net_{2})](https://private.codecogs.com/gif.latex?net_%7B2%7D%3Dv%5ETx&plus;b_%7B2%7D%2Ch%3Dsigmoid%28net_%7B2%7D%29)                    (4-1)

根据BP算法步骤：

 1）初始化网络中的所有参数并给出学习率![\eta](https://private.codecogs.com/gif.latex?%5Ceta)：

​                    ![w=\begin{bmatrix}0.15 &0.20 \\ 0.25 &0.30 \end{bmatrix}, b_{1}=\begin{bmatrix}0.1\\ 0.1\end{bmatrix}, v=\begin{bmatrix}0.40 &0.45 \\ 0.50 &0.55 \end{bmatrix}, b_{2}=\begin{bmatrix}0.2\\ 0.2\end{bmatrix},\eta =0.5](https://private.codecogs.com/gif.latex?w%3D%5Cbegin%7Bbmatrix%7D0.15%20%260.20%20%5C%5C%200.25%20%260.30%20%5Cend%7Bbmatrix%7D%2C%20b_%7B1%7D%3D%5Cbegin%7Bbmatrix%7D0.1%5C%5C%200.1%5Cend%7Bbmatrix%7D%2C%20v%3D%5Cbegin%7Bbmatrix%7D0.40%20%260.45%20%5C%5C%200.50%20%260.55%20%5Cend%7Bbmatrix%7D%2C%20b_%7B2%7D%3D%5Cbegin%7Bbmatrix%7D0.2%5C%5C%200.2%5Cend%7Bbmatrix%7D%2C%5Ceta%20%3D0.5)

  2）激活前向传播，将参数带入式(4-1)，并计算损失函数：

​    输入层-->隐藏层：

​                         ![net_{1}=w^Tx+b_{1}=\bigl(\begin{smallmatrix} 0.15*0.05+0.25*0.1+0.1\\ 0.20*0.05+0.30*0.1+0.1 \end{smallmatrix}\bigr)=\bigl(\begin{smallmatrix} 0.1325\\ 0.1400 \end{smallmatrix}\bigr)](https://private.codecogs.com/gif.latex?net_%7B1%7D%3Dw%5ETx&plus;b_%7B1%7D%3D%5Cbigl%28%5Cbegin%7Bsmallmatrix%7D%200.15*0.05&plus;0.25*0.1&plus;0.1%5C%5C%200.20*0.05&plus;0.30*0.1&plus;0.1%20%5Cend%7Bsmallmatrix%7D%5Cbigr%29%3D%5Cbigl%28%5Cbegin%7Bsmallmatrix%7D%200.1325%5C%5C%200.1400%20%5Cend%7Bsmallmatrix%7D%5Cbigr%29)            (4-2)

​                           ![h=sigmoid(net_{1})=sigmoid\bigl(\begin{smallmatrix} 0.1325\\ 0.1400\end{smallmatrix}\bigr)=\bigl(\begin{smallmatrix} 0.5331\\ 0.5349 \end{smallmatrix}\bigr)](https://private.codecogs.com/gif.latex?h%3Dsigmoid%28net_%7B1%7D%29%3Dsigmoid%5Cbigl%28%5Cbegin%7Bsmallmatrix%7D%200.1325%5C%5C%200.1400%5Cend%7Bsmallmatrix%7D%5Cbigr%29%3D%5Cbigl%28%5Cbegin%7Bsmallmatrix%7D%200.5331%5C%5C%200.5349%20%5Cend%7Bsmallmatrix%7D%5Cbigr%29)             (4-3)

​     隐藏层-->输出层：

​                      ![net_{2}=v^Tx+b_{2}=\bigl(\begin{smallmatrix} 0.40*0.5331+0.5*0.5349+0.2\\ 0.45*0.5331+0.55*0.5349+0.2 \end{smallmatrix}\bigr)=\bigl(\begin{smallmatrix} 0.6807\\ 0.7341 \end{smallmatrix}\bigr)](https://private.codecogs.com/gif.latex?net_%7B2%7D%3Dv%5ETx&plus;b_%7B2%7D%3D%5Cbigl%28%5Cbegin%7Bsmallmatrix%7D%200.40*0.5331&plus;0.5*0.5349&plus;0.2%5C%5C%200.45*0.5331&plus;0.55*0.5349&plus;0.2%20%5Cend%7Bsmallmatrix%7D%5Cbigr%29%3D%5Cbigl%28%5Cbegin%7Bsmallmatrix%7D%200.6807%5C%5C%200.7341%20%5Cend%7Bsmallmatrix%7D%5Cbigr%29)        (4-4)

​                         ![\hat{Y}=sigmoid(net_{2})=sigmoid\bigl(\begin{smallmatrix} 0.6807\\ 0.7341\end{smallmatrix}\bigr)=\bigl(\begin{smallmatrix} 0.6639\\ 0.6575 \end{smallmatrix}\bigr)](https://private.codecogs.com/gif.latex?%5Chat%7BY%7D%3Dsigmoid%28net_%7B2%7D%29%3Dsigmoid%5Cbigl%28%5Cbegin%7Bsmallmatrix%7D%200.6807%5C%5C%200.7341%5Cend%7Bsmallmatrix%7D%5Cbigr%29%3D%5Cbigl%28%5Cbegin%7Bsmallmatrix%7D%200.6639%5C%5C%200.6575%20%5Cend%7Bsmallmatrix%7D%5Cbigr%29)          (4-5)

​     损失函数：

​                           ![E(\theta )=\frac{1}{2}(Y-\hat{Y})^T(Y-\hat{Y})=\frac{1}{2}\bigl(\begin{smallmatrix} 0-0.6639\\ 1-0.6757 \end{smallmatrix}\bigr)=0.2796](https://private.codecogs.com/gif.latex?E%28%5Ctheta%20%29%3D%5Cfrac%7B1%7D%7B2%7D%28Y-%5Chat%7BY%7D%29%5ET%28Y-%5Chat%7BY%7D%29%3D%5Cfrac%7B1%7D%7B2%7D%5Cbigl%28%5Cbegin%7Bsmallmatrix%7D%200-0.6639%5C%5C%201-0.6757%20%5Cend%7Bsmallmatrix%7D%5Cbigr%29%3D0.2796)              (4-6)

 3）计算输出单元的误差项和隐藏单元的误差项

​    **输出单元的误差项：**根据公式(3-19)，将![Y,\hat{Y},net_{2},h](https://private.codecogs.com/gif.latex?Y%2C%5Chat%7BY%7D%2Cnet_%7B2%7D%2Ch)带入其中，得到需更新的梯度误差：

​                   ![\delta ^{(1)}=\hat{Y}\odot (1-\hat{Y})\odot (\hat{Y}-Y)=\begin{pmatrix} \hat{y}_{1}\\ \hat{y}_{2}\end{pmatrix}\odot \begin{pmatrix} 1-\hat{y}_{1}\\ 1-\hat{y}_{2}\end{pmatrix}\odot \begin{pmatrix} \hat{y}_{1}-y_{1}\\ \hat{y}_{2}-y_{2} \end{pmatrix}](https://private.codecogs.com/gif.latex?%5Cdelta%20%5E%7B%281%29%7D%3D%5Chat%7BY%7D%5Codot%20%281-%5Chat%7BY%7D%29%5Codot%20%28%5Chat%7BY%7D-Y%29%3D%5Cbegin%7Bpmatrix%7D%20%5Chat%7By%7D_%7B1%7D%5C%5C%20%5Chat%7By%7D_%7B2%7D%5Cend%7Bpmatrix%7D%5Codot%20%5Cbegin%7Bpmatrix%7D%201-%5Chat%7By%7D_%7B1%7D%5C%5C%201-%5Chat%7By%7D_%7B2%7D%5Cend%7Bpmatrix%7D%5Codot%20%5Cbegin%7Bpmatrix%7D%20%5Chat%7By%7D_%7B1%7D-y_%7B1%7D%5C%5C%20%5Chat%7By%7D_%7B2%7D-y_%7B2%7D%20%5Cend%7Bpmatrix%7D)      

​                       ![=\begin{pmatrix}0.6639\\0.6757 \end{pmatrix}\odot \begin{pmatrix}1-0.6639\\ 1-0.6757\end{pmatrix}\odot \begin{pmatrix}0.6639-0\\ 0.6757-1\end{pmatrix}=\begin{pmatrix} 0.14814\\ -0.07106 \end{pmatrix}](https://private.codecogs.com/gif.latex?%3D%5Cbegin%7Bpmatrix%7D0.6639%5C%5C0.6757%20%5Cend%7Bpmatrix%7D%5Codot%20%5Cbegin%7Bpmatrix%7D1-0.6639%5C%5C%201-0.6757%5Cend%7Bpmatrix%7D%5Codot%20%5Cbegin%7Bpmatrix%7D0.6639-0%5C%5C%200.6757-1%5Cend%7Bpmatrix%7D%3D%5Cbegin%7Bpmatrix%7D%200.14814%5C%5C%20-0.07106%20%5Cend%7Bpmatrix%7D)             

​                   ![\bigtriangledown _{1}v =h\cdot \delta ^{(1)}^T=\begin{pmatrix}0.5331\\ 0.5349\end{pmatrix}\cdot \begin{pmatrix}0.14814\\ -0.07106\end{pmatrix}^{T}=\begin{pmatrix}0.07897 &-0.03788 \\ 0.07924 &-0.03801 \end{pmatrix}](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B1%7Dv%20%3Dh%5Ccdot%20%5Cdelta%20%5E%7B%281%29%7D%5ET%3D%5Cbegin%7Bpmatrix%7D0.5331%5C%5C%200.5349%5Cend%7Bpmatrix%7D%5Ccdot%20%5Cbegin%7Bpmatrix%7D0.14814%5C%5C%20-0.07106%5Cend%7Bpmatrix%7D%5E%7BT%7D%3D%5Cbegin%7Bpmatrix%7D0.07897%20%26-0.03788%20%5C%5C%200.07924%20%26-0.03801%20%5Cend%7Bpmatrix%7D)

   如果对v中每一个元素求偏导，有：

​                          ![\bigtriangledown _{1}v_{11}=(\hat{y}_{1}-y_{1})(\hat{y}_{1}(1-\hat{y}_{1}))h_{1}=0.07897](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B1%7Dv_%7B11%7D%3D%28%5Chat%7By%7D_%7B1%7D-y_%7B1%7D%29%28%5Chat%7By%7D_%7B1%7D%281-%5Chat%7By%7D_%7B1%7D%29%29h_%7B1%7D%3D0.07897)

​                          ![\bigtriangledown _{1}v_{12}=(\hat{y}_{2}-y_{2})(\hat{y}_{2}(1-\hat{y}_{2}))h_{1}=-0.03788](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B1%7Dv_%7B12%7D%3D%28%5Chat%7By%7D_%7B2%7D-y_%7B2%7D%29%28%5Chat%7By%7D_%7B2%7D%281-%5Chat%7By%7D_%7B2%7D%29%29h_%7B1%7D%3D-0.03788)

​                          ![\bigtriangledown _{1}v_{21}=(\hat{y}_{1}-y_{1})(\hat{y}_{1}(1-\hat{y}_{1}))h_{2}=0.07924](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B1%7Dv_%7B21%7D%3D%28%5Chat%7By%7D_%7B1%7D-y_%7B1%7D%29%28%5Chat%7By%7D_%7B1%7D%281-%5Chat%7By%7D_%7B1%7D%29%29h_%7B2%7D%3D0.07924)

​                          ![\bigtriangledown _{1}v_{22}=(\hat{y}_{2}-y_{2})(\hat{y}_{2}(1-\hat{y}_{2}))h_{2}=-0.03801](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B1%7Dv_%7B22%7D%3D%28%5Chat%7By%7D_%7B2%7D-y_%7B2%7D%29%28%5Chat%7By%7D_%7B2%7D%281-%5Chat%7By%7D_%7B2%7D%29%29h_%7B2%7D%3D-0.03801)

​                               ![\bigtriangledown _{1}v=\begin{pmatrix} 0.07897 &-0.03788 \\ 0.07924&-0.03801 \end{pmatrix}](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B1%7Dv%3D%5Cbegin%7Bpmatrix%7D%200.07897%20%26-0.03788%20%5C%5C%200.07924%26-0.03801%20%5Cend%7Bpmatrix%7D)

  用公式(3-19)和对v中每一个元素求偏导，得到的结果一致。

  **隐藏单元的误差项**：根据公式(3-23)，将![\delta ^{(1)},net_{1},h,v,x](https://private.codecogs.com/gif.latex?%5Cdelta%20%5E%7B%281%29%7D%2Cnet_%7B1%7D%2Ch%2Cv%2Cx)带入其中，得到需更新的梯度误差

​                ![\bigtriangledown _{1}w=x\cdot (h\odot (1-h)\odot (v\cdot \delta ^{(1)}))^T](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B1%7Dw%3Dx%5Ccdot%20%28h%5Codot%20%281-h%29%5Codot%20%28v%5Ccdot%20%5Cdelta%20%5E%7B%281%29%7D%29%29%5ET)

​                    ![=\begin{pmatrix}x_{1}\\ x_{2}\end{pmatrix}\cdot\left ( \begin{pmatrix} h_{1}\\h_{2} \end{pmatrix}\odot \begin{pmatrix}1-h_{1}\\1-h_{2} \end{pmatrix} \odot \left ( \begin{pmatrix}v_{11} &v_{12} \\ v_{21} &v_{22} \end{pmatrix}\cdot \delta ^{(1)} \right )\right )^T](https://private.codecogs.com/gif.latex?%3D%5Cbegin%7Bpmatrix%7Dx_%7B1%7D%5C%5C%20x_%7B2%7D%5Cend%7Bpmatrix%7D%5Ccdot%5Cleft%20%28%20%5Cbegin%7Bpmatrix%7D%20h_%7B1%7D%5C%5Ch_%7B2%7D%20%5Cend%7Bpmatrix%7D%5Codot%20%5Cbegin%7Bpmatrix%7D1-h_%7B1%7D%5C%5C1-h_%7B2%7D%20%5Cend%7Bpmatrix%7D%20%5Codot%20%5Cleft%20%28%20%5Cbegin%7Bpmatrix%7Dv_%7B11%7D%20%26v_%7B12%7D%20%5C%5C%20v_%7B21%7D%20%26v_%7B22%7D%20%5Cend%7Bpmatrix%7D%5Ccdot%20%5Cdelta%20%5E%7B%281%29%7D%20%5Cright%20%29%5Cright%20%29%5ET)

​                    ![=\begin{pmatrix}0.05\\ 0.10\end{pmatrix}\cdot\left ( \begin{pmatrix} 0.5331\\0.5349 \end{pmatrix}\odot \begin{pmatrix}1-0.5331\\1-0.5349 \end{pmatrix} \odot \left ( \begin{pmatrix}0.40 &0.45 \\ 0.50 &0.55\end{pmatrix}\cdot\begin{pmatrix}0.14814\\-0.007106 \end{pmatrix} \right )\right )^T](https://private.codecogs.com/gif.latex?%3D%5Cbegin%7Bpmatrix%7D0.05%5C%5C%200.10%5Cend%7Bpmatrix%7D%5Ccdot%5Cleft%20%28%20%5Cbegin%7Bpmatrix%7D%200.5331%5C%5C0.5349%20%5Cend%7Bpmatrix%7D%5Codot%20%5Cbegin%7Bpmatrix%7D1-0.5331%5C%5C1-0.5349%20%5Cend%7Bpmatrix%7D%20%5Codot%20%5Cleft%20%28%20%5Cbegin%7Bpmatrix%7D0.40%20%260.45%20%5C%5C%200.50%20%260.55%5Cend%7Bpmatrix%7D%5Ccdot%5Cbegin%7Bpmatrix%7D0.14814%5C%5C-0.007106%20%5Cend%7Bpmatrix%7D%20%5Cright%20%29%5Cright%20%29%5ET)

​                    ![=\begin{pmatrix}0.05\\0.10 \end{pmatrix}\cdot \begin{pmatrix}0.02728\\0.03499 \end{pmatrix}^T=\begin{pmatrix} 1.364\times 10^{-3} & 1.750\times 10^{-3}\\ 2.728\times 10^{-3}&3.500\times 10^{-3} \end{pmatrix}](https://private.codecogs.com/gif.latex?%3D%5Cbegin%7Bpmatrix%7D0.05%5C%5C0.10%20%5Cend%7Bpmatrix%7D%5Ccdot%20%5Cbegin%7Bpmatrix%7D0.02728%5C%5C0.03499%20%5Cend%7Bpmatrix%7D%5ET%3D%5Cbegin%7Bpmatrix%7D%201.364%5Ctimes%2010%5E%7B-3%7D%20%26%201.750%5Ctimes%2010%5E%7B-3%7D%5C%5C%202.728%5Ctimes%2010%5E%7B-3%7D%263.500%5Ctimes%2010%5E%7B-3%7D%20%5Cend%7Bpmatrix%7D)

​    若对w中每一个元素求偏导，有：

​                   ![\bigtriangledown _{1}w_{11}=x_{1}(h_{1}(1-h_{1})v_{11}\delta _{1}^{(1)}+h_{1}(1-h_{1})v_{12}\delta _{2}^{(1)})=1.364\times 10^{-3}](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B1%7Dw_%7B11%7D%3Dx_%7B1%7D%28h_%7B1%7D%281-h_%7B1%7D%29v_%7B11%7D%5Cdelta%20_%7B1%7D%5E%7B%281%29%7D&plus;h_%7B1%7D%281-h_%7B1%7D%29v_%7B12%7D%5Cdelta%20_%7B2%7D%5E%7B%281%29%7D%29%3D1.364%5Ctimes%2010%5E%7B-3%7D)

​                   ![\bigtriangledown _{1}w_{12}=x_{1}(h_{2}(1-h_{2})v_{21}\delta _{1}^{(1)}+h_{2}(1-h_{2})v_{22}\delta _{2}^{(1)})=1.750\times 10^{-3}](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B1%7Dw_%7B12%7D%3Dx_%7B1%7D%28h_%7B2%7D%281-h_%7B2%7D%29v_%7B21%7D%5Cdelta%20_%7B1%7D%5E%7B%281%29%7D&plus;h_%7B2%7D%281-h_%7B2%7D%29v_%7B22%7D%5Cdelta%20_%7B2%7D%5E%7B%281%29%7D%29%3D1.750%5Ctimes%2010%5E%7B-3%7D)

​                   ![\bigtriangledown _{1}w_{21}=x_{2}(h_{1}(1-h_{1})v_{11}\delta _{1}^{(1)}+h_{1}(1-h_{1})v_{12}\delta _{2}^{(1)})=2.728\times 10^{-3}](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B1%7Dw_%7B21%7D%3Dx_%7B2%7D%28h_%7B1%7D%281-h_%7B1%7D%29v_%7B11%7D%5Cdelta%20_%7B1%7D%5E%7B%281%29%7D&plus;h_%7B1%7D%281-h_%7B1%7D%29v_%7B12%7D%5Cdelta%20_%7B2%7D%5E%7B%281%29%7D%29%3D2.728%5Ctimes%2010%5E%7B-3%7D)

​                   ![\bigtriangledown _{1}w_{22}=x_{2}(h_{2}(1-h_{2})v_{21}\delta _{1}^{(1)}+h_{2}(1-h_{2})v_{22}\delta _{2}^{(1)})=3.500\times 10^{-3}](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B1%7Dw_%7B22%7D%3Dx_%7B2%7D%28h_%7B2%7D%281-h_%7B2%7D%29v_%7B21%7D%5Cdelta%20_%7B1%7D%5E%7B%281%29%7D&plus;h_%7B2%7D%281-h_%7B2%7D%29v_%7B22%7D%5Cdelta%20_%7B2%7D%5E%7B%281%29%7D%29%3D3.500%5Ctimes%2010%5E%7B-3%7D)

​                      ![\bigtriangledown _{1}w=\begin{pmatrix} \bigtriangledown _{1}w_{11}& \bigtriangledown _{1}w_{12} \\ \bigtriangledown _{1}w_{21}& \bigtriangledown _{1}w_{22} \end{pmatrix}=\begin{pmatrix} 1.364\times 10^{-3} &1.750\times 10^{-3} \\ 2.728\times 10^{-3}&3.500\times 10^{-3} \end{pmatrix}](https://private.codecogs.com/gif.latex?%5Cbigtriangledown%20_%7B1%7Dw%3D%5Cbegin%7Bpmatrix%7D%20%5Cbigtriangledown%20_%7B1%7Dw_%7B11%7D%26%20%5Cbigtriangledown%20_%7B1%7Dw_%7B12%7D%20%5C%5C%20%5Cbigtriangledown%20_%7B1%7Dw_%7B21%7D%26%20%5Cbigtriangledown%20_%7B1%7Dw_%7B22%7D%20%5Cend%7Bpmatrix%7D%3D%5Cbegin%7Bpmatrix%7D%201.364%5Ctimes%2010%5E%7B-3%7D%20%261.750%5Ctimes%2010%5E%7B-3%7D%20%5C%5C%202.728%5Ctimes%2010%5E%7B-3%7D%263.500%5Ctimes%2010%5E%7B-3%7D%20%5Cend%7Bpmatrix%7D)

​    用公式(3-23)和对v中每一个元素求偏导，得到的结果一致。

 **注意：**一般情况下，不会对偏置项更新

 4）更新神经网络中的权值

​             ![v^{(1)}=v^{(0)}-\eta \ast \bigtriangledown _{1}v=\begin{pmatrix}0.40 &0.45 \\ 0.50 &0.55 \end{pmatrix}-0.5\ast \begin{pmatrix}0.07897 &-0.03788 \\ 0.07924 &-0.03801 \end{pmatrix}](https://private.codecogs.com/gif.latex?v%5E%7B%281%29%7D%3Dv%5E%7B%280%29%7D-%5Ceta%20%5Cast%20%5Cbigtriangledown%20_%7B1%7Dv%3D%5Cbegin%7Bpmatrix%7D0.40%20%260.45%20%5C%5C%200.50%20%260.55%20%5Cend%7Bpmatrix%7D-0.5%5Cast%20%5Cbegin%7Bpmatrix%7D0.07897%20%26-0.03788%20%5C%5C%200.07924%20%26-0.03801%20%5Cend%7Bpmatrix%7D)

​                 ![=\begin{pmatrix}0.36051 &0.46894 \\ 0.46038 &0.56901 \end{pmatrix}](https://private.codecogs.com/gif.latex?%3D%5Cbegin%7Bpmatrix%7D0.36051%20%260.46894%20%5C%5C%200.46038%20%260.56901%20%5Cend%7Bpmatrix%7D)

​            ![w^{(1)}=w^{(0)}-\eta \ast \bigtriangledown _{1}w=\begin{pmatrix}0.15 &0.20\\ 0.25 &0.30 \end{pmatrix}-0.5\ast \begin{pmatrix}1.364\times 10^{-3} &1.750\times 10^{-3} \\ 2.728\times 10^{-3} &3.500\times 10^{-3} \end{pmatrix}](https://private.codecogs.com/gif.latex?w%5E%7B%281%29%7D%3Dw%5E%7B%280%29%7D-%5Ceta%20%5Cast%20%5Cbigtriangledown%20_%7B1%7Dw%3D%5Cbegin%7Bpmatrix%7D0.15%20%260.20%5C%5C%200.25%20%260.30%20%5Cend%7Bpmatrix%7D-0.5%5Cast%20%5Cbegin%7Bpmatrix%7D1.364%5Ctimes%2010%5E%7B-3%7D%20%261.750%5Ctimes%2010%5E%7B-3%7D%20%5C%5C%202.728%5Ctimes%2010%5E%7B-3%7D%20%263.500%5Ctimes%2010%5E%7B-3%7D%20%5Cend%7Bpmatrix%7D)

​                 ![=\begin{pmatrix}0.14983 &0.19978 \\ 0.24966 &0.29956 \end{pmatrix}](https://private.codecogs.com/gif.latex?%3D%5Cbegin%7Bpmatrix%7D0.14983%20%260.19978%20%5C%5C%200.24966%20%260.29956%20%5Cend%7Bpmatrix%7D) 

   于是，得到第一次更新的参数值w,v。

 5）重复步骤2-4，直到损失值达到了预先设定的阈值或迭代次数用完，得到最终的权值。

​    以上即为BP算法的更新权值的过程，下面将上述实例的推导过程用代码实现：

### **2.5 实例编程实现(运行环境python3)**

   根据BP算法的步骤，将上述例子对应的代码写出如下：

```python
# encoding:utf-8
# ********* 导入相应的模块***********
import math
import numpy as np
from numpy import *
 
#**********设定模型所需的激活函数，运行此代码时，带'*'部分请删除*********
# 激活函数
def sigmoids(z):
    a = []
    for each in z:
        b = 1/(1+math.exp(-each[0]))
        a.append(b)
    return a
 
**********设定前向传播过程，即模型的设定部分，此处均根据模型第3部分的模型设定部分的公式编写对应的代码*********
 
# 前向传播,返回预测值
def forwordmd(X,W,V,B1,B2):
    net1 = W.T*X+B1
    H = matrix(sigmoids(np.array(net1))).T # 隐藏层单元
    net2 = V.T*H+B2
    pred_y = matrix(sigmoids(np.array(net2))).T # 预测值
    return pred_y,H,net1,net2
 
#**********设定模型反向传播，按照步骤4的公式编辑*********
# 反向传播,更新权重
def Bpaugorith(Y,pred_y,H,V,aph,W):
    Errorterm = 0.5*(Y-pred_y).T*(Y-pred_y)# 给出误差公式
    # 计算输出单元的误差项
    a1 = multiply(pred_y-Y,pred_y) # 矩阵对应元素相乘,即逐元素相乘
    a2 = multiply(a1,1-pred_y)
    Verror = H*a2.T
    # 计算隐藏单元的误差项
    Werror = X*(multiply(multiply(H,1-H),(V*a2))).T
    # 更新权重
    Vupdate = V - aph*Verror
    Wupdate = W - aph*Werror
    return Vupdate,Wupdate,Errorter
 
#**********主程序部分，此处设定了步骤1中的参数初始化和输入值及输出值的真实值，及步骤5中设置迭代次数和设置阈值停止迭代的代码*********
 
if __name__ =='__main__':
    X = matrix([0.05,0.10]).T
    Y = matrix([0.01,0.99]).T
    # 给出初始权重
    W = matrix([[0.15,0.20],[0.25,0.30]])
    B1 = matrix([0.1,0.1]).T
    V = matrix([[0.40,0.45],[0.50,0.55]])
    B2 = matrix([0.2,0.2]).T
 
    #***********初始权重亦可随机生成***********
    # 随机生成参数
    # np.random.seed(0)
    # W = matrix(np.random.normal(0,1,[2,2]))
    # B1 = matrix(np.random.normal(0, 1, [1, 2]))
    # V = matrix(np.random.normal(0, 1, [2, 2]))
    # B2 = matrix(np.random.normal(0, 1, [1, 2]))
    #***********随机生成参数部分，若有自己设定，将此部分注释*********
    aph = 0.5 # 学习率
    #*********从此处为迭代次数设置部分***********
    # 迭代10次
    n = 10 # 迭代次数
    for i in range(n):
        # 激活前向算法
        pred_y, H,net1,net2 = forwordmd(X,W,V,B1,B2)  # 得到预测值和隐藏层值
        # 更新权重
        Vupdate, Wupdate,Errorvalue = Bpaugorith(Y,pred_y,H,V,net1,net2,aph,W)  # 得到更新的权重
        W,V = Wupdate,Vupdate
    print ('损失函数e：%.2f'%e)
    print ('预测值：')
    print (pred_y)
    print ('更新的权重V：')
    print (Vupdate)
    print ('更新的权重W:')
    print (Wupdate)
    print ('损失值：')
    print (Errorvalue)
 
    # 阈值E，可根据需要自行更改，若需要运行此部分，请将迭代次数部分注释后运行
    # 阈值E
    # e,m = 0.19,1
    # pred_y, H, net1, net2 = forwordmd(X,W,V,B1,B2)  # 得到预测值和隐藏层值
    # 更新权重
    # Vupdate, Wupdate, Errorvalue = Bpaugorith(Y,pred_y,H,V,net1,net2,aph,W)  # 得到更新的权重
    # W,V = Wupdate,Vupdate
    # while Errorvalue>e:
        # 激活前向算法
        # pred_y, H, net1, net2 = forwordmd(X,W,V,B1,B2)  # 得到预测值和隐藏层值
        # 更新权重
        # Vupdate, Wupdate, Errorvalue = Bpaugorith(Y,pred_y,H,V,net1,net2,aph,W)  # 得到更新的权重
        # W, V = Wupdate, Vupdate
        # m = m+1
    # print ('迭代次数：%d'%n)
    # print ('更新权重:%d次'% m)
    # print ('预测值：')
    # print (pred_y)
    # print ('更新的权重V：')
    # print (Vupdate)
    # print ('更新的权重W:')
    # print (Wupdate)
    # print ('损失值：')
    # print (Errorvalue)
​
 
    #*********阈值设置部分结束***********
 
​


```



以上部分为本例中的代码部分。设定了激活函数，前向传播(即模型的设定)及反向传播过程，步骤5中有阈值设定和迭代步数，这一部分的程序如主程序中。前向传播部分和反向传播部分，以上内容均根据推导的公式一句句编写出来的。感兴趣的朋友可以自己尝试编写这部分程序。

[代码链接](https://gitee.com/someone317/backpropagation_algorithm_test/blob/master/BPtest1.py)

### **2.6 BP算法缺陷与改进**

#### 2.6.1  **BP算法缺陷：**

1）局部极小值

对于多层网络，误差曲面可能含有多个不同的局部极小值，梯度下降可能导致陷入局部极小值。

2）权值过多

当隐藏节点过多，层数越多时，权值成倍增长。权值的增长意味着对应的空间维数的增加，过高的维数易导致训练后期的过拟合。

3）容易过拟合

训练的次数过多、空间维数过高均容易过拟合。

#### 2.6.2 **BP算法改进：**

 1）利用动量法改进BP算法

动量法权值调整算法的具体做法是：将上一次权值调整量的一部分迭加到按本次误差计算所得的权值调整量上，作为本次的实际权值调整量，即：

​                               ![w^{(k)}=\beta w^{(k-1)}-\eta \bigtriangledown _{k}w](https://private.codecogs.com/gif.latex?w%5E%7B%28k%29%7D%3D%5Cbeta%20w%5E%7B%28k-1%29%7D-%5Ceta%20%5Cbigtriangledown%20_%7Bk%7Dw)

其中，![\beta](https://private.codecogs.com/gif.latex?%5Cbeta)表示动量系数，![\eta](https://private.codecogs.com/gif.latex?%5Ceta)表示学习率。

 

2）自适应调整学习率

 **调整的基本指导思想**是：在学习收敛的情况下，增大![\eta](https://private.codecogs.com/gif.latex?%5Ceta)以缩短学习时间；当![\eta](https://private.codecogs.com/gif.latex?%5Ceta)偏大致使不能收敛时，要及时减小它的值，知道收敛为止。此方法适用于设置阈值的情况下。

 

3）动量-自适应学习速率调整算法

 采用动量法，BP算法可以找到更优的解；采用自适应学习速率法时，BP算法可以缩短训练时间。将以上两种方法结合起来，就得到动量-自适应学习率调整算法。

上述2）和3）都适应于设置阈值来停止程序的方法。
