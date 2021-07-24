# Cat & stack

⌚️: 2020年8月9日

📚参考

---

## torch.cat 

> `torch.cat`(*tensors*,*dim=0*,*out=None*)→ Tensor

对数据沿着某一维度进行**拼接**。cat后数据的总维数不变。
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

## torch.stack

> `torch.stack`(*tensors*,*dim=0*,*out=None*)→ Tensor

而stack则会增加新的维度。**堆叠**
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

## 