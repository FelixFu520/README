# Python模块搜索路径

⌚️:2021年08月06日

📚参考

---

## 一 搜索路径

最近在学习python的C++扩展（pybind11)，写完一个扩展模块之后，想要在自己的环境中以后都能自动导入这个模块，而不用手动去添加路径(修改sys.path)应该怎么弄？以前最开始学习Python的时候看过这块内容，然而时间长了总会记忆不清，就再回顾了一遍。
概括来说，Python的自动搜索路径是这样的：

1. 程序的根目录
2. PYTHONPATH环境变量设置的目录
3. 标准库的目录
4. 任何能够找到的.pth文件的内容
5. 第三方扩展的site-package目录

最终，这五个部分的拼接成为了sys.path，其中第一和第三、第五部分是自动定义的。

### 1 根目录(自动)

Python首先在根目录搜索要导入的文件。这个根目录的入口依赖于你怎么运行代码；当你运行一个程序时，这个入口就是程序运行入口(top-level script file)文件所在的目录；当你用交互式窗口期运行代码时，这个入口就是你所在的工作目录。

### 2 PYTHONPATH 目录(可配置的)

接下来，python会搜索PYTHONPATH环境变量里列出的所有目录，因为这个搜索在标准库之前，所以要小心不要覆盖一些标准库的同名模块。

### 3 标准库目录(自动)

这个没什么好说的，pyton会自动搜寻标准库模块所在的目录。

### 4 .pth文件列出的目录(可配置的)

这是用的比较少的一个python特性。它允许用户以每行一个的方式列出搜索路径，它和PYTHONPATH环境变量的不同是会在标准库路径之后搜索；而且它是针对这个python安装的，而不是针对用户的（环境变量会随着用户的不同而不同）。 那么，.pth文件应该放在哪里呢？可以通过以下代码找到.pth文件可以放置的位置：

```
import site
site.getsitepackages()
```


在我的环境中，输出如下：

`['C:\\Python27', 'C:\\Python27\\lib\\site-packages']`

### 5 Lib/site-package目录(自动)

最后，python会在搜索路径上自动加上site-packages目录，这一般是第三方扩展安装的地方，一般是由distutils工具发布的。

## 二 添加自定义路径

增加python引用库 sys.path.append()

### 方式1

当我们导入一个模块时：import  xxx，默认情况下python解析器会搜索当前目录、已安装的内置模块和第三方模块，搜索路径存放在sys模块的path中：

```
import sys
sys.path
[ '', 'C:\\Python352\\Lib\\idlelib', 'C:\\Python352\\python35.zip', 'C:\\Python352\\DLLs', 'C:\\Python352\\lib', 'C:\\Python352', 'C:\\Python352\\lib\\site-packages', 'C:\\Python352\\lib\\site-packages\\setuptools-28.6.1-py3.5.egg', 'C:\\Python352\\lib\\site-packages\\pip-8.1.2-py3.5.egg', 'C:\\Python352\\lib\\site-packages\\requests-2.11.1-py3.5.egg', 'C:\\Python352\\lib\\site-packages\\xlutils-2.0.0-py3.5.egg', 'C:\\Python352\\lib\\site-packages\\xlwt-1.1.2-py3.5.egg', 'C:\\Python352\\lib\\site-packages\\pymongo-3.3.1-py3.5-win-amd64.egg', 'C:\\Python352\\lib\\site-packages\\pytz-2016.7-py3.5.egg', 'C:\\Python352\\lib\\site-packages\\zope.interface-4.3.3-py3.5-win-amd64.egg']
```

sys.path 返回的是一个列表！
该路径已经添加到系统的环境变量了，当我们要添加自己的搜索目录时，可以通过列表的append()方法；

对于模块和自己写的脚本不在同一个目录下，在脚本开头加sys.path.append('xxx')：

```
import sys
sys.path.append(’引用模块的地址 ')
```

这种方法是运行时修改，脚本运行后就会失效的。

### 方式2

另外一种方法是：

把路径添加到系统的环境变量，或把该路径的文件夹放进已经添加到系统环境变量的路径内。环境变量的内容会自动添加到模块搜索路径中。



原文：http://www.tuicool.com/articles/EB3miqr



sys模块包含了与python解释器和它的环境有关的函数，这个你可以通过dir(sys)来查看他里面的方法和成员属性。

下面的两个方法可以将模块路径加到当前模块扫描的路径里：

sys.path.append('你的模块的名称')。

sys.path.insert(0,'模块的名称')

永久添加路径到sys.path中，方式有三，如下：



1. 将写好的py文件放到 已经添加到系统环境变量的 目录下 ；

2) 在 /usr/lib/python2.6/site-packages 下面新建一个.pth 文件(以pth作为后缀名) 
将模块的路径写进去，一行一个路径，如： vim pythonmodule.pth
/home/liu/shell/config
/home/liu/shell/base 
3) 使用PYTHONPATH环境变量
export PYTHONPATH=$PYTHONPATH:/home/liu/shell/config