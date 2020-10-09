# Ubuntu 16.04 Server 版安装过程图文详解
如何制作Ubuntu 16.04 server的镜像，自己百度。   
进入系统安装的第一个界面，开始系统的安装操作。每一步的操作，左下角都会提示操作方式！！
### 1.选择系统语言-English  
![](../imgs/60.png)   
### 2.选择操作-Install Ubuntu Server
![](../imgs/61.png)   
### 3.选择安装过程和系统的默认语言-English
![](../imgs/62.png)   
### 4.选择区域-other
![](../imgs/63.png)   
### 5.选择亚洲-Asia
![](../imgs/64.png)   
### 6.选择国家-China
![](../imgs/65.png)   
### 7.选择字符集编码-United States
![](../imgs/66.png)   
### 8.是否扫描和配置键盘，选择否-No
![](../imgs/67.png)   
### 9.选择键盘类型-English (US)
![](../imgs/68.png)   
### 10.选择键盘布局-English (US)
![](../imgs/69.png)   
### 11.配置网络，因为内网没开DHCP ,暂时等装完系统在进行配置
![](../imgs/70.png)    
### 12.设置主机名称(自行设置，这里我设置为“ubuntu”)-Continue
![](../imgs/71.png)   
### 13.设置用户全名(这里为“myuser”)-Continue
![](../imgs/72.png)   
### 14.设置登录账号(这里为“myuser”)-Continue；
![](../imgs/73.png)   
### 15.设置登录密码(空格选择“Show Password in Clear”可以显示密码)-Continue；
![](../imgs/74.png)   
### 16.重复上一步设置的登录密码-Continue；
![](../imgs/75.png)   
### 17.是否加密home文件夹，选择否-No
![](../imgs/76.png)  
### 18.选择分区方式(分区向导-使用整个磁盘)-“Guided - use entire disk and set up LVM”
![](../imgs/77.png)   
### 19.选择要分区的磁盘(这里只有一块)
![](../imgs/78.png)   
### 20.是否将变更写入磁盘，选择是-Yes
![](../imgs/79.png)   
![](../imgs/80.png)   
### 21.磁盘分区选择NO,这里要把boot分区给删了
![](../imgs/81.png)   
### 22.选择/boot回车-delete the partition
![](../imgs/82.png)   
![](../imgs/83.png)   
### 23.完成分区
![](../imgs/84.png)   
### 24.选择Yes
![](../imgs/85.png)
### 25.选择升级方式，No automatic updates
![](../imgs/86.png)   
### 26.选择要安装的软件，多加一个OpenSSH Server
![](../imgs/87.png)   
### 27.是否安装GRUB引导程序，选择是-Yes
![](../imgs/88.png)   
### 28.完成安装，选择下一步-Continue
![](../imgs/89.png)   
### 29.系统安装完会自动启动主机，然后输入设置好的登录账户和密码就可以开始使用了
![](../imgs/90.png) 