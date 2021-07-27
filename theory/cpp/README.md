# C++总结

⌚️:2020年11月30日

📚参考

---



```
1 运算符
2 控制结构
3 函数
4 基本类型
5 复合类型
6 std库
7 内存模型
```

C++特点

```
1、过程式【数据结构、算法（强调算法）】
2、OOP【数据结构（强调数据）、算法】
3、泛化编程【强调是独立于特定数据类型】
```



----

## 1 运算符

| **运算符类型** | **作用**                               |
| -------------- | -------------------------------------- |
| 算术运算符     | 用于处理四则运算                       |
| 赋值运算符     | 用于将表达式的值赋给变量               |
| 比较运算符     | 用于表达式的比较，并返回一个真值或假值 |
| 逻辑运算符     | 用于根据表达式的值返回真值或假值       |

### 算术运算符

| **运算符** | **术语**   | **示例**    | **结果**  |
| ---------- | ---------- | ----------- | --------- |
| +          | 正号       | +3          | 3         |
| -          | 负号       | -3          | -3        |
| +          | 加         | 10 + 5      | 15        |
| -          | 减         | 10 - 5      | 5         |
| *          | 乘         | 10 * 5      | 50        |
| /          | 除         | 10 / 5      | 2         |
| %          | 取模(取余) | 10 % 3      | 1         |
| ++         | 前置递增   | a=2; b=++a; | a=3; b=3; |
| ++         | 后置递增   | a=2; b=a++; | a=3; b=2; |
| --         | 前置递减   | a=2; b=--a; | a=1; b=1; |
| --         | 后置递减   | a=2; b=a--; | a=1; b=2; |

### 赋值运算符

| **运算符** | **术语** | **示例**   | **结果**  |
| ---------- | -------- | ---------- | --------- |
| =          | 赋值     | a=2; b=3;  | a=2; b=3; |
| +=         | 加等于   | a=0; a+=2; | a=2;      |
| -=         | 减等于   | a=5; a-=3; | a=2;      |
| *=         | 乘等于   | a=2; a*=2; | a=4;      |
| /=         | 除等于   | a=4; a/=2; | a=2;      |
| %=         | 模等于   | a=3; a%2;  | a=1;      |

### 比较运算符

| **运算符** | **术语** | **示例** | **结果** |
| ---------- | -------- | -------- | -------- |
| ==         | 相等于   | 4 == 3   | 0        |
| !=         | 不等于   | 4 != 3   | 1        |
| <          | 小于     | 4 < 3    | 0        |
| >          | 大于     | 4 > 3    | 1        |
| <=         | 小于等于 | 4 <= 3   | 0        |
| >=         | 大于等于 | 4 >= 1   | 1        |

### 逻辑运算符

| **运算符** | **术语** | **示例** | **结果**                                               |
| ---------- | -------- | -------- | ------------------------------------------------------ |
| !          | 非       | !a       | 如果a为假，则!a为真； 如果a为真，则!a为假。            |
| &&         | 与       | a && b   | 如果a和b都为真，则结果为真，否则为假。                 |
| \|\|       | 或       | a \|\| b | 如果a和b有一个为真，则结果为真，二者都为假时，结果为假 |



## 2 控制结构

### 分支

**if else**

```
if(条件1){ 条件1满足执行的语句 }else if(条件2){条件2满足执行的语句}... else{ 都不满足执行的语句}
```



**switch**

```
switch(表达式)

{

	case 结果1：执行语句;break;

	case 结果2：执行语句;break;

	...

	default:执行语句;break;

}
```



**?:**

```
表达式1 ? 表达式2 ：表达式3
```



### 循环

**for**

```
 for(起始表达式;条件表达式;末尾循环体) { 循环语句; }
```



**while**

```
while(循环条件){ 循环语句 }
```



**do while**

```
do{ 循环语句 } while(循环条件);
```



**for each**

```
double prices[5] = {4.99, ...};
for(double x: prices)
		std::cout << x << std::endl;
```

### 异常

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



## 3 函数

##### **定义**

```
typeName functionName(parameterList)
{
	statement(s);
	return 变量/常量/表达式/可以转为typeName类型/不能是数组;
}

```

##### **声明/原型**

```
为什么需要函数原型？
原型描述了函数到编译器的接口。通常在include文件中。1、编译器正确处理函数返回值；2、编译器检查使用的参数数目是否正确；3、编译器检查使用的参数类型是否正确。

typeName funs(typeName x, parameterList); 有类型列表足以，但是为了理解还是要把变量名加上。而且变量名可以与定义时的变量名不同
```

##### **调用**

```
函数名（参数）
```

##### 函数与数组

```
数组作为函数的参数和返回值

int sum_arr(int arr[], int n);//声明
int sum_arr(int arr[], int n){...} //定义

int cookies[ArSize] = {....};
int sum = sum_arr(cookies, ArSize);//调用


在c++中数组名视为指针，数组名时其第一个元素的地址。即cookies == &cookies[0],因此等价于
int sum_arr(int * arr, int n);

总结：
arr[i] == * (ar + i) //values in two notations
&arr[i] == ar + i	//addresses in two notations

可以这样理解地址传递：sum_arr()函数仍然传递了一个值，这个值被赋给一个新的变量，但这个值是一个地址，变量可以理解为地址变量。


使用数组区间的函数——概念理解（就是int sum_arr(const int * begin, const int * end);)
```

