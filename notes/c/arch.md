# C++

2020年12月4日

[C++ Standard Library headers](https://en.cppreference.com/w/cpp/header)− C++ 标准库





---

对应语法

## 数据结构

### 0⃣️数组

### 1⃣️队列

### 2⃣️链表

### 3⃣️树

### 4⃣️图

### 5⃣️堆

### 6⃣️栈

### 7⃣️散列表

## 基础知识

### 0⃣️存储类

存储类定义 C++ 程序中变量/函数的范围（可见性）和生命周期。这些说明符放置在它们所修饰的类型之前。下面列出 C++ 程序中可用的存储类：

- auto
- register
- static
- extern
- mutable
- thread_local (C++11)

从 C++ 17 开始，auto 关键字不再是 C++ 存储类说明符，且 register 关键字被弃用。

### 1⃣️量

- 常量
  - #define
  
  - const
  
  - 整数常量
  
    - 85         // 十进制 
    - 0213       // 八进制  
    - 0x4b       // 十六进制  
    - 30         // 整数  
    - 30u        // 无符号整数  
    - 30l        // 长整数  
    - 30ul       // 无符号长整数
  
  - 浮点常量
  
    - 3.14159       // 合法的 
    -  314159E-5L    // 合法的  
    - 510E          // 非法的：不完整的指数 
    - 210f          // 非法的：没有小数或指数
    -  .e55          // 非法的：缺少整数或分数
  
  - 布尔常量
  
  - 字符常量
  
  - 字符串常量
  
    
  
- 变量

  - 作用域
    - 局部变量
    - 全局变量

### 2⃣️数据类型

**简单**

- 整型：short int long sizeof
- 实数:   float,double
- 字符型:转义字符
- 字符串:C语言风格, C++风格
- 布尔值

| 类型               | 位            | 范围                                                         |
| :----------------- | :------------ | :----------------------------------------------------------- |
| char               | 1 个字节      | -128 到 127 或者 0 到 255                                    |
| unsigned char      | 1 个字节      | 0 到 255                                                     |
| signed char        | 1 个字节      | -128 到 127                                                  |
| int                | 4 个字节      | -2147483648 到 2147483647                                    |
| unsigned int       | 4 个字节      | 0 到 4294967295                                              |
| signed int         | 4 个字节      | -2147483648 到 2147483647                                    |
| short int          | 2 个字节      | -32768 到 32767                                              |
| unsigned short int | 2 个字节      | 0 到 65,535                                                  |
| signed short int   | 2 个字节      | -32768 到 32767                                              |
| long int           | 8 个字节      | -9,223,372,036,854,775,808 到 9,223,372,036,854,775,807      |
| signed long int    | 8 个字节      | -9,223,372,036,854,775,808 到 9,223,372,036,854,775,807      |
| unsigned long int  | 8 个字节      | 0 到 18,446,744,073,709,551,615                              |
| float              | 4 个字节      | 精度型占4个字节（32位）内存空间，+/- 3.4e +/- 38 (~7 个数字) |
| double             | 8 个字节      | 双精度型占8 个字节（64位）内存空间，+/- 1.7e +/- 308 (~15 个数字) |
| long double        | 16 个字节     | 长双精度型 16 个字节（128位）内存空间，可提供18-19位有效数字。 |
| wchar_t            | 2 或 4 个字节 | 1 个宽字符                                                   |

从上表可得知，变量的大小会根据编译器和所使用的电脑而有所不同。

**复合**

- 数组
  - 一维数组
  - 二维数组
- 结构体
  - 结构体数组
  - 结构体指针



**typedef 声明**

- typedef type newname; 

**枚举类型**

```
enum 枚举名{ 
     标识符[=整型常数], 
     标识符[=整型常数], 
... 
    标识符[=整型常数]
} 枚举变量;
```



### 3⃣️输入输出

- 输入 cin
- 输出cout

### 4⃣️运算符

- 算数
- 赋值
- 比较
- 逻辑

### 5⃣️流程控制

- 顺序
- 分支：if, 三目运算符, switch
- 循环：while，do while, for
- Break, continue, goto

### 6⃣️函数

- 定义
  - 返回值类型
  - 函数名
  - 参数表列
  - 函数体语句
  - return 表达式
- 调用
  - 值传递
  - 地址传递
  - 引用传值
- 声明
  - 文件分写
- Lambda 函数与表达式

### 7⃣️指针

- 定义语法
- 空指针和野指针
- const
  - 修饰指针	const int * p1 = &a;const修饰的是指针，指针指向可以改，指针指向的值不可以更改--常量指针	
  - 修饰常量    int * const p2 = &a;const修饰的是常量，指针指向不可以改，指针指向的值可以更改--指针常量
  - 两者皆修饰
  - Int * 代表量；p1代指针。const int * p表示常量指针，量不支持改，指向可改；同理，int * const p表示指针常量，量可改，指针不可改。
- 指针与数组
- 指针与函数

## 核心编程

### 1⃣️内存分区

- #### 程序运行前
  - 代码区：存放函数体的二进制代码，由操作系统进行管理的
  - 全局区：存放全局变量和静态变量以及常量

- #### 程序运行后

  - 栈区：由编译器自动分配释放, 存放函数的参数值,局部变量等
  - 堆区：由程序员分配和释放,若程序员不释放,程序结束时由操作系统回收

- #### new操作符

  - new
  - delete[]

### 2⃣️引用

- #### 基本使用

  - 语法：数据类型 &别名 = 原名

- #### 引用注意事项

  - 引用必须初始化
  - 引用在初始化后，不可以改变

- #### 引用做函数参数

  - **作用：**函数传参时，可以利用引用的技术让形参修饰实参
  - **优点：**可以简化指针修改实参

- #### 引用做函数返回值

  - 作用：引用是可以作为函数的返回值存在的
  - 注意：**不要返回局部变量引用**
  - 用法：函数调用作为左值

- #### 引用的本质

  - int* const ref = &a

- #### 常量引用：

  - 主要用来修饰形参，防止误操作  const int& v

### 3⃣️函数的提高

- #### 默认参数

- #### 函数占位参数

- #### 函数重载
  
  - 概述
  - 条件
    - 同一个作用域下
    - 函数名称相同
    - 函数参数**类型不同** 或者 **个数不同** 或者 **顺序不同**

### 4⃣️类和对象

- #### 封装
  - 意义1:属性和方法放到一起
  - 意义2:public、protected、private
  - struct和class区别

- #### 对象的初始化和清理
  - 构造函数
    - 语法
    - 两种分类方式：

      -  按参数分为： 有参构造和无参构造

      -  按类型分为： 普通构造和拷贝构造
    - 三种调用方式：

      - 无参调用
      - 括号法
      - 显示法
      -  隐式转换法
    - 拷贝构造函数调用时机
      - 使用一个已经创建完毕的对象来初始化一个新对象
      - 值传递的方式给函数参数传值
      - 以值方式返回局部对象
    - 深拷贝与浅拷贝问题
      - 浅拷贝：简单的赋值拷贝操作
      - 深拷贝：在堆区重新申请空间，进行拷贝操作
    - 初始化列表
      - 构造函数()：属性1(值1),属性2（值2）... {}
    - 静态成员
      - 静态成员变量
        - 所有对象共享同一份数据
        - 在编译阶段分配内存
        - 类内声明，类外初始化
      - 静态成员函数
        - 所有对象共享同一个函数
        - 静态成员函数只能访问静态成员变量
  - 析构函数

- #### C++对象模型和this指针

  - 成员变量和成员函数分开存储

  - this指针概念

  - 空指针访问成员函数

  - **const修饰成员函数**

    **常函数：**

    - 成员函数后加const后我们称为这个函数为**常函数**
    - 常函数内不可以修改成员属性
    - 成员属性声明时加关键字mutable后，在常函数中依然可以修改

    **常对象：**

    - 声明对象前加const称该对象为常对象
    - 常对象只能调用常函数

- #### 友元
  - 全局函数做友元
  - 类做友元
  - 成员函数做友元

- #### 运算符重载
  - 加法运算符重载
  - 左移运算符重载
  - 递增运算符重载
  - 赋值运算符重载
  - 关系运算符重载
  - 函数调用运算符重载（仿函数）

- #### 继承
  - 继承的基本语法
  - 继承方式
    - 公共继承
    - 保护继承
    - 私有继承
  - 继承中的对象模型
    - 从父类继承过来的成员，哪些属于子类对象中？
  - 继承中构造和析构顺序
  - 继承同名成员处理方式
    - 访问子类同名成员 直接访问即可
    - 访问父类同名成员 需要加作用域
  - 继承同名静态成员处理方式
    - 访问子类同名成员 直接访问即可
    - 访问父类同名成员 需要加作用域
  - 多继承语法
  - 菱形继承
    - 菱形继承带来的主要问题是子类继承两份相同的数据，导致资源浪费以及毫无意义
    - 利用虚继承可以解决菱形继承问题

- #### 多态
  - 多态的基本概念

    - 静态多态: 函数重载 和 运算符重载属于静态多态，复用函数名
    - 动态多态: 派生类和虚函数实现运行时多态
    - 静态多态的函数地址早绑定 - 编译阶段确定函数地址
    - 动态多态的函数地址晚绑定 - 运行阶段确定函数地址

  - 纯虚函数和抽象类

    - virtual 返回值类型 函数名 （参数列表）= 0 ;

  -  虚析构和纯虚析构

    - 多态使用时，如果子类中有属性开辟到堆区，那么父类指针在释放时无法调用到子类的析构代码

    - 解决方式：将父类中的析构函数改为**虚析构**或者**纯虚析构**

    - 虚析构和纯虚析构共性：

      - 可以解决父类指针释放子类对象
      - 都需要有具体的函数实现

    - 虚析构和纯虚析构区别：

      - 如果是纯虚析构，该类属于抽象类，无法实例化对象
      - 虚析构语法：virtual ~类名(){}
      - 纯虚析构语法：virtual ~类名() = 0;类名::~类名(){}

      

### 5⃣️文件操作

| 打开方式    | 解释                       |
| ----------- | -------------------------- |
| ios::in     | 为读文件而打开文件         |
| ios::out    | 为写文件而打开文件         |
| ios::ate    | 初始位置：文件尾           |
| ios::app    | 追加方式写文件             |
| ios::trunc  | 如果文件存在先删除，再创建 |
| ios::binary | 二进制方式                 |

- #### 文本文件

  - 写文件

    - 包含头文件

      \#include <fstream>

    - 创建流对象

      ofstream ofs;

    - 打开文件

      ofs.open("文件路径",打开方式);

    - 写数据

      ofs << "写入的数据";

    - 关闭文件

      ofs.close();

  - 读文件

    - 包含头文件

      \#include <fstream>

    - 创建流对象

      ifstream ifs;

    - 打开文件并判断文件是否打开成功

      ifs.open("文件路径",打开方式);

    - 读数据

      四种方式读取:while (getline(ifs, buf))

    - 关闭文件

      ifs.close();

- #### 二进制文件

  - 写文件
  - 读文件

### 6⃣️异常处理

[异常类结构树&自定义异常](https://www.runoob.com/cplusplus/cpp-exceptions-handling.html)

```
try
{
   // 保护代码
}catch( ExceptionName e1 )
{
   // catch 块
}catch( ExceptionName e2 )
{
   // catch 块
}catch( ExceptionName eN )
{
   // catch 块
}
```

```
double division(int a, int b)
{
   if( b == 0 )
   {
      throw "Division by zero condition!";
   }
   return (a/b);
}
```

### 7⃣️命名空间

- 定义
  - namespace namespace_name {   // 代码声明 }
- 调用
  - name::code;  // code 可以是变量或函数

### 8⃣️预处理器

[🔗](https://www.runoob.com/cplusplus/cpp-preprocessor.html)

- #**define** **预处理**

- 参数宏：\#define MIN(a,b) (a<b ? a : b)

- 条件编译

  - ```
    #ifdef DEBUG 
       cerr <<"Variable x = " << x << endl;
    #endif
    
    ```

- #和 ## 运算符

C++ 提供了下表所示的一些预定义宏：

| 宏       | 描述                                                         |
| :------- | :----------------------------------------------------------- |
| __LINE__ | 这会在程序编译时包含当前行号。                               |
| __FILE__ | 这会在程序编译时包含当前文件名。                             |
| __DATE__ | 这会包含一个形式为 month/day/year 的字符串，它表示把源文件转换为目标代码的日期。 |
| __TIME__ | 这会包含一个形式为 hour:minute:second 的字符串，它表示程序被编译的时间。 |

### 9⃣️信号处理

[🔗](https://www.runoob.com/cplusplus/cpp-signal-handling.html)

信号是由操作系统传给进程的中断，会提早终止一个程序。在 UNIX、LINUX、Mac OS X 或 Windows 系统上，可以通过按 Ctrl+C 产生中断。

有些信号不能被程序捕获，但是下表所列信号可以在程序中捕获，并可以基于信号采取适当的动作。这些信号是定义在 C++ 头文件 <csignal> 中。

| 信号    | 描述                                         |
| :------ | :------------------------------------------- |
| SIGABRT | 程序的异常终止，如调用 **abort**。           |
| SIGFPE  | 错误的算术运算，比如除以零或导致溢出的操作。 |
| SIGILL  | 检测非法指令。                               |
| SIGINT  | 程序终止(interrupt)信号。                    |
| SIGSEGV | 非法访问内存。                               |
| SIGTERM | 发送到程序的终止请求。                       |

- signal() 函数
- raise() 函数

### 🔟多线程

[Link](https://www.runoob.com/cplusplus/cpp-multithreading.html)

### 1⃣️1⃣️Web 编程

[Link](https://www.runoob.com/cplusplus/cpp-web-programming.html)







## 提高编程

### 1⃣️模版

- #### 概念

- #### 函数模板

  -  函数模板语法。template<typename T>
  - 函数模板注意事项
    - 自动类型推导，必须推导出一致的数据类型T,才可以使用
    - 模板必须要确定出T的数据类型，才可以使用
  - 普通函数与函数模板的区别
    - 普通函数调用时可以发生自动类型转换（隐式类型转换）
    - 函数模板调用时，如果利用自动类型推导，不会发生隐式类型转换
    - 如果利用显示指定类型的方式，可以发生隐式类型转换
  - 普通函数与函数模板的调用规则
  - 模板的局限性

- #### 类模板

  - 类模板语法  template<typename T>
  - 类模板与函数模板区别
    - 类模板没有自动类型推导的使用方式
    - 类模板在模板参数列表中可以有默认参数
  - 类模板中成员函数创建时机
  - 类模板对象做函数参数
    - 指定传入的类型 --- 直接显示对象的数据类型
    - 参数模板化 --- 将对象中的参数变为模板进行传递
    - 整个类模板化 --- 将这个对象类型 模板化进行传递
  - 类模板与继承
  - 类模板成员函数类外实现
  - 类模板分文件编写
  - 类模板与友元

### 2⃣️STL初识

**容器、算法、迭代器、仿函数、适配器（配接器）、空间配置器**

- 容器
  - 数组, 列表，链表, 堆栈、树, 图, 集合, 映射表……
  - **序列式容器**和**关联式容器**
- 算法
  - 拷贝，替换，删除；查找、计数、遍历、寻找极值
  - **质变算法**和**非质变算法**
- 迭代器
  - 双向迭代器，和随机访问迭代器





### 3⃣️STL-常用容器

- #### string容器

  - 概念：char * 和string区别
  - 构造：
    - `string();` //创建一个空的字符串 例如: string str;
    - `string(const char* s);` //使用字符串s初始化
    - `string(const string& str);` //使用一个string对象初始化另一个string对象
    - `string(int n, char c);` //使用n个字符c初始化
  - 赋值操作
    - `string& operator=(const char* s);` //char*类型字符串 赋值给当前的字符串
    - `string& operator=(const string &s);` //把字符串s赋给当前的字符串
    - `string& operator=(char c);` //字符赋值给当前的字符串
    - `string& assign(const char *s);` //把字符串s赋给当前的字符串
    - `string& assign(const char *s, int n);` //把字符串s的前n个字符赋给当前的字符串
    - `string& assign(const string &s);` //把字符串s赋给当前字符串
    - `string& assign(int n, char c);` //用n个字符c赋给当前字符串
  - 拼接操作
    - `string& operator+=(const char* str);` //重载+=操作符
    - `string& operator+=(const char c);` //重载+=操作符
    - `string& operator+=(const string& str);` //重载+=操作符
    - `string& append(const char *s); `//把字符串s连接到当前字符串结尾
    - `string& append(const char *s, int n);` //把字符串s的前n个字符连接到当前字符串结尾
    - `string& append(const string &s);` //同operator+=(const string& str)
    - `string& append(const string &s, int pos, int n);`//字符串s中从pos开始的n个字符连接到字符串结尾
  - 查找和替换
    - `int find(const string& str, int pos = 0) const;` //查找str第一次出现位置,从pos开始查找
    - `int find(const char* s, int pos = 0) const; `//查找s第一次出现位置,从pos开始查找
    - `int find(const char* s, int pos, int n) const; `//从pos位置查找s的前n个字符第一次位置
    - `int find(const char c, int pos = 0) const; `//查找字符c第一次出现位置
    - `int rfind(const string& str, int pos = npos) const;` //查找str最后一次位置,从pos开始查找
    - `int rfind(const char* s, int pos = npos) const;` //查找s最后一次出现位置,从pos开始查找
    - `int rfind(const char* s, int pos, int n) const;` //从pos查找s的前n个字符最后一次位置
    - `int rfind(const char c, int pos = 0) const; `//查找字符c最后一次出现位置
    - `string& replace(int pos, int n, const string& str); `//替换从pos开始n个字符为字符串str
    - `string& replace(int pos, int n,const char* s); `//替换从pos开始的n个字符为字符串s
  - 比较操作
    - `int compare(const string &s) const; `//与字符串s比较
    - `int compare(const char *s) const;` //与字符串s比较
  - 存取操作
    - `char& operator[](int n); `//通过[]方式取字符
    - `char& at(int n); `//通过at方法获取字符
  - 插入和删除
    - `string& insert(int pos, const char* s); `//插入字符串
    - `string& insert(int pos, const string& str); `//插入字符串
    - `string& insert(int pos, int n, char c);` //在指定位置插入n个字符c
    - `string& erase(int pos, int n = npos);` //删除从Pos开始的n个字符
  - 子串
    - `string substr(int pos = 0, int n = npos) const;` //返回由pos开始的n个字符组成的字符串

- #### vector容器

  - 概念
  - 构造
    - `vector<T> v; `//采用模板实现类实现，默认构造函数
    - `vector(v.begin(), v.end()); `//将v[begin(), end())区间中的元素拷贝给本身。
    - `vector(n, elem);` //构造函数将n个elem拷贝给本身。
    - `vector(const vector &vec);` //拷贝构造函数。
  - 赋值操作
    - `vector& operator=(const vector &vec);`//重载等号操作符
    - `assign(beg, end);` //将[beg, end)区间中的数据拷贝赋值给本身。
    - `assign(n, elem);` //将n个elem拷贝赋值给本身。
  - 容量和大小
    - `empty(); `//判断容器是否为空
    - `capacity();` //容器的容量
    - `size();` //返回容器中元素的个数
    - `resize(int num);` //重新指定容器的长度为num，若容器变长，则以默认值填充新位置。 //如果容器变短，则末尾超出容器长度的元素被删除。
    - `resize(int num, elem);` //重新指定容器的长度为num，若容器变长，则以elem值填充新位置。 //如果容器变短，则末尾超出容器长度的元素被删除
  - 插入和删除
    - `push_back(ele);` //尾部插入元素ele
    - `pop_back();` //删除最后一个元素
    - `insert(const_iterator pos, ele);` //迭代器指向位置pos插入元素ele
    - `insert(const_iterator pos, int count,ele);`//迭代器指向位置pos插入count个元素ele
    - `erase(const_iterator pos);` //删除迭代器指向的元素
    - `erase(const_iterator start, const_iterator end);`//删除迭代器从start到end之间的元素
    - `clear();` //删除容器中所有元素
  - 数据存取
    - `at(int idx); `//返回索引idx所指的数据
    - `operator[]; `//返回索引idx所指的数据
    - `front(); `//返回容器中第一个数据元素
    - `back();` //返回容器中最后一个数据元素
  - 互换容器
    - `swap(vec);` // 将vec与本身的元素互换
  - 预留空间
    - `reserve(int len);`//容器预留len个元素长度，预留位置不初始化，元素不可访问。

  

- #### deque容器

  - 概念
  - 构造
    - `deque<T>` deqT; //默认构造形式
    - `deque(beg, end);` //构造函数将[beg, end)区间中的元素拷贝给本身。
    - `deque(n, elem);` //构造函数将n个elem拷贝给本身。
    - `deque(const deque &deq);` //拷贝构造函数
  - 赋值操作
    - `deque& operator=(const deque &deq); `//重载等号操作符
    - `assign(beg, end);` //将[beg, end)区间中的数据拷贝赋值给本身。
    - `assign(n, elem);` //将n个elem拷贝赋值给本身。
  - 大小操作
    - `deque.empty();` //判断容器是否为空
    - `deque.size();` //返回容器中元素的个数
    - `deque.resize(num);` //重新指定容器的长度为num,若容器变长，则以默认值填充新位置。 //如果容器变短，则末尾超出容器长度的元素被删除。
    - `deque.resize(num, elem);` //重新指定容器的长度为num,若容器变长，则以elem值填充新位置。 //如果容器变短，则末尾超出容器长度的元素被删除。
  - 插入操作
    - `push_back(elem);` //在容器尾部添加一个数据
    - `push_front(elem);` //在容器头部插入一个数据
    - `pop_back();` //删除容器最后一个数据
    - `pop_front();` //删除容器第一个数据
    -  
    - `insert(pos,elem);` //在pos位置插入一个elem元素的拷贝，返回新数据的位置。
    - `insert(pos,n,elem);` //在pos位置插入n个elem数据，无返回值。
    - `insert(pos,beg,end);` //在pos位置插入[beg,end)区间的数据，无返回值。
    - `clear();` //清空容器的所有数据
    - `erase(beg,end);` //删除[beg,end)区间的数据，返回下一个数据的位置。
    - `erase(pos);` //删除pos位置的数据，返回下一个数据的位置。
  - 存取操作
    - `at(int idx); `//返回索引idx所指的数据
    - `operator[]; `//返回索引idx所指的数据
    - `front(); `//返回容器中第一个数据元素
    - `back();` //返回容器中最后一个数据元素
  - 排序
    - `sort(iterator beg, iterator end)` //对beg和end区间内元素进行排序

- #### stack容器

  - 构造函数：
    - `stack<T> stk;` //stack采用模板类实现， stack对象的默认构造形式
    - `stack(const stack &stk);` //拷贝构造函数
  - 赋值操作：
    - `stack& operator=(const stack &stk);` //重载等号操作符
  - 数据存取：
    - `push(elem);` //向栈顶添加元素
    - `pop();` //从栈顶移除第一个元素
    - `top(); `//返回栈顶元素
  - 大小操作：
    - `empty();` //判断堆栈是否为空
    - `size(); `//返回栈的大小

- #### queue 容器

  - 构造函数：

    - `queue<T> que;` //queue采用模板类实现，queue对象的默认构造形式
    - `queue(const queue &que);` //拷贝构造函数

  - 赋值操作：

    - `queue& operator=(const queue &que);` //重载等号操作符

  - 数据存取：

    - `push(elem);` //往队尾添加元素
    - `pop();` //从队头移除第一个元素
    - `back();` //返回最后一个元素
    - `front(); `//返回第一个元素

    大小操作：

    - `empty();` //判断堆栈是否为空
    - `size(); `//返回栈的大小

- #### list容器

  - list概念
  - 构造
    - `list<T> lst;` //list采用采用模板类实现,对象的默认构造形式：
    - `list(beg,end);` //构造函数将[beg, end)区间中的元素拷贝给本身。
    - `list(n,elem);` //构造函数将n个elem拷贝给本身。
    - `list(const list &lst);` //拷贝构造函数。
  - 赋值和交换
    - `assign(beg, end);` //将[beg, end)区间中的数据拷贝赋值给本身。
    - `assign(n, elem);` //将n个elem拷贝赋值给本身。
    - `list& operator=(const list &lst);` //重载等号操作符
    - `swap(lst);` //将lst与本身的元素互换。
  - 大小操作
    - `size(); `//返回容器中元素的个数
    - `empty(); `//判断容器是否为空
    - `resize(num);` //重新指定容器的长度为num，若容器变长，则以默认值填充新位置。 //如果容器变短，则末尾超出容器长度的元素被删除。
    - `resize(num, elem); `//重新指定容器的长度为num，若容器变长，则以elem值填充新位置。
  - 插入与删除
    - push_back(elem);//在容器尾部加入一个元素
    - pop_back();//删除容器中最后一个元素
    - push_front(elem);//在容器开头插入一个元素
    - pop_front();//从容器开头移除第一个元素
    - insert(pos,elem);//在pos位置插elem元素的拷贝，返回新数据的位置。
    - insert(pos,n,elem);//在pos位置插入n个elem数据，无返回值。
    - insert(pos,beg,end);//在pos位置插入[beg,end)区间的数据，无返回值。
    - clear();//移除容器的所有数据
    - erase(beg,end);//删除[beg,end)区间的数据，返回下一个数据的位置。
    - erase(pos);//删除pos位置的数据，返回下一个数据的位置。
    - remove(elem);//删除容器中所有与elem值匹配的元素。
  - 存取
    - `front();` //返回第一个元素。
    - `back();` //返回最后一个元素
  - 反转和排序
    - `reverse();` //反转链表
    - `sort();` //链表排序

- #### set/ multiset 容器

  - set基本概念
  - 构造和赋值
    - `set<T> st;` //默认构造函数：
    - `set(const set &st);` //拷贝构造函数
    - `set& operator=(const set &st);` //重载等号操作符
  - 大小和交换
    - `size();` //返回容器中元素的数目
    - `empty();` //判断容器是否为空
    - `swap(st);` //交换两个集合容器
  - 插入和删除
    - `insert(elem);` //在容器中插入元素。
    - `clear();` //清除所有元素
    - `erase(pos);` //删除pos迭代器所指的元素，返回下一个元素的迭代器。
    - `erase(beg, end);` //删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器。
    - `erase(elem);` //删除容器中值为elem的元素。
  - 查找和统计
    - `find(key);` //查找key是否存在,若存在，返回该键的元素的迭代器；若不存在，返回set.end();
    - `count(key);` //统计key的元素个数
  - set和multiset区别
  - pair对组
    - `pair<type, type> p ( value1, value2 );`
    - `pair<type, type> p = make_pair( value1, value2 );`
  - set容器排序
    - 利用仿函数可以指定set容器的排序规则
    - set存放自定义数据类型

- #### map/ multimap容器

  - map基本概念
  - 构造和赋值
    - `map<T1, T2> mp;` //map默认构造函数:
    - `map(const map &mp);` //拷贝构造函数
    - `map& operator=(const map &mp);` //重载等号操作符
  - 大小和交换
    - `size();` //返回容器中元素的数目
    - `empty();` //判断容器是否为空
    - `swap(st);` //交换两个集合容器
  - 插入和删除
    - `insert(elem);` //在容器中插入元素。
    - `clear();` //清除所有元素
    - `erase(pos);` //删除pos迭代器所指的元素，返回下一个元素的迭代器。
    - `erase(beg, end);` //删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器。
    - `erase(key);` //删除容器中值为key的元素。
  - 查找和统计
    - `find(key);` //查找key是否存在,若存在，返回该键的元素的迭代器；若不存在，返回set.end();
    - `count(key);` //统计key的元素个数
  - 排序
    - 利用仿函数，可以改变排序规则



### 4⃣️STL- 函数对象

- #### 函数对象

  - 概念
  - 函数对象使用

- #### 谓词

  - 谓词概念
  - 一元谓词
  - 二元谓词

- #### 内建函数对象

  - 意义
  - 算术仿函数
    - `template<class T> T plus<T>` //加法仿函数
    - `template<class T> T minus<T>` //减法仿函数
    - `template<class T> T multiplies<T>` //乘法仿函数
    - `template<class T> T divides<T>` //除法仿函数
    - `template<class T> T modulus<T>` //取模仿函数
    - `template<class T> T negate<T>` //取反仿函数
  - 关系仿函数
    - `template<class T> bool equal_to<T>` //等于
    - `template<class T> bool not_equal_to<T>` //不等于
    - `template<class T> bool greater<T>` //大于
    - `template<class T> bool greater_equal<T>` //大于等于
    - `template<class T> bool less<T>` //小于
    - `template<class T> bool less_equal<T>` //小于等于
  - 逻辑仿函数
    - `template<class T> bool logical_and<T>` //逻辑与
    - `template<class T> bool logical_or<T>` //逻辑或
    - `template<class T> bool logical_not<T>` //逻辑非



### 5⃣️STL- 常用算法

- #### 概念：

  - 算法主要是由头文件`<algorithm>` `<functional>` `<numeric>`组成。
  - `<algorithm>`是所有STL头文件中最大的一个，范围涉及到比较、 交换、查找、遍历操作、复制、修改等等
  - `<numeric>`体积很小，只包括几个在序列上面进行简单数学运算的模板函数
  - `<functional>`定义了一些模板类,用以声明函数对象。

- #### 常用遍历算法

  - `for_each` //遍历容器。for_each(iterator beg, iterator end, _func);
  - `transform` //搬运容器到另一个容器中。transform(iterator beg1, iterator end1, iterator beg2, _func）

- #### 常用查找算法

  - `find` //查找元素   find(iterator beg, iterator end, value);
  - `find_if` //按条件查找元素  find_if(iterator beg, iterator end, _Pred);
  - `adjacent_find` //查找相邻重复元素  adjacent_find(iterator beg, iterator end);
  - `binary_search` //二分查找法  bool binary_search(iterator beg, iterator end, value);
  - `count` //统计元素个数  count(iterator beg, iterator end, value);
  - `count_if` //按条件统计元素个数  count_if(iterator beg, iterator end, _Pred);

- #### 常用排序算法

  - `sort` //对容器内元素进行排序 / sort(iterator beg, iterator end, _Pred);
  - `random_shuffle` //洗牌 指定范围内的元素随机调整次序   random_shuffle(iterator beg, iterator end);
  - `merge `// 容器元素合并，并存储到另一容器中   merge(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
  - `reverse` // 反转指定范围的元素  reverse(iterator beg, iterator end);

- #### 常用拷贝和替换算法

  - `copy` // 容器内指定范围的元素拷贝到另一容器中   copy(iterator beg, iterator end, iterator dest)
  - `replace` // 将容器内指定范围的旧元素修改为新元素. replace(iterator beg, iterator end, oldvalue, newvalue);
  - `replace_if `// 容器内指定范围满足条件的元素替换为新元素. replace_if(iterator beg, iterator end, _pred, newvalue);
  - `swap` // 互换两个容器的元素. swap(container c1, container c2);

- #### 常用算术生成算法

  - `accumulate` // 计算容器元素累计总和. accumulate(iterator beg, iterator end, value);
  - `fill` // 向容器中添加元素.  fill(iterator beg, iterator end, value);

- #### 常用集合算法

  - `set_intersection` // 求两个容器的交集. set_intersection(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
  - `set_union` // 求两个容器的并集.  set_union(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
  - `set_difference `// 求两个容器的差集.  set_difference(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);

  

## C++库

### 1⃣️标准函数库

这个库是由通用的、独立的、不属于任何类的函数组成的。函数库继承自 C 语言。

- 输入/输出 I/O

- 字符串和字符处理

- 数学

  - **<cmath>**

    - **double cos/sin/tan/log/sqrt/fabs/floor(double);**
    - **double pow(double, double);**
    - **double hypot(double, double);**
    - **int abs(int);**

  - 随机数

    - ```
      #include <iostream>
      #include <ctime>
      #include <cstdlib>
       
      using namespace std;
       
      int main ()
      {
         int i,j;
       
         // 设置种子
         srand( (unsigned)time( NULL ) );
       
         /* 生成 10 个随机数 */
         for( i = 0; i < 10; i++ )
         {
            // 生成实际的随机数
            j= rand();
            cout <<"随机数： " << j << endl;
         }
       
         return 0;
      }
      ```

  

- 时间、日期和本地化

  -  <ctime>

- 动态分配

- 其他

- 宽字符函数

### 2⃣️面向对象类库

这个库是类及其相关函数的集合。标准的 C++ 面向对象类库定义了大量支持一些常见操作的类，比如输入/输出 I/O、字符串处理、数值处理。面向对象类库包含以下内容：

- 标准的 C++ I/O 类
- String 类
- 数值类
- STL 容器类
- STL 算法
- STL 函数对象
- STL 迭代器
- STL 分配器
- 本地化库
- 异常处理类
- 杂项支持库

