# B站猿来教育    樵夫教你学Python 第五章-模块

"""
pickle模块：
    1. .load    把文件中的字节反序列化成对象
    2. .loads   把字节转化为对象（数据）
    3. .dump    把对象序列化成字节之后写入文件
    4. .dumps   把对象（数据）转化为字节
序列化：把对象转化为二进制字节
反序列化：把二进制字节转化为对象
"""
import pickle
lst1 = ['A', 'B', 'C']
bs1 = pickle.dumps(lst1)
print(bs1)
bs2 = b'\x80\x04\x95\x11\x00\x00\x00\x00\x00\x00\x00]\x94(\x8c\x01A\x94\x8c\x01B\x94\x8c\x01C\x94e.'
lst2 = pickle.loads(bs2)
print(lst2)

dic = {'A':'a', 'B':'b'}
f = open("data_error.txt", mode="w", encoding="utf-8")
f.write(str(dic))
f = open("data_error.txt", mode="r", encoding="utf-8")
s = f.read()
print(s, type(s))

dic = {'A':'a', 'B':'b'}
pickle.dump(dic, open("date_right.txt", mode="wb"))
dic = pickle.load(open("date_right.txt", mode="rb"))
print(dic, type(dic))

"""
json模块：
一种来自于前端的数据交互的数据格式
    1. .dumps   可以把对象转化为json
    2. .loads   可以把json转化为对象
    ensure_ascii=False
    3. .dump    
    4. .load    
"""
import json
# 1.把python中的字典或者列表，转化成json字符串
dic = {'A':'a', 'B':'b', 'C':'c', "中文":"参数"}
s1 = json.dumps(dic)
s2 = json.dumps(dic, ensure_ascii=False)    #json处理中文需要加 ensure_ascii=False
print(s1, type(s1))
print(s2, type(s2))
# 2.前端返回的json字符串，需要转化成python中的字典
s = '{"A":"a", "壹":"一"}'    #注意单双引号的使用
d = json.loads(s)
print(d, type(d))
#前端json和python中的字典的区别：
#数据类型的写法不同：
    #   python    前端
    #1.  True     true
    #2.  False    false
    #3.  None     null
dic = {"A":1, "B":True, "C":False, "D":None}
print(json.dumps(dic))
#返回：{"A": 1, "B": true, "C": false, "D": null}

#列表的转化
lst = ["123", "abc", "一二三", True]
s = json.dumps(lst, ensure_ascii=False)
print(s, type(s))

dic1 = {"A":"壹", "B":"b", "C":3}
json.dump(dic1, open('date2.txt', mode="w", encoding="utf-8"), ensure_ascii=False)
dic2 = json.load(open('date2.txt', mode="r", encoding="utf-8"))
print(dic2, type(dic2))