##### 函数与二维数组

```
二维数组作为函数的参数和返回值

int data[3][4] = {{1,2,3,4}, ...};
int total = sum(data, 3) //调用

int sum(int (*arr)[4], int size);//原型，arr是指针而不是数组
或
int sum(int arr[][4], int size){访问方法：arr[r][c] == *（*（arr+r)+c)};
```

##### 函数与CStyle 字符串

```
CStyle字符串就是数组，即同处理函数与数组的内容一致。

CStyle做为函数的-参数-和-返回值-。
```

##### 函数与结构体

```
结构体相当于一个基本类型的变量，用于函数的参数、函数的返回值、函数的内部。

```

##### 函数与String

```
CStyle贴近数组，String贴近结构或对象。

string作为参数和返回值

void display(const string sa[], int n){}//声明
string list[SIZE];//调用
display(list);
```

##### 函数与array对象

```
std::array<double, 4>作为参数或者返回值
```

##### 递归

```
void recurs(argumentList){
	statements1;
	if(test){
		recurs(argumentList);
	statements2;
	}
}
```

##### 函数指针

```
与数据项相似，函数也有地址。

1、获取函数的地址：直接使用函数名
2、声明函数指针：
		double pam(int);//函数声明
		double (*pf)(int);//函数指针说明，区别double *pf(int)。 （*pf)等价于一个函数名，所以pf就是一个函数指针
		pf = pam;//函数指针赋值，注意函数的参数和返回值  是否和函数指针声明中的参数和返回值 的类型一致
3、使用指针来调用函数
		（*pf）相当于函数名，所以在调用时，使用(*pf)(args);
		C++中允许:pf(args);可以把‘*’省略
		
		
高级一点
const double * f1(const double ar[], int n);
const double * f2(const double [], int);
const double * f3(const double *, int);//三个等价

const double* (*p1)(const double *, int);
const double* (*p1)(const double *, int)=f1;
auto p2 = f2;

cout<<(*p1)(av,3);
cout<<p2(av,3);


函数指针的数组
const double * (*pa[3])(const double * , int) = {f1,f2,f3}//初始化3个函数指针数组
auto pb = pa;//auto 只能推断单个变量，不能推断数组
数组名时只想第一个元素的指针，因此pa和pb都是指向函数的指针。所以pa和pb都是函数指针的指针。
const double * px = pa[0](av,3);
const double * py = (*pb[1])(av,3);
double x = *pa[0](av,3);
double y = *(*pb[1])(av,3);

const double *(*(*pd)[3])(const double *,int) = &pa; pa数组的指针，数组名。[]运算符高于*
*pd是数组。

```

##### 内联函数

```
在函数声明前加上关键字inline
在函数定义前加上关键字inline

选择性的使用内联函数：对比执行函数代码时间与处理调用机制的时间。
```

##### 默认参数

```
在函数原型中添加
```

##### 函数重载

```
函数重载的关键是函数的参数列表（参数数目或参数类型不同）
```

##### 函数模版

```
template <typename AnyType>
void swap(AnyType &a, AnyType &b){
	AnyType temp;
	temp = a;
	a = b;
	b = temp;
}

完整实现：
//函数声明
template <typename T> 
void Swap(T &a, T &b);
//函数定义
template<typename T>
void swap(T &a, T &b){}
//函数调用
swap（a,b);



重载模版
被重载的模版的函数特征标必须不同
eg.
//声明
template <typename T>
void swap(T &a, T &b);

template <typename T>
void swap(T a[], T b[], int n);


显示具体化
stuct job {char name[40];double salary;int floor;};
void swap(job &, job &);/non template function prototype

template<typename T>//template prototype
void swap(T &, T &);

template <> void swap<job>(job&, job &);//explicit specialization for the job type 具体化


实例化
add<double>(x,m);
```



## 4 基本类型

类型转换

- 自动：赋值；算术；传参
- 强制：`(long) variable; int(variable);static_cast<long>(variable);`

### 整型

- 有无符号（unsigned）;
- 前缀表示进制；
- 后缀表示类型；
- 如何选择整型？

**char**

**short**

**int**

**long**

**long long**

**w_char**

**char16_t**

**char32_t**

### 浮点型

**float**

**double**

**long double**



## 5 复合类型

### 数组

定义

```
数据类型 数组名[ 数组长度 ];
数据类型 数组名[ 数组长度 ] = { 值1，值2 ...};
数据类型 数组名[ ] = { 值1，值2 ...};

确定长度和类型即可。是为了确定内存大小
typeName arrayName[arraySize];
arraySize可以是整数常量、const值、常量表达式
```

初始化

```
arr[0] = 1;//单个初始化
int arr[2] = {1,2};//定义时初始化
```

调用

```
arr[0];
```



### 二维数组

定义

