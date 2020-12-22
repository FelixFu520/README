cmake_minimum_required(VERSION 2.6)
SET(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++11)

project(Tutorial)

set(Tutorial_VERSION_MAJOR 1)
set(Tutorial_VERSION_MINOR 0)

configure_file(
	"${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
	"${PROJECT_BINARY_DIR}/TutorialConfig.h"
	)

include_directories("${PROJECT_BINARY_DIR}")
option (USE_MYMATH "Use tutorial provided math implementation" ON) 
# 是否使用自定义函数库
if (USE_MYMATH)	
	include_directories ("${PROJECT_SOURCE_DIR}/MathFunctionsLib")
	add_subdirectory (MathFunctionsLib)
	set(EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif(USE_MYMATH)
add_executable(Tutorial tutorial.cxx)
target_link_libraries (Tutorial ${EXTRA_LIBS})

install(TARGETS Tutorial DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
          DESTINATION include
          )


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
