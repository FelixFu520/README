# C++ 函数们

⌚️:2020年11月30日

📚参考

----

## 1. atof函数

功能：将字串转换成浮点型数

相关函数 atoi，atol，strtod，strtol，strtoul



表头文件 #include <stdlib.h>

定义函数 double atof(const char *nptr);

函数说明:

​      atof()会扫描参数nptr字符串，跳过前面的空格字符，直到遇上数字或正负符号才开始做转换，而再遇到非数字或字符串结束时('\0')才结束转换，并将结果返回。参数nptr字符串可包含正负号、小数点或E(e)来表示指数部分，如123.456或123e-2。返回值返回转换后的浮点型数。 

```cpp
int main( ) 
{
	double d;
	char *str = "1234567.89";
	d = atof(str);
	printf("string = %s double = %lf\n", str, d);
	
	char *a = "-100.23";
	char *b = "200e-2";
	double c;
	c = atof(a) + atof(b);
	printf("c = %.2lf\n",c);
	
	return 0;
}
```

# 2. c++中的auto和for循环

### 1. auto的使用 

c++11引入了auto类型说明符，auto让编译器通过初始值来推算变量的类型，所以auto定义的变量必须有初始值。 
使用auto也能在一条语句中声明多个变量，因为一条声明语句只能有一个基本数据类型，所以该语句中所有变量的初始基本数据类型都必须一样： 
eg: auto i=0,*p=& i; //正确 auto sz=0,pi=3.14;//错误，sz和pi的类型不一样。

### 2.for循环

范围for循环，遍历给定序列中的每个元素并对序列中的每个值执行某种操作。

```
for(declaration:expression)
    statement   
    

expression 部分是一个对象，用于表示一个序列，declaration部分负责定义一个变量，该变量被用于访问序列中的基础元素，每次迭代declaration部分的变量会被初始化为expression部分的下一个元素值。
```

范围for循环有两种用法：

```
string s("hello,world");
decltype(s.size()) punct_cnt=0;//decltype也是c++11特性，用于选择和返回操作数的数据类型。

for(auto c:s)//对于s中的每个字符
    if(ispunct(c)) //C 库函数 int ispunct(int c) 检查所传的字符是否是标点符号字符。标点符号字符可以是非字母数字（正如 isalnum 中的一样）的任意图形字符（正如 isgraph 中的一样）。如果 c 是一个标点符号字符，则该函数返回非零值（true），否则返回 0（false）。
        ++punct_cnt;
        
        
        
        
string s("hello,world");

for(auto &c:s);//对于s中的每个字符，c是一个引用，赋值语句将会改变s中字符的值
    c=toupper(c);//C 库函数 int toupper(int c) 把小写字母转换为大写字母。

cout<<s<<endl;
```

## 3. C++ STL unordered_map介绍与使用方法

对于map，前面已经提到过，其内部数据结构为红黑树，因此所有元素插入到map里面都会排好序，而且搜索过程为平衡二叉树搜索，因此时间复杂度为`O(logN)`。我们知道还有一种快速的搜索方法，那边是哈希(又名散列)，利用哈希函数，通过哈希值能快速的查找到所需元素。unordered_map便是采用这种数据结构实现，unordered _map与map的使用基本一样，都是key/value之间的映射，只是他们内部采用的数据结构不一样。

> 由于unordered_map内部是用散列表来实现快速查找，因此其内部元素完全是一种无序状态。哈希表利用哈希函数，将关键字的哈希值放都一个桶(bucket)里面，具有相同哈希值的放入到同一个桶。

##### 头文件：#include <unordered_map>

##### 构造函数

```C++
typedef std::unordered_map<std::string,std::string> stringmap;

stringmap first;                              // empty
stringmap second ( {{"apple","red"},{"lemon","yellow"}} );       // init list
stringmap third ( {{"orange","orange"},{"strawberry","red"}} );  // init list
stringmap fourth (second);                    // copy
stringmap fifth (merge(third,fourth));        // move
stringmap sixth (fifth.begin(),fifth.end());  // range

```

##### 容器大小

```C++
stringmap second ( {{"apple","red"},{"lemon","yellow"}} );       // init list

cout << second.empty() << endl;
cout << second.size() << endl;
```

##### 获取元素

```C++
cout << second[0] << endl;
cout << second.at(0) << endl;

```

##### 元素查找

```C++
unordered_map<char, int>::iterator it;
it = unorderedFirst.find('a');   //返回查找到元素的iterator，如未查找到，返回end()

if (it != unorderedFirst.end())
{
	cout << (*it).first << " " << (*it).second << endl;
}

int n;
n = unorderedFirst.count('z');  //测试某个关键字是否存在

cout << n << endl;

```

##### 元素修改

```C++
pair<unordered_map<char, int>::iterator, bool> ret;
ret = unorderedFirst.insert(pair<char, int>('a', 10));

if (ret.second)
{
	cout << "insert succeed.." << endl;
}
else
{
	cout << "insert failed.." << endl;
}


unordered_map<char, int> second;
second['a'] = 1;
second['b'] = 2;
second['c'] = 3;

//删除元素
second.erase ( second.begin() );      // erasing by iterator
second.erase ('a');             // erasing by key
second.erase ( second.find('c'), second.end() ); // erasing by range


second.clear();  //清空
second.swap(first);   //互换

cout << second.bucket_count() << endl;  //返回桶的数量

cout << second.bucket_size() << endl;  //返回每个桶的大小

cout << second.bucket('a') << endl; //返回当前元素在哪个桶

unorderedFirst.rehash(10);   //设置桶的数量

```

##### unordered_map使用

- unordered_map内部使用哈希表进行存储与搜索。由于需要使用hash来进行映射，因此需要判断两个关键字是否相等，对于内部类型，可以直接进行判断，如果是用户自定义类型，则需要重载"=="运算符，指定如何判断两个关键字是否相等。以下是在网上摘录的一段代码，个人觉得比较详细的unordered_map的使用方法，这里只是其中一种使用方法：利用函数对象。(若有侵权，请联系我删除)

```C++
#include <iostream>
#include <unordered_map>

using namespace std;


struct Person
{
	string name;
	int age;

	Person(string name, int age)
	{
		this->name =  name;
		this->age = age;
	}

};

/* the object of hash function */
struct PersonHash
{
    size_t operator()(const Person& per) const{
        return hash<string>()(per.name) ^ hash<int>()(per.age);
    }
};

/* the object of compare */
struct PersonCmp
{
    bool operator()(const Person& pera, const Person& perb) const{
        return pera.name == perb.name && pera.age == perb.age;
    }
};

/* define the unordered_map type */
typedef unordered_map<Person, int, PersonHash, PersonCmp> umap;


int main()
{

	umap m;


	Person p1("Tom1",20);
	Person p2("Tom2",22);
	Person p3("Tom3",22);
	Person p4("Tom4",23);
	Person p5("Tom5",24);
	m.insert(umap::value_type(p3, 100));
	m.insert(umap::value_type(p4, 100));
	m.insert(umap::value_type(p5, 100));
	m.insert(umap::value_type(p1, 100));
	m.insert(umap::value_type(p2, 100));		
	
	/* 这里打印出来的顺序于插入顺序并不相同，确切的说是完全无序的 */
	for(umap::iterator iter = m.begin(); iter != m.end(); iter++)
	{
		cout << iter->first.name << "\t" << iter->first.age << endl;
	}		


	return 0;
}

```

