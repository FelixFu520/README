cmake_minimum_required(VERSION 3.14)

# include lib header file
#INCLUDE_DIRECTORIES(/usr/include/hello) 
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)

# add executable with shared library 
ADD_EXECUTABLE(main_s main.c) 
TARGET_LINK_LIBRARIES(main_s hello)


# add executable with static library
ADD_EXECUTABLE(main_a main.c)
#TARGET_LINK_LIBRARIES(main_a libhello.a)
TARGET_LINK_LIBRARIES(main_a hello_static)
