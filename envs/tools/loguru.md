# Python日志库loguru——轻松记日志，一个函数搞定

⌚️: 2021年08月09日

📚参考

- [官网教程](https://loguru.readthedocs.io/en/stable/index.html)
- https://pythondict.com/life-intelligent/tools/loguru/

---



## 简介

loguru，第三方库，轻松记日志，一个函数搞定。

![在这里插入图片描述](F:\GitHub\README\envs\tools\imgs\20200722160117356.gif)

**Loguru** 一个能彻底解放你的日志记录器。

它即插即用，具备多种方式滚动日志、自动压缩日志文件、定时删除等功能。

除此之外，多线程安全、高亮日志、日志告警等功能也不在话下。

下面就给大家介绍一下这个强大[工具](https://pythondict.com/tag/tools/)的基本使用方法。

Loguru 安装方式很简单，打开终端输入：

```
pip install loguru
```

即可完成安装。



## 初试

无需样板即可使用

```
from loguru import logger

logger.debug('调试消息')
logger.info('普通消息')
logger.warning('警告消息')
logger.error('错误消息')
logger.critical('严重错误消息')
logger.success('成功调用')
```

![在这里插入图片描述](F:\GitHub\README\envs\tools\imgs\20200722160924493.png)





## 添加Handler, Formatter, Filter

无需繁琐地添加，只需要 add()

还原到标准输出 logger.remove()

```
from loguru import logger

print(logger.add('file_{time}.log', format="{name} {level} {message}", level="INFO", rotation='5 MB', encoding='utf-8'))  # 根据时间为日志命名，每5MB新建一个
logger.debug('调试消息')
logger.info('普通消息')
logger.warning('警告消息')
logger.error('错误消息')
logger.critical('严重错误消息')

logger.remove()  # 还原到标准输出
logger.debug('调试消息')
logger.info('普通消息')
logger.warning('警告消息')
logger.error('错误消息')
logger.critical('严重错误消息')
```



产生了新日志文件

![在这里插入图片描述](F:\GitHub\README\envs\tools\imgs\20200722162650332.png)



## 循环、保留、压缩

- 循环，rotation，达到指定大小后建新日志。
- 保留，retention，定期清理。
- 压缩，compression，压缩节省空间。

```
from loguru import logger

logger.add("file_1.log", rotation="500 MB")  # 自动循环过大的文件
logger.add("file_2.log", rotation="12:00")  # 每天中午创建新文件
logger.add("file_3.log", rotation="1 week")  # 一旦文件太旧进行循环

logger.add("file_X.log", retention="10 days")  # 定期清理

logger.add("file_Y.log", compression="zip")  # 压缩节省空间

```


查看[详细配置](https://loguru.readthedocs.io/en/stable/api/logger.html#file)

## 捕获异常

使用catch()装饰器 或 上下文管理器

- 装饰器

```
from loguru import logger


@logger.catch
def func(x, y, z):
    return 1 / (x + y + z)


if __name__ == '__main__':
    func(0, 1, -1)
```

- 
  上下文管理器

```
from loguru import logger


def func(x, y, z):
    return 1 / (x + y + z)


with logger.catch():
    func(0, 1, -1)
```


输出

![在这里插入图片描述](F:\GitHub\README\envs\tools\imgs\20200722164213499.png)



完整描述异常
Loguru允许显示整个堆栈跟踪，包括变量的值（使用了[better-exceptions](https://github.com/Qix-/better-exceptions） ))

添加参数 backtrace=True 和 diagnose=True

```
from loguru import logger

logger.add('out.log', backtrace=True, diagnose=True, encoding='utf-8')  # 注意！可能泄漏敏感数据


def func(a, b):
    return a / b


def nested(c):
    try:
        func(5, c)
    except ZeroDivisionError:
        logger.exception("What?!")


nested(0)
```

![在这里插入图片描述](F:\GitHub\README\envs\tools\imgs\20200722165610228.png)





## 结构化日志

保存为JSON格式，添加参数 serialize=True

```
from loguru import logger

logger.add('json.log', serialize=True, encoding='utf-8')
logger.debug('调试消息')
```


json.log

```
{"text": "2020-07-22 17:14:13.574 | DEBUG    | __main__:<module>:4 - \u8c03\u8bd5\u6d88\u606f\n", "record": {"elapsed": {"repr": "0:00:00.009893", "seconds": 0.009893}, "exception": null, "extra": {}, "file": {"name": "test.py", "path": "D:/code/test/test.py"}, "function": "<module>", "level": {"icon": "\ud83d\udc1e", "name": "DEBUG", "no": 10}, "line": 4, "message": "\u8c03\u8bd5\u6d88\u606f", "module": "test", "name": "__main__", "process": {"id": 104568, "name": "MainProcess"}, "thread": {"id": 86560, "name": "MainThread"}, "time": {"repr": "2020-07-22 17:14:13.574082+08:00", "timestamp": 1595409253.574082}}}
```





通过 bind() 添加额外属性来结构化日志

```
from loguru import logger

logger.add("file.log", format="{extra[ip]} {extra[user]} {message}")
context_logger = logger.bind(ip="192.168.0.1", user="someone")
context_logger.info("Contextualize your logger easily")
context_logger.bind(user="someone_else").info("Inline binding of extra attribute")
context_logger.info("Use kwargs to add context during formatting: {user}", user="anybody")
```



file.log

```
192.168.0.1 someone Contextualize your logger easily
192.168.0.1 someone_else Inline binding of extra attribute
192.168.0.1 anybody Use kwargs to add context during formatting: anybod
```







结合 bind(special=True) 和 filter 对日志进行更细粒度的控制

```
from loguru import logger

logger.add("special.log", filter=lambda record: "special" in record["extra"])
logger.debug("This message is not logged to the file")
logger.bind(special=True).info("This message, though, is logged to the file!")
```



special.log

`2020-07-22 17:06:40.998 | INFO     | __main__:<module>:5 - This message, though, is logged to the file!`



## 时间格式

```
from loguru import logger

logger.add('file.log', format='{time:YYYY-MM-DD HH:mm:ss} | {level} | {message}', encoding='utf-8')
logger.debug('调试消息')
```


file.log

`2020-07-22 17:18:08 | DEBUG | 调试消息`



## 解析器

通常需要从日志中提取特定信息， parse() 可用处理日志和正则表达式。

```
-*- coding: utf-8 -*-

from loguru import logger
from dateutil import parser

logger.add('file.log', format='{time} - {level.no} - {message}', encoding='utf-8')
logger.debug('调试消息')

pattern = r'(?P<time>.*) - (?P<level>[0-9]+) - (?P<message>.*)'  # 带命名组的正则表达式
caster_dict = dict(time=parser.parse, level=int)  # 匹配)

for i in logger.parse('file.log', pattern, cast=caster_dict):
    print(i)
    # {'time': datetime.datetime(2020, 7, 22, 17, 33, 12, 554282, tzinfo=tzoffset(None, 28800)), 'level': 10, 'message': '璋冭瘯娑堟伅'}
```



logger.parse() 没有参数 encoding，本人测试解析中文会乱码





## 异步、线程安全、多进程安全

默认为线程安全，但不是异步或多进程安全的，添加参数 enqueue=True 即可：

`logger.add("somefile.log", enqueue=True)`

协程可用 complete() 等待





## PyCharm日志插件

安装方法：File → Settings → Plugins → Marketplace 搜 Ideolog → Install → Restart

需要根据正则表达式[自定义日志格式](https://github.com/JetBrains/ideolog/wiki/Custom-Log-Formats)，参考：[正则表达式教程](https://github.com/ziishaned/learn-regex/blob/master/translations/README-cn.md)

test.log

```
DEBUG:root:调试信息
INFO:root:普通信息
WARNING:root:警告信息
ERROR:root:错误信息
CRITICAL:root:严重错误信息
2019-12-15 20:17:02 - MainThread - root - DEBUG - DEBUG.
2019-12-15 20:17:02 - MainThread - root - INFO - INFO.
2019-12-15 20:17:02 - MainThread - root - WARNING - WARNING.
2019-12-15 20:17:02 - MainThread - root - ERROR - ERROR.
2019-12-15 20:17:02 - MainThread - root - CRITICAL - CRITICAL.
```


设置格式

![image-20210809173221439](F:\GitHub\README\envs\tools\imgs\image-20210809173221439.png)

![image-20210809173240003](F:\GitHub\README\envs\tools\imgs\image-20210809173240003.png)



## 封装

传入多个参数，一次记日志（str() 换成 repr() 会带上 ''）

```
from loguru import logger

logger.add('{time:YYYY-MM-DD HHmmss}.log', format="{message}", rotation='5 MB', encoding='utf-8')  # 根据时间为日志命名，每5MB新建一个


def info(*args):
    logger.info(' '.join([str(i) for i in args]))


a = ('123', '345', None)
info(*a)
# 123 345 None

```