## 1. Darknet网络结构

```python
im = np.random.randn(1, 3, 224, 224)
im = torch.from_numpy(im).float()
model = Darknet19()
out = model(im)
print(out.size())
print(model)
```

```shell
torch.Size([1, 1000])
Darknet19(
  (layer0): Sequential(
    (0): Conv2d(3, 32, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (1): BatchNorm2d(32, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (2): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (layer1): Sequential(
    (0): MaxPool2d(kernel_size=2, stride=2, padding=0, dilation=1, ceil_mode=False)
    (1): Conv2d(32, 64, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (2): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (3): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (layer2): Sequential(
    (0): MaxPool2d(kernel_size=2, stride=2, padding=0, dilation=1, ceil_mode=False)
    (1): Conv2d(64, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (2): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (3): LeakyReLU(negative_slope=0.1, inplace=True)
    (4): Conv2d(128, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (5): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (6): LeakyReLU(negative_slope=0.1, inplace=True)
    (7): Conv2d(64, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (8): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (9): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (layer3): Sequential(
    (0): MaxPool2d(kernel_size=2, stride=2, padding=0, dilation=1, ceil_mode=False)
    (1): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (2): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (3): LeakyReLU(negative_slope=0.1, inplace=True)
    (4): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (5): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (6): LeakyReLU(negative_slope=0.1, inplace=True)
    (7): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (8): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (9): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (layer4): Sequential(
    (0): MaxPool2d(kernel_size=2, stride=2, padding=0, dilation=1, ceil_mode=False)
    (1): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (2): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (3): LeakyReLU(negative_slope=0.1, inplace=True)
    (4): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (5): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (6): LeakyReLU(negative_slope=0.1, inplace=True)
    (7): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (8): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (9): LeakyReLU(negative_slope=0.1, inplace=True)
    (10): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (11): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (12): LeakyReLU(negative_slope=0.1, inplace=True)
    (13): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (14): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (15): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (layer5): Sequential(
    (0): MaxPool2d(kernel_size=2, stride=2, padding=0, dilation=1, ceil_mode=False)
    (1): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (2): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (3): LeakyReLU(negative_slope=0.1, inplace=True)
    (4): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (5): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (6): LeakyReLU(negative_slope=0.1, inplace=True)
    (7): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (8): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (9): LeakyReLU(negative_slope=0.1, inplace=True)
    (10): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (11): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (12): LeakyReLU(negative_slope=0.1, inplace=True)
    (13): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (14): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (15): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (conv): Conv2d(1024, 1000, kernel_size=(1, 1), stride=(1, 1))
  (avgpool): GlobalAvgPool2d()
  (softmax): Softmax(dim=1)
)
```



```python
from torchsummary import summary
net = Darknet19().cuda()
summary(net, (3, 418, 418))
```

