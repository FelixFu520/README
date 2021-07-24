# transpose & permute

⌚️: 2020年8月9日

📚参考

---

## transpose

两个维度互换

代码如下：

```
torch.manual_seed(1)
x = torch.randn(2,3)
print(x)
```

原来x的结果：

```
 0.6614  0.2669  0.0617
 0.6213 -0.4519 -0.1661
[torch.FloatTensor of size 2x3]
```

将x的维度互换

```
x.transpose(0,1)
```

结果

```
0.6614  0.6213
 0.2669 -0.4519
 0.0617 -0.1661
[torch.FloatTensor of size 3x2]
```

## tpermute

多个维度互换，更灵活的transpose

permute是更灵活的transpose，可以灵活的对原数据的维度进行调换，而数据本身不变。
代码如下：

```
x = torch.randn(2,3,4)
print(x.size())
x_p = x.permute(1,0,2) # 将原来第1维变为0维，同理，0→1,2→2
print(x_p.size())
```

结果：

```
torch.Size([2, 3, 4])
torch.Size([3, 2, 4])
```

## 