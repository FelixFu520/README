# dir()和vars()的区别

2020年8月9日

---

dir():默认打印当前模块的所有属性，如果传一个对象参数则打印当前对象的属性

vars():默认打印当前模块的所有属性，如果传一个对象参数则打印当前对象的属性



vars():函数以字典形式返回参数中每个成员的当前值，如果vars函数没有带参数,那么它会返回包含当前局部命名空间中所有成员的当前值的一个字典。

\>>> help(vars)
Help on built-in function vars in module __builtin__:
vars(...)
  vars([object]) -> dictionary 
  Without arguments, equivalent to locals().
  With an argument, equivalent to object.__dict__.

**dir()和vars()的区别就是：dir()只打印属性，vars()则打印属性与属性的值。**



```python
a='abcdefg'
class B():
    c='djfj'
 
print dir()
print vars()
print dir(B)
print vars(B)
```

结果：
['B', '__builtins__', '__doc__', '__file__', '__name__', '__package__', 'a']
{'a': 'abcdefg', 'B': <class __main__.B at 0x02A2DD88>, '__builtins__': <module '__builtin__' (built-in)>, '__file__': 'E:\\workspace\\python day03\\main\\test.py', '__package__': None, '__name__': '__main__', '__doc__': None}
['__doc__', '__module__', 'c']
{'__module__': '__main__', 'c': 'djfj', '__doc__': None}



```python
>>> class C(object):
	    f=2
 
	
>>> dir(C)
['__class__', '__delattr__', '__dict__', '__doc__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', 'f']
>>> vars(C)
dict_proxy({'__dict__': <attribute '__dict__' of 'C' objects>, '__module__': '__main__', '__weakref__': <attribute '__weakref__' of 'C' objects>, '__doc__': None, 'f': 2})
>>> C.__dict__
dict_proxy({'__dict__': <attribute '__dict__' of 'C' objects>, '__module__': '__main__', '__weakref__': <attribute '__weakref__' of 'C' objects>, '__doc__': None, 'f': 2})
>>> c=C()
>>> dir(c)
['__class__', '__delattr__', '__dict__', '__doc__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', 'f']
>>> vars(c)
{}
>>> c.__dict__
{}
>>> 


```


