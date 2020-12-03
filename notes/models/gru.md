# 详解RNN、LSTM、GRU

 2020-06-02 [原文](https://www.codenong.com/cs106474456/)

----

**写在前面**

本博客会分三大部分：
1.RNN详解，这块会介绍到双向RNN,也会简单提一下深度RNN模型
2.LSTM内部结构详解
3.GRU单元详解

### 文章目录

- 写在前面

- \1. RNN详解

- - 1.1符号解释：考虑St结点，t代表t时刻，St就代表t时刻记忆单元的值，St-1，St，St+1构成一个记忆单元，整体叫做循环核
  - 1.2 RNN的计算过程
  - 1.3 双向循环网络(BRNN)
  - 1.4 深度双向循环网络

- \2. LSTM详解

- - 2.1 为什么要有LSTM(等价与问RNN中的缺陷)
  - 2.2 LSTM内部原理(Long Short-Term Memory)
  - 2.3 GRU(Gate Recurrent Units)

- \3. 总结

- \4. 参考文献

---



## **1. RNN详解**

![在这里插入图片描述](imgs/rnn/1211.png)

首先要说明一点：图中所有的W相等，所有的U相等，所有的V相等，即RNN实现**参数共享**。

### 1.1符号解释

考虑St结点，t代表t时刻，St就代表t时刻记忆单元的值，St-1，St，St+1构成一个记忆单元，整体叫做循环核

①W权重矩阵：指的是上一个隐藏结点的值St-1所需要乘的参数矩阵，它会对St的值贡献一部分
②U权重矩阵：Xt所需要成的参数矩阵，它也会对St的值贡献一部分。
(TIPS:等于说St的值由两部分组成)
③V权重矩阵：St所需要的参数矩阵，矩阵点乘的结果就是t时刻的输出Ot



从图中可以看出，RNN其实就是比全连接层多了一个参数权重W

### 1.2 RNN的计算过程

![在这里插入图片描述](imgs/rnn/324.png)

- **在前向传播时，记忆体内的存储的状态信息St在每一时刻都会被刷新，最后输出Ot+1，每个记忆体中记忆单元的个数根据需求选取。例如用四个单词预测一个，就选取4个记忆单元作为一个循环核的记忆体。**

### 1.3 双向循环网络(BRNN)

![在这里插入图片描述](imgs/rnn/adsfs.png)

![在这里插入图片描述](imgs/rnn/acvvx.png)

### 1.4 深度双向循环网络

![在这里插入图片描述](imgs/rnn/asdfxzc.png)
![在这里插入图片描述](https://i2.wp.com/img-blog.csdnimg.cn/20200601163413963.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NDQ0MTEzMQ==,size_16,color_FFFFFF,t_70)

## **2. LSTM详解**

### 2.1 为什么要有LSTM(等价与问RNN中的缺陷)

**RNN中会存在梯度消失问题**，当然也存在梯度爆炸问题，梯度爆炸可以通过**梯度剪裁或者降低学习率来解决**，而梯度消失则很难解决。

吴恩达教授讲了一个例子很生动，这里贴出来：

The cat,which already ate… … …(很多食物)，was full

The cats ,which already ate… … …(很多食物)，were full

我们如何捕捉到cat单复数的问题，这需要在was/were这里获取到cat/cats的信息，然后我们都知道深度网络模型中都存在梯度消失问题，这是我们丢失了以前的信息。我们称这种现象也叫“短期依赖”。

- 下面是梯度消失导致的现象，参数几乎不再更新。
  ![在这里插入图片描述](imgs/rnn/csfadf.png)

### 2.2 LSTM内部原理(Long Short-Term Memory)

LSTM 和 GRU 是解决短时记忆问题的解决方案，它们具有称为“门”的内部机制，可以调节信息流。

![在这里插入图片描述](imgs/rnn/asdfsad.png)

这些“门”可以知道序列中哪些重要的数据是需要保留，而哪些是要删除的。 随后，它可以沿着长链序列传递相关信息以进行预测，几乎所有基于递归神经网络的技术成果都是通过这两个网络实现的。

LSTM 和 GRU 可以在语音识别、语音合成和文本生成中找到，你甚至可以用它们为视频生成字幕。对 LSTM 和 GRU 擅长处理长序列的原因，到这篇文章结束时你应该会有充分了解。



LSTM 的控制流程与 RNN 相似，它们都是在前向传播的过程中处理流经细胞的数据，不同之处在于 LSTM 中细胞的结构和运算有所变化。
![在这里插入图片描述](imgs/rnn/asdxcv.png)

这一系列运算操作使得 LSTM具有能选择保存信息或遗忘信息的功能。咋一看这些运算操作时可能有点复杂，但没关系下面将带你一步步了解这些运算操作。
![在这里插入图片描述](imgs/rnn/cxvsadf.png)
![在这里插入图片描述](imgs/rnn/jdhfdg.png)
![在这里插入图片描述](imgs/rnn/sdvasv.png)
接下来了解一下门结构的功能。LSTM 有三种类型的门结构：遗忘门、输入门和输出门。
![在这里插入图片描述](imgs/rnn/xzcvzx.png)
![在这里插入图片描述](imgs/rnn/sfvn.png)
![在这里插入图片描述](imgs/rnn/xczvx.png)
![在这里插入图片描述](imgs/rnn/fvvsadf.png)
![在这里插入图片描述](imgs/rnn/vada.png)
![在这里插入图片描述](imgs/rnn/bfdbfds.png)
![在这里插入图片描述](imgs/rnn/fbgfhsds.png)
**让我们再梳理一下。遗忘门确定前一个步长中哪些相关的信息需要被保留；输入门确定当前输入中哪些信息是重要的，需要被添加的；输出门确定下一个隐藏状态应该是什么。**

![在这里插入图片描述](https://i2.wp.com/img-blog.csdnimg.cn/20200601165458696.png)
![在这里插入图片描述](imgs/rnn/asdfzxcv.png)
![在这里插入图片描述](imgs/rnn/vcbgsfjhf.png)

### 2.3 GRU(Gate Recurrent Units)

知道了 LSTM 的工作原理之后，来了解一下 GRU。GRU 是新一代的循环神经网络，与 LSTM 非常相似。与 LSTM 相比，GRU 去除掉了细胞状态，使用隐藏状态来进行信息的传递。它只包含两个门：更新门和重置门。



![在这里插入图片描述](imgs/rnn/cdfga.png)

![在这里插入图片描述](imgs/rnn/bdfshsd.png)

- 相比于RNN，我们只是中间隐藏层的结构发生了变化。
  ![在这里插入图片描述](imgs/rnn/fdsg.png)

  

- σ为sigmoid函数，通过这个函数可以将数据变换为0-1范围内的数值，从而来充当门控信号
  ![在这里插入图片描述](imgs/rnn/bdsfg.png)
  ![在这里插入图片描述](imgs/rnn/gfh.png)
  ![在这里插入图片描述](imgs/rnn/bsdf.png)
  ![在这里插入图片描述](imgs/rnn/bgshs.png)
  ![在这里插入图片描述](imgs/rnn/shds.png)

## **3. 总结**

GRU输入输出的结构与普通的RNN相似，其中的内部思想与LSTM相似。

与LSTM相比，GRU内部少了一个”门控“，参数比LSTM少，但是却也能够达到与LSTM相当的功能。考虑到硬件的计算能力和时间成本，因而很多时候我们也就会选择更加”实用“的GRU啦。