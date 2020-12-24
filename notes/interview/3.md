**6.deeplearning 调参经验？**

一、参数初始化 下面几种方式,随便选一个,结果基本都差不多。但是一定要做。否则可能会减慢收敛速度，影响收敛结果，甚至造成Nan等一系列问题。 下面的n\_in为网络的输入大小，n\_out为网络的输出大小，n为n\_in或(n\_in+n\_out)\*0.5

Xavier初始法论文：http://jmlr.org/proceedings/papers/v9/glorot10a/glorot10a.pdf

He初始化论文：https://arxiv.org/abs/1502.01852 uniform均匀分布初始化：w = np.random.uniform(low=-scale, high=scale, size=\[n\_in,n\_out\])

Xavier初始法，适用于普通激活函数(tanh,sigmoid)：scale = np.sqrt(3/n)

He初始化，适用于ReLU：scale = np.sqrt(6/n) normal高斯分布初始化：w = np.random.randn(n\_in,n\_out) \* stdev # stdev为高斯分布的标准差，均值设为0

Xavier初始法，适用于普通激活函数 (tanh,sigmoid)：stdev = np.sqrt(n)

He初始化，适用于ReLU：stdev = np.sqrt(2/n)

svd初始化：对RNN有比较好的效果。参考论文：https://arxiv.org/abs/1312.6120

二、数据预处理方式 zero-center ,这个挺常用的.X -= np.mean(X, axis = 0) # zero-centerX /= np.std(X, axis = 0) # normalize PCA whitening,这个用的比较少.

三、训练技巧 要做梯度归一化,即算出来的梯度除以minibatch size clip c(梯度裁剪): 限制最大梯度,其实是value = sqrt(w1^2+w2^2….),如果value超过了阈值,就算一个衰减系系数,让value的值等于阈值: 5,10,15

dropout对小数据防止过拟合有很好的效果,值一般设为0.5,小数据上dropout+sgd在我的大部分实验中，效果提升都非常明显.因此可能的话，建议一定要尝试一下。

dropout的位置比较有讲究, 对于RNN,建议放到输入->RNN与RNN->输出的位置.关于RNN如何用dropout,可以参考这篇论文:http://arxiv.org/abs/1409.2329 adam,adadelta等,在小数据上,我这里实验的效果不如sgd, sgd收敛速度会慢一些，但是最终收敛后的结果，一般都比较好。

如果使用sgd的话,可以选择从1.0或者0.1的学习率开始,隔一段时间,在验证集上检查一下,如果cost没有下降,就对学习率减半. 我看过很多论文都这么搞,我自己实验的结果也很好. 当然,也可以先用ada系列先跑,最后快收敛的时候,更换成sgd继续训练.同样也会有提升.据说adadelta一般在分类问题上效果比较好，adam在生成问题上效果比较好。

除了gate之类的地方,需要把输出限制成0-1之外,尽量不要用sigmoid,可以用tanh或者relu之类的激活函数.1. sigmoid函数在-4到4的区间里，才有较大的梯度。之外的区间，梯度接近0，很容易造成梯度消失问题。2. 输入0均值，sigmoid函数的输出不是0均值的。 rnn的dim和embdding size,一般从128上下开始调整. batch size,一般从128左右开始调整.batch size合适最重要,并不是越大越好. word2vec初始化,在小数据上,不仅可以有效提高收敛速度,也可以可以提高结果.

四、尽量对数据做shuffle LSTM 的forget gate的bias,用1.0或者更大的值做初始化,可以取得更好的结果,来自这篇论文:http://jmlr.org/proceedings/papers/v37/jozefowicz15.pdf, 我这里实验设成1.0,可以提高收敛速度.实际使用中,不同的任务,可能需要尝试不同的值. Batch Normalization据说可以提升效果，不过我没有尝试过，建议作为最后提升模型的手段，参考论文：Accelerating Deep Network Training by Reducing Internal Covariate Shift

如果你的模型包含全连接层（MLP），并且输入和输出大小一样，可以考虑将MLP替换成Highway Network,我尝试对结果有一点提升，建议作为最后提升模型的手段，原理很简单，就是给输出加了一个gate来控制信息的流动，详细介绍请参考论文: http://arxiv.org/abs/1505.00387 一轮加正则，一轮不加正则，反复进行。

