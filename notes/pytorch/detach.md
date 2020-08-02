# detach() item() cpu() numpy()理解

2020年8月2日

---

## 1. numpy和tensor类型转换

在深度学习训练后，需要计算每个epoch得到的模型的训练效果的时候，一般会用到detach() item() cpu() numpy()等函数。
例如

```python
import torch.optim as optim
import torch.utils.data
import torch.backends.cudnn as cudnn


gpu_info = torch.randn(3,3).cuda()
print(gpu_info)

tensor([[ 0.9621, -1.0931, -0.8481],
        [-0.1668, -1.3945,  0.6562],
        [ 0.6152,  0.4177, -0.3538]], device='cuda:0')
```



### 1. 1 item（）

item()返回的是tensor中的值，且只能返回单个值（标量），不能返回向量，使用返回loss等。

```python
loss.item() # 获得loss的值
```



### 1.2 detach（）

detach阻断反向传播，返回值仍为tensor

```python
gpu_info.detach()  #返回tensor，仍在gpu上

tensor([[ 0.9621, -1.0931, -0.8481],
        [-0.1668, -1.3945,  0.6562],
        [ 0.6152,  0.4177, -0.3538]], device='cuda:0')

```

### 1.3 cpu（）/cuda（）

cpu()将变量放在cpu上，仍为tensor：

```python
gpu_info.cpu()

tensor([[ 0.9621, -1.0931, -0.8481],
        [-0.1668, -1.3945,  0.6562],
        [ 0.6152,  0.4177, -0.3538]])

gpu_info.cpu().detach()

tensor([[ 0.9621, -1.0931, -0.8481],
        [-0.1668, -1.3945,  0.6562],
        [ 0.6152,  0.4177, -0.3538]])
```

### 1.4 numpy（）

numpy()将tensor转换为numpy：
注意cuda上面的变量类型只能是tensor，不能是其他

```python
gpu_info.detach().numpy()

TypeError   Traceback (most recent call last)
<ipython-input-12-53aa55b45af2> in <module>()
----> 1 gpu_info.detach().numpy()
TypeError: can't convert CUDA tensor to numpy. Use Tensor.cpu() to copy the tensor to host memory first.
123456
gpu_info.cpu().numpy()

array([[ 0.9621306 , -1.0930926 , -0.8481391 ],
       [-0.1667992 , -1.3945109 ,  0.656157  ],
       [ 0.6151904 ,  0.41773367, -0.35378388]], dtype=float32)
```

## 2. 切断反向传播

pytorch .detach() .detach_() 和 .data用于切断反向传播。当我们再训练网络的时候可能希望保持一部分的网络参数不变，只对其中一部分的参数进行调整；或者值训练部分分支网络，并不让其梯度对主网络的梯度造成影响，这时候我们就需要使用detach()函数来切断一些分支的反向传播

### 2.1  detach()[source]

返回一个新的`Variable`，从当前计算图中分离下来的，但是仍指向原变量的存放位置,不同之处只是requires_grad为false，得到的这个`Variable`永远不需要计算其梯度，不具有grad。

**即使之后重新将它的requires_grad置为true,它也不会具有梯度grad**

这样我们就会继续使用这个新的`Variable进行计算，后面当我们进行`反向传播时，到该调用detach()的`Variable`就会停止，不能再继续向前进行传播

源码为：

```
def detach(self):
        """Returns a new Variable, detached from the current graph.
        Result will never require gradient. If the input is volatile, the output
        will be volatile too.
        .. note::
          Returned Variable uses the same data tensor, as the original one, and
          in-place modifications on either of them will be seen, and may trigger
          errors in correctness checks.
        """
        result = NoGrad()(self)  # this is needed, because it merges version counters
        result._grad_fn = None
　　　　 return result
```



可见函数进行的操作有：

- 将grad_fn设置为None
- `将Variable`的`requires_grad设置为False`

