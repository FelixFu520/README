# Pytorch张量（Tensor）复制

2020年8月9日

---

tensor复制可以使用`clone()`函数和`detach()`函数即可实现各种需求。

## 1. clone

clone()函数可以返回一个完全相同的tensor,新的tensor开辟新的内存，但是仍然留在计算图中。

## 2. detach

detach()函数可以返回一个完全相同的tensor,新的tensor开辟与旧的tensor共享内存，新的tensor会脱离计算图，不会牵扯梯度计算。此外，一些原地操作(in-place, such as resize_ / resize_as_ / set_ / transpose_) 在两者任意一个执行都会引发错误。

## 3. 使用分析

| # Operation             | New/Shared memory | Still in computation graph |
| ----------------------- | ----------------- | -------------------------- |
| tensor.clone()          | New               | Yes                        |
| tensor.detach()         | Shared            | No                         |
| tensor.clone().detach() | New               | No                         |

如下执行一些实例：
首先导入包并固定随机种子

```python
import torch
torch.manual_seed(0)
```



1.clone()之后的tensor requires_grad=True,detach()之后的tensor requires_grad=False，但是梯度并不会流向clone()之后的tensor

```python
x= torch.tensor([1., 2., 3.], requires_grad=True)
clone_x = x.clone()
detach_x = x.detach()
clone_detach_x = x.clone().detach()

f = torch.nn.Linear(3, 1)
y = f(x)
y.backward()

print(x.grad)
print(clone_x.requires_grad)
print(clone_x.grad)
print(detach_x.requires_grad)
print(clone_detach_x.requires_grad)
```

输出：

```python
tensor([-0.0043,  0.3097, -0.4752])
True
None
False
False
```



2.将计算图中参与运算tensor变为clone()后的tensor。此时梯度仍然只流向了原始的tensor。

```python
x= torch.tensor([1., 2., 3.], requires_grad=True)
clone_x = x.clone()
detach_x = x.detach()
clone_detach_x = x.detach().clone()

f = torch.nn.Linear(3, 1)
y = f(clone_x)
y.backward()

print(x.grad)
print(clone_x.grad)
print(detach_x.requires_grad)
print(clone_detach_x.requires_grad)
```

输出：

```python
tensor([-0.0043,  0.3097, -0.4752])
None
False
False
```



3.将原始tensor设为requires_grad=False，clone()后的梯度设为.requires_grad_()，clone()后的tensor参与计算图的运算，则梯度穿向clone()后的tensor。

```python
x= torch.tensor([1., 2., 3.], requires_grad=False)
clone_x = x.clone().requires_grad_()
detach_x = x.detach()
clone_detach_x = x.detach().clone()

f = torch.nn.Linear(3, 1)
y = f(clone_x)
y.backward()

print(x.grad)
print(clone_x.grad)
print(detach_x.requires_grad)
print(clone_detach_x.requires_grad)
```

输出：

```python
None
tensor([-0.0043,  0.3097, -0.4752])
False
False
```



4.detach()后的tensor由于与原始tensor共享内存，所以原始tensor在计算图中数值反向传播更新之后，detach()的tensor值也发生了改变。

```python
x = torch.tensor([1., 2., 3.], requires_grad=True)
f = torch.nn.Linear(3, 1)
w = f.weight.detach()
print(f.weight)
print(w)

y = f(x)
y.backward()

optimizer = torch.optim.SGD(f.parameters(), 0.1)
optimizer.step()

print(f.weight)
print(w)
```

输出：

```python
Parameter containing:
tensor([[-0.0043,  0.3097, -0.4752]], requires_grad=True)
tensor([[-0.0043,  0.3097, -0.4752]])
Parameter containing:
tensor([[-0.1043,  0.1097, -0.7752]], requires_grad=True)
tensor([[-0.1043,  0.1097, -0.7752]])
```