# Yolov3

2020年9月3日

---

## 1 DataLoader

调试ListDataset类。



本案例，dataloader的类型是，

#### Images：

1、读取数据

2、填充像素

```
# Pad to square resolution，（填充像素）
img, pad = pad_to_square(img, 0)
```



#### Labels：

1、因为填充图像的像素了，所以需要修改labels

2、**target的格式为（属于第几张图片batchsize，类别cls，中心点cx（0～1，相对于整张图），中心点cy（0～1，相对于整张图），图像的宽w（0～1），图像的高h（0～1））**



## 2 Models

### 2.1  self.module_defs

```shell
<class 'list'>: [
{'type': 'net', 'batch': '48', 'subdivisions': '1', 'width': '416', 'height': '416', 'channels': '3', 'momentum': '0.9', 'decay': '0.0005', 'angle': '0', 'saturation': '1.5', 'exposure': '1.5', 'hue': '.1', 'learning_rate': '0.001', 'burn_in': '1000', 'max_batches': '500200', 'policy': 'steps', 'steps': '400000,450000', 'scales': '.1,.1'}, 

{'type': 'convolutional', 'batch_normalize': '1', 'filters': '32', 'size': '3', 'stride': '1', 'pad': '1', 'activation': 'leaky'}, 

{'type': 'convolutional', 'batch_normalize': '1', 'filters': '64', 'size': '3', 'stride': '2', 'pad': '1', 'activation': 'leaky'}, 

{'type': 'convolutional', 'batch_normalize': '1', 'filters': '32', 'size': '1', 'stride': '1', 'pad': '1', 'activation': 'leaky'}, 

{'type': 'convolutional', 'batch_normalize': '1', 'filters': '64', 'size': '3', 'stride': '1', 'pad': '1', 'activation': 'leaky'}, 

{'type': 'shortcut', 'from': '-3', 'activation': 'linear'}, 

{'type': 'convolutional', 'batch_normalize': '1', 'filters': '128', 'size': '3', 'stride': '2', 'pad': '1', 'activation': 'leaky'},

{'type': 'convolutional', 'batch_normalize': '1', 'filters': '64', 'size': '1', 'stride': '1', 'pad': '1', 'activation': 'leaky'},

{'type': 'convolutional', 'batch_normalize': '1', 'filters': '128', 'size': '3', 'stride': '1', 'pad': '1', 'activation': 'leaky'}, 

{'type': 'shortcut', 'from': '-3', 'activation': 'linear'}, 

{'type': 'convolutional', 'batch_normalize': '1', 'filters': '64', 'size': '1', 'stride': '1', 'pad': '1', 'activation': 'leaky'}, 

{'type': 'convolutional', 'batch_normalize': '1', 'filters': '128', 'size': '3', 'stride': '1', 'pad': '1', 'activation': 'leaky'}, 

{'type': 'shortcut', 'from': '-3', 'activation': 'linear'}, 

{'type': 'convolutional', 'batch_normalize': '1', 'filters': '256', 'size': '3', 'stride': '2', 'pad': '1', 'activation': 'leaky'},

{'type': 'convolutional', 'batch_normalize': '1', 'filters': '128', 'size': '1', 'stride': '1', 'pad': '1', 'activation': 'leaky'}, 

{'type': 'convolutional', 'batch_normalize': '1', 'filters': '256', 'size': '3', 'stride': '1', 'pad': '1', 'activation': 'leaky'}, 

{'type': 'shortcut', 'from': '-3', 'activation': 'linear'}, 

{'type': 'convolutional', 'batch_normalize': '1', 'filters': '128', 'size': '1', 'stride': '1', 'pad': '1', 'activation': 'leaky'}, 

{'type': 'convolutional', 'batch_normalize': '1', 'filters': '256', 'size': '3', 'stride': '1', 'pad': '1', 'activation': 'leaky'}, 

{'type': 'shortcut', 'from': '-3', 'activation': 'linear'}, 

{'type': 'convolutional', 'batch_normalize': '1', 'filters': '128', 'size': '1', 'stride': '1', 'pad': '1', 'activation': 'leaky'}, 

{'type': 'convolutional', 'batch_normalize': '1', 'filters': '256', 'size': '3', 'stride': '1', 'pad': '1', 'activation': 'leaky'},

{'type': 'shortcut', 'from': '-3', 'activation': 'linear'}, 

{'type': 'convolutional', 'batch_normalize': '1', 'filters': '128', 'size': '1', 'stride': '1', 'pad': '1', 'activation': 'leaky'}, 

...
```

### 2.2 output_filters

```
<class 'list'>: [3, 32, 64, 32, 64, 64, 128, 64, 128, 128, 64, 128, 128, 256, 128, 256, 256, 128, 256, 256, 128, 256, 256, 128, 256, 256, 128, 256, 256, 128, 256, 256, 128, 256, 256, 128, 256, 256, 512, 256, 512, 512, 256, 512, 512, 256, 512, 512, 256, 512, 512, 256, 512, 512, 256, 512, 512, 256, 512, 512, 256, 512, 512, 1024, 512, 1024, 1024, 512, 1024, 1024, 512, 1024, 1024, 512, 1024, 1024, 512, 1024, 512, 1024, 512, 1024, 255, 255, 512, 256, 256, 768, 256, 512, 256, 512, 256, 512, 255, 255, 256, 128, 128, 384, 128, 256, 128, 256, 128, 256, 255, 255]
```

### 2.3 self.hyperparams

```
<class 'dict'>: 
{
'type': 'net', 
'batch': '48', 
'subdivisions': '1', 
'width': '416', 
'height': '416', 
'channels': '3', 
'momentum': '0.9', 
'decay': '0.0005', 
'angle': '0', 
'saturation': '1.5', 
'exposure': '1.5', 
'hue': '.1', 
'learning_rate': '0.001',
'burn_in': '1000', 
'max_batches': '500200', 
'policy': 'steps', 
'steps': '400000,450000', 
'scales': '.1,.1'
}
```

### 2.4 self.module_list

