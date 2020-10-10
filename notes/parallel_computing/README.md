# 分布式

- 🍀[分布式介绍](introduce.md)
- 🍀[MPI概念介绍](mpi.md)
- 🍀





### 🍀Horovod搭建过程

♨️[整体日志](all.md)

1. [IPMI配置](ipmi.md)  

2. [Ubuntu16.04 Server安装](serverinstall.md)

3. [Ubuntu16.04 配置IP](ip.md)

4. [Ubuntu16.04 修改APT源](apt.md)

5. [Ubuntu16.04 安装NVIDIA驱动](driverinstall.md) 【一、安装440版本，可根据需求调换版本】

6. [Ubuntu16.04 安装CUDA，cuDNN](cudainstall.md)【二、安装cuda10.2 和cudnn7.6.5，可根据需求调换版本】

7. [Ubuntu16.04安装nccl](https://docs.nvidia.com/deeplearning/nccl/install-guide/index.html#debian)|[测试](https://github.com/NVIDIA/nccl-tests)【三、安装nccl 2.6.4，可根据需求调换版本，apt-cache madison】

8. [Pytorch多机多卡](https://github.com/FelixFu520/Parallel-Pytorch)【四、测试多机多卡，先测试无RDMA的。需安装torch 1.2   torchvision0.4.0】

9. [装安IB驱动](ib.md)【五、装IB，加速IB卡之间的RDMA】

10. [Pytorch多机多卡](https://github.com/FelixFu520/Parallel-Pytorch)【六、再次跑多机多卡程序，与四的效果对比】

11. [安装NV_Peer_Memory](nv_peer_memory.md)【七、安装nv_peer_memory, 加速GPURDMA】

12. [Pytorch多机多卡](https://github.com/FelixFu520/Parallel-Pytorch)【八、再次跑多机多卡程序与四、六对比】

13. [安装OpenMPI](openmpi.md)【九、安装OpenMPI，为Horovod做准备】

14. [安装Horovod](horovod.md)【十、安装Horovod，并测试程序，与四、六、八对比】

15. [Ubuntu16.04 安装Docker](docker.md)【十一、安装Docker】

16. [Ubuntu16.04 安装NVIDIA Docker](nvdocker.md)【十二、安装NV-Docker】

17. [在Docker中运行Horovod](all.md)【十三、在Docker中运行Horovod】

    

