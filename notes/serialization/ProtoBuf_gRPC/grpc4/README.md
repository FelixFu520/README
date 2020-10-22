# grpc| python 实战 grpc

只要代码可以跑起来, 很多难题都会迎刃而解. so, keep coding and stay hungry.之前用 swoole 写 server 时就接触过 protobuf, 本来以为基于 protobuf 的 grpc, 上手起来会轻轻松松, 没想到结结实实的折腾了许久, 从 php 开始配置 grpc 需要的环境, 到无奈转到 grpc 最亲和 的 go 语言, 又无奈面对各种 go get 撞墙, 直到现在使用 python 语言, 终于 丝般顺滑 的跑完了官网 demo. 代码运行起来后, 之前 grpc 中不太理解的概念, 终于可以 会心一笑 了.

1. grpc 的基础: protobuf
2. grpc helloworld: python 实战 grpc 环境配置
3. grpc basic: grpc 4 种通信方式

## grpc 的基础: protobuf

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

## grpc helloworld: python 实战 grpc 环境配置
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

## grpc basic: 4 种通信方式

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



## Reference
* [博客](https://www.jianshu.com/p/43fdfeb105ff)