```
ModuleList(
  (0): Sequential(
    (conv_0): Conv2d(3, 32, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_0): BatchNorm2d(32, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_0): LeakyReLU(negative_slope=0.1)
  )
  (1): Sequential(
    (conv_1): Conv2d(32, 64, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1), bias=False)
    (batch_norm_1): BatchNorm2d(64, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_1): LeakyReLU(negative_slope=0.1)
  )
  (2): Sequential(
    (conv_2): Conv2d(64, 32, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_2): BatchNorm2d(32, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_2): LeakyReLU(negative_slope=0.1)
  )
  (3): Sequential(
    (conv_3): Conv2d(32, 64, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_3): BatchNorm2d(64, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_3): LeakyReLU(negative_slope=0.1)
  )
  (4): Sequential(
    (shortcut_4): EmptyLayer()
  )
  (5): Sequential(
    (conv_5): Conv2d(64, 128, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1), bias=False)
    (batch_norm_5): BatchNorm2d(128, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_5): LeakyReLU(negative_slope=0.1)
  )
  (6): Sequential(
    (conv_6): Conv2d(128, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_6): BatchNorm2d(64, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_6): LeakyReLU(negative_slope=0.1)
  )
  (7): Sequential(
    (conv_7): Conv2d(64, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_7): BatchNorm2d(128, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_7): LeakyReLU(negative_slope=0.1)
  )
  (8): Sequential(
    (shortcut_8): EmptyLayer()
  )
  (9): Sequential(
    (conv_9): Conv2d(128, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_9): BatchNorm2d(64, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_9): LeakyReLU(negative_slope=0.1)
  )
  (10): Sequential(
    (conv_10): Conv2d(64, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_10): BatchNorm2d(128, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_10): LeakyReLU(negative_slope=0.1)
  )
  (11): Sequential(
    (shortcut_11): EmptyLayer()
  )
  (12): Sequential(
    (conv_12): Conv2d(128, 256, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1), bias=False)
    (batch_norm_12): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_12): LeakyReLU(negative_slope=0.1)
  )
  (13): Sequential(
    (conv_13): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_13): BatchNorm2d(128, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_13): LeakyReLU(negative_slope=0.1)
  )
  (14): Sequential(
    (conv_14): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_14): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_14): LeakyReLU(negative_slope=0.1)
  )
  (15): Sequential(
    (shortcut_15): EmptyLayer()
  )
  (16): Sequential(
    (conv_16): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_16): BatchNorm2d(128, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_16): LeakyReLU(negative_slope=0.1)
  )
  (17): Sequential(
    (conv_17): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_17): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_17): LeakyReLU(negative_slope=0.1)
  )
  (18): Sequential(
    (shortcut_18): EmptyLayer()
  )
  (19): Sequential(
    (conv_19): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_19): BatchNorm2d(128, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_19): LeakyReLU(negative_slope=0.1)
  )
  (20): Sequential(
    (conv_20): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_20): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_20): LeakyReLU(negative_slope=0.1)
  )
  (21): Sequential(
    (shortcut_21): EmptyLayer()
  )
  (22): Sequential(
    (conv_22): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_22): BatchNorm2d(128, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_22): LeakyReLU(negative_slope=0.1)
  )
  (23): Sequential(
    (conv_23): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_23): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_23): LeakyReLU(negative_slope=0.1)
  )
  (24): Sequential(
    (shortcut_24): EmptyLayer()
  )
  (25): Sequential(
    (conv_25): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_25): BatchNorm2d(128, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_25): LeakyReLU(negative_slope=0.1)
  )
  (26): Sequential(
    (conv_26): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_26): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_26): LeakyReLU(negative_slope=0.1)
  )
  (27): Sequential(
    (shortcut_27): EmptyLayer()
  )
  (28): Sequential(
    (conv_28): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_28): BatchNorm2d(128, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_28): LeakyReLU(negative_slope=0.1)
  )
  (29): Sequential(
    (conv_29): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_29): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_29): LeakyReLU(negative_slope=0.1)
  )
  (30): Sequential(
    (shortcut_30): EmptyLayer()
  )
  (31): Sequential(
    (conv_31): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_31): BatchNorm2d(128, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_31): LeakyReLU(negative_slope=0.1)
  )
  (32): Sequential(
    (conv_32): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_32): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_32): LeakyReLU(negative_slope=0.1)
  )
  (33): Sequential(
    (shortcut_33): EmptyLayer()
  )
  (34): Sequential(
    (conv_34): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_34): BatchNorm2d(128, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_34): LeakyReLU(negative_slope=0.1)
  )
  (35): Sequential(
    (conv_35): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_35): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_35): LeakyReLU(negative_slope=0.1)
  )
  (36): Sequential(
    (shortcut_36): EmptyLayer()
  )
  (37): Sequential(
    (conv_37): Conv2d(256, 512, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1), bias=False)
    (batch_norm_37): BatchNorm2d(512, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_37): LeakyReLU(negative_slope=0.1)
  )
  (38): Sequential(
    (conv_38): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_38): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_38): LeakyReLU(negative_slope=0.1)
  )
  (39): Sequential(
    (conv_39): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_39): BatchNorm2d(512, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_39): LeakyReLU(negative_slope=0.1)
  )
  (40): Sequential(
    (shortcut_40): EmptyLayer()
  )
  (41): Sequential(
    (conv_41): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_41): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_41): LeakyReLU(negative_slope=0.1)
  )
  (42): Sequential(
    (conv_42): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_42): BatchNorm2d(512, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_42): LeakyReLU(negative_slope=0.1)
  )
  (43): Sequential(
    (shortcut_43): EmptyLayer()
  )
  (44): Sequential(
    (conv_44): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_44): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_44): LeakyReLU(negative_slope=0.1)
  )
  (45): Sequential(
    (conv_45): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_45): BatchNorm2d(512, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_45): LeakyReLU(negative_slope=0.1)
  )
  (46): Sequential(
    (shortcut_46): EmptyLayer()
  )
  (47): Sequential(
    (conv_47): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_47): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_47): LeakyReLU(negative_slope=0.1)
  )
  (48): Sequential(
    (conv_48): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_48): BatchNorm2d(512, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_48): LeakyReLU(negative_slope=0.1)
  )
  (49): Sequential(
    (shortcut_49): EmptyLayer()
  )
  (50): Sequential(
    (conv_50): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_50): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_50): LeakyReLU(negative_slope=0.1)
  )
  (51): Sequential(
    (conv_51): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_51): BatchNorm2d(512, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_51): LeakyReLU(negative_slope=0.1)
  )
  (52): Sequential(
    (shortcut_52): EmptyLayer()
  )
  (53): Sequential(
    (conv_53): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_53): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_53): LeakyReLU(negative_slope=0.1)
  )
  (54): Sequential(
    (conv_54): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_54): BatchNorm2d(512, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_54): LeakyReLU(negative_slope=0.1)
  )
  (55): Sequential(
    (shortcut_55): EmptyLayer()
  )
  (56): Sequential(
    (conv_56): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_56): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_56): LeakyReLU(negative_slope=0.1)
  )
  (57): Sequential(
    (conv_57): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_57): BatchNorm2d(512, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_57): LeakyReLU(negative_slope=0.1)
  )
  (58): Sequential(
    (shortcut_58): EmptyLayer()
  )
  (59): Sequential(
    (conv_59): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_59): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_59): LeakyReLU(negative_slope=0.1)
  )
  (60): Sequential(
    (conv_60): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_60): BatchNorm2d(512, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_60): LeakyReLU(negative_slope=0.1)
  )
  (61): Sequential(
    (shortcut_61): EmptyLayer()
  )
  (62): Sequential(
    (conv_62): Conv2d(512, 1024, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1), bias=False)
    (batch_norm_62): BatchNorm2d(1024, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_62): LeakyReLU(negative_slope=0.1)
  )
  (63): Sequential(
    (conv_63): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_63): BatchNorm2d(512, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_63): LeakyReLU(negative_slope=0.1)
  )
  (64): Sequential(
    (conv_64): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_64): BatchNorm2d(1024, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_64): LeakyReLU(negative_slope=0.1)
  )
  (65): Sequential(
    (shortcut_65): EmptyLayer()
  )
  (66): Sequential(
    (conv_66): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_66): BatchNorm2d(512, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_66): LeakyReLU(negative_slope=0.1)
  )
  (67): Sequential(
    (conv_67): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_67): BatchNorm2d(1024, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_67): LeakyReLU(negative_slope=0.1)
  )
  (68): Sequential(
    (shortcut_68): EmptyLayer()
  )
  (69): Sequential(
    (conv_69): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_69): BatchNorm2d(512, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_69): LeakyReLU(negative_slope=0.1)
  )
  (70): Sequential(
    (conv_70): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_70): BatchNorm2d(1024, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_70): LeakyReLU(negative_slope=0.1)
  )
  (71): Sequential(
    (shortcut_71): EmptyLayer()
  )
  (72): Sequential(
    (conv_72): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_72): BatchNorm2d(512, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_72): LeakyReLU(negative_slope=0.1)
  )
  (73): Sequential(
    (conv_73): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_73): BatchNorm2d(1024, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_73): LeakyReLU(negative_slope=0.1)
  )
  (74): Sequential(
    (shortcut_74): EmptyLayer()
  )
  (75): Sequential(
    (conv_75): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_75): BatchNorm2d(512, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_75): LeakyReLU(negative_slope=0.1)
  )
  (76): Sequential(
    (conv_76): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_76): BatchNorm2d(1024, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_76): LeakyReLU(negative_slope=0.1)
  )
  (77): Sequential(
    (conv_77): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_77): BatchNorm2d(512, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_77): LeakyReLU(negative_slope=0.1)
  )
  (78): Sequential(
    (conv_78): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_78): BatchNorm2d(1024, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_78): LeakyReLU(negative_slope=0.1)
  )
  (79): Sequential(
    (conv_79): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_79): BatchNorm2d(512, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_79): LeakyReLU(negative_slope=0.1)
  )
  (80): Sequential(
    (conv_80): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_80): BatchNorm2d(1024, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_80): LeakyReLU(negative_slope=0.1)
  )
  (81): Sequential(
    (conv_81): Conv2d(1024, 255, kernel_size=(1, 1), stride=(1, 1))
  )
  (82): Sequential(
    (yolo_82): YOLOLayer(
      (mse_loss): MSELoss()
      (bce_loss): BCELoss()
    )
  )
  (83): Sequential(
    (route_83): EmptyLayer()
  )
  (84): Sequential(
    (conv_84): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_84): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_84): LeakyReLU(negative_slope=0.1)
  )
  (85): Sequential(
    (upsample_85): Upsample()
  )
  (86): Sequential(
    (route_86): EmptyLayer()
  )
  (87): Sequential(
    (conv_87): Conv2d(768, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_87): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_87): LeakyReLU(negative_slope=0.1)
  )
  (88): Sequential(
    (conv_88): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_88): BatchNorm2d(512, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_88): LeakyReLU(negative_slope=0.1)
  )
  (89): Sequential(
    (conv_89): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_89): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_89): LeakyReLU(negative_slope=0.1)
  )
  (90): Sequential(
    (conv_90): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_90): BatchNorm2d(512, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_90): LeakyReLU(negative_slope=0.1)
  )
  (91): Sequential(
    (conv_91): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_91): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_91): LeakyReLU(negative_slope=0.1)
  )
  (92): Sequential(
    (conv_92): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_92): BatchNorm2d(512, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_92): LeakyReLU(negative_slope=0.1)
  )
  (93): Sequential(
    (conv_93): Conv2d(512, 255, kernel_size=(1, 1), stride=(1, 1))
  )
  (94): Sequential(
    (yolo_94): YOLOLayer(
      (mse_loss): MSELoss()
      (bce_loss): BCELoss()
    )
  )
  (95): Sequential(
    (route_95): EmptyLayer()
  )
  (96): Sequential(
    (conv_96): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_96): BatchNorm2d(128, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_96): LeakyReLU(negative_slope=0.1)
  )
  (97): Sequential(
    (upsample_97): Upsample()
  )
  (98): Sequential(
    (route_98): EmptyLayer()
  )
  (99): Sequential(
    (conv_99): Conv2d(384, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_99): BatchNorm2d(128, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_99): LeakyReLU(negative_slope=0.1)
  )
  (100): Sequential(
    (conv_100): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_100): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_100): LeakyReLU(negative_slope=0.1)
  )
  (101): Sequential(
    (conv_101): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_101): BatchNorm2d(128, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_101): LeakyReLU(negative_slope=0.1)
  )
  (102): Sequential(
    (conv_102): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_102): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_102): LeakyReLU(negative_slope=0.1)
  )
  (103): Sequential(
    (conv_103): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (batch_norm_103): BatchNorm2d(128, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_103): LeakyReLU(negative_slope=0.1)
  )
  (104): Sequential(
    (conv_104): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (batch_norm_104): BatchNorm2d(256, eps=1e-05, momentum=0.9, affine=True, track_running_stats=True)
    (leaky_104): LeakyReLU(negative_slope=0.1)
  )
  (105): Sequential(
    (conv_105): Conv2d(256, 255, kernel_size=(1, 1), stride=(1, 1))
  )
  (106): Sequential(
    (yolo_106): YOLOLayer(
      (mse_loss): MSELoss()
      (bce_loss): BCELoss()
    )
  )
)
```

