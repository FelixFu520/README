# np.prod函数详解

2020年8月9日

---



```
numpy.prod(a, axis=None, dtype=None, out=None, keepdims=<class 'numpy._globals._NoValue'>)
```

返回给定轴上的数组元素的乘积。

```
print(np.prod([[1, 2], [3, 4]], axis=0))	# [3 8]
print(np.prod([[1, 2], [3, 4]], axis=1))  # [ 2 12]
```

