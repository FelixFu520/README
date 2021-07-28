# Horovod安装

⌚️: 2020年8月9日

📚参考

---

[官网教程](https://horovod.readthedocs.io/en/latest/gpus.html)



参考官方，我用的是ubuntu系统、nccl是使用本地安装的，选择horovod的安装方式如下，



```
HOROVOD_GPU_OPERATIONS=NCCL pip install --no-cache-dir horovod

root@node01:~# HOROVOD_GPU_OPERATIONS=NCCL pip install --no-cache-dir horovod
DEPRECATION: Python 3.5 reached the end of its life on September 13th, 2020. Please upgrade your Python as Python 3.5 is no longer maintained. pip 21.0 will drop support for Python 3.5 in January 2021. pip 21.0 will remove support for this functionality.
Requirement already satisfied: horovod in /usr/local/lib/python3.5/dist-packages (0.19.5)
Requirement already satisfied: cloudpickle in /usr/local/lib/python3.5/dist-packages (from horovod) (1.6.0)
Requirement already satisfied: psutil in /usr/local/lib/python3.5/dist-packages (from horovod) (5.7.2)
Requirement already satisfied: pyyaml in /usr/local/lib/python3.5/dist-packages (from horovod) (5.3.1)
Requirement already satisfied: six in /usr/lib/python3/dist-packages (from horovod) (1.10.0)
Requirement already satisfied: cffi>=1.4.0 in /usr/local/lib/python3.5/dist-packages (from horovod) (1.14.3)
Requirement already satisfied: pycparser in /usr/local/lib/python3.5/dist-packages (from cffi>=1.4.0->horovod) (2.20)

```



```
pip list

root@node01:~# pip list
DEPRECATION: Python 3.5 reached the end of its life on September 13th, 2020. Please upgrade your Python as Python 3.5 is no longer maintained. pip 21.0 will drop support for Python 3.5 in January 2021. pip 21.0 will remove support for this functionality.
Package             Version
------------------- ----------------------
cffi                1.14.3
chardet             2.3.0
cloudpickle         1.6.0
command-not-found   0.3
horovod             0.19.5
language-selector   0.1
numpy               1.18.5
Pillow              7.2.0
pip                 20.2.3
psutil              5.7.2
pycparser           2.20
pycurl              7.43.0
pygobject           3.20.0
python-apt          1.1.0b1+ubuntu0.16.4.2
python-debian       0.1.27
python-systemd      231
PyYAML              5.3.1
requests            2.9.1
setuptools          20.7.0
six                 1.10.0
ssh-import-id       5.5
torch               1.2.0
torchvision         0.4.0
ufw                 0.35
unattended-upgrades 0.1
urllib3             1.13.1
wheel               0.29.0
root@node01:~# 

```

