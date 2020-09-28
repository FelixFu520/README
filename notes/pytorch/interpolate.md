# Pytorch上下采样函数--interpolate

2020年9月23日

---

最近用到了上采样下采样操作，pytorch中使用interpolate可以很轻松的完成

```python
def interpolate(input, size=None, scale_factor=None, mode='nearest', align_corners=None):
    r"""
    根据给定 size 或 scale_factor，上采样或下采样输入数据input.
    
    当前支持 temporal, spatial 和 volumetric 输入数据的上采样，其shape 分别为：3-D, 4-D 和 5-D.
    输入数据的形式为：mini-batch x channels x [optional depth] x [optional height] x width.

    上采样算法有：nearest, linear(3D-only), bilinear(4D-only), trilinear(5D-only).
    
    参数:
    - input (Tensor): input tensor
    - size (int or Tuple[int] or Tuple[int, int] or Tuple[int, int, int]):输出的 spatial 尺寸.
    - scale_factor (float or Tuple[float]): spatial 尺寸的缩放因子.
    - mode (string): 上采样算法:nearest, linear, bilinear, trilinear, area. 默认为 nearest.
    - align_corners (bool, optional): 如果 align_corners=True，则对齐 input 和 output 的角点像素(corner pixels)，保持在角点像素的值. 只会对 mode=linear, bilinear 和 trilinear 有作用. 默认是 False.
    """
    from numbers import Integral
    from .modules.utils import _ntuple

    def _check_size_scale_factor(dim):
        if size is None and scale_factor is None:
            raise ValueError('either size or scale_factor should be defined')
        if size is not None and scale_factor is not None:
            raise ValueError('only one of size or scale_factor should be defined')
        if scale_factor is not None and isinstance(scale_factor, tuple)\
                and len(scale_factor) != dim:
            raise ValueError('scale_factor shape must match input shape. '
                             'Input is {}D, scale_factor size is {}'.format(dim, len(scale_factor)))

    def _output_size(dim):
        _check_size_scale_factor(dim)
        if size is not None:
            return size
        scale_factors = _ntuple(dim)(scale_factor)
        # math.floor might return float in py2.7
        return [int(math.floor(input.size(i + 2) * scale_factors[i])) for i in range(dim)]

    if mode in ('nearest', 'area'):
        if align_corners is not None:
            raise ValueError("align_corners option can only be set with the "
                             "interpolating modes: linear | bilinear | trilinear")
    else:
        if align_corners is None:
            warnings.warn("Default upsampling behavior when mode={} is changed "
                          "to align_corners=False since 0.4.0. Please specify "
                          "align_corners=True if the old behavior is desired. "
                          "See the documentation of nn.Upsample for details.".format(mode))
            align_corners = False

    if input.dim() == 3 and mode == 'nearest':
        return torch._C._nn.upsample_nearest1d(input, _output_size(1))
    elif input.dim() == 4 and mode == 'nearest':
        return torch._C._nn.upsample_nearest2d(input, _output_size(2))
    elif input.dim() == 5 and mode == 'nearest':
        return torch._C._nn.upsample_nearest3d(input, _output_size(3))
    elif input.dim() == 3 and mode == 'area':
        return adaptive_avg_pool1d(input, _output_size(1))
    elif input.dim() == 4 and mode == 'area':
        return adaptive_avg_pool2d(input, _output_size(2))
    elif input.dim() == 5 and mode == 'area':
        return adaptive_avg_pool3d(input, _output_size(3))
    elif input.dim() == 3 and mode == 'linear':
        return torch._C._nn.upsample_linear1d(input, _output_size(1), align_corners)
    elif input.dim() == 3 and mode == 'bilinear':
        raise NotImplementedError("Got 3D input, but bilinear mode needs 4D input")
    elif input.dim() == 3 and mode == 'trilinear':
        raise NotImplementedError("Got 3D input, but trilinear mode needs 5D input")
    elif input.dim() == 4 and mode == 'linear':
        raise NotImplementedError("Got 4D input, but linear mode needs 3D input")
    elif input.dim() == 4 and mode == 'bilinear':
        return torch._C._nn.upsample_bilinear2d(input, _output_size(2), align_corners)
    elif input.dim() == 4 and mode == 'trilinear':
        raise NotImplementedError("Got 4D input, but trilinear mode needs 5D input")
    elif input.dim() == 5 and mode == 'linear':
        raise NotImplementedError("Got 5D input, but linear mode needs 3D input")
    elif input.dim() == 5 and mode == 'bilinear':
        raise NotImplementedError("Got 5D input, but bilinear mode needs 4D input")
    elif input.dim() == 5 and mode == 'trilinear':
        return torch._C._nn.upsample_trilinear3d(input, _output_size(3), align_corners)
    else:
        raise NotImplementedError("Input Error: Only 3D, 4D and 5D input Tensors supported"
                                  " (got {}D) for the modes: nearest | linear | bilinear | trilinear"
                                  " (got {})".format(input.dim(), mode))

```

举个例子：

```python
    x = Variable(torch.randn([1, 3, 64, 64]))
    y0 = F.interpolate(x, scale_factor=0.5)
    y1 = F.interpolate(x, size=[32, 32])

    y2 = F.interpolate(x, size=[128, 128], mode="bilinear")

    print(y0.shape)
    print(y1.shape)
    print(y2.shape)
```

这里注意上采样的时候mode默认是“nearest”，这里指定双线性插值“bilinear”
得到结果

```python
torch.Size([1, 3, 32, 32])
torch.Size([1, 3, 32, 32])
torch.Size([1, 3, 128, 128])
```