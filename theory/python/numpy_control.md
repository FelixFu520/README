# Numpy控制、测试

⌚️:2020年11月30日

📚参考

---

**TDD**（**Test Driven Development，测试驱动的开发**）是软件开发史上最重要的里程碑之一。TDD主要专注于自动单元测试，它的目标是尽最大限度自动化测试代码。如果代码被改动，我们仍可以运行测试并捕捉可能存在的问题。换言之，测试对于已经存在的功能模块依然有效。

​    内容：

>  单元测试；
>
>  断言机制；
>
>  浮点数精度。

## 1. 断言函数

​    **单元测试**通常使用断言函数作为测试的组成部分。在进行数值计算时，我们经常遇到比较两个近似相等的浮点数这样的基本问题。整数之间的比较很简单，但浮点数却非如此，这是由于计算机对浮点数的表示本身就是不精确的。numpy.testing包中有很多实用的工具函数考虑了浮点数比较的问题，可以测试前提是否成立。

​    函 数 描 述：

> assert_almost_equal 如果两个数字的近似程度没有达到指定**精度**，就抛出异常
>
> assert_approx_equal 如果两个数字的近似程度没有达到指定**有效数字**，就抛出异常
>
> assert_array_almost_equal 如果两个数组中元素的近似程度没有达到指定精度，就抛出异常
>
> assert_array_equal 如果两个数组对象不相同，就抛出异常
>
> assert_array_less 两个数组必须形状一致，并且第一个数组的元素严格小于第二个数组的元素，否则就抛出异常
>
> assert_equal 如果两个对象不相同，就抛出异常
>
> assert_raises 若用填写的参数调用函数没有抛出指定的异常，则测试不通过
>
> assert_warns 若没有抛出指定的警告，则测试不通过
>
> assert_string_equal 断言两个字符串变量完全相同
>
> assert_allclose 如果两个对象的近似程度超出了指定的容差限，就抛出异常



```python
import numpy as np



#使用NumPy testing包中的assert_almost_equal函数在不同的精度要求下检查了两个浮点数0.123456789和0.123456780是否近似相等


# (1) 调用函数，指定较低的精度（小数点后7位）：
print 'Decimal 7',np.testing.assert_almost_equal(0.123456789,0.123456780,decimal=7)


# (2) 调用函数，指定较高的精度（小数点后9位）：
print 'Decimal 9',np.testing.assert_almost_equal(0.123456789,0.123456780,decimal=9)

# (1) 调用函数，指定较低的有效数字位：
print "Significance 8", np.testing.assert_approx_equal(0.123456789,0.123456780,significant=8)

# (2) 调用函数，指定较高的有效数字位：
print "Significance 9", np.testing.assert_approx_equal(0.123456789, 0.123456780,significant=9)

# (1) 调用函数，指定较低的精度：
print "Decimal 8", np.testing.assert_array_almost_equal([0, 0.123456789], [0,0.123456780], decimal=8)

# (2) 调用函数，指定较高的精度：
print "Decimal 9", np.testing.assert_array_almost_equal([0, 0.123456789], [0,0.123456780], decimal=9)

# (1) 调用assert_allclose函数：
print "Pass", np.testing.assert_allclose([0, 0.123456789, np.nan], [0, 0.123456780,np.nan], rtol=1e-7, atol=0)

# (2) 调用assert_array_equal函数：
print "Fail", np.testing.assert_array_equal([0, 0.123456789, np.nan], [0, 0.123456780,np.nan])

# (1) 调用assert_array_less函数比较两个有严格顺序的数组：
print "Pass", np.testing.assert_array_less([0, 0.123456789, np.nan], [1, 0.23456780,np.nan])

# (2) 调用assert_array_less函数，使测试不通过：
print "Fail", np.testing.assert_array_less([0, 0.123456789, np.nan], [0, 0.123456780,np.nan])

# 调用assert_equal函数：
print "Equal?", np.testing.assert_equal((1, 2), (1, 3))

# (1) 调用assert_string_equal函数，比较一个字符串和其自身。显然，该测试应通过：
print "Pass", np.testing.assert_string_equal("NumPy", "NumPy")

# (2) 调用assert_string_equal函数，比较一个字符串和另一个字母完全相同但大小写有区别的字符串。该测试应抛出异常：
print "Fail", np.testing.assert_string_equal("NumPy", "Numpy")

# (1) 使用finfo函数确定机器精度：
eps = np.finfo(float).eps
print "EPS", eps

# (2) 使用assert_array_almost_equal_nulp函数比较两个近似相等的浮点数1.0和1.0+ eps（epsilon），然后对1.0 + 2 * eps做同样的比较：
print "1",
np.testing.assert_array_almost_equal_nulp(1.0, 1.0 + eps)
print "2",
np.testing.assert_array_almost_equal_nulp(1.0, 1.0 + 2 * eps)

# (1) 使用finfo函数确定机器精度：
eps = np.finfo(float).eps
print "EPS", eps

# (2) 与前面的“动手实践”教程做相同的比较，但这里我们使用assert_array_max_ulp函数和适当的maxulp参数值：
print "1", np.testing.assert_array_max_ulp(1.0, 1.0 + eps)
print "2", np.testing.assert_array_max_ulp(1.0, 1 + 2 * eps, maxulp=2)
```



