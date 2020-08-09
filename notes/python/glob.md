# glob()函数的作用和用法

2020年8月9日

---

glob是python自己带的一个文件操作相关模块，用它可以查找符合自己目的的文件，类似于Windows下的文件搜索，支持通配符操作，*,?,[]这三个通配符，*代表0个或多个字符，?代表一个字符，[]匹配指定范围内的字符，如[0-9]匹配数字。两个主要方法如下。

## 1. glob方法：

glob模块的主要方法就是glob,该方法返回所有匹配的文件路径**列表**（list）；该方法需要一个参数用来指定匹配的路径字符串（字符串可以为绝对路径也可以为相对路径），其返回的文件名只包括当前目录里的文件名，不包括子文件夹里的文件。

比如：

```
glob.glob(r’c:*.txt’)
```

我这里就是获得C盘下的所有txt文件

```
glob.glob(r’E:\pic**.jpg’)
```

获得指定目录下的所有jpg文件

使用**相对路径**：

glob.glob(r’../*.py’)

## 2. iglob方法：

获取一个**迭代器**（ iterator ）对象，使用它可以逐个获取匹配的文件路径名。与glob.glob()的区别是：glob.glob同时获取所有的匹配路径，而 glob.iglob一次只获取一个匹配路径。下面是一个简单的例子：

**#父目录中所有的.py文件**

```
f = glob.iglob(r'../*.py')
print f
<generator object iglob at 0x00B9FF80>

for py in f:
    print py
```

f是一个迭代器对象，通过遍历，可以输出所有满足条件的*.py文件

官方说明：

```
glob.glob(pathname)

Return a possibly-empty list of path names that match pathname, which must be a string containing a path specification. pathname can be either absolute (like /usr/src/Python-1.5/Makefile) or relative (like http://www.cnblogs.com/Tools/*/*.gif), and can contain shell-style wildcards. Broken symlinks are included in the results (as in the shell).



glob.iglob(pathname)

Return an iterator which yields the same values as glob() without actually storing them all simultaneously.

New in version 2.5.
```

For example, consider a directory containing only the following files: 1.gif, 2.txt, andcard.gif. glob() will produce the following results. Notice how any leading components of the path are preserved.

```
>>> import glob
>>> glob.glob('./[0-9].*')
['./1.gif', './2.txt']

>>> glob.glob('*.gif')
['1.gif', 'card.gif']

>>> glob.glob('?.gif')
['1.gif']
```