```
数据类型 数组名[ 行数 ][ 列数 ];
数据类型 数组名[ 行数 ][ 列数 ] = { {数据1，数据2 } ，{数据3，数据4 } };
数据类型 数组名[ 行数 ][ 列数 ] = { 数据1，数据2，数据3，数据4};
数据类型 数组名[ ][ 列数 ] = { 数据1，数据2，数据3，数据4};
```



### 字符串

**C-Style**

用数组表示字符串，然后用`'\0'`表示结尾。

```
char cat[8] = {'f', 's', ..., '\0'};
char fish[] = "Bubbles"; //用引号括起的字符串隐式地包括结尾的空字符

char name1[100];
cin>>name1;//遇到'\0'停止

cin.getline(name1, 100);//通过回车键输入的换行符来确定输入结尾。

cin.get(name1, 100);//不在读取并丢弃换行符，而是将其留在输入队列中
cin.get(name1, 100);//a problem 第一个字符得到'\0'，因此在读完数据后，加cin.get();
cin.get(name1, 100).get();
```



**String**

```
string是类。

std::string str1 = "sadf";
std::string str2 ;
str2 = str1;//赋值
str2 = str1 + str1;//拼接
str2 += str1;//附加
```



### 结构体

定义

```
struct 结构体名 { 结构体成员列表 }；
```

初始化

```
结构体名 变量名；
struct 结构体名{……}变量名={...},变量名={};
```

调用

```
变量名.成员名
```

结构体数组

```
struct 结构体名 数组名[元素个数] = { {} , {} , ... {} }
```



### 共用体

定义

```
union one4all{
	int int_val;
	double double_val;
};
```

初始化&调用

```
one4all pail;
pail.int_val = 15;
cout<<pail.int_val;

pail.double_val = 2.3;
cout<<pail.double_val;
```



### 枚举

```
定义
enum spectrum {red, orange, yellow, ...};

调用
spectrum band;
band = red;
```



### 指针

指针也是一种类型，存储地址的类型

**定义**

```
数据类型 * 指针变量名；

如何记名称，看const和*的位置，const int * p-->常量指针；int * const p-->指针常量。
如何记修改内容，看const和p和int，const int * p-->指针指向的值不可改，指向可改；int * const p-->指针的指向不可改，指向的值可改。
```

**赋值**

```
类型 指针变量名 = & 变量;
类型 指针变量名 = new 类型；
```

**使用**

```
指针变量名 -> 成员；
*指针变量名 等价于 变量名；

```

**new&delete**

```
类型 变量名 = new 类型；

delete 变量名；
delete [] 变量名；
```

**指针和数组**



**指针和函数**

```
参数和返回使用指针。
注意删除delete
```



**指针与const**

```
1、指针指向一个常量对象
int age = 39;
const int * pt = &age;
这里，不可以通过*pt来改变值，可以用age来改变值。

2、指针本身声明为常量
```

### 引用

主要是用作函数的形参，针对结构体、类这种比较大的结构。

**定义**

```
数据类型 &别名 = 原名 等价于 int * const pr = & rats;

&是取地址符，但是C++又给其另一个角色，那就是引用声明符,一个类型标识符。
int rats;
int & rodents = rats;//不可以先声明，在初始化，例如int & rodent;rodent = rat;
```

**引用与函数**

```
引用应用在函数的参数和返回值

free_throws & swapp(int & a,int &b);//原型
swapp(a,b);//调用

对比值传递，地址传递（指针）、引用传递三种方式
```

**注意**

```
double refcube(const double &ra);//使用const限定变量值不可修改

const free_throws & clone(free_throws & ft){
	free_throws newguy;
	newguy =ft;
	return newguy;
}//尽量避免这种情况，即避免返回指向临时变量的指针。或者使用new产生新的存储空间
```

**引用与结构体、类**

```
引用用于参数、返回值&、const
```

**如何使用引用参数**

```
引用的功能
1、修改参数中的值
2、传递地址，提高程序运行速度

参数传递选择依据：
如果数据对象很小，如内置数据类型或小型结构，则按值传递。
如果数据对象是数组，则使用指针，因为这是唯一的选择，并将指针声明为指向const的指针。
如果数据对象是较大的结构，则使用const指针或const引用，以提高程序效率。这样可以节省复制结构所需的时间和空间。
如果数据对象是类对象，则使用const引用。类设计的语义常常要求使用引用，这是C++新增这项特性的主要原因。因此，传递类对象参数的标准方式是按引用传递。

对于修改调用函数中数据的函数：
如果数据对象是内置数据类型，则使用指针。如果看到诸如fixit(&x)这样的代码（其中x是int），则很明显，该函数将修改x。
如果数据对象是数组，则只能使用指针。
如果数据对象是结构，则使用引用或指针。
如果数据对象是对象，则使用引用。

```

### 类

类的特点是：封装、多态和继承。

类一般由两部分组成：

- 类声明：以数据成员的方式描述数据部分，以成员函数（被称为方法）的方式描述**公有接口**。
- 类方法定义：描述如何实现类成员函数

#### 封装

##### **声明/定义**

