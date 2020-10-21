# expand & repeat

2020年10月21日

---

## **1.torch.expand**

函数返回张量在某一个维度扩展之后的张量，就是将张量广播到新形状。函数对返回的张量不会分配新内存，即在原始张量上返回只读视图，返回的张量内存是不连续的。类似于numpy中的broadcast_to函数的作用。如果希望张量内存连续，可以调用contiguous函数。

例子：

```
import torch

x = torch.tensor([1, 2, 3, 4])
xnew = x.expand(2, 4)
print(xnew)
```

输出：

> tensor([[1, 2, 3, 4],
>     [1, 2, 3, 4]])

## **2.torch.repeat**

torch.repeat用法类似np.tile，就是将原矩阵横向、纵向地复制。与torch.expand不同的是torch.repeat返回的张量在内存中是连续的。

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
>     [1, 2, 3],
>     [1, 2, 3]])