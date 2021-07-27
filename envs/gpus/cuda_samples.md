# CUDA Samples

⌚️: 2020年10月23日

📚参考

- [github](https://github.com/NVIDIA/cuda-samples)

----



# 简介

1. Simple Reference 
   基础CUDA示例，适用于初学者， 反映了运用CUDA和CUDA runtime APIs的一些基本概念.
2. Utilities Reference 
   演示如何查询设备能力和衡量GPU/CPU 带宽的实例程序。 
3. Graphics Reference 
   图形化示例展现的是 CUDA, OpenGL, DirectX 之间的互通性
4. Imaging Reference 
   图像处理，压缩，和数据分析
5. Finance Reference 
   金融计算的并行处理
6. Simulations Reference 
   展现一些运用CUDA的模拟算法
7. Advanced Reference 
   用CUDA实现的一些先进的算法
8. Cudalibraries Reference 
   这类示例主要告诉我们该如何使用CUDA各种函数库(NPP, CUBLAS, CUFFT,CUSPARSE, and CURAND).

# Simple Reference

1. asyncAPI 
   使用CUDA stream和events重叠CPU和GPU的执行
2. cdpSimplePrint - Simple Print (CUDA Dynamic Parallelism) 
   展示了使用CUDA Dynamic Parallelism进行简单输出，需要3.5以上。依赖于CDP
3. cdpSimpleQuicksort - Simple Quicksort (CUDA DynamicParallelism) 
   使用CUDA DynamicParallelism进行快速排序。也要求3.5以上
4. clock - Clock 
   如何使用clock函数去精确测量block的性能
5. clock_nvrtc - Clock libNVRTC 
   使用libNVRTC里的clock_nvtrc函数精确测量blokc性能
6. cppIntegration - C++ Integration 
   展示如何将CUDA程序整合进一个现成的C++应用中。CUDA的入口指针在主机端就是个函数，只有包含这个函数的时候才会用nvcc编译。也展示了向量类型也可以被CUDA使用。
7. cppOverload 
   展示如何在GPU上重载C++函数
8. cudaOpenMP 
   如何使用cudaOpenMP API来写多GPU程序
9. fp16ScalarProduct - FP16 Scalar Product 
   计算两个FP16类型标量的乘积
10. inlinePTX - Using Inline PTX 
    展示在CUDA代码中嵌入ptx代码
11. inlinePTX_nvrtc - Using Inline PTX with libNVRTC 
    同上
12. matrixMul - Matrix Multiplication (CUDA Runtime API Version) 
    实现了矩阵乘法。为了清楚地展示CUDA编程的规则而不是致力于优化矩阵乘法。为了展示GPU矩阵乘的性能，也使用了CUBLAS这个库去展示高性能的矩阵乘。
13. matrixMul_nvrtc - Matrix Multiplication with libNVRTC 
    同上
14. matrixMulCUBLAS - Matrix Multiplication (CUBLAS) 
    同上
15. matrixMulDrv - Matrix Multiplication (CUDA Driver API Version) 
    这个是使用驱动API实现的矩阵乘。
16. simpleAssert 
    如何使用Assert函数
17. simpleAssert_nvrtc - simpleAssert with libNVRTC 
    同上
18. simpleAtomicIntrinsics - Simple Atomic Intrinsics 
    原子操作
19. simpleAtomicIntrinsics_nvrtc - Simple Atomic Intrinsics with libNVRTC 
    同上
20. simpleCallback - Simple CUDA Callbacks 
    CUDA5.0的新功能。使用CPU回调CUDA流和事件的多线程异步计算。
21. simpleCubemapTexture - Simple Cubemap Texture 
    CUDA4.1的新功能，如何在代码中使用cubemap Textures
22. simpleIPC 
    展示进程间通讯(Inter Process Communication,IPC)，需要Linux系统
23. simpleLayeredTexture - Simple Layered Texture 
    CUDA4.0支持层次纹理操作
24. simpleMPI 
    如何使用信息传递接口(Message Passing Interface,MPI)
25. simpleMultiCopy - Simple Multi Copy and Compute 
    1.1以上，将计算和数据传输重叠。在2.0的机器上，在PCIe上任意方向的全速重叠都是可能的。这个例子展示了使用CUDA stream来重叠数据传输和Kernel执行。
26. simpleMultiGPU - Simple Multi-GPU 
    CUDA4.0对于CUDA上下文的管理和多GPU上的多线程并发
27. simpleOccupancy 
    通过利用配置程序启动一个Kernel来说明CUDA占用计算器(occupancy calculator)和占用启动配置器的使用(这特么都是啥。。。)，并检测不同配置下的使用率。
28. simpleP2P - Simple Peer-to-Peer Transfers with Multi-GPU 
    展示P2P的数据传输。也就是设备之间的数据传输。
29. simplePitchLinearTexture - Pitch Linear Texture 
    这翻译成等步长纹理。
30. simplePrintf 
    如何在设备中使用输出语句。在2.0之前，要用cuPrintf，之后可以直接printf。
31. simpleSeparateCompilation - Simple Static GPU Device Library 
    5.0特性，创建一个GPU静态库并在其他的Kernel中使用。这个例子展示了如何把一个(静态库中的)设备函数作为函数指针被调用。
32. simpleStreams 
    使用CUDA流重叠数据传输和Kernel执行。使用了页锁定内存
33. simpleSurfaceWrite - Simple Surface Write 
    2D表面引用
34. simpleTemplates - Simple Templates 
    就是讲讲模板怎么用，特别的，如何使用模板动态申请共享内存。
35. simpleTemplates_nvrtc - Simple Templates with libNVRTC 
    同上
36. simpleTexture - Simple Texture 
    使用纹理内存
37. simpleTextureDrv - Simple Texture (Driver Version) 
    使用驱动API操作纹理内存
38. simpleVoteIntrinsics - Simple Vote Intrinsics 
    如何使用Vote Intrinsics(不知道是啥)
39. simpleVoteIntrinsics_nvrtc - Simple Vote Intrinsics with libNVRTC 
    同上并且要使用NVRTC 接口。
40. simpleZeroCopy 
    零拷贝内存的使用，利用零拷贝可以直接从地址中读取而不用传递。
41. systemWideAtomics - System wide Atomics 
    原子操作
42. template - Template 
    一个零碎的模板工程，可以被用于创建一个粗大工程。
43. UnifiedMemoryStreams - Unified Memory Streams 
    使用统一内存的OpenMP和流。
44. vectorAdd - Vector Addition 
    运行时API实现的向量加法
45. vectorAdd_nvrtc - Vector Addition with libNVRTC 
    同上
46. vectorAddDrv - Vector Addition Driver API 
    同上

# Utilities Reference

1. bandwidthTest - Bandwidth Test 
   检测GPU之间内存复制的带宽和PCIe带宽。可以检测各种带宽。
2. deviceQuery - Device Query 
   设备信息。
3. deviceQuery - Device Query 
   使用驱动API检测设备信息。
4. p2pBandwidthLatencyTest - Peer-to-Peer Bandwidth Latency Test with Multi-GPUs 
   用来检测设备之间的数据计算时延和带宽。使用P2P和没使用都检测了。
5. topologyQuery - Topology Query 
   多GPU下请求的拓补结构。

# Graphics Reference

1. bindlessTexture - Bindless Texture 
   展示对cudaSurfaceObject, cudaTextureObject和MipMap的使用
2. Mandelbrot 
   展示Mandelbrot 或者 Julia集。同时也展示如何使用”double single”算法提高放大精度。
3. marchingCubes - Marching Cubes Isosurfaces 
   嗯。。。实在不知道是在讲啥，只能直译了。使用marching cubes算法从一堆数据中抽象出来几何等值面。
4. simpleD3D10 - Simple Direct3D10 (Vertex Array) 
   展示CUDA和Direct3D10的互操作性，通过CUDA产生了定点数组使用Direct3D10给出几何结构(?)
5. simpleD3D10RenderTarget - Simple Direct3D10 Render Target 
   CUDA和Direct3D10中渲染目标(rendertargets)的互操作性。使用CUDA对渲染目标的位置产生一个可视化直方图。
6. simpleD3D10Texture - Simple D3D10 Texture 
   展示CUDA和Direct3D10的纹理互操作性。
7. simpleD3D11Texture - Simple D3D11 Texture 
   呐，不出所料是展示CUDA和Direct3D11的纹理互操作性咯。
8. simpleD3D9 - Simple Direct3D9 (Vertex Arrays) 
   见条目4
9. simpleD3D9Texture - Simple D3D9 Texture 
   见条目6
10. simpleGL - Simple OpenGL 
    这是CUDA和OpenGL的互操作性。通过CUDA修改定点位置，然后用OpenGL渲染。
11. simpleGLES - Simple OpenGLES 
    展示CUDA和OpenGLES的数据交换。改变顶点位置并用OpenGL ES渲染。
12. simpleGLES_EGLOutput - Simple OpenGLES EGLOutput 
    展示CUDA和OpenGLES的数据交换。改变顶点位置并用OpenGL ES渲染。并展示使用EGLOutput机制和DRM库如何直接渲染显示。(然后显示在屏幕上)
13. simpleGLES_screen - Simple OpenGLES on Screen 
    展示CUDA和OpenGLES的数据交换。改变顶点位置并用OpenGL ES渲染。
14. simpleTexture3D - Simple Texture 3D 
    使用3维纹理
15. SLID3D10Texture - SLI D3D10 Texture 
    展示带有Direct3D10纹理的SLI与CUDA的互操作性。创建了一个从CUDAKernel写入的D3D10纹理。之后Direct3D在屏幕上渲染了结果
16. volumeFiltering - Volumetric Filtering with 3D Textures and Surface Writes 
    使用3D纹理和3D表面写进行3D体积过滤
17. volumeRender - Volume Rendering with 3D Textures 
    使用3D纹理进行基础的体积渲染

# Imaging Reference

暂略

# Finance Reference

暂略

# Simulations Reference

1. fluidsD3D9 - Fluids (Direct3D Version) 
   利用CUDA和CUFFT进行流体模拟，利用Direct3D 9渲染。
2. fluidsGL - Fluids (OpenGL Version) 
   利用CUDA和CUFFT进行流体模拟，利用OpenGL渲染。
3. fluidsGLES - Fluids (OpenGLES Version) 
   利用CUDA和CUFFT进行流体模拟，利用OpenGL渲染。
4. nbody - CUDA N-Body Simulation 
   模拟了N体问题(对的，包括三体)。通过参数可以控制N的大小，并且能够控制使用多少GPU设备。体的位置和速度使用零拷贝内存存储，对于设备数量少于4和有大量体的情况，带宽不再是运行瓶颈我们可以实现大规模的数据。
5. nbody_opengles - CUDA N-Body Simulation with GLES 
   这个模拟不提供用户交互。
6. nbody_screen - CUDA N-Body Simulation on Screen 
   在屏幕上模拟？
7. oceanFFT - CUDA FFT Ocean Simulation 
   使用CUFFT库模拟海洋高度场(Ocean height field)，并用OpenGL渲染。
8. particles - Particles 
   模拟大量粒子的相互作用。可以控制参数粒子的个数。这个粒子实现了一种统一数据结构，利用原子操作或者Thrust库的快速基数排序。
9. smokeParticles - Smoke Particles 
   烟雾的光影体积模拟，用CUDA实现的一些先进的算法，使用半张角切片(half-angle slicing)技术。使用CUDA模拟，Thrust库排序，OpenGL渲染。
10. VFlockingD3D10 
    这个是模拟什么大鸟的V型绒毛的(V-shaped flocks by big birds)。。。有GPU和CPU实现版本，使用g去开关这两者。

# Advanced Reference

1. alignedTypes - Aligned Types 
   展示对齐与非对齐结构体之间传输速度
2. c++11_cuda - C++11 CUDA 
   展示CUDA对C++11特性的支持。扫描了输入文件，输出x,y,z,w的。
3. cdpAdvancedQuicksort - Advanced Quicksort (CUDA Dynamic Parallelism) 
   实现了高级的快速排序，使用CUDA Dynamic Parallelism。
4. cdpBezierTessellation - Bezier Line Tessellation (CUDA Dynamic Parallelism) 
   嗯，就是，bezier tessellation of lines这个的实现。什么贝启尔曲线啥的，中文和英文一样看不到 （= = ）
5. cdpLUDecomposition - LU Decomposition (CUDA Dynamic Parallelism) 
   LU分解是一种将非奇异矩阵进行三角分解的方法，然后CUDA模拟一下。
6. cdpQuadtree - Quad Tree (CUDA Dynamic Parallelism) 
   象限四分树(哇哦。。。)
7. concurrentKernels - Concurrent Kernels 
   stream中并行执行多个Kernel，并阐明如何处理CUDA stream之间的依赖。
8. eigenvalues - Eigenvalues 
   算特征值对于线性代数来说十分重要。这个例子实现了一个并行的二分算法，计算一个随机大小的三对角矩阵的特征值。
9. fastWalshTransform - Fast Walsh Transform 
   实现快速沃尔什变换
10. FDTD3d - CUDA C 3D FDTD 
    该样例在3D表面上应用有限差分时域进展模板。(是的你没看错)
11. FunctionPointers - Function Pointers 
    教你怎么使用函数指针并且实现了索贝尔边缘检测。
12. interval - Interval Computing 
    实现区间计算。
13. lineOfSight - Line of Sight 
    视线算法的视线。给定一个高度图和来自一些观察点的射线，计算从观察点沿着光线经过的所有的点。
14. matrixMulDynlinkJIT - Matrix Multiplication (CUDA Driver API version with Dynamic Linking Version) 
    使用CUDA驱动API再次实现矩阵乘法。展示了如何在运行时链接驱动并且即时编译PTX代码。主要也是为了展示CUDA的程序规则而不是优化程序。CUBLAS被用于这个计算。 
    15.mergeSort - Merge Sort 
    实现了归并排序。虽然这种排序在大序列的排序上通常效率较低，但是在中等大小的键值对排序上是个好的选择。
15. newdelete - NewDelete 
    展示在设备上动态new 和 delete空间和声明虚函数。
16. ptxjit - PTX Just-in-Time compilation 
    使用驱动API从PTX即时编译Kernel。并展示了运行时和驱动API互操作性的无缝衔接。对于CUDA5.5，这个例子展示如何使用cuLink*这样的函数链接PTX。
17. radixSortThrust - CUDA Radix Sort (Thrust Library) 
    使用Thrust库进行超级快而且高效并行的基数排序。既可以进行键值对排序也可以只进行键的排序。这个代码使用了线程束同步，依赖于GPU上的线程都属于线程束这个规则，所有的线程都同步地执行。当线程束内的线程访问共享内存时，代码中不用__syncthreads()。对于这种没有竞争条件的操作，想要正确执行必须将共享内存定义为volatile。如果不定义，在缺少__syncthreads()时，编译器会延迟将数据存到共享内存而是保存到寄存器中(编译器的优化措施)，这样会导致错误。因此要主要这方面的应用。
18. reduction - CUDA Parallel Reduction 
    规约。这里有一些优化方法。
19. scalarProd - Scalar Product 
    标量相乘。
20. scan - CUDA Parallel Prefix Sum (Scan) 
    并行前缀和(也称扫描算法)。
21. segmentationTreeThrust - CUDA Segmentation Tree Thrust Library 
    构造图像分割树的方法。基于Boruvka的MST算法。
22. shfl_scan - CUDA Parallel Prefix Sum with Shuffle Intrinsics (SHFL_Scan) 
    如何使用shuffle(线程束混洗)来进行扫描。
23. simpleHyperQ 
    流中多个Kernel并行，并且使用了HyperQ技术([这里竟然有教程](http://blog.csdn.net/langb2014/article/details/51348515#t4))
24. sortingNetworks - CUDA Sorting Networks 
    双调排序奇偶合并排序。虽然这种排序在大序列的排序上通常效率较低，但是在中等大小的键值对排序上是个好的选择。
25. StreamPriorities - Stream Priorities 
    如何使用流。
26. threadFenceReduction 
    使用thread Fence来进行规约。单步规约需要原子操作和_threadfence()指令
27. threadMigration - CUDA Context Thread Management 
    适合使用CUDA上下文管理和使用新的CUDA4.0的参数传递以及CUDA启动API。CUDA上下文可以被分别创建并且独立地和不同的线程连接。
28. transpose - Matrix Transpose 
    矩阵转置。有一些操作用来优化。

# Cudalibraries Reference

1. batchCUBLAS 
   教你怎么使用批量的CUBLAS的API提高程序性能。
2. BiCGStab 
   使用CUSPARSE和CUBLAS对有限的对称和非对称线性系统的稳定双共轭梯度(Bi-Conjugate Gradient Stabilized)迭代方法。
3. boxFilterNPP - Box Filter with NPP 
   如何使用NPP盒式过滤器函数执行盒式过滤。
4. cannyEdgeDetectorNPP - Canny Edge Detector NPP 
   什么边缘检测过滤器。用这个可以把输入图片搞成灰度图片。
5. conjugateGradient - ConjugateGradient 
   使用CUBLAS and CUSPARSE库实现共轭梯度计算
6. conjugateGradientPrecond - Preconditioned Conjugate Gradient 
   使用CUBLAS and CUSPARSE库实现前承条件共轭梯度计算
7. conjugateGradientUM - ConjugateGradientUM 
   使用统一内存和CUBLAS and CUSPARSE库实现共轭梯度计算
8. cuHook - CUDA Interception Library 
   展示如何编译和使用一个截距库。这个库要通过LD_PRELOAD加载。 
   libcuhook.so.1 ./cuHook
9. cuSolverDn_LinearSolver - cuSolverDn Linear Solver 
   实现cuSolverDN的LU, QR和Cholesky因式分解
10. cuSolverRf - cuSolverRf Refactorization 
    重新因子化。
11. cuSolverSp_LinearSolver - cuSolverSp Linear Solver 
    实现cuSolverSP的LU, QR和Cholesky因式分解
12. cuSolverSp_LowlevelCholesky - cuSolverSp LowlevelCholesky Solver 
    使用cuSolverSP底层API实现Cholesky因式分解
13. cuSolverSp_LowlevelQR - cuSolverSp Lowlevel QR Solver 
    使用cuSolverSP底层API实现QR因式分解
14. FilterBorderControlNPP - Filter Border Control NPP 
    如何在常见模式下使用NPP过滤器函数的边缘版本，可以用来备份NPP的相同的无边界版本函数的结果，也可以被用来开关不同原图片边缘的边界控制，这些图片边缘依赖于被作为输入的原图片的部分。(是是是，你说得都对)
15. freeImageInteropNPP - FreeImage and NPP Interopability 
    使用FreeImage库
16. histEqualizationNPP - Histogram Equalization with NPP 
    如何使用NNP把图片数据直方图均值化
17. jpegNPP - JPEG encode/decode and resize with NPP 
    流水线处理图片。首先一个JPEG图片被哈弗曼编码然后被离散余弦转换且去量子化。不同区域被重新调整大小。最后反过来，重新量子化，正向离散余弦转换再哈弗曼解码。
18. MC_EstimatePiInlineP - Monte Carlo Estimation of Pi(inline PRNG) 
    使用蒙特卡罗方法模拟π(内联PRNG)，并使用NVIDIA CURAND库。
19. MC_EstimatePiInlineQ - Monte Carlo Estimation of Pi(inline QRNG) 
    使用蒙特卡罗方法模拟π(内联QRNG)，并使用NVIDIA CURAND库。
20. MC_EstimatePiP - Monte Carlo Estimation of Pi (batch PRNG) 
    使用蒙特卡罗方法模拟π(使用批量PRNG).)，并使用NVIDIA CURAND库。
21. MC_EstimatePiQ - Monte Carlo Estimation of Pi (batch QRNG) 
    使用蒙特卡罗方法模拟π(使用批量RRNG).)，并使用NVIDIA CURAND库。
22. MC_SingleAsianOptionP - Monte Carlo Single Asian Option 
    使用蒙特卡罗方法模拟简单亚式期权，并使用NVIDIA CURAND库。
23. MersenneTwisterGP11213 
    模拟梅森旋转算法，使用cuRAND产生随机数
24. nvgraph_Pagerank - NVGRAPH Page Rank 
    使用NVGRAPH库进行Page Rank
25. nvgraph_SemiRingSpmv - NVGRAPH Semi-Ring SpMV 
    使用NVGRAPH库进行半环向量乘法。
26. nvgraph_SSSP - NVGRAPH Single Source Shortest Path 
    使用NVGRAPH库计算单源最短路径
27. randomFog - Random Fog 
    演示使用CURAND产生伪随机和准随机算法
28. simpleCUBLAS - Simple CUBLAS 
    演示怎么使用最新的CUBLAS库
29. simpleCUBLASXT - Simple CUBLAS XT 
    CUBLAS-XT库使用
30. simpleCUFFT - Simple CUFFT 
    使用CUFFT计算带有过滤的信号的1维卷积，通过将其转换入频域(frequency domain)，使其二者相乘，并重新传回时域。CUFFT计划是产生于简单和高级API的需求的。
31. simpleCUFFT_2d_MGPU - SimpleCUFFT_2d_MGPU 
    这个是用CUFFT计算二维卷积。，并且是多个GPU。
32. simpleCUFFT_callback - Simple CUFFT Callbacks 
    这个也是 使用CUFFT计算带有过滤的信号的1维卷积，通过将其转换入频域(frequency domain)，使其二者相乘，并重新传回时域。不同之处在于，多个步骤是由用户提供的一个CUFFT回调函数实现而不是一个分离的Kernel调用。
33. simpleCUFFT_MGPU - Simple CUFFT_MGPU 
    多GPU的一维卷积。
34. simpleDevLibCUBLAS - simpleDevLibCUBLAS GPU Device API Library Functions (CUDA Dynamic Parallelism) 
    该示例实现了一个简单的CUBLAS函数调用，调用运行CUBLAS函数的GPU设备API库