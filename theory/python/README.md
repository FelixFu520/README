# Python总结

⌚️:2020年11月30日

📚参考

---



```
1 运算符
2 控制结构
3 函数
4 基本类型
5 复合类型

Python中每个东西都是对象，包括函数。

Python是弱类型， 因此Python对于一个类型数据，不会有声明->赋值->调用/使用这些步骤，只有个赋值->使用.  
Python中的变量、对象和引用的概念。类型属于对象，而不是变量

多使用dir(string);help(string.replace);


```

| 对象类型  | 分类 | 是否可变 |
| --------- | ---- | -------- |
| 数字      | 数值 | 否       |
| 字符串    | 序列 | 否       |
| 列表      | 序列 | 是       |
| 字典      | 对应 | 是       |
| 元组      | 序列 | 否       |
| 文件      | 扩展 | N/A      |
| Sets      | 集合 | 是       |
| frozenset | 集合 | 否       |
| bytearray | 序列 | 是       |

```
Collections
	*Sequences
		-Immutable
			+String
			+Unicode
			+Bytes
			+Tuple
		-Mutable
			+List
			+Bytearray
	*Mappings
		-Dictionary
	*Sets
		-Set
		-Frozenset

-------------------------	
Numbers
	*Integers
		-Integer
		-Long
		-Boolean
	*Float
		-Complex
		-Decimal
		-Fraction
		
-------------------------
Callables
	*Function
	*Generator
	*Class
	*Method
		-Bound
		-Unbound
		
-------------------------
Other
	*Module
	*Instance
	*File
	*None
	*View

-------------------------
Internals
	*Type
	*Code
	*Frame
	*Traceback

```



## 1 运算符

运算符优先级；运算符重载；

**算术运算符**

`+，-，*,**，/，//,%`

**赋值运算符**

`=，+=，-=，*=，/=，%=`

```
赋值语句

spam = "Spam" # 基本形式
spam,ham = 'yum','YUM' 	# 元组赋值运算（位置性）
[spam,ham] = ['yum','YUM'] # 列表赋值运算（位置性）
a,b,c,d = 'spam'	# 序列赋值运算，通用性
a,*b = 'spam' # 扩展的序列解包
spam = ham = 'lunch' # 多目标赋值运算
spams += 43	# 增强赋值运算
```

**比较运算符**

`<, <=, >, >=, ==, !=`

**位运算符**

`|, ^,&,<<,>>, ~`

**逻辑运算符**

` or, and, not`

**集合操作**

`+（合集），-（差集）, &, | ,`

**其他**

`x in y, x not in y` 成员关系（可迭代对象、集合）

`x is y, x is not y`对象实体测试

`isinstance(True int)`

## 2 控制结构

#### 分支

```
expression1 if y else expression2 # 三目运算符

if <test1>:
		<statements1>
elif<test2>:
		<statements2>
else:
		<statements3> 
		
```

#### 循环

while循环

```
while <test>:
		<statements1>
		pass/break/continue
else:
		<statements> # 没有碰到break时
```

for循环

```
for <target> in <object>:
		<statements>
else:
		<statements>
	
	
	
for x in range(5,-5,-1):
		pass
		
S = 'abcdefghijk'
for c in S[::2]:
		pass
```

zip&map

```
L1 = [1,2,3,4]
L2 = [5,6,7,8]
L3 = [9,10,11,12]

zip(L1,L2,L3)	# 压缩

list(map(ord,'spam'))	# 映射

# 产生偏移和元素
S = 'spam'
for (offset,item) in enumerate(S):
		print(item, 'appears at offset', offset)
		
```



## 3 函数

- def是可执行的代码，def语句是实时执行的
- def创建了一个对象并将其赋值给某一个变量名：函数名是函数的引用
- lambda创建一个对象但将其作为结果返回
- return将一个结果对象发送给调用者
- yield向调用者发回一个结果对象，但是记住它离开的地方
- global声明了一个模块级的变量并被赋值
- nonlocal声明了将要赋值的一个封闭的函数变量
- 函数是通过赋值（对象引用）传递的
- 参数、返回值以及变量并不是声明

#### 定义

```
def <name>(arg1,arg2,...,argN):
		<statements>
```

#### 调用

```
funName(arg1,...)
```

#### 参数

