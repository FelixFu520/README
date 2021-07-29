# TVM源码学习

⌚️:2020年11月30日

📚参考

---



## 1. 简介

本系列博客的主要目的是博主在打算学习TVM时，发现对TVM的源码介绍内容非常少，因此本系列博客主要以学习TVM框架为前提下，来对TVM的源码内容进行解读，从而也能帮助更多的人来了解TVM。

## 2. TVM源码目录结构

1. 3rdparty：主要是TVM使用到的第三方库
2. apps：包含了TVM的扩展项目，并有使用TVM的示例
3. cmake：cmake工程文件
4. conda：conda安装脚本
5. docker：包含TVM的docker模块
6. docs：包含TVM的文档
7. golang：包含TVM的golang接口
8. include：包含TVM中C源码的头文件
9. jvm：包含TVM的java接口
10. licenses： 包含TVM使用的license
11. nnvm：TVM使用的一类编译器前端nnvm
12. python：TVM的Python源代码
13. rust：包含TVM的rust接口？
14. src：包含TVM的C源代码
15. tests：包含TVM的测试用例
16. topi：包含TVM的相关优化
17. tutorial：包含TVM的相关教程
18. vta：包含基于TVM的vta项目
19. web：包含TVM的web后端
20. 其他文件：相关编译文件



## 3. TVM代码库演练示例

https://blog.csdn.net/weixin_42164269/article/details/104291677

了解新的代码库可能是一个挑战。对于像TVM这样的代码库，尤其如此，其中不同的组件以非显而易见的方式交互。在本指南中，我们尝试通过一个简单的示例来说明构成编译 的关键元素。对于每个重要步骤，我们都会显示在代码库中的哪个位置。目的是让新开发人员和感兴趣的用户更快地进入代码库。

### **3.1 代码库结构概述**

在TVM库的根目录中，我们具有以下子目录，这些子目录一起构成了大部分代码库。

- `src` -用于操作符编译和部署运行时的C ++代码。
- `src/relay` -Relay实现，深度学习框架的新功能IR。
- `python`-Python前端，封装【src】中C ++函数和对象实现。
- `topi` -计算标准神经网络操作符的定义和后端调度。

使用标准的深度学习术语，【`src/relay`】是管理计算图的组件，并且图中的节点是使用【`src`】其余部分中实现的基础结构来编译和执行的。`python`为用户可用来执行编译的C ++ API和驱动程序代码提供python绑定。操作符对应【src/relay/op】中注册的每一个节点。操作符的实现位于【`topi`】，并且使用C ++或Python进行编码。

当用户通过【`relay.build(...)`】调用图编译时，图中的每个节点都会发生以下操作序列：

- 通过查询操作符注册表来查找操作符实现
- 为操作符生成计算表达式和调度
- 将运算符编译为目标代码

TVM代码库有趣的方面之一是C ++和Python之间的互操作性不是单向的。通常，所有执行繁重工作的代码都是用C ++实现的，并且为用户界面提供了Python绑定。在TVM中也是如此，但是在TVM代码库中，C ++代码也可以调用Python模块中定义的函数。例如，卷积运算符是用Python实现的，其实现是从Relay中的C ++代码调用的。

### **3.2 向量加法示例**