```
----------------------------------------------------------------
        Layer (type)               Output Shape         Param #
================================================================
            Conv2d-1         [-1, 32, 418, 418]             864
       BatchNorm2d-2         [-1, 32, 418, 418]              64
         LeakyReLU-3         [-1, 32, 418, 418]               0
         MaxPool2d-4         [-1, 32, 209, 209]               0
            Conv2d-5         [-1, 64, 209, 209]          18,432
       BatchNorm2d-6         [-1, 64, 209, 209]             128
         LeakyReLU-7         [-1, 64, 209, 209]               0
         MaxPool2d-8         [-1, 64, 104, 104]               0
            Conv2d-9        [-1, 128, 104, 104]          73,728
      BatchNorm2d-10        [-1, 128, 104, 104]             256
        LeakyReLU-11        [-1, 128, 104, 104]               0
           Conv2d-12         [-1, 64, 104, 104]           8,192
      BatchNorm2d-13         [-1, 64, 104, 104]             128
        LeakyReLU-14         [-1, 64, 104, 104]               0
           Conv2d-15        [-1, 128, 104, 104]          73,728
      BatchNorm2d-16        [-1, 128, 104, 104]             256
        LeakyReLU-17        [-1, 128, 104, 104]               0
        MaxPool2d-18          [-1, 128, 52, 52]               0
           Conv2d-19          [-1, 256, 52, 52]         294,912
      BatchNorm2d-20          [-1, 256, 52, 52]             512
        LeakyReLU-21          [-1, 256, 52, 52]               0
           Conv2d-22          [-1, 128, 52, 52]          32,768
      BatchNorm2d-23          [-1, 128, 52, 52]             256
        LeakyReLU-24          [-1, 128, 52, 52]               0
           Conv2d-25          [-1, 256, 52, 52]         294,912
      BatchNorm2d-26          [-1, 256, 52, 52]             512
        LeakyReLU-27          [-1, 256, 52, 52]               0
        MaxPool2d-28          [-1, 256, 26, 26]               0
           Conv2d-29          [-1, 512, 26, 26]       1,179,648
      BatchNorm2d-30          [-1, 512, 26, 26]           1,024
        LeakyReLU-31          [-1, 512, 26, 26]               0
           Conv2d-32          [-1, 256, 26, 26]         131,072
      BatchNorm2d-33          [-1, 256, 26, 26]             512
        LeakyReLU-34          [-1, 256, 26, 26]               0
           Conv2d-35          [-1, 512, 26, 26]       1,179,648
      BatchNorm2d-36          [-1, 512, 26, 26]           1,024
        LeakyReLU-37          [-1, 512, 26, 26]               0
           Conv2d-38          [-1, 256, 26, 26]         131,072
      BatchNorm2d-39          [-1, 256, 26, 26]             512
        LeakyReLU-40          [-1, 256, 26, 26]               0
           Conv2d-41          [-1, 512, 26, 26]       1,179,648
      BatchNorm2d-42          [-1, 512, 26, 26]           1,024
        LeakyReLU-43          [-1, 512, 26, 26]               0
        MaxPool2d-44          [-1, 512, 13, 13]               0
           Conv2d-45         [-1, 1024, 13, 13]       4,718,592
      BatchNorm2d-46         [-1, 1024, 13, 13]           2,048
        LeakyReLU-47         [-1, 1024, 13, 13]               0
           Conv2d-48          [-1, 512, 13, 13]         524,288
      BatchNorm2d-49          [-1, 512, 13, 13]           1,024
        LeakyReLU-50          [-1, 512, 13, 13]               0
           Conv2d-51         [-1, 1024, 13, 13]       4,718,592
      BatchNorm2d-52         [-1, 1024, 13, 13]           2,048
        LeakyReLU-53         [-1, 1024, 13, 13]               0
           Conv2d-54          [-1, 512, 13, 13]         524,288
      BatchNorm2d-55          [-1, 512, 13, 13]           1,024
        LeakyReLU-56          [-1, 512, 13, 13]               0
           Conv2d-57         [-1, 1024, 13, 13]       4,718,592
      BatchNorm2d-58         [-1, 1024, 13, 13]           2,048
        LeakyReLU-59         [-1, 1024, 13, 13]               0
           Conv2d-60         [-1, 1000, 13, 13]       1,025,000
  GlobalAvgPool2d-61                 [-1, 1000]               0
          Softmax-62                 [-1, 1000]               0
================================================================
Total params: 20,842,376
Trainable params: 20,842,376
Non-trainable params: 0
----------------------------------------------------------------
Input size (MB): 2.00
Forward/backward pass size (MB): 380.19
Params size (MB): 79.51
Estimated Total Size (MB): 461.70
----------------------------------------------------------------
```

## 2. yolov2

```python
model = Yolov2()
im = np.random.randn(1, 3, 416, 416)
im = torch.from_numpy(im).float()
out = model(im)
print(model)
delta_pred, conf_pred, class_pred = out
print('delta_pred size:', delta_pred.size())
print('conf_pred size:', conf_pred.size())
print('class_pred size:', class_pred.size())
```

