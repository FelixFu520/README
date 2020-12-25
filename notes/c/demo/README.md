root@node01:~/demo/build# cmake ..
-- Configuring done
-- Generating done
-- Build files have been written to: /root/demo/build
root@node01:~/demo/build# make
[ 25%] Built target hello
[ 50%] Built target hello_static
Scanning dependencies of target main_a
[ 62%] Linking C executable main_a
[ 75%] Built target main_a
Scanning dependencies of target main_s
[ 87%] Building C object src/CMakeFiles/main_s.dir/main.c.o
[100%] Linking C executable main_s
[100%] Built target main_s
root@node01:~/demo/build# make install
[ 25%] Built target hello
[ 50%] Built target hello_static
[ 75%] Built target main_a
[100%] Built target main_s
Install the project...
-- Install configuration: ""
-- Installing: /usr/local/lib/libhello.so.1.2
-- Up-to-date: /usr/local/lib/libhello.so.1
-- Up-to-date: /usr/local/lib/libhello.so
-- Installing: /usr/local/lib/libhello.a
-- Up-to-date: /usr/local/include/hello/hello.h
-- Installing: /usr/local/bin/main_s
-- Set runtime path of "/usr/local/bin/main_s" to ""
-- Installing: /usr/local/bin/main_a
-- Up-to-date: /usr/local/lib/libhello.so.1.2
-- Up-to-date: /usr/local/lib/libhello.so.1
-- Up-to-date: /usr/local/lib/libhello.so

root@node01:~/demo/build# ldconfig
root@node01:~/demo/build# main_s
Hello World
root@node01:~/demo/build# main_a
Hello World
root@node01:~/demo/build# 
