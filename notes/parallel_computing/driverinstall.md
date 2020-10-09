# Ubuntu16.04安装NVIDIA驱动
## 1、卸载原有的NVIDIA驱动（没装的话就跳过）
```
一般方法:
sudo apt remove nvidia*
如果使用.run文件安装,使用--uninstall卸载（具体方法百度）
```
## 2、禁用nouveau
安装NVIDIA需要把系统自带的驱动禁用，打开文件：
```
sudo vim /etc/modprobe.d/blacklist.conf

# 在文本最后添加以下内容：
blacklist nouveau
option nouveau modeset=0
``` 
   
  
保存退出，执行以下命令生效：
```
sudo update-initramfs -u
```
重启电脑后输入：
```
lsmod | grep nouveau
```
没有任何输出说明禁用成功。

## 3、安装NVIDIA显卡驱动
首先查看自己电脑自己电脑支持的驱动版本：   
```
sudo apt-cache search nvidia*     
```
或者直接去官网下载最新版本的驱动，然后安装（建议这种方式安装）
```
cd ~/Download/ 
sudo chmod a+x NVIDIA-Linux-x86_64-384.130.run
```
安装:
```
sudo ./NVIDIA-Linux-x86_64-375.20.run --no-opengl-files
```
* –no-opengl-files 只安装驱动文件，不安装OpenGL文件。这个参数最重要
* –no-x-check 安装驱动时不检查X服务
* –no-nouveau-check 安装驱动时不检查nouveau 
* 后面两个参数可不加。   

提示安装基本上都是accept，yes，当提示你nvidia-xconfig时，就视自己的电脑情况而定，如果电脑是双显卡（双独显、集显和独显）就选择不安装，如果只有一个显卡就选择安装。    
   
安装完毕后重启验证是否安装成功：
```
nvidia-smi
```
出现以上类似的输出表示已经安装成功
## 4、卸载驱动
```
$ sudo /usr/bin/nvidia-uninstall #uninstall driver
```
