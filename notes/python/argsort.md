# numpy排序

（sort、argsort、lexsort、partition、sorted）

2020年10月21日

---

python的numpy中涉及了几种简单的排序方法，在此简单介绍，以便后续使用。

------

## 一 、numpy.sort

**以下是官网上给出的该方法的简介：**

```
numpy.sort(a, axis=1, kind='quicksort', order=None)
Parameters:	a : array_like
				Array to be sorted.
			axis : int or None, optional
				Axis along which to sort. If None, the array is flattened 
				before sorting. The default is 1, which sorts along the last
				 axis.
			kind : {‘quicksort’, ‘mergesort’, ‘heapsort’}, optional
				Sorting algorithm. Default is ‘quicksort’.
			order : str or list of str, optional
				When a is an array with fields defined, this argument
				specifies which fields to compare first, second, etc. A 
				single field can be specified as a string, and not all 
				fields need be specified, but unspecified fields will still 
				be used, in the order in which they come up in the dtype, to 
				break ties.
Returns:	sorted_array : ndarray
			Array of the same type and shape as a.
```

*a*：所需排序的数组

axis：数组排序时的基准，axis=0，按列排列；axis=1，按行排列

kind：数组排序时使用的方法，其中：kind='quicksort'  为快排；kind=′mergesort′为混排；kind=′heapsort′为堆排；

order：一个字符串或列表，可以设置按照某个属性进行排序



#### 举例说明

###### 参数axis

```
import numpy as np
>>> list1 = [[4,3,2],[2,1,4]]
>>> array=np.array(list1) 
>>> array
array([[4, 3, 2],
       [2, 1, 4]])
>>> array.sort(axis=1)   
>>> array
array([[2, 3, 4],
       [1, 2, 4]])
# axis=1,说明是按照行进行排序，也就是说，每一行上的元素实现了递增，
# 如[4, 3, 2]变为了[2, 3, 4]，[2, 1, 4]变为了[1, 2, 4]
>>> array.sort(axis=0)
>>>> array
array([[1, 2, 4],
       [2, 3, 4]])
# axis=0,说明是按照列进行排序，也就是说，每一列上的元素实现了递增，
# 如[2, 1]变为了[1, 2]，[3, 2]变为了[2, 3]
>>>np.sort(array, axis=None)
array([1, 2, 2, 3, 4, 4])
# 当axis=None，将所有元素统一排序
```

###### 参数order

```
import numpy as np
>>> dtype = [('Name', 'S10'), ('Height', float), ('Age', int)]
>>> values = [('Li', 1.8, 41), ('Wang', 1.9, 38),('Duan', 1.7, 38)]
>>> a = np.array(values, dtype=dtype)
>>> np.sort(a, order='Height')  # 按照属性Height进行排序,此时参数为字符串                      
array([('Duan', 1.7, 38), ('Li', 1.8, 41),('Wang', 1.9, 38)],
      dtype=[('Name', '|S10'), ('Height', '<f8'), ('Age', '<i4')])
>>> np.sort(a, order=['Age', 'Height']) 
# 先按照属性Age排序,如果Age相等，再按照Height排序，此时参数为列表        
array([('Duan', 1.7, 38), ('Wang', 1.9, 38),('Li', 1.8, 41)],
      dtype=[('Name', '|S10'), ('Height', '<f8'), ('Age', '<i4')])
```

------

## 二 、 numpy.argsort

```
numpy.argsort(a, axis=1, kind='quicksort', order=None)
Parameters:	a : array_like
				Array to sort.
			axis : int or None, optional
				Axis along which to sort. The default is 1 (the last axis).
				If None, the flattened array is used.
			kind : {‘quicksort’, ‘mergesort’, ‘heapsort’}, optional
				Sorting algorithm.
			order : str or list of str, optional
				When a is an array with fields defined, this argument
				specifies which fields to compare first, second, etc. A
				single field can be specified as a string, and not all fields
				need be specified, but unspecified fields will still be used,
				in the order in which they come up in the dtype, to break
				ties.
Returns:	index_array : ndarray, int
				Array of indices that sort a along the specified axis. If a
				is one-dimensional, a[index_array] yields a sorted a.
123456789101112131415161718
```

*a*：所需排序的数组

axis：数组排序时的基准，axis=0，按列排列；axis=1，按行排列

