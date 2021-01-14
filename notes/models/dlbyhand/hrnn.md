# 零基础入门深度学习(5) - 循环神经网络

2021年1月14日

---

## 0. 往期回顾

在前面的文章系列文章中，我们介绍了全连接神经网络和卷积神经网络，以及它们的训练和使用。他们都只能单独的去处理一个个的输入，前一个输入和后一个输入是完全没有关系的。但是，某些任务需要能够更好的处理**序列**的信息，即前面的输入和后面的输入是有关系的。比如，当我们在理解一句话意思时，孤立的理解这句话的每个词是不够的，我们需要处理这些词连接起来的整个**序列**；当我们处理视频的时候，我们也不能只单独的去分析每一帧，而要分析这些帧连接起来的整个**序列**。这时，就需要用到深度学习领域中另一类非常重要神经网络：**循环神经网络(Recurrent Neural Network)**。RNN种类很多，也比较绕脑子。不过读者不用担心，本文将一如既往的对复杂的东西剥茧抽丝，帮助您理解RNNs以及它的训练算法，并动手实现一个**循环神经网络**。

## 1. 语言模型

RNN是在**自然语言处理**领域中最先被用起来的，比如，RNN可以为**语言模型**来建模。那么，什么是语言模型呢？

我们可以和电脑玩一个游戏，我们写出一个句子前面的一些词，然后，让电脑帮我们写下接下来的一个词。比如下面这句：

> 我昨天上学迟到了，老师批评了____。

我们给电脑展示了这句话前面这些词，然后，让电脑写下接下来的一个词。在这个例子中，接下来的这个词最有可能是『我』，而不太可能是『小明』，甚至是『吃饭』。

**语言模型**就是这样的东西：给定一个一句话前面的部分，预测接下来最有可能的一个词是什么。

**语言模型**是对一种语言的特征进行建模，它有很多很多用处。比如在语音转文本(STT)的应用中，声学模型输出的结果，往往是若干个可能的候选词，这时候就需要**语言模型**来从这些候选词中选择一个最可能的。当然，它同样也可以用在图像到文本的识别中(OCR)。

使用RNN之前，语言模型主要是采用N-Gram。N可以是一个自然数，比如2或者3。它的含义是，假设一个词出现的概率只与前面N个词相关。我们以2-Gram为例。首先，对前面的一句话进行切词：

> 我 昨天 上学 迟到 了 ，老师 批评 了 ____。

如果用2-Gram进行建模，那么电脑在预测的时候，只会看到前面的『了』，然后，电脑会在语料库中，搜索『了』后面最可能的一个词。不管最后电脑选的是不是『我』，我们都知道这个模型是不靠谱的，因为『了』前面说了那么一大堆实际上是没有用到的。如果是3-Gram模型呢，会搜索『批评了』后面最可能的词，感觉上比2-Gram靠谱了不少，但还是远远不够的。因为这句话最关键的信息『我』，远在9个词之前！

现在读者可能会想，可以提升继续提升N的值呀，比如4-Gram、5-Gram.......。实际上，这个想法是没有实用性的。因为我们想处理任意长度的句子，N设为多少都不合适；另外，模型的大小和N的关系是指数级的，4-Gram模型就会占用海量的存储空间。

所以，该轮到RNN出场了，RNN理论上可以往前看(往后看)任意多个词。

## 2. 循环神经网络是啥

循环神经网络种类繁多，我们先从最简单的基本循环神经网络开始吧。

### 2.1 基本循环神经网络

下图是一个简单的循环神经网络如，它由输入层、一个隐藏层和一个输出层组成：

![img](imgs/2256672-479f2a7488b91671.png)