### 2.5 forword过程

#### self.layers

```
<class 'list'>: [
YOLOLayer(
  (mse_loss): MSELoss()
  (bce_loss): BCELoss()
), 
YOLOLayer(
  (mse_loss): MSELoss()
  (bce_loss): BCELoss()
), 
YOLOLayer(
  (mse_loss): MSELoss()
  (bce_loss): BCELoss()
)]
```

```
# Define detection layer
yolo_layer = YOLOLayer(anchors, num_classes, img_size)
```

#### 2.5.1 self.grid_x/y

```
grid_x:(1, 1, g, g)
tensor([[[[ 0.,  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9., 10., 11., 12., 13., 14.],
          [ 0.,  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9., 10., 11., 12., 13., 14.],
          [ 0.,  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9., 10., 11., 12., 13., 14.],
          [ 0.,  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9., 10., 11., 12., 13., 14.],
          [ 0.,  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9., 10., 11., 12., 13., 14.],
          [ 0.,  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9., 10., 11., 12., 13., 14.],
          [ 0.,  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9., 10., 11., 12., 13., 14.],
          [ 0.,  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9., 10., 11., 12., 13., 14.],
          [ 0.,  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9., 10., 11., 12., 13., 14.],
          [ 0.,  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9., 10., 11., 12., 13., 14.],
          [ 0.,  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9., 10., 11., 12., 13., 14.],
          [ 0.,  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9., 10., 11., 12., 13., 14.],
          [ 0.,  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9., 10., 11., 12., 13., 14.],
          [ 0.,  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9., 10., 11., 12., 13., 14.],
          [ 0.,  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9., 10., 11., 12., 13., 14.]]]], device='cuda:0')
           
           
grid_y:
tensor([[[[ 0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  0., 0.],
          [ 1.,  1.,  1.,  1.,  1.,  1.,  1.,  1.,  1.,  1.,  1.,  1.,  1.,  1., 1.],
          [ 2.,  2.,  2.,  2.,  2.,  2.,  2.,  2.,  2.,  2.,  2.,  2.,  2.,  2., 2.],
          [ 3.,  3.,  3.,  3.,  3.,  3.,  3.,  3.,  3.,  3.,  3.,  3.,  3.,  3., 3.],
          [ 4.,  4.,  4.,  4.,  4.,  4.,  4.,  4.,  4.,  4.,  4.,  4.,  4.,  4., 4.],
          [ 5.,  5.,  5.,  5.,  5.,  5.,  5.,  5.,  5.,  5.,  5.,  5.,  5.,  5., 5.],
          [ 6.,  6.,  6.,  6.,  6.,  6.,  6.,  6.,  6.,  6.,  6.,  6.,  6.,  6., 6.],
          [ 7.,  7.,  7.,  7.,  7.,  7.,  7.,  7.,  7.,  7.,  7.,  7.,  7.,  7., 7.],
          [ 8.,  8.,  8.,  8.,  8.,  8.,  8.,  8.,  8.,  8.,  8.,  8.,  8.,  8., 8.],
          [ 9.,  9.,  9.,  9.,  9.,  9.,  9.,  9.,  9.,  9.,  9.,  9.,  9.,  9., 9.],
          [10., 10., 10., 10., 10., 10., 10., 10., 10., 10., 10., 10., 10., 10., 10.],
          [11., 11., 11., 11., 11., 11., 11., 11., 11., 11., 11., 11., 11., 11., 11.],
          [12., 12., 12., 12., 12., 12., 12., 12., 12., 12., 12., 12., 12., 12., 12.],
          [13., 13., 13., 13., 13., 13., 13., 13., 13., 13., 13., 13., 13., 13., 13.],
          [14., 14., 14., 14., 14., 14., 14., 14., 14., 14., 14., 14., 14., 14., 14.]]]], device='cuda:0')
```