```
传递参数
1、参数的传递 是 通过自动将对象赋值给本地变量名来实现的
2、在函数内部的参数名的赋值不会影响调用者
3、改变函数的可变对象参数的值也许会对调用者有影响

4、不可变参数“通过值传递”进行传递
5、可变对象是通过“指针”进行传递的


参数匹配
语法								位置					解释
func(value)				调用者				常规参数：通过位置进行匹配
func(name=value)	调用者				关键字参数：通过变量名匹配
func(*sequence)		调用者				以name传递所有的对象，并作为独立的基于位置的参数
func(**dict)			调用者				以name成对的传递所有的关键字/值，并作为独立的关键字参数

def func(name)		函数				常规参数：通过位置或变量名进行匹配
def func(name=value)	函数		默认参数值，如果没有在调用中传递的话
def func(*name)		函数				匹配并收集（在元组中）所有包含位置的参数
def func(**name)	函数				匹配并收集（在字典中）所有包含位置的参数
def func(*args,name)	函数		参数必须在调用中按照关键字传递
def func(*,name=value)				(python3.0)
```

#### 匿名函数

```
由lambda表达式所返回的函数对象与由def创建并赋值后的函数对象工作起来是完全一样的，但是lambda特点如下：
1、lambda是一个表达式，而不是一个语句
2、lambda的主体是一个单个表达式，而不是一个代码块


lambda args1,args2:expression
```

#### 递归函数

```
def mysum(L):
		print(L)
		if not L:
				return 0
		else:
				return L[0] + mysum(L[1:])
```

#### 其他

```
在序列中映射函数:map
list(map((lambda x: return x + 10), [1,2,3,4]))

函数式编程工具：filter和reduce
list(filter((lambda x : x > 0), range(-5,5)))

reduce((lambda x,y:x+y), [1,2,3,4]) # 10
```



## 4 基本类型

### 动态类型

**变量、对象和引用**

```
Python是弱类型， 因此Python对于一个类型数据，不会有声明->赋值->调用/使用这些步骤，只有个赋值->使用.  1、变量创建2、变量类型3、变量使用Python中的变量、对象和引用的概念。
```

**类型属于对象，而不是变量**

**对象的垃圾收集**

**共享引用**

```
拷贝浅拷贝深拷贝
```

### 数字(数值，不可变)

`1、定义=赋值，  2、使用。 name = value`

- 整型 `1234, -24,0, 9999999999`  `0o16, 0x9ff, 0b101010`
- 浮点型 `1.23, 1. , 3.14e-10, 4.0e+210`
- 复数 `3+4j, 3.0+4.0j, 3J`
- 固定精度的十进制数
- 有理分数
- 集合
- 布尔类型
- 无穷的整数精度
- 各种数字内置函数和模块



### 其他

类型

```
Type也是一个对象，在python中类型本身也是对象类型。

type(list)
```



None

```
None也是一个对象
```



布尔

```
定义
非零为True
空或者None为False
or
bool(1)
```



## 5 复合类型

### 字符串(序列，不可变)

##### 定义

```
s = ''
s = "spam's"
S = 's\np\ta\x00m' #转义序列
s = """..."""
s = r"\temp\spam"
S = b"spam"
s = u"spam"

name = "value"
or 
name = str(other type)
```



##### 使用

```
使用变量名即可
```



##### 索引&切片—**序列操作**

```
S = "Spam"len(S)S[-1]S[10:2:-1]
```

##### 拼接—序列操作

```
s1 + s2s * 3
```



##### 迭代—**序列操作**

```
[c*2 for c in S]'spam' in S # 成员操作
```



##### 不可变性

```
不可修改字符串中的内容，只能重新创建。
```



##### 表示输出

```
"%s, eggs, and %s"  % ("spam", "SPAM")'{0},eggs, and {1}'.format("spam", "SPAM")
```



##### 类型方法

```
S.find('pa')

S.replace('pa', 'XYZ') # 不管如何操作，S的值不变，只会产生新的值

S.split(',')

S.upper()

S.isalpha()

S.rstrip()

S.isdigit()

S.lower()

S.endswith("spam")

'spam'.join(strlist)

S.encode("latin-1")




```



### 列表（序列，可变）

- 任意对象的有序集合
- 通过偏移读取（索引&切片）
- 可变长度、异构以及任意嵌套
- 属于可变序列的分类
- **对象引用数组**



##### **定义**

```
L = [123, "spam", 1.23]  or  L = list("spam"/other type) # 无固定类型约束


L = []
L = [0,1,2,3]
L = ['abc', ['def','gihi']]	#嵌套
L = list("spam") # 可迭代项目的列表，连续证书的列表
L = list(range(-4,4))


```

##### **使用**

```
通过偏移读取——索引和切片
```



##### 索引&切片—**序列操作**

```
索引返回对象，切片返回新的列表。索引和切片 主要为了获取、赋值、删除。len(L)L[i]	# 索引	L[i:j:k] # 切片L[i][j]  # 多次索引
```



##### 拼接—序列操作

```
L1 + L2 #拼接

L * 3	#重复
```



