# Squeeze & unsqueeze

⌚️: 2020年8月9日

📚参考

----

## 理论

### unsqueeze

torch.unsqueeze(input, dim, out=None)

- **作用**：扩展维度

返回一个新的张量，对输入的既定位置插入维度 1

- **注意：** 返回张量与输入张量共享内存，所以改变其中一个的内容会改变另一个。

如果dim为负，则将会被转化dim+input.dim()+1

- **参数:**
- `tensor (Tensor)` – 输入张量
- `dim (int)` – 插入维度的索引
- `out (Tensor, optional)` – 结果张量

### squeeze

torch.squeeze(input, dim=None, out=None)

- **作用**：降维

将输入张量形状中的1 去除并返回。 如果输入是形如(A×1×B×1×C×1×D)，那么输出形状就为： (A×B×C×D)

当给定dim时，那么挤压操作只在给定维度上。例如，输入形状为: (A×1×B), `squeeze(input, 0)` 将会保持张量不变，只有用 `squeeze(input, 1)`，形状会变成 (A×B)。

- **注意**： 返回张量与输入张量共享内存，所以改变其中一个的内容会改变另一个。
- **参数**:
- `input (Tensor)` – 输入张量
- `dim (int, optional)` – 如果给定，则input只会在给定维度挤压
- `out (Tensor, optional)` – 输出张量

**为何只去掉 1 呢？**

**多维张量本质上就是一个变换，如果维度是 1 ，那么，1 仅仅起到扩充维度的作用，而没有其他用途，因而，在进行降维操作时，为了加快计算，是可以去掉这些 1 的维度。**



常用来增加或减少维度,如没有batch维度时，增加batch维度为1。

- squeeze(dim_n)压缩，减少dim_n维度 ，即去掉元素数量为1的dim_n维度。
- unsqueeze(dim_n)，增加dim_n维度，元素数量为1。

## 上代码

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

