# C++ atof函数

2020年11月26日

----



atof函数：

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