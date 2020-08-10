# Pytorch常见方法

2020年8月9日

---

## 1. torch.size

torch.size ()：查看当前Tensor的维度，用法也很简单：

终端进入Python环境

\>>>import torch
\>>>a = torch.Tensor([[1, 2, 3], [4, 5, 6]])
\>>>a.size()

(2, 3)



## 2. torch.clamp

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
torch.clamp(input, *, max, out=None) → Tensor
```

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

## 3. torch.max()

> **形式：** torch.max(input) → Tensor
> 返回输入tensor中所有元素的最大值：

```python
a = torch.randn(1, 3)
>>0.4729 -0.2266 -0.2085
torch.max(a) #也可以写成a.max()
>>0.4729
```



> **形式：** torch.max(input, dim, keepdim=False, out=None) -> (Tensor, LongTensor)
> 按维度dim 返回最大值，并且返回索引。

`torch.max(a,0)`返回每一列中最大值的那个元素，且返回索引（返回最大元素在这一列的行索引）。返回的最大值和索引各是一个tensor，一起构成元组(Tensor, LongTensor)

```python
a = torch.randn(3,3)
>>
0.2252 -0.0901  0.5663
-0.4694  0.8073  1.3596
 0.1073 -0.7757 -0.8649
 
torch.max(a,0)
>>
(
 0.2252
 0.8073
 1.3596
[torch.FloatTensor of size 3]
, 
 0
 1
 1
[torch.LongTensor of size 3]
)
```

`torch.max(a,1)`返回每一行中最大值的那个元素，且返回其索引（返回最大元素在这一行的列索引）

```python
a = torch.randn(3,3)
>>
0.2252 -0.0901  0.5663
-0.4694  0.8073  1.3596
 0.1073 -0.7757 -0.8649
 
torch.max(a,1)
>>
(
 0.5663
 1.3596
 0.1073
[torch.FloatTensor of size 3]
, 
 2
 2
 0
[torch.LongTensor of size 3]
)
```

**拓展：**
`torch.max()[0]`， 只返回最大值的每个数
`troch.max()[1]`， 只返回最大值的每个索引
`torch.max()[1].data` 只返回variable中的数据部分（去掉Variable containing:）
`torch.max()[1].data.numpy()` 把数据转化成numpy ndarry
`torch.max()[1].data.numpy().squeeze()` 把数据条目中维度为1 的删除掉

## 4. torch.cat 

> `torch.cat`(*tensors*,*dim=0*,*out=None*)→ Tensor

对数据沿着某一维度进行拼接。cat后数据的总维数不变。
比如下面代码对两个2维tensor（分别为2\*3,1\*3）进行拼接，拼接完后变为3\*3还是2维的tensor。
代码如下：

```
import torch
torch.manual_seed(1)
x = torch.randn(2,3)
y = torch.randn(1,3)
print(x,y)
```

结果：

```
0.6614  0.2669  0.0617
 0.6213 -0.4519 -0.1661
[torch.FloatTensor of size 2x3]
 
-1.5228  0.3817 -1.0276
[torch.FloatTensor of size 1x3]
```

将两个tensor拼在一起：

```
torch.cat((x,y),0)
```

结果：

```
 0.6614  0.2669  0.0617
 0.6213 -0.4519 -0.1661
-1.5228  0.3817 -1.0276
[torch.FloatTensor of size 3x3]
```

更灵活的拼法：

```
torch.manual_seed(1)
x = torch.randn(2,3)
print(x)
print(torch.cat((x,x),0))
print(torch.cat((x,x),1))
```

结果

```
// x
0.6614  0.2669  0.0617
 0.6213 -0.4519 -0.1661
[torch.FloatTensor of size 2x3]

// torch.cat((x,x),0)
 0.6614  0.2669  0.0617
 0.6213 -0.4519 -0.1661
 0.6614  0.2669  0.0617
 0.6213 -0.4519 -0.1661
[torch.FloatTensor of size 4x3]

// torch.cat((x,x),1)
 0.6614  0.2669  0.0617  0.6614  0.2669  0.0617
 0.6213 -0.4519 -0.1661  0.6213 -0.4519 -0.1661