```python
 
Yolov2(
  (conv1): Sequential(
    (0): Sequential(
      (0): Conv2d(3, 32, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (1): BatchNorm2d(32, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (2): LeakyReLU(negative_slope=0.1, inplace=True)
    )
    (1): Sequential(
      (0): MaxPool2d(kernel_size=2, stride=2, padding=0, dilation=1, ceil_mode=False)
      (1): Conv2d(32, 64, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (2): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (3): LeakyReLU(negative_slope=0.1, inplace=True)
    )
    (2): Sequential(
      (0): MaxPool2d(kernel_size=2, stride=2, padding=0, dilation=1, ceil_mode=False)
      (1): Conv2d(64, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (2): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (3): LeakyReLU(negative_slope=0.1, inplace=True)
      (4): Conv2d(128, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
      (5): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (6): LeakyReLU(negative_slope=0.1, inplace=True)
      (7): Conv2d(64, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (8): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (9): LeakyReLU(negative_slope=0.1, inplace=True)
    )
    (3): Sequential(
      (0): MaxPool2d(kernel_size=2, stride=2, padding=0, dilation=1, ceil_mode=False)
      (1): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (2): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (3): LeakyReLU(negative_slope=0.1, inplace=True)
      (4): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
      (5): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (6): LeakyReLU(negative_slope=0.1, inplace=True)
      (7): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (8): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (9): LeakyReLU(negative_slope=0.1, inplace=True)
    )
    (4): Sequential(
      (0): MaxPool2d(kernel_size=2, stride=2, padding=0, dilation=1, ceil_mode=False)
      (1): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (2): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (3): LeakyReLU(negative_slope=0.1, inplace=True)
      (4): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
      (5): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (6): LeakyReLU(negative_slope=0.1, inplace=True)
      (7): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (8): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (9): LeakyReLU(negative_slope=0.1, inplace=True)
      (10): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
      (11): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (12): LeakyReLU(negative_slope=0.1, inplace=True)
      (13): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (14): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (15): LeakyReLU(negative_slope=0.1, inplace=True)
    )
  )
  (conv2): Sequential(
    (0): MaxPool2d(kernel_size=2, stride=2, padding=0, dilation=1, ceil_mode=False)
    (1): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (2): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (3): LeakyReLU(negative_slope=0.1, inplace=True)
    (4): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (5): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (6): LeakyReLU(negative_slope=0.1, inplace=True)
    (7): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (8): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (9): LeakyReLU(negative_slope=0.1, inplace=True)
    (10): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (11): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (12): LeakyReLU(negative_slope=0.1, inplace=True)
    (13): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (14): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (15): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (conv3): Sequential(
    (0): Sequential(
      (0): Conv2d(1024, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (1): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (2): LeakyReLU(negative_slope=0.1, inplace=True)
    )
    (1): Sequential(
      (0): Conv2d(1024, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (1): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (2): LeakyReLU(negative_slope=0.1, inplace=True)
    )
  )
  (downsampler): Sequential(
    (0): Conv2d(512, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (1): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (2): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (conv4): Sequential(
    (0): Sequential(
      (0): Conv2d(1280, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (1): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (2): LeakyReLU(negative_slope=0.1, inplace=True)
    )
    (1): Conv2d(1024, 125, kernel_size=(1, 1), stride=(1, 1))
  )
  (reorg): ReorgLayer()
)
delta_pred size: torch.Size([1, 845, 4])
conf_pred size: torch.Size([1, 845, 1])
class_pred size: torch.Size([1, 845, 20])

```



```python
from torchsummary import summary
net = Yolov2().cuda()
summary(net, (3, 418, 418))
```

