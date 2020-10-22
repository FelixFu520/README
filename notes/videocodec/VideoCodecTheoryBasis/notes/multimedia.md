# 多媒体
**多媒体（Multimedia**是多种媒体的综合，一般包括文本，声音和图像等多种媒体形式。   
  
在计算机系统中，多媒体指组合两种或两种以上媒体的一种人机交互式信息交流和传播媒体。使用的媒体包括文字、图片、照片、声音 、动画和影片，以及程式所提供的互动功能。   
  
多媒体是超媒体（Hypermedia）系统中的一个子集，而超媒体系统是使用超链接（Hyperlink）构成的全球信息系统，全球信息系统是因特网上使用TCP/IP 协议和UDP/IP 协议的应用系统。二维的多媒体网页使用HTML、XML等语言编写，三维的多媒体网页使用VRML等语言编写。许多多媒体作品使用光盘发行，以后将更多地使用网络发行。  
  
## 一、视频格式
视频格式可以分为适合本地播放的**本地影像视频**和适合在网络中播放的网络**流媒体影像视频**两大类。    

原始的视频数据可以理解为通过摄像头等驱动获取的没有经过编码的数据，市面上usb摄像头输出的格式常见的有：**RGB24**、**YUV2**、**YV2**，MJPEG（经过编码的数据）。   
   
### 1.常见格式
* [MPEG-图像运动专家组（Motion Picture Experts Group）](https://baike.baidu.com/item/MPEG)   
* [AVI-音频视频交错（Audio Video Interleaved）](https://baike.baidu.com/item/AVI/213655)   
* [MOV](https://baike.baidu.com/item/MOV)
* [ASF-高级流格式（Advanced Streaming format)](https://baike.baidu.com/item/ASF/3918)  
* [WMV](https://baike.baidu.com/item/WMV)
* [NAVI](https://baike.baidu.com/item/nAVI/838785)
* [3GP](https://baike.baidu.com/item/3gp)
* [Real Video](https://baike.baidu.com/item/REAL%20VIDEO)
* [MKV](https://baike.baidu.com/item/mkv)
* [FLV](https://baike.baidu.com/item/flv)
* [F4V](https://baike.baidu.com/item/F4V)
* [RMVB](https://baike.baidu.com/item/rmvb)
* [WebM](https://baike.baidu.com/item/WebM)
## 二.音频格式
### 1.常见格式
* [CD](https://baike.baidu.com/item/cd/3663?fr=aladdin)
* [WAVE](https://baike.baidu.com/item/WAVE/13872619)
* [AIFF](https://baike.baidu.com/item/AIFF)
* [AU](https://baike.baidu.com/item/Adobe%20Audition/6782463?fromtitle=AU&fromid=17105768)
* [MP3](https://baike.baidu.com/item/mp3/9858706)
* [MPEG-4](https://baike.baidu.com/item/MPEG-4)
* [MIDI](https://baike.baidu.com/item/MIMD)
* [WMA](https://baike.baidu.com/item/WMA/2175065)
* [RealAudio](https://baike.baidu.com/item/RealAudio)
* [VQF](https://baike.baidu.com/item/VQF)
* [OggVorbis](https://baike.baidu.com/item/Ogg%20Vorbis)
* [AMR-Adaptive Multi-Rate](https://baike.baidu.com/item/Adaptive%20Multi%20Rate)
### 2.比较
作为数字音乐文件格式的标准，WAV格式容量过大，因而使用起来不方便。因此，一般情况下，我们把它压缩为MP3或WMA格式。
## 三.字幕格式
* 外挂字幕：视频文件和字幕文件分离。
* 内嵌字幕：视频文件和字幕文件集成到一起。  
  
### 1.外挂字幕的格式
* srt格式：这是最好的，体积小，用记事本可以打开编辑。
* sub+idx：这种事图形字幕，只能用字幕转换软件；体积较大。
* ass字幕：网上比较少，比srt多一些特效。  
## 四、采集录制和播放渲染
### 1.视频采集
视频采集（Video Capture）把模拟视频转换成数字视频，并按数字视频文件的格式保存下来。所谓视频采集就是将模拟摄像头、录像机、LD视盘机、电视机输出的视频信号，通过专用的模拟、数字转换设备，转换为二进制数字信息的过程。   
  
在视频采集工作中，**视频采集卡**是主要设备，它分为**专业**和**家用**两个级别。专业视频采集卡不仅可以进行视频采集，并且还可以实现硬件级的视频压缩和视频编辑。   家庭级的视频采集卡只能做到视频采集和初步硬件压缩，而更低端的电视卡，虽可以进行视频采集，但他通常都省却了硬件级的视频压缩功能。  
### 2. 视频渲染
Shade（着色）提供了非常直观，实时的表面基本着色效果，根据硬件的能力，还能显示出纹理贴图、光源影响甚至阴影效果，但这一切都是粗糙的，特别是没有硬件支持的情况下，他的显式甚至会是无理无序的。   
  
Render（渲染）效果就不同了，它是基于一套完整的程序计算出来的，硬件对他的影响只是一个速度问题，而不会改变渲染的结果，影响结果的是看他基于什么程序渲染的，比如是光线追踪还是光能追踪。   
## 五、编解码器
编解码器（codec）指的是一个能够对一个信号或者一个数据流进行变换的设备或者程序。   
## 六、容器
音视频编码及文件格式（容器）是个很庞大的知识领域。  首先要分清媒体文件和编码的区别：文件是即包括视频又包括音频、甚至还带有脚本的一个集合，也可以叫做容器； 文件当中的视频和音频的压缩算法才是具体的编码。   
  
### 1.常见音视频编码分类
* MPEG
* H.26x系列
* 微软的windows media系列
* Real Media系列
* QuickTime系列
### 2.DTS文件格式（容器）
* AVI
* MPEG
* MPG
* VOB
* MP4
* 3GP
* ASF
* RM
* MOV
* MKV
* WAV
* MP3
## 七、协议
### 1.视频协议
目前主要的视频压缩协议有：H.261,H.263,H.264和MPEG-1，MPEG-2，MPEG-4.  
   
从应用角度来说，MPEG系列在消费类应用更广些，比如VCD是MPEG-1，DVD是MPEG-2。而H.x系列常用到**视频会议**。  
  
从技术角度来说，H系列的协议对网络的支持更好些，这点MPEG系列要差些，但是MPEG每一代都比H系列的协议晚些，算法也更先进些，因此，它用来做存储协议是合适的。   
### 2.音频协议
音频协议也分为两大类：ITU组织的主要是用于视频会议的g系列协议，包括g.711,g.722,g.723,g.726,g.728,g.729等。这些协议的特点：第一对人讲话压缩的比较好，对音乐比较差。第二压缩率大，码率低。    
ISO更为人熟知，比如mp3.    
### 3.上层通讯协议
在视频会议系统中，目前流行的有**h.323和sip协议**，在流媒体应用中，**isma， rtsp**应用的比较多。   
## 八、常用概念介绍
