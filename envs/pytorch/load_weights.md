# Pytorch修改预训练模型时遇到key不匹配问题

⌚️: 2021年5月6日

📚参考

- [参考-1](https://blog.csdn.net/chanbo8205/article/details/89923453)

---

最近想着修改网络的预训练模型vgg.pth，但是发现当我加载预训练模型权重到新建的模型并保存之后。在我使用新赋值的网络模型时出现了key不匹配的问题。

```
# 加载后保存（未修改网络）
base_weights = torch.load(args.save_folder + args.basenet)
ssd_net.vgg.load_state_dict(base_weights) 
torch.save(ssd_net.state_dict(), args.save_folder + 'ssd_base' + '.pth')

# 将新保存的网络代替之前的预训练模型
ssd_net = build_ssd('train', cfg['min_dim'], cfg['num_classes'])
net = ssd_net
...
if args.resume:
    ...
else:
    base_weights = torch.load(args.save_folder + args.basenet)
    #args.basenet为ssd_base.pth
    print('Loading base network...')
    ssd_net.vgg.load_state_dict(base_weights) 
```


此时会如下出错误：

Loading base network…
Traceback (most recent call last):
File “train.py”, line 264, in
train()
File “train.py”, line 110, in train
ssd_net.vgg.load_state_dict(base_weights)
…
RuntimeError: Error(s) in loading state_dict for ModuleList:
Missing key(s) in state_dict: “0.weight”, “0.bias”, … “33.weight”, “33.bias”.
Unexpected key(s) in state_dict: “vgg.0.weight”, “vgg.0.bias”, … “vgg.33.weight”, “vgg.33.bias”.

说明之前的预训练模型 key参数为"0.weight", “0.bias”，但是经过加载保存之后变为了"vgg.0.weight", “vgg.0.bias”
我认为是因为本身的模型定义文件里self.vgg = nn.ModuleList(base)这一句。
现在的问题是因为自己定义保存的模型key参数多了一个前缀。
可以通过如下语句进行修改，并加载

```
from collections import OrderedDict   #导入此模块
base_weights = torch.load(args.save_folder + args.basenet)
print('Loading base network...')
new_state_dict = **OrderedDict()**  
for k, v in base_weights.items():
    name = k[4:]   # remove `vgg.`，即只取vgg.0.weights的后面几位
    new_state_dict[name] = v 
    ssd_net.vgg.load_state_dict(new_state_dict) 
```

此时就不会再出错了。