# Python sys 模块详解

⌚️:2020年11月30日

📚参考

---

## 1. 简介

“sys”即“system”，“系统”之意。该模块提供了一些接口，用于访问 Python 解释器自身使用和维护的变量，同时模块中还提供了一部分函数，可以与解释器进行比较深度的交互。

## 2. 常用功能

### 2.1 sys.argv

“argv”即“argument value”的简写，是一个列表对象，其中存储的是在命令行调用 Python 脚本时提供的“命令行参数”。

这个列表中的第一个参数是被调用的脚本名称，也就是说，调用 Python 解释器的“命令”（`python`）本身并没有被加入这个列表当中。这个地方要注意一下，因为这一点跟 C 程序的行为有所不同，C 程序读取命令行参数是从头开始的。

举例来说，在当前目录下新建一个 Python 文件`sys_argv_example.py`，其内容为：

```
import sys

print("The list of command line arguments:\n", sys.argv)
```

在命令行运行该脚本：

```
$ python sys_argv_example.py
The list of command line arguments:
 ['example.py']
 
```

加上几个参数试试：

```
$ python sys_argv_example.py arg1 arg2 arg3
The list of command line arguments:
 ['example.py', 'arg1', 'arg2', 'arg3']
```

利用好这个属性，可以极大增强 Python 脚本的交互性。

### 2.2 sys.platform

查看`sys`模块中的`sys.platform`属性可以得到关于运行平台更详细的信息”，这里我们就来试试：

```
>>> import sys
>>> sys.platform
'win32'
```

在 Linux 上：

```
>>> sys.platform
'linux'
```

比较一下`os.name`的结果，不难发现，`sys.platform`的信息更加准确。

### 2.3 sys.byteorder

“byteorder”即“字节序”，指的是在计算机内部存储数据时，数据的低位字节存储在存储空间中的高位还是低位。

“小端存储”时，数据的低位也存储在存储空间的低位地址中，此时`sys.byteorder`的值为`“little”`。如果不注意，在按地址顺序打印内容的时候，可能会把小端存储的内容打错。当前**大部分机器**都是使用的小端存储。

所以不出意外的话，你的机器上执行下述交互语句也应当跟我的结果一样：

```
>>> sys.byteorder
'little'
```

而另外还存在一种存储顺序是“大端存储”，即数据的高位字节存储在存储空间的低位地址上，此时`sys.byteorder`的值为`“big”`。

这种方式看起来好像很合理也很自然，因为我们一般在书面表示的时候都将低位地址写在左边，高位地址写在右边，大端存储的顺序就很符合人类的阅读习惯。但实际上对机器而言，内存地址并没有左右之分，所谓的“自然”其实并不存在。

抱歉我并没有使用大端存储的机器可以用作演示，因此只能说如果是大端存储的机器上运行 Python，输出结果应该像下面这样，也就是说下面这个示例并非我得到的真实运行结果，仅供参考：

```
>>> sys.byteorder
'big'
```

### 2.4 sys.executable

该属性是一个字符串，在正常情况下，其值是当前运行的 Python 解释器对应的可执行程序所在的绝对路径。

比如在 Windows 上使用 Anaconda 安装的 Python，该属性的值就是：

```
>>> sys.executable
'E:\\Anaconda\\Anaconda\\python.exe'
```

### 2.5 sys.modules

该属性是一个字典，包含的是各种已加载的模块的模块名到模块具体位置的映射。

通过手动修改这个字典，可以重新加载某些模块；但要注意，切记不要大意删除了一些基本的项，否则可能会导致 Python 整个儿无法运行。

关于其具体的值，由于内容过多，就不在此给出示例了，读者可以自行查看。

### 2.6 sys.builtin_module_names

该属性是一个字符串元组，其中的元素均为当前所使用的的 Python 解释器内置的模块名称。

注意区别`sys.modules`和`sys.builtin_module_names`——前者的关键字（keys）列出的是导入的模块名，而后者则是解释器内置的模块名。

其值示例如下：

