# Python计算中位数 numpy.median

2020年11月20日

---

numpy模块下的median作用为：
计算沿指定轴的中位数
返回数组元素的中位数

其函数接口为：

```
median(a, 
       axis=None, 
       out=None,
       overwrite_input=False, 
       keepdims=False)
```

其中各参数为：
a：输入的数组；
axis：计算哪个轴上的中位数，比如输入是二维数组，那么axis=0对应行，axis=1对应列，如果对于二维数组不指定长度，将拉伸为一唯计算中位数；
out：用于放置求取中位数后的数组。 它必须具有与预期输出相同的形状和缓冲区长度；
overwrite_input :一个bool型的参数，默认为Flase。如果为True那么将直接在数组内存中计算，这意味着计算之后原数组没办法保存，但是好处在于节省内存资源，Flase则相反；
keepdims：一个bool型的参数，默认为Flase。如果为True那么求取中位数的那个轴将保留在结果中；

```
>>> a = np.array([[10, 7, 4], [3, 2, 1]])
>>> a
array([[10,  7,  4],
       [ 3,  2,  1]])
       
       
>>> np.median(a)
# 1，2，3，4，7，10 
# (3+4)/2 = 3.5
3.5


>>> np.median(a, axis=0)
#(10+3)/2 = 6.5
#(7+2)/2 = 4.5
#(4+1)/2 = 2.5 
array([ 6.5,  4.5,  2.5])


>>> np.median(a, axis=1)
#奇数个数中位数
array([ 7.,  2.])


>>> m = np.median(a, axis=0)
>>> out = np.zeros_like(m)
>>> np.median(a, axis=0, out=m)
array([ 6.5,  4.5,  2.5])

>>> m
array([ 6.5,  4.5,  2.5])
>>> b = a.copy()
>>> np.median(b, axis=1, overwrite_input=True)
array([ 7.,  2.])

>>> assert not np.all(a==b)
>>> b = a.copy()
>>> np.median(b, axis=None, overwrite_input=True)
3.5
```

