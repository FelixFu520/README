cmake_minimum_required(VERSION 2.6)
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
