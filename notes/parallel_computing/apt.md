# Ubuntu16.04更改apt源
## 一、Ubuntu16.04：控制台挂载/(卸载)U盘
### 1.将U盘插入

### 2.直接回车，然后输入以下命令
```
sudo fdisk -l
```
此时，会输出一大段问题，只看最后一段可以得到U盘
```
Device Boot Start End Sectors Size Id Type
/dev/sdb4 * 256 7866367 7866112 3.8G b W95 FAT32
```
### 3.挂载U盘
```
sudo mount -t vfat /dev/sdb4 /media 
//-t 后的vfat是文件系统格式，即FAT32
//dev/sdb4是需要挂载的U盘//media是挂载点
```
### 4.进入U盘
```
cd /media
```
### 5.卸载U盘
```
sudo umount /dev/sdb4
```
## 一、ubuntu16.04 server 更换apt-get阿里源
### 1.备份系统自带源
```
mv /etc/apt/sources.list /etc/apt/sources.list.bak
```
### 2.修改/etc/apt/sources.list文件
```
vim /etc/apt/sources.list  
```
加入如下内容
```
# 默认注释了源码镜像以提高 apt update 速度，如有需要可自行取消注释
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-updates main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-updates main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-backports main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-backports main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-security main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-security main restricted universe multiverse

# 预发布软件源，不建议启用
# deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-proposed main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-proposed main restricted universe multiverse
```
### 3.更新生效
```
apt-get update
```
