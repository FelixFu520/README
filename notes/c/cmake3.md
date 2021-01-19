# Cmake tutorial

2020年12月22日

[参考-1](https://github.com/chaneyzorn/CMake-tutorial)  | [参考-2](https://www.ctolib.com/hlmmd-cmake-tutorial.html)  | [参考-3](https://www.jianshu.com/p/6df3857462cd)

cmake官方教程（翻译）[官方教程](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)

本教程所有源代码取自cmake源码[Test/Tutorial](https://gitlab.kitware.com/cmake/cmake/tree/master/Tests/Tutorial)

---

## Step0 起步

最基础的项目工程是通过单一源文件编译得到可执行文件。对于这样简单的工程，只需要两行CMakeLists.txt代码即可实现。以下是一个简单示例。

先建立一个文件夹，用于存放我们的工程。

```
mkdir -p cmake/step1
cd cmake/step1
touch tutorial.cxx
touch CMakeLists.txt
```

源代码tutoriol.cxx实现了求一个数的平方根的功能：

```
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " number" << std::endl;
    return 1;
  }
  double inputValue = atof(argv[1]);

  double outputValue = sqrt(inputValue);
  std::cout << "The square root of " << inputValue 
            << " is " << outputValue << std::endl;
  return 0;
}
```

CMakeLists.txt的内容：

```
cmake_minimum_required (VERSION 2.6)
project (Tutorial)
add_executable(Tutorial tutorial.cxx)
```

```
add_executable(<name> [WIN32] [MACOSX_BUNDLE]
               [EXCLUDE_FROM_ALL]
               source1 [source2 ...])
```

- name: 工程所要构建的目标名称
- WIN32/..: 目标app运行的平台
- source1：构建目标App的源文件



CMakeLists.txt中的命令支持大写、小写，大小写混合。本例中使用小写。

编译的时候，在当前目录下新建一个build目录，用于存放编译过程产生的文件以及生成的可执行文件。

```
mkdir build
cd build
cmake ..
make
```

cmake .. 表示在..（上级）目录中寻找CMakeLists.txt进行编译，cmake执行成功后会自动生成Makefile文件，执行make即可完成编译。

cmake 执行结果：

```
root@x:~/qinrui/cmake/step1/build# cmake ..
-- The C compiler identification is GNU 5.4.0
-- The CXX compiler identification is GNU 5.4.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /root/qinrui/cmake/step1/build
```

make执行结果：

```
root@x:~/qinrui/cmake/step1/build# make
Scanning dependencies of target Tutorial
[ 50%] Building CXX object CMakeFiles/Tutorial.dir/tutorial.cxx.o
[100%] Linking CXX executable Tutorial
[100%] Built target Tutorial
```

## Step1 添加版本号和配置头文件

我们要给当前工程添加的第一个特性是版本号信息。尽管可以在源代码中完成该操作，但在CMakeLists.txt中完成此操作能够大大提升灵活性。我们可以按照以下方式修改CMakeLists.txt

注意，在CMakeLists.txt中，"#"表示注释。

```
cmake_minimum_required (VERSION 3.3)
project (Tutorial)
# 版本号信息
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

# 配置一个头文件，从而将CMake的一些设置传递到源文件中。
# 以TutorialConfig.h.in为模板，生成TutorialConfig.h
configure_file (
  "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
  "${PROJECT_BINARY_DIR}/TutorialConfig.h"
  )
 
# 将构建目录添加到include的搜索路径中,这样就能够找到TutorialConfig.h
# 添加TutorialConfig.h的路径到头文件的搜索路径
include_directories("${PROJECT_BINARY_DIR}")
 
# 添加可执行文件名
add_executable(Tutorial tutorial.cxx)
```

因为配置文件会被写入构建目录中，所以我们将这个目录添加到include文件的搜索范围中。

```
configure_file(<input> <output>
               [COPYONLY] [ESCAPE_QUOTES] [@ONLY]
               [NEWLINE_STYLE [UNIX|DOS|WIN32|LF|CRLF] ])
```

cmake会自动定义两个变量

- ${PROJECT_SOURCE_DIR}： 当前工程最上层的目录
- ${PROJECT_BINARY_DIR}：　当前工程的构建目录（本例中新建的build目录）



我们在工程中添加头文件模板TutorialConfig.h.in：

```
// 配置信息
#define Tutorial_VERSION_MAJOR @Tutorial_VERSION_MAJOR@
#define Tutorial_VERSION_MINOR @Tutorial_VERSION_MINOR@
```

当Cmake生成这个配置文件时，@Tutorial_VERSION_MAJOR@ 和 @Tutorial_VERSION_MINOR@ 将会被CMakeLists.txt中设置的值替换。接下来我们修改tutorial.cxx来include头文件以获取版本号。

添加了一条include以引用TutorialConfig.h。在usage 信息中添加了版本号。

```
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include "TutorialConfig.h"
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << argv[0] << " Version "
              << Tutorial_VERSION_MAJOR << "."
              << Tutorial_VERSION_MINOR << std::endl;
    std::cout << "Usage: " << argv[0] << " number" << std::endl;
    return 1;
  }

  double inputValue = atof(argv[1]);

  double outputValue = sqrt(inputValue);
  std::cout << "The square root of " << inputValue
            << " is " << outputValue << std::endl;
  return 0;
}
```

将build的内容清空，重新cmake，make编译。

```
cd build
rm -rf *
cmake ..
make
```

此时的文件目录结构为：（省略了CMakeFiles内的文件）

```
.
├── build
│   ├── CMakeCache.txt
│   ├── CMakeFiles
│   ├── cmake_install.cmake
│   ├── Makefile
│   ├── Tutorial
│   └── TutorialConfig.h
├── CMakeLists.txt
├── TutorialConfig.h.in
└── tutorial.cxx
```

运行结果：

```
root@x:~/qinrui/cmake/step1/build# ./Tutorial 
./Tutorial Version 1.0
Usage: ./Tutorial number
```

## Step2 添加库文件

接下来我们将会往项目中添加库文件。这个库包含了我们自己写的sqrt的实现，以替代系统库。本教程中我们将库文件放入MathFunctionsLib子目录中。这个字母录也包含一个CMakeLists.txt文件，只有一行

```
add_library(MathFunctions mysqrt.cxx)
```

添加MathFunctions.h头文件，同样只有一行定义：

```
double mysqrt(double x);
```

在mysqrt.cxx中给出mysqrt实现：

```
#include "MathFunctions.h"
#include <iostream>

double mysqrt(double x)
{
	if (x <= 0)
	{
		return 0;
	}

	double result = x;

	// 循环计算10次
	for (int i = 0; i < 10; ++i)
	{
		if (result <= 0)
		{
			result = 0.1;
		}
		double delta = x - (result * result);
		result = result + 0.5 * delta / result;
	}
	return result;
}
```

现在的目录结构

```
.
├── build
├── CMakeLists.txt
├── MathFunctions
│ ├── CMakeLists.txt
│ ├── MathFunctions.h
│ └── mysqrt.cxx
├── TutorialConfig.h.in
└── tutorial.cxx
```



CMakeLists.txt文件需要相应做如下改动

- 添加一行add_subdirectory来保证新加的library在工程构建过程中被编译。
- 添加新的头文件搜索路径MathFunction/MathFunctions.h。
- 添加新的library到executable。

在mysqrt.cxx源代码中提供了mysqrt函数，实现了和sqrt函数相同的功能。为了使用新的库，我们在顶层CMakeLists中添加一行add_subdirectory调用，这样库文件就会被构建。同时添加include路径，使得MathFunctions/MathFunctions.h 头文件中定义的函数原型能被找到。最后一步是将库文件添加到可执行文件中。在顶层CMakeLists.txt中添加：

```
include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
add_subdirectory (MathFunctions) 
 
# 添加可执行文件
add_executable (Tutorial tutorial.cxx)
target_link_libraries (Tutorial MathFunctions)
```



最后要修改tutorial.cxx文件来调用自定义的mysqrt函数
最后编译一下试试

```ruby
  $ cmake ..
  $ make
  $ ./Tutorial
```

看一下编译的log

```csharp
Scanning dependencies of target MathFunctions
[ 50%] Building CXX object MathFunctions/CMakeFiles/MathFunctions.dir/mysqrt.cxx.o
Linking CXX static library libMathFunctions.a
[ 50%] Built target MathFunctions
Scanning dependencies of target Tutorial
[100%] Building CXX object CMakeFiles/Tutorial.dir/tutorial.cxx.o
Linking CXX executable Tutorial
[100%] Built target Tutorial
```

这里编译生成了新的库libMathFunctions.a





下面考虑将MathFunctions这个库设置成可选的。当使用较大的库或者第三方库时会用到该功能。在顶层CMakeLists.txt中添加：

```
# 是否使用自定义函数库
option (USE_MYMATH "Use tutorial provided math implementation" ON) 
```

运行ccmake ..会跳出来配置的GUI，在GUi中会看到新添加的这个选项，用户可以根据需要进行修改。
下一个改变是依据配置来判断是否编译和链接MathFunctions库。按照如下所示的修改CMakeList.txt的末尾几行：

```
# 是添加自定义库
if (USE_MYMATH)
  include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
  add_subdirectory (MathFunctions)
  set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)
 
# 添加可执行文件
add_executable (Tutorial tutorial.cxx)
target_link_libraries (Tutorial  ${EXTRA_LIBS})
```

这个例子里还是用了变量（EXTRA_LIBS）来收集后面link进可执行文件的时候任意可选的库。这是一个常用的方法，在工程非常大有很多optional的组件的时候，可以让这个编译文件保持干净。



代码的修改就更直接了(用宏定义隔离开)：

使用USE_MYMATH来判定是否需要编译使用MathFunctions。这里使用了一个EXTRA_LIBS变量来收集所有可选的库，用于链接到可执行文件。这是一种保证具有多重选择的大型项目整洁性的常用方法。相关源代码的修改如下：

```
#include <cmath>
#include <iostream>
#include <string>

#include "TutorialConfig.h"

#ifdef USE_MYMATH
#include "MathFunctions.h"
#endif

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << argv[0] << " Version " << Tutorial_VERSION_MAJOR
				  << "." << Tutorial_VERSION_MINOR << std::endl;
		std::cout << "Usage: " << argv[0] << " number" << std::endl;
		return 1;
	}

	double inputValue = std::stod(argv[1]);

#ifdef USE_MYMATH
	double outputValue = mysqrt(inputValue);
	std::cout << "Mysqrt: The square root of " << inputValue
			  << " is " << outputValue << std::endl;
#else
	double outputValue = sqrt(inputValue);
	std::cout << "sqrt:  The square root of " << inputValue
			  << " is " << outputValue << std::endl;
#endif

	return 0;
}
```

在源代码中我们同样使用了USE_MYMATH，CMake通过TutorialConfig.h.in将该值传递到源代码中。需要在该文件内添加：

```
#cmakedefine USE_MYMATH
```

## Step3 添加库的依赖项

使用依赖项可以更好地控制库/可执行文件的链接和引用。同时也提供了对CMake内目标属性的控制。使用依赖项的主要语法是：

```
  -  target_compile_definitions
  -  target_compile_options
  -  target_include_directories
  -  target_link_libraries
```

首先是MathFunctions。我们首先声明任何链接到MathFunctions的文件都 需要包含当前的源目录，而MathFunctions本身 没有。因此，这可以使用INTERFACE 依赖项。在MathFunction目录下的CMakeLists.txt中添加：

```
# 声明所有链接到我们的都需要引用当前目录，
# 去寻找MathFunctions.h，而我们自身不需要
target_include_directories(MathFunctions
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )
```

这样我们就为MathFunctions指定了使用要求，我们可以安全地删除之前使用的EXTRA_INCLUDES变量。

## Step4 安装与测试

现在我们可以开始添加测试功能和安装规则。

安装规则相对简单：对MathFunctions我们安装库文件和头文件，对应用我们安装可执行文件并配置头文件。

在MathFunctions/CMakeLists.txt中添加：

```
install (TARGETS MathFunctions DESTINATION bin)
install (FILES MathFunctions.h DESTINATION include)
```

在顶层CMakeLists.txt中添加：

```
install(TARGETS Tutorial DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
          DESTINATION include
          )
```

在经过cmake和make后，使用make installl 命令进行安装，输出如下：

```
root@x:~/qinrui/cmake/step4/build# make install 
[ 50%] Built target MathFunctions
[100%] Built target Tutorial
Install the project...
-- Install configuration: ""
-- Installing: /usr/local/bin/Tutorial
-- Installing: /usr/local/include/TutorialConfig.h
-- Installing: /usr/local/bin/libMathFunctions.a
-- Installing: /usr/local/include/MathFunctions.h
```

此时Tutorial即已经被安装到系统中，不需要再当前目录下执行，也不需要使用./运行。

接下来对我们的应用进行测试。在顶层CMakeLists.txt中我们可以添加一些测试样例来验证应用的正确性。

```
# 启用测试
enable_testing()

# 测试应用能否运行
add_test(NAME Runs COMMAND Tutorial 25)

# 测试Usage语句是否正确
add_test(NAME Usage COMMAND Tutorial)
set_tests_properties(Usage
  PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number"
  )

# 定义一个测试样例函数
function(do_test target arg result)
  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
  set_tests_properties(Comp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction(do_test)

# 添加测试样例
do_test(Tutorial 25 "25 is 5")
do_test(Tutorial -25 "-25 is [-nan|nan|0]")
do_test(Tutorial 0.0001 "0.0001 is 0.01")
```

编译完成后，要运行这些测试，需要执行

```
ctest -N
ctest -VV
```

```
root@node01:~/cmake_tutorials/step4/build# ctest -N
Test project /root/cmake_tutorials/step4/build
  Test #1: Runs
  Test #2: Usage
  Test #3: Comp25
  Test #4: Comp-25
  Test #5: Comp0.0001

Total Tests: 5
root@node01:~/cmake_tutorials/step4/build# ctest -VV
UpdateCTestConfiguration  from :/root/cmake_tutorials/step4/build/DartConfiguration.tcl
UpdateCTestConfiguration  from :/root/cmake_tutorials/step4/build/DartConfiguration.tcl
Test project /root/cmake_tutorials/step4/build
Constructing a list of tests
Done constructing a list of tests
Updating test list for fixtures
Added 0 tests to meet fixture requirements
Checking test dependency graph...
Checking test dependency graph end
test 1
    Start 1: Runs

1: Test command: /root/cmake_tutorials/step4/build/Tutorial "25"
1: Test timeout computed to be: 10000000
1: Mysqrt: The square root of 25 is 5
1/5 Test #1: Runs .............................   Passed    0.00 sec
test 2
    Start 2: Usage

2: Test command: /root/cmake_tutorials/step4/build/Tutorial
2: Test timeout computed to be: 10000000
2: /root/cmake_tutorials/step4/build/Tutorial Version 1.0
2: Usage: /root/cmake_tutorials/step4/build/Tutorial number
2/5 Test #2: Usage ............................   Passed    0.00 sec
test 3
    Start 3: Comp25

3: Test command: /root/cmake_tutorials/step4/build/Tutorial "25"
3: Test timeout computed to be: 10000000
3: Mysqrt: The square root of 25 is 5
3/5 Test #3: Comp25 ...........................   Passed    0.00 sec
test 4
    Start 4: Comp-25

4: Test command: /root/cmake_tutorials/step4/build/Tutorial "-25"
4: Test timeout computed to be: 10000000
4: Mysqrt: The square root of -25 is 0
4/5 Test #4: Comp-25 ..........................   Passed    0.00 sec
test 5
    Start 5: Comp0.0001

5: Test command: /root/cmake_tutorials/step4/build/Tutorial "0.0001"
5: Test timeout computed to be: 10000000
5: Mysqrt: The square root of 0.0001 is 0.01
5/5 Test #5: Comp0.0001 .......................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 5

Total Test time (real) =   0.02 sec
```

## Step5 添加系统自检

让我们考虑当往项目中添加的代码中依赖的功能目标平台没有的情况。比如，我们需要添加的代码取决于目标平台是否有log和exp函数。我们假设这些功能不常见。

如果平台拥有log和exp函数，我们就在mysqrt函数中使用它们来计算平方根。我们先通过在顶层CMakeLists.txt中使用CheckSymbolExists.cmake宏来测试这些功能。

```
# 当前系统是否提供log和exp函数？
include(CheckSymbolExists)
set(CMAKE_REQUIRED_LIBRARIES "m")
check_symbol_exists(log "math.h" HAVE_LOG)
check_symbol_exists(exp "math.h" HAVE_EXP)
```

cmake时的输出：

```
-- Looking for log
-- Looking for log - found
-- Looking for exp
-- Looking for exp - found
```

接下来在TutorialConfig.h.in中添加这些定义，使我们能够在mysqrt.cxx中使用它们

```
// 平台是否有log和exp函数
#cmakedefine HAVE_LOG
#cmakedefine HAVE_EXP
```

接下来修改MathFunctions/mysqrt.cxx。先引用cmath头文件，然后使用#ifdef，给出一个由log和exp函数实现的sqrt函数。

```
#include "MathFunctions.h"
//#include "TutorialConfig.h"
#include <iostream>
#include <cmath>
double mysqrt(double x)
{
	if (x <= 0)
	{
		return 0;
	}

	// 如果有log和exp就使用它们
#if defined(HAVE_LOG) && defined(HAVE_EXP)
	double result = exp(log(x) * 0.5);
	std::cout << "Computing sqrt of " << x
			  << " to be " << result << " using log" << std::endl;
#else
	double result = x;

	//循环十次
	for (int i = 0; i < 10; ++i)
	{
		if (result <= 0)
		{
			result = 0.1;
		}
		double delta = x - (result * result);
		result = result + 0.5 * delta / result;
		std::cout << "Computing sqrt of " << x
				  << " to be " << result << std::endl;
	}
#endif
	return result;
}
```

此时如果我们运行cmake，HAVE_LOG和HAVE_EXP都被定义了，但是mysqrt并没有使用它们。那是因为我们没有在mysqrt.cxx中引用TutorialConfig.h（被我特意注释了）。同时我们要更新对应的CMakeLists.txt文件，告诉它该头文件在哪。

```
  add_library(MathFunctions mysqrt.cxx)

# 声明所有链接到我们的都需要引用当前目录，
# 去寻找MathFunctions.h，而我们自身不需要
# 我们自己需要 Tutorial_BINARY_DIR 但我们的使用者不需要，
# 所以定义为PRIVATE
  target_include_directories(MathFunctions
            INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
            PRIVATE ${Tutorial_BINARY_DIR}
            )

  install(TARGETS MathFunctions DESTINATION lib)
  install(FILES MathFunctions.h DESTINATION include)
```

实际上，更好地处理方法是将HAVE_LOG和HAVE_EXP定义在MathFunctions.h中。

运行结果：

```
root@x:~/qinrui/cmake/step5/build# ./Tutorial 123
Computing sqrt of 123 to be 11.0905 using log
Mysqrt: The square root of 123 is 11.0905
```

## Step6 添加自定义命令和生成文件

本节我们会展示如何将一个生成的文件添加到应用程序的构建过程中。在本例中，我们建立一张预先计算好的平方根表，作为构建的一部分，将表编译进应用程序中。

首先，我们需要一个生成表的程序。我们在MathFunctions子目录下新建MakeTable.cxx文件来实现这个功能。

```
// 建立平方根表
#include <cmath>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		return 1;
	}

	std::ofstream fout(argv[1], std::ios_base::out);
	const bool fileOpen = fout.is_open();
	if (fileOpen)
	{
		fout << "double sqrtTable[] = {" << std::endl;
		for (int i = 0; i < 10; ++i)
		{
			fout << sqrt(static_cast<double>(i)) << "," << std::endl;
		}
		fout << "0};" << std::endl;
		fout.close();
	}
	return fileOpen ? 0 : 1;
}
```

注意在这段C++程序中，输出文件名是由命令行参数决定的。

接下来就是要在MathFunctions的CMakeLists.txt中添加命令，使改程序的运行成为构建的一部分。

```
  #  首先添加一个生成表格的可执行文件
  add_executable(MakeTable MakeTable.cxx)

# 添加命令去生成源代码
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  DEPENDS MakeTable
  )

#  添加库
add_library(MathFunctions
            mysqrt.cxx
            ${CMAKE_CURRENT_BINARY_DIR}/Table.h
            )
# 声明所有链接到我们的都需要引用当前目录，
# 去寻找MathFunctions.h，而我们自身不需要
# 我们自己需要 Tutorial_BINARY_DIR 但我们的使用者不需要，
# 所以定义为PRIVATE
# 我们需要可执行目录去寻找table.h
target_include_directories(MathFunctions
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          PRIVATE ${Tutorial_BINARY_DIR}
                  ${CMAKE_CURRENT_BINARY_DIR}
          )
install(TARGETS MathFunctions DESTINATION lib)
install(FILES MathFunctions.h DESTINATION include)
```

首先，MakeTable的可执行文件被添加。之后我们添加一个命令，用于指定Table.h并运行生成MakeTable 所以我们需要让CMake知道mysqrt.cxx依赖于生成的文件Table.h。将Table.h添加到MathFunctions库中的源代码列表。 此外还需要将可执行目录添加到include目录列表中，以便Table.h能够发现并包含在mysqrt.cxx中。

```
#include "MathFunctions.h"
#include "TutorialConfig.h"
#include <iostream>

// 引用生成的表
#include "Table.h"

#include <cmath>

double mysqrt(double x)
{
	if (x <= 0)
	{
		return 0;
	}

	// 通过查表来辅助查找一个初值
	double result = x;
	if (x >= 1 && x < 10)
	{
		result = sqrtTable[static_cast<int>(x)];
	}

	// 循环计算十次
	for (int i = 0; i < 10; ++i)
	{
		if (result <= 0)
		{
			result = 0.1;
		}
		double delta = x - (result * result);
		result = result + 0.5 * delta / result;
		std::cout << "Computing sqrt of " << x
				  << " to be " << result << std::endl;
	}

	return result;
}
```

cmake编译运行，找到Table.h的位置及内容

```
root@x:~/qinrui/cmake/step6# find . -name Table.h
./build/MathFunctions/Table.h
root@x:~/qinrui/cmake/step6/build# cat MathFunctions/Table.h 
double sqrtTable[] = {
0,
1,
1.41421,
1.73205,
2,
2.23607,
2.44949,
2.64575,
2.82843,
3,
0};
```

## Step7 构建安装程序

接下来我们假设我们需要将项目提供给他人使用。我们希望在多种平台上提供二进制和源代码。 这和我们之前的安装操作(Step4)有一些不同。在这个例子中，我们会构建支持二进制安装和包管理的安装程序。为此，我们使用CPack来创建平台安装程序。具体来说，需要在顶层CMakeLists.txt中添加几行。

```
 include(InstallRequiredSystemLibraries)
 set(CPACK_RESOURCE_FILE_LICENSE  \
  "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
 set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
 set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
 include(CPack)
```

我们首先include(InstallRequiredSystemLibraries)，这个模块包含项目所需的运行库。 然后设置CPack变量，用于存储许可证和版本信息。版本信息就是之前我们设置的。最后include(CPack) 模块，它会利用这些变量和一些系统设置来搭建安装包。

正常Cmake make之后，用cpack命令构建二进制分发。命令输出：

```
root@x:~/qinrui/cmake/step7/build# cpack
CPack: Create package using STGZ
CPack: Install projects
CPack: - Run preinstall target for: Tutorial
CPack: - Install project: Tutorial
CPack: Create package
CPack: - package: /root/qinrui/cmake/step7/build/ \
Tutorial-1.0.1-Linux.sh generated.
CPack: Create package using TGZ
CPack: Install projects
CPack: - Run preinstall target for: Tutorial
CPack: - Install project: Tutorial
CPack: Create package
CPack: - package: /root/qinrui/cmake/step7/build/ \
Tutorial-1.0.1-Linux.tar.gz generated.
CPack: Create package using TZ
CPack: Install projects
CPack: - Run preinstall target for: Tutorial
CPack: - Install project: Tutorial
CPack: Create package
CPack: - package: /root/qinrui/cmake/step7/build/ \
Tutorial-1.0.1-Linux.tar.Z generated.
```

生成的压缩文件中，有三个目录，/bin，/include, /lib 分别对应可执行文件、包含文件、库文件

## Step8 添加仪表盘

添加对将测试结果提交到仪表板的支持非常简单。我们 在之前的步骤中已经为我们的项目定义了许多测试 教程。我们只需运行这些测试并将其提交到仪表板。为了include仪表盘我们在顶层CMakeLists.txt include CTest模块

```
Replace:
  # enable testing
  enable_testing()

With:
  # enable dashboard scripting
  include(CTest)
```

Ctest模块会自动调用enable_testing，所以可以删除。

我们还需要创建一个CTestConfig.cmake文件，我们可以在其中指定项目名称以及需要提交到仪表盘的部分。