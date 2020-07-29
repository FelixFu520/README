PyCUDA 安装及测试

2020年7月29日



## 1. 安装

> 依赖 Numpy
>
> 查看CUDA版本：cat /usr/local/cuda/version.txt  （目前实验CUDA版本为：CUDA Version 9.0.176）
>
> 查看cudnn版本：cat /usr/local/cuda/include/cudnn.h | grep CUDNN_MAJOR -A 2  （目前实验cudnn版本：7.0）

### 1.1 直接安装

```sh
sudo apt install python-pycuda1
or
pip install pycuda==2017.1.1  
```

  注意：pycuda查看可以看这里：[pycuda](http://www.lfd.uci.edu/~gohlke/pythonlibs/?cm_mc_uid=08085305845514542921829&cm_mc_sid_50200000=1456395916#pycuda)官网。  （参看版本之间的对应）

### 1.2 源码安装： 

Step 1 下载并解压 [PyCUDA](http://pypi.python.org/pypi/pycuda)

```sh
$ wget http://pypi.python.org/pypi/pycuda
$ tar xfz pycuda-VERSION.tar.gz12
```

Step 2 编译PyCUDA

```sh
$ cd pycuda-VERSION # if you're not there already
$ python configure.py --cuda-root=/where/ever/you/installed/cuda
$ su -c "make install"123
```

## 2. 测试

### 2.1 e.g. 1

```sh
$ cd pycuda-VERSION/test
$ python test_driver.py12
```

输出 OK 即成功. 

### 2.2 e.g. 2

```sh
$ cd pycuda-VERSION/examples
$ python test_demo.py12
```

### 2.3 e.g. 3

```python
import pycuda.autoinit
import pycuda.driver 

free_bytes, total_bytes = pycuda.driver.mem_get_info() # 查询当前显卡的总显存，可用显存
12345
```



## 参考

> [官方文档](https://documen.tician.de/pycuda/driver.html)
>
> [原文-1](https://blog.csdn.net/zziahgf/article/details/74640889)
>
> [原文-2](https://blog.csdn.net/u014365862/article/details/85338619)