```
>>> sys.builtin_module_names
('_abc', '_ast', '_bisect', '_blake2', '_codecs', '_codecs_cn', '_codecs_hk', '_codecs_iso2022', '_codecs_jp', '_codecs_kr', '_codecs_tw', '_collections', '_contextvars', '_csv', '_datetime', '_functools', '_heapq', '_imp', '_io', '_json', '_locale', '_lsprof', '_md5', '_multibytecodec', '_opcode', '_operator', '_pickle', '_random', '_sha1', '_sha256', '_sha3', '_sha512', '_signal', '_sre', '_stat', '_string', '_struct', '_symtable', '_thread', '_tracemalloc', '_warnings', '_weakref', '_winapi', 'array', 'atexit', 'audioop', 'binascii', 'builtins', 'cmath', 'errno', 'faulthandler', 'gc', 'itertools', 'marshal', 'math', 'mmap', 'msvcrt', 'nt', 'parser', 'sys', 'time', 'winreg', 'xxsubtype', 'zipimport', 'zlib')
```

### 2.7 sys.path

A list of strings that specifies the search path for modules. Initialized from the environment variable [`PYTHONPATH`](https://docs.python.org/3/using/cmdline.html#envvar-PYTHONPATH), plus an installation-dependent default.

该属性是一个由字符串组成的列表，其中各个元素表示的是 Python 搜索模块的路径；在程序启动期间被初始化。

其中第一个元素（也就是`path[0]`）的值是最初调用 Python 解释器的脚本所在的绝对路径；如果是在交互式环境下查看`sys.path`的值，就会得到一个空字符串。

命令行运行脚本（脚本代码见示例 `sys_path_example.py`）：

```
$ python sys_path_example.py
The path[0] =  D:\justdopython\sys_example
```

交互式环境查看属性第一个元素：

```
>>> sys.path[0]
''
```

> python程序中使用 import XXX 时，python解析器会在当前目录、已安装和第三方模块中搜索 xxx，如果都搜索不到就会报错。使用sys.path.append()方法可以临时添加搜索路径，方便更简洁的import其他包和模块。这种方法导入的路径会在python程序退出后失效。
>
> 1. 加入上层目录和绝对路径
>
> ```python
> import sys
> sys.path.append('..') #表示导入当前文件的上层目录到搜索路径中
> sys.path.append('/home/model') # 绝对路径
> from folderA.folderB.fileA import functionA
> ```
>
> 2. 加入当前目录
>
> ```python
> import os,sys
> sys.path.append(os.getcwd())
> ```
>
> os.getcwd()用于获取当前工作目录
>
> 3. 定义搜索优先顺序
>
> ```python
> import sys
> sys.path.insert(1, "./model")
> ```
>
> sys.path.insert(1, "./crnn")定义搜索路径的优先顺序，序号从0开始，表示最大优先级，sys.path.insert()加入的也是临时搜索路径，程序退出后失效。

## 3. 进阶功能

### 3.1 sys.stdin

即 Python 的标准输入通道。通过改变这个属性为其他的类文件（file-like）对象，可以实现输入的重定向，也就是说可以用其他内容替换标准输入的内容。

所谓“标准输入”，实际上就是通过键盘输入的字符。

在示例（`sys_stdin_example.py`）中，我们尝试把这个属性的值改为一个打开的文件对象`hello_python.txt`，其中包含如下的内容：

```none
Hello Python!
Just do Python, go~

Go, Go, GO!
```

由于`input()`使用的就是标准输入流，因此通过修改`sys.stdin`的值，我们使用老朋友`input()`函数，也可以实现对文件内容的读取，程序运行效果如下：

```
$ python sys_stdin_example.py
Hello Python!
Just do Python, go~

Go, Go, GO!
```

### 3.2 sys.stdout

与上一个“标准输入”类似，`sys.stdout`则是代表“标准输出”的属性。

通过将这个属性的值修改为某个文件对象，可以将本来要打印到屏幕上的内容写入文件。

比如运行示例程序`sys_stdout_example.py`，用来临时生成日志也是十分方便的：

```
import sys


# 以附加模式打开文件，若不存在则新建
with open("count_log.txt", 'a', encoding='utf-8') as f:
    sys.stdout = f
    for i in range(10):
        print("count = ", i)
```

### 3.3 sys.err

与前面两个属性类似，只不过该属性标识的是标准错误，通常也是定向到屏幕的，可以粗糙地认为是一个输出错误信息的特殊的标准输出流。由于性质类似，因此不做演示。

此外，`sys`模块中还存在几个“私有”属性：`sys.__stdin__`，`sys.__stdout__`，`sys.__stderr__`。这几个属性中保存的就是最初定向的“标准输入”、“标准输出”和“标准错误”流。在适当的时侯，我们可以借助这三个属性将`sys.stdin`、`sys.stdout`和`sys.err`恢复为初始值。

### 3.4 sys.getrecursionlimit() 和 sys.setrecursionlimit()

`sys.getrecursionlimit()`和`sys.setrecursionlimit()`是成对的。前者可以获取 Python 的最大递归数目，后者则可以设置最大递归数目。因为初学阶段很少用到，因此只做了解。

### 3.5 sys.getrefcount()

在《[第12天：Python 之引用](http://www.justdopython.com/2019/09/12/python-reference-012)》中我们其实已经用到过这个函数，其返回值是 Python 中某个对象被引用的次数。关于“引用”的知识可以回去看看这篇文章。

### 3.6 sys.getsizeof()

这个函数的作用与 C 语言中的`sizeof`运算符类似，返回的是作用对象所占用的字节数。

比如我们就可以看看一个整型对象`1`在内存中的大小：

```
>>> sys.getsizeof(1)
28
```

注意，在 Python 中，某类对象的大小并非一成不变的：

```
>>> sys.getsizeof(2**30-1)
28
>>> sys.getsizeof(2**30)
32
```

### 3.7 sys.int_info 和 sys.float_info

这两个属性分别给出了 Python 中两个重要的数据类型的相关信息。

其中`sys.int_info`的值为：

```
>>> sys.int_info
sys.int_info(bits_per_digit=30, sizeof_digit=4)
```

在文档中的解释为：

|      属性      |                             解释                             |
| :------------: | :----------------------------------------------------------: |
| bits_per_digit | number of bits held in each digit. Python integers are stored internally in base `2**int_info.bits_per_digit` |
|  sizeof_digit  |    size in bytes of the C type used to represent a digit     |

指的是 Python 以 2 的`sys.int_info.bits_per_digit`次方为基来表示整数，也就是说它是“2 的`sys.int_info.bits_per_digit`次方进制”的数。这样的数每一个为都用 C 类中的 4 个字节来存储。

换句话说，每“进 1 位”（即整数值增加2 的`sys.int_info.bits_per_digit`次方），就需要多分配 4 个字节用以保存某个整数。

因此在`sys.getsizeof()`的示例中，我们可以看到`2**30-1`和`2**30`之间，虽然本身只差了 1，但是所占的字节后者却比前者多了 4。

而`sys.float_info`的值则是：

```
>>> sys.float_info
sys.float_info(max=1.7976931348623157e+308, max_exp=1024, max_10_exp=308, min=2.2250738585072014e-308, min_exp=-1021, min_10_exp=-307, dig=15, mant_dig=53, epsilon=2.220446049250313e-16, radix=2, rounds=1)
```

其中各项具体的含义就不在这里继续展开了，感兴趣的同学可以参看[文档](https://docs.python.org/3/library/sys.html?highlight=sys.float_info#sys.float_info)和[《深入理解计算机系统》](https://book.douban.com/subject/26912767/)等讲解组成原理的书。

## 4. 一个有趣的功能

接下来让我们放松一下。

每次打开 Python 的交互式界面，我们都会看到一个提示符`>>>`。不知道你有没有想过要把这个东西换成另外的什么呢？

反正我没想过哈哈——至少在文档中看到这两个属性之前，我确实没有想过。哪两个属性呢？

就这俩货：`sys.ps1`和`sys.ps2`

所谓“ps”，应当是“prompts”的简写，即“提示符”。

这两个属性中，`sys.ps1`代表的是一级提示符，也就是进入 Python 交互界面之后就会出现的那一个`>>>`；而第二个`sys.ps2`则是二级提示符，是在同一级内容没有输入完，换行之后新行行首的提示符`...`。当然，两个属性都是字符串。

好了，知道怎么回事儿就好办了。

现在我们就来一个：

```
>>> sys.ps1 = "justdopython "
justdopython li = [1,2,3]
justdopython li[0]
1
justdopython 
```

提示符已经被改变了，当然，有点长，不大美观哈哈。

咱们换一下：

```
justdopython sys.ps1 = "ILoveYou: "
ILoveYou: print("你可真是个小机灵鬼儿！")
你可真是个小机灵鬼儿！
ILoveYou:
```

有点儿意思吧？

