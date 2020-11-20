# torch.max()使用讲解

2020年11月20日

---



在分类问题中，通常需要使用`max()`函数对`softmax`函数的输出值进行操作，求出预测值索引。下面讲解一下`torch.max()`函数的输入及输出值都是什么。

# 1. torch.max(input, dim) 函数

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

# 2.准确率的计算



```python
pred_y = torch.max(predict, 1)[1].numpy()
y_label = torch.max(label, 1)[1].data.numpy()
accuracy = (pred_y == y_label).sum() / len(y_label)
```