如果输入 `volatile=True(即不需要保存记录，当只需要结果而不需要更新参数时这么设置来加快运算速度)`，那么返回的`Variable` `volatile=True`。（`volatile`已经弃用）

**`注意：`**

返回的`Variable`和原始的`Variable`公用同一个`data tensor`。`in-place函数`修改会在两个`Variable`上同时体现(因为它们共享`data tensor`)，当要对其调用backward()时可能会导致错误。

举例：

比如正常的例子是：

```
import torch

a = torch.tensor([1, 2, 3.], requires_grad=True)
print(a.grad)
out = a.sigmoid()

out.sum().backward()
print(a.grad)
```

返回：

```
(deeplearning) userdeMBP:pytorch user$ python test.py 
None
tensor([0.1966, 0.1050, 0.0452])
```

 

当使用detach()但是没有进行更改时，并不会影响backward():

```
import torch

a = torch.tensor([1, 2, 3.], requires_grad=True)
print(a.grad)
out = a.sigmoid()
print(out)

#添加detach(),c的requires_grad为False
c = out.detach()
print(c)

#这时候没有对c进行更改，所以并不会影响backward()
out.sum().backward()
print(a.grad)
```

返回：

```
(deeplearning) userdeMBP:pytorch user$ python test.py 
None
tensor([0.7311, 0.8808, 0.9526], grad_fn=<SigmoidBackward>)
tensor([0.7311, 0.8808, 0.9526])
tensor([0.1966, 0.1050, 0.0452])
```

可见c,out之间的区别是c是没有梯度的，out是有梯度的

 

如果这里使用的是c进行sum()操作并进行backward()，则会报错：

```
import torch

a = torch.tensor([1, 2, 3.], requires_grad=True)
print(a.grad)
out = a.sigmoid()
print(out)

#添加detach(),c的requires_grad为False
c = out.detach()
print(c)

#使用新生成的Variable进行反向传播
c.sum().backward()
print(a.grad)
```

返回：

```
(deeplearning) userdeMBP:pytorch user$ python test.py 
None
tensor([0.7311, 0.8808, 0.9526], grad_fn=<SigmoidBackward>)
tensor([0.7311, 0.8808, 0.9526])
Traceback (most recent call last):
  File "test.py", line 13, in <module>
    c.sum().backward()
  File "/anaconda3/envs/deeplearning/lib/python3.6/site-packages/torch/tensor.py", line 102, in backward
    torch.autograd.backward(self, gradient, retain_graph, create_graph)
  File "/anaconda3/envs/deeplearning/lib/python3.6/site-packages/torch/autograd/__init__.py", line 90, in backward
    allow_unreachable=True)  # allow_unreachable flag
RuntimeError: element 0 of tensors does not require grad and does not have a grad_fn
```



如果此时对c进行了更改，这个更改会被autograd追踪，在对out.sum()进行backward()时也会报错，因为此时的值进行backward()得到的梯度是错误的：

```
import torch

a = torch.tensor([1, 2, 3.], requires_grad=True)
print(a.grad)
out = a.sigmoid()
print(out)

#添加detach(),c的requires_grad为False
c = out.detach()
print(c)
c.zero_() #使用in place函数对其进行修改

#会发现c的修改同时会影响out的值
print(c)
print(out)

#这时候对c进行更改，所以会影响backward()，这时候就不能进行backward()，会报错
out.sum().backward()
print(a.grad)
```

返回：

```
(deeplearning) userdeMBP:pytorch user$ python test.py 
None
tensor([0.7311, 0.8808, 0.9526], grad_fn=<SigmoidBackward>)
tensor([0.7311, 0.8808, 0.9526])
tensor([0., 0., 0.])
tensor([0., 0., 0.], grad_fn=<SigmoidBackward>)
Traceback (most recent call last):
  File "test.py", line 16, in <module>
    out.sum().backward()
  File "/anaconda3/envs/deeplearning/lib/python3.6/site-packages/torch/tensor.py", line 102, in backward
    torch.autograd.backward(self, gradient, retain_graph, create_graph)
  File "/anaconda3/envs/deeplearning/lib/python3.6/site-packages/torch/autograd/__init__.py", line 90, in backward
    allow_unreachable=True)  # allow_unreachable flag
RuntimeError: one of the variables needed for gradient computation has been modified by an inplace operation
```



 

