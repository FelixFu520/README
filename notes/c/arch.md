# C++

2020年12月4日

---

对应语法

## 基础知识

### 1⃣️量

- 常量
  - #define
  - const
- 变量



### 2⃣️数据类型

**简单**

- 整型：short int long sizeof
- 实数:   float,double
- 字符型:转义字符
- 字符串:C语言风格, C++风格
- 布尔值

**复合**

- 数组
  - 一维数组
  - 二维数组
- 结构体
  - 结构体数组
  - 结构体指针

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
- 声明
  - 文件分写

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

- 代码区
- 全局区：存放全局变量和静态变量以及常量
- 栈：不要返回栈区内容
- 堆：new delete[]

### 2⃣️引用

- 引用的本质：int* const ref = &a
- 常量引用：const int& v

### 3⃣️函数的提高

- 默认参数
- 函数重载
  - 同一个作用域下
  - 函数名称相同
  - 函数参数**类型不同** 或者 **个数不同** 或者 **顺序不同**

### 4⃣️类和对象

#### 封装

- 封装
  - 意义1:属性和方法放到一起
  - 意义2:public、protected、private
- 继承
- 多态



#### 对象的初始化和清理

- 构造函数

  - 两种分类方式：

    -  按参数分为： 有参构造和无参构造

    -  按类型分为： 普通构造和拷贝构造
  - 三种调用方式：

    - 无参构造
    - 括号法
  - 显示法
    -  隐式转换法
  - 深拷贝与浅拷贝问题
  - 初始化列表
  - 静态成员
    - 静态变量
    - 静态函数
- 析构函数

#### C++对象模型和this指针



#### 友元

- 全局函数做友元
- 类做友元
- 成员函数做友元

#### 运算符重载

- 加法运算符重载
- 左移运算符重载
- 递增运算符重载
- 赋值运算符重载
- 关系运算符重载
- 函数调用运算符重载（仿函数）

#### 继承

- 继承的基本语法
- 继承方式
- 继承中的对象模型
- 继承中构造和析构顺序
- 继承同名静态成员处理方式
- 多继承语法
- 菱形继承

#### 多态

- 多态的基本概念
- 纯虚函数和抽象类
-  虚析构和纯虚析构

### 5⃣️文件操作

#### 文本文件



#### 二进制文件



## 提高编程

### 1⃣️模版

- 函数模板
  -  函数模板语法
  - 函数模板注意事项
  - 普通函数与函数模板的区别
  - 普通函数与函数模板的调用规则
  - 模板的局限性
- 类模板
  - 类模板语法
  - 类模板与函数模板区别
  - 类模板中成员函数创建时机
  - 类模板对象做函数参数
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

- 函数对象
- 谓词
- 内建函数对象



### 5⃣️STL- 常用算法

- 常用遍历算法

- 常用查找算法

- 常用排序算法

- 常用拷贝和替换算法

- 常用算术生成算法

- 常用集合算法

  





