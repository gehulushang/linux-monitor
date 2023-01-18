import time
import requests
import json
url = "http://127.0.0.1:7999/api/test"

rawParams = "{\"role_id\": 1,\"occupation\": \"paladin\",\"camp\": \"alliance\"}"
myParams = {"key":"test","info":"plusroax"}
print(myParams)
# print(rawParams)
jsonParams = json.dumps(myParams)
print(jsonParams)

print(time.time())
res = requests.post(url=url, json=myParams, params=myParams)
print(time.time())
print('url:',res.request.url)
print("response:",res.text)
print(json.loads(res.text))
resJson = json.loads(res.text)
print(resJson['result'])