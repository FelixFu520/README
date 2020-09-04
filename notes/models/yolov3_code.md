# Yolov3

2020年9月3日

---

### self.module_defs

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



### self.hyperparams

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



### self.module_list

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

### Self.layers

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



YOLOLayer(
  (mse_loss): MSELoss()
  (bce_loss): BCELoss()
)