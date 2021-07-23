# 直方图均衡化

⌚️: 2020年8月1日

📚参考

- [直方图拉伸和图像均衡化](https://www.zhihu.com/column/p/31213741)
- [对比度拉伸和直方图均衡之间的区别](https://www.codenong.com/41118808/)

---

图像对比度增强的方法可以分成两类:一类是直接对比度增强方法;另一类是间接对比度增强方法。直方图拉伸和直方图均衡化是两种最常见的间接对比度增强方法。

直方图拉伸是通过对比度拉伸对直方图进行调整，从而“扩大”前景和背景灰度的差别，以达到增强对比度的目的，这种方法可以利用线性或非线性的方法来实现;直方图均衡化则通过使用累积函数对灰度值进行“调整”以实现对比度的增强。

直方图均衡化处理的“中心思想”是把原始图像的灰度直方图从比较集中的某个灰度区间变成在全部灰度范围内的均匀分布。直方图均衡化就是对图像进行非线性拉伸，重新分配图像像素值，使一定灰度范围内的像素数量大致相同。直方图均衡化就是把给定图像的直方图分布改变成“均匀”分布直方图分布。
　　缺点： 
　　1）变换后图像的灰度级减少，某些细节消失； 

　　2）某些图像，如直方图有高峰，经处理后对比度不自然的过分增强。 

　　

直方图均衡化是图像处理领域中利用图像直方图对对比度进行调整的方法。这种方法通常用来增加许多图像的局部对比度，尤其是当图像的有用数据的对比度相当接近的时候。通过这种方法，亮度可以更好地在直方图上分布。这样就可以用于增强局部的对比度而不影响整体的对比度，直方图均衡化通过有效地扩展常用的亮度来实现这种功能。　　这种方法对于背景和前景都太亮或者太暗的图像非常有用，这种方法尤其是可以带来X光图像中更好的骨骼结构显示以及曝光过度或者曝光不足照片中更好的细节。这种方法的一个主要优势是它是一个相当直观的技术并且是可逆操作，如果已知均衡化函数，那么就可以恢复原始的直方图，并且计算量也不大。这种方法的一个缺点是它对处理的数据不加选择，它可能会增加背景杂讯的对比度并且降低有用信号的对比度。



## 1. python + opencv 直方图均衡化

直方图均衡化的三种情况,分别是:

- 灰度图像直方图均衡化
- 彩色图像直方图均衡化
- YUV 直方图均衡化

插入原图:

![原图](imgs/uuu.png)

### 灰度图像直方图均衡化

对直方图均衡化主要使用opencv提供的一个equalizeHist()方法.

```
import cv2
import numpy as np

img = cv2.imread("image0.jpg", 1)
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
cv2.imshow("src", gray)

dst = cv2.equalizeHist(gray)
cv2.imshow("dst", dst)

cv2.waitKey(0)
```




### 彩色图像直方图均衡化

彩色图像的直方图均衡化和灰度图像略有不同,需要将彩色图像先用split()方法,将三个通道拆分,然后分别进行均衡化.最后使用merge()方法将均衡化之后的三个通道进行合并.操作如下:

```
import cv2
import numpy as np

img = cv2.imread("image0.jpg", 1)
cv2.imshow("src", img)

# 彩色图像均衡化,需要分解通道 对每一个通道均衡化

(b, g, r) = cv2.split(img)
bH = cv2.equalizeHist(b)
gH = cv2.equalizeHist(g)
rH = cv2.equalizeHist(r)

# 合并每一个通道

result = cv2.merge((bH, gH, rH))
cv2.imshow("dst", result)

cv2.waitKey(0)
```



### YUV 直方图均衡化

```
import cv2
import numpy as np
img = cv2.imread("image0.jpg", 1)

imgYUV = cv2.cvtColor(img, cv2.COLOR_BGR2YCrCb)
cv2.imshow("src", img)

channelsYUV = cv2.split(imgYUV)
channelsYUV[0] = cv2.equalizeHist(channelsYUV[0])

channels = cv2.merge(channelsYUV)
result = cv2.cvtColor(channels, cv2.COLOR_YCrCb2BGR)
cv2.imshow("dst", result)

cv2.waitKey(0)
```

## 2. python + opencv 直方图拉伸

```
#coding:utf-8
'''
灰度拉伸
定义：灰度拉伸，也称对比度拉伸，是一种简单的线性点运算。作用：扩展图像的
      直方图，使其充满整个灰度等级范围内
公式：
g(x,y) = 255 / (B - A) * [f(x,y) - A],
其中，A = min[f(x,y)],最小灰度级；B = max[f(x,y)],最大灰度级；
     f(x,y)为输入图像,g(x,y)为输出图像

缺点：如果灰度图像中最小值A=0，最大值B=255，则图像没有什么改变

'''

import cv2
import numpy as np

def grey_scale(image):
    img_gray = cv2.cvtColor(image,cv2.COLOR_RGB2GRAY)
    
    rows,cols = img_gray.shape
    flat_gray = img_gray.reshape((cols * rows,)).tolist()
    A = min(flat_gray)
    B = max(flat_gray)
    print('A = %d,B = %d' %(A,B))
    output = np.uint8(255 / (B - A) * (img_gray - A) + 0.5)
    return output

src = cv2.imread('datas/f4.jpg')
result = grey_scale(src)
cv2.imshow('src',cv2.cvtColor(src,cv2.COLOR_BGR2GRAY))
cv2.imshow('result',result)

cv2.waitKey()
cv2.destroyAllWindows()
```

