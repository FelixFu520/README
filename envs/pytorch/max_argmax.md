# max & argmax & ...

⌚️: 2020年8月9日

📚参考

---



在分类问题中，通常需要使用`max()`函数对`softmax`函数的输出值进行操作，求出预测值索引。下面讲解一下`torch.max()`函数的输入及输出值都是什么。

## 1. torch.max(input, dim) 函数

```
output = torch.max(input, dim)
```

> 输入
>
> - `input`是softmax函数输出的一个`tensor`
> - `dim`是max函数索引的维度`0/1`，`0`是每列的最大值，`1`是每行的最大值

> 输出
>
> - 函数会返回两个`tensor`，第一个`tensor`是每行的最大值，softmax的输出中最大的是1，所以第一个`tensor`是全1的`tensor`；第二个`tensor`是每行最大值的索引。

我们通过一个实例可以更容易理解这个函数的用法。



```python
import torch
a = torch.tensor([[1,5,62,54], [2,6,2,6], [2,65,2,6]])
print(a)
```

输出：

```python
tensor([[ 1,  5, 62, 54],
        [ 2,  6,  2,  6],
        [ 2, 65,  2,  6]])
```

索引每行的最大值：

```python
torch.max(a, 1)
```

输出：

```python
torch.return_types.max(
values=tensor([62,  6, 65]),
indices=tensor([2, 3, 1]))
```

在计算准确率时第一个tensor `values`是不需要的，所以我们只需提取第二个tensor，并将tensor格式的数据转换成array格式。

```python
torch.max(a, 1)[1].numpy()
```

输出：

```cpp
array([2, 3, 1], dtype=int64)
```

*注：在有的地方我们会看到`torch.max(a, 1).data.numpy()`的写法，这是因为在早期的pytorch的版本中，variable变量和tenosr是不一样的数据格式，variable可以进行反向传播，tensor不可以，需要将variable转变成tensor再转变成numpy。现在的版本已经将variable和tenosr合并，所以只用`torch.max(a,1).numpy()`就可以了。

### 准确率的计算

```python
pred_y = torch.max(predict, 1)[1].numpy()
y_label = torch.max(label, 1)[1].data.numpy()
accuracy = (pred_y == y_label).sum() / len(y_label)
```

### **拓展**

`torch.max()[0]`， 只返回最大值的每个数
`troch.max()[1]`， 只返回最大值的每个索引
`torch.max()[1].data` 只返回variable中的数据部分（去掉Variable containing:）
`torch.max()[1].data.numpy()` 把数据转化成numpy ndarry
`torch.max()[1].data.numpy().squeeze()` 把数据条目中维度为1 的删除掉

## 2. torch.argmax函数

**argmax函数**：`torch.argmax(input, dim=None, keepdim=False)`返回指定维度最大值的序号，**dim给定的定义是：the demention to reduce**.也就是把dim这个维度的，变成这个维度的最大值的index。

1）dim的不同值表示不同维度。特别的在dim=0表示二维中的列，dim=1在二维矩阵中表示行。广泛的来说，我们不管一个矩阵是几维的，比如一个矩阵维度如下：(d0,d1,...,dn−1) ，那么dim=0就表示对应到d0 也就是第一个维度，dim=1表示对应到也就是第二个维度，一次类推。

2）知道dim的值是什么意思还不行，还要知道函数中这个dim给出来会发生什么。结合这两个才会知道dim在函数中的作用。下面举两个例子说明上面的第二点。

例子一：torch.argmax()函数中dim表示该维度会消失。

这个消失是什么意思？官方英文解释是：dim (int) – the dimension to reduce.
我们知道argmax就是得到最大值的序号索引，对于一个维度为(d0,d1) 的矩阵来说，我们想要求每一行中最大数的在该行中的列号，最后我们得到的就是一个维度为(d0,1) 的一矩阵。这时候，列就要消失了。

因此，我们想要求每一行最大的列标号，我们就要指定dim=1，表示我们不要列了，保留行的size就可以了。
假如我们想求每一列的最大行标，就可以指定dim=0，表示我们不要行了。
example 1

```python
import torch
a=torch.tensor(
              [
                  [1, 5, 5, 2],
                  [9, -6, 2, 8],
                  [-3, 7, -9, 1]
              ])
b=torch.argmax(a,dim=0)
print(b)
print(a.shape)
```

 \#结果：

```html
tensor([1, 2, 0, 1])
torch.Size([3, 4])
```

dim=0维度上为3,即在那3组数据中作比较，求得是每一列中的最大行标，因此为[1,2,0,4]

