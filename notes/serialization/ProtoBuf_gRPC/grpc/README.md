# 用Python编写简单的gRPC服务
这里写个简单的Python gRPC示例，能实现加法和乘法的计算器
## 环境
安装gRPC相关的库，grpcio-tools主要用根据我们的protocol buffer定义来生成Python代码，官方解释是Protobuf code generator for gRPC。protocolbuffers/protobuf是Google开发的一种序列化数据结构的协议。具体结构和语法超纲了，现在还不多用做太多理解，只要会用就行了。

```shell
$ sudo pip3 install grpcio grpcio-tools
```
## 定义服务
使用protocolbuffers/protobuf格式来创建结构化数据文件SimpleCal.proto，内容如下：   
```shell
syntax = "proto3";

service Cal {
  rpc Add(AddRequest) returns (ResultReply) {}
  rpc Multiply(MultiplyRequest) returns (ResultReply) {}
}

message AddRequest {
  int32 number1  = 1;
  int32 number2  = 2;
}

message MultiplyRequest {
  int32 number1  = 1;
  int32 number2  = 2;
}

message ResultReply {
  int32 number = 1;
}
```

在SimpleCal.proto 文件中定义了一个服务Cal，定义了2个RPC方法：Add和Multiply，需要分别在gRPC的服务端中实现加法和乘法。

同时我们也定义了2个方法的参数，Add方法的参数是AddRequest，包含number1和number2两个整数参数。 Multiply方法的参数是MultiplyRequest，里面也有number1和number2两个整数参数。两个函数的返回结构都是ResultReply，内容是一个整数。


根据上面的定义，生成Python代码：
```
$ python3 -m grpc_tools.protoc -I. --python_out=. --grpc_python_out=. ./SimpleCal.proto
$ ls
SimpleCal_pb2_grpc.py  SimpleCal_pb2.py  SimpleCal.proto
```

使用python3 -m grpc_tools.protoc --hel能获得命令的参数含义。ls可以看到grpc_tools 帮我们自动生成了 SimpleCal_pb2_grpc.py， SimpleCal_pb2.py这2个文件。这2个文件会在后面的客户端和服务端代码中被引用。
```
python3 -m grpc_tools.protoc --help
Usage: /usr/local/lib/python3.6/dist-packages/grpc_tools/protoc.py [OPTION] PROTO_FILES
Parse PROTO_FILES and generate output based on the options given:
  -IPATH, --proto_path=PATH   Specify the directory in which to search for
                              imports.  May be specified multiple times;
                              directories will be searched in order.  If not
                              given, the current working directory is used.
                              If not found in any of the these directories,
                              the --descriptor_set_in descriptors will be
                              checked for required proto file.
  --version                   Show version info and exit.
  -h, --help                  Show this text and exit.
  --encode=MESSAGE_TYPE       Read a text-format message of the given type
                              from standard input and write it in binary
                              to standard output.  The message type must
                              be defined in PROTO_FILES or their imports.
  --decode=MESSAGE_TYPE       Read a binary message of the given type from
                              standard input and write it in text format
                              to standard output.  The message type must
                              be defined in PROTO_FILES or their imports.
  --decode_raw                Read an arbitrary protocol message from
                              standard input and write the raw tag/value
                              pairs in text format to standard output.  No
                              PROTO_FILES should be given when using this
                              flag.
  --descriptor_set_in=FILES   Specifies a delimited list of FILES
                              each containing a FileDescriptorSet (a
                              protocol buffer defined in descriptor.proto).
                              The FileDescriptor for each of the PROTO_FILES
                              provided will be loaded from these
                              FileDescriptorSets. If a FileDescriptor
                              appears multiple times, the first occurrence
                              will be used.
  -oFILE,                     Writes a FileDescriptorSet (a protocol buffer,
    --descriptor_set_out=FILE defined in descriptor.proto) containing all of
                              the input files to FILE.
  --include_imports           When using --descriptor_set_out, also include
                              all dependencies of the input files in the
                              set, so that the set is self-contained.
  --include_source_info       When using --descriptor_set_out, do not strip
                              SourceCodeInfo from the FileDescriptorProto.
                              This results in vastly larger descriptors that
                              include information about the original
                              location of each decl in the source file as
                              well as surrounding comments.
  --dependency_out=FILE       Write a dependency output file in the format
                              expected by make. This writes the transitive
                              set of input file paths to FILE
  --error_format=FORMAT       Set the format in which to print errors.
                              FORMAT may be 'gcc' (the default) or 'msvs'
                              (Microsoft Visual Studio format).
  --print_free_field_numbers  Print the free field numbers of the messages
                              defined in the given proto files. Groups share
                              the same field number space with the parent 
                              message. Extension ranges are counted as 
                              occupied fields numbers.

  --plugin=EXECUTABLE         Specifies a plugin executable to use.
                              Normally, protoc searches the PATH for
                              plugins, but you may specify additional
                              executables not in the path using this flag.
                              Additionally, EXECUTABLE may be of the form
                              NAME=PATH, in which case the given plugin name
                              is mapped to the given executable even if
                              the executable's own name differs.
  --grpc_python_out=OUT_DIR   Generate Python source file.
  --python_out=OUT_DIR        Generate Python source file.
  @<filename>                 Read options and filenames from file. If a
                              relative file path is specified, the file
                              will be searched in the working directory.
                              The --proto_path option will not affect how
                              this argument file is searched. Content of
                              the file will be expanded in the position of
                              @<filename> as in the argument list. Note
                              that shell expansion is not applied to the
                              content of the file (i.e., you cannot use
                              quotes, wildcards, escapes, commands, etc.).
                              Each line corresponds to a single argument,
                              even if it contains spaces.
```


