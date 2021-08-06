# Python & C++混合编程

⌚️:2021年08月06日

📚参考

- https://github.com/pybind/pybind11
- https://pybind11.readthedocs.io/en/stable/index.html
- https://blog.csdn.net/u012483097/article/details/108797976
- https://www.freesion.com/article/61461281946/

---



python调用C/C++有不少的方法，如boost.python, swig, ctypes, pybind11等，这些方法有繁有简，而pybind11的优点是对C++ 11支持很好，API比较简单，现在我们就简单记下Pybind11的入门操作。

pybind11是一个轻量级的只包含头文件的库，它主要是用来在已有的 C++代码的基础上做扩展，它的语法和目标非常像Boost.Python，但Boost.Python为了兼容现有的基本所有的C++编译器而变得非常复杂和庞大，而因此付出的代价是很多晦涩的模板技巧以及很多不必要的对旧版编译器的支持。Pybind11摒弃了这些支持，它只支持python2.7以上以及C++ 11以上的编译器，使得它比Boost.Python更加简洁高效。

## 一、pybind11

### 1. 安装pybind11

```
1.pybind11的安装：
（1）先安装这些第三方库：
sudo apt-get install cmake==3.18.2（如果已经安装cmake，可以升级一下cmake：sudo pip install --upgrade cmake==3.18.2）
sudo pip install -i https://pypi.tuna.tsinghua.edu.cn/simple/  pytest


（2）安装pybind11：
a.先下载pybind11的源代码：https://github.com/pybind/pybind11
b.进入pybind源代码，并建立新文件build，进行build，cmake,make..,具体如下：
cd  that_folder
mkdir build
cd build
cmake ..
make check -j 4  (make and check, not necessary)
sudo make install  (maybe should disable python3 in /usr/bin/ if you use python2)
```

### 2. C++利用pybind11转化为python API：

（1）建立一个新文件夹example，把编译后好的pybind11-master,放在example里面，然后在example文件夹新建example.cpp,并编辑：

```
#include <pybind11/pybind11.h>
namespace py = pybind11;
 
int add(int i, int j)
{
    return i + j;
}
 
PYBIND11_MODULE(example, m)
{
    // optional module docstring
    m.doc() = "pybind11 example plugin";
    // expose add function, and add keyword arguments and default arguments
    m.def("add", &add, "A function which adds two numbers", py::arg("i")=1, py::arg("j")=2);
 
    // exporting variables
    m.attr("the_answer") = 42;
    py::object world = py::cast("World");
    m.attr("what") = world;
}
 
```



（2）在文件夹example新建CMakeList.txt,并编辑：

```
cmake_minimum_required(VERSION 3.5.1)
project(example)
#这一句一定要，编译要用release模式，不设的话，默认是debug，速度慢很多 
set(CMAKE_BUILD_TYPE "Release")
add_subdirectory(pybind11)
pybind11_add_module(example example.cpp)

```



（3）在文件夹example新建build文件夹，打开命令行窗口，并cd build，cmake，make,得到最后example的python API的so：

在命令行窗口输入：

```
import example
example.add(1,2)
```





### 3.pybind11与numpy图像数据借口和速度对比：以图像rgb转化为gray的例子。

a.编写pybind11的C++代码：

```
#include<iostream>
#include<pybind11/pybind11.h>
#include<pybind11/numpy.h>
namespace py=pybind11;
py::array_t<double> rgb_to_gray(py::array_t<unsigned char>& img_rgb)
{
	if(img_rgb.ndim()!=3)
	{
		throw std::runtime_error("RGB image must has 3 channels!");
	}
	py::array_t<unsigned char> img_gray=py::array_t<unsigned char>(img_rgb.shape()[0]*img_rgb.shape()[1]);
	img_gray.resize({img_rgb.shape()[0],img_rgb.shape()[1]});
	auto rgb=img_rgb.unchecked<3>();
	auto gray=img_gray.mutable_unchecked<2>();
	for(int i=0;i<img_rgb.shape()[0];i++)
	{
		for(int j=0;j<img_rgb.shape()[1];j++)
		{
			auto R=rgb(i,j,0);
			auto G=rgb(i,j,1);
			auto B=rgb(i,j,2);
			auto GRAY=(R*30+G*59+B*11+50)/100;
			gray(i,j)=static_cast<unsigned char>(GRAY);
		}
	}
	return img_gray;
}
PYBIND11_MODULE(example,m)
{
	m.doc()="simple demo";
	m.def("rgb_to_gray",&rgb_to_gray);
}
```



b.编写CMakeList.txt:

```
cmake_minimum_required(VERSION 3.8.12)
project(example)

add_subdirectory(pybind11)
pybind11_add_module(example example.cpp)
```



c:与rgb换成gray的python代码速度和cv2自带的cv2.cvtColor(img_rgb, cv2.COLOR_BGR2GRAY)对比：

a.python的代码：

```
import cv2
import time
import numpy as np
def rgb_to_gray(img_rgb):
        if img_rgb.shape[2]!=3:
                print('image channels is 3')
        h,w,c=img_rgb.shape
        gray=np.zeros(shape=(h,w),dtype=np.uint8)
        for i in range(h):
                for j in range(w):
                        R=img_rgb[i,j,0]
                        G=img_rgb[i,j,1]
                        B=img_rgb[i,j,2]
                        GRAY=(R*30+G*59+B*11+50)/100
                        gray[i,j]=np.uint8(GRAY)
        return gray
```



b.对比pybind11 c++的速度：

对比代码：

```
import cv2
import example
import time
import numpy as np
def rgb_to_gray(img_rgb):
	if img_rgb.shape[2]!=3:
		print('image channels is 3')
	h,w,c=img_rgb.shape
	gray=np.zeros(shape=(h,w),dtype=np.uint8)
	for i in range(h):
		for j in range(w):
			R=img_rgb[i,j,0]
			G=img_rgb[i,j,1]
			B=img_rgb[i,j,2]
			GRAY=(R*30+G*59+B*11+50)/100
			gray[i,j]=np.uint8(GRAY)
	return gray
img_rgb=cv2.imread("lena.png")
for i in range(1000):
	t1=time.clock()
	rgb_to_gray(img_rgb)
	t2=time.clock()
	print("python time:{}/s".format(t2-t1))
	print("...................................")
	t1=time.clock()
	example.rgb_to_gray(img_rgb)
	t2=time.clock()
	print("pybind11 time:{}/s".format(t2-t1))
	print("...................................")
	t1=time.clock()
	cv2.cvtColor(img_rgb, cv2.COLOR_BGR2GRAY)
	t2=time.clock()
	print("cv2.cvtColor time:{}/s".format(t2-t1))
	print("...................................")
```

c.结果和分析：

分析，用python直接写的速度最慢，cv2自带的函数最快，结论，像素级别的操作，能用cv2自带的函数就用，如果cv2没有，那就用pybind11编写c++代码转换为python API接口，像素级别的处理，python太慢了，根本原因是python的for效率太低了。
