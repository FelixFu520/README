# 基于IB网卡（Infiniband）OpenMPI集群搭建

2020年10月10日

----

## 一、准备工作

**实验设备**：两台塔式服务器
**操作系统**：Ubuntu16.04 STL
**IP配置**：
192.168.50/33.11 node01

192.168.50/33.12 node02


**相关软件**：IB网卡驱动（驱动安装方式详见[这篇文章](ib.md)） 

## 二、在每个节点安装OpenMPI

### 2.1 下载OpenMPI

在官网上[下载](https://www.open-mpi.org/software/ompi/v4.0/)安装包这里使用，

### 2.2 解压并进行配置

```bash
root@node01:~# ls
data  HorovodInstall  main.py  openmpi-4.0.0.tar.gz
root@node01:~# tar zxvf openmpi-4.0.0.tar.gz

root@node01:~# cd openmpi-4.0.0/

root@node01:~/openmpi-4.0.0# ./configure --enable-mca-no-build=btl-uct --prefix="/usr/local/openmpi"

```

**注意**：最后一行是将其安装到 /usr/local/openmpi目录下，可以指定为其他目录。

### 2.3 Build并安装

```bash
make -j #开启多核编译，j可以跟数字例如：make -j8。
```

> 踩坑1: 
>
> 在编译过程中，可能会出现下面的错误
>
> ```
> make[2]: Leaving directory '/root/openmpi-4.0.0/opal'
> Making all in mca/common/sm
> make[2]: Entering directory '/root/openmpi-4.0.0/opal/mca/common/sm'
>   CC       common_sm.lo
>   CC       common_sm_mpool.lo
>   LN_S     libmca_common_sm.la
>   CCLD     libmca_common_sm.la
> make[2]: Leaving directory '/root/openmpi-4.0.0/opal/mca/common/sm'
> Making all in mca/common/ucx
> make[2]: Entering directory '/root/openmpi-4.0.0/opal/mca/common/ucx'
>   CC       libmca_common_ucx_la-common_ucx.lo
>   LN_S     libmca_common_ucx.la
>   CCLD     libmca_common_ucx.la
> /usr/bin/ld: cannot find -lnuma
> collect2: error: ld returned 1 exit status
> Makefile:1912: recipe for target 'libmca_common_ucx.la' failed
> make[2]: *** [libmca_common_ucx.la] Error 1
> make[2]: Leaving directory '/root/openmpi-4.0.0/opal/mca/common/ucx'
> Makefile:2378: recipe for target 'all-recursive' failed
> make[1]: *** [all-recursive] Error 1
> make[1]: Leaving directory '/root/openmpi-4.0.0/opal'
> Makefile:1896: recipe for target 'all-recursive' failed
> make: *** [all-recursive] Error 1
> 
> ```
>
> 解决：
>
> ```
> apt install libnuma-dev
> make clean
> make -j32
> ```
>
> 
>
> 踩坑2:
>
> 有些人编译可能出错，注意，UCX可能存在不匹配，报错如下：
>
> ```bash
> btl_uct_module.c: In function ‘mca_btl_uct_reg_mem’:
> btl_uct_module.c:214:22: error: ‘UCT_MD_MEM_ACCESS_REMOTE_GET’ undeclared (first use in this function)
>          uct_flags |= UCT_MD_MEM_ACCESS_REMOTE_GET;
>                       ^
> btl_uct_module.c:214:22: note: each undeclared identifier is reported only once for each function it appears in
> btl_uct_module.c:217:22: error: ‘UCT_MD_MEM_ACCESS_REMOTE_PUT’ undeclared (first use in this function)
>          uct_flags |= UCT_MD_MEM_ACCESS_REMOTE_PUT;
>                       ^
> btl_uct_module.c:220:22: error: ‘UCT_MD_MEM_ACCESS_REMOTE_ATOMIC’ undeclared (first use in this function)
>          uct_flags |= UCT_MD_MEM_ACCESS_REMOTE_ATOMIC;
>                       ^
> btl_uct_module.c:225:21: error: ‘UCT_MD_MEM_ACCESS_ALL’ undeclared (first use in this function)
>          uct_flags = UCT_MD_MEM_ACCESS_ALL;
> 
> 
> ```
>
> 此时，需要关闭UCX(见https://github.com/open-mpi/ompi/issues/6640)：
>
> ```
> $ ./configure --enable-mca-no-build=btl-uct
> ```
>
> 或者
>
> 先安装[UCX](https://www.mellanox.com/products/ucx)|[github](https://github.com/openucx/ucx)。安装方法见：
>
> https://github.com/openucx/ucx

```
make install
```



### 2.4 添加环境变量

```bash
vim ~/.bashrc
```

在文件中添加

```bash
#openmpi properties
export PATH=$PATH:/usr/local/openmpi/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/openmpi/lib
```

保存后执行

```bash
source ~/.bashrc
ldconfig
```

### 2.5 测试是否安装成功

```bash
mpirun
```

如下图所示表示成功

```
root@node01:~/openmpi-4.0.0# mpirun --allow-run-as-root --help
mpirun (Open MPI) 4.0.0

Usage: mpirun [OPTION]...  [PROGRAM]...
Start the given program using Open RTE

-c|-np|--np <arg0>       Number of processes to run
   -gmca|--gmca <arg0> <arg1>  
                         Pass global MCA parameters that are applicable to
                         all contexts (arg0 is the parameter name; arg1 is
                         the parameter value)
-h|--help <arg0>         This help message
   -mca|--mca <arg0> <arg1>  
                         Pass context-specific MCA parameters; they are
                         considered global if --gmca is not used and only
                         one context is specified (arg0 is the parameter
                         name; arg1 is the parameter value)
   -n|--n <arg0>         Number of processes to run
-q|--quiet               Suppress helpful messages
-v|--verbose             Be verbose
-V|--version             Print version and exit

For additional mpirun arguments, run 'mpirun --help <category>'

The following categories exist: general (Defaults to this option), debug,
    output, input, mapping, ranking, binding, devel (arguments useful to OMPI
    Developers), compatibility (arguments supported for backwards compatibility),
    launch (arguments to modify launch options), and dvm (Distributed Virtual
    Machine arguments).

Report bugs to http://www.open-mpi.org/community/help/
```

## 三、实现各节点SSH免密登录

### 3.1 网络环境配置

分别配置两台机器的hosts文件，在此之前先通过ifconfig命令查看两台机器的IP地址，我的IP地址为：
node01：192.168.50/33.11
node02：192.168.50/33.12
然后修改hosts文件：

```bash
vim /etc/hosts

eg.
127.0.0.1       localhost
192.168.50.16   ubuntu

# The following lines are desirable for IPv6 capable hosts
::1     localhost ip6-localhost ip6-loopback
ff02::1 ip6-allnodes
ff02::2 ip6-allrouters

192.168.33.11 node01
192.168.33.12 node02

```

将下面两行写入hosts文件中

> 192.168.33.11 node01
> 192.168.33.12 node02

此时，两个节点间应该可以互相ping通

### 3.2 SSH免密登录

第一步：在本地机器上使用`ssh-keygen`产生公钥私钥对

```bash
root@node01:~# ssh-keygen
Generating public/private rsa key pair.
Enter file in which to save the key (/root/.ssh/id_rsa): 
Created directory '/root/.ssh'.
Enter passphrase (empty for no passphrase): 
Enter same passphrase again: 
Your identification has been saved in /root/.ssh/id_rsa.
Your public key has been saved in /root/.ssh/id_rsa.pub.
The key fingerprint is:
SHA256:sYRzvHtgw9CxHJA79JKfhFsyL7zEMguVh2POeBRDQ3E root@node01
The key's randomart image is:
+---[RSA 2048]----+
|   o=.Eoo        |
|    ooo= +       |
|     *+=O        |
|    B X*++       |
|   B = @S.       |
|  o * *.++       |
|   o = o. .      |
|    . .  .       |
|                 |
+----[SHA256]-----+
```

第二步：用ssh-copy-id将公钥复制到远程机器中

```bash
ssh-copy-id -i ~/.ssh/id_rsa.pub remote-host

eg.
在node01上执行，node02上同理

root@node01:~# ssh-copy-id -i ~/.ssh/id_rsa.pub node02
/usr/bin/ssh-copy-id: INFO: Source of key(s) to be installed: "/root/.ssh/id_rsa.pub"
The authenticity of host 'node02 (192.168.33.12)' can't be established.
ECDSA key fingerprint is SHA256:iOyc/Y0I1gE+3CdgQlnLCo6foFoiCVsgKoEMhsGITqw.
Are you sure you want to continue connecting (yes/no)? yes
/usr/bin/ssh-copy-id: INFO: attempting to log in with the new key(s), to filter out any that are already installed
/usr/bin/ssh-copy-id: INFO: 1 key(s) remain to be installed -- if you are prompted now it is to install the new keys
root@node02's password: 

Number of key(s) added: 1

Now try logging into the machine, with:   "ssh 'node02'"
and check to make sure that only the key(s) you wanted were added.

root@node01:~# ssh-copy-id -i ~/.ssh/id_rsa.pub node01
/usr/bin/ssh-copy-id: INFO: Source of key(s) to be installed: "/root/.ssh/id_rsa.pub"
The authenticity of host 'node01 (192.168.33.11)' can't be established.
ECDSA key fingerprint is SHA256:drbk1u9kSEE63gFrYKKBm7SB23iSiwUhbBxLqlrMago.
Are you sure you want to continue connecting (yes/no)? yes
/usr/bin/ssh-copy-id: INFO: attempting to log in with the new key(s), to filter out any that are already installed
/usr/bin/ssh-copy-id: INFO: 1 key(s) remain to be installed -- if you are prompted now it is to install the new keys
root@node01's password: 

Number of key(s) added: 1

Now try logging into the machine, with:   "ssh 'node01'"
and check to make sure that only the key(s) you wanted were added.

```

第三步：登录到远程机器不用输入密码

```bash
ssh remote-host
```

**注意：**
（1）每个节点都要操作这些步骤
（2）不仅要能免密登录其它节点，而且还要免密登录自己

## 四、建立和挂载NFS共享目录（这个我不需要，所以没做）

1、在所有节点中建立相同路径下的相同目录：

```bash
sudo mkdir /home/mpi_share
```

2、在所有节点安装NFS

```bash
sudo apt-get install nfs-kernel-server
```

3、在所有节点配置NFS服务器

```bash
sudo gedit /etc/exports
```

打开文件后，在文件的最后附件上所有同步的客户端的ip和权限，如下：

> /home/mpi_share 10.0.0.1 (rw,sync,no_root_squash,no_subtree_check)
> /home/mpi_share 10.0.0.2 (rw,sync,no_root_squash,no_subtree_check)

其中/home/mpi_share是共享目录，ip地址是所有的客户端（其它节点）的地址，包括本机的，后面括号中的是权限，具体含义可上网查阅（rw即读写权限）。
4、在其中一个节点启动NFS服务器

```bash
sudo /etc/init.d/nfs-kernel-server restart
```

5、在其余节点挂载NFS服务器

```bash
sudo mount -t nfs 10.0.0.2:/home/mpi_share /home/mpi_share
```

- 如果想开机自动挂载：把上述指令`sudo mount -t nfs 10.0.0.2:/home/mpi_share /home/mpi_share` 写到 /etc/rc.local 文件中）。
- 如果想要卸载共享文件夹：使用`sudo umount -lf /home/mpi_share` 卸载。
- 注意是`/home/mpi_share`不是`/home/mpi_share/` 没有最后的斜杠。

6、测试NFS
在NFS服务器端的共享目录建立一个文件sudo gedit test.c并保存，几秒钟后检查其他节点中是否在共享目录中产生了该文件，若产生则配置成功。

## 五、集群环境执行MPI程序

我们在共享文件夹里添加一个MPI代码（cpi.c）代码和配置文件hostfile如下：
**1. 编写mpi代码（cpi.c）**

```bash
sudo gedit /home/mpi_share/cpi.c
```

**<<cpi.c>>**

```c
#include "mpi.h"
#include <stdio.h>
#include <math.h>

double f(double);

double f(double a)
{
    return (4.0 / (1.0 + a * a));
}

int main(int argc, char *argv[])
{
    int n, myid, numprocs, i;
    double PI25DT = 3.141592653589793238462643;
    double mypi, pi, h, sum, x;
    double startwtime = 0.0, endwtime;
    int namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Get_processor_name(processor_name, &namelen);

    fprintf(stdout, "Process %d of %d is on %s\n", myid, numprocs, processor_name);
    fflush(stdout);

    n = 1000000000;  /* default # of rectangles */
    if (myid == 0)
        startwtime = MPI_Wtime();

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    h = 1.0 / (double) n;
    sum = 0.0;
    /* A slightly better approach starts from large i and works back */
    for (i = myid + 1; i <= n; i += numprocs) {
        x = h * ((double) i - 0.5);
        sum += f(x);
    }
    mypi = h * sum;

    MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (myid == 0) {
        endwtime = MPI_Wtime();
        printf("pi is approximately %.16f, Error is %.16f\n", pi, fabs(pi - PI25DT));
        printf("wall clock time = %f\n", endwtime - startwtime);
        fflush(stdout);
    }

    MPI_Finalize();
    return 0;
}
```

**2. 编写hostfile配置文件**

```bash
sudo gedit /home/mpi_share/hostfile 
```

**<< hostfile >>**

```c
node01 slots=4
node02 slots=4
```

**3. 编译并运行MPI程序**

```bash
cd /home/mpi_share/        #进入共享目录

mpicc cpi.c -o cpi            #编译cpi.c代码为cpi

/usr/local/openmpi/bin/mpirun -n 8 -hostfile hostfile ./cpi          #执行cpi

```

> 踩坑2
>
> 注意：有的读者说使用mpirun -n 8 -hostfile hostfile ./cpi会报如下错。
>
> ```bash
> bash: orted: 未找到命令
> --------------------------------------------------------------------------
> ORTE was unable to reliably start one or more daemons.
> This usually is caused by:
> 
> * not finding the required libraries and/or binaries on
>   one or more nodes. Please check your PATH and LD_LIBRARY_PATH
>   settings, or configure OMPI with --enable-orterun-prefix-by-default
> 
> * lack of authority to execute on one or more specified nodes.
>   Please verify your allocation and authorities.
> 
> * the inability to write startup files into /tmp (--tmpdir/orte_tmpdir_base).
>   Please check with your sys admin to determine the correct location to use.
> 
> *  compilation of the orted with dynamic libraries when static are required
>   (e.g., on Cray). Please check your configure cmd line and consider using
>   one of the contrib/platform definitions for your system type.
> 
> * an inability to create a connection back to mpirun due to a
>   lack of common network interfaces and/or no route found between
>   them. Please check network connectivity (including firewalls
>   and network routing requirements).
> 
> ```
>
> 解决方案：
>
> 1. 每台节点上在终端上输入`sudo ldconfig`。
> 2. 检查～/.bashrc文件中PATH和 LD_LIBRARY_PATH路径是否正确。
>
> ```bash
>    #openmpi properties
>    export PATH=$PATH:/usr/local/openmpi/bin
>    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/openmpi/lib
> ```
>
> 1. 使用mpirun的完整路径即
>
> ```bash
>    /usr/local/openmpi/bin/mpirun -n 8 -hostfile hostfile ./cpi
> ```

运行结果如下，我们发现两个节点都各启动了四个进程

```
root@node01:~/data# /usr/local/openmpi/bin/mpirun  --allow-run-as-root -n 8 -hostfile hostfile ./cpi
--------------------------------------------------------------------------
By default, for Open MPI 4.0 and later, infiniband ports on a device
are not used by default.  The intent is to use UCX for these devices.
You can override this policy by setting the btl_openib_allow_ib MCA parameter
to true.

  Local host:              node01
  Local adapter:           mlx4_0
  Local port:              1

--------------------------------------------------------------------------
--------------------------------------------------------------------------
WARNING: There was an error initializing an OpenFabrics device.

  Local host:   node01
  Local device: mlx4_0
--------------------------------------------------------------------------
Process 0 of 8 is on node01
Process 3 of 8 is on node01
Process 1 of 8 is on node01
Process 2 of 8 is on node01
Process 5 of 8 is on node02
Process 7 of 8 is on node02
Process 4 of 8 is on node02
Process 6 of 8 is on node02
pi is approximately 3.1415926535898278, Error is 0.0000000000000346
wall clock time = 0.764424
[node01:10901] 7 more processes have sent help message help-mpi-btl-openib.txt / ib port not selected
[node01:10901] Set MCA parameter "orte_base_help_aggregate" to 0 to see all help / error messages
[node01:10901] 7 more processes have sent help message help-mpi-btl-openib.txt / error in device init
```



## 参考

> https://blog.csdn.net/weixin_42819452/article/details/102592740
>
> https://blog.csdn.net/weixin_42819452/article/details/102952976