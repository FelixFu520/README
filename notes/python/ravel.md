# ravel()、flatten()、squeeze()

2020年8月9日

---

numpy中的ravel()、flatten()、squeeze()都有将多维数组转换为一维数组的功能，区别： 

- ravel()：如果没有必要，不会产生源数据的副本
- flatten()：返回源数据的副本 
- squeeze()：只能对维数为1的维度降维

另外，reshape(-1)也可以“拉平”多维数组

```
arr = np.arange(12).reshape(3, 4)

arr
```

```
array([[ 0,  1,  2,  3],
       [ 4,  5,  6,  7],
       [ 8,  9, 10, 11]])
```



```
arr.ravel()
```

```
array([ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11])
```



```
arr.flatten()
```

```
array([ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11])
```



```
arr1 = np.arange(3).reshape(3, 1)
arr1
```

```
array([[0],
       [1],
       [2]])
```



```
np.squeeze(arr1)
```

```
array([0, 1, 2])
```



```
arr.reshape(-1)
```

```
array([ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11])
```

