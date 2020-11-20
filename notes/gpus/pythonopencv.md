# Ubuntu下安裝Python版OpenCV

2020年11月20日

---



# 前言

筆者試著要在Ubuntu系統下安裝Python版的OpenCV，一開始只使用pip來安裝，但卻會報錯。後來才發現原來它還需要幾個debian的package才能成功運行。

# 安裝指令

這裡直接給出可以成功執行的指令：

```sh
pip install opencv-python
apt-get install -y libglib2.0-0
apt-get install -y libsm6 libxext6
apt-get install -y libxrender-dev
1234
```

# 踩坑記錄

此處記錄安裝過程中碰到的錯誤訊息及解決方式

- 在執行完`pip install opencv-python`後，想要`import cv2`，卻出現了如下錯誤，這個錯誤可以用`apt-get install -y libglib2.0-0`來解決

> ImportError: libgthread-2.0.so.0: cannot open shared object file: No such file or directory

- 第二行執行結束後，同樣想要`import cv2`，這時會出現如下錯誤，這個錯誤可以用`apt-get install -y libsm6 libxext6`來解決

> ImportError: libSM.so.6: cannot open shared object file: No such file or directory

- 第三行執行結束後，想要`import cv2`，會出現如下錯誤，這個錯誤可以用`apt-get install -y libxrender-dev`來解決

> ImportError: libXrender.so.1: cannot open shared object file: No such file or directory

# 測試

Python版的OpenCV安裝完成後可以用以下代碼測試：

```python
import cv2
print(cv2.__version__) #3.4.3
12
```

如果未出現任何錯誤訊息表示安裝成功。

