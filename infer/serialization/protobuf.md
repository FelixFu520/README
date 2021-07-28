# protocbuf案例

⌚️:2020年11月30日

📚参考

- [本文blog](https://www.jianshu.com/p/b723053a86a6)

---

## Protobuf是什么

Protobuf实际是一套类似Json或者XML的数据传输格式和规范，用于不同应用或进程之间进行通信时使用。通信时所传递的信息是通过Protobuf定义的message数据结构进行打包，然后编译成二进制的码流再进行传输或者存储。

## Protobuf的优点

相比较而言，Protobuf有如下优点：

* 足够简单
* 序列化后体积很小:消息大小只需要XML的1/10 ~ 1/3
* 解析速度快:解析速度比XML快20 ~ 100倍
* 多语言支持
* 更好的兼容性,Protobuf设计的一个原则就是要能够很好的支持向下或向上兼容

## 如何安装使用Protobuf

### 安装

使用Python的话简便的安装方法如下

```shell
pip install protobuf    # 安装protobuf库
sudo apt-get install protobuf-compiler  # 安装protobuf编译器
```

如果自己编译安装的话可以参考git上安装指导，虽然写得不清楚:)   

### 使用

使用Protobuf有如下几个步骤：

1. 定义消息   
2. 初始化消息以及存储传输消息   
3. 读取消息并解析   

下面以一个实际的例子来说明如何使用Protobuf，先展示出项目的实际目录结构：

```shell
 ├──helloworld
    ├── my
    │   ├── helloworld_pb2.py
    │   ├── helloworld_pb2.pyc
    │   └── __init__.py
    ├── mybuffer.io
    ├── my.helloworld.proto
    ├── reader.py
    └── writer.py
```

#### 定义消息

Protobuf的消息结构是通过一种叫做Protocol Buffer Language的语言进行定义和描述的，实际上Protocol Buffer Language分为两个版本，版本2和版本3，默认不声明的情况下使用的是版本2，下面以版本2为来举个栗子, 假设我们定义了文件名为my.helloworld.proto的文件，如下：

```shell
package my;
message helloworld
{
    required int32 id = 1;
    required string str = 2;
    optional int32 wow = 3;
}

```

此时，目录结构为：

```shell
 ├──helloworld
    ├── README.md
    ├── my.helloworld.proto

```

然后我们需要使用protoc进行编译   

```
protoc -I=./ --python_out=./ ./my.helloworld.proto
```

-I: 是设定源路径   
--python_out: 用于设定编译后的输出结果，如果使用其它语言请使用对应语言的option    
最后一个参数是你要编译的proto文件    

此时目录结构为：   

```shell
 ├──helloworld
    ├── my
    │   ├── helloworld_pb2.py
    ├── my.helloworld.proto
```

现在已经定义好了消息的数据结构，接下来看下如何使用  

#### 消息初始化和存储传输

我们来通过writer.py来初始化消息并存储为文件，代码如下：

```
from my.helloworld_pb2 import helloworld

def main():
    hw = helloworld()
    hw.id = 123
    hw.str = "eric"
    print hw

    with open("mybuffer.io", "wb") as f:
        f.write(hw.SerializeToString())

if __name__ == "__main__":
    main()
```

执行writer.py之后就会将序列化的结果存储在文件mybuffer.io中，然后看下如何读取    

```shell
 ├──helloworld
    ├── my
    │   ├── helloworld_pb2.py
    ├── mybuffer.io
    ├── my.helloworld.proto
    └── writer.py
```

#### 消息读取与解析

我们通过reader.py来读取和解析消息，代码如下：

```
from my.helloworld_pb2 import helloworld


def main():
    hw = helloworld()
    with open("mybuffer.io", "rb") as f:
        hw.ParseFromString(f.read())
        print hw.id
        print hw.str


if __name__ == "__main__":
    main()
```

```shell
 ├──helloworld
    ├── my
    │   ├── helloworld_pb2.py
    ├── mybuffer.io
    ├── my.helloworld.proto
    ├── reader.py
    └── writer.py
```



