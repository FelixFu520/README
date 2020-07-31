# 内置函数

2020年7月31日

---

## filter

**描述**

**filter()** 函数用于过滤序列，过滤掉不符合条件的元素，返回由符合条件元素组成的新列表。

该接收两个参数，第一个为函数，第二个为序列，序列的每个元素作为参数传递给函数进行判断，然后返回 True 或 False，最后将返回 True 的元素放到新列表中。

**语法**

以下是 filter() 方法的语法:

```
filter(function, iterable)
```

**参数**

- function -- 判断函数。
- iterable -- 可迭代对象。

**返回值**

返回列表。

------

**实例**

以下展示了使用 filter 函数的实例：

```
## 过滤出列表中的所有奇数：

#!/usr/bin/python 
# -*- coding: UTF-8 -*-  
def is_odd(n):    
		return n % 2 == 1  
		
newlist = filter(is_odd, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) 
print(newlist)
```

输出结果 ：

```
[1, 3, 5, 7, 9]
```

```
## 过滤出1~100中平方根是整数的数：

#!/usr/bin/python 
# -*- coding: UTF-8 -*-  
import math 
def is_sqr(x):
		return math.sqrt(x) % 1 == 0  
		
newlist = filter(is_sqr, range(1, 101)) 
print(newlist)
```

输出结果 ：

```
[1, 4, 9, 16, 25, 36, 49, 64, 81, 100]
```