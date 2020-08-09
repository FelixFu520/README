# easydict的简单使用

2020年8月9日

---

写在前面：当遇到一个陌生的python第三方库时，可以去pypi这个主页查看描述以迅速入门！
或者

```python
import time
dir（time）
```



easydict的作用：**可以使得以属性的方式去访问字典的值**！

```python
>>> from easydict import EasyDict as edict
>>> d = edict({'foo':3, 'bar':{'x':1, 'y':2}})
>>> d.foo
3
>>> d.bar.x
1
>>> d = edict(foo=3)
>>> d.foo
3
```

解析json目录时很有用

```python
>>> from easydict import EasyDict as edict
>>> from simplejson import loads
>>> j = """{
"Buffer": 12,
"List1": [
    {"type" : "point", "coordinates" : [100.1,54.9] },
    {"type" : "point", "coordinates" : [109.4,65.1] },
    {"type" : "point", "coordinates" : [115.2,80.2] },
    {"type" : "point", "coordinates" : [150.9,97.8] }
]
}"""

>>> d = edict(loads(j))
>>> d.Buffer
12
>>> d.List1[0].coordinates[1]
54.9
```

也可以这样用

```html
>>> d = EasyDict()
>>> d.foo = 3
>>> d.foo
3
>>> d = EasyDict(log=False)
>>> d.debug = True
>>> d.items()
[('debug', True), ('log', False)]
```



```html
>>> class Flower(EasyDict):
...     power = 1
...

>>> f = Flower({'height': 12})
>>> f.power
1
>>> f['power']
1
```