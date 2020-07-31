# OS模块

2020年7月31日

---

> os 顾名思义，就是与操作系统相关的标准库。如：文件，目录，执行系统命令等。

## 1. 导入模块

os 是 python 标准库模块，随 python 一起安装，无需单独安装，可直接导入。

```python
import os
```

## 2. path 子模块

涉及与磁盘文件操作，最常使用的当属 `path` 模块了。`path` 是 `os` 的子模块，可以通过 `from os import path` 使用，也可以直接通过 `os.path` 属性的方式使用。本文，为了保持一致性，统一采用后者的书写形式。

### 2.1 exists(path)

检测文件或目录是否存在。存在返回 `True` , 不存在返回 `False` 。

```python
os.path.exists("dog.jpeg")
True
```

### 2.2 isfile(path)

判断是否为文件。是返回 `True`， 不是返回 `False`。也可以用来判断文件是否存在。

```python
os.path.isfile("dogs/")
False
```

### 2.3 isdir(path)

判断是否为目录。是返回 `True`， 不是返回 `False`。也可以用来判断目录是否存在。

```python
os.path.isdir("dogs/")
True
```

### 2.4 basename(path)

返回不包含所在目录的文件名（含扩展）。

```python
os.path.basename("dir1/dir2/file.ext")
'file.ext'
```

### 2.5 dirname(path)

返回文件所在目录。

```python
os.path.dirname("dir1/dir2/file.ext")
'dir1/dir2'
```

### 2.6 split(path)

返回一个元组。元组第一个元素为文件所在目录，第二个元素为文件名（含扩展）。等效于 `(dirname(path), basename(path))`。

```python
os.path.split("dir1/dir2/file.ext")
('dir1/dir2', 'file.ext')
```

### 2.7 splitext(path)

返回一个元组。元组第一个元素为文件所在目录和文件名（不含扩展），第二个元素为扩展名（包含 `.`）。常用来读取或更改文件扩展名。

```python
os.path.splitext("dir1/dir2/file.ext")
('dir1/dir2/file', '.ext')
```

### 2.8 join(path, *paths)

将路径不同部分拼接成一个完整的路径。等效于 `os.sep.join([path, *paths])` 。

```python
os.path.join("dir1", "dir2", "file.ext")
'dir1/dir2/file.ext'
```

### 2.9 getsize(path)

返回文件大小。单位字节。

```python
os.path.getsize("dog.jpeg")
18335
```

## 3 目录操作

### 3.1 listdir(path='.')

返回一个列表。列表为给定目录下所有文件和子目录，但不包含特殊目录 `.` 和 `..`。默认为当前目录。

```python
os.listdir("dogs")[:5]
['122.Pointer',
 '069.French_bulldog',
 '124.Poodle',
 '112.Nova_scotia_duck_tolling_retriever',
 '043.Canaan_dog']
```

### 3.2 mkdir(path, mode=0o777)

创建名为 `path` 的目录。并以数字形式指定目录权限，默认权限为 777 。

```python
os.mkdir("newdir")
```

### 3.3 makedirs(path, mode=0o777)

递归方式创建路径为 `path` 的目录。并以数字形式指定目录权限，默认权限为 777 。可以看作功能更强大的 `mkdir`，它会自动创建叶子节点目录的所有上级目录，而 `mkdir` 必须在上级目录已经存在情况下，才能创建叶子节点的目录。

```python
os.makedirs("parent/child/newdir")
```

### 3.4 rmdir(path)