## 2. 单元测试

单元测试是对代码的一小部分进行自动化测试的单元，通常是一个函数或方法。Python中有用于单元测试的PyUnit API（Application Programming Interface，应用程序编程接口）。

```html
import numpy
import unittest
 
def factorial(n):
    if n == 0:
        return 1
 
    if n < 0:
        raise ValueError, "Don't be so negative"
    return numpy.arange(1, n+1).cumprod()
class FactorialTest(unittest.TestCase):
    def test_factorial(self):
        # 对3的阶乘进行测试，应该能通过
        self.assertEqual(6, factorial(3)[-1])
        numpy.testing.assert_equal(numpy.array([1, 2, 6]), factorial(3))
    def test_zero(self):
        # 对0的阶乘进行测试，应该能通过
        self.assertEqual(1, factorial(0))
    def test_negative(self):
        # 对负整数的阶乘进行测试，应该不能通过
        # 阶乘函数会抛出一个ValueError类型的异常，但我们期望得到一个IndexError类型的异常
        self.assertRaises(IndexError, factorial(-10))
if __name__ == '__main__':
    unittest.main()
```

运行：

```python
.E.
======================================================================
ERROR: test_negative (__main__.FactorialTest)
----------------------------------------------------------------------
Traceback (most recent call last):
  File "C:/Users/Administrator/Desktop/Python_Opencv/Test/One/func.py", line 598, in test_negative
    self.assertRaises(IndexError, factorial(-10))
  File "C:/Users/Administrator/Desktop/Python_Opencv/Test/One/func.py", line 581, in factorial
    raise ValueError, "Don't be so negative"
ValueError: Don't be so negative
----------------------------------------------------------------------
Ran 3 tests in 0.013s
FAILED (errors=1)


```



## 3.  nose 和测试装饰器：

鼻子（nose）是长在嘴上方的器官，人和动物的呼吸和闻都依赖于它。nose同时也是一种Python框架，使得（单元）测试更加容易。nose可以帮助你组织测试代码。根据nose的文档，“任何能够匹配testMatch正则表达式（默认为(?:^|[b_.-])[Tt]est）的Python源代码文件、文件夹或库都将被收集用于测试”。nose充分利用了装饰器（decorator）。Python装饰器是有一定含义的对函数或方法的注解。numpy.testing模块中有很多装饰器。
装 饰 器 描 述

> numpy.testing.decorators.deprecated 在运行测试时过滤掉过期警告
>
> numpy.testing.decorators.knownfailureif 根据条件抛出KnownFailureTest异常
>
> numpy.testing.decorators.setastest 将函数标记为测试函数或非测试函数
>
> numpy.testing.decorators. skipif 根据条件抛出SkipTest异常
>
> numpy.testing.decorators.slow 将测试函数标记为“运行缓慢”