#### 2.5.2 self.scaled_anchors

size=(3, 2)

```
tensor([[ 3.6250,  2.8125],
        [ 4.8750,  6.1875],
        [11.6562, 10.1875]], device='cuda:0')
```

#### 2.5.3 self.anchor_w

size=((1, 3, 1, 1))

```
tensor([[[[ 3.6250]],

         [[ 4.8750]],

         [[11.6562]]]], device='cuda:0')
```

#### 2.5.4 self.anchor_h

size=((1, 3, 1, 1))

```
tensor([[[[ 2.8125]],

         [[ 6.1875]],

         [[10.1875]]]], device='cuda:0')
```

#### 2.5.5 output

size=(20, 675, 85)

```
tensor([[[2.1460e+01, 2.3032e+01, 1.2535e+02,  ..., 1.9618e-03,
          2.3184e-03, 4.6381e-03],
         [5.2952e+01, 2.6481e+01, 1.0620e+02,  ..., 1.0603e-03,
          1.0682e-03, 2.1743e-03],
         [7.9974e+01, 2.4095e+01, 1.5655e+02,  ..., 2.3346e-03,
          1.0593e-03, 1.4862e-03],
         ...,
         [3.8891e+02, 4.5532e+02, 3.5761e+02,  ..., 1.0648e-04,
          7.0435e-05, 2.4291e-04],
         [4.2064e+02, 4.5335e+02, 1.6050e+02,  ..., 1.1913e-03,
          4.2018e-05, 3.1642e-05],
         [4.4985e+02, 4.5025e+02, 2.8738e+02,  ..., 4.1058e-04,
          3.3185e-04, 2.2158e-04]],

        [[2.0698e+01, 7.8813e+00, 8.8591e+01,  ..., 7.9718e-06,
          1.8815e-05, 4.2511e-06],
         [5.5575e+01, 2.1354e+01, 1.2019e+02,  ..., 6.2613e-06,
          2.0618e-06, 8.9923e-07],
         [7.9002e+01, 2.1285e+01, 1.9770e+02,  ..., 2.9121e-05,
          7.8294e-06, 3.3719e-06],
         ...,
         [3.9804e+02, 4.6229e+02, 3.4875e+02,  ..., 2.1746e-04,
          6.6530e-04, 9.3463e-04],
         [4.2689e+02, 4.5777e+02, 2.1189e+02,  ..., 9.0000e-03,
          1.0367e-03, 9.0484e-04],
         [4.5456e+02, 4.5429e+02, 3.5477e+02,  ..., 8.4231e-03,
          5.5690e-03, 7.4499e-03]],

        [[2.0722e+01, 9.3156e+00, 8.3388e+01,  ..., 9.5133e-04,
          8.3921e-05, 4.1334e-05],
         [5.4958e+01, 2.1757e+01, 1.0401e+02,  ..., 2.6319e-03,
          8.2772e-05, 2.8089e-05],
         [7.1642e+01, 2.0362e+01, 1.3546e+02,  ..., 6.0012e-02,
          1.2329e-03, 6.4532e-04],
         ...,
         [3.9825e+02, 4.6083e+02, 3.2429e+02,  ..., 9.6897e-03,
          4.1966e-03, 4.1784e-03],
         [4.3085e+02, 4.5948e+02, 2.2520e+02,  ..., 2.4895e-02,
          4.3187e-03, 2.6827e-03],
         [4.5845e+02, 4.5646e+02, 3.5999e+02,  ..., 2.7223e-02,
          1.2643e-02, 1.5023e-02]],

        ...,

        [[1.9931e+01, 9.3695e+00, 9.0951e+01,  ..., 2.5294e-05,
          5.8669e-05, 2.8087e-05],
         [5.5059e+01, 2.1469e+01, 1.2721e+02,  ..., 1.7767e-05,
          1.6587e-05, 1.3270e-05],
         [8.4146e+01, 2.4129e+01, 1.9564e+02,  ..., 1.4897e-05,
          3.2402e-05, 5.1902e-05],
         ...,
         [4.0399e+02, 4.6576e+02, 3.3788e+02,  ..., 7.0186e-05,
          5.0409e-04, 1.5017e-03],
         [4.3115e+02, 4.6142e+02, 2.7758e+02,  ..., 8.5354e-03,
          3.8837e-03, 5.3136e-03],
         [4.6128e+02, 4.5743e+02, 3.9993e+02,  ..., 3.7022e-02,
          1.5602e-02, 3.9856e-02]],

        [[1.9610e+01, 8.3864e+00, 8.9714e+01,  ..., 5.6382e-05,
          7.4248e-05, 3.9298e-05],
         [5.6059e+01, 2.1039e+01, 1.2930e+02,  ..., 1.1757e-04,
          7.7300e-06, 3.1359e-06],
         [8.0455e+01, 2.1777e+01, 1.9500e+02,  ..., 2.4211e-04,
          7.8318e-06, 2.7164e-06],
         ...,
         [3.9859e+02, 4.6221e+02, 3.4044e+02,  ..., 7.1256e-03,
          3.1211e-03, 5.6906e-03],
         [4.3208e+02, 4.6189e+02, 3.0909e+02,  ..., 2.6875e-02,
          5.6187e-03, 8.9126e-03],
         [4.6679e+02, 4.6346e+02, 3.6009e+02,  ..., 3.9073e-02,
          7.7188e-03, 1.7209e-02]],

        [[1.9287e+01, 7.8497e+00, 8.8286e+01,  ..., 3.4341e-05,
          5.3954e-05, 1.7133e-05],
         [5.5359e+01, 2.2961e+01, 1.1005e+02,  ..., 1.0431e-05,
          5.3738e-06, 4.6251e-06],
         [8.1544e+01, 2.0545e+01, 1.8979e+02,  ..., 2.7707e-07,
          3.8494e-07, 1.4885e-06],
         ...,
         [4.0548e+02, 4.6200e+02, 3.6747e+02,  ..., 6.3532e-06,
          6.4777e-04, 1.8194e-04],
         [4.2581e+02, 4.5861e+02, 2.5832e+02,  ..., 1.3929e-03,
          2.2758e-03, 7.7876e-04],
         [4.5788e+02, 4.5682e+02, 3.8657e+02,  ..., 1.4299e-02,
          1.4948e-02, 1.9224e-02]]], device='cuda:0', grad_fn=<CatBackward>)
```

