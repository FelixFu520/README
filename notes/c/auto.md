# c++中的auto和for循环

2020年12月16日

---



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