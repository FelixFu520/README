# Python  按比例切分数据集

⌚️:2021年08月05日

📚参考

---





```
import random

def split(full_list,shuffle=False,ratio=0.2):
    n_total = len(full_list)
    offset = int(n_total * ratio)
    if n_total==0 or offset<1:
        return [],full_list
    if shuffle:
        random.shuffle(full_list)
    sublist_1 = full_list[:offset]
    sublist_2 = full_list[offset:]
    return sublist_1,sublist_2


if __name__ == "__main__":
    li = range(5)
    sublist_1,sublist_2 = split(li,shuffle=True,ratio=0.2)

    print sublist_1,len(sublist_1)
    print sublist_2,len(sublist_2)
```