## 3 loss

### 3.1 build_targets

```
def build_targets(pred_boxes, pred_cls, target, anchors, ignore_thres):
```

pred_boxes size (20, 3, 15, 15, 4)

pred_cls size(20, 3, 15, 15, 80)

target size(175, 6)

anchors size (3, 2)   tensor([[ 3.6250,  2.8125],  [ 4.8750,  6.1875],   [11.6562, 10.1875]], device='cuda:0')

ignore_thres = 0.5

#### 2.6.1 bbox_wh_iou

```
ious = torch.stack([bbox_wh_iou(anchor, gwh) for anchor in anchors])

anchors：(3, 2)
tensor([[ 3.6250,  2.8125],
        [ 4.8750,  6.1875],
        [11.6562, 10.1875]], device='cuda:0')
        
gwh：（181， 2）
tensor([[ 0.7131,  0.2951],
        [ 1.0264,  1.1280],
        [ 0.6818,  0.3539],
        [ 0.7805,  0.2973],
        ......
        [ 1.5168,  3.4495]], device='cuda:0')

iou:(3, 181)
tensor([[2.5381e-02, 3.0473e-01, 4.1132e-01, 3.2632e-01, 1.6332e-01, 3.4117e-01,
         6.2277e-01, 2.1408e-02, 4.7755e-01, 4.3175e-01, 3.7170e-01, 3.4015e-01,
         3.5455e-01, 1.2074e-01, 3.2031e-01, 1.6461e-02, 1.0316e-02, 7.5603e-01,
         4.6286e-01, 4.7469e-01, 4.9892e-01, 4.3991e-01, 6.4282e-01, 5.0371e-01,
         6.7112e-01, 1.5442e-01, 2.6981e-01, 6.2841e-01, 1.4431e-01, 1.4002e-01,
         3.0308e-01, 4.5482e-02, 1.3309e-01, 7.6277e-01, 1.0175e-01, 2.7622e-03,
         8.2249e-03, 9.2760e-02, 2.9202e-03, 7.2341e-03, 7.6433e-03, 3.0561e-02,
         5.7262e-03, 5.3036e-03, 6.9117e-03, 6.9520e-03, 1.2004e-02, 8.2051e-03,
         1.1748e-01, 2.7313e-02, 5.2325e-02, 7.1019e-03, 2.9924e-02, 1.6867e-02,
         2.1980e-02, 7.4776e-02, 1.0641e-01, 7.9349e-01, 3.3450e-01, 1.7355e-01,
         2.4924e-01, 5.6316e-01, 7.8000e-02, 8.9305e-02, 2.0624e-01, 7.7366e-01,
         6.9545e-01, 5.8117e-01, 1.3986e-01, 2.2296e-01, 5.8385e-01, 5.9485e-01,
         1.2943e-01, 4.4316e-02, 1.0965e-01, 5.8396e-02, 3.0418e-01, 7.6006e-03,
         1.8266e-02, 7.9170e-02, 3.0211e-02, 5.8204e-02, 1.3903e-01, 3.6657e-01,
         5.7045e-01, 3.3840e-01, 3.3559e-01, 8.9066e-02, 1.8347e-01, 1.7933e-03,
         4.2323e-03, 8.6571e-01, 5.0057e-03, 6.3139e-03, 5.6447e-02, 9.8563e-02,
         3.0684e-01, 3.3872e-01, 5.8567e-01, 1.6000e-02, 2.3494e-02, 1.2974e-01,
         5.5831e-02, 6.6027e-03, 8.4965e-02, 7.0051e-02, 1.4516e-01, 1.5478e-03,
         4.5427e-02, 9.6442e-04, 4.6854e-02, 2.2659e-02, 1.3579e-02, 7.8544e-03,
         1.4067e-03, 7.9000e-03, 9.8900e-02, 2.9908e-02, 2.1235e-01, 4.3918e-01,
         3.2422e-01, 1.8093e-02, 4.6920e-02, 2.1204e-02, 3.4620e-02, 2.2767e-02,
         4.5442e-01, 5.5507e-02, 5.7671e-03, 3.5975e-02, 1.6964e-02, 6.0189e-01,
         3.8675e-02, 3.8281e-01, 7.0876e-01, 2.1202e-01, 8.8290e-02, 4.7727e-02,
         1.2608e-02, 7.3101e-02, 1.7172e-02, 1.4319e-02, 2.2293e-01, 2.6781e-01,
         7.1805e-02],
        [8.5788e-03, 1.0300e-01, 1.4544e-01, 3.3034e-01, 4.8319e-01, 1.1531e-01,
         3.4798e-01, 7.2357e-03, 1.6141e-01, 2.4218e-01, 1.4449e-01, 4.0897e-01,
         7.3589e-01, 4.0809e-02, 5.3477e-01, 5.5636e-03, 3.4869e-03, 4.4707e-01,
         4.1792e-01, 1.6044e-01, 1.6863e-01, 1.4869e-01, 2.1727e-01, 1.7025e-01,
         2.2684e-01, 4.5686e-01, 9.1196e-02, 5.3785e-01, 4.8777e-02, 4.1427e-01,
         1.0244e-01, 1.5373e-02, 4.4983e-02, 2.5781e-01, 3.4390e-02, 9.3362e-04,
         2.7800e-03, 3.1352e-02, 9.8700e-04, 2.4451e-03, 2.5834e-03, 1.0330e-02,
         1.9354e-03, 1.7926e-03, 2.3361e-03, 2.3498e-03, 4.0574e-03, 2.7733e-03,
         3.9709e-02, 9.2318e-03, 1.7686e-02, 2.4004e-03, 1.0114e-02, 5.7010e-03,
         7.4290e-03, 2.5274e-02, 3.5965e-02, 4.2596e-01, 2.2977e-01, 5.1347e-01,
         8.4243e-02, 1.9035e-01, 2.6364e-02, 3.0185e-02, 6.9708e-02, 3.8613e-01,
         3.4939e-01, 5.7716e-01, 4.1378e-01, 7.5360e-02, 4.2738e-01, 5.0469e-01,
         4.3746e-02, 1.4979e-02, 3.7061e-02, 1.9738e-02, 1.0281e-01, 2.5690e-03,
         6.1738e-03, 2.6759e-02, 1.0211e-02, 1.9673e-02, 4.6990e-02, 2.4606e-01,
         1.9281e-01, 1.4527e-01, 1.2910e-01, 3.0104e-02, 7.7848e-02, 6.0611e-04,
         1.4305e-03, 3.7840e-01, 1.6919e-03, 2.1341e-03, 1.9079e-02, 3.3314e-02,
         3.9277e-01, 1.1448e-01, 3.6877e-01, 5.4080e-03, 7.9407e-03, 4.3851e-02,
         1.8871e-02, 2.2317e-03, 2.8718e-02, 2.3677e-02, 4.9064e-02, 5.2314e-04,
         1.5354e-02, 3.2597e-04, 1.5837e-02, 7.6586e-03, 4.5897e-03, 2.6548e-03,
         4.7547e-04, 2.6702e-03, 3.3428e-02, 1.0109e-02, 4.2880e-01, 1.4844e-01,
         1.2732e-01, 6.1154e-03, 1.5859e-02, 7.1668e-03, 1.1702e-02, 7.6952e-03,
         3.0500e-01, 1.8761e-02, 1.9492e-03, 1.2159e-02, 5.7339e-03, 3.9181e-01,
         1.3072e-02, 1.8635e-01, 2.3956e-01, 7.1662e-02, 2.9842e-02, 1.6131e-02,
         4.2615e-03, 2.4708e-02, 5.8042e-03, 4.8399e-03, 6.5957e-01, 9.0519e-02,
         2.4270e-02],
        [2.1792e-03, 2.6163e-02, 3.6945e-02, 2.6310e-01, 5.2570e-01, 2.9292e-02,
         8.8394e-02, 1.8380e-03, 4.1001e-02, 6.1518e-02, 3.6702e-02, 2.5241e-01,
         2.4216e-01, 1.0366e-02, 2.6804e-01, 1.4132e-03, 8.8573e-04, 1.1356e-01,
         1.0616e-01, 4.0755e-02, 4.2835e-02, 3.7769e-02, 5.5190e-02, 4.3247e-02,
         5.7620e-02, 5.5601e-01, 2.3165e-02, 1.3662e-01, 1.2390e-02, 6.1316e-01,
         2.6022e-02, 3.9049e-03, 1.1427e-02, 6.5489e-02, 8.7356e-03, 2.3716e-04,
         7.0616e-04, 7.9641e-03, 2.5071e-04, 6.2110e-04, 6.5622e-04, 2.6239e-03,
         4.9163e-04, 4.5535e-04, 5.9341e-04, 5.9688e-04, 1.0307e-03, 7.0446e-04,
         1.0087e-02, 2.3450e-03, 4.4925e-03, 6.0974e-04, 2.5691e-03, 1.4481e-03,
         1.8871e-03, 6.4200e-03, 9.1356e-03, 1.0820e-01, 1.2326e-01, 4.9471e-01,
         2.1399e-02, 4.8351e-02, 6.6968e-03, 7.6675e-03, 1.7707e-02, 9.8084e-02,
         8.8752e-02, 1.4773e-01, 6.1389e-01, 1.9143e-02, 1.4705e-01, 1.2820e-01,
         1.1112e-02, 3.8048e-03, 9.4140e-03, 5.0137e-03, 2.6116e-02, 6.5256e-04,
         1.5683e-03, 6.7973e-03, 2.5938e-03, 4.9972e-03, 1.1936e-02, 1.1753e-01,
         4.8977e-02, 3.6901e-02, 3.2793e-02, 7.6469e-03, 1.9775e-02, 1.5396e-04,
         3.6337e-04, 9.6120e-02, 4.2977e-04, 5.4209e-04, 4.8463e-03, 8.4623e-03,
         1.1633e-01, 2.9081e-02, 9.3673e-02, 1.3737e-03, 2.0171e-03, 1.1139e-02,
         4.7935e-03, 5.6688e-04, 7.2948e-03, 6.0144e-03, 1.2463e-02, 1.3289e-04,
         3.9002e-03, 8.2802e-05, 4.0228e-03, 1.9454e-03, 1.1659e-03, 6.7436e-04,
         1.2078e-04, 6.7827e-04, 8.4912e-03, 2.5678e-03, 4.0432e-01, 3.7707e-02,
         3.2342e-02, 1.5534e-03, 4.0284e-03, 1.8205e-03, 2.9724e-03, 1.9547e-03,
         1.2493e-01, 4.7656e-03, 4.9514e-04, 3.0887e-03, 1.4565e-03, 1.2567e-01,
         3.3205e-03, 4.7335e-02, 6.0851e-02, 1.8203e-02, 7.5803e-03, 4.0977e-03,
         1.0825e-03, 6.2762e-03, 1.4744e-03, 1.2294e-03, 3.8512e-01, 2.2993e-02,
         6.1650e-03]], device='cuda:0')

best_n:size 181
tensor([0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
        0], device='cuda:0')
        
best_ious: size 181
tensor([0.0254, 0.3047, 0.4113, 0.3303, 0.5257, 0.3412, 0.6228, 0.0214, 0.4775,
        0.4318, 0.3717, 0.4090, 0.7359, 0.1207, 0.5348, 0.0165, 0.0103, 0.7560,
        0.4629, 0.4747, 0.4989, 0.4399, 0.6428, 0.5037, 0.6711, 0.5560, 0.2698,
        0.6284, 0.1443, 0.6132, 0.3031, 0.0455, 0.1331, 0.7628, 0.1017, 0.0028,
        0.0082, 0.0928, 0.0029, 0.0072, 0.0076, 0.0306, 0.0057, 0.0053, 0.0069,
        0.0070, 0.0120, 0.0082, 0.1175, 0.0273, 0.0523, 0.0071, 0.0299, 0.0169,
        0.0220, 0.0748, 0.1064, 0.7935, 0.3345, 0.5135, 0.2492, 0.5632, 0.0780,
        0.0893, 0.2062, 0.7737, 0.6954, 0.5812, 0.6139, 0.2230, 0.5838, 0.5949,
        0.1294, 0.0443, 0.1096, 0.0584, 0.3042, 0.0076, 0.0183, 0.0792, 0.0302,
        0.0582, 0.1390, 0.3666, 0.5705, 0.3384, 0.3356, 0.0891, 0.1835, 0.0018,
        0.0042, 0.8657, 0.0050, 0.0063, 0.0564, 0.0986, 0.3928, 0.3387, 0.5857,
        0.0160, 0.0235, 0.1297, 0.0558, 0.0066, 0.0850, 0.0701, 0.1452, 0.0015,
        0.0454, 0.0010, 0.0469, 0.0227, 0.0136, 0.0079, 0.0014, 0.0079, 0.0989,
        0.0299, 0.4288, 0.4392, 0.3242, 0.0181, 0.0469, 0.0212, 0.0346, 0.0228,
        0.4544, 0.0555, 0.0058, 0.0360, 0.0170, 0.6019, 0.0387, 0.3828, 0.7088,
        0.2120, 0.0883, 0.0477, 0.0126, 0.0731, 0.0172, 0.0143, 0.6596, 0.2678,
        0.0718], device='cuda:0')
```