```
class 类名{ 访问权限： 属性 / 行为 };

public 公共权限
protected 保护权限
private 私有权限

声明部分：在头文件中，主要放声明和定义部分
//stock00.h
#ifndef STOCK00_H_
#define STOCK00_H_

#include<string>

class Stock //class declaration
{
private:
	std::string company;
	long shares;
	double share_val;
	double total_val;
	void set_tot(){total_val = shares * share_val;}
public:
	void acquire(const std::string & co, long n, double pr);
	void buy(long num, double price);
	void sell(long num, double price);
	void update(double price);
	void show();
}; //别忘记这里有个分号；

#endif


实现部分：这些代码基本在源文件中
定义成员函数时，使用作用域解析运算符（::）来表示函数所属的类。
//stock00.cpp
#include<iostream>
#include "stock00.h"

void Stock::acquire(const std::string & co; long n ,double pr){
	……;
}
void Stock::buy(long num, double price){
	……;
}
void Stock::sell(long num, double price){
	.....;
}
void Stock::update(double price){
	.....;
}
void Stock::show(){
	...;
}
```

##### 内联方法

```
Stock::set_tot()是一个内联函数，类声明将短小的成员函数作为内联函数，或者在实现文件中
class Stock{
private:
...;
void set_tot();
public:
...;
}

inline void Stock::set_tot(){//内联方法
	total_val = shares * share_val;
}
```

##### 构造方法&析构方法

```
构造函数：主要作用在于创建对象时为对象的成员属性赋值，构造函数由编译器自动调用，无须手动调用。
析构函数：主要作用在于对象销毁前系统自动调用，执行一些清理工作。

构造函数语法：类名(){}
    构造函数，没有返回值也不写void
    函数名称与类名相同
    构造函数可以有参数，因此可以发生重载
    程序在调用对象时候会自动调用构造，无须手动调用,而且只会调用一次
    
析构函数语法： ~类名(){}
    析构函数，没有返回值也不写void
    函数名称与类名相同,在名称前加上符号 ~
    析构函数不可以有参数，因此不可以发生重载
    程序在对象销毁前会自动调用析构，无须手动调用,而且只会调用一次
    
构造两种分类方式：
​ 按参数分为： 有参构造和无参构造
​ 按类型分为： 普通构造和拷贝构造
class Person {
public:
	//无参（默认）构造函数
	Person();
	//有参构造函数
	Person(int a);
	//拷贝构造函数
	Person(const Person& p);
	//析构函数
	~Person();
public:
	int age;
};



初始化列表
构造函数()：属性1(值1),属性2（值2）... {}
```

##### **调用**

```
三种调用方式：
​ 无参
​ 括号法
​ 显示法
​ 隐式转换法

Person p; //调用无参构造函数

//2.1  括号法，常用
Person p1(10);
//注意1：调用无参构造函数不能加括号，如果加了编译器认为这是一个函数声明
//Person p2();

//2.2 显式法
Person p2 = Person(10); 
Person p3 = Person(p2);
//Person(10)单独写就是匿名对象  当前行结束之后，马上析构

//2.3 隐式转换法
Person p4 = 10; // Person p4 = Person(10); 
Person p5 = p4; // Person p5 = Person(p4); 

//注意2：不能利用 拷贝构造函数 初始化匿名对象 编译器认为是对象声明
//Person p5(p4);
```

#####  **深拷贝与浅拷贝**

```
深浅拷贝是面试经典问题，也是常见的一个坑
浅拷贝：简单的赋值拷贝操作
深拷贝：在堆区重新申请空间，进行拷贝操作

class Person {
public:
	//无参（默认）构造函数
	Person() {
		cout << "无参构造函数!" << endl;
	}
	//有参构造函数
	Person(int age ,int height) {
		
		cout << "有参构造函数!" << endl;

		m_age = age;
		m_height = new int(height);
		
	}
	//拷贝构造函数  
	Person(const Person& p) {
		cout << "拷贝构造函数!" << endl;
		//如果不利用深拷贝在堆区创建新内存，会导致浅拷贝带来的重复释放堆区问题
		m_age = p.m_age;
    // m_age = p.m_age; 编译器默认写的
		m_height = new int(*p.m_height);
		
	}

	//析构函数
	~Person() {
		cout << "析构函数!" << endl;
		if (m_height != NULL)
		{
			delete m_height;
		}
	}
public:
	int m_age;
	int* m_height;
};

void test01()
{
	Person p1(18, 180);

	Person p2(p1);

	cout << "p1的年龄： " << p1.m_age << " 身高： " << *p1.m_height << endl;

	cout << "p2的年龄： " << p2.m_age << " 身高： " << *p2.m_height << endl;
}

int main() {

	test01();

	system("pause");

	return 0;
}

总结：如果属性有在堆区开辟的，一定要自己提供拷贝构造函数，防止浅拷贝带来的问题
```

#####  静态成员

```
静态成员就是在成员变量和成员函数前加上关键字static，称为静态成员

静态成员分为：
- 静态成员变量
  - 所有对象共享同一份数据
  - 在编译阶段分配内存
  - 类内声明，类外初始化
- 静态成员函数
  - 所有对象共享同一个函数
  - 静态成员函数只能访问静态成员变量
```

##### C++对象模型和this指针

