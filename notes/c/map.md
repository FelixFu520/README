# C++ STL unordered_map介绍与使用方法

2020年

## unordered_map(无序映射)

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