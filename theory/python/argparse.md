# Python之Argparse模块

⌚️:2020年11月30日

📚参考

- https://docs.python.org/zh-cn/3/library/argparse.html

---

argparse 模块可以轻松编写用户友好的命令行接口。程序定义它需要的参数，然后 argparse 将弄清如何从 sys.argv 解析出那些参数。 argparse 模块还会自动生成帮助和使用手册，并在用户给程序传入无效参数时报出错误信息。

**argparse简单使用流程**

主要有三个步骤：

- 创建 `ArgumentParser()` 对象
- 调用 `add_argument()` 方法添加参数
- 使用 `parse_args()` 解析添加的参数

### 1. 创建解析器对象

```
parser = argparse.ArgumentParser()
```

一般这样即可，全部可选参数如下。

```
class argparse.ArgumentParser(prog=None, usage=None, description=None, epilog=None, parents=[], formatter_class=argparse.HelpFormatter, prefix_chars='-', fromfile_prefix_chars=None, argument_default=None, conflict_handler='error', add_help=True, allow_abbrev=True)
```

详细解释参考官方文档：https://docs.python.org/zh-cn/3/library/argparse.html#argparse.ArgumentParser

### 2. 添加参数

分为添加位置参数-positional arguments和可选参数-optional arguments
添加位置参数声明的参数名前缀不带-或--，按照顺序进行解析，在命令中必须出现，否则报错，命令通常为：

```
parser.add_argument("a")
parser.add_argument("b")
parser.add_argument("c")
```

添加可选参数声明的参数名前缀带-或--,前缀是-的为短参数，前缀是--是长参数，两者可以都有，也可以只有一个,短参数和长参数效果一样。可选参数的值接在位置参数的后面，不影响位置参数的解析顺序。
以深度学习训练中经常出现的为例：

```
parser.add_argument('--batch-size', type=int, default=64, metavar='N',
                        help='input batch size for training (default: 64)')
parser.add_argument('--momentum', type=float, default=0.5, metavar='M',
                        help='SGD momentum (default: 0.5)')
parser.add_argument('--no-cuda', action='store_true', default=False,
                        help='disables CUDA training')
parser.add_argument('--save-model', action='store_true', default=False,
                        help='For Saving the current Model')
```

其中action参数的'store_true'指的是：触发action时为真，不触发则为假。即储存了一个bool变量，默认为false，触发不用赋值即变为true
type:指定参数类别，默认是str，传入数字要定义
help：是一些提示信息
default：是默认值
metavar: 在 usage 说明中的参数名称，对于必选参数默认就是参数名称，对于可选参数默认是全大写的参数名称.
其它详细用法文档介绍：https://docs.python.org/zh-cn/3/library/argparse.html#argparse.ArgumentParser.add_argument

### 3. 解析参数

```
args = parser.parse_args()
```

这样args就有了参数属性，可以用args了。

示例：

```
# 导入包
import argparse 
# 创建解析器
parser = argparse.ArgumentParser() 

#添加位置参数(positional arguments)
parser.add_argument('-a', type=int，help='input a int')
args = parser.parse_args()
print(args.a)
```