kind：数组排序时使用的方法，其中：kind='quicksort'  为快排；kind=′mergesort′为混排；kind=′heapsort′为堆排；

order：一个字符串或列表，可以设置按照某个属性进行排序



#### 举例说明

###### 参数axis

```
>>>list1=[4,2,5,7,3]
>>>a=np.array(list1)
>>>a
array([4, 2, 5, 7, 3])
>>>b=np.argsort(a)
>>>b
array([1, 4, 0, 2, 3], dtype=int64)
# 列表b的元素表示的是原列表a中的元素的索引，5各元素的索引分别为0-4
# 返回的结果可以这样解读：
# 	b[0]=1，表示原列表a的最小元素的索引为1，即原列表a中的第2个元素为最小值
#	b[1]=4，表示原列表a的第二小元素的索引为4，即原列表a中的第5个元素为第二小元素
#	...
#	b[4]=3，表示原列表a中的最大元素的索引为3，即原列表a中的第4个元素为最大值

>>>list2=[[3, 2],[5, 7]]
>>>c=np.array(list2)
>>>c
array([[3, 2],[5, 7]])
>>>np.argsort(c, axis=1)
array([[1, 0],[0, 1]],dtype=int64)
# axis=1，表明按照行进行排序，即是对[3, 2]进行排序，所以得到索引为[1, 0],其他同理
>>>np.argsort(c, axis=0)
array([[0, 1],[0, 1]],dtype=int64)
# axis=0，表明按照列进行排序，即是对[3, 5]进行排序，所以得到索引为[0, 1],其他同理
```

###### 参数order

```
>>> x = np.array([(1, 0), (0, 1)], dtype=[('x', '<i4'), ('y', '<i4')])
>>> x
array([(1, 0), (0, 1)], dtype=[('x', '<i4'), ('y', '<i4')])
>>> np.argsort(x, order=('x','y'))
# 先按照x进行比较，再按照y进行比较，即是先比较1与0
array([1, 0])
>>> np.argsort(x, order=('y','x'))
# 先按照y进行比较，再按照x进行比较，即是先比较0与1
array([0, 1])
```

## 三 、 numpy.lexsort

```
numpy.argsort(a, axis=-1, kind='quicksort', order=None)
Parameters:		a : array_like
					Array to sort.
				axis : int or None, optional
					Axis along which to sort. The default is -1 (the last
					axis). If None, the flattened array is used.
				kind : {‘quicksort’, ‘mergesort’, ‘heapsort’}, optional
					Sorting algorithm.
				order : str or list of str, optional
					When a is an array with fields defined, this argument
					specifies which fields to compare first, second, etc. A
					single field can be specified as a string, and not all 
					fields need be specified, but unspecified fields will 
					still be used, in the order in which they come up in the 
					dtype, to break ties.
Returns:		index_array : ndarray, int
					Array of indices that sort a along the specified axis. If
					a is one-dimensional, a[index_array] yields a sorted a
```

*a*：所需排序的数组

axis：数组排序时的基准，axis=0，按列排列；axis=1，按行排列

kind：数组排序时使用的方法，其中：kind='quicksort'  为快排；kind=′mergesort′为混排；kind=′heapsort′为堆排；

order：一个字符串或列表，可以设置按照某个属性进行排序

#### 举例说明

```
>>> a=[1,5,1,4,3,4,4]
>>> b=[9,4,0,4,0,2,1]
>>> np.lexsort((b,a))
# b在前，a在后，即是先按照a的元素进行比较
# 如a中的最小值为两个1，其索引分别为0,2，再计较b中相应索引上的值，即9,0
# 对应的最小应是：1,0，而其对应的索引为2，所以排序后返回的结果第一个值为索引2
# 下一个最小应是：1,9，而其对应的索引为0，所以排序后返回的结果第一个值为索引0
# 以此类推...
array([2, 0, 4, 6, 5, 3, 1], dtype=int64)
>>> np.lexsort((a,b))
# a在前，b在后，即是先按照b的元素进行比较
# 如b中的最小值为两个0，其索引分别为0,4，再计较a中相应索引上的值，即1,3
# 对应的最小应是：0,1，而其对应的索引为2，所以排序后返回的结果第一个值为索引2
# 下一个最小应是：0,3，而其对应的索引为4，所以排序后返回的结果第一个值为索引4
# 以此类推...
array([2, 4, 6, 5, 3, 1, 0], dtype=int64)
>>> c=[[1,5,1,4,3,4,4],[9,4,0,4,0,2,1]]
>>> c
[[1, 5, 1, 4, 3, 4, 4], [9, 4, 0, 4, 0, 2, 1]]
>>> np.lexsort(c)
# 此种情况与先b后a的情况一致
array([2, 4, 6, 5, 3, 1, 0], dtype=int64)
```

