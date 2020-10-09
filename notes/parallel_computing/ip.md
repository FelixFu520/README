# Ubuntu命令行网络配置
### 1.配置IP
打开ubuntu的/etc/network/interfaces文件默认的内容如下：
```
auto lo
iface lo inet loopback

# 动态获取的配置方法：
auto eth0
iface eth0 inet dhcp

# 静态分配的配置方法：
auto eth0
iface eth0 inet static
address 192.168.0.1
netmask 255.255.255.0
gateway 192.168.0.1
```
### 2. 配置DNS
```
vim /etc/resolvconf/resolv.conf.d/base
# 加入以下内容
223.5.5.5
114.114.114.114

resolvconf -u
```
### 3.重启下网络
```
$/etc/init.d/networking restart(这条命令是重启网卡)
或者
$ifdown eth0
$ifup eth0（这两条命令是有针对性的重启某个网络接口，因为一个系统可能有多个网络接口）
```
### 3.查看网络配置的参数是不是正确（每进行一次操作都可以查看一下是不是修改了网络配置）
```
$ifconfig
```
### 4.看看是不是能够ping通
ping不通网关说明网络配置有问题 ping不通域名说明dns有问题
   
```
查看DNS：cat /etc/resolv.conf   
查看网关：ip route show    
启动网卡：
方式一：ifdown/ifup
# ifdown eth0
# ifup eth0
方式二：
ifconfig
# ifconfig eth0 down
# ifconfig eth0 up
```