```
成员变量和成员函数分开存储
在C++中，类内的成员变量和成员函数分开存储, 只有非静态成员变量才属于类的对象上

this指针的用途：
当形参和成员变量同名时，可用this指针来区分
在类的非静态成员函数中返回对象本身，可使用return *this
```

##### const修饰成员函数

```
常函数：
成员函数后加const后我们称为这个函数为常函数
常函数内不可以修改成员属性
成员属性声明时加关键字mutable后，在常函数中依然可以修改


常对象：
声明对象前加const称该对象为常对象
常对象只能调用常函数
class Person {
public:
	Person() {
		m_A = 0;
		m_B = 0;
	}

	//this指针的本质是一个指针常量，指针的指向不可修改
	//如果想让指针指向的值也不可以修改，需要声明常函数
	void ShowPerson() const {
		//const Type* const pointer;
		//this = NULL; //不能修改指针的指向 Person* const this;
		//this->mA = 100; //但是this指针指向的对象的数据是可以修改的

		//const修饰成员函数，表示指针指向的内存空间的数据不能修改，除了mutable修饰的变量
		this->m_B = 100;
	}

	void MyFunc() const {
		//m_A = 10000;
	}

public:
	int m_A;
	mutable int m_B; //可修改 可变的
};


//const修饰对象  常对象
void test01() {

	const Person person; //常量对象  
	cout << person.m_A << endl;
	//person.mA = 100; //常对象不能修改成员变量的值,但是可以访问
	person.m_B = 100; //但是常对象可以修改mutable修饰成员变量

	//常对象访问成员函数
	person.MyFunc(); //常对象不能调用const的函数

}

int main() {

	test01();

	system("pause");

	return 0;
}
```

##### 友元

```
友元的三种实现
    全局函数做友元
    类做友元
    成员函数做友元
  
//全局函数做友元
class Building
{
	//告诉编译器 goodGay全局函数 是 Building类的好朋友，可以访问类中的私有内容
	friend void goodGay(Building * building);
public:
	Building()
	{
		this->m_SittingRoom = "客厅";
		this->m_BedRoom = "卧室";
	}


public:
	string m_SittingRoom; //客厅

private:
	string m_BedRoom; //卧室
};


void goodGay(Building * building)
{
	cout << "好基友正在访问： " << building->m_SittingRoom << endl;
	cout << "好基友正在访问： " << building->m_BedRoom << endl;
}


void test01()
{
	Building b;
	goodGay(&b);
}

int main(){

	test01();

	system("pause");
	return 0;
}

类做友元

class Building;
class goodGay
{
public:

	goodGay();
	void visit();

private:
	Building *building;
};


class Building
{
	//告诉编译器 goodGay类是Building类的好朋友，可以访问到Building类中私有内容
	friend class goodGay;

public:
	Building();

public:
	string m_SittingRoom; //客厅
private:
	string m_BedRoom;//卧室
};

Building::Building()
{
	this->m_SittingRoom = "客厅";
	this->m_BedRoom = "卧室";
}

goodGay::goodGay()
{
	building = new Building;
}

void goodGay::visit()
{
	cout << "好基友正在访问" << building->m_SittingRoom << endl;
	cout << "好基友正在访问" << building->m_BedRoom << endl;
}

void test01()
{
	goodGay gg;
	gg.visit();

}

int main(){

	test01();

	system("pause");
	return 0;
}

成员函数做友元

class Building;
class goodGay
{
public:

	goodGay();
	void visit(); //只让visit函数作为Building的好朋友，可以发访问Building中私有内容
	void visit2(); 

private:
	Building *building;
};


class Building
{
	//告诉编译器  goodGay类中的visit成员函数 是Building好朋友，可以访问私有内容
	friend void goodGay::visit();

public:
	Building();

public:
	string m_SittingRoom; //客厅
private:
	string m_BedRoom;//卧室
};

Building::Building()
{
	this->m_SittingRoom = "客厅";
	this->m_BedRoom = "卧室";
}

goodGay::goodGay()
{
	building = new Building;
}

void goodGay::visit()
{
	cout << "好基友正在访问" << building->m_SittingRoom << endl;
	cout << "好基友正在访问" << building->m_BedRoom << endl;
}

void goodGay::visit2()
{
	cout << "好基友正在访问" << building->m_SittingRoom << endl;
	//cout << "好基友正在访问" << building->m_BedRoom << endl;
}

void test01()
{
	goodGay  gg;
	gg.visit();

}

int main(){
    
	test01();

	system("pause");
	return 0;
}
```

##### 对象数组

```
Stock mystuff[40] = { Stock{"A", 12.3, 20}, ..., 不够的使用默认构造无参的补};
mystuff[0].update();
对象与指针等等一起使用。

总结一下，类就像一个基本类型一样，可以与数组，结构体，指针，类等一起使用。
```

##### 运算符重载