删除目录。目录必须存在，并且只能删除空目录。不存在或不为空，都会异常。要想递归删除整个目录树，请使用 [shutil.rmtree()](https://link.zhihu.com/?target=https%3A//docs.python.org/zh-cn/3/library/shutil.html%23shutil.rmtree)。

```python
os.rmdir("newdir")
```

### 3.5 removedirs(path)

递归删除目录。目录必须存在，并且只能删除空目录。不存在或不为空，都会异常。与 `rmdir`不同的是，在删除了叶子节点目录后，会逐次删除上级目录，直到遇到不为空的目录。

```python
os.removedirs("parent/child/newdir")
```

### *3.6 remove(path)*

删除文件。不能删除目录，给定路径必须为文件，否则会异常。

*Warm Suggestion*: 以下复制文件的操作，推荐使用 [shutil.copyfile](https://link.zhihu.com/?target=https%3A//docs.python.org/zh-cn/3/library/shutil.html%3Fhighlight%3Dshutil%23module-shutil)。

```python
# 复制文件
with open("dog.jpeg", "rb") as f:
    content = f.read()
    with open("dog.copy.jpeg", "wb") as f2:
        f2.write(content)

# 删除文件
os.remove("dog.copy.jpeg")
```

## 4. 其他 os 接口

### 4.1 getenv(key, default=None)

获取环境变量。

```python
os.getenv("PATH")
'/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin'
```

### 4.2 get_exec_path(env=None)

返回用于搜索可执行文件的目录列表。看以看作是 `PATH` 环境变量的列表形式。

```python
os.get_exec_path()
['/usr/local/bin',
 '/usr/bin',
 '/bin',
 '/usr/sbin',
 '/sbin']
```

### 4.3 system(command)

在当前进程中，启动子进程，执行命令 command（字符串），主进程会阻塞，直到子进程执行完成。这是通过调用标准C函数 `system()` 来实现的，并且具有相同的限制。

```python
if os.name == "nt":
    command = "dir"
else:
    command = "ls -l"

os.system(command)
0
```

### 4.4 os.walk()

python中os.walk是一个简单易用的文件、目录遍历器，可以帮助我们高效的处理文件、目录方面的事情。

#### 1.载入

要使用os.walk,首先要载入该函数

可以使用以下两种方法

- import os
- from os import walk

#### 2.使用

os.walk的函数声明为:

walk(top, topdown=True, onerror=None, followlinks=False)

参数

- top 是你所要遍历的目录的地址
- topdown 为真，则优先遍历top目录，否则优先遍历top的子目录(默认为开启)
- onerror 需要一个 callable 对象，当walk需要异常时，会调用
- followlinks 如果为真，则会遍历目录下的快捷方式(linux 下是 symbolic link)实际所指的目录(默认关闭)

os.walk 的返回值是一个生成器(**generator**),也就是说我们需要不断的遍历它，来获得所有的内容。

每次遍历的对象都是返回的是一个三元组(root,dirs,files)

- root 所指的是当前正在遍历的这个文件夹的本身的地址
- dirs 是一个 list ，内容是该文件夹中所有的目录的名字(不包括子目录)
- files 同样是 list , 内容是该文件夹中所有的文件(不包括子目录)

如果topdown 参数为真，walk 会遍历top文件夹，与top文件夹中每一个子目录。

举个例子

如果我们有如下的文件结构:



```css
      a ->   b   ->   1.txt,  2.txt
             c   ->   3.txt
             d   ->   
           4.txt
           5.txt
```



```bash
for (root, dirs, files) in os.walk('a'):
    #第一次运行时，当前遍历目录为 a
    所以 root == 'a'
         dirs == [ 'b', 'c', 'd']
         files == [ '4.txt', '5.txt']
    
    。。。

    # 接着遍历 dirs 中的每一个目录
    b:  root  = 'a\\b'
        dirs  = []
        files = [ '1.txt', '2.txt']
    
    # dirs为空，返回
    # 遍历c
    c:  root  = 'a\\c'
        dirs  = []
        files = [ '3.txt' ]
    
    PS : 如果想获取文件的全路径，只需要 
    for f in files:
        path = os.path.join(root,f)
    
    # 遍历d
    d:  root  = 'a\\b'
        dirs  = []
        files = []

    遍历完毕，退出循环
```

#### 3.简单的例子

保持目录 a 的目录结构，在 b 中创建对应的文件夹,并把a中所有的文件加上后缀 _bak

```csharp
import os

Root = 'a'
Dest = 'b'

for (root, dirs, files) in os.walk(Root):
    new_root = root.replace(Root, Dest, 1)
    if not os.path.exists(new_root):
        os.mkdir(new_root)
    
    for d in dirs:
        d = os.path.join(new_root, d)
        if not os.path.exists(d):
            os.mkdir(d)
    
    for f in files:
        # 把文件名分解为 文件名.扩展名
        # 在这里可以添加一个 filter，过滤掉不想复制的文件类型，或者文件名
        (shotname, extension) = os.path.splitext(f)
        # 原文件的路径
        old_path = os.path.join(root, f)
        new_name = shotname + '_bak' + extension
        # 新文件的路径
        new_path = os.path.join(new_root, new_name)
        try:
            # 复制文件
            open(new_path, 'wb').write(open(old_path, 'rb').read())
        except IOError as e:
            print(e)
```