### 服务端
下面是服务端代码 cal_server.py：
```python
from concurrent import futures
import grpc
import SimpleCal_pb2
import SimpleCal_pb2_grpc

class CalServicer(SimpleCal_pb2_grpc.CalServicer):
  def Add(self, request, context):   # Add函数的实现逻辑
    print("Add function called")
    return SimpleCal_pb2.ResultReply(number=request.number1 + request.number2)

  def Multiply(self, request, context):   # Multiply函数的实现逻辑
    print("Multiply service called")
    return SimpleCal_pb2.ResultReply(number=request.number1 * request.number2)

def serve():
  server = grpc.server(futures.ThreadPoolExecutor(max_workers=5))
  SimpleCal_pb2_grpc.add_CalServicer_to_server(CalServicer(),server)
  server.add_insecure_port("[::]:50051")
  server.start()
  print("grpc server start...")
  server.wait_for_termination()

if __name__ == '__main__':
  serve()
```
这里的重点在于CalServicer类中对Add和Multiply两个方法的实现。逻辑很简单，从request中读取number1和number2，然后相加。注意，这里的所有变量都需要完整名称：request.number1和request.number2， 不能使用位置参数。Multiply 的实现和Add一样，不多说了。 serve函数里定义了gRPC的运行方式，使用5个worker的线程池。
### 客户端

客户端代码 cal_client.py ：
```python
import SimpleCal_pb2
import SimpleCal_pb2_grpc
import grpc

def run(n, m):
  channel = grpc.insecure_channel('localhost:50051') # 连接上gRPC服务端
  stub = SimpleCal_pb2_grpc.CalStub(channel)
  response = stub.Add(SimpleCal_pb2.AddRequest(number1=n, number2=m))  # 执行计算命令
  print(f"{n} + {m} = {response.number}")
  response = stub.Multiply(SimpleCal_pb2.MultiplyRequest(number1=n, number2=m))
  print(f"{n} * {m} = {response.number}")

if __name__ == "__main__":
  run(100, 300)
```
客户端的逻辑更加简单，就连上gRPC服务，然后发起调用。