```
加号运算符重载、左移运算符重载、递增运算符重载、赋值运算符重载、关系运算符重载、函数调用运算符重载
class Person {
public:
	Person() {};
	Person(int a, int b)
	{
		this->m_A = a;
		this->m_B = b;
	}
	//成员函数实现 + 号运算符重载
	Person operator+(const Person& p) {
		Person temp;
		temp.m_A = this->m_A + p.m_A;
		temp.m_B = this->m_B + p.m_B;
		return temp;
	}


public:
	int m_A;
	int m_B;
};

//全局函数实现 + 号运算符重载
//Person operator+(const Person& p1, const Person& p2) {
//	Person temp(0, 0);
//	temp.m_A = p1.m_A + p2.m_A;
//	temp.m_B = p1.m_B + p2.m_B;
//	return temp;
//}

//运算符重载 可以发生函数重载 
Person operator+(const Person& p2, int val)  
{
	Person temp;
	temp.m_A = p2.m_A + val;
	temp.m_B = p2.m_B + val;
	return temp;
}

void test() {

	Person p1(10, 10);
	Person p2(20, 20);

	//成员函数方式
	Person p3 = p2 + p1;  //相当于 p2.operaor+(p1)
	cout << "mA:" << p3.m_A << " mB:" << p3.m_B << endl;


	Person p4 = p3 + 10; //相当于 operator+(p3,10)
	cout << "mA:" << p4.m_A << " mB:" << p4.m_B << endl;

}

int main() {

	test();

	system("pause");

	return 0;
}
```

#### 多态

多态分为两类

- 静态多态: 函数重载 和 运算符重载属于静态多态，复用函数名
- 动态多态: 派生类和虚函数实现运行时多态

静态多态和动态多态区别：

- 静态多态的函数地址早绑定 - 编译阶段确定函数地址
- 动态多态的函数地址晚绑定 - 运行阶段确定函数地址

##### 动态多态

多态满足条件

- 有继承关系
- 子类重写父类中的虚函数

多态使用条件

- 父类指针或引用指向子类对象

```
class Animal
{
public:
	//Speak函数就是虚函数
	//函数前面加上virtual关键字，变成虚函数，那么编译器在编译的时候就不能确定函数调用了。
	virtual void speak()
	{
		cout << "动物在说话" << endl;
	}
};

class Cat :public Animal
{
public:
	void speak()
	{
		cout << "小猫在说话" << endl;
	}
};

class Dog :public Animal
{
public:

	void speak()
	{
		cout << "小狗在说话" << endl;
	}

};
//我们希望传入什么对象，那么就调用什么对象的函数
//如果函数地址在编译阶段就能确定，那么静态联编——不加virtual关键字
//如果函数地址在运行阶段才能确定，就是动态联编

void DoSpeak(Animal & animal)
{
	animal.speak();
}
//
//多态满足条件： 
//1、有继承关系
//2、子类重写父类中的虚函数
//多态使用：
//父类指针或引用指向子类对象

void test01()
{
	Cat cat;
	DoSpeak(cat);


	Dog dog;
	DoSpeak(dog);
}


int main() {

	test01();

	system("pause");

	return 0;
}
```



##### 虚析构和纯虚析构

多态使用时，如果子类中有属性开辟到堆区，那么父类指针在释放时无法调用到子类的析构代码

解决方式：将父类中的析构函数改为**虚析构**或者**纯虚析构**

虚析构和纯虚析构共性：

- 可以解决父类指针释放子类对象
- 都需要有具体的函数实现

虚析构和纯虚析构区别：

- 如果是纯虚析构，该类属于抽象类，无法实例化对象

虚析构语法：

```
virtual ~类名(){}
```

纯虚析构语法：

```
virtual ~类名() = 0;类名::~类名(){}
```

总结：

1. 虚析构或纯虚析构就是用来解决通过父类指针释放子类对象

 2. 如果子类中没有堆区数据，可以不写为虚析构或纯虚析构

 3. 拥有纯虚析构函数的类也属于抽象类

```
class Animal {public:	Animal()	{		cout << "Animal 构造函数调用！" << endl;	}	virtual void Speak() = 0;	//析构函数加上virtual关键字，变成虚析构函数	//virtual ~Animal()	//{	//	cout << "Animal虚析构函数调用！" << endl;	//}	virtual ~Animal() = 0;};Animal::~Animal(){	cout << "Animal 纯虚析构函数调用！" << endl;}//和包含普通纯虚函数的类一样，包含了纯虚析构函数的类也是一个抽象类。不能够被实例化。class Cat : public Animal {public:	Cat(string name)	{		cout << "Cat构造函数调用！" << endl;		m_Name = new string(name);	}	virtual void Speak()	{		cout << *m_Name <<  "小猫在说话!" << endl;	}	~Cat()	{		cout << "Cat析构函数调用!" << endl;		if (this->m_Name != NULL) {			delete m_Name;			m_Name = NULL;		}	}public:	string *m_Name;};void test01(){	Animal *animal = new Cat("Tom");	animal->Speak();	//通过父类指针去释放，会导致子类对象可能清理不干净，造成内存泄漏	//怎么解决？给基类增加一个虚析构函数	//虚析构函数就是用来解决通过父类指针释放子类对象	delete animal;}int main() {	test01();	system("pause");	return 0;}
```







#### 继承

