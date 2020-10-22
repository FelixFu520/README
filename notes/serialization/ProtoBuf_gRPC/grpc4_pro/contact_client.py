import logging
import random
import threading
import time

import grpc
import contact_pb2
import contact_pb2_grpc


# 接收服务端发送过来的任务
def get_task(stub):
    try:
        for task in stub.getTask(contact_pb2.Empty()):
            print(f"客户端已接收到服务端任务：{task.task}\n")
            # 顺便再告诉服务端我已经接收到你发的任务，你不用担心我没接收到它
            yield contact_pb2.Result(
                ret=f"客户端接收到任务:{task.task}"
            )
    except Exception as e:
        print(f'err:{e}')
        return
        
# 客户端再通知服务端我接收到你的消息了
def tell_result(stub):
    result = get_task(stub)
    stub.tellResult(result)
    
def run():
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = contact_pb2_grpc.ContactStub(channel)
        while True:
            try:
                threading.Thread(target=send_status, args=(stub,), daemon=True).start()
                tell_result(stub)
                print("OK")
            except grpc.RpcError as e:
                print(f"server connected out, please retry:{e.code()},{e.details()}")
            except Exception as e:
                print(f'unknown err:{e}')
                print("ERROR!!")
            finally:
                time.sleep(2)


if __name__ == '__main__':
    run()


