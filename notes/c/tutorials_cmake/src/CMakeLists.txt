
ADD_EXECUTABLE(HW main.cpp)

target_link_libraries(HW mysqrt)

install(TARGETS HW  DESTINATION bin)