[torch.FloatTensor of size 2x6]
```

## 5. torch.stack

> `torch.stack`(*tensors*,*dim=0*,*out=None*)→ Tensor

而stack则会增加新的维度。
如对两个1\*2维的tensor在第0个维度上stack，则会变为2\*1\*2的tensor；在第1个维度上stack，则会变为1\*2\*2的tensor。
见代码：

```
a = torch.ones([1,2])
b = torch.ones([1,2])
c= torch.stack([a,b],0) // 第0个维度stack
```

输出：

```
tensor([[[1., 1.]],

        [[1., 1.]]])
[torch.FloatTensor of size 2x1x2]

c= torch.stack([a,b],1) // 第1个维度stack

```

输出：

```
tensor([[[1., 1.],
         [1., 1.]]])
[torch.FloatTensor of size 1x2x2]
```

## 6. transpose

两个维度互换

代码如下：

```
torch.manual_seed(1)
x = torch.randn(2,3)
print(x)
```

原来x的结果：

```
 0.6614  0.2669  0.0617
 0.6213 -0.4519 -0.1661
[torch.FloatTensor of size 2x3]
```

将x的维度互换

```
x.transpose(0,1)
```

结果

```
0.6614  0.6213
 0.2669 -0.4519
 0.0617 -0.1661
[torch.FloatTensor of size 3x2]
```

## 7. permute

多个维度互换，更灵活的transpose

permute是更灵活的transpose，可以灵活的对原数据的维度进行调换，而数据本身不变。
代码如下：

```
x = torch.randn(2,3,4)
print(x.size())
x_p = x.permute(1,0,2) # 将原来第1维变为0维，同理，0→1,2→2
print(x_p.size())
```

结果：

```
torch.Size([2, 3, 4])
torch.Size([3, 2, 4])
```

## 8. squeeze 和 unsqueeze

> torch.unsqueeze(input, dim, out=None)
>
> - **作用**：扩展维度
>
> 返回一个新的张量，对输入的既定位置插入维度 1
>
> - **注意：** 返回张量与输入张量共享内存，所以改变其中一个的内容会改变另一个。
>
> 如果dim为负，则将会被转化dim+input.dim()+1
>
> - **参数:**
> - `tensor (Tensor)` – 输入张量
> - `dim (int)` – 插入维度的索引
> - `out (Tensor, optional)` – 结果张量

> torch.squeeze(input, dim=None, out=None)
>
> - **作用**：降维
>
> 将输入张量形状中的1 去除并返回。 如果输入是形如(A×1×B×1×C×1×D)，那么输出形状就为： (A×B×C×D)
>
> 当给定dim时，那么挤压操作只在给定维度上。例如，输入形状为: (A×1×B), `squeeze(input, 0)` 将会保持张量不变，只有用 `squeeze(input, 1)`，形状会变成 (A×B)。
>
> - **注意**： 返回张量与输入张量共享内存，所以改变其中一个的内容会改变另一个。
> - **参数**:
> - `input (Tensor)` – 输入张量
> - `dim (int, optional)` – 如果给定，则input只会在给定维度挤压
> - `out (Tensor, optional)` – 输出张量
>
> **为何只去掉 1 呢？**
>
> **多维张量本质上就是一个变换，如果维度是 1 ，那么，1 仅仅起到扩充维度的作用，而没有其他用途，因而，在进行降维操作时，为了加快计算，是可以去掉这些 1 的维度。**



常用来增加或减少维度,如没有batch维度时，增加batch维度为1。

- squeeze(dim_n)压缩，减少dim_n维度 ，即去掉元素数量为1的dim_n维度。
- unsqueeze(dim_n)，增加dim_n维度，元素数量为1。

上代码：

```
# 定义张量
import torch

b = torch.Tensor(2,1)
b.shape
Out[28]: torch.Size([2, 1])

# 不加参数，去掉所有为元素个数为1的维度
b_ = b.squeeze()
b_.shape
Out[30]: torch.Size([2])

# 加上参数，去掉第一维的元素为1，不起作用，因为第一维有2个元素
b_ = b.squeeze(0)
b_.shape 
Out[32]: torch.Size([2, 1])

# 这样就可以了
b_ = b.squeeze(1)
b_.shape
Out[34]: torch.Size([2])

# 增加一个维度
b_ = b.unsqueeze(2)
b_.shape
Out[36]: torch.Size([2, 1, 1])
```