### 2.2 data

如果上面的操作使用的是.data，效果会不同：

这里的不同在于.data的修改不会被autograd追踪，这样当进行backward()时它不会报错，回得到一个错误的backward值

```
import torch

a = torch.tensor([1, 2, 3.], requires_grad=True)
print(a.grad)
out = a.sigmoid()
print(out)


c = out.data
print(c)
c.zero_() #使用in place函数对其进行修改

#会发现c的修改同时也会影响out的值
print(c)
print(out)

#这里的不同在于.data的修改不会被autograd追踪，这样当进行backward()时它不会报错，回得到一个错误的backward值
out.sum().backward()
print(a.grad)
```

返回：

```
(deeplearning) userdeMBP:pytorch user$ python test.py 
None
tensor([0.7311, 0.8808, 0.9526], grad_fn=<SigmoidBackward>)
tensor([0.7311, 0.8808, 0.9526])
tensor([0., 0., 0.])
tensor([0., 0., 0.], grad_fn=<SigmoidBackward>)
tensor([0., 0., 0.])
```

 上面的内容实现的原理是：

**In-place 正确性检查**

所有的`Variable`都会记录用在他们身上的 `in-place operations`。如果`pytorch`检测到`variable`在一个`Function`中已经被保存用来`backward`，但是之后它又被`in-place operations`修改。当这种情况发生时，在`backward`的时候，`pytorch`就会报错。这种机制保证了，如果你用了`in-place operations`，但是在`backward`过程中没有报错，那么梯度的计算就是正确的。

 

⚠️下面结果正确是因为改变的是sum()的结果，中间值a.sigmoid()并没有被影响，所以其对求梯度并没有影响：

```
import torch

a = torch.tensor([1, 2, 3.], requires_grad=True)
print(a.grad)
out = a.sigmoid().sum() #但是如果sum写在这里，而不是写在backward()前，得到的结果是正确的
print(out)


c = out.data
print(c)
c.zero_() #使用in place函数对其进行修改

#会发现c的修改同时也会影响out的值
print(c)
print(out)

#没有写在这里
out.backward()
print(a.grad)
```

返回：

```
(deeplearning) userdeMBP:pytorch user$ python test.py 
None
tensor(2.5644, grad_fn=<SumBackward0>)
tensor(2.5644)
tensor(0.)
tensor(0., grad_fn=<SumBackward0>)
tensor([0.1966, 0.1050, 0.0452])
```

 

### 2.3  detach_()[source]

将一个`Variable`从创建它的图中分离，并把它设置成叶子`variable`

其实就相当于变量之间的关系本来是x -> m -> y,这里的叶子variable是x，但是这个时候对m进行了.detach_()操作,其实就是进行了两个操作：

- 将m的grad_fn的值设置为None,这样m就不会再与前一个节点x关联，这里的关系就会变成x, m -> y,此时的m就变成了叶子结点
- 然后会将m的requires_grad设置为False，这样对y进行backward()时就不会求m的梯度

 

⚠️

这么一看其实detach()和detach_()很像，两个的区别就是detach_()是对本身的更改，detach()则是生成了一个新的variable

比如x -> m -> y中如果对m进行detach()，后面如果反悔想还是对原来的计算图进行操作还是可以的

但是如果是进行了detach_()，那么原来的计算图也发生了变化，就不能反悔了

 

## 3. PyTorch中 detach() 、detach_()和 data 的区别