```
----------------------------------------------------------------
        Layer (type)               Output Shape         Param #
================================================================
            Conv2d-1         [-1, 32, 418, 418]             864
       BatchNorm2d-2         [-1, 32, 418, 418]              64
         LeakyReLU-3         [-1, 32, 418, 418]               0
         MaxPool2d-4         [-1, 32, 209, 209]               0
            Conv2d-5         [-1, 64, 209, 209]          18,432
       BatchNorm2d-6         [-1, 64, 209, 209]             128
         LeakyReLU-7         [-1, 64, 209, 209]               0
         MaxPool2d-8         [-1, 64, 104, 104]               0
            Conv2d-9        [-1, 128, 104, 104]          73,728
      BatchNorm2d-10        [-1, 128, 104, 104]             256
        LeakyReLU-11        [-1, 128, 104, 104]               0
           Conv2d-12         [-1, 64, 104, 104]           8,192
      BatchNorm2d-13         [-1, 64, 104, 104]             128
        LeakyReLU-14         [-1, 64, 104, 104]               0
           Conv2d-15        [-1, 128, 104, 104]          73,728
      BatchNorm2d-16        [-1, 128, 104, 104]             256
        LeakyReLU-17        [-1, 128, 104, 104]               0
        MaxPool2d-18          [-1, 128, 52, 52]               0
           Conv2d-19          [-1, 256, 52, 52]         294,912
      BatchNorm2d-20          [-1, 256, 52, 52]             512
        LeakyReLU-21          [-1, 256, 52, 52]               0
           Conv2d-22          [-1, 128, 52, 52]          32,768
      BatchNorm2d-23          [-1, 128, 52, 52]             256
        LeakyReLU-24          [-1, 128, 52, 52]               0
           Conv2d-25          [-1, 256, 52, 52]         294,912
      BatchNorm2d-26          [-1, 256, 52, 52]             512
        LeakyReLU-27          [-1, 256, 52, 52]               0
        MaxPool2d-28          [-1, 256, 26, 26]               0
           Conv2d-29          [-1, 512, 26, 26]       1,179,648
      BatchNorm2d-30          [-1, 512, 26, 26]           1,024
        LeakyReLU-31          [-1, 512, 26, 26]               0
           Conv2d-32          [-1, 256, 26, 26]         131,072
      BatchNorm2d-33          [-1, 256, 26, 26]             512
        LeakyReLU-34          [-1, 256, 26, 26]               0
           Conv2d-35          [-1, 512, 26, 26]       1,179,648
      BatchNorm2d-36          [-1, 512, 26, 26]           1,024
        LeakyReLU-37          [-1, 512, 26, 26]               0
           Conv2d-38          [-1, 256, 26, 26]         131,072
      BatchNorm2d-39          [-1, 256, 26, 26]             512
        LeakyReLU-40          [-1, 256, 26, 26]               0
           Conv2d-41          [-1, 512, 26, 26]       1,179,648
      BatchNorm2d-42          [-1, 512, 26, 26]           1,024
        LeakyReLU-43          [-1, 512, 26, 26]               0
           Conv2d-44           [-1, 64, 26, 26]          32,768
      BatchNorm2d-45           [-1, 64, 26, 26]             128
        LeakyReLU-46           [-1, 64, 26, 26]               0
       ReorgLayer-47          [-1, 256, 13, 13]               0
        MaxPool2d-48          [-1, 512, 13, 13]               0
           Conv2d-49         [-1, 1024, 13, 13]       4,718,592
      BatchNorm2d-50         [-1, 1024, 13, 13]           2,048
        LeakyReLU-51         [-1, 1024, 13, 13]               0
           Conv2d-52          [-1, 512, 13, 13]         524,288
      BatchNorm2d-53          [-1, 512, 13, 13]           1,024
        LeakyReLU-54          [-1, 512, 13, 13]               0
           Conv2d-55         [-1, 1024, 13, 13]       4,718,592
      BatchNorm2d-56         [-1, 1024, 13, 13]           2,048
        LeakyReLU-57         [-1, 1024, 13, 13]               0
           Conv2d-58          [-1, 512, 13, 13]         524,288
      BatchNorm2d-59          [-1, 512, 13, 13]           1,024
        LeakyReLU-60          [-1, 512, 13, 13]               0
           Conv2d-61         [-1, 1024, 13, 13]       4,718,592
      BatchNorm2d-62         [-1, 1024, 13, 13]           2,048
        LeakyReLU-63         [-1, 1024, 13, 13]               0
           Conv2d-64         [-1, 1024, 13, 13]       9,437,184
      BatchNorm2d-65         [-1, 1024, 13, 13]           2,048
        LeakyReLU-66         [-1, 1024, 13, 13]               0
           Conv2d-67         [-1, 1024, 13, 13]       9,437,184
      BatchNorm2d-68         [-1, 1024, 13, 13]           2,048
        LeakyReLU-69         [-1, 1024, 13, 13]               0
           Conv2d-70         [-1, 1024, 13, 13]      11,796,480
      BatchNorm2d-71         [-1, 1024, 13, 13]           2,048
        LeakyReLU-72         [-1, 1024, 13, 13]               0
           Conv2d-73          [-1, 125, 13, 13]         128,125
================================================================
Total params: 50,655,389
Trainable params: 50,655,389
Non-trainable params: 0
----------------------------------------------------------------
Input size (MB): 2.00
Forward/backward pass size (MB): 392.25
Params size (MB): 193.23
Estimated Total Size (MB): 587.48
----------------------------------------------------------------
```



