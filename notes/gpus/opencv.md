# 安装OpenCV3与python-opencv

2020年9月4日

---

### 1 .安装cmake等依赖

```
$apt-get install cmake build-essential libgtk2.0-dev libavcodec-dev libavformat-dev libjpeg.dev libtiff4.dev libswscale-dev libjasper-dev
```

### 2 .[下载](http://opencv.org/releases.html)OpenCV-4.1.0

```
apt install git
git clone https://github.com/opencv/opencv/tree/4.1.0
```

或者官方下载

```
$unzip opencv-3.4.1.zip
$cd opencv-3.4.1 
$mkdir my_build_dir
$cd my_build_dir
```

### 3 .编译

Cmake一下

```
$cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
```

![img](imgs/96.png)

```
可能这里需要很长时间，所以要提前下载下来：
—————— start
1、下载　ippicv_2019_lnx_intel64_general_20180723.tgz文件,以存到iCloud。
2、修改配置文件
修改opencv里相关配置文件
打开终端，输入
    gedit ~/DownLoad/opencv_source/opencv/3rdparty/ippicv/ippicv.cmake #就是这个文件的路径
将47行的
     "https://raw.githubusercontent.com/opencv/opencv_3rdparty/${IPPICV_COMMIT}/ippicv/"
改为步骤1中手动下载的文件的本地路径：
    "file:~/Downloads/" #（仅供参考，根据自己的路径填写）
编辑完成保存退出。
——————— end
```

Cmake后

```
--     Linker flags (Release):      -Wl,--gc-sections  
--     Linker flags (Debug):        -Wl,--gc-sections  
--     ccache:                      NO
--     Precompiled headers:         YES
--     Extra dependencies:          dl m pthread rt
--     3rdparty dependencies:
-- 
--   OpenCV modules:
--     To be built:                 calib3d core dnn features2d flann gapi highgui imgcodecs imgproc ml objdetect photo stitching ts video videoio
--     Disabled:                    world
--     Disabled by dependency:      -
--     Unavailable:                 java js python2 python3
--     Applications:                tests perf_tests apps
--     Documentation:               NO
--     Non-free algorithms:         NO
-- 
--   GUI: 
--     GTK+:                        YES (ver 2.24.30)
--       GThread :                  YES (ver 2.48.2)
--       GtkGlExt:                  NO
--     VTK support:                 NO
-- 
--   Media I/O: 
--     ZLib:                        /usr/local/anaconda3/envs/sitonholy/lib/libz.so (ver 1.2.11)
--     JPEG:                        /usr/lib/x86_64-linux-gnu/libjpeg.so (ver 80)
--     WEBP:                        build (ver encoder: 0x020e)
--     PNG:                         /usr/lib/x86_64-linux-gnu/libpng.so (ver 1.2.54)
--     TIFF:                        build (ver 42 - 4.0.10)
--     JPEG 2000:                   /usr/lib/x86_64-linux-gnu/libjasper.so (ver 1.900.1)
--     OpenEXR:                     build (ver 1.7.1)
--     HDR:                         YES
--     SUNRASTER:                   YES
--     PXM:                         YES
--     PFM:                         YES
-- 
--   Video I/O:
--     DC1394:                      NO
--     FFMPEG:                      YES
--       avcodec:                   YES (56.60.100)
--       avformat:                  YES (56.40.101)
--       avutil:                    YES (54.31.100)
--       swscale:                   YES (3.1.101)
--       avresample:                NO
--     GStreamer:                   NO
--     v4l/v4l2:                    YES (linux/videodev2.h)
-- 
--   Parallel framework:            pthreads
-- 
--   Trace:                         YES (with Intel ITT)
-- 
--   Other third-party libraries:
--     Intel IPP:                   2019.0.0 Gold [2019.0.0]
--            at:                   /root/opencv-4.1.0/mybuild/3rdparty/ippicv/ippicv_lnx/icv
--     Intel IPP IW:                sources (2019.0.0)
--               at:                /root/opencv-4.1.0/mybuild/3rdparty/ippicv/ippicv_lnx/iw
--     Lapack:                      NO
--     Eigen:                       NO
--     Custom HAL:                  NO
--     Protobuf:                    build (3.5.1)
-- 
--   OpenCL:                        YES (no extra features)
--     Include path:                /root/opencv-4.1.0/3rdparty/include/opencl/1.2
--     Link libraries:              Dynamic load
-- 
--   Python (for build):            /usr/bin/python2.7
-- 
--   Java:                          
--     ant:                         NO
--     JNI:                         NO
--     Java wrappers:               NO
--     Java tests:                  NO
-- 
--   Install to:                    /usr/local
-- -----------------------------------------------------------------
-- 
-- Configuring done
-- Generating done
-- Build files have been written to: /root/opencv-4.1.0/mybuild
```

### 4 . 安装

```
$make -j32
$sudo make install
```

### 5.安装python-Opencv

可直接使用apt安装

```
sudo apt-get install python-opencv
sudo apt-get install python-numpy
```

### 6.安装

```
pip install -i https://pypi.tuna.tsinghua.edu.cn/simple opencv-python 
pip install -i https://pypi.tuna.tsinghua.edu.cn/simple opencv-contrib-python
```

### 7.测试

打开python，importcv模块成功即可。

```
import cv2
```