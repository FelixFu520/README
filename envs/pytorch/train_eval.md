# Pytorch中train和eval模式的区别

⌚️: 2020年8月9日

📚参考

---

## 前言：

在使用Pytorhch框架时总会看见在模型训练前会加上model.trian(), 而在模型测试或者验证之前则会加上model.eval(), 那这两者之间有什么区别了？？

## model.eval()

我们来看看官方的解释：由于在验证或者测试时，我们不需要模型中的某些层起作用（比如:Dropout层），也不希望某些层的参数被改变（i.e. BatchNorm的参数），这时就需要设置成**model.eval()**模式

## model.train()

但是在训练模型的时候又希望这些层起作用，所以又要重新将这些层设置回来，这时候就需要用到**model.train()**模式

## torch.no_grad()

在模型测试或者验证时还需要使用到一个函数：torch.no_grad()。

作用：
禁用梯度计算的上下文管理器。

解释：
当在模型推断（val/test）时，我们不会调用反向传播。这时禁止计算梯度， 它将减少原本需要require_grad = True的计算的内存消耗。在这种模式下，即使输入具有require_grad = True，每次计算的结果也将具有require_grad = False。

代码示例：

>x = torch.tensor([1], requires_grad=True)
>with torch.no_grad():
>...   y = x * 2
>y.requires_grad
>False
>@torch.no_grad()  #用作装饰器
>... def doubler(x):
>...     return x * 2
>z = doubler(x)
>z.requires_grad
>False



## torch.enable_grad()

作用：
与torch.no_grad()的作用相反，如果梯度计算torch.no_grad()或者torch.set_grad_enabled()禁止了， 使用torch.enable_grad()将会允许梯度计算的上下文管理器。
代码示例:

>x = torch.tensor([1], requires_grad=True)
>with torch.no_grad():
>...   with torch.enable_grad():
>...     y = x * 2
>y.requires_grad
>True
>y.backward()
>x.grad
>@torch.enable_grad()
>... def doubler(x):
>...     return x * 2
>with torch.no_grad():
>...     z = doubler(x)
>z.requires_grad
>True

