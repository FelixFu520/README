# argsort(）函数

2020年10月21日

---

第一步：先定义一个array数据 

```
import numpy as np 
x=np.array([2,4,5,3,-10,1])
```



第二步：输出结果： 

```
y=np.argsort(x) 
print(y) 
输出结果为：y=[4 5 0 3 1 2]
```



第三步：总结： 
**argsort()函数是将x中的元素从小到大排列，提取其对应的index(索引号)** 
例如：x[4]=-10最小，所以y[0]=4, 
同理：x[2]=5最大，所以y[5]=2。

看以下官方案例：

```
    One dimensional array:一维数组

    >>> x = np.array([3, 1, 2])
    >>> np.argsort(x)
    array([1, 2, 0])

    Two-dimensional array:二维数组

    >>> x = np.array([[0, 3], [2, 2]])
    >>> x
    array([[0, 3],
           [2, 2]])

    >>> np.argsort(x, axis=0) #按列排序
    array([[0, 1],
           [1, 0]])

    >>> np.argsort(x, axis=1) #按行排序
    array([[0, 1],
           [0, 1]])1234567891011121314151617181920
>>> x = np.array([3, 1, 2])
>>> np.argsort(x) #按升序排列
array([1, 2, 0])
>>> np.argsort(-x) #按降序排列
array([0, 2, 1])
```