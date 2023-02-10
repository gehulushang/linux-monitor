import time
import requests
import json
from threading import Thread
from time import sleep, ctime


url = "http://127.0.0.1:7999/api/test"

rawParams = "{\"role_id\": 1,\"occupation\": \"paladin\",\"camp\": \"alliance\"}"
myParams = {"key":"test","info":"plusroax"}

class TestAgent(object):
    def __init__(self):
        pass

    def func(self, idx, count):
        for i in range(count):
            print('---开始---', 'thread idx: ', idx, ' count: ', i)

            jsonParams = json.dumps(myParams)
            res = requests.post(url=url, json=myParams, params=myParams)
            print(json.loads(res.text))

            print('***结束***', 'thread idx: ', idx, ' count: ', i)

    def post_test(self, concurrence, count):
        start_timestamp = time.time()
        thread_objs = []
        for idx in range(concurrence):
            thread_obj = Thread(target=self.func, args=(idx, count))
            thread_objs.append(thread_obj)
        for obj in thread_objs:
            obj.start()
        for obj in thread_objs:
            obj.join()
        end_timestamp = time.time()
        print(end_timestamp - start_timestamp)

if __name__ == '__main__':
    obj = TestAgent()
    obj.post_test(1, 1)