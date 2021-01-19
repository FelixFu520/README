# CMakeLists格式

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



## 2.Demo

见`tutorials_cmake`目录

