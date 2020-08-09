# python split()与strip()的区别

2020年8月9日

---

## 1. split()

Python **split()** 通过指定分隔符对字符串进行切片，如果参数 num 有指定值，则分隔 num+1 个子字符串

### **1.1 split() 方法语法：**

```
str.split(str="", num=string.count(str))
```

**参数解释：**

- str -- 分隔符，默认为所有的空字符，包括空格、换行(\n)、制表符(\t)等。
- num -- 分割次数。默认为 -1, 即分隔所有。

**返回值：**

返回分割后的字符串列表。



### 1.2 举例：

```python
#!/usr/bin/python
# -*- coding: UTF-8 -*-


str = "Line1-abcdef \nLine2-abc \nLine4-abcd";
print str.split( );       # 以空格为分隔符，包含 \n
print str.split(' ', 1 ); # 以空格为分隔符，分隔成两个
```

输出结果为：

```python
['Line1-abcdef', 'Line2-abc', 'Line4-abcd']
['Line1-abcdef', '\nLine2-abc \nLine4-abcd']
```

以 # 号为分隔符，指定第二个参数为 1，返回两个参数列表。

```python
#!/usr/bin/python
# -*- coding: UTF-8 -*-


txt = "Google#Runoob#Taobao#Facebook"
# 第二个参数为 1，返回两个参数列表
x = txt.split("#", 1)
print x
```

输出结果为

```
['Google', 'Runoob#Taobao#Facebook']
```

## 2. strip()

Python strip() 方法用于移除字符串头尾指定的字符（默认为空格或换行符）或字符序列。

**注意：**该方法只能删除开头或是结尾的字符，不能删除中间部分的字符。

### **2.1 strip()方法语法：**

```python
str.strip([chars])
```

**参数：**

- chars -- 移除字符串头尾指定的字符序列。

**返回值：**

返回移除字符串头尾指定的字符生成的新字符串。

**举例：**

```python
#!/usr/bin/python
# -*- coding: UTF-8 -*-


str = "00000003210Runoob01230000000"; 
print str.strip( '0' );  # 去除首尾字符 0

str2 = "   Runoob      ";   # 去除首尾空格
print str2.strip();
```

输出结果为

```python
3210Runoob0123
Runoob
```

从结果上看，可以注意到中间部分的字符并未删除。

以下例子演示了只要头尾包含有指定字符序列中的字符就删除：

```python
#!/usr/bin/python
# -*- coding: UTF-8 -*-


str = "123abcrunoob321"
print (str.strip( '12' ))  # 字符序列为 12
```

输出结果为:

```python
3abcrunoob3
```