### 运行
下面开启服务端，并执行客户端代码调用gRPC服务，结果如下：
```python
$ python3 cal_server.py  &
$ python3 cal_client.py 
100 + 300 = 400
100 * 300 = 30000
```
执行结果表明客户端和服务端已经都运行正常。更多的gRPC样例可以访问gRPC官网的Example, [grpc/grpc](https://github.com/grpc/grpc/tree/master/examples/python) 。
# 博客-2
## RPC基础

RPC 是两个子系统之间进行的直接消息交互，它使用操作系统提供的套接字来作为消息的载体，以特定的消息格式来定义消息内容和边界。

gRPC 是 Google 开源的基于 Protobuf 和 Http2.0 协议的通信框架，Google 深度学习框架 tensorflow 底层的 RPC 通信就完全依赖于 gRPC 库

## 基于python简单使用grpc

### 安装工具依赖

pip install grpcio
pip install protobuf
pip install grpcio_tools

编写协议文件vim compute.proto
```
    syntax = "proto3"; //说明使用proto3语法定义协议

    package compute;
    service Compute {
        // 我们rpc服务的名字
        // 后面
        // 服务端 会用到 <ComputeServicer>
        // 客户端 会用到 <ComputeStub>
        rpc SayHello (HelloRequest) returns (HelloReply) {}
        // SayHello 调用的方法
        // HelloRequest 客户端输入的消息（对象）
        // returns 服务端
        // HelloReply 服务端 返回的消息（对象）
    }

    message HelloRequest {
        //定义 客户端输入消息内容
        string helloworld = 1;
    }

    message HelloReply {
        //定义服务端消息内容
        string result = 1;
    }
```
```
python -m grpc_tools.protoc -I ./ --python_out=./ --grpc_python_out=./ compute.proto


# python_out目录指定 xxxx_pb2.py的输出路径，我们指定为./ 当前路径
# grpc_python_out指定xxxx_pb2_grpc.py文件的输出路径,我们指定为./ 当前路径
# grpc_tools.protoc 这是我们的工具包，刚刚安装的
# -I参数指定协议文件的查找目录，我们都将它们设置为当前目录./
# compute.proto 我们的协议文件

ls
compute_pb2_grpc.py  compute_pb2.py  compute.proto
# compute.proto 协议文件
# compute_pb2.py 里面有消息序列化类
# compute_pb2_grpc.py 包含了服务器 Stub 类和客户端 Stub 类，以及待实现的服务 RPC 接口。
```
### 编写服务器
```
import time
import grpc
from concurrent import futures

import compute_pb2,compute_pb2_grpc # 刚刚生产的两个文件

class ComputeServicer(compute_pb2_grpc.ComputeServicer):
    def SayHello(self,request,ctx):
        max_len = str(len(request.helloworld))
        return compute_pb2.HelloReply(result=max_len)
    
def main():
    # 多线程服务器
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    # 实例化 计算len的类
    servicer = ComputeServicer()
    # 注册本地服务,方法ComputeServicer只有这个是变的
    compute_pb2_grpc.add_ComputeServicer_to_server(servicer, server)
    # 监听端口
    server.add_insecure_port('127.0.0.1:19999')
    # 开始接收请求进行服务
    server.start()
    # 使用 ctrl+c 可以退出服务
    try:
        print("running...")
        time.sleep(1000)
    except KeyboardInterrupt:
        print("stopping...")
        server.stop(0)


if __name__ == '__main__':
    main()
```


### 编写客户端
```
import grpc
import compute_pb2
import compute_pb2_grpc

_HOST = '127.0.0.1'
_PORT = '19999'


def main():
    with grpc.insecure_channel("{0}:{1}".format(_HOST, _PORT)) as channel:
        client = compute_pb2_grpc.ComputeStub(channel=channel)
        response = client.SayHello(compute_pb2.HelloRequest(helloworld="123456"))
    print("received: " + response.result)


if __name__ == '__main__':
    main()
```
 其中，关键的步骤为：

 1、连接rpc服务器；

 2、对service获取一个stub用于调用接口；

 3、发送数据、接收数据。

## Reference
* [本篇博客](https://github.com/grpc/grpc/tree/master/examples/python)
* [blog-2](https://blog.csdn.net/sunt2018/article/details/90176015)