##### 迭代&解析—**序列操作**

```
for x in L :print(x)

col2 = [row[1] for row in M]

3 in L # 成员操作
```



##### 类型操作(增删改查+)

```
L.append("NI")

L.extend([5,6,7]) //尾端加入

L.insert(I,X)

L.index(1)

L.Count(X)

L.sort(key=str.lower, reverse=True) / sorted(L,key=str.lower, reverse=True)

L.reverse()

delL[k]

del L[i:j]

L.pop() / L.pop(2)

L.remove(2)

L[i:j] = []

2 in L
```



##### 列表嵌套

```

```



### 字典（对应，可变）

- 通过键而不是偏移量来读取
- 任意对象的无序集合
- 可变长、异构、任意嵌套
- 属于可变映射类型
- 对象引用表



##### **定义**

```
D = {}D = {'food':"Spam", 'quanitity':4, ...}D = dict.fromkeys(['a','b'])D = dict(zip(keyslist, valslist))D = dict(name='Bob', age=42)字典嵌套rec = {'name':{'first':'Bob', 'last':"Smith"},			 'job':['dev', 'mgr'],			 'age':40.5}			 
```



##### **使用**（增删改查+）

```
name = D["name"]["first"]
```



##### **迭代和解析**

```
D = {x: x*2 for x in range(10)}D = {k:v for (k,v) in zip(['a', 'b', 'c'], [1,2,3])}
```



##### 类型操作（增删改查+）

```
D.keys()	# 键
D.values()	#值
D.items()	#键+值

D["one"] = “asdf“ # 增加、修改
D.copy()	#副本
D.get(key,default)
D.update(D2)	#合并
D.pop(key)	#删除
len(D)
D[key] = 42 # 新增/修改、删除键

del D[key]
list(D.keys())

D1.keys() & D2.keys()

"ham" in D
```



### 元组（序列，不可变）

- 任意对象的有序集合
- 通过偏移存取
- 属于不可变序列类型
- 固定长度、异构、任意嵌套
- 对象引用的数组

##### 定义

```
()
T = (9,) # 如果T = （9）则表示T是个整型
T = (0, "Ni", 1.2 , 3)
T = o, "Ni", 1.2, 3
T = ('abc',('def', 'ghi')) #嵌套元组
T = tuple('spam') # 一个可迭代对象的项的元组
```

##### 使用

```
T[i]
T[i][j]
```

##### 索引&切片—序列操作

```
len(T)
T[i:j]

```

##### 拼接—序列操作

```
T1 + T2
T1 * 3
```

##### 迭代—序列操作

```
for x in T:print(x)

[x**2 for x in T]

'spam' in T # 成员关系
```



##### 类型操作

```
T.index（‘Ni')T.count("ni")
```





### 集合（集合，可变）

##### 定义

```
s = 
```





### 类

#### 封装/定义

```
class className(Object):		def __init__():				pass						def funcs():				pass
```

#### 多态

**运算符重载**

```
方法						重载							调用
__init__				构造函数					对象建立：X = Class(args)
__del__					析构函数					X对象回收
__add__					运算符+					 如果没有_iadd_，X+Y，X+=Y

....


```

**函数重载**

```

```



#### 继承



### 文件（扩展）

```
output = open(r"/root/test.txt", 'w') # 创建输出文件
input = open(r"path", 'r') 	# 创建输入文件

aString = input.read()	# 把整个文件读进单一字符串
aString = input.read(N)  # 读取之后的N个字节到一个字符串
aString = input.readline()	# 读取下一行到一个字符串
aList = input.readlines()	# 读取整个文件到字符串列表

output.write(aString) # 写入字节到文件
output.writelines(aList) # 把列表内所有字符串写入文件
ouput.close()	# 手动关闭
output.flush() # 把输出缓冲区刷到硬盘中，但不关闭文件

anyFile.seek(N)	# 修改文件位置到偏移量N处以便进行下一个操作

for line in open('data'):use line 	# 文件迭代器一行一行地读取

open('f.txt', encoding='latin-1')	# Python3.0 Unicode文本文件（str字符串）
open('f.bin', 'rb')	# Python3.0二进制byte文件（bytes字符串）
```



### 迭代器

##### [概念](https://juejin.cn/post/6844903834381189127)

