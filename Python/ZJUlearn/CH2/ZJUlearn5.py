# B站Python大本营   浙江大学72小时 第二章-set集合

# 5.集合1
"""
特点：set集合是无序的，用 {}
"""
s1 = {}
s2 = {1, 2, "abc", 3}
print(s1, s2)
print(type(s1), type(s2))   #当{}中没有数据时数据类型为dict字典

#s = {1, 2, "abc", 3, []}   TypeError:unhashable type: 'list'
"""
不可哈希：
    python中的set集合进行数据存储的时候
    需要对数据进行哈希计算，根据计算出来的哈希值进行存储数据
    set集合要求存储的数据必须是可以进行哈希计算的
    可变的数据类型（list, dict, set）
可哈希：
    不可变的数据类型（int, float, str, tuple, bool）
"""

# 集合2：增删改查
s = set()       #创建空集合
t = tuple()     #创建空元组
l = list()      #创建空列表
s = str()       #创建空字符串

s = set()
#=====向集合中添加内容=====
s.add("abc")
s.add(123)
s.add(1.23)
s.add((1,2,3))
s.add(False)    #集合添加
print(s)
#=====向集合中删除内容=====
s.pop() #集合删除，无索引，弹出最后一位,由于集合无序，测试的时候无法验证是最后一个
print(s)
s.remove(123)   #集合删除
print(s)
#=====向集合中修改内容=====
#先删除，再新增
s.remove('abc')
s.add('ABC')
print(s)
#=====向集合中查询内容=====
#通过for循环来查找
for item in s:
    print(item)

# 补充：交集、并集、差集
s1 = {"abc", "def", "ghi"}
s2 = {"ABC", "def", "123"}
print(s1 & s2)  #交集
print(s1.intersection(s2))  #交集
print(s1 | s2)  #并集
print(s1.union(s2))         #并集
print(s1 - s2)  #差集（仅s1有）
print(s2 - s1)  #差集（仅s2有）
print(s1.difference(s2))    #差集（仅s1有）
print(s2.difference(s1))    #差集（仅s2有）

#集合中不会出现重复的元素
#作用：去除重复
lst = ["abc", "abc", "abc", "def", "ghi"]
print(lst)
print(list(set(lst)))   #去除重复之后的数据是无序的