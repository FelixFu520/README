# Python glob的使用及glob.glob的排序问题

⌚️:2021年08月13日

📚参考

---



```
【摘要】简介：      glob是python自带的一个操作文件的相关模块，由于模块功能比较少，所以很容易掌握。用它可以查找符合特定规则的文件路径名。使用该模块查找文件，只需要用到："*"，"?"，"[]"这三个匹配符 星号"*"匹配0个或多个字符 问号"?"匹配任何单个字符 "[]"匹配指定范围内的一个特定字符，如：[0-9]匹配范围内数字，[a-z]和[A-Z]匹配范围内字母 一、...
```

## 简介：

glob是python自带的一个操作文件的相关模块，由于模块功能比较少，所以很容易掌握。用它可以查找符合特定规则的文件路径名。使用该模块查找文件，只需要用到：**"\*"，"?"，"[]"**这三个匹配符

1. 星号**"\*"**匹配0个或多个字符
2. 问号**"?"**匹配任何单个字符
3. **"[]"**匹配指定范围内的一个特定字符，如：[0-9]匹配范围内数字，[a-z]和[A-Z]匹配范围内字母

## 一、glob.glob：

返回所有匹配的文件路径列表。它只有一个参数pathname，定义了文件路径匹配规则，这里可以是绝对路径，也可以是相对路径。

**1、通配符**

星号**"\*"**匹配0个或多个字符

```javascript
import glob
path = glob.glob('C:/Users/huangzh/Desktop/dir/*.txt')
print(path)
"""
结果：
[C:/Users/huangzh/Desktop/dir\\file.txt, C:/Users/huangzh/Desktop/dir\\file1.txt, C:/Users/huangzh/Desktop/dir\\file2.txt, C:/Users/huangzh/Desktop/dir\\fileA.txt, C:/Users/huangzh/Desktop/dir\\fileB.txt]
"""
```

上级目录也可以用星号替代

```javascript
import glob
path = glob.glob('C:/Users/huangzh/Desktop/*/*.*')
for file in path: print(file)
"""
结果：
C:/Users/huangzh/Desktop\dir\file.txt
C:/Users/huangzh/Desktop\dir\file1.txt
C:/Users/huangzh/Desktop\dir\file2.txt
C:/Users/huangzh/Desktop\dir\fileA.txt
C:/Users/huangzh/Desktop\dir\fileB.txt
"""
```

**2、单个字符通配符**

问号**"?"**匹配任何单个字符

```javascript
import glob
path = glob.glob('C:/Users/huangzh/Desktop/dir/file?.txt')
for file in path: print(file)
"""
结果：
C:/Users/huangzh/Desktop/dir\file1.txt
C:/Users/huangzh/Desktop/dir\file2.txt
C:/Users/huangzh/Desktop/dir\fileA.txt
C:/Users/huangzh/Desktop/dir\fileB.txt
"""
```

**3、字符范围**

**"[]"**匹配指定范围内的一个特定字符，如：[0-9]匹配范围内数字，[a-z]和[A-Z]匹配范围内字母

```javascript
import glob
path = glob.glob('C:/Users/huangzh/Desktop/dir/file[0-9].txt')
for file in path: print(file)
"""
结果：
C:/Users/huangzh/Desktop/dir\file1.txt
C:/Users/huangzh/Desktop/dir\file2.txt
"""

path = glob.glob('C:/Users/huangzh/Desktop/dir/file[A-Z].txt')
for file in path: print(file)
"""
结果：
C:/Users/huangzh/Desktop/dir\fileA.txt
C:/Users/huangzh/Desktop/dir\fileB.txt
"""
```

**一起使用**

```javascript
import glob
path = glob.glob('C:/Users/huangzh/Desktop/dir/*?.t[a-z]t')
for file in path: print(file)
"""
结果：
C:/Users/huangzh/Desktop/dir\file.txt
C:/Users/huangzh/Desktop/dir\file1.txt
C:/Users/huangzh/Desktop/dir\file2.txt
C:/Users/huangzh/Desktop/dir\fileA.txt
C:/Users/huangzh/Desktop/dir\fileB.txt
"""
```

## 二、glob.glob的排序问题

对按顺序生成的文件glob.glob是这样排序的：

```javascript
import glob
path = glob.glob('C:/Users/huangzh/Desktop/dir/*.txt')
for file in path: print(file)
"""
结果：
C:/Users/huangzh/Desktop/dir\file1.txt
C:/Users/huangzh/Desktop/dir\file10.txt
C:/Users/huangzh/Desktop/dir\file100.txt
C:/Users/huangzh/Desktop/dir\file1000.txt
C:/Users/huangzh/Desktop/dir\file2.txt
C:/Users/huangzh/Desktop/dir\file3.txt
"""
```

显然这不是理想的顺序，甚至会影响结果

所以，可以用sorted进行排序

**1、按生成时间排序：**

```javascript
import glob
import os
path = glob.glob('C:/Users/huangzh/Desktop/dir/*.txt')
print(sorted(path, key = os.path.getctime))
"""
结果：
['C:/Users/huangzh/Desktop/dir\\file1.txt', 'C:/Users/huangzh/Desktop/dir\\file2.txt', 'C:/Users/huangzh/Desktop/dir\\file3.txt', 'C:/Users/huangzh/Desktop/dir\\file10.txt', 'C:/Users/huangzh/Desktop/dir\\file100.txt', 'C:/Users/huangzh/Desktop/dir\\file1000.txt']
"""
```

**2、按大小排序：**

```javascript
import glob
import os
path = glob.glob('C:/Users/huangzh/Desktop/dir/*.txt')
sorted(path, key = os.path.getsize)
```