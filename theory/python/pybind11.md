# Python & C++混合编程

⌚️:2021年08月06日

📚参考

- https://github.com/pybind/pybind11
- https://pybind11.readthedocs.io/en/stable/index.html
- https://blog.csdn.net/u012483097/article/details/108797976
- https://www.freesion.com/article/61461281946/
- 文档地址：[torch.utils.cpp_extension](https://ptorch.com/docs/8/torch-utils-cpp_extension)

---



## 一、Python与C语言混合编程：通过distutils或setuptools实现的一个简单的C扩展

这个介绍一个扩展Python组件的例子，组件是通过C语言开发的(用python的Ｃ-API实现)， 然后通过python的distutils组件安装，例子中内容来自《python cocobook》英文版，一本非常不错的书。

### 目录结构

首先目录结构如下

```
dev
|__sample.h
|__sample.c
|__subtest01
       |__pysample.c
       |__setup.py
       |__libsample.so
```

### 源码内容

sample.h

```
/* sample.h */
 
extern int gcd(int x, int y);
extern int in_mandel(double x0, double y0, int n);
extern int divide(int a, int b, int *remainder);
extern double avg(double *a, int n);
 
typedef struct Point {
    double x,y;
} Point;
 
extern double distance(Point *p1, Point *p2);
```

sample.c

```
/* sample.c */
#include <math.h>
 
/* Compute the greatest common divisor */
int gcd(int x, int y) {
    int g = y;
    while (x > 0) {
        g = x;
        x = y % x;
        y = g;
    }
    return g;
}
 
/* Test if (x0,y0) is in the Mandelbrot set or not */
int in_mandel(double x0, double y0, int n) {
  double x=0,y=0,xtemp;
  while (n > 0) {
    xtemp = x*x - y*y + x0;
    y = 2*x*y + y0;
    x = xtemp;
    n -= 1;
    if (x*x + y*y > 4) return 0;
  }
  return 1;
}
 
/* Divide two numbers */
int divide(int a, int b, int *remainder) {
  int quot = a / b;
  *remainder = a % b;
  return quot;
}
 
/* Average values in an array */
double avg(double *a, int n) {
  int i;
  double total = 0.0;
  for (i = 0; i < n; i++) {
    total += a[i];
  }
  return total / n;
}
 
/* A C data structure */
typedef struct Point {
    double x,y;
} Point;
 
/* Function involving a C data structure */
double distance(Point *p1, Point *p2) {
   return hypot(p1->x - p2->x, p1->y - p2->y);
}
```

pysample.c

```
#include "Python.h"
#include "sample.h"
 
/* int gcd(int, int) */
static PyObject *py_gcd(PyObject *self, PyObject *args) {
  int x, y, result;
 
  if (!PyArg_ParseTuple(args,"ii", &x, &y)) {
    return NULL;
  }
  result = gcd(x,y);
  return Py_BuildValue("i", result);
}
 
/* int in_mandel(double, double, int) */
static PyObject *py_in_mandel(PyObject *self, PyObject *args) {
  double x0, y0;
  int n;
  int result;
  
  if (!PyArg_ParseTuple(args, "ddi", &x0, &y0, &n)) {
    return NULL;
  }
  result = in_mandel(x0,y0,n);
  return Py_BuildValue("i", result);
}
 
/* int divide(int, int, int *) */
static PyObject *py_divide(PyObject *self, PyObject *args) {
  int a, b, quotient, remainder;
  if (!PyArg_ParseTuple(args, "ii", &a, &b)) {
    return NULL;
  }
  quotient = divide(a,b, &remainder);
  return Py_BuildValue("(ii)", quotient, remainder);
}
 
/* Module method table */
static PyMethodDef SampleMethods[] = {
  {"gcd",  py_gcd, METH_VARARGS, "Greatest common divisor"},
  {"in_mandel", py_in_mandel, METH_VARARGS, "Mandelbrot test"},
  {"divide", py_divide, METH_VARARGS, "Integer division"},
  { NULL, NULL, 0, NULL}
};
 
/* Module structure */
static struct PyModuleDef samplemodule = {
  PyModuleDef_HEAD_INIT,
  "sample",           /* name of module */
  "A sample module",  /* Doc string (may be NULL) */
  -1,                 /* Size of per-interpreter state or -1 */
  SampleMethods       /* Method table */
};
 
/* Module initialization function */
PyMODINIT_FUNC
PyInit_sample(void) {
  return PyModule_Create(&samplemodule);
}
```

setup.py

```
# setup.py
from distutils.core import setup, Extension
 
setup(name="sample", 
      ext_modules=[
        Extension("sample",
                  ["../sample.c", "pysample.c"],
                  include_dirs = ['..'],
                  )
        ]
)
```

### 编译安装

在目录subtest01下面，直接编译安装
（注意一般情况下，大家直接使用python命令即可，我使用的是自己编译的版本python372，编译过程可参考：
https://blog.csdn.net/tanmx219/article/details/86518446）

`$  python setup.py build_ext --inplace`
此时会输出一些信息，

```
running build_ext
building 'sample' extension
creating build
creating build/temp.linux-x86_64-3.7-pydebug
gcc -pthread -Wno-unused-result -Wsign-compare -g -Og -Wall -fPIC -fPIC -I.. -I/usr/local/include/python3.7dm -c ../sample.c -o build/temp.linux-x86_64-3.7-pydebug/../sample.o
gcc -pthread -Wno-unused-result -Wsign-compare -g -Og -Wall -fPIC -fPIC -I.. -I/usr/local/include/python3.7dm -c pysample.c -o build/temp.linux-x86_64-3.7-pydebug/pysample.o
gcc -pthread -shared build/temp.linux-x86_64-3.7-pydebug/../sample.o build/temp.linux-x86_64-3.7-pydebug/pysample.o -L/usr/local/lib -lpython3.7dm -o /home/matthew/dev/tutorial/subtest01/sample.cpython-37dm-x86_64-linux-gnu.so
```

此时，如果你要在subtest01目录下启动python372，是可以直接使用sample这个组件的，如，

```
$ python3
Python 3.7.2 (default, Jan 18 2019, 20:12:21) 
[GCC 7.3.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> import sample
>>> sample.gcd(35,42)
7
>>> sample.divide(42,8)
(5, 2)
>>> sample
<module 'sample' from '~/dev/tutorial/subtest01/sample.cpython-37dm-x86_64-linux-gnu.so'>
>>> exit()
```



但若要在任意目录下都能运行sample组件，则需要把组件拷贝到python的库目录下面，

```
$ sudo  cp  sample.cpython-37dm-x86_64-linux-gnu.so      /usr/local/lib/python3.7/lib-dynload/
```

测试完了就删除掉吧，没啥用

整个过程还是比较简单的。

如果你的工程项目比较大的话，相信都会综合应用一些相关的工具来实现，比如cmake，那么这些安装卸载的东西就能通过cmake脚本实现啦。

### 使用setuptools

本质上setuptools和distutils没有什么太大的不同，可以看作是distutils的增强版。所以如果你想使用setuptools，只要在setup.py中把distutils换成setuptools即可，下面我给出本演示中可以使用的完整的setup.py源码，编译安装命令仍然是上面那个：
`python setup.py build_ext --inplace`

```
# setup.py
from setuptools import setup, Extension
 
setup(name="sample", 
      ext_modules=[
        Extension("sample",
                  ["../sample.c", "pysample.c"],
                  include_dirs = ['..'],
                  )
        ]
)
```

如果你想把打包发布的话，使用命令｀python setup.py sdist｀会得到一个压缩包，拷贝到你需要的地方解压缩再｀python setup.py install｀就可以了，这个过程这里就不再展开详述了。

## 二、pybind11

python调用C/C++有不少的方法，如boost.python, swig, ctypes, pybind11等，这些方法有繁有简，而pybind11的优点是对C++ 11支持很好，API比较简单，现在我们就简单记下Pybind11的入门操作。

pybind11是一个轻量级的只包含头文件的库，它主要是用来在已有的 C++代码的基础上做扩展，它的语法和目标非常像Boost.Python，但Boost.Python为了兼容现有的基本所有的C++编译器而变得非常复杂和庞大，而因此付出的代价是很多晦涩的模板技巧以及很多不必要的对旧版编译器的支持。Pybind11摒弃了这些支持，它只支持python2.7以上以及C++ 11以上的编译器，使得它比Boost.Python更加简洁高效。

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


## 三、pytorch通过torch.utils.cpp_extension构建CUDA/C++拓展

注意这个和前面的《[Python与C语言混合编程：通过distutils或setuptools实现的一个简单的C扩展](https://blog.csdn.net/tanmx219/article/details/86665706)》不同，这个是pytorch的扩展，不是python的扩展。

在pytorch的utils中，集成了setuptools模块。

官方文档在这里：https://pytorch.org/docs/master/cpp_extension.html

中文说明在这里：https://ptorch.com/news/188.html



### torch.utils.cpp_extension.CppExtension(name, sources, *args, **kwargs)

创建一个`C++`的`setuptools.Extension`。

便捷地创建一个`setuptools.Extension`具有最小（但通常是足够）的参数来构建`C++`扩展的方法。

所有参数都被转发给`setuptools.Extension`构造函数。

例

```
>>> from setuptools import setup
>>> from torch.utils.cpp_extension import BuildExtension, CppExtension
>>> setup(
        name='extension',
        ext_modules=[
            CppExtension(
                name='extension',
                sources=['extension.cpp'],
                extra_compile_args=['-g'])),
        ],
        cmdclass={
            'build_ext': BuildExtension
        })
```

### torch.utils.cpp_extension.CUDAExtension(name, sources, *args, **kwargs)

为`CUDA/C++`创建一个`setuptools.Extension`。

创建一个`setuptools.Extension`用于构建`CUDA/C ++`扩展的最少参数（但通常是足够的）的便捷方法。这里包括`CUDA`路径，库路径和运行库。 所有参数都被转发给`setuptools.Extension`构造函数。

例

```
>>> from setuptools import setup
>>> from torch.utils.cpp_extension import BuildExtension, CppExtension
>>> setup(
        name='cuda_extension',
        ext_modules=[
            CUDAExtension(
                    name='cuda_extension',
                    sources=['extension.cpp', 'extension_kernel.cu'],
                    extra_compile_args={'cxx': ['-g'],
                                        'nvcc': ['-O2']})
        ],
        cmdclass={
            'build_ext': BuildExtension
        })
```

### torch.utils.cpp_extension.BuildExtension（dist，** kw ）

自定义`setuptools`构建扩展。

`setuptools.build_ext`子类负责传递所需的最小编译器参数（例如`-std=c++11`）以及混合的`C ++/CUDA`编译（以及一般对`CUDA`文件的支持）。

当使用`BuildExtension`时，它将提供一个用于`extra_compile_args`（不是普通列表）的词典，通过语言（`cxx`或`cuda`）映射到参数列表提供给编译器。这样可以在混合编译期间为`C ++`和`CUDA`编译器提供不同的参数。

### torch.utils.cpp_extension.load

torch.utils.cpp_extension.load(name, sources, extra_cflags=None, extra_cuda_cflags=None, extra_ldflags=None, extra_include_paths=None, build_directory=None, verbose=False)



即时加载(JIT)`PyTorch C ++`扩展。

为了加载扩展，会创建一个`Ninja`构建文件，该文件用于将指定的源编译为动态库。随后将该库作为模块加载到当前`Python`进程中，并从该函数返回，以备使用。

默认情况下，构建文件创建的目录以及编译结果库是`<tmp>/torch_extensions/<name>`，其中`<tmp>`是当前平台上的临时文件夹以及`<name>`为扩展名。这个位置可以通过两种方式被覆盖。首先，如果`TORCH_EXTENSIONS_DIR`设置了环境变量，它将替换`<tmp>/torch_extensions`并将所有扩展编译到此目录的子文件夹中。其次，如果`build_directory`函数设置了参数，它也将覆盖整个路径，即,库将直接编译到该文件夹中。

要编译源文件，使用默认的系统编译器（c++），可以通过设置`CXX`环境变量来覆盖它。将其他参数传递给编译过程，`extra_cflags`或者`extra_ldflags`可以提供。例如，要通过优化来编译您的扩展，你可以传递`extra_cflags=['-O3']`，也可以使用 `extra_cflags`传递进一步包含目录。

提供了混合编译的`CUDA`支持。只需将`CUDA`源文件（`.cu`或`.cuh`）与其他源一起传递即可。这些文件将被检测，并且使用`nvcc`而不是`C ++`编译器进行编译。包括将`CUDA lib64`目录作为库目录传递并进行`cudart`链接。您可以将其他参数传递给`nvcc extra_cuda_cflags`，就像使用`C ++`的`extra_cflags`一样。使用了各种原始方法来查找`CUDA`安装目录，通常情况下可以正常运行。如果不可以，最好设置`CUDA_HOME`环境变量。

- 参数：
  - name - 要构建的扩展名。这个必须和`pybind11`模块的名字一样！
  - sources - `C++`源文件的相对或绝对路径列表。
  - extra_cflags - 编译器参数的可选列表，用于转发到构建。
  - extra_cuda_cflags - 编译器标记的可选列表，在构建`CUDA`源时转发给`nvcc`。
  - extra_ldflags - 链接器参数的可选列表，用于转发到构建。
  - extra_include_paths - 转发到构建的包含目录的可选列表。
  - build_directory - 可选路径作为构建区域。
  - verbose - 如果为`True`，打开加载步骤的详细记录。
- 返回：
  - 加载`PyTorch`扩展作为`Python`模块。

例

```
>>> from torch.utils.cpp_extension import load
>>> module = load(
        name='extension',
        sources=['extension.cpp', 'extension_kernel.cu'],
        extra_cflags=['-O2'],
        verbose=True)
```

### 后面还新添加了一个load_inline,不过没有中文翻译

Loads a PyTorch C++ extension just-in-time (JIT) from string sources.

This function behaves exactly like [`load()`](https://pytorch.org/docs/master/cpp_extension.html#torch.utils.cpp_extension.load), but takes its sources as strings rather than filenames. These strings are stored to files in the build directory, after which the behavior of [`load_inline()`](https://pytorch.org/docs/master/cpp_extension.html#torch.utils.cpp_extension.load_inline) is identical to [`load()`](https://pytorch.org/docs/master/cpp_extension.html#torch.utils.cpp_extension.load).

See [the tests](https://github.com/pytorch/pytorch/blob/master/test/test_cpp_extensions.py) for good examples of using this function.

Sources may omit two required parts of a typical non-inline C++ extension: the necessary header includes, as well as the (pybind11) binding code. More precisely, strings passed to `cpp_sources` are first concatenated into a single `.cpp` file. This file is then prepended with `#include <torch/extension.h>`.

Furthermore, if the `functions` argument is supplied, bindings will be automatically generated for each function specified. `functions` can either be a list of function names, or a dictionary mapping from function names to docstrings. If a list is given, the name of each function is used as its docstring.

The sources in `cuda_sources` are concatenated into a separate `.cu` file and prepended with `torch/types.h`, `cuda.h`and `cuda_runtime.h` includes. The `.cpp` and `.cu` files are compiled separately, but ultimately linked into a single library. Note that no bindings are generated for functions in `cuda_sources` per se. To bind to a CUDA kernel, you must create a C++ function that calls it, and either declare or define this C++ function in one of the `cpp_sources` (and include its name in `functions`).

See [`load()`](https://pytorch.org/docs/master/cpp_extension.html#torch.utils.cpp_extension.load) for a description of arguments omitted below.

| Parameters: | **cpp_sources** – A string, or list of strings, containing C++ source code. |
| :---------- | ------------------------------------------------------------ |
|             | **cuda_sources** – A string, or list of strings, containing CUDA source code. |
|             | **functions** – A list of function names for which to generate function bindings. If a dictionary is given, it should map function names to docstrings (which are otherwise just the function names). |
|             | **with_cuda** – Determines whether CUDA headers and libraries are added to the build. If set to `None` (default), this value is automatically determined based on whether `cuda_sources` is provided. Set it to True` to force CUDA headers and libraries to be included. |

Example

```python
>>> from torch.utils.cpp_extension import load_inline
>>> source = '''
at::Tensor sin_add(at::Tensor x, at::Tensor y) {
  return x.sin() + y.sin();
}
'''
>>> module = load_inline(name='inline_extension',
                         cpp_sources=[source],
                         functions=['sin_add'])
```

### torch.utils.cpp_extension.include_paths(cuda=False)

获取构建`C++`或`CUDA`扩展所需的路径。

- 参数： `cuda` - 如果为True，则包含`CUDA`特定的包含路径。
- 返回： 包含路径字符串的列表。

例如：

```
from setuptools import setup
from torch.utils.cpp_extension import BuildExtension, CppExtension
 
torch.utils.cpp_extension.include_paths(cuda=False)
# 
['/usr/local/lib/python3.6/site-packages/torch/lib/include', 
'/usr/local/lib/python3.6/site-packages/torch/lib/include/TH', 
'/usr/local/lib/python3.6/site-packages/torch/lib/include/THC']
```

### torch.utils.cpp_extension.check_compiler_abi_compatibility(compiler)

验证给定的编译器是否与`PyTorch` ABI兼容。

- 参数：compiler(str) - 要检查可执行的编译器文件名(例如g++),必须在`shell`进程中可执行。
- 返回：如果编译器（可能）与`PyTorch`ABI不兼容，则为`False`，否则返回`True`。

### torch.utils.cpp_extension.verify_ninja_availability()

如果可以在[ninja](https://ninja-build.org/)上运行则返回`True`。

