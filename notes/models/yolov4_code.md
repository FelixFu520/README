# Yolov4代码解读

2020年10月19日

----

## 1. dataset.py（mosica解读）

### 什么是Mosaic数据增强方法

Yolov4的mosaic数据增强参考了CutMix数据增强方式，理论上具有一定的相似性！
**CutMix数据增强方式利用两张图片进行拼接。**

![在这里插入图片描述](imgs/asdfcxv.png)

但是mosaic利用了四张图片，**根据论文所说其拥有一个巨大的优点是丰富检测物体的背景！且在BN计算的时候一下子会计算四张图片的数据！**
就像下图这样：

![在这里插入图片描述](imgs/rrrrr.png)



### **实现思路**

1、每次读取四张图片。

![在这里插入图片描述](imgs/65654.png)

![在这里插入图片描述](imgs/fgh6.png)

![在这里插入图片描述](imgs/vbvbvbv.png)

![在这里插入图片描述](imgs/sgfasadf.png)

2、分别对四张图片进行翻转、缩放、色域变化等，并且按照四个方向位置摆好。

![在这里插入图片描述](imgs/g1.png)

![在这里插入图片描述](imgs/f2.png)

![在这里插入图片描述](imgs/as1.png)

![在这里插入图片描述](imgs/gdas1.png)

3、进行图片的组合和框的组合

![在这里插入图片描述](imgs/yjdy4.png)

### 代码