### **3.1 介绍**

  在使用PyTorch的过程中，我们经常会遇到detach() 、detach_()和 data这三种类别，如果你不详细分析它们的使用场所，的确是很容易让人懵逼。

  1）detach()与detach_()

  在x->y->z传播中，如果我们对y进行detach()，梯度还是能正常传播的，但如果我们对y进行detach_()，就把x->y->z切成两部分：x和y->z，x就无法接受到后面传过来的梯度

  2）detach()和data

  共同点：x.data（x.detach()） 返回和 x 的相同数据 tensor, 这个新的tensor和原来的tensor（即x）是共用数据的，一者改变，另一者也会跟着改变，且require s_grad = False

  不同点： x.data 不能被 autograd 追踪求微分，即使被改了也能错误求导，而x.detach()则不行

 

### **3.2 代码**

```python
import torch


a = torch.tensor([1, 2, 3.], requires_grad=True)
print(a)

out = a.tanh()
print(out)

c = out.data  # 需要走注意的是，通过.data “分离”得到的的变量会和原来的变量共用同样的数据，而且新分离得到的张量是不可求导的，c发生了变化，原来的张量也会发生变化
c.zero_() # 改变c的值，原来的out也会改变
print(c.requires_grad)
print(c)
print(out.requires_grad)
print(out)
print("----------------------------------------------")

out.sum().backward()  # 对原来的out求导，
print(a.grad)  # 不会报错，但是结果却并不正确

#输出
tensor([1., 2., 3.], requires_grad=True)
tensor([0.7616, 0.9640, 0.9951], grad_fn=<TanhBackward>)
False
tensor([0., 0., 0.])
True
tensor([0., 0., 0.], grad_fn=<TanhBackward>)
----------------------------------------------
tensor([1., 1., 1.])
```

 

```python
import torch
 
a = torch.tensor([1, 2, 3.], requires_grad=True)
print(a)
out = a.tanh()
print(out)
c = out.detach()  # 需要走注意的是，通过.detach() “分离”得到的的变量会和原来的变量共用同样的数据，而且新分离得到的张量是不可求导的，c发生了变化，原来的张量也会发生变化
c.zero_()  # 改变c的值，原来的out也会改变
print(c.requires_grad)
print(c)
print(out.requires_grad)
print(out)
print("----------------------------------------------")
 
out.sum().backward()  # 对原来的out求导，
print(a.grad)  # 此时会报错，错误结果参考下面,显示梯度计算所需要的张量已经被“原位操作inplace”所更改了。
 
# 输出
tensor([1., 2., 3.], requires_grad=True)
tensor([0.7616, 0.9640, 0.9951], grad_fn=<TanhBackward>)
False
tensor([0., 0., 0.])
True
tensor([0., 0., 0.], grad_fn=<TanhBackward>)
----------------------------------------------
Traceback (most recent call last):
  File "E:/python/TCL/entropy_coding_project/test_code/test27.py", line 15, in <module>
    out.sum().backward()  # 对原来的out求导，
  File "D:\ProgramData\Anaconda3\lib\site-packages\torch\tensor.py", line 107, in backward
    torch.autograd.backward(self, gradient, retain_graph, create_graph)
  File "D:\ProgramData\Anaconda3\lib\site-packages\torch\autograd\__init__.py", line 93, in backward
    allow_unreachable=True)  # allow_unreachable flag
RuntimeError: one of the variables needed for gradient computation has been modified by an inplace operation: [torch.FloatTensor [3]], which is output 0 of TanhBackward, is at version 1; expected version 0 instead. Hint: enable anomaly detection to find the operation that failed to compute its gradient, with torch.autograd.set_detect_anomaly(True).


```

 

## 参考

> [pytorch .detach() .detach_() 和 .data用于切断反向传播](https://www.cnblogs.com/wanghui-garcia/p/10677071.html)
>
> [pytorch detach() item() cpu() numpy()理解](https://blog.csdn.net/ODIMAYA/article/details/102892799)
>
> [PyTorch中 detach() 、detach_()和 data 的区别](https://blog.csdn.net/u013289254/article/details/102557070)

