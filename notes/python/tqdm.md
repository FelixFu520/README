# tqdm

2020年7月31日

---

## 一、简介

tqdm是Python中专门用于进度条美化的模块，通过在非while的循环体内嵌入tqdm，可以得到一个能更好展现程序运行过程的提示进度条，本文就将针对tqdm的基本用法进行介绍。

## 二、基本用法

**tqdm**:

tqdm中的tqdm()是实现进度条美化的基本方法，在for循环体中用tqdm()包裹指定的迭代器或range()即可，下面是两个简单的例子：

```javascript
from tqdm import tqdm
import time

text = ""
for char in tqdm(["a", "b", "c", "d"]):
    time.sleep(0.25)
    text = text + char
    
print(text)
```

```
100%|████████████████████████████████████████████████████████████████| 4/4 [00:01<00:00,  3.99it/s]
abcd

```



传入range()：

```javascript
for it in tqdm(range(10)):
    time.sleep(0.5)
```

```
100%|████████████████████████████████████████████████████████████████| 4/4 [00:01<00:00,  3.99it/s]
```



**trange**：

作为tqdm(range())的简洁替代，如下例：

```javascript
from tqdm import trange

for i in trange(100):
    time.sleep(0.01)
```

```
100%|████████████████████████████████████████████████████████████████| 4/4 [00:01<00:00,  3.99it/s]
```



 也可以使用一些较为高级的写法使得代码更简练，如下面两种写法，得到的效果相同：

```javascript
'''method 1'''
with tqdm(total=100) as pbar:
    for i in range(10):
        time.sleep(0.1)
        pbar.update(10)

'''method 2'''
pbar = tqdm(total=100)
for i in range(10):
    time.sleep(0.1)
    pbar.update(10)
pbar.close()
```

```
100%|████████████████████████████████████████████████████████████████| 4/4 [00:01<00:00,  3.99it/s]
```



**结合jupyter notebook**：

tqdm针对jupyter notebook添加了专门的进度条美化方法，使用tqdm_notebook()方法，下面是一个简单的例子：

```javascript
from tqdm import tqdm_notebook
import time

for i in tqdm_notebook(range(100),desc='demo：'):
    time.sleep(0.01)
```

```
100%|████████████████████████████████████████████████████████████████| 4/4 [00:01<00:00,  3.99it/s]
```