------

## 四 、 ndarry.sort

基本与numpy.sort一致，不再介绍，详情参考：[SciPy.org](https://docs.scipy.org/doc/numpy/reference/generated/numpy.ndarray.sort.html#numpy.ndarray.sort)

------

## 五 、numpy.searchsorted

```
numpy.searchsorted(a, v, side='left', sorter=None)
Parameters:		a : 1-D array_like
					Input array. If sorter is None, then it must be sorted in
					ascending order, otherwise sorter must be an array of
					indices that sort it.
				v : array_like
					Values to insert into a.
				side : {‘left’, ‘right’}, optional
					If ‘left’, the index of the first suitable location found
					is given. If ‘right’, return the last such index. If 
					there is no suitable index, return either 0 or N (where N 
					is the length of a).
				sorter : 1-D array_like, optional
					Optional array of integer indices that sort array a into
					ascending order. They are typically the result of 
					argsort.
Returns:		indices : array of ints
					Array of insertion points with the same shape as v
```

*a*：所需排序的数组

*v*：待查询索引的元素值

side:查询索引时的方向，其中：

kind='left'为从左至右；k i n d = ′ r i g h t ′ 为从右至左

sorder：一个字符串或列表，可以设置按照某个属性进行排序

#### 举例说明

```
>>> list3=[1,2,3,4,5]
>>> np.searchsorted(list3,2)
1
# 如若要在list3中插入元素2，则应当将其插在原列表索引为1的地方，即是插在元素1的后面
>>> np.searchsorted(list3,[-5,7,4,9])
array([0, 5, 3, 5], dtype=int64)
# 如若要在list3中插入元素-5，则应当将其插在原列表索引为0的地方，即是插在元素1的前面
# 其他以此类推...

```

------

## 六 、numpy.partition(与此对应的还有argpartition)

```
numpy.partition(a, kth, axis=-1, kind='introselect', order=None)
Parameters:		a : array_like
					Array to be sorted.
				kth : int or sequence of ints
					Element index to partition by. The k-th value of the
					element will be in its final sorted position and all 
					smaller elements will be moved before it and all equal or 
					greater elements behind it. The order all elements in the 
					partitions is undefined. If provided with a sequence of 
					k-th it will partition all elements indexed by k-th of 
					them into their sorted position at once.
				axis : int or None, optional
					Axis along which to sort. If None, the array is flattened
					before sorting. The default is -1, which sorts along the 
					last axis.
				kind : {‘introselect’}, optional
					Selection algorithm. Default is ‘introselect’.
				order : str or list of str, optional
					When a is an array with fields defined, this argument
					specifies which fields to compare first, second, etc. A 
					single field can be specified as a string. Not all fields 
					need be specified, but unspecified fields will still be 
					used, in the order in which they come up in the dtype, to 
					break ties.
Returns:		partitioned_array : ndarray
					Array of the same type and shape as a
```

#### 举例说明

```
>>>list=[3,4,5,2,1]
>>>np.partition(list,3)
array([2, 1, 3, 4, 5])
# 以排序后的第3个数，即3进行分区，分区后的结果即是：
# 小于3的元素2,1位于3的前面，大于等于3的元素4,5位于3的后面
```

------

## 七 、 s o r t e d ( )

```
sorted(iterable[, cmp[, key[, reverse]]])
sorted() 函数对所有可迭代的对象进行排序操作。
	sort 与 sorted 区别：
	sort 是应用在 list 上的方法，sorted 可以对所有可迭代的对象进行排序操作。
	list 的 sort 方法返回的是对已经存在的列表进行操作，而内建函数 sorted 方法返回的是一个
	新的 list，而不是在原来的基础上进行的操作。
# sorted()可以利用参数reverse=True进行反向排序
>>>list=[3,4,2,6,1]
>>>sorted(list)
[1, 2, 3, 4, 6]
>>>sorted(list, reverse=True)
[6, 4, 3, 2, 1]
```