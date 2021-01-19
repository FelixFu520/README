
cmake_minimum_required (VERSION 3.3)
project (HW) # HW Hello World
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# -------------------------------Version Info
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})

# CMakeLists to source
configure_file (
  "${PROJECT_SOURCE_DIR}/config/hello.h.in"
  "${PROJECT_BINARY_DIR}/config/hello.h"
  )

# config version
include_directories("${PROJECT_BINARY_DIR}/config") # find head config/hello.h
# -------------------------------------------

# ----------------------------------lib mysqrt
option (USE_MYMATH "Use tutorial provided math implementation" ON) 
if(USE_MYMATH)
	include_directories ("${PROJECT_SOURCE_DIR}/lib") # mysqrt lib head
	add_subdirectory (lib) 
       #set (EXTRA_LIBS ${EXTRA_LIBS} mysqrt)
endif(USE_MYMATH)
# ----------

#----------------------------------src source
#add_executable(HW main.cpp)
# target_link_libraries(HW ${EXTRA_LIBS})
#target_link_libraries(HW mysqrt)

#install(TARGETS HW  DESTINATION bin)
ADD_SUBDIRECTORY(src bin)
#-------------------------------------------
install(FILES "${PROJECT_BINARY_DIR}/config/hello.h" DESTINATION include)