```
继承的语法：class 子类 : 继承方式 父类, 继承方式 父类2

继承方式一共有三种：
公共继承
保护继承
私有继承

总结：继承中 先调用父类构造函数，再调用子类构造函数，析构顺序与构造相反

访问子类同名成员 直接访问即可
访问父类同名成员 需要加作用域。s.Base.value


```



## 6 内存模型&名称空间

##### 单独编译/代码分开

```
include头文件中常包含内容：
函数原型
使用#define或const定义的符号常量
结构声明
类声明
模版声明
内联函数


#ifndef COORDIN_H_
#define COORDIN_H_
//place include file contents here
#endif


```

##### 内存四区

```
内存四区，不同区域存放的数据，赋予不同的生命周期, 给我们更大的灵活编程

程序执行前
代码区：存放函数体的二进制代码，由操作系统进行管理的
全局区：存放全局变量和静态变量以及常量（const修饰的全局变量，字符串常量）

程序执行后
栈区：由编译器自动分配释放, 存放函数的参数值,局部变量，const修饰的局部常量等
堆区：由程序员分配和释放,若程序员不释放,程序结束时由操作系统回收
```

##### 名称空间

```
namespace Jack{
	double pail;
	……

}

using namespace std::string；//使用
```



## 7 STL类型

STL大体分为六大组件，分别是:**容器、算法、迭代器、仿函数、适配器（配接器）、空间配置器**

1. 容器：各种数据结构，如vector、list、deque、set、map等,用来存放数据。
2. 算法：各种常用的算法，如sort、find、copy、for_each等
3. 迭代器：扮演了容器与算法之间的胶合剂。
4. 仿函数：行为类似函数，可作为算法的某种策略。
5. 适配器：一种用来修饰容器或者仿函数或迭代器接口的东西。
6. 空间配置器：负责空间的配置与管理。

### STL-常用容器

顺序容器(sequenial container)

STL标准库中，提供了多种不同的顺序容器，**可变大小数组**vector，**双端队列**deque，**双向链表**llist，**固定大小数组**array等



确定使用哪种容器

- 除非有充分的理由选择其他容器，否则vector永远是最好的选择。
- 如果元素中有大量小元素且内存额外开销很重要，避免使用list和forward_list。
- 如果要求随机访问，应使用vector或deque。
- 如果程序要求在中间插入或删除，应使用list或forward_list。
- 如果程序需要在头尾插入删除，则应使用双端队列deque。
- 如果程序开始时需要中间插入，之后需要随机访问。