纳尼？！相信第一次看到这个玩意的读者内心和我一样是崩溃的。因为**循环神经网络**实在是太难画出来了，网上所有大神们都不得不用了这种抽象艺术手法。不过，静下心来仔细看看的话，其实也是很好理解的。如果把上面有W的那个带箭头的圈去掉，它就变成了最普通的**全连接神经网络**。x是一个向量，它表示**输入层**的值（这里面没有画出来表示神经元节点的圆圈）；s是一个向量，它表示**隐藏层**的值（这里隐藏层面画了一个节点，你也可以想象这一层其实是多个节点，节点数与向量s的维度相同）；U是输入层到隐藏层的**权重矩阵**（读者可以回到第三篇文章[零基础入门深度学习(3) - 神经网络和反向传播算法](https://www.zybuluo.com/hanbingtao/note/476663)，看看我们是怎样用矩阵来表示**全连接神经网络**的计算的）；o也是一个向量，它表示**输出层**的值；V是隐藏层到输出层的**权重矩阵**。那么，现在我们来看看W是什么。**循环神经网络**的**隐藏层**的值s不仅仅取决于当前这次的输入x，还取决于上一次**隐藏层**的值s。**权重矩阵** W就是**隐藏层**上一次的值作为这一次的输入的权重。

如果我们把上面的图展开，**循环神经网络**也可以画成下面这个样子：

![img](imgs/2256672-cf18bb1f06e750a4.png)

![](imgs/rr1.png)

### 2.2 双向循环神经网络

对于**语言模型**来说，很多时候光看前面的词是不够的，比如下面这句话：

> 我的手机坏了，我打算____一部新手机。

可以想象，如果我们只看横线前面的词，手机坏了，那么我是打算修一修？换一部新的？还是大哭一场？这些都是无法确定的。但如果我们也看到了横线后面的词是『一部新手机』，那么，横线上的词填『买』的概率就大得多了。

在上一小节中的**基本循环神经网络**是无法对此进行建模的，因此，我们需要**双向循环神经网络**，如下图所示：

![img](imgs/2256672-039a45251aa5d220.png)



![](imgs/rr2.png)



### 2.3 深度循环神经网络

前面我们介绍的**循环神经网络**只有一个隐藏层，我们当然也可以堆叠两个以上的隐藏层，这样就得到了**深度循环神经网络**。如下图所示：

![img](imgs/4801.png)

![](imgs/rr3.png)







## 3. 循环神经网络的训练

### 3.1 循环神经网络的训练算法：BPTT

![](imgs/rr4.png)

#### 前向计算

![](imgs/rr5.png)

#### 误差项的计算

![](imgs/rr6.png)

![](imgs/rr7.png)

![](imgs/rr8.png)

**循环层**将**误差项**反向传递到上一层网络，与普通的**全连接层**是完全一样的，这在前面的文章[零基础入门深度学习(3) - 神经网络和反向传播算法](https://www.zybuluo.com/hanbingtao/note/476663)中已经详细讲过了，在此仅简要描述一下。

![](imgs/rr9.png)



#### 权重梯度的计算

![](imgs/rr10.png)



回忆一下我们在文章[零基础入门深度学习(3) - 神经网络和反向传播算法](https://www.zybuluo.com/hanbingtao/note/476663)介绍的全连接网络的权重梯度计算算法：只要知道了任意一个时刻的**误差项**，以及上一个时刻循环层的输出值，就可以按照下面的公式求出权重矩阵在t时刻的梯度：

![](imgs/rr11.png)

![](imgs/rr12.png)

![](imgs/rr13.png)

![](imgs/rr14.png)

![](imgs/rr15.png)

![](imgs/rr16.png)

![](imgs/rr17.png)



### 3.2 RNN的梯度爆炸和消失问题

![](imgs/rr18.png)

## 4. RNN的应用举例——基于RNN的语言模型

现在，我们介绍一下基于RNN语言模型。我们首先把词依次输入到循环神经网络中，每输入一个词，循环神经网络就输出截止到目前为止，下一个最可能的词。例如，当我们依次输入：

> 我 昨天 上学 迟到 了

神经网络的输出如下图所示：

![img](imgs/480a.png)

其中，s和e是两个特殊的词，分别表示一个序列的开始和结束。

### 4.1 向量化

![](imgs/rr20.png)

![](imgs/rr21.png)



### 4.2 Softmax层

![](imgs/rr22.png)

![](imgs/rr23.png)



### 4.3 语言模型的训练

可以使用**监督学习**的方法对语言模型进行训练，首先，需要准备训练数据集。接下来，我们介绍怎样把语料

> 我 昨天 上学 迟到 了

转换成语言模型的训练数据集。

首先，我们获取**输入-标签**对：

| 输入 | 标签 |
| :--: | :--: |
|  s   |  我  |
|  我  | 昨天 |
| 昨天 | 上学 |
| 上学 | 迟到 |
| 迟到 |  了  |
|  了  |  e   |

然后，使用前面介绍过的**向量化**方法，对输入x和标签y进行**向量化**。这里面有意思的是，对标签y进行向量化，其结果也是一个one-hot向量。例如，我们对标签『我』进行向量化，得到的向量中，只有第2019个元素的值是1，其他位置的元素的值都是0。它的含义就是下一个词是『我』的概率是1，是其它词的概率都是0。

最后，我们使用**交叉熵误差函数**作为优化目标，对模型进行优化。

在实际工程中，我们可以使用大量的语料来对模型进行训练，获取训练数据和训练的方法都是相同的。

### 4.4 交叉熵误差

![](imgs/rr24.png)

我们当然可以选择其他函数作为我们的误差函数，比如最小平方误差函数(MSE)。不过对概率进行建模时，选择交叉熵误差函数更make sense。具体原因，感兴趣的读者请阅读[参考文献7](https://jamesmccaffrey.wordpress.com/2011/12/17/neural-network-classification-categorical-data-softmax-activation-and-cross-entropy-error/)。

## 5. RNN的实现

> 完整代码请参考GitHub: https://github.com/hanbt/learn_dl/blob/master/rnn.py (python2.7)

为了加深我们对前面介绍的知识的理解，我们来动手实现一个RNN层。我们复用了上一篇文章[零基础入门深度学习(4) - 卷积神经网络](https://www.zybuluo.com/hanbingtao/note/485480)中的一些代码，所以先把它们导入进来。

```
import numpy as npfrom cnn import ReluActivator, IdentityActivator, element_wise_op
```

我们用RecurrentLayer类来实现一个**循环层**。下面的代码是初始化一个循环层，可以在构造函数中设置卷积层的超参数。我们注意到，循环层有两个权重数组，U和W。

```
class RecurrentLayer(object):    def __init__(self, input_width, state_width,                 activator, learning_rate):        self.input_width = input_width        self.state_width = state_width        self.activator = activator        self.learning_rate = learning_rate        self.times = 0       # 当前时刻初始化为t0        self.state_list = [] # 保存各个时刻的state        self.state_list.append(np.zeros(            (state_width, 1)))           # 初始化s0        self.U = np.random.uniform(-1e-4, 1e-4,            (state_width, input_width))  # 初始化U        self.W = np.random.uniform(-1e-4, 1e-4,            (state_width, state_width))  # 初始化W
```

在forward方法中，实现循环层的前向计算，这部分比较简单。

```
    def forward(self, input_array):        '''        根据『式2』进行前向计算        '''        self.times += 1        state = (np.dot(self.U, input_array) +                 np.dot(self.W, self.state_list[-1]))        element_wise_op(state, self.activator.forward)        self.state_list.append(state)
```

在backword方法中，实现BPTT算法。

```
    def backward(self, sensitivity_array,                  activator):        '''        实现BPTT算法        '''        self.calc_delta(sensitivity_array, activator)        self.calc_gradient()    def calc_delta(self, sensitivity_array, activator):        self.delta_list = []  # 用来保存各个时刻的误差项        for i in range(self.times):            self.delta_list.append(np.zeros(                (self.state_width, 1)))        self.delta_list.append(sensitivity_array)        # 迭代计算每个时刻的误差项        for k in range(self.times - 1, 0, -1):            self.calc_delta_k(k, activator)    def calc_delta_k(self, k, activator):        '''        根据k+1时刻的delta计算k时刻的delta        '''        state = self.state_list[k+1].copy()        element_wise_op(self.state_list[k+1],                    activator.backward)        self.delta_list[k] = np.dot(            np.dot(self.delta_list[k+1].T, self.W),            np.diag(state[:,0])).T    def calc_gradient(self):        self.gradient_list = [] # 保存各个时刻的权重梯度        for t in range(self.times + 1):            self.gradient_list.append(np.zeros(                (self.state_width, self.state_width)))        for t in range(self.times, 0, -1):            self.calc_gradient_t(t)        # 实际的梯度是各个时刻梯度之和        self.gradient = reduce(            lambda a, b: a + b, self.gradient_list,            self.gradient_list[0]) # [0]被初始化为0且没有被修改过    def calc_gradient_t(self, t):        '''        计算每个时刻t权重的梯度        '''        gradient = np.dot(self.delta_list[t],            self.state_list[t-1].T)        self.gradient_list[t] = gradient
```

有意思的是，BPTT算法虽然数学推导的过程很麻烦，但是写成代码却并不复杂。

在update方法中，实现梯度下降算法。

```
    def update(self):        '''        按照梯度下降，更新权重        '''        self.W -= self.learning_rate * self.gradient
```

上面的代码不包含权重U的更新。这部分实际上和全连接神经网络是一样的，留给感兴趣的读者自己来完成吧。

**循环层**是一个**带状态**的层，每次forword都会改变循环层的内部状态，这给梯度检查带来了麻烦。因此，我们需要一个reset_state方法，来重置循环层的内部状态。

```
    def reset_state(self):        self.times = 0       # 当前时刻初始化为t0        self.state_list = [] # 保存各个时刻的state        self.state_list.append(np.zeros(            (self.state_width, 1)))      # 初始化s0
```

最后，是梯度检查的代码。

```
def gradient_check():    '''    梯度检查    '''    # 设计一个误差函数，取所有节点输出项之和    error_function = lambda o: o.sum()    rl = RecurrentLayer(3, 2, IdentityActivator(), 1e-3)    # 计算forward值    x, d = data_set()    rl.forward(x[0])    rl.forward(x[1])    # 求取sensitivity map    sensitivity_array = np.ones(rl.state_list[-1].shape,                                dtype=np.float64)    # 计算梯度    rl.backward(sensitivity_array, IdentityActivator())    # 检查梯度    epsilon = 10e-4    for i in range(rl.W.shape[0]):        for j in range(rl.W.shape[1]):            rl.W[i,j] += epsilon            rl.reset_state()            rl.forward(x[0])            rl.forward(x[1])            err1 = error_function(rl.state_list[-1])            rl.W[i,j] -= 2*epsilon            rl.reset_state()            rl.forward(x[0])            rl.forward(x[1])            err2 = error_function(rl.state_list[-1])            expect_grad = (err1 - err2) / (2 * epsilon)            rl.W[i,j] += epsilon            print 'weights(%d,%d): expected - actural %f - %f' % (                i, j, expect_grad, rl.gradient[i,j])
```

需要注意，每次计算error之前，都要调用reset_state方法重置循环层的内部状态。下面是梯度检查的结果，没问题！

![img](imgs/480b.png)

## 小节

至此，我们讲完了基本的**循环神经网络**、它的训练算法：**BPTT**，以及在语言模型上的应用。RNN比较烧脑，相信拿下前几篇文章的读者们搞定这篇文章也不在话下吧！然而，**循环神经网络**这个话题并没有完结。我们在前面说到过，基本的循环神经网络存在梯度爆炸和梯度消失问题，并不能真正的处理好长距离的依赖（虽然有一些技巧可以减轻这些问题）。事实上，真正得到广泛的应用的是循环神经网络的一个变体：**长短时记忆网络**。它内部有一些特殊的结构，可以很好的处理长距离的依赖，我们将在下一篇文章中详细的介绍它。现在，让我们稍事休息，准备挑战更为烧脑的**长短时记忆网络**吧。

## 参考资料

1. [RECURRENT NEURAL NETWORKS TUTORIAL](http://www.wildml.com/2015/09/recurrent-neural-networks-tutorial-part-1-introduction-to-rnns/)
2. [Understanding LSTM Networks](http://colah.github.io/posts/2015-08-Understanding-LSTMs/)
3. [The Unreasonable Effectiveness of Recurrent Neural Networks](http://karpathy.github.io/2015/05/21/rnn-effectiveness)
4. [Attention and Augmented Recurrent Neural Networks](http://distill.pub/2016/augmented-rnns/)
5. [On the difficulty of training recurrent neural networks, Bengio et al.](http://www.jmlr.org/proceedings/papers/v28/pascanu13.pdf)
6. [Recurrent neural network based language model, Mikolov et al.](http://www.fit.vutbr.cz/research/groups/speech/publi/2010/mikolov_interspeech2010_IS100722.pdf)
7. [Neural Network Classification, Categorical Data, Softmax Activation, and Cross Entropy Error, McCaffrey](https://jamesmccaffrey.wordpress.com/2011/12/17/neural-network-classification-categorical-data-softmax-activation-and-cross-entropy-error/)