我们使用一个直接使用低级TVM API的简单示例。该示例是矢量加法，[【](https://docs.tvm.ai/tutorials/get_started.html#sphx-glr-tutorials-get-started-py)https://docs.tvm.ai/tutorials/get_started.html#sphx-glr-tutorials-get-started-py[】](https://docs.tvm.ai/tutorials/get_started.html#sphx-glr-tutorials-get-started-py)进行详细介绍。

```html
n = 1024
A = tvm.placeholder((n,), name='A')
B = tvm.placeholder((n,), name='B')
C = tvm.compute(A.shape, lambda i: A[i] + B[i], name="C")
```

在这里，`A`，`B`，`C的`类型是【`tvm.tensor.Tensor`】，定义在【`python/tvm/tensor.py`】中。Python中的【`Tensor`】是由C ++中的【`Tensor`】包装的，在【`include/tvm/tensor.h`】和【`src/lang/tensor.cc`】中实现。TVM中的所有Python类型都可以视为具有相同名称的基础C ++类型的句柄。如果您在下面看到Python 【`Tensor`】类型的定义，可以看到它是【`Object`】的子类。

```html
@register_object
class Tensor(Object, _expr.ExprOp):
    """Tensor object, to construct, see function.Tensor"""
    def __call__(self, *indices):
       ...
```

对象协议是将C ++类型公开给前端语言（包括Python）的基础。TVM实现Python包装的方法并不简单。[【](https://docs.tvm.ai/dev/runtime.html#tvm-node-and-compiler-stack)https://docs.tvm.ai/dev/runtime.html#tvm-node-and-compiler-stack[】](https://docs.tvm.ai/dev/runtime.html#tvm-node-and-compiler-stack)简要介绍了[它](https://docs.tvm.ai/dev/runtime.html#tvm-node-and-compiler-stack)，如果您有兴趣，请参阅【`python/tvm/_ffi/`】详细信息。

我们使用【`TVM_REGISTER_*`】宏，以[PackedFunc](https://docs.tvm.ai/dev/runtime.html#packedfunc)的形式将C ++函数公开给前端语言。【`PackedFunc`】 是TVM在C ++和Python之间实现互操作性的另一种机制。特别的，这使得从C ++代码库调用Python函数非常容易。您还可以检查【 [FFI Navigator](https://github.com/tqchen/ffi-navigator)（https://github.com/tqchen/ffi-navigator）】，该[导航](https://github.com/tqchen/ffi-navigator)器使您可以在python和c ++ FFI调用之间进行导航。

【`Tensor`】对象具有【`Operation`】与其相关联，定义在【`python/tvm/te/tensor.py`】，【`include/tvm/te/operation.h`】和【`src/tvm/te/operation`】子目录。【`Tensor`】是【`Operation`】对象的输出。每个【`Operation`】对象都有相应的【`input_tensors()`】方法，该方法返回输入【`Tensor`】列表。这样我们就可以跟踪【`Operation`】之间的依赖关系。

我们传递与输出张量【`C`】相对应的运算以到【`python/tvm/te/schedule.py`】中的【`tvm.create_schedule()`】函数。

```html
s = tvm.create_schedule(C.op)
```

此函数映射到【`include/tvm/schedule.h`】中的C ++函数。

```html
inline Schedule create_schedule(Array<Operation> ops) {
  return ScheduleNode::make(ops);
}
```

`【Schedule】`由【`Stage`】和输出【`Operation`】的集合组成。

`【Stage】`对应一个【`Operation`】。在上面的矢量加法示例中，有两个占位符操作和一个计算操作，因此调度【`s`】包含三个阶段。各【`Stage`】保持关于循环嵌套结构的信息，每个循环的类型（`Parallel`，`Vectorized`，`Unrolled`），并且下一个【`Stage`】循环嵌套执行其计算`，`如果有的话。

`【Schedule】`和【`Stage`】被定义在【`tvm/python/te/schedule.py`】，【`include/tvm/te/schedule.h`】和【`src/te/schedule/schedule_ops.cc`】。

为简单起见，我们在上述【create_schedule()】函数创建的默认调度中调用【`tvm.build(...)`】函数。

```html
target = "cuda"
fadd = tvm.build(s, [A, B, C], target)
```

`定义在【python/tvm/driver/build_module.py】中的【tvm.build()】，接受一个调度`，输入和输出【`Tensor`】以及目标，然后返回一个【[`tvm.runtime.Module`](https://docs.tvm.ai/api/python/runtime.html#tvm.runtime.Module)】对象。一个【[`tvm.runtime.Module`](https://docs.tvm.ai/api/python/runtime.html#tvm.runtime.Module)】对象包含一个可以使用函数调用语法调用的已编译函数。

【`tvm.build()`】的过程可以分为两个步骤：

- 降低，将高级别的初始循环嵌套结构转换为最终的低级别IR
- 代码生成，其中从低级IR生成目标机器代码

降低是通过【`tvm.lower()`】函数完成的，定义在【`python/tvm/build_module.py`】中。首先，执行边界推断，并创建初始循环嵌套结构。

```html
def lower(sch,
          args,
          name="default_function",
          binds=None,
          simple_mode=False):
   ...
   bounds = schedule.InferBound(sch)
   stmt = schedule.ScheduleOps(sch, bounds)
   ...
```

边界推断是推断所有循环边界和中间缓冲区大小的过程。如果您以CUDA后端为目标并且使用共享内存，则会在此处自动确定所需的最小大小。绑定推理在【`src/te/schedule/bound.cc`】，【`src/te/schedule/graph.cc`】和【`src/te/schedule/message_passing.cc`】中实现。有关绑定推理如何工作的更多信息，请参见【http://docs.tvm.ai/dev/inferbound.html】。

`【stmt】`，是【`ScheduleOps()`】的输出，代表初始的循环嵌套结构。如果您已将【`reorder`】原语和【`split` 】原语应用到你的调度中，则初始循环嵌套已经反映了这些更改。【`ScheduleOps()`】在【`src/te/schedule/schedule_ops.cc`】中定义。

接下来，我们将多个降低转换应用于【`stmt`】。这些过程在【`src/tir/pass`】子目录中实现。例如，如果您已对时间表应用了【`vectorize`】或【`unroll`】原语，则它们将被应用到循环矢量化和下面的展开过程中。

```html
...
stmt = ir_pass.VectorizeLoop(stmt)
...
stmt = ir_pass.UnrollLoop(
    stmt,
    cfg.auto_unroll_max_step,
    cfg.auto_unroll_max_depth,
    cfg.auto_unroll_max_extent,
    cfg.unroll_explicit)
...
```

降低完成后，【`build()`】函数从降低的函数生成目标机器代码。如果以x86为目标，则此代码可以包含SSE或AVX指令，或以CUDA为目标的PTX指令。除了目标特定的机器代码之外，TVM还生成主机侧代码，该代码负责内存管理，内核启动等。

代码生成由【`python/tvm/target/codegen.py`】中定义的【`build_module()`】函数完成。在C ++侧，代码生成在`【src/target/codegen】`子目录中实现。【`build_module()`】Python函数将达到【`src/target/codegen/codegen.cc`】中的【`Build()`】函数：

```html
runtime::Module Build(const Array<LoweredFunc>& funcs,
                      const std::string& target) {
  std::string build_f_name = "codegen.build_" + target;
  const PackedFunc* bf = runtime::Registry::Get(build_f_name);
  runtime::Module m = (*bf)(funcs, target);
  return m;
}
```

【`Build()`】函数在【`PackedFunc`】注册表中查找给定目标的代码生成器，并调用找到的函数。例如，【`codegen.build_cuda`】函数在【`src/codegen/build_cuda_on.cc`】中注册，如下所示：

```html
TVM_REGISTER_GLOBAL("codegen.build_cuda")
.set_body([](TVMArgs args, TVMRetValue* rv) {
    *rv = BuildCUDA(args[0]);
  });
```

上述使用【`CodeGenCUDA` 】类从降低IR生成的CUDA源码核【`BuildCUDA()`】定义在【`src/codegen/codegen_cuda.cc`】，和使用NVRTC内核编译。如果您针对使用LLVM（包括x86，ARM，NVPTX和AMDGPU）的后端，则代码生成主要由【s`rc/codegen/llvm/codegen_llvm.cc`】中定义的类【`CodeGenLLVM`】完成。【`CodeGenLLVM`】将TVM IR转换为LLVM IR，运行大量LLVM优化遍历，并生成目标机器代码。

【`src/codegen/codegen.cc`】中的【`Build()`】函数返回定义在【`include/tvm/runtime/module.h`】和【`src/runtime/module.cc`】中定义的对象【`runtime::Module`】。【`Module`】对象是一个容器，装载特定于目标的【`ModuleNode`】对象。每个后端都实现【`ModuleNode`】子类，以添加目标特定的运行时API调用。例如，CUDA后端在【`src/runtime/cuda/cuda_module.cc`】中实现【`CUDAModuleNode`】类，该类管理CUDA驱动程序API。上面的【`BuildCUDA()`】函数用【`runtime::Module`】装饰【`CUDAModuleNode`】，并返回到Python端。LLVM后端【`LLVMModuleNode`】在【`src/codegen/llvm/llvm_module.cc`】中实现，它处理已编译代码的JIT执行。【`ModuleNode`】的其他子类可以在【`src/runtime`】的子目录下找到，与每个后端相对应。

返回的模块（可以认为是已编译函数和设备API的组合）可以在TVM的NDArray对象上调用。

```html
ctx = tvm.context(target, 0)
a = tvm.nd.array(np.random.uniform(size=n).astype(A.dtype), ctx)
b = tvm.nd.array(np.random.uniform(size=n).astype(B.dtype), ctx)
c = tvm.nd.array(np.zeros(n, dtype=C.dtype), ctx)
fadd(a, b, c)
output = c.asnumpy()
```

在幕后，TVM会自动分配设备内存并管理内存传输。为此，每个后端都需要继承【`DeviceAPI`】类，定义在【`include/tvm/runtime/device_api.h`】中，并重写内存管理方法以使用特定于设备的API。例如，在【src/runtime/cuda/cuda_device_api.cc】中实现的【`CUDADeviceAPI`】CUDA后端，以使用【`cudaMalloc`】，【`cudaMemcpy`】等。

首次使用【`fadd(a, b, c)`】调用已编译的模块时，【`ModuleNode`】的【`GetFunction()`】方法被调用，来获得一个可用于内核调用的【`PackedFunc` 】方法。例如，在【src/runtime/cuda/cuda_device_api.cc】中，CUDA后端【`CUDAModuleNode::GetFunction()`】实现如下：

```html
PackedFunc CUDAModuleNode::GetFunction(
      const std::string& name,
      const std::shared_ptr<ModuleNode>& sptr_to_self) {
  auto it = fmap_.find(name);
  const FunctionInfo& info = it->second;
  CUDAWrappedFunc f;
  f.Init(this, sptr_to_self, name, info.arg_types.size(), info.thread_axis_tags);
  return PackFuncVoidAddr(f, info.arg_types);
}
```

【`PackedFunc`】的超载【`operator()`】将被调用，这反过来又调用实现在【`src/runtime/cuda/cuda_module.cc`】中的【`CUDAWrappedFunc`】的【`operator()`】函数，在这里终于我们看到了【`cuLaunchKernel`】驱动调用：

```html
class CUDAWrappedFunc {
 public:
  void Init(...)
  ...
  void operator()(TVMArgs args,
                  TVMRetValue* rv,
                  void** void_args) const {
    int device_id;
    CUDA_CALL(cudaGetDevice(&device_id));
    if (fcache_[device_id] == nullptr) {
      fcache_[device_id] = m_->GetFunc(device_id, func_name_);
    }
    CUstream strm = static_cast<CUstream>(CUDAThreadEntry::ThreadLocal()->stream);
    ThreadWorkLoad wl = thread_axis_cfg_.Extract(args);
    CUresult result = cuLaunchKernel(
        fcache_[device_id],
        wl.grid_dim(0),
        wl.grid_dim(1),
        wl.grid_dim(2),
        wl.block_dim(0),
        wl.block_dim(1),
        wl.block_dim(2),
        0, strm, void_args, 0);
  }
};
```

总结了TVM如何编译和执行函数。尽管我们没有详细介绍TOPI或Relay，但是最后，所有神经网络操作符都经过与上述相同的编译过程。鼓励您深入研究其余代码库的细节。