### 2. 网络结构

```
layer     filters    size              input                output

   0 conv     32  3 x 3 / 1   416 x 416 x   3   ->   416 x 416 x  32 0.299 BF
   1 conv     64  3 x 3 / 2   416 x 416 x  32   ->   208 x 208 x  64 1.595 BF
   
   
   # layer1
   2 conv     32  1 x 1 / 1   208 x 208 x  64   ->   208 x 208 x  32 0.177 BF
   3 conv     64  3 x 3 / 1   208 x 208 x  32   ->   208 x 208 x  64 1.595 BF
   4 Shortcut Layer: 1
   
   
   5 conv    128  3 x 3 / 2   208 x 208 x  64   ->   104 x 104 x 128 1.595 BF
   
   
   # layer2
   6 conv     64  1 x 1 / 1   104 x 104 x 128   ->   104 x 104 x  64 0.177 BF
   7 conv    128  3 x 3 / 1   104 x 104 x  64   ->   104 x 104 x 128 1.595 BF
   8 Shortcut Layer: 5
   9 conv     64  1 x 1 / 1   104 x 104 x 128   ->   104 x 104 x  64 0.177 BF
  10 conv    128  3 x 3 / 1   104 x 104 x  64   ->   104 x 104 x 128 1.595 BF
  11 Shortcut Layer: 8
  
  
  12 conv    256  3 x 3 / 2   104 x 104 x 128   ->    52 x  52 x 256 1.595 BF
  
  
  # layer3
  13 conv    128  1 x 1 / 1    52 x  52 x 256   ->    52 x  52 x 128 0.177 BF
  14 conv    256  3 x 3 / 1    52 x  52 x 128   ->    52 x  52 x 256 1.595 BF
  15 Shortcut Layer: 12
  16 conv    128  1 x 1 / 1    52 x  52 x 256   ->    52 x  52 x 128 0.177 BF
  17 conv    256  3 x 3 / 1    52 x  52 x 128   ->    52 x  52 x 256 1.595 BF
  18 Shortcut Layer: 15
  19 conv    128  1 x 1 / 1    52 x  52 x 256   ->    52 x  52 x 128 0.177 BF
  20 conv    256  3 x 3 / 1    52 x  52 x 128   ->    52 x  52 x 256 1.595 BF
  21 Shortcut Layer: 18
  22 conv    128  1 x 1 / 1    52 x  52 x 256   ->    52 x  52 x 128 0.177 BF
  23 conv    256  3 x 3 / 1    52 x  52 x 128   ->    52 x  52 x 256 1.595 BF
  24 Shortcut Layer: 21
  25 conv    128  1 x 1 / 1    52 x  52 x 256   ->    52 x  52 x 128 0.177 BF
  26 conv    256  3 x 3 / 1    52 x  52 x 128   ->    52 x  52 x 256 1.595 BF
  27 Shortcut Layer: 24
  28 conv    128  1 x 1 / 1    52 x  52 x 256   ->    52 x  52 x 128 0.177 BF
  29 conv    256  3 x 3 / 1    52 x  52 x 128   ->    52 x  52 x 256 1.595 BF
  30 Shortcut Layer: 27
  31 conv    128  1 x 1 / 1    52 x  52 x 256   ->    52 x  52 x 128 0.177 BF
  32 conv    256  3 x 3 / 1    52 x  52 x 128   ->    52 x  52 x 256 1.595 BF
  33 Shortcut Layer: 30
  34 conv    128  1 x 1 / 1    52 x  52 x 256   ->    52 x  52 x 128 0.177 BF
  35 conv    256  3 x 3 / 1    52 x  52 x 128   ->    52 x  52 x 256 1.595 BF
  36 Shortcut Layer: 33
  
  
  37 conv    512  3 x 3 / 2    52 x  52 x 256   ->    26 x  26 x 512 1.595 BF
  
  # layer4
  38 conv    256  1 x 1 / 1    26 x  26 x 512   ->    26 x  26 x 256 0.177 BF
  39 conv    512  3 x 3 / 1    26 x  26 x 256   ->    26 x  26 x 512 1.595 BF
  40 Shortcut Layer: 37
  41 conv    256  1 x 1 / 1    26 x  26 x 512   ->    26 x  26 x 256 0.177 BF
  42 conv    512  3 x 3 / 1    26 x  26 x 256   ->    26 x  26 x 512 1.595 BF
  43 Shortcut Layer: 40
  44 conv    256  1 x 1 / 1    26 x  26 x 512   ->    26 x  26 x 256 0.177 BF
  45 conv    512  3 x 3 / 1    26 x  26 x 256   ->    26 x  26 x 512 1.595 BF
  46 Shortcut Layer: 43
  47 conv    256  1 x 1 / 1    26 x  26 x 512   ->    26 x  26 x 256 0.177 BF
  48 conv    512  3 x 3 / 1    26 x  26 x 256   ->    26 x  26 x 512 1.595 BF
  49 Shortcut Layer: 46
  50 conv    256  1 x 1 / 1    26 x  26 x 512   ->    26 x  26 x 256 0.177 BF
  51 conv    512  3 x 3 / 1    26 x  26 x 256   ->    26 x  26 x 512 1.595 BF
  52 Shortcut Layer: 49
  53 conv    256  1 x 1 / 1    26 x  26 x 512   ->    26 x  26 x 256 0.177 BF
  54 conv    512  3 x 3 / 1    26 x  26 x 256   ->    26 x  26 x 512 1.595 BF
  55 Shortcut Layer: 52
  56 conv    256  1 x 1 / 1    26 x  26 x 512   ->    26 x  26 x 256 0.177 BF
  57 conv    512  3 x 3 / 1    26 x  26 x 256   ->    26 x  26 x 512 1.595 BF
  58 Shortcut Layer: 55
  59 conv    256  1 x 1 / 1    26 x  26 x 512   ->    26 x  26 x 256 0.177 BF
  60 conv    512  3 x 3 / 1    26 x  26 x 256   ->    26 x  26 x 512 1.595 BF
  61 Shortcut Layer: 58
  
  
  62 conv   1024  3 x 3 / 2    26 x  26 x 512   ->    13 x  13 x1024 1.595 BF
  
  
  # layer5
  63 conv    512  1 x 1 / 1    13 x  13 x1024   ->    13 x  13 x 512 0.177 BF
  64 conv   1024  3 x 3 / 1    13 x  13 x 512   ->    13 x  13 x1024 1.595 BF
  65 Shortcut Layer: 62
  66 conv    512  1 x 1 / 1    13 x  13 x1024   ->    13 x  13 x 512 0.177 BF
  67 conv   1024  3 x 3 / 1    13 x  13 x 512   ->    13 x  13 x1024 1.595 BF
  68 Shortcut Layer: 65
  69 conv    512  1 x 1 / 1    13 x  13 x1024   ->    13 x  13 x 512 0.177 BF
  70 conv   1024  3 x 3 / 1    13 x  13 x 512   ->    13 x  13 x1024 1.595 BF
  71 Shortcut Layer: 68
  72 conv    512  1 x 1 / 1    13 x  13 x1024   ->    13 x  13 x 512 0.177 BF
  73 conv   1024  3 x 3 / 1    13 x  13 x 512   ->    13 x  13 x1024 1.595 BF
  74 Shortcut Layer: 71
  
  
  # convolutional set
  75 conv    512  1 x 1 / 1    13 x  13 x1024   ->    13 x  13 x 512 0.177 BF
  76 conv   1024  3 x 3 / 1    13 x  13 x 512   ->    13 x  13 x1024 1.595 BF
  77 conv    512  1 x 1 / 1    13 x  13 x1024   ->    13 x  13 x 512 0.177 BF
  78 conv   1024  3 x 3 / 1    13 x  13 x 512   ->    13 x  13 x1024 1.595 BF
  79 conv    512  1 x 1 / 1    13 x  13 x1024   ->    13 x  13 x 512 0.177 BF
  
  
  # predict one
  80 conv   1024  3 x 3 / 1    13 x  13 x 512   ->    13 x  13 x1024 1.595 BF
  81 conv     18  1 x 1 / 1    13 x  13 x1024   ->    13 x  13 x  18 0.006 BF
  82 yolo
  
  
  
  83 route  79
  84 conv    256  1 x 1 / 1    13 x  13 x 512   ->    13 x  13 x 256 0.044 BF
  85 upsample            2x    13 x  13 x 256   ->    26 x  26 x 256
  86 route  85 61
  
  
  # convolutional
  87 conv    256  1 x 1 / 1    26 x  26 x 768   ->    26 x  26 x 256 0.266 BF
  88 conv    512  3 x 3 / 1    26 x  26 x 256   ->    26 x  26 x 512 1.595 BF
  89 conv    256  1 x 1 / 1    26 x  26 x 512   ->    26 x  26 x 256 0.177 BF
  90 conv    512  3 x 3 / 1    26 x  26 x 256   ->    26 x  26 x 512 1.595 BF
  91 conv    256  1 x 1 / 1    26 x  26 x 512   ->    26 x  26 x 256 0.177 BF
  
  
  # predict two
  92 conv    512  3 x 3 / 1    26 x  26 x 256   ->    26 x  26 x 512 1.595 BF
  93 conv     18  1 x 1 / 1    26 x  26 x 512   ->    26 x  26 x  18 0.012 BF
  94 yolo
  
  
  95 route  91
  96 conv    128  1 x 1 / 1    26 x  26 x 256   ->    26 x  26 x 128 0.044 BF
  97 upsample            2x    26 x  26 x 128   ->    52 x  52 x 128
  98 route  97 36
  
  
  # convolutional
  99 conv    128  1 x 1 / 1    52 x  52 x 384   ->    52 x  52 x 128 0.266 BF
 100 conv    256  3 x 3 / 1    52 x  52 x 128   ->    52 x  52 x 256 1.595 BF
 101 conv    128  1 x 1 / 1    52 x  52 x 256   ->    52 x  52 x 128 0.177 BF
 102 conv    256  3 x 3 / 1    52 x  52 x 128   ->    52 x  52 x 256 1.595 BF
 103 conv    128  1 x 1 / 1    52 x  52 x 256   ->    52 x  52 x 128 0.177 BF
 
 
 # predict three
 104 conv    256  3 x 3 / 1    52 x  52 x 128   ->    52 x  52 x 256 1.595 BF
 105 conv     18  1 x 1 / 1    52 x  52 x 256   ->    52 x  52 x  18 0.025 BF
 106 yolo
```



YOLOLayer(
  (mse_loss): MSELoss()
  (bce_loss): BCELoss()
)



