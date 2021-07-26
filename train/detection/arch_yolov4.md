## Yolo v4

![20200705173102480](imgs/20200705173102480.png)

## [**Yolov4_ 的网络结构**](https://github.com/FelixFu520/yolov4_)

```
YoloBody(
  (backbone): CSPDarkNet(
    (conv1): BasicConv(
      (conv): Conv2d(3, 32, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (bn): BatchNorm2d(32, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (activation): Mish()
    )
    (stages): ModuleList(
      (0): Resblock_body(
        (downsample_conv): BasicConv(
          (conv): Conv2d(32, 64, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1), bias=False)
          (bn): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
          (activation): Mish()
        )
        (split_conv0): BasicConv(
          (conv): Conv2d(64, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
          (bn): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
          (activation): Mish()
        )
        (split_conv1): BasicConv(
          (conv): Conv2d(64, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
          (bn): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
          (activation): Mish()
        )
        (blocks_conv): Sequential(
          (0): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(64, 32, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(32, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(32, 64, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (1): BasicConv(
            (conv): Conv2d(64, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
            (bn): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
            (activation): Mish()
          )
        )
        (concat_conv): BasicConv(
          (conv): Conv2d(128, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
          (bn): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
          (activation): Mish()
        )
      )
      (1): Resblock_body(
        (downsample_conv): BasicConv(
          (conv): Conv2d(64, 128, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1), bias=False)
          (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
          (activation): Mish()
        )
        (split_conv0): BasicConv(
          (conv): Conv2d(128, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
          (bn): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
          (activation): Mish()
        )
        (split_conv1): BasicConv(
          (conv): Conv2d(128, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
          (bn): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
          (activation): Mish()
        )
        (blocks_conv): Sequential(
          (0): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(64, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(64, 64, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (1): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(64, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(64, 64, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (2): BasicConv(
            (conv): Conv2d(64, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
            (bn): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
            (activation): Mish()
          )
        )
        (concat_conv): BasicConv(
          (conv): Conv2d(128, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
          (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
          (activation): Mish()
        )
      )
      (2): Resblock_body(
        (downsample_conv): BasicConv(
          (conv): Conv2d(128, 256, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1), bias=False)
          (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
          (activation): Mish()
        )
        (split_conv0): BasicConv(
          (conv): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
          (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
          (activation): Mish()
        )
        (split_conv1): BasicConv(
          (conv): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
          (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
          (activation): Mish()
        )
        (blocks_conv): Sequential(
          (0): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(128, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(128, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (1): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(128, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(128, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (2): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(128, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(128, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (3): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(128, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(128, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (4): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(128, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(128, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (5): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(128, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(128, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (6): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(128, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(128, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (7): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(128, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(128, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (8): BasicConv(
            (conv): Conv2d(128, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
            (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
            (activation): Mish()
          )
        )
        (concat_conv): BasicConv(
          (conv): Conv2d(256, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
          (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
          (activation): Mish()
        )
      )
      (3): Resblock_body(
        (downsample_conv): BasicConv(
          (conv): Conv2d(256, 512, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1), bias=False)
          (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
          (activation): Mish()
        )
        (split_conv0): BasicConv(
          (conv): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
          (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
          (activation): Mish()
        )
        (split_conv1): BasicConv(
          (conv): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
          (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
          (activation): Mish()
        )
        (blocks_conv): Sequential(
          (0): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(256, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(256, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (1): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(256, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(256, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (2): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(256, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(256, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (3): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(256, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(256, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (4): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(256, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(256, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (5): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(256, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(256, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (6): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(256, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(256, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (7): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(256, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(256, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (8): BasicConv(
            (conv): Conv2d(256, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
            (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
            (activation): Mish()
          )
        )
        (concat_conv): BasicConv(
          (conv): Conv2d(512, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
          (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
          (activation): Mish()
        )
      )
      (4): Resblock_body(
        (downsample_conv): BasicConv(
          (conv): Conv2d(512, 1024, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1), bias=False)
          (bn): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
          (activation): Mish()
        )
        (split_conv0): BasicConv(
          (conv): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
          (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
          (activation): Mish()
        )
        (split_conv1): BasicConv(
          (conv): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
          (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
          (activation): Mish()
        )
        (blocks_conv): Sequential(
          (0): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(512, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(512, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (1): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(512, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(512, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (2): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(512, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(512, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (3): Resblock(
            (block): Sequential(
              (0): BasicConv(
                (conv): Conv2d(512, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
                (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
              (1): BasicConv(
                (conv): Conv2d(512, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
                (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
                (activation): Mish()
              )
            )
          )
          (4): BasicConv(
            (conv): Conv2d(512, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
            (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
            (activation): Mish()
          )
        )
        (concat_conv): BasicConv(
          (conv): Conv2d(1024, 1024, kernel_size=(1, 1), stride=(1, 1), bias=False)
          (bn): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
          (activation): Mish()
        )
      )
    )
  )
  (conv1): Sequential(
    (0): Sequential(
      (conv): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
      (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (1): Sequential(
      (conv): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (bn): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (2): Sequential(
      (conv): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
      (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
  )
  (SPP): SpatialPyramidPooling(
    (maxpools): ModuleList(
      (0): MaxPool2d(kernel_size=5, stride=1, padding=2, dilation=1, ceil_mode=False)
      (1): MaxPool2d(kernel_size=9, stride=1, padding=4, dilation=1, ceil_mode=False)
      (2): MaxPool2d(kernel_size=13, stride=1, padding=6, dilation=1, ceil_mode=False)
    )
  )
  (conv2): Sequential(
    (0): Sequential(
      (conv): Conv2d(2048, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
      (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (1): Sequential(
      (conv): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (bn): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (2): Sequential(
      (conv): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
      (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
  )
  (upsample1): Upsample(
    (upsample): Sequential(
      (0): Sequential(
        (conv): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
        (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
        (relu): LeakyReLU(negative_slope=0.1)
      )
      (1): Upsample(scale_factor=2.0, mode=nearest)
    )
  )
  (conv_for_P4): Sequential(
    (conv): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (relu): LeakyReLU(negative_slope=0.1)
  )
  (make_five_conv1): Sequential(
    (0): Sequential(
      (conv): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
      (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (1): Sequential(
      (conv): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (2): Sequential(
      (conv): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
      (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (3): Sequential(
      (conv): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (4): Sequential(
      (conv): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
      (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
  )
  (upsample2): Upsample(
    (upsample): Sequential(
      (0): Sequential(
        (conv): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
        (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
        (relu): LeakyReLU(negative_slope=0.1)
      )
      (1): Upsample(scale_factor=2.0, mode=nearest)
    )
  )
  (conv_for_P3): Sequential(
    (conv): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (relu): LeakyReLU(negative_slope=0.1)
  )
  (make_five_conv2): Sequential(
    (0): Sequential(
      (conv): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
      (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (1): Sequential(
      (conv): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (2): Sequential(
      (conv): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
      (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (3): Sequential(
      (conv): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (4): Sequential(
      (conv): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
      (bn): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
  )
  (yolo_head3): Sequential(
    (0): Sequential(
      (conv): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (1): Conv2d(256, 75, kernel_size=(1, 1), stride=(1, 1))
  )
  (down_sample1): Sequential(
    (conv): Conv2d(128, 256, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1), bias=False)
    (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (relu): LeakyReLU(negative_slope=0.1)
  )
  (make_five_conv3): Sequential(
    (0): Sequential(
      (conv): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
      (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (1): Sequential(
      (conv): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (2): Sequential(
      (conv): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
      (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (3): Sequential(
      (conv): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (4): Sequential(
      (conv): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
      (bn): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
  )
  (yolo_head2): Sequential(
    (0): Sequential(
      (conv): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (1): Conv2d(512, 75, kernel_size=(1, 1), stride=(1, 1))
  )
  (down_sample2): Sequential(
    (conv): Conv2d(256, 512, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1), bias=False)
    (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (relu): LeakyReLU(negative_slope=0.1)
  )
  (make_five_conv4): Sequential(
    (0): Sequential(
      (conv): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
      (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (1): Sequential(
      (conv): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (bn): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (2): Sequential(
      (conv): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
      (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (3): Sequential(
      (conv): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (bn): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (4): Sequential(
      (conv): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
      (bn): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
  )
  (yolo_head1): Sequential(
    (0): Sequential(
      (conv): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
      (bn): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
      (relu): LeakyReLU(negative_slope=0.1)
    )
    (1): Conv2d(1024, 75, kernel_size=(1, 1), stride=(1, 1))
  )
)
```