五、Ensemble Ensemble是论文刷结果的终极核武器,深度学习中一般有以下几种方式 同样的参数,不同的初始化方式 不同的参数,通过cross-validation,选取最好的几组 同样的参数,模型训练的不同阶段，即不同迭代次数的模型。 不同的模型,进行线性融合. 例如RNN和传统模型.

**7.CNN为什么可以应用在CV、NLP、SPEECH乃至ALPHA GO中？**

以上几个不相关问题的相关性在于，都存在局部与整体的关系，由低层次的特征经过组合，组成高层次的特征，并且得到不同特征之间的空间相关性。如下图：低层次的直线／曲线等特征，组合成为不同的形状，最后得到汽车的表示。

![](https://julyedu-img-public.oss-cn-beijing.aliyuncs.com/Public/Image/Question/1512808716_101.png)

CNN抓住此共性的手段主要有四个：局部连接／权值共享／池化操作／多层次结构。 局部连接使网络可以提取数据的局部特征；权值共享大大降低了网络的训练难度，一个Filter只提取一个特征，在整个图片（或者语音／文本） 中进行卷积；池化操作与多层次结构一起，实现了数据的降维，将低层次的局部特征组合成为较高层次的特征，从而对整个图片进行表示。如下图：

![](https://julyedu-img-public.oss-cn-beijing.aliyuncs.com/Public/Image/Question/1512808777_641.png)

上图中，如果每一个点的处理使用相同的Filter，则为全卷积，如果使用不同的Filter，则为Local-Conv。

**8.LSTM为什么比RNN好？**

因为LSTM有进有出且当前的cell informaton是通过input gate控制之后叠加的，RNN是叠乘，因此LSTM可以防止梯度消失或者爆炸。

**9.Sigmiod、Relu、Tanh三个激活函数的缺点和不足，有没有更好的激活函数？**

sigmoid、Tanh、ReLU的缺点在121问题中已有说明，为了解决ReLU的dead cell的情况，发明了Leaky Relu， 即在输入小于0时不让输出为0，而是乘以一个较小的系数，从而保证有导数存在。同样的目的，还有一个ELU，函数示意图如下。

![](https://julyedu-img-public.oss-cn-beijing.aliyuncs.com/Public/Image/Question/1512976776_132.jpg)

还有一个激活函数是Maxout，即使用两套w,b参数，输出较大值。本质上Maxout可以看做Relu的泛化版本，因为如果一套w,b全都是0的话，那么就是普通的ReLU。Maxout可以克服Relu的缺点，但是参数数目翻倍。

![](https://julyedu-img-public.oss-cn-beijing.aliyuncs.com/Public/Image/Question/1512976811_634.png)

**10.为什么引入非线性激活函数？**

第一，对于神经网络来说，网络的每一层相当于f(wx+b)=f(w'x)，对于线性函数，其实相当于f(x)=x，那么在线性激活函数下，每一层相当于用一个矩阵去乘以x，那么多层就是反复的用矩阵去乘以输入。根据矩阵的乘法法则，多个矩阵相乘得到一个大矩阵。所以线性激励函数下，多层网络与一层网络相当。比如，两层的网络f(W1\*f(W2x))=W1W2x=Wx。 第二，非线性变换是深度学习有效的原因之一。原因在于非线性相当于对空间进行变换，变换完成后相当于对问题空间进行简化，原来线性不可解的问题现在变得可以解了。 下图可以很形象的解释这个问题，左图用一根线是无法划分的。经过一系列变换后，就变成线性可解的问题了。

![](https://julyedu-img-public.oss-cn-beijing.aliyuncs.com/Public/Image/Question/1512979018_790.jpg)

如果不用激励函数（其实相当于激励函数是f(x) = x），在这种情况下你每一层输出都是上层输入的线性函数，很容易验证，无论你神经网络有多少层，输出都是输入的线性组合，与没有隐藏层效果相当，这种情况就是最原始的感知机（Perceptron）了。 正因为上面的原因，我们决定引入非线性函数作为激励函数，这样深层神经网络就有意义了（不再是输入的线性组合，可以逼近任意函数）。最早的想法是sigmoid函数或者tanh函数，输出有界，很容易充当下一层输入（以及一些人的生物解释）。
