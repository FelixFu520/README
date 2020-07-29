# 入门案例代码解析

2020年7月29日

![](imgs/fit1.png)

[参考代码](https://github.com/FelixFu520/TensorRT/blob/master/torch2onnx2tensorrt_cnn/pytorch_onnx_trt-2.ipynb)|[原始代码](https://github.com/RizhaoCai/PyTorch_ONNX_TensorRT)

## 1. 构建Engine

**NetworkDefinition-->Builder-->Engine**

```python
# Build an engine
engine = get_engine(max_batch_size, onnx_model_path, trt_engine_path, fp16_mode, int8_mode)
```



```python
def get_engine(max_batch_size=1, onnx_file_path="", engine_file_path="",\
               fp16_mode=False, int8_mode=False, save_engine=False,
              ):
    """Attempts to load a serialized engine if available, otherwise builds a new TensorRT engine and saves it."""
    def build_engine(max_batch_size, save_engine):
        """Takes an ONNX file and creates a TensorRT engine to run inference with"""
        # create_network() without parameters will make parser.parse() return False
        with trt.Builder(TRT_LOGGER) as builder, \
                builder.create_network(flags=1 << (int)(trt.NetworkDefinitionCreationFlag.EXPLICIT_BATCH)) as network,\
                trt.OnnxParser(network, TRT_LOGGER) as parser:
            
            builder.max_workspace_size = 1 << 30 # Your workspace size
            builder.max_batch_size = max_batch_size
            #pdb.set_trace()
            builder.fp16_mode = fp16_mode  # Default: False
            builder.int8_mode = int8_mode  # Default: False
            if int8_mode:
                # To be updated
                raise NotImplementedError
                
            # Parse model file
            if not os.path.exists(onnx_file_path):
                quit('ONNX file {} not found'.format(onnx_file_path))
                
            print('Loading ONNX file from path {}...'.format(onnx_file_path))
            with open(onnx_file_path, 'rb') as model:
                print('Beginning ONNX file parsing')
                parser.parse(model.read())
            print('Completed parsing of ONNX file')
            print('Building an engine from file {}; this may take a while...'.format(onnx_file_path))
            #pdb.set_trace()
            #network.mark_output(network.get_layer(network.num_layers-1).get_output(0)) # Riz   
            #network.mark_output(network.get_layer(network.num_layers-1).get_output(1)) # Riz
            
            engine = builder.build_cuda_engine(network)
            print("Completed creating Engine")
            
            if save_engine:
                with open(engine_file_path, "wb") as f:
                    f.write(engine.serialize())
            return engine
        
    if os.path.exists(engine_file_path):
        # If a serialized engine exists, load it instead of building a new one.
        print("Reading engine from file {}".format(engine_file_path))
        with open(engine_file_path, "rb") as f, trt.Runtime(TRT_LOGGER) as runtime:
            return runtime.deserialize_cuda_engine(f.read())
    else:
        return build_engine(max_batch_size, save_engine)
```

get_engine()方法判别engine是否存在，存在的话直接用trt.Runtime()类的runtime对象下的deserialize_cuda_engine方法读取。

```python
with open(engine_file_path, "rb") as f, trt.Runtime(TRT_LOGGER) as runtime:
            return runtime.deserialize_cuda_engine(f.read())
```



如果不存在，调用build_engine方法先后创建builder, network, parser；然后，运用parser.parse()方法解析model，builder.build_cuda_engine方法根据网络创建engine；最后，利用engine.serialize()方法把创建好的engine并行化（保存为二进制流），存在”engine_file_path“这个文件下。



##### 构建Engine整个过程总结：

![](imgs/fit1.png)

**NetWork Definition**-->*Builder*-->**Engine**

```shell
1. 创建类
	trt.Builder(TRT_LOGGER) as builder
	builder.create_network(flags=1 << (int)(trt.NetworkDefinitionCreationFlag.EXPLICIT_BATCH)) as network
  trt.OnnxParser(network, TRT_LOGGER) as parser
2. 解析ONNX
	with open(onnx_file_path, 'rb') as model:
  		parser.parse(model.read())
3. 创建Engine
	engine = builder.build_cuda_engine(network)
4. 序列化
	with open(engine_file_path, "wb") as f:
  		f.write(engine.serialize())
  with open(engine_file_path, "rb") as f, trt.Runtime(TRT_LOGGER) as runtime:
  		return runtime.deserialize_cuda_engine(f.read())
                 
```

## 2. 运行TensorRT Engine

```python
# Create the context for this engine
context = engine.create_execution_context() 
# Allocate buffers for input and output
inputs, outputs, bindings, stream = allocate_buffers(engine) # input, output: host # bindings 


# Do inference
shape_of_output = (max_batch_size, 10)
# Load data to the buffer
inputs[0].host = x_input.reshape(-1)
# inputs[1].host = ... for multiple input
t1 = time.time()
trt_outputs = do_inference(context, bindings=bindings, inputs=inputs, outputs=outputs, stream=stream) # numpy data
t2 = time.time()
output_from_trt_engine = postprocess_the_outputs(trt_outputs[0], shape_of_output)
```

```python
class HostDeviceMem(object):
    def __init__(self, host_mem, device_mem):
        """Within this context, host_mom means the cpu memory and device means the GPU memory
        """
        self.host = host_mem 
        self.device = device_mem
    def __str__(self):
        return "Host:\n" + str(self.host) + "\nDevice:\n" + str(self.device)

    def __repr__(self):
        return self.__str__()
    
def allocate_buffers(engine):
    inputs = []
    outputs = []
    bindings = []
    stream = cuda.Stream()
    for binding in engine:
        size = trt.volume(engine.get_binding_shape(binding)) * engine.max_batch_size
        dtype = trt.nptype(engine.get_binding_dtype(binding))
        # Allocate host and device buffers
        host_mem = cuda.pagelocked_empty(size, dtype)
        device_mem = cuda.mem_alloc(host_mem.nbytes)
        # Append the device buffer to device bindings.
        bindings.append(int(device_mem))
        # Append to the appropriate list.
        if engine.binding_is_input(binding):
            inputs.append(HostDeviceMem(host_mem, device_mem))
        else:
            outputs.append(HostDeviceMem(host_mem, device_mem))
    return inputs, outputs, bindings, stream
```

##### TensorRT 执行 整个过程总结：

![](imgs/fit1.png)

**Engine**-->上下文准备(context、buffers、input、output）-->推理，转换输出

```shell
1.Create the context for this engine
  context = engine.create_execution_context() # 这段代码就是创建了一个在runtime过程中所必需的context。（最后也要destroy）
2. Allocate buffers for input and output
  inputs, outputs, bindings, stream = allocate_buffers(engine) # input, output: host # bindings # allocate_buffers方法为这个创造出来的engine分配空间。
```



## 3. 总结

![](imgs/fit1.png)

**NetWork Definition**-->*Builder*-->**Engine**-->准备上下文(context、buffers、input、output）-->推理，转换输出

```shell
1. 创建类
	trt.Builder(TRT_LOGGER) as builder
	builder.create_network(flags=1 << (int)(trt.NetworkDefinitionCreationFlag.EXPLICIT_BATCH)) as network
  trt.OnnxParser(network, TRT_LOGGER) as parser
2. 解析ONNX
	with open(onnx_file_path, 'rb') as model:
  		parser.parse(model.read())
3. 创建Engine
	engine = builder.build_cuda_engine(network)
4. 序列化
	with open(engine_file_path, "wb") as f:
  		f.write(engine.serialize())
  with open(engine_file_path, "rb") as f, trt.Runtime(TRT_LOGGER) as runtime:
  		return runtime.deserialize_cuda_engine(f.read())
  		
5.Create the context for this engine
  context = engine.create_execution_context() # 这段代码就是创建了一个在runtime过程中所必需的context。（最后也要destroy）
6. Allocate buffers for input and output
  inputs, outputs, bindings, stream = allocate_buffers(engine) # input, output: host # bindings # allocate_buffers方法为这个创造出来的engine分配空间。
                 
```



## 参考

> [代码解析](https://blog.csdn.net/qq_33120609/article/details/96578190)
>
> 