## [**yolov4的网络结构**](https://github.com/FelixFu520/yolov4)

```
ModuleList(
  (0): Sequential(
    (conv1): Conv2d(3, 32, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn1): BatchNorm2d(32, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish1): Mish()
  )
  (1): Sequential(
    (conv2): Conv2d(32, 64, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1), bias=False)
    (bn2): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish2): Mish()
  )
  (2): Sequential(
    (conv3): Conv2d(64, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn3): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish3): Mish()
  )
  (3): EmptyModule()
  (4): Sequential(
    (conv4): Conv2d(64, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn4): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish4): Mish()
  )
  (5): Sequential(
    (conv5): Conv2d(64, 32, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn5): BatchNorm2d(32, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish5): Mish()
  )
  (6): Sequential(
    (conv6): Conv2d(32, 64, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn6): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish6): Mish()
  )
  (7): EmptyModule()
  (8): Sequential(
    (conv7): Conv2d(64, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn7): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish7): Mish()
  )
  (9): EmptyModule()
  (10): Sequential(
    (conv8): Conv2d(128, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn8): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish8): Mish()
  )
  (11): Sequential(
    (conv9): Conv2d(64, 128, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1), bias=False)
    (bn9): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish9): Mish()
  )
  (12): Sequential(
    (conv10): Conv2d(128, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn10): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish10): Mish()
  )
  (13): EmptyModule()
  (14): Sequential(
    (conv11): Conv2d(128, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn11): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish11): Mish()
  )
  (15): Sequential(
    (conv12): Conv2d(64, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn12): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish12): Mish()
  )
  (16): Sequential(
    (conv13): Conv2d(64, 64, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn13): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish13): Mish()
  )
  (17): EmptyModule()
  (18): Sequential(
    (conv14): Conv2d(64, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn14): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish14): Mish()
  )
  (19): Sequential(
    (conv15): Conv2d(64, 64, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn15): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish15): Mish()
  )
  (20): EmptyModule()
  (21): Sequential(
    (conv16): Conv2d(64, 64, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn16): BatchNorm2d(64, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish16): Mish()
  )
  (22): EmptyModule()
  (23): Sequential(
    (conv17): Conv2d(128, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn17): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish17): Mish()
  )
  (24): Sequential(
    (conv18): Conv2d(128, 256, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1), bias=False)
    (bn18): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish18): Mish()
  )
  (25): Sequential(
    (conv19): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn19): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish19): Mish()
  )
  (26): EmptyModule()
  (27): Sequential(
    (conv20): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn20): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish20): Mish()
  )
  (28): Sequential(
    (conv21): Conv2d(128, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn21): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish21): Mish()
  )
  (29): Sequential(
    (conv22): Conv2d(128, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn22): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish22): Mish()
  )
  (30): EmptyModule()
  (31): Sequential(
    (conv23): Conv2d(128, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn23): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish23): Mish()
  )
  (32): Sequential(
    (conv24): Conv2d(128, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn24): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish24): Mish()
  )
  (33): EmptyModule()
  (34): Sequential(
    (conv25): Conv2d(128, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn25): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish25): Mish()
  )
  (35): Sequential(
    (conv26): Conv2d(128, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn26): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish26): Mish()
  )
  (36): EmptyModule()
  (37): Sequential(
    (conv27): Conv2d(128, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn27): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish27): Mish()
  )
  (38): Sequential(
    (conv28): Conv2d(128, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn28): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish28): Mish()
  )
  (39): EmptyModule()
  (40): Sequential(
    (conv29): Conv2d(128, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn29): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish29): Mish()
  )
  (41): Sequential(
    (conv30): Conv2d(128, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn30): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish30): Mish()
  )
  (42): EmptyModule()
  (43): Sequential(
    (conv31): Conv2d(128, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn31): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish31): Mish()
  )
  (44): Sequential(
    (conv32): Conv2d(128, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn32): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish32): Mish()
  )
  (45): EmptyModule()
  (46): Sequential(
    (conv33): Conv2d(128, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn33): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish33): Mish()
  )
  (47): Sequential(
    (conv34): Conv2d(128, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn34): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish34): Mish()
  )
  (48): EmptyModule()
  (49): Sequential(
    (conv35): Conv2d(128, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn35): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish35): Mish()
  )
  (50): Sequential(
    (conv36): Conv2d(128, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn36): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish36): Mish()
  )
  (51): EmptyModule()
  (52): Sequential(
    (conv37): Conv2d(128, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn37): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish37): Mish()
  )
  (53): EmptyModule()
  (54): Sequential(
    (conv38): Conv2d(256, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn38): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish38): Mish()
  )
  (55): Sequential(
    (conv39): Conv2d(256, 512, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1), bias=False)
    (bn39): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish39): Mish()
  )
  (56): Sequential(
    (conv40): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn40): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish40): Mish()
  )
  (57): EmptyModule()
  (58): Sequential(
    (conv41): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn41): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish41): Mish()
  )
  (59): Sequential(
    (conv42): Conv2d(256, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn42): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish42): Mish()
  )
  (60): Sequential(
    (conv43): Conv2d(256, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn43): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish43): Mish()
  )
  (61): EmptyModule()
  (62): Sequential(
    (conv44): Conv2d(256, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn44): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish44): Mish()
  )
  (63): Sequential(
    (conv45): Conv2d(256, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn45): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish45): Mish()
  )
  (64): EmptyModule()
  (65): Sequential(
    (conv46): Conv2d(256, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn46): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish46): Mish()
  )
  (66): Sequential(
    (conv47): Conv2d(256, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn47): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish47): Mish()
  )
  (67): EmptyModule()
  (68): Sequential(
    (conv48): Conv2d(256, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn48): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish48): Mish()
  )
  (69): Sequential(
    (conv49): Conv2d(256, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn49): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish49): Mish()
  )
  (70): EmptyModule()
  (71): Sequential(
    (conv50): Conv2d(256, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn50): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish50): Mish()
  )
  (72): Sequential(
    (conv51): Conv2d(256, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn51): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish51): Mish()
  )
  (73): EmptyModule()
  (74): Sequential(
    (conv52): Conv2d(256, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn52): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish52): Mish()
  )
  (75): Sequential(
    (conv53): Conv2d(256, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn53): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish53): Mish()
  )
  (76): EmptyModule()
  (77): Sequential(
    (conv54): Conv2d(256, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn54): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish54): Mish()
  )
  (78): Sequential(
    (conv55): Conv2d(256, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn55): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish55): Mish()
  )
  (79): EmptyModule()
  (80): Sequential(
    (conv56): Conv2d(256, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn56): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish56): Mish()
  )
  (81): Sequential(
    (conv57): Conv2d(256, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn57): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish57): Mish()
  )
  (82): EmptyModule()
  (83): Sequential(
    (conv58): Conv2d(256, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn58): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish58): Mish()
  )
  (84): EmptyModule()
  (85): Sequential(
    (conv59): Conv2d(512, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn59): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish59): Mish()
  )
  (86): Sequential(
    (conv60): Conv2d(512, 1024, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1), bias=False)
    (bn60): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish60): Mish()
  )
  (87): Sequential(
    (conv61): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn61): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish61): Mish()
  )
  (88): EmptyModule()
  (89): Sequential(
    (conv62): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn62): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish62): Mish()
  )
  (90): Sequential(
    (conv63): Conv2d(512, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn63): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish63): Mish()
  )
  (91): Sequential(
    (conv64): Conv2d(512, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn64): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish64): Mish()
  )
  (92): EmptyModule()
  (93): Sequential(
    (conv65): Conv2d(512, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn65): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish65): Mish()
  )
  (94): Sequential(
    (conv66): Conv2d(512, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn66): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish66): Mish()
  )
  (95): EmptyModule()
  (96): Sequential(
    (conv67): Conv2d(512, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn67): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish67): Mish()
  )
  (97): Sequential(
    (conv68): Conv2d(512, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn68): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish68): Mish()
  )
  (98): EmptyModule()
  (99): Sequential(
    (conv69): Conv2d(512, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn69): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish69): Mish()
  )
  (100): Sequential(
    (conv70): Conv2d(512, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn70): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish70): Mish()
  )
  (101): EmptyModule()
  (102): Sequential(
    (conv71): Conv2d(512, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn71): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish71): Mish()
  )
  (103): EmptyModule()
  (104): Sequential(
    (conv72): Conv2d(1024, 1024, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn72): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (mish72): Mish()
  )
  (105): Sequential(
    (conv73): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn73): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky73): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (106): Sequential(
    (conv74): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn74): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky74): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (107): Sequential(
    (conv75): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn75): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky75): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (108): MaxPool2d(kernel_size=5, stride=1, padding=2, dilation=1, ceil_mode=False)
  (109): EmptyModule()
  (110): MaxPool2d(kernel_size=9, stride=1, padding=4, dilation=1, ceil_mode=False)
  (111): EmptyModule()
  (112): MaxPool2d(kernel_size=13, stride=1, padding=6, dilation=1, ceil_mode=False)
  (113): EmptyModule()
  (114): Sequential(
    (conv76): Conv2d(2048, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn76): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky76): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (115): Sequential(
    (conv77): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn77): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky77): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (116): Sequential(
    (conv78): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn78): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky78): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (117): Sequential(
    (conv79): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn79): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky79): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (118): Upsample_expand()
  (119): EmptyModule()
  (120): Sequential(
    (conv80): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn80): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky80): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (121): EmptyModule()
  (122): Sequential(
    (conv81): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn81): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky81): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (123): Sequential(
    (conv82): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn82): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky82): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (124): Sequential(
    (conv83): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn83): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky83): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (125): Sequential(
    (conv84): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn84): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky84): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (126): Sequential(
    (conv85): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn85): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky85): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (127): Sequential(
    (conv86): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn86): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky86): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (128): Upsample_expand()
  (129): EmptyModule()
  (130): Sequential(
    (conv87): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn87): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky87): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (131): EmptyModule()
  (132): Sequential(
    (conv88): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn88): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky88): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (133): Sequential(
    (conv89): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn89): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky89): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (134): Sequential(
    (conv90): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn90): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky90): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (135): Sequential(
    (conv91): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn91): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky91): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (136): Sequential(
    (conv92): Conv2d(256, 128, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn92): BatchNorm2d(128, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky92): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (137): Sequential(
    (conv93): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn93): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky93): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (138): Sequential(
    (conv94): Conv2d(256, 255, kernel_size=(1, 1), stride=(1, 1))
  )
  (139): YoloLayer()
  (140): EmptyModule()
  (141): Sequential(
    (conv95): Conv2d(128, 256, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1), bias=False)
    (bn95): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky95): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (142): EmptyModule()
  (143): Sequential(
    (conv96): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn96): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky96): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (144): Sequential(
    (conv97): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn97): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky97): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (145): Sequential(
    (conv98): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn98): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky98): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (146): Sequential(
    (conv99): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn99): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky99): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (147): Sequential(
    (conv100): Conv2d(512, 256, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn100): BatchNorm2d(256, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky100): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (148): Sequential(
    (conv101): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn101): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky101): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (149): Sequential(
    (conv102): Conv2d(512, 255, kernel_size=(1, 1), stride=(1, 1))
  )
  (150): YoloLayer()
  (151): EmptyModule()
  (152): Sequential(
    (conv103): Conv2d(256, 512, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1), bias=False)
    (bn103): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky103): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (153): EmptyModule()
  (154): Sequential(
    (conv104): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn104): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky104): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (155): Sequential(
    (conv105): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn105): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky105): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (156): Sequential(
    (conv106): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn106): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky106): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (157): Sequential(
    (conv107): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn107): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky107): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (158): Sequential(
    (conv108): Conv2d(1024, 512, kernel_size=(1, 1), stride=(1, 1), bias=False)
    (bn108): BatchNorm2d(512, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky108): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (159): Sequential(
    (conv109): Conv2d(512, 1024, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1), bias=False)
    (bn109): BatchNorm2d(1024, eps=1e-05, momentum=0.1, affine=True, track_running_stats=True)
    (leaky109): LeakyReLU(negative_slope=0.1, inplace=True)
  )
  (160): Sequential(
    (conv110): Conv2d(1024, 255, kernel_size=(1, 1), stride=(1, 1))
  )
  (161): YoloLayer()
)
```