example2 在三维坐标中

```python
import torch
a=torch.tensor([
              [
                  [1, 5, 5, 2],
                  [9, -6, 2, 8],
                  [-3, 7, -9, 1]
              ],
 
              [
                  [-1, 7, -5, 2],
                  [9, 6, 2, 8],
                  [3, 7, 9, 1]
              ]])
b=torch.argmax(a,dim=0)
print(b)
print(a.shape)
 
"""
tensor([[0, 1, 0, 1],
        [1, 1, 1, 1],
        [1, 1, 1, 1]])
torch.Size([2, 3, 4])"""
 
#dim=0,即将第一个维度消除，也就是将两个[3*4]矩阵只保留一个，因此要在两组中作比较，即将上下两个[3*4]的矩阵分别在对应的位置上比较
 
b=torch.argmax(a,dim=1)
“”“
tensor([[1, 2, 0, 1],
        [1, 2, 2, 1]])
torch.Size([2, 3, 4])”“”
#dim=1，即将第二个维度消除,这么理解：矩阵维度变为[2*4];
"""[1, 5, 5, 2],
   [9, -6, 2, 8],
   [-3, 7, -9, 1];
纵向压缩成一维，因此变为[1,2,0,1];同理得到[1,2,2,1];"""
b=torch.argmax(a,dim=2)
"""
tensor([[2, 0, 1],
        [1, 0, 2]])
"""
#dim=2,即将第三个维度消除，这么理解：矩阵维度变为[2*3]
"""
   [1, 5, 5, 2],
   [9, -6, 2, 8],
   [-3, 7, -9, 1];
横向压缩成一维
[2,0,1],同理得到下面的“”“

```

## 3. torch.size

torch.size ()：查看当前Tensor的维度，用法也很简单：

终端进入Python环境

\>>>import torch
\>>>a = torch.Tensor([[1, 2, 3], [4, 5, 6]])
\>>>a.size()

(2, 3)



## 4. torch.clamp

> torch.clamp(input, min, max, out=None) → Tensor

将输入`input`张量每个元素的夹紧到区间 [min,max]，并返回结果到一个新张量。

操作定义如下：

```python
      | min, if x_i < min
y_i = | x_i, if min <= x_i <= max
      | max, if x_i > max
```

如果输入是FloatTensor or DoubleTensor类型，则参数`min` `max` 必须为实数，否则须为整数。【译注：似乎并非如此，无关输入类型，`min`， `max`取整数、实数皆可。】

参数：

- input (Tensor) – 输入张量
- min (Number) – 限制范围下限
- max (Number) – 限制范围上限
- out (Tensor, optional) – 输出张量

例子：

```python
>>> a = torch.randn(4)
>>> a
-1.4511
-0.6812
 0.3302
-1.7423

[torch.FloatTensor of size 4]

>>> torch.clamp(a, min=-0.5, max=0.5)
-0.5000
-0.5000
 0.3302
-0.5000

[torch.FloatTensor of size 4]
torch.clamp(input, *, min, out=None) → Tensor


a.clamp_(min=-0.5,max=0.5) #另一种实现方法
-0.5000
-0.5000
 0.3302
-0.5000
[torch.FloatTensor of size 4]
```

将输入`input`张量每个元素的限制到不小于`min` ，并返回结果到一个新张量。

如果输入是FloatTensor or DoubleTensor类型，则参数 `min` 必须为实数，否则须为整数。【译注：似乎并非如此，无关输入类型，`min`取整数、实数皆可。】

参数：

- input (Tensor) – 输入张量
- value (Number) – 限制范围下限
- out (Tensor, optional) – 输出张量

例子：

```python
>>> a = torch.randn(4)
>>> a

 1.3869
 0.3912
-0.8634
-0.5468
[torch.FloatTensor of size 4]

>>> torch.clamp(a, min=0.5)

 1.3869
 0.5000
 0.5000
 0.5000
[torch.FloatTensor of size 4]

```

`torch.clamp(input, *, max, out=None) → Tensor`

将输入`input`张量每个元素的限制到不大于`max` ，并返回结果到一个新张量。

如果输入是FloatTensor or DoubleTensor类型，则参数 `max` 必须为实数，否则须为整数。【译注：似乎并非如此，无关输入类型，`max`取整数、实数皆可。】

参数：

- input (Tensor) – 输入张量
- value (Number) – 限制范围上限
- out (Tensor, optional) – 输出张量

例子：

