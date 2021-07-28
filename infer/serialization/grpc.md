# grpc

⌚️:2020年11月30日

📚参考

- [博客](https://www.jianshu.com/p/43fdfeb105ff)
- [本篇博客](https://github.com/grpc/grpc/tree/master/examples/python)
- [blog-2](https://blog.csdn.net/sunt2018/article/details/90176015)
- [blog](https://blog.csdn.net/xiaobai_ol/article/details/103433981)

---

RPC 是两个子系统之间进行的直接消息交互，它使用操作系统提供的套接字来作为消息的载体，以特定的消息格式来定义消息内容和边界。

gRPC 是 Google 开源的基于 Protobuf 和 Http2.0 协议的通信框架，Google 深度学习框架 tensorflow 底层的 RPC 通信就完全依赖于 gRPC 库

## grpc介绍

grpc是谷歌开源的一套基于rpc实现的通讯框架(官网有更完整的定义)。在搞懂grpc之前，首先要弄懂rpc是什么。下面是自己理解的rpc定义，若有不对，望指出：

```
rpc官方称为 远程过程调用 。我这里理解为远程函数调用，即一个本机程序调用另一个机器的程序中的某个函数。因不是同一机器调用，故需要远程访问操作。
```

与远程过程调用相反的则是“近程过程调用”(哈哈，自己乱起的)。其实就是实现和调用都在同一个机器的程序中。比如，学过面向对象语言的（如java）可以解释为：一个类中实现了一个方法，然后另一个程序中new了一个这个类的事例(对象)，并调用该方法。而远程过程调用则相当于一个机器中实现了一个类的方法，另一个机器new了这个类的对象，它若想要调用该方法，必须要与实现了类方法的机器进行通讯。此时我们可以称实现了类方法的机器为服务端，new了对象的机器为客户端。

## grpc通信方式

grpc同http通讯一样，也是基于“请求响应”模式的一种通讯。客户端请求，服务器响应。关于grpc的更多介绍可以参考官网。下面说一下grpc的四种通信方式[见官网](https://www.grpc.io/docs/languages/python/basics/)，根据不同业务场景，可以分为：

**客户端单次请求，服务端回应一次:**

```
// Obtains the feature at a given position.
rpc GetFeature(Point) returns (Feature) {}
```

**客户端一次请求，服务端流式应答（其实相当于返回给客户端多条数据）**

```
// Obtains the Features available within the given Rectangle.  Results are
// streamed rather than returned at once (e.g. in a response message with a
// repeated field), as the rectangle may cover a large area and contain a
// huge number of features.
rpc ListFeatures(Rectangle) returns (stream Feature) {}
```

**客户端流式请求，服务端回应一次**

```
// Accepts a stream of Points on a route being traversed, returning a
// RouteSummary when traversal is completed.
rpc RecordRoute(stream Point) returns (RouteSummary) {}
```

**客户端流式请求，服务端流式应答**

```
// Accepts a stream of RouteNotes sent while a route is being traversed,
// while receiving other RouteNotes (e.g. from other users).
rpc RouteChat(stream RouteNote) returns (stream RouteNote) {}
```


知道了四种通信方式后，回到主要问题上，我们要利用这四种通信方式来实现客户端与服务端互相通信。要实现互相通信，我这里想到的有两种：

**1.客户端与服务端各自既是客户端又是服务端**

这种方式感觉是最容易实现的。即在客户端与服务端之间各实现一套“请求响应模型”，这样客户端主动通信服务端时是正常请求响应，服务端主动通信客户端时它此时就变为客户端来请求。这样在外部看来两个机器之间就能互相通信了。
该种实现方式建立了两个通道来通信。缺点是要实现两套通信代码。

**2.客户端与服务端直接互相通信**

我们已经知道grpc是基于请求响应的，客户端请求，服务端响应。那怎么让服务端主动请求客户端通信呢？ 其实我们可以用grpc的 第2或第4种的服务端流式响应 。原理是可以让客户端先发一个空消息给服务端让服务端知道（相当于客户端在服务端注册），然后服务端流式回应。因流式回应不会一下子都回完，我们可以在中途把服务端要发给客户端的消息加入到流中，让流把消息捎回到客户端。
在外部来看客户端与服务端能互相通信了。不过这种缺点是把互相通信的业务都糅杂到一块了。

## 一、python 实战 grpc

只要代码可以跑起来, 很多难题都会迎刃而解. so, keep coding and stay hungry.之前用 swoole 写 server 时就接触过 protobuf, 本来以为基于 protobuf 的 grpc, 上手起来会轻轻松松, 没想到结结实实的折腾了许久, 从 php 开始配置 grpc 需要的环境, 到无奈转到 grpc 最亲和 的 go 语言, 又无奈面对各种 go get 撞墙, 直到现在使用 python 语言, 终于 丝般顺滑 的跑完了官网 demo. 代码运行起来后, 之前 grpc 中不太理解的概念, 终于可以 会心一笑 了.

1. grpc 的基础: protobuf
2. grpc helloworld: python 实战 grpc 环境配置
3. grpc basic: grpc 4 种通信方式

### grpc 的基础: protobuf

grpc 使用 protobuf 进行数据传输. protobuf 是一种数据交换格式, 由三部分组成:

**1. proto 文件: 使用的 proto 语法的文本文件, 用来定义数据格式**


proto语法现在有 proto2 和 proto3 两个版本, 推荐使用 proto3, 更加简洁明了

```shell
// [python quickstart](https://grpc.io/docs/quickstart/python.html#run-a-grpc-application)
// python -m grpc_tools.protoc --python_out=. --grpc_python_out=. -I. helloworld.proto

// helloworld.proto
syntax = "proto3";

service Greeter {
    rpc SayHello(HelloRequest) returns (HelloReply) {}
    rpc SayHelloAgain(HelloRequest) returns (HelloReply) {}
}

message HelloRequest {
    string name = 1;
}

message HelloReply {
    string message = 1;
}
```

**2.protoc: protobuf 编译器(compile), 将 proto 文件编译成不同语言的实现, 这样不同语言中的数据就可以和 protobuf 格式的数据进行交互** 


**3.protobuf 运行时(runtime): protobuf 运行时所需要的库, 和 protoc 编译生成的代码进行交互**


* 使用 protobuf 的过程:编写 proto 文件 -> 使用 protoc 编译 -> 添加 protobuf 运行时 -> 项目中集成

* 更新 protobuf 的过程:修改 proto 文件 -> 使用 protoc 重新编译 -> 项目中修改集成的地方

```
PS: proto3 的语法非常非常的简单, 上手 protobuf 也很轻松, 反而是配置 protoc 的环境容易卡住, 所以推荐使用 python 入门, 配置 protoc 这一步非常省心.
```

### grpc helloworld: python 实战 grpc 环境配置

上面已经定义好了 grpc helloworld demo 所需的 proto 文件, 现在来具体看看 python 怎么一步步把 grpc helloworld 的环境搭建起来:

**1.protobuf 运行时(runtime)**  
这一步很简单, 安装 grpc 相关的 python 模块(module) 即可  
`pip install grpcio`  
**2.使用 protoc 编译 proto 文件, 生成 python 语言的实现**   

```
# 安装 python 下的 protoc 编译器
pip install grpcio-tools

# 编译 proto 文件
python -m grpc_tools.protoc --python_out=. --grpc_python_out=. -I. helloworld.proto

python -m grpc_tools.protoc: python 下的 protoc 编译器通过 python 模块(module) 实现, 所以说这一步非常省心
--python_out=. : 编译生成处理 protobuf 相关的代码的路径, 这里生成到当前目录
--grpc_python_out=. : 编译生成处理 grpc 相关的代码的路径, 这里生成到当前目录
-I. helloworld.proto : proto 文件的路径, 这里的 proto 文件在当前目录
```

编译后生成的代码:

helloworld_pb2.py: 用来和 protobuf 数据进行交互    
helloworld_pb2_grpc.py: 用来和 grpc 进行交互   
**3.最后一步, 编写 helloworld 的 grpc 实现:**  

服务器端: helloworld_grpc_server.py   

```python
from concurrent import futures
import time
import grpc
import helloworld_pb2
import helloworld_pb2_grpc

# 实现 proto 文件中定义的 GreeterServicer
class Greeter(helloworld_pb2_grpc.GreeterServicer):
    # 实现 proto 文件中定义的 rpc 调用
    def SayHello(self, request, context):
        return helloworld_pb2.HelloReply(message = 'hello {msg}'.format(msg = request.name))

    def SayHelloAgain(self, request, context):
        return helloworld_pb2.HelloReply(message='hello {msg}'.format(msg = request.name))

def serve():
    # 启动 rpc 服务
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    helloworld_pb2_grpc.add_GreeterServicer_to_server(Greeter(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    try:
        while True:
            time.sleep(60*60*24) # one day in seconds
    except KeyboardInterrupt:
        server.stop(0)

if __name__ == '__main__':
    serve()
```

客户端: helloworld_grpc_client.py    

```python
import grpc
import helloworld_pb2
import helloworld_pb2_grpc

def run():
    # 连接 rpc 服务器
    channel = grpc.insecure_channel('localhost:50051')
    # 调用 rpc 服务
    stub = helloworld_pb2_grpc.GreeterStub(channel)
    response = stub.SayHello(helloworld_pb2.HelloRequest(name='czl'))
    print("Greeter client received: " + response.message)
    response = stub.SayHelloAgain(helloworld_pb2.HelloRequest(name='daydaygo'))
    print("Greeter client received: " + response.message)

if __name__ == '__main__':
    run()
```

运行 python helloworld_grpc_server.py 和 python helloworld_grpc_client.py, 就可以看到效果了

### grpc basic: 4 种通信方式

helloworld 使用了最简单的 grpc 通信方式: 类似 http 协议的一次 request+response.

根据不同的业务场景, grpc 支持 4 种通信方式:

* 客服端一次请求, 服务器一次应答
* 客服端一次请求, 服务器多次应答(流式)
* 客服端多次请求(流式), 服务器一次应答
* 客服端多次请求(流式), 服务器多次应答(流式)

官方提供了一个 route guide service 的 demo, 应用到了这 4 种通信方式, 具体的业务如下:

* 数据源: json 格式的数据源, 存储了很多地点, 每个地点由经纬度(point)和地名(location)组成
* 通信方式 1: 客户端请求一个地点是否在数据源中
* 通信方式 2: 客户端指定一个矩形范围(矩形的对角点坐标), 服务器返回这个范围内的地点信息
* 通信方式 3: 客户端给服务器发送多个地点信息, 服务器返回汇总信息(summary)
* 通信方式 4: 客户端和服务器使用地点信息 聊天(chat)


对应的 proto 文件: routeguide.proto:   

```shell
// [python quickstart](https://grpc.io/docs/quickstart/python.html#run-a-grpc-application)
// python -m grpc_tools.protoc --python_out=. --grpc_python_out=. -I. routeguide.proto

syntax = "proto3";

service RouteGuide {
    // simple rpc
    rpc GetFeature(Point) returns (Feature) {}
    // server2client stream rpc
    rpc ListFeature(Rectangle) returns (stream Feature) {}
    // client2server stream rpc
    rpc RecordRoute(stream Point) returns (RouteSummary) {}
    // stream rpc
    rpc RouteChat(stream RouteNote) returns (stream RouteNote) {}
}

message Point {
    int32 latitude = 1;
    int32 longitude = 2;
}

message Rectangle {
    Point lo = 1;
    Point hi = 2;
}

message Feature {
    string name = 1;
    Point location = 2;
}

message RouteNote {
    Point location = 1;
    string message = 2;
}

message RouteSummary {
    int32 point_count = 1;
    int32 feature_count = 2;
    int32 distance = 3;
    int32 elapsed_time = 4;
}
```

proto 中想要表示流式传输, 只需要添加 stream 关键字即可   

同样的, 使用 protoc 生成代码:

```
python -m grpc_tools.protoc --python_out=. --grpc_python_out=. -I. routeguide.proto
```

生成了 routeguide_pb2.py routeguide_pb2_grpc.py 文件, 和上面的 helloworld 对应

这里需要增加一个 routeguide_db.py, 用来处理 demo 中数据源(routeguide_db.json)文件:

```python
import json
import routeguide_pb2

def read_routeguide_db():
    feature_list = []
    with open('route_guide_db.json') as f:
        for item in json.load(f):
            feature = routeguide_pb2.Feature(
                name = item['name'],
                location = routeguide_pb2.Point(
                    latitude=item['location']['latitude'],
                    longitude=item['location']['longitude']
                )
            )
            feature_list.append(feature)
    return feature_list
```

处理 json 的过程很简单, 解析 json 数据得到由坐标点组成的数组

好了, 还剩下一个难题: **怎么处理流式数据呢?**. 答案是 for-in + yield

* 客户端读取服务器发送的流式数据   

```python
print("-------------- ListFeatures --------------")
response = stub.ListFeature(routeguide_pb2.Rectangle(
    lo = routeguide_pb2.Point(latitude=400000000, longitude=-750000000),
    hi=routeguide_pb2.Point(latitude=420000000, longitude=-730000000)
))
for feature in response:
    print("Feature called {name} at {location}".format(name=feature.name, location=feature.location))
```

* 客户端发送流式数据给服务器   

```python
def generate_route(feature_list):
    for _ in range(0, 20):
        random_feature = feature_list[random.randint(0, len(feature_list) - 1)]
        print("random feature {name} at {location}".format(
            name=random_feature.name, location=random_feature.location))
        yield random_feature.location

print("-------------- RecordRoute --------------")
feature_list = routeguide_db.read_routeguide_db()
route_iterator = generate_route(feature_list)
response = stub.RecordRoute(route_iterator)
print("point count: {point_count} feature count: {feature_count} distance: {distance} elapsed time:{elapsed_time}".format(
    point_count  = response.point_count,
    feature_count = response.feature_count,
    distance = response.distance,
    elapsed_time = response.elapsed_time
))
```

* 完整的服务器端代码: routeguide_grpc_server.py:

```python
from concurrent import futures
import math
import time
import grpc
import routeguide_pb2
import routeguide_pb2_grpc
import routeguide_db

def get_feature(db, point):
    for feature in db:
        if feature.location == point:
            return feature
    return None


def get_distance(start, end):
    """Distance between two points."""
    coord_factor = 10000000.0
    lat_1 = start.latitude / coord_factor
    lat_2 = end.latitude / coord_factor
    lon_1 = start.longitude / coord_factor
    lon_2 = end.longitude / coord_factor
    lat_rad_1 = math.radians(lat_1)
    lat_rad_2 = math.radians(lat_2)
    delta_lat_rad = math.radians(lat_2 - lat_1)
    delta_lon_rad = math.radians(lon_2 - lon_1)

    # Formula is based on http://mathforum.org/library/drmath/view/51879.html
    a = (pow(math.sin(delta_lat_rad / 2), 2) +
         (math.cos(lat_rad_1) * math.cos(lat_rad_2) * pow(
             math.sin(delta_lon_rad / 2), 2)))
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))
    R = 6371000
    # metres
    return R * c

class RouteGuide(routeguide_pb2_grpc.RouteGuideServicer):
    def __init__(self):
        self.db = routeguide_db.read_routeguide_db()

    def GetFeature(self, request, context):
        feature = get_feature(self.db, request)
        if feature is None:
            return routeguide_pb2.Feature(name = '', location = request)
        else:
            return feature

    def ListFeature(self, request, context):
        left = min(request.lo.longitude, request.hi.longitude)
        right = max(request.lo.longitude, request.hi.longitude)
        top = max(request.lo.latitude, request.hi.latitude)
        bottom = min(request.lo.latitude, request.hi.latitude)
        for feature in self.db:
            if (feature.location.longitude >= left
                and feature.location.longitude <= right
            and feature.location.latitude >= bottom
            and feature.location.latitude <= top):
                yield feature

    def RecordRoute(self, request_iterator, context):
        point_count = 0
        feature_count = 1
        distance = 0.0
        prev_point = None

        start_time = time.time()
        for point in request_iterator:
            point_count += 1
            if get_feature(self.db, point):
                feature_count += 1
            if prev_point:
                distance += get_distance(prev_point, point)
            prev_point = point
        elapsed_time = time.time() - start_time
        return routeguide_pb2.RouteSummary(
            point_count = point_count,
            feature_count = feature_count,
            distance = int(distance),
            elapsed_time = int(elapsed_time)
        )

    def RouteChat(self, request_iterator, context):
        prev_notes = []
        for new_note in request_iterator:
            for prev_note in prev_notes:
                if prev_note.location == new_note.location:
                    yield prev_note
            prev_notes.append(new_note)

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    routeguide_pb2_grpc.add_RouteGuideServicer_to_server(RouteGuide(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    try:
        while True:
            time.sleep(60*60*24) # one day in seconds
    except KeyboardInterrupt:
        server.stop(0)

if __name__ == '__main__':
    serve()
```

* 完整的客户端代码: routeguide_grpc_client.py:  

```python
import grpc
import routeguide_pb2
import routeguide_pb2_grpc
import routeguide_db
import random

def get_feature(feature):
    if not feature.location:
        print("Server returned incomplete feature")
        return
    if feature.name:
        print("Feature called {name} at {location}".format(name = feature.name, location = feature.location))
    else:
        print("Found no feature at {location}".format(location = feature.location))

def generate_route(feature_list):
    for _ in range(0, 20):
        random_feature = feature_list[random.randint(0, len(feature_list) - 1)]
        print("random feature {name} at {location}".format(
            name=random_feature.name, location=random_feature.location))
        yield random_feature.location

def make_route_note(message, latitude, longitude):
    return routeguide_pb2.RouteNote(
        message=message,
        location=routeguide_pb2.Point(latitude=latitude, longitude=longitude))

def generate_route_note():
    msgs = [
        make_route_note('msg 1', 0, 0),
        make_route_note('msg 2', 1, 0),
        make_route_note('msg 3', 0, 1),
        make_route_note('msg 4', 0, 0),
        make_route_note('msg 5', 1, 1),
    ]
    for msg in msgs:
        print("send message {message} location {location}".format(message = msg.message, location = msg.location))
        yield msg

def run():
    channel = grpc.insecure_channel('localhost:50051')
    stub = routeguide_pb2_grpc.RouteGuideStub(channel)
    print("-------------- GetFeature --------------")
    response = stub.GetFeature(routeguide_pb2.Point(latitude=409146138, longitude=-746188906))
    get_feature(response)
    response = stub.GetFeature(routeguide_pb2.Point(latitude=0, longitude=-0))
    get_feature(response)

    print("-------------- ListFeatures --------------")
    response = stub.ListFeature(routeguide_pb2.Rectangle(
        lo = routeguide_pb2.Point(latitude=400000000, longitude=-750000000),
        hi=routeguide_pb2.Point(latitude=420000000, longitude=-730000000)
    ))
    for feature in response:
        print("Feature called {name} at {location}".format(name=feature.name, location=feature.location))

    print("-------------- RecordRoute --------------")
    feature_list = routeguide_db.read_routeguide_db()
    route_iterator = generate_route(feature_list)
    response = stub.RecordRoute(route_iterator)
    print("point count: {point_count} feature count: {feature_count} distance: {distance} elapsed time:{elapsed_time}".format(
        point_count  = response.point_count,
        feature_count = response.feature_count,
        distance = response.distance,
        elapsed_time = response.elapsed_time
    ))

    print("-------------- RouteChat --------------")
    response = stub.RouteChat(generate_route_note())
    for msg in response:
        print("recived message {message} location {location}".format(
            message=msg.message, location=msg.location))

if __name__ == '__main__':
    run()
```

运行 python routeguide_grpc_server.py 和 python routeguide_grpc_client.py 就可以看到效果.

## 二、入门demo：基于python简单使用grpc

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



## 三、用Python编写简单的gRPC服务

这里写个简单的Python gRPC示例，能实现加法和乘法的计算器

### 环境

安装gRPC相关的库，grpcio-tools主要用根据我们的protocol buffer定义来生成Python代码，官方解释是Protobuf code generator for gRPC。protocolbuffers/protobuf是Google开发的一种序列化数据结构的协议。具体结构和语法超纲了，现在还不多用做太多理解，只要会用就行了。

```shell
$ sudo pip3 install grpcio grpcio-tools
pip install grpcio
pip install protobuf
pip install grpcio_tools
```

### 定义服务

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



## 四、基于grpc的流式方式实现双向通讯(python)

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

**contact.proto内容如下：**

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

**总结**

从上面看出，服务端主动通信给客户端，还是逃不过grpc的请求响应方式。上面代码只是实现了一种互相通信的方法，但是没有既充当客户端又充当服务端那种方法简单。

