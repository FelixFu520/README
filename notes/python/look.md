# Python中查看变量的类型，内存地址，所占字节的大小

2020年7月30日



## 查看变量的类型

```python
#利用内置type()函数
>>> nfc=["Packers","49"]
>>> afc=["Ravens","48"]
>>> combine=zip(nfc,afc)
>>> type(combine)
<class 'zip'>
```

## 查看变量的内存地址

```
#利用内置函数id(),是以十进制显示
>>> id(nfc)
2646554913160
>>> id(afc)
2646554913544
```

## 查看变量所占字节的大小

```
>>> import sys
>>> print(sys.getsizeof(combine))
64
>>> print(sys.getsizeof(nfc))
80
>>> print(sys.getsizeof(afc))
80
```