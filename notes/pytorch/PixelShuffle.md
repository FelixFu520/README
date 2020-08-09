# PyTorch中的PixelShuffle

2020年8月9日

---

**感性认识**

一般的**convolution**操作会使feature map变小， 
但当我们的stride=1/r<1时，可以让卷积后的feature map变大，这个新的操作叫做**sub-pixel convolution**，具体原理可以看[Real-Time Single Image and Video Super-Resolution Using an Efficient Sub-Pixel Convolutional Neural Network](https://arxiv.org/abs/1609.05158)这篇paper。

## 1. 定义

该类定义如下：

```python
class torch.nn.PixleShuffle(upscale_factor)
```

这里的`upscale_factor`就是放大的倍数。

## 2. 输入输出的shape

具体一点来说，`Pixelshuffle`会将shape为(∗,$r^2C$,H,W)的`Tensor`给reshape成(∗,C,rH,rW)的`Tensor`。形式化地说，它的输入输出的shape如下： 
\- **Input**: (N,$C∗upscale\_factor^2$,H,W) 
\- **Output**: (N,C,H∗upscale_factor,W∗upscale_factor)

其中N代表batch size。

## 3. 例子

下面举个例子

```python
ps = nn.PixelShuffle(3)# 缩放到三倍，r == 3
input = torch.tensor(1, 9, 4, 4)## r^2 C == 9C == 9，所以C == 1
output = ps(input)
print(output.size())
# 输出为：
# torch.Size([1, 1, 12, 12])
```