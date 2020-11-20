# torch.sum()的用法

2020年11月20日

---



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