| 容器          | 特点                                                         |
| ------------- | ------------------------------------------------------------ |
| Vector        | 1、内存连续；<br/> 2、支持随机访问；<br/> 3、随机访问效率高 ；<br/> 4、插入与删除：只有在末尾插入和删除的效率比较高(常量时间复杂度O(1))，在容器中查找或者在中间和前面插入或删除时，呈线性复杂度O(n)。 |
| Queue         |                                                              |
| Deque         | 1、允许在两端进行插入和删除<br/>2、在时间复杂度上会比向量更加复杂<br/>3、本质上和vector很相似 ， 但是内存机制比起vector更加复杂：<br/>比vector多了 push_front pop_front方法 少了capacity 和 reserve |
| Stack         |                                                              |
| List          | 1、内存不连续 ，底层实现是链表 ；<br/>2、插入和删除的效率比较快 ，随机访问效率比较低；<br/>3、和vector相比，不再需要 capacity 和 reserve 操作，因为链表没有大小限制 ，不需要为了效率增加预分配内存的功能。 |
| Forward_list  | 单向链表                                                     |
| Array         | 和其它容器不同，array 容器的大小是固定的，无法动态的扩展或收缩，这也就意味着，在使用该容器的过程无法借由增加或移除元素而改变其大小，它只允许访问或者替换存储的元素。 |
| set           |                                                              |
| map           |                                                              |
| unordered_map |                                                              |
| unorered_set  | 1、不再以键值对的形式存储数据，而是直接存储数据的值； <br/>2、容器内部存储的各个元素的值都互不相等，且不能被修改。<br/>3、不会对内部存储的数据进行排序（这和该容器底层采用哈希表结构存储数据有关，可阅读《[C++ STL无序容器底层实现原理](http://c.biancheng.net/view/7235.html)》一文做详细了解）； |



#### string容器—字符串

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

#### vector容器—向量

- 概念
  - 向量（Vector）是一个封装了动态大小数组的顺序容器（Sequence Container）。跟任意其它类型容器一样，它能够存放各种类型的对象。可以简单的认为，向量是一个能够存放任意类型的动态数组。
- 容器特性
  - 1.顺序序列:顺序容器中的元素按照严格的线性顺序排序。可以通过元素在序列中的位置访问对应的元素。
  - 2.动态数组:支持对序列中的任意元素进行快速直接访问，甚至可以通过指针算述进行该操作。操供了在序列末尾相对快速地添加/删除元素的操作。
  - 3.能够感知内存分配器的（Allocator-aware）:容器使用一个内存分配器对象来动态地处理它的存储需求。
  - 自己总结：
    - 1、内存连续；
    - 2、支持随机访问；
    - 3、随机访问效率高 ；
    - 4、插入与删除：只有在末尾插入和删除的效率比较高(常量时间复杂度O(1))，在容器中查找或者在中间和前面插入或删除时，呈线性复杂度O(n)。
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

#### queue 容器—队列

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

#### deque容器—双端队列

- 概念
- 特点
  - 1、允许在两端进行插入和删除
  - 2、在时间复杂度上会比向量更加复杂
  - 3、本质上和vector很相似 ， 但是内存机制比起vector更加复杂：
  - 比vector多了 push_front pop_front方法 少了capacity 和 reserve
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

#### stack容器—栈

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



#### list容器—双向链表

- [概念](https://blog.csdn.net/Nire_Yeyu/article/details/100938315)
- 特点
  - 内存不连续 ，底层实现是链表 ；
  - 插入和删除的效率比较快 ，随机访问效率比较低；
  - 和vector相比，不再需要 capacity 和 reserve 操作，因为链表没有大小限制 ，不需要为了效率增加预分配内存的功能。
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

#### forword_list容器—单向链表

- 概念
  - 一个单向链表，只支持单向顺序访问，在链表的任何位置进行插入/删除操作都非常快。
- [方法](https://www.codenong.com/cs105807292/)

#### array容器—数组

- 概念
- 特点
  - 和其它容器不同，array 容器的大小是固定的，无法动态的扩展或收缩，这也就意味着，在使用该容器的过程无法借由增加或移除元素而改变其大小，它只允许访问或者替换存储的元素。
- [方法](http://c.biancheng.net/view/6688.html)

#### set/ multiset 容器—集合

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

#### map/ multimap容器—映射

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

#### unordered_map容器

**map**

```
#include<iostream>
#include<map>
#include<string>
 
using namespace std;
 
int main()
{
	// 构造函数
	map<string, int> dict;
	
	// 插入数据的三种方式
	dict.insert(pair<string,int>("apple",2));
	dict.insert(map<string, int>::value_type("orange",3));
	dict["banana"] = 6;
 
	// 判断是否有元素
	if(dict.empty())
		cout<<"该字典无元素"<<endl;
	else
		cout<<"该字典共有"<<dict.size()<<"个元素"<<endl;
 
	// 遍历
	map<string, int>::iterator iter;
	for(iter=dict.begin();iter!=dict.end();iter++)
		cout<<iter->first<<ends<<iter->second<<endl;
 
	// 查找
	if((iter=dict.find("banana"))!=dict.end()) //  返回一个迭代器指向键值为key的元素，如果没找到就返回end()
		cout<<"已找到banana,其value为"<<iter->second<<"."<<endl;
	else
		cout<<"未找到banana."<<endl;
 
	if(dict.count("watermelon")==0) // 返回键值等于key的元素的个数
		cout<<"watermelon不存在"<<endl;
	else
		cout<<"watermelon存在"<<endl;
	
	pair<map<string, int>::iterator, map<string, int>::iterator> ret;
	ret = dict.equal_range("banana"); // 查找键值等于 key 的元素区间为[start,end)，指示范围的两个迭代器以 pair 返回
	cout<<ret.first->first<<ends<<ret.first->second<<endl;
	cout<<ret.second->first<<ends<<ret.second->second<<endl;
 
	iter = dict.lower_bound("boluo"); // 返回一个迭代器，指向键值>=key的第一个元素。
	cout<<iter->first<<endl;
	iter = dict.upper_bound("boluo"); // 返回一个迭代器，指向值键值>key的第一个元素。
	cout<<iter->first<<endl;
	return 0;
}


```

**unordered_map**

```
#include<string>  
#include<iostream>  
#include<unordered_map>
using namespace std;  
  
int main()
{
	unordered_map<string, int>  dict; // 声明unordered_map对象
	
	// 插入数据的三种方式
	dict.insert(pair<string,int>("apple",2));
	dict.insert(unordered_map<string, int>::value_type("orange",3));
	dict["banana"] = 6;
	
	// 判断是否有元素
	if(dict.empty())
		cout<<"该字典无元素"<<endl;
	else
		cout<<"该字典共有"<<dict.size()<<"个元素"<<endl;
	
	// 遍历
	unordered_map<string, int>::iterator iter;
	for(iter=dict.begin();iter!=dict.end();iter++)
		cout<<iter->first<<ends<<iter->second<<endl;
	
	// 查找
	if(dict.count("boluo")==0)
		cout<<"can't find boluo!"<<endl;
	else
		cout<<"find boluo!"<<endl;
	
	if((iter=dict.find("banana"))!=dict.end())
		cout<<"banana="<<iter->second<<endl;
	else
		cout<<"can't find boluo!"<<endl;
	
	return 0;
}


```



#### unordered_set容器



## 8 方法

##### decltype

```
decltype (expression) var;
eg.
decltype(x+y) xpy = x + y;
```

##### 常量定义

```
#define name value

const typename name = value;
```

##### 变量和常量

```
int a;
int指出所需的内存空间（类型、大小）。
a指出存储的位置。
```

##### 常见库

```
<math.h>(c), <cmath>(c++)

<stdio.h>

<stdlib.h>

<iostream>

```