以下是根据[pytorch YOLOV4](https://github.com/Tianxiaomo/pytorch-YOLOv4)的代码对Mosaic数据增强进行的整理。

![在这里插入图片描述](imgs/df444.png)

**图1**

部分代码展示：

```python
oh, ow, oc = img.shape    # img为读取的图片数据      
# self.cfg.jitter为cfg文件中的参数，默认给的是0.2                                              
dh, dw, dc = np.array(np.array([oh, ow, oc]) * self.cfg.jitter, dtype=np.int)  
# 首先生成一些随机偏移的坐标，分别代表左右上下                                    
pleft = random.randint(-dw, dw)   
pright = random.randint(-dw, dw)  
ptop = random.randint(-dh, dh)    
pbot = random.randint(-dh, dh) 
# 裁剪部分的长和宽
swidth = ow - pleft - pright
sheight = oh - ptop - pbot     
```

整个Mosaic过程如图一所示，图一展示的是pleft,pright,ptop,pbot都大于0时的情况，首先在原图上找到以(pleft,pright)为左上角，swidth，sheight为宽和长的矩形，然后取这个矩形和原图的交集(也就是深绿色的部分)。

注意：图1中(2)这里不是直接取的交集出来，而是先创建一个宽为swidth，长为sheight的矩形，再将矩形赋值为原图RGB三个通道的均值，然后再将上面说的交集部分根据计算的坐标放在这个矩形上面，只不过图一是基于pleft,pright,ptop,pbot都大于0时的情况，所以正好放在(0, 0)坐标上。具体可以参考一以下代码。

```python
# new_src_rect也就是上面说的交集的坐标(x1, y1, x2, y2)
 new_src_rect = rect_intersection(src_rect, img_rect)                                                                                                                        
 dst_rect = [max(0, -pleft), max(0, -ptop), max(0, -pleft) + new_src_rect[2] - new_src_rect[0], 
             max(0, -ptop) + new_src_rect[3] - new_src_rect[1]]  
                                            
cropped = np.zeros([sheight, swidth, 3])                                   
cropped[:, :, ] = np.mean(img, axis=(0, 1))                                
# 这里就是将交集部分放在矩形上                                                      
cropped[dst_rect[1]:dst_rect[3], dst_rect[0]:dst_rect[2]] = \              
    img[new_src_rect[1]:new_src_rect[3], new_src_rect[0]:new_src_rect[2]]  

```

然后对图片进行resize，resize为网络输入所需要的分辨率，默认情况下就是608x608大小。然后根据计算的左上坐标，以及随机得到的宽CutX，长Cuty，裁剪一部分区域作为一张新图的左上部分。图1中(4)红框表示裁剪的区域，注意：图1中(4)左上角的(0, 0)坐标是因为pleft,pright大于0，根据计算所得。计算裁剪坐标的过程可参照以下代码。

```python
# 根据网络的输入大小随机计算的cut_x、cut_y，min_offset为预设参数，默认为0.2
# cfg.w，cfg.h为网络的输入大小，默认为608
 cut_x = random.randint(int(self.cfg.w * min_offset), int(self.cfg.w * (1 - min_offset)))
 cut_y = random.randint(int(self.cfg.h * min_offset), int(self.cfg.h * (1 - min_offset)))
# 裁剪坐标的计算过程                                                                                 
left_shift = int(min(cut_x, max(0, (-int(pleft) * self.cfg.w / swidth))))                         
top_shift = int(min(cut_y, max(0, (-int(ptop) * self.cfg.h / sheight))))                          
                                                                                                  
right_shift = int(min((self.cfg.w - cut_x), max(0, (-int(pright) * self.cfg.w / swidth))))        
bot_shift = int(min(self.cfg.h - cut_y, max(0, (-int(pbot) * self.cfg.h / sheight))))               
# 这里的ai参数为图一中的(3), out_img初始化的新图
# 该函数的功能就是图1中(3)到(5)的过程，分别将裁剪的图片粘贴到新图的左上，右上，左下，右下
# 循环4次，每循环一次粘贴一次，每次根据给的参数i粘贴到哪个部分                                       
out_img, out_bbox = blend_truth_mosaic(out_img, ai, truth.copy(), self.cfg.w, self.cfg.h, cut_x,  
                                       cut_y, i, left_shift, right_shift, top_shift, bot_shift)   
```

以下是blend_truth_mosaic函数细节：

```python
def blend_truth_mosaic(out_img, img, bboxes, w, h, cut_x, cut_y, i_mixup,                                        
                       left_shift, right_shift, top_shift, bot_shift):                                           
    left_shift = min(left_shift, w - cut_x)                                                                      
    top_shift = min(top_shift, h - cut_y)                                                                        
    right_shift = min(right_shift, cut_x)                                                                        
    bot_shift = min(bot_shift, cut_y)                                                                            
                                                                                                                 
    if i_mixup == 0:                                                                                             
        bboxes = filter_truth(bboxes, left_shift, top_shift, cut_x, cut_y, 0, 0)                                 
        out_img[:cut_y, :cut_x] = img[top_shift:top_shift + cut_y, left_shift:left_shift + cut_x]                
    if i_mixup == 1:                                                                                             
        bboxes = filter_truth(bboxes, cut_x - right_shift, top_shift, w - cut_x, cut_y, cut_x, 0)                
        out_img[:cut_y, cut_x:] = img[top_shift:top_shift + cut_y, cut_x - right_shift:w - right_shift]          
    if i_mixup == 2:                                                                                             
        bboxes = filter_truth(bboxes, left_shift, cut_y - bot_shift, cut_x, h - cut_y, 0, cut_y)                 
        out_img[cut_y:, :cut_x] = img[cut_y - bot_shift:h - bot_shift, left_shift:left_shift + cut_x]            
    if i_mixup == 3:                                                                                             
        bboxes = filter_truth(bboxes, cut_x - right_shift, cut_y - bot_shift, w - cut_x, h - cut_y, cut_x, cut_y)
        out_img[cut_y:, cut_x:] = img[cut_y - bot_shift:h - bot_shift, cut_x - right_shift:w - right_shift]      
                                                                                                                 
    return out_img, bboxes                                                                                       

```

最后说明一下对于标签框的处理，图1中可以看到，当进行裁剪的时候，如果裁剪了样本当中的标签框的部分区域，则将其舍弃，保留裁剪之后还完整的标签框。

下图为pleft,pright,ptop,pbot都小于0的裁剪情况：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200527193239600.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1ExdTFORw==,size_16,color_FFFFFF,t_70#pic_center)

**图2**

由于时间关系，我只画了比较容易画的两种情况图，也只做了粘贴左上角的部分，但其实也都是一个道理。
本文只做了Mosaic的裁剪部分详解，当然个人觉得比较关键的也是这个部分，其实当中还有一些其他增强操作，例如随机翻转，模糊，HSV增强等等，这个暂时还没有做，后续会进行更新。
最后，这是我根据[pytorch YOLOV4](https://github.com/Tianxiaomo/pytorch-YOLOv4)的代码，自己的理解，如果有错，欢迎指正，谢谢。

### 参考

> https://blog.csdn.net/weixin_44791964/article/details/105996954
>
> https://blog.csdn.net/Q1u1NG/article/details/106388904
>
> 