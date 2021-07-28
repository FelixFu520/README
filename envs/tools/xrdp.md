# XRDP安装

⌚️: 2020年10月21日

📚参考

---



```
#安装xrdp

  sudo apt-get install xrdp

#安装vnc4server

 sudo apt-get install vnc4server tightvncserver

#安装xubuntu-desktop

 sudo apt-get install xubuntu-desktop

#向xsession中写入xfce4-session

  echo "xfce4-session" >~/.xsession


设置配置文件

sudo vi /etc/xrdp/startwm.sh﻿​
在. /etc/X11/Xsession 前一行插入

xfce4-session﻿​

#开启xrdp服务

sudo service xrdp restart

Ubuntu 16.04 8卡10卡xface桌面

1安装server 版系统

2安装xrdp

3安装xubuntu-desktop桌面

5启动lightdm
```

