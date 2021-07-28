# CMakeLists格式

⌚️:2020年11月30日

📚参考

---

## 1. 框架

1. 工程配置部分
   - 工程名、编译调试模式、编译系统语言
2. 依赖执行部分
   - 工程包、头文件、依赖苦等
3. 其他辅助部分（非必需）
   - 参数打印、遍历目录
4. 判断控制部分（非必需）
   - 条件判断、函数定义、条件执行等

Note:

1.对于${X}，X表示变量名称， ​\${X}表示变量值，if语句除外。 

2.导入的功能函数，如SET大小写均可，没有特殊限制

```
command(arg1 arg2 ...)		# 运行命令
set(var_name var_value)		# 定义变量，或者给已存在的变量赋值
command(arg1 ${var_name})	# 使用变量

**************************工程配置部分********************************
cmake_minimum_required(VERSION num)		# Cmake最低版本号要求
project(cur_project_name)							# 项目信息
set(CMAKE_CXX_FLAGS "xxx")						# 设定编译器版本，如-std=c++11
set(CMAKE_BUILD_TYPE "xxx")						# 设定编译模式，如Debug/Release
MESSAGE(STATUS" This is BINARY dir " ${HELLO_BINARY_DIR})	# 输出信息

**************************依赖执行部分********************************
find_package(std_lib_name VERSION REQUIRED)		# 引入外部依赖
add_library(<name> [lib_type] source1)				# 生成库类型（动态/静态）
include_directories(${std_lib_name_INCLUDE_DIRS})		# 指定include路径，放在add_exectutable前面
add_executable(cur_project_name XXX.cpp)			# 指定生成目标
target_link_libraries(${std_lib_name_LIBRARIES})	# 指定libraries路径，放在add_executable后面

install()

**************************其他辅助部分********************************
function(function_name arg)			# 定义一个函数
add_subdirectory(dir)						# 添加一个子目录
AUX_SOURCE_DIRECTORY(. SRC_LIST)	# 查找当前目录所有文件，并保存到SRC_LIST变量中
FOREACH(one_dir ${SRC_LIST})
		MESSAGE(${one_dir})				# 使用message进行打印
ENDFOREACH(onedir)

**************************判断控制部分*******************************
if(expression)
	COMMAND1(ARGS)
ELSE(expression)
	COMMAND2(ARGS)
ENDIF(expression)

# expression
IF(var)	# 不是空，0，N，NO，OFF，FASLE，NOTFOUND或<var>_NOTFOUND时为真
IF(NOT var)
IF(var1 AND var2)
IF(var1 OR var2)
IF(COMMAND cmd)	# 当给定的cmd确实是命令并可以调用是为真
IF(EXISTS dir)
IF(EXISTS file)
IF(IS_DIRECTORY dirname)		# 当dirname是目录
IF(file1 IS_NEWER_THAN file2)	# 当file1比file2新，为真

# 循环
WHILE(condition)
	COMMAND1(ARGS)
	//...
ENDWHILE(condition)
```

## 2. 具体命令解析

### `PROJECT(projectname [CXX] [C] [Java])`

你可以用这个指令定义工程名称，并可指定工程支持的语言，支持的语言列表是可以忽略的， 默认情况表示支持所有语言。这个指令隐式的定义了两个 cmake 变量:`<projectname>_BINARY_DIR` 以及`<projectname>_SOURCE_DIR`，这里就是`HELLO_BINARY_DIR` 和 `HELLO_SOURCE_DIR`(所以 CMakeLists.txt 中两个 MESSAGE 指令可以直接使用了这两个变量)，因为采用的是内部编译，两个变量目前指的都是工程所在路径/backup/cmake/t1，后面我们会讲到外部编译，两者所指代的内容会有所不同。 

同时 cmake 系统也帮助我们预定义了 `PROJECT_BINARY_DIR` 和 `PROJECT_SOURCE_DIR`变量，他们的值分别跟 `HELLO_BINARY_DIR` 与 `HELLO_SOURCE_DIR` 一致。 为了统一起见，建议以后直接使用 `PROJECT_BINARY_DIR`，`PROJECT_SOURCE_DIR`，即使修改了工程名称，也不会影响这两个变量。如果使用了`<projectname>_SOURCE_DIR`，修改工程名称后，需要同时修改这些变量。



### **SET 指令的语法是：**

`SET(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]]) `

现阶段，你只需要了解 SET 指令可以用来显式的定义变量即可。 比如我们用到的是 `SET(SRC_LIST main.c)`，如果有多个源文件，也可以定义成：`SET(SRC_LIST main.c t1.c t2.c)`。



### **MESSAGE 指令的语法是：**

`MESSAGE([SEND_ERROR | STATUS | FATAL_ERROR] "message to display"...)`

这个指令用于向终端输出用户定义的信息，包含了三种类型:

```
SEND_ERROR，产生错误，生成过程被跳过。
SATUS，输出前缀为--的信息。
FATAL_ERROR，立即终止所有 cmake 过程. 
```

我们在这里使用的是 STATUS 信息输出，演示了由 PROJECT 指令定义的两个隐式变量HELLO_BINARY_DIR 和 HELLO_SOURCE_DIR。



### **ADD_EXECUTABLE(hello ${SRC_LIST})**

定义了这个工程会生成一个文件名为 hello 的可执行文件，相关的源文件是 SRC_LIST 中定义的源文件列表， 本例中你也可以直接写成 ADD_EXECUTABLE(hello main.c)。 

在本例我们使用了`${}`来引用变量，这是` cmake` 的变量应用方式，但是，有一些例外，比如在` IF `控制语句，变量是直接使用变量名引用，而不需要`${}`。如果使用了`${}`去应用变量，其实 IF 会去判断名为`${}`所代表的值的变量，那当然是不存在的了。

```
add_executable(<name> [WIN32] [MACOSX_BUNDLE]
               [EXCLUDE_FROM_ALL]
               source1 [source2 ...])
```

- name: 工程所要构建的目标名称
- WIN32/..: 目标app运行的平台
- source1：构建目标App的源文件

### **`ADD_SUBDIRECTORY `指令**

`ADD_SUBDIRECTORY(source_dir [binary_dir] [EXCLUDE_FROM_ALL])`

这个指令**用于向当前工程添加存放源文件的子目录**，**并可以指定中间二进制和目标二进制存放的位置**。EXCLUDE_FROM_ALL 参数的含义是将这个目录从编译过程中排除，比如，工程 的 example，可能就需要工程构建完成后，再进入 example 目录单独进行构建(当然，你 也可以通过定义依赖来解决此类问题)。 上面的例子定义了将 src 子目录加入工程，并指定编译输出(包含编译中间结果)路径为bin 目录。如果不进行 bin 目录的指定，那么编译结果(包括中间结果)都将存放在build/src 目录(这个目录跟原有的 src 目录对应)，指定 bin 目录后，相当于在编译时 将 src 重命名为 bin，所有的中间结果和目标二进制都将存放在 bin 目录。 

这里需要提一下的是 SUBDIRS 指令，使用方法是：SUBDIRS(dir1 dir2...)，但是这个指令已经不推荐使用。它可以一次添加多个子目录，并且，即使外部编译，子目录体系仍然会被保存。 如果我们在上面的例子中将 ADD_SUBDIRECTORY (src bin)修改为 SUBDIRS(src)。那么在 build 目录中将出现一个 src 目录，生成的目标代码 hello 将存放在 src 目录中。 



## 3. Demo

见`tutorials_cmake`目录

