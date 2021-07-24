# expand & repeat

⌚️: 2020年8月9日

📚参考

---

*torch.Tensor*是包含一种数据类型元素的多维矩阵。A *torch.Tensor* is a multi-dimensional matrix containing elements of a single data type.torch.Tensor有两个实例方法可以用来扩展某维的数据的尺寸，分别是***repeat()***和***expand()***：

## 1. expand

> expand(*sizes) -> Tensor
> *sizes(torch.Size or int) - the desired expanded **size**
> Returns a new view of the self tensor with singleton dimensions expanded to a larger size.

函数返回张量在某一个维度扩展之后的张量，就是将张量广播到新形状。函数对返回的**张量不会分配新内存**，即在原始张量上返回只读视图，返回的张量内存是不连续的。类似于numpy中的broadcast_to函数的作用。如果希望张量内存连续，可以调用contiguous函数。

**tensor.expend()函数**

```
>>> import torch
>>> a=torch.tensor([[2],[3],[4]])
>>> print(a.size())
torch.Size([3, 1])
>>> a.expand(3,2)
tensor([[2, 2],
    [3, 3],
    [4, 4]])
>>> a
tensor([[2],
    [3],
    [4]])
    
import torch

>> x = torch.tensor([1, 2, 3])
>> x.expand(2, 3)
tensor([[1, 2, 3],
        [1, 2, 3]])
        
        
>> x = torch.randn(2, 1, 1, 4)
>> x.expand(-1, 2, 3, -1)
torch.Size([2, 2, 3, 4])
```

可以看出expand()函数括号里面为变形后的size大小，而且原来的tensor和tensor.expand()是不共享内存的。



**tensor.expand_as()函数**

```
>>> b=torch.tensor([[2,2],[3,3],[5,5]])
>>> print(b.size())
torch.Size([3, 2])
>>> a.expand_as(b)
tensor([[2, 2],
    [3, 3],
    [4, 4]])
>>> a
tensor([[2],
    [3],
    [4]])
```

可以看出，b和a.expand_as(b)的size是一样大的。且是不共享内存的。

## 2. repeat

torch.repeat用法类似np.tile，就是将原矩阵横向、纵向地复制。与torch.expand不同的是torch.repeat返回的张量在内存中是连续的。

**repeat()**

> repeat(*sizes) -> Tensor
> *size(torch.Size or int) - The **number of times** to repeat this tensor along each dimension.
> Repeats this tensor along the specified dimensions.

沿着特定的维度重复这个张量，和*expand()*不同的是，这个函数**拷贝**张量的数据。

例子：

```python3
import torch

>> x = torch.tensor([1, 2, 3])
>> x.repeat(3, 2)
tensor([[1, 2, 3, 1, 2, 3],
        [1, 2, 3, 1, 2, 3],
        [1, 2, 3, 1, 2, 3]])
```



```text
>> x2 = torch.randn(2, 3, 4)
>> x2.repeat(2, 1, 3).shape
torch.Tensor([4, 3, 12])
```



例子1：

将张量横向的复制

```
import torch

x = torch.tensor([1, 2, 3])
xnew = x.repeat(1,3)
print(xnew)
```

输出：

> tensor([[1, 2, 3, 1, 2, 3, 1, 2, 3]])

例子2：

将张量纵向的复制

```
import torch

x = torch.tensor([1, 2, 3])
xnew = x.repeat(3,1)
print(xnew)
```

输出：

> tensor([[1, 2, 3],
>  [1, 2, 3],
>  [1, 2, 3]])