```
1、可迭代对象简单的说，一个对象(在Python里面一切都是对象)只要实现了只要实现了__iter__()方法，那么用isinstance()函数检查就是Iterable对象;常见的可迭代对象    集合或序列类型（如list、tuple、set、dict、str）    文件对象    在类中定义了__iter__()方法的对象，可以被认为是 Iterable对象，但自定义的可迭代对象要能在for循环中正确使用，就需要保证__iter__()实现必须是正确的（即可以通过内置iter()函数转成Iterator对象。关于Iterator下文还会说明，这里留下一个坑，只是记住iter()函数是能够将一个可迭代对象转成迭代器对象，然后在for中使用）。要在for循环中使用，就必须满足iter()的调用(即调用这个函数不会出错，能够正确转成一个Iterator对象)    在类中实现了如果只实现__getitem__()的对象可以通过iter()函数转化成迭代器但其本身不是可迭代对象。所以当一个对象能够在for循环中运行，但不一定是Iterable对象。2、迭代器当我们对可迭代的概念了解后，对于迭代器就比较好理解了。 一个对象实现了__iter__()和__next__()方法，那么它就是一个迭代器对象。一个迭代器(Iterator)对象不仅可以在for循环中使用，还可以通过内置函数next()函数进行调用集合和序列对象是可迭代的但不是迭代器文件对象是迭代器
```



##### 格式

```
for x in iterable：
		<statements>
		
L = [x + 10 for x in L if ...]

for line in open('test.txt').readlines():
		pass
		
		
		

		
iterable:序列类型（列表、元组、字符串）、文件、
iterator:range、map、zip、filter

		
```

##### 迭代对象和迭代器

```
python提供了一个内置对象next，他会自动调用一个对象的__next__方法，即next(X) 等价于X.__next()__，X是可迭代对象。

iter可以将一个可迭代对象生成一个迭代器

L = [1,2,3]
I = iter(L)
I.next() # 1
I.next() # 2
I.next() # 3
```





### 生成器

##### 概念

```
一个生成器既是可迭代的也是迭代器

定义生成器有两种方式：
    列表生成器
    使用yield定义生成器函数
    
    
列表生成器
		g = (x * 2 for x in range(10)) # 0～18的偶数生成器 
    print(isinstance(g, Iterable)) # true
    print(isinstance(g, Iterator)) # true
    print(isinstance(g, Generator)) # true
    print(hasattr(g, "__iter__")) # true
    print(hasattr(g, "__next__")) # true
    print(next(g)) # 0
    print(next(g)) # 2
    列表生成器可以不需要消耗大量的内存来生成一个巨大的列表，只有在需要数据的时候才会进行计算。
    
使用yield定义生成器函数
    def gen():
        for i in range(10):
            yield i 
		当程序遇到yield关键字时，这个生成器函数就返回了，直到再次执行了next()函数，它就会从上次函数返回的执行点继续执行，即yield退出时保存了函数执行的位置、变量等信息，再次执行时，就从这个yield退出的地方继续往下执行。
```



### 装饰器

#### 概念

```
装饰是为函数和类制定管理代码的一种方式。装饰器本身的形式是处理其他的可调用对象的对象（如函数）。
```



### 模块

```
import *.*
from * import *

为什么使用模块
1、代码重用
2、系统命名空间的划分
3、实现共享服务和数据

模块搜索路径
1、程序的主目录
2、PYTHONPATH目录（如果已经进行了设置）
3、标准链接库目录
4、任何.pth文件的内容（如果存在的话）

sys.path列表

```



### 文档

```
dir函数								对象中可用属性的列表
文档字符串:__doc__			附在对象上的文件中的文档
PyDoc：help函数			 对象的交互帮助
```



## 6 其他

#### 引用VS拷贝

```
赋值操作总是存储对象的引用，而不是这些对象的拷贝。

明确的拷贝操作
1、没有限制条件的分片表达式(L[:])能够复制序列
2、字典copy方法（X.copy()）能够复制字典
3、有些内置函数（例如，list）能够生成拷贝（list(L)）
4、copy标准库模块能够生成完成拷贝
```

#### 比较、相等性和真值

```
"=="操作符测试值的相等性。Python运行相等测试，递归地比较所有内嵌对象。
"is"表达式测试对象的一致性。 Python测试两者是否是同一个对象（也就是说，在同一个内存地址中）。
```

#### 作用域

```
变量名解析：LEGB原则
当发现变量时，LEGB范围去搜索
Local(function)：本地作用域
Enclosing function locals：上一层结构中def或lambda的本地作用域
Global(module)：全局作用域
Built-in(Python)：内置作用域


X = 00
def func():
		global X
		X = 88
		
		
def tester(start):
		state = start
		def nested(label):
				nonlocal state
				print(label, state)
				state += 1
		return nested
F = tester(0)
F('spam') # spam 0
F('ham')  # ham 1
F('eggs') # eggs 2
```

#### 异常

```
try:
	pass
except name1,name2:
	pass
except:
	pass
else:
	pass
finally:
	pass
	

raise 	IndexError


assert


with expression [as variable]:
		with-block
```

