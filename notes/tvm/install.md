# Ubuntu下TVM的编译安装

2020年11月26日

---



官方安装文档地址：https://docs.tvm.ai/install/index.html
系统环境：Ubuntu 18.04 LTS 64-bit，其他环境或需求可参考官方文档。



## 1. LLVM部分

虽然LLVM对于TVM是可选项，但是如果要部署到CPU端，那么LLVM几乎是必须的，所以建议安装LLVM。本次安装LLVM6.0。
**第一步，添加相关源**
编辑`/etc/apt/sources.list`，将以下源加入：

```
deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial-6.0 main
deb-src http://apt.llvm.org/xenial/ llvm-toolchain-xenial-6.0 main     
```

加入完成后需取得数字证书

```
wget -O - http://llvm.org/apt/llvm-snapshot.gpg.key|sudo apt-key add -
```

然后务必进行`apt-get update`
**第二步，安装LLVM**

```
apt-get install clang-6.0 lldb-6.0
```

其他操作系统和LLVM版本参考：https://apt.llvm.org/

## 2. TVM部分

**第一步，从GitHub克隆TVM的repo**

```
# 1. Clone the project
git clone --recursive https://github.com/apache/incubator-tvm tvm
```

注意此处的`--recursive`是必须的，否则在编译时会出错。
**第二步，安装前准备**

```
# 2. Install Linux dependencies
sudo apt-get update
sudo apt-get install -y python3 python3-pip python3-dev python3-setuptools gcc libtinfo-dev zlib1g-dev build-essential cmake libedit-dev libxml2-dev

```

**第三步，修改config.cmake配置**
建立build文件夹，复制`config.cmake`。

```
# 3. Build the shared library
mkdir build
cp cmake/config.cmake build # change settings in cmake file
```

然后修改LLVM配置，将`set(USE_LLVM OFF)`改为`set(USE_LLVM ON)`
**第四步，启动编译**

```
# for cpu and gpu, need to install LLVM first
# i) Download LLVM pre-built version 9.0 from http://releases.llvm.org/download.html
# 2) set (USE_LLVM /path/to/llvm/bin/llvm-config) in config.cmake

cd build
cmake ..
make -j4
```

如果顺利完成，即可进入Python包安装

## 3. Python包安装

此处使用官方文档推荐的**第一种方法**进行Python包安装。这种方法可以使我们更改源代码并重新编译后，无需对Python端进行任何更改。
**第一步，编辑`~/.bashrc`，在文件末尾添加：**

```
# 方式一（推荐）
# 4. Python package installation
# Recommended for developers, no need to call setup!
# It would be better if adding them to ~/.bashrc
export TVM_HOME=/path/to/tvm
export PYTHONPATH=TVM_HOME/python:TVM_HOME/topi/python:TVM_HOME/nnvm/python:{PYTHONPATH}

# 方式二
#install tvm package for the current user
#NOTE: if you installed python via homebrew, --user is not needed during installaiton
#it will be automatically installed to your user directory.
#providing --user flag may trigger error during installation in such case.
export MACOSX_DEPLOYMENT_TARGET=10.9  # This is required for mac to avoid symbol conflicts with libstdc++
cd python; python setup.py install --user; cd ..
cd topi/python; python setup.py install --user; cd ../..
cd nnvm/python; python setup.py install --user; cd ../..


```

其中`/path/to/tvm`为tvm目录。
**第二步，使修改立即生效**

```
source ~/.bashrc
```

**最后安装其他Python依赖**
必须的依赖：

```
pip install --user numpy decorator attrs
```

事实证明官方教程讲得很清晰，之后就可以顺利在Python里`import tvm`啦！



如果需要RPC Tracker：

```
pip install --user tornado
```

如果需要auto-tuning模块：

```
pip install --user tornado psutil xgboost
```

解析Relay text format程序必须使用Python 3并安装：

```
pip install --user mypy orderedset antlr4-python3-runtime
```



## 参考

> https://blog.csdn.net/u014448054/article/details/101352550