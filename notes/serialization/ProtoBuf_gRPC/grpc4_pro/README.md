# 基于grpc的流式方式实现双向通讯(python)
## grpc介绍

grpc是谷歌开源的一套基于rpc实现的通讯框架(官网有更完整的定义)。在搞懂grpc之前，首先要弄懂rpc是什么。下面是自己理解的rpc定义，若有不对，望指出：
```
rpc官方称为 远程过程调用 。我这里理解为远程函数调用，即一个本机程序调用另一个机器的程序中的某个函数。因不是同一机器调用，故需要远程访问操作。
```
与远程过程调用相反的则是“近程过程调用”(哈哈，自己乱起的)。其实就是实现和调用都在同一个机器的程序中。比如，学过面向对象语言的（如java）可以解释为：一个类中实现了一个方法，然后另一个程序中new了一个这个类的事例(对象)，并调用该方法。而远程过程调用则相当于一个机器中实现了一个类的方法，另一个机器new了这个类的对象，它若想要调用该方法，必须要与实现了类方法的机器进行通讯。此时我们可以称实现了类方法的机器为服务端，new了对象的机器为客户端。


## grpc通信方式

grpc同http通讯一样，也是基于“请求响应”模式的一种通讯。客户端请求，服务器响应。关于grpc的更多介绍可以参考官网。下面说一下grpc的四种通信方式[见官网](https://www.grpc.io/docs/languages/python/basics/)，根据不同业务场景，可以分为：

#### 客户端单次请求，服务端回应一次:
```
// Obtains the feature at a given position.
rpc GetFeature(Point) returns (Feature) {}
```
#### 客户端一次请求，服务端流式应答（其实相当于返回给客户端多条数据）
```
// Obtains the Features available within the given Rectangle.  Results are
// streamed rather than returned at once (e.g. in a response message with a
// repeated field), as the rectangle may cover a large area and contain a
// huge number of features.
rpc ListFeatures(Rectangle) returns (stream Feature) {}
```

#### 客户端流式请求，服务端回应一次
```
// Accepts a stream of Points on a route being traversed, returning a
// RouteSummary when traversal is completed.
rpc RecordRoute(stream Point) returns (RouteSummary) {}
```
#### 客户端流式请求，服务端流式应答
```
// Accepts a stream of RouteNotes sent while a route is being traversed,
// while receiving other RouteNotes (e.g. from other users).
rpc RouteChat(stream RouteNote) returns (stream RouteNote) {}
```


知道了四种通信方式后，回到主要问题上，我们要利用这四种通信方式来实现客户端与服务端互相通信。要实现互相通信，我这里想到的有两种：

#### 1.客户端与服务端各自既是客户端又是服务端
这种方式感觉是最容易实现的。即在客户端与服务端之间各实现一套“请求响应模型”，这样客户端主动通信服务端时是正常请求响应，服务端主动通信客户端时它此时就变为客户端来请求。这样在外部看来两个机器之间就能互相通信了。
该种实现方式建立了两个通道来通信。缺点是要实现两套通信代码。

#### 2.客户端与服务端直接互相通信
我们已经知道grpc是基于请求响应的，客户端请求，服务端响应。那怎么让服务端主动请求客户端通信呢？ 其实我们可以用grpc的 第2或第4种的服务端流式响应 。原理是可以让客户端先发一个空消息给服务端让服务端知道（相当于客户端在服务端注册），然后服务端流式回应。因流式回应不会一下子都回完，我们可以在中途把服务端要发给客户端的消息加入到流中，让流把消息捎回到客户端。
在外部来看客户端与服务端能互相通信了。不过这种缺点是把互相通信的业务都糅杂到一块了。

## 具体实现

上面说了两种互相通信的实现方法及grpc的四种通信方式。这里采用第二种实现方法及grpc的第二种通信方式来实现，编程语言采用Python实现。

grpc采用protobuf来定义和传输数据。故通信的数据是用proto文件来定义的。关于proto的语法可以参考文档
首先建立如下的目录：
```
│  contact_client.py
│  contact_server.py
|
├─contact
│  │  contact.proto
│  │ 
│  │  __init__.py
│  
```

* contact.proto：定义通信的数据部分
* contact_client.py：客户端代码
* contact_server.py：服务端代码

### contact.proto内容如下：
```
syntax = "proto3";

// 定义一个服务
service Contact {
    // 客户端通信给服务端，通信方式可以随意选择，这里我选择第4种通信方式
    rpc sendStatus (stream ClientMsg) returns (stream Result);
    // 客户端发送一个空消息给服务端，服务端就能给客户端通信了
    rpc getTask (Empty) returns (stream ServerMsg);
    // 客户端接受完服务端消息处理完后，再告诉服务端。这个tellResult也可以不要，看具体需求
    rpc tellResult (stream Result) returns (Empty);
}

message ClientMsg {
    string msg = 1;
}

message ServerMsg {
    string task = 1;
}

message Empty {

}

message Result {
    string ret = 1;
}
```
在contact文件夹下运行命令：
```
python -m grpc_tools.protoc -I. --python_out=. --grpc_python_out=. contact.proto
```
会在contact目录下自动生成contact_pb2.py和contact_pb2_grpc.py两个文件。下来就是实现具体的通信了，首先是客户端向服务端发消息：

contact_server.py中代码实现具体代码：    
```python
    # 注意服务端的具体实现函数是在类里面
    def sendStatus(self, request_iterator, context):
        for note in request_iterator:
            yield contact_pb2.Result(
                result=f"服务端接收到消息:{note.msg}"
            )


```

contact_client.py中的代码为：   
```python
# 先制造一些客户端能发送的数据
def make_some_data():
    for i in range(15):
        num = random.randint(1, 20)
        yield contact_pb2.ClientMsg(msg=f"数据:{num}")
        
        
def send_status(stub):
    try:
        while True:
            status_response = stub.sendStatus(make_some_data())
            for ret in status_response:
                print(ret.result)
            time.sleep(60)
    except Exception as e:
        print(f'err in send_status:{e}')
        return

```

上面的代码就实现了客户端主动通信服务端的功能。可以看到是服务端先实现具体的代码，然后客护端调用具体函数与服务端通信，最后再对服务端返回的数据进行处理。

而服务端主动通信客户端的方式可以理解为：客户端先给服务端发送一个消息，告诉服务端我在线，然后服务端就能发数据给客户端了，最后客户端再通知服务端我接收了你的哪些数据。具体代码为：

server端代码：
```python
import logging
import random
import time
from concurrent import futures

import grpc
from contact import contact_pb2_grpc
from contact import contact_pb2

# 在类初试化的时候定义了一个列表self.tasks来充当任务队列
def getTask(self, request_iterator, context):
    print("服务端已接收到客户端上线通知，开始发送任务给客户端\n")
    last_index = 0
    while True:
        print("服务端开始发送任务给客户端了。。。。。。\n")
        while len(self.tasks) > last_index:
            n = self.tasks[last_index]
            last_index += 1
            yield n
            print(f'服务端发送给了客户端任务：{n.task}##########\n')
            
       # 顺便制造些服务端的任务数据用来填充到任务队列里面
        for i in range(10):
            num = random.randint(100, 200)
            self.tasks.append(contact_pb2.ServerMsg(
                task=f"任务:{num}"
            ))
        time.sleep(40)

def tellResult(self, request_iterator, context):
    for response in request_iterator:
        print(f"我已经知道客户端接收到我发过去的任务:{response.ret}")

    return contact_pb2.Empty()


```
client端代码

```python
import logging
import random
import threading
import time

import grpc
from contact import contact_pb2
from contact import contact_pb2_grpc


# 接收服务端发送过来的任务
def get_task(stub):
    try:
        for task in stub.getTask(contact_pb2.Empty()):
            print(f"客户端已接收到服务端任务：{task.task}\n")
            # 顺便再告诉服务端我已经接收到你发的任务，你不用担心我没接收到它
            yield contact_pb2.Result(
                ret=f"客户端接收到任务:{task.task}"
            )
    except Exception as e:
        print(f'err:{e}')
        return
        
# 客户端再通知服务端我接收到你的消息了
def tell_result(stub):
   result = get_task(stub)
    stub.tellResult(result)
    
def run():
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = contact_pb2_grpc.ContactStub(channel)
        while True:
            try:
                threading.Thread(target=send_status, args=(stub,), daemon=True).start()
                tell_result(stub)
            except grpc.RpcError as e:
                print(f"server connected out, please retry:{e.code()},{e.details()}")
            except Exception as e:
                print(f'unknown err:{e}')
            finally:
                time.sleep(2)


if __name__ == '__main__':
    run()


```

日志：   
```shell

```

### 总结

从上面看出，服务端主动通信给客户端，还是逃不过grpc的请求响应方式。上面代码只是实现了一种互相通信的方法，但是没有既充当客户端又充当服务端那种方法简单。


## Reference
* [blog](https://blog.csdn.net/xiaobai_ol/article/details/103433981)