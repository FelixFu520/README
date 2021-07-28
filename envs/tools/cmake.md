# CMake安装

⌚️: 2020年10月21日

📚参考

---

#### 下载

[https://cmake.org](https://cmake.org/) or https://github.com/Kitware/CMake/releases/tag/v3.14.4

```
#tar -zxvf file_name.tar.gz
#cd cmake-3.14.4/
#./configure
#make
#make install

#update-alternatives --install /usr/bin/cmake cmake /usr/local/bin/cmake 1 --force
update-alternatives: using /usr/local/bin/cmake to provide /usr/bin/cmake (cmake) in auto mode

# cmake --version
cmake version 3.14.4
CMake suite maintained and supported by Kitware (kitware.com/cmake).
```