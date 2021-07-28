# 序列化

⌚️:2020年11月30日

📚参考

- [xml、json、protobuf序列化协议](https://zhuanlan.zhihu.com/p/91313277)
- [序列化手段](https://cloud.tencent.com/developer/article/1491609)

---

## 1. 为什么需要序列化和反序列化协议 

### **1.1 什么是多维数据？** 

从逻辑上不是线性排列的数据就是多维的，最常见的就是树形数据结构，比如引用数据类型：我们在对一个对象进行深拷贝的时候常常需要递归地遍历嵌套树的每一层，才能得到这个对象的全部信息。但是这种树形结构的基本生存资料是对象所在的平台比如JavaScript运行环境，同一个JS对象不能原封不动地拿到Java的环境下使用（虽然感觉底层原理都差不多），反之亦然，就是这个简单的道理：多维数据结构“不通用”，虽然JS对象和Java对象都是多维度的，但多维结构不同。

如何实现跨平台的通用数据格式呢，只能使用一个维度的数据结构，比如字符串（json）。

序列化也叫编码，与之对应的逆操作就是反序列化或者解码，一维数据抵达不同平台（这里的浏览器，服务器和数据库都是不同的平台）后就要进行反序列化，从而将数据改造成易于自己理解的多维结构。

还有一个很好的解释是，网络只能传输一维的数据流。



### 1.2 序列化和反序列化基础

![](F:\GitHub\README_\infer\serialization\imgs\1.png)

![img](F:\GitHub\README_\infer\serialization\imgs\2.png)

**序列化和反序列化概念**

- 序列化：把对象转换为字节序列的过程称为对象的序列化。
- 反序列化：把字节序列恢复为对象的过程称为对象的反序列化。

**什么情况下需要序列化**

- 当你想把的内存中的对象状态保存到一个文件中或者数据库中时候；
- 当你想用套接字在网络上传送对象的时候。

### 1.3 如何实现序列化?

主流序列化协议：**xml、json、protobuf**

## 2. 各大降维技术优缺点(对比)

### 2.1 JSON

**[JSON](https://link.zhihu.com/?target=https%3A//baike.baidu.com/item/JSON)**(**[J](https://link.zhihu.com/?target=https%3A//baike.baidu.com/item/JavaScript)**[ava](https://link.zhihu.com/?target=https%3A//baike.baidu.com/item/JavaScript)**[S](https://link.zhihu.com/?target=https%3A//baike.baidu.com/item/JavaScript)**[cript](https://link.zhihu.com/?target=https%3A//baike.baidu.com/item/JavaScript) **O**bject **N**otation, JS 对象简谱) 是一种**通用和轻量级**的数据交换格式。以**文本结构**存储。



**优点**

1. 简单易用开发成本低 
2. 跨语言 
3. 轻量级数据交换 
4. 非冗长性（对比xml标签简单括号闭环）
5. 可以即时编译，用括号和引号**闭合数据块**的语法可以监测网络是否中断（因为代码可以突然解析失败），这一点优于其他的标记语言比如yaml和markdown。

**缺点**

1. 体积大，影响高并发 
2. 无版本检查，自己做兼容 
3. 片段的创建和验证过程比一般的XML复杂 
4. 缺乏命名空间导致信息混合



总结：JSON流行的原因自然离不开它爸爸（JavaScript）。作为JS对象的子集，json是最简单最通用的应用协议之一，使用广泛，开发效率高，但**性能相对较低**，维护成本较高，所以json有望被message pack取代，参考[这篇文章](http://mp.weixin.qq.com/s?__biz=MzUxNTg5Njg3Ng==&mid=2247484072&idx=1&sn=d45b3c5180c613c799274b7eba41d557&chksm=f9aee1ebced968fdf0424e9e2abc46b93d264704f9cadc4a1016d93e3195d7fb37cdfca9e2fd&scene=21#wechat_redirect)。



### 2.2 Protobuf

**protocol buffer**是Google的一种**独立和轻量级**的数据交换格式。以**二进制结构**进行存储。Protobuf是一种以有效并可扩展的格式编码结构化数据的方式。

**优点**

1. 跨语言，可自定义数据结构。 
2. 字段被编号，新添加的字段不影响老结构。解决了向后兼容问题。
3. 自动化生成代码，简单易用。 
4. 二进制消息，效率高，性能高。

**缺点**

1. 二进制格式，可读性差（抓包dump后的数据很难看懂）
2. 对象冗余，字段很多，生成的类较大，占用空间。 
3. 默认不具备动态特性（可以通过动态定义生成消息类型或者动态编译支持）

总结：简单快速上手，高效兼容性强，维护成本较高。



### 2.3 MessagePack

![](F:\GitHub\README_\infer\serialization\imgs\3.png)

**优点**

1. 跨语言，多语言支持(超多) 
2. It’s like JSON.but fast and small.序列化反序列化效率高（比json快一倍），文件体积小，比json小一倍。 
3. 兼容所有json数据格式，独有二进制类型，date类型等。
4. 提供流接口

**缺点**

1. 缺乏复杂模型支持。【但可定制】 
2. 流行度不高，原生支持的平台不多。



总结：高性能但目前的维护成本较高。



### 2.4 YAML

> YAML: YAML Ain’t Markup Language.

yaml的可读性可能比json还强，因为它用空白字符实现缩进，取代了括号和引号。yaml还支持特殊的“内部引用”语法，给人一种“可编程”的感觉。事实上yaml的规格超级巨大，非常复杂，和轻量级的json形成鲜明对比。yaml序列化以后是这样的：

```javascript
- name: William
  last name: Bailey
  dob: 1962
  nickname: Axl Rose
  instruments:
    - vocals
    - piano

- name: Saul
  last name: Hudson
  dob: 1965
  nickname: Slash
  instruments:
    - guitar
```

### 2.5 Thrift（Facebook）

**优点**

1. 序列化和RPC支持一站式解决，比pb更方便 
2. 跨语言，IDL接口定义语言，自动生成多语言文件 
3. 省流量，体积较小 
4. 包含完整的客户端/服务端堆栈，可快速实现RPC 5 为服务端提供了多种工作模式，如线程池模型、非阻塞模型

**缺点**

1. 不支持双通道 
2. rpc方法非线程安全，服务器容易被挂死，需要串行化。 
3. 默认不具备动态特性（可以通过动态定义生成消息类型或者动态编译支持）
4. 开发环境、编译较麻烦



总结：跨语言、实现简单，初次使用较麻烦，需要避免使用问题和场景限制。

### 2.6 BSON

bson有以下特性：

方便存储二进制信息：更适合交换图像和附件

专为快速内存操作而设计

简单的规范：像JSON一样，BSON有一个非常简短的规范

BSON是[MongoDB](https://cloud.tencent.com/product/mongodb?from=10680)的主要存储结构和传输协议：BSON旨在轻松遍历

额外数据类型：

- double（64位IEEE 754浮点数）
- date（自Unix纪元以来的整数毫秒数）
- 字节数组（二进制数据）
- BSON对象和BSON阵列
- JavaScript代码
- MD5二进制数据
- 正则表达式

BSON的名字取得倒是好听（Binary JSON），容易让人产生一种BSON就是标准二进制json的错觉，我们不能被这个标题党忽悠。



### 2.7 MessagePack VS BSON

这2款产品都宣称是二进制的json，关于2者的优劣一直争论不休。事实上msgpack和bson并不是竞争关系，而是适用于不同场景：

- msgpack适用于空间效率要求高的场景：网络传输；
- bson适用于时间效率要求高的场景：数据库的CRUD；

所以msgpack更加紧凑，体积小，符合最优编码；而bson比较冗长，但增删改查比较快。

StackOverflow上MessagePack的原作者也给出了自己的看法，客观的说明了msgpack和bson的应用场景：msgpack为网络服务，bson为数据库服务。



### 2.8 XML VS JSON VS Protobuf

![img](F:\GitHub\README_\infer\serialization\imgs\4.png)

**名词解释：**

- **通用：协议是标准的，不同的第三方软件都可以相互进行序列化和反序列化，比如使用cjson序列化后的数据，可以使用jsoncpp反序列化。**
- **独立：标准是私有的，比如protocol buffer协议，目前只有Google自家支持。**
- **文本格式：可以看出内容的具体文字含义，比如**

![img](F:/GitHub/README-1/notes/serialization/imgs/5.png)

- **二进制格式：纯数值的数据，可读性不强。比如protobuf序列化后的数据。**



#### 2.8.1 速度测试和序列化后数据大小对比

**测试10万次序列化**



![img](F:\GitHub\README_\infer\serialization\imgs\6.png)



**测试10万次反序列化**



![img](F:\GitHub\README_\infer\serialization\imgs\7.png)



#### 2.8.2 带宽计算对比



**以腾讯云带宽成本进行核算**



![img](F:/GitHub/README-1/notes/serialization/imgs/8.png)



**以QPS 1万计算**



![img](F:\GitHub\README_\infer\serialization\imgs\9.png)


