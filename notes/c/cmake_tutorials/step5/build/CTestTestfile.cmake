# CMake generated Testfile for 
# Source directory: /root/cmake_tutorials/step5
# Build directory: /root/cmake_tutorials/step5/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Runs "/root/cmake_tutorials/step5/build/Tutorial" "25")
set_tests_properties(Runs PROPERTIES  _BACKTRACE_TRIPLES "/root/cmake_tutorials/step5/CMakeLists.txt;42;add_test;/root/cmake_tutorials/step5/CMakeLists.txt;0;")
add_test(Usage "/root/cmake_tutorials/step5/build/Tutorial")
set_tests_properties(Usage PROPERTIES  PASS_REGULAR_EXPRESSION "Usage:.*number" _BACKTRACE_TRIPLES "/root/cmake_tutorials/step5/CMakeLists.txt;45;add_test;/root/cmake_tutorials/step5/CMakeLists.txt;0;")
add_test(Comp25 "/root/cmake_tutorials/step5/build/Tutorial" "25")
set_tests_properties(Comp25 PROPERTIES  PASS_REGULAR_EXPRESSION "25 is 5" _BACKTRACE_TRIPLES "/root/cmake_tutorials/step5/CMakeLists.txt;52;add_test;/root/cmake_tutorials/step5/CMakeLists.txt;59;do_test;/root/cmake_tutorials/step5/CMakeLists.txt;0;")
add_test(Comp-25 "/root/cmake_tutorials/step5/build/Tutorial" "-25")
set_tests_properties(Comp-25 PROPERTIES  PASS_REGULAR_EXPRESSION "-25 is [-nan|nan|0]" _BACKTRACE_TRIPLES "/root/cmake_tutorials/step5/CMakeLists.txt;52;add_test;/root/cmake_tutorials/step5/CMakeLists.txt;60;do_test;/root/cmake_tutorials/step5/CMakeLists.txt;0;")
add_test(Comp0.0001 "/root/cmake_tutorials/step5/build/Tutorial" "0.0001")
set_tests_properties(Comp0.0001 PROPERTIES  PASS_REGULAR_EXPRESSION "0.0001 is 0.01" _BACKTRACE_TRIPLES "/root/cmake_tutorials/step5/CMakeLists.txt;52;add_test;/root/cmake_tutorials/step5/CMakeLists.txt;61;do_test;/root/cmake_tutorials/step5/CMakeLists.txt;0;")
subdirs("MathFunctionsLib")