```python
>>> a = torch.randn(4)
>>> a

 1.3869
 0.3912
-0.8634
-0.5468
[torch.FloatTensor of size 4]

>>> torch.clamp(a, max=0.5)

 0.5000
 0.3912
-0.8634
-0.5468
[torch.FloatTensor of size 4]
```

## 5. torch.sum()的用法

torch.sum()对输入的tensor数据的某一维度求和，一共两种用法

```
１．torch.sum(input, dtype=None)
２．torch.sum(input, list: dim, bool: keepdim=False, dtype=None) → Tensor
　
input:输入一个tensor
dim:要求和的维度，可以是一个列表
keepdim:求和之后这个dim的元素个数为１，所以要被去掉，如果要保留这个维度，则应当keepdim=True
#If keepdim is True, the output tensor is of the same size as input except in the dimension(s) dim where it is of size 1. 

```

例子：

```
a = torch.ones((2, 3))
print(a):
tensor([[1, 1, 1],
 		[1, 1, 1]])

a1 =  torch.sum(a)
a2 =  torch.sum(a, dim=0)
a3 =  torch.sum(a, dim=1)

print(a)
print(a1)
print(a2)

```

输出结果：

```
tensor(6.)
tensor([2., 2., 2.])
tensor([3., 3.])

```

如果加上keepdim=True, 则会保持dim的维度不被squeeze

```
a1 =  torch.sum(a, dim=(0, 1), keepdim=True)
a2 =  torch.sum(a, dim=(0, ), keepdim=True)
a3 =  torch.sum(a, dim=(1, ), keepdim=True)

```

输出结果：

```
tensor([[6.]])
tensor([[2., 2., 2.]])
tensor([[3., 3.]])
```

## 6. topk函数详解

听名字就知道这个函数是用来求tensor中某个dim的前k大或者前k小的值以及对应的index。

### 用法

`torch.topk(input, k, dim=None, largest=True, sorted=True, out=None) -> (Tensor, LongTensor)`



> input：一个tensor数据
> k：指明是得到前k个数据以及其index
> dim： 指定在哪个维度上排序， 默认是最后一个维度
> largest：如果为True，按照大到小排序； 如果为False，按照小到大排序
> sorted：返回的结果按照顺序返回
> out：可缺省，不要



topk最常用的场合就是求一个样本被网络认为前k个最可能属于的类别。我们就用这个场景为例，说明函数的使用方法。
假设一个tensor$ F ∈ R ^{N × D}$  ，N是样本数目，一般等于batch size， D是类别数目。我们想知道每个样本的最可能属于的那个类别，其实可以用torch.max得到。如果要使用topk，则k应该设置为1。

```
import torch

pred = torch.randn((4, 5))
print(pred)
values, indices = pred.topk(1, dim=1, largest=True, sorted=True)
print(indices)


# 用max得到的结果，设置keepdim为True，避免降维。因为topk函数返回的index不降维，shape和输入一致。
_, indices_max = pred.max(dim=1, keepdim=True)
print(indices_max == indices)

# pred
tensor([[-0.1480, -0.9819, -0.3364,  0.7912, -0.3263],
        [-0.8013, -0.9083,  0.7973,  0.1458, -0.9156],
        [-0.2334, -0.0142, -0.5493,  0.0673,  0.8185],
        [-0.4075, -0.1097,  0.8193, -0.2352, -0.9273]])

# indices, shape为 【4,1】,
tensor([[3],   #【0, 0】代表第一个样本最可能属于第一类别
        [2],   #【1, 0】代表第二个样本最可能属于第二类别
        [4],
        [2]])

# indices_max等于indices
tensor([[True],
        [True],
        [True],
        [True]])
```


现在在尝试一下k=2

```
import torch

pred = torch.randn((4, 5))
print(pred)
values, indices = pred.topk(2, dim=1, largest=True, sorted=True)  # k=2
print(indices)

# pred

tensor([[-0.2203, -0.7538,  1.8789,  0.4451, -0.2526],
        [-0.0413,  0.6366,  1.1155,  0.3484,  0.0395],
        [ 0.0365,  0.5158,  1.1067, -0.9276, -0.2124],
        [ 0.6232,  0.9912, -0.8562,  0.0148,  1.6413]])

# indices

tensor([[2, 3],
        [2, 1],
        [2, 1],
        [4, 1]])
```


可以发现indices的shape变成了【4, k】，k=2。
其中indices[0] = [2,3]。其意义是说明第一个样本的前两个最大概率对应的类别分别是第3类和第4类。

大家可以自行print一下values。可以发现values的shape和indices的shape是一样的。indices描述了在values中对应的值在pred中的位置。

