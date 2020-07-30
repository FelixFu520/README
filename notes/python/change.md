# Python 字符串前面加u,r,b,f的含义

2020年7月30日

---

## 1、字符串前加 u

例：u"我是含有中文字符组成的字符串。"

作用：

后面字符串以 Unicode 格式 进行编码，一般用在中文字符串前面，防止因为源码储存格式问题，导致再次使用时出现乱码。

 

## 2、字符串前加 r

例：r"\n\n\n\n”　　# 表示一个普通生字符串 \n\n\n\n，而不表示换行了。

作用：

去掉反斜杠的转移机制。

（特殊字符：即那些，反斜杠加上对应字母，表示对应的特殊含义的，比如最常见的”\n”表示换行，”\t”表示Tab等。 ）

应用：

常用于正则表达式，对应着re模块。

 

## 3、字符串前加 b

例: response = b'<h1>Hello World!</h1>'   # b' ' 表示这是一个 bytes 对象

作用：

b" "前缀表示：后面字符串是bytes 类型。

用处：

网络编程中，服务器和浏览器只认bytes 类型数据。

如：*send 函数的参数和 recv 函数的返回值都是 bytes 类型*

附：

在 Python3 中，bytes 和 str 的互相转换方式是
str.encode('utf-8')
bytes.decode('utf-8')



## 4、字符串前加 f

import time
t0 = time.time()
time.sleep(1)
name = 'processing'

*# 以 **f**开头表示在字符串内支持大括号内的python 表达式*
print(f'{name} done in {time.time() - t0:.2f} s') 

**输出：**
processing done in 1.00 s

 