# B站Python大本营   浙江大学72小时 第二章-dict字典

# 6.字典1
"""
特点：字典是以键值对的形式进行存储数据的
表示方式：{key1:value, key2:value, key3:value,……}
"""
dic = {1:'a', 2:'b', 3:'c'}
val = dic[2]    #[key]索引,来查询相应的value
print(val)
#字典的key必须是可哈希的数据类型
#字典的value可以是任何的数据类型

# 字典2：增删改查
dic = dict()    #方法一
dic = {}        #方法二
print(dic)
#=====向字典中添加内容=====
dic[1] = "a"
dic.setdefault("abc", "ABC")    #设置默认值，若之前已经有了某一key,则.setdefault就不起作用
print(dic)
#=====向字典中修改内容=====
dic[1] = 'A'    #当字典中已存在某一key,此时执行修改操作
dic.setdefault("abc", "abc")
print(dic)
#=====向字典中删除内容=====
dic.pop("abc")  # .pop(key) 删除字典中key所对应的元素
print(dic)
#=====向字典中查询内容=====
print(dic[1])       #如果key不存在，程序会报错
print(dic.get(1))   #如果key不存在，程序返回None
ret = dic.get(2)
if ret is None:
    print(ret, type(ret))

# 字典3：循环和嵌套
dic = {1:'a', 2:'b', 3:'c', 4:'d'}
#==========循环==========
#可以通过for循环取得key
for key in dic:
    print(key, dic[key])
#把字典中所有的key全部保存在一个列表中
print(dic.keys())
print(list(dic.keys()))
#把字典中的所有value全部保存在一个列表中
print(dic.values())
print(list(dic.values()))
#直接取得字典中的key和value
print(dic.items())
print(list(dic.items()))

for item in dic.items():    #item = (key, value) 元组
    key = item[0]
    value = item[1]
    #key, value = item   #解构(解包)：元组或者列表都可以执行，
    print(item,key,value)
for key,value in dic.items():
    print(key, value)

#==========嵌套==========
person = {
    "name" : "li4",
    "age"  : 20,
    "wife" : {
        "name" : "zhang3",
        "age"  : 18,
        "friend" : {
            "name" : "wang2",
            "age"  : 19,
            "hobby": "soccer"
        }
    },
    "childern" : [
        {"name":"child1", "age":7},
        {"name":"child2", "age":8},
        {"name":"child3", "age":9},
    ]
}
ret = person["wife"]["friend"]["age"]
print(ret)
person["childern"][1]["age"] = person["childern"][1]["age"] + 1
print(person)

# 字典4：循环删除（示例）
dic = {
    "赵四":"123",
    "刘能":"456",
    "大脚":"789",
    "大脑袋":"+-*/"
}
temp = []   #准备一个临时列表，负责存储要删除的内容
print(dic)
for key in dic:
    if key.startswith("大"):
        temp.append(key)
        #dic.pop(key)    报错：dictionary changed size during iteration
for t in temp:  #循环列表，删除字典中的内容
    dic.pop(t)
print(dic)