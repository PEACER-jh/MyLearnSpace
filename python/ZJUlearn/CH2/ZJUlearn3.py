# B站Python大本营   浙江大学72小时 第二章-list列表

# 3.列表1：概念
"""
在python中用 [] 来表示一个列表
列表中的元素通过 , 隔开
特性：
    1.于字符串一样也有索引和切片
    2.列表的索引若超过范围会报错
    3.可以用for循环进行遍历
    4.用 len() 取得列表的长度
    5.重点：列表的“增删改查”
"""
a = ["abc", 123, [123, True]]
lst = ["abc", "def", "ghi", "jkl"]
print(lst[0])     #索引
print(lst[1:3])   #切片
print(lst[::-1])
#print(lst[114514])
for item in lst:     #可以用for循环进行遍历
    print(item)
print(len(lst))

# 列表2：增删改查
lst = []
#=====向列表中添加内容=====
#1. .append() 在列表的最后追加
lst.append("abc")
lst.append(123)
lst.append([1,2,3])
print(lst)
#2. .insert(index, object)  在列表的index位置插入object
lst.insert(0, "a1壹")
print(lst)
#3. .extend([lst2]) 合并两个列表
lst.extend(["sin", "cos", "tan"])
print(lst)
#=====向列表中删除内容=====
#1. .pop(index) 将列表的index位置的数据删除并返回
ret = lst.pop(3)
print(lst)
print(ret)
#2. .remove(object) 删除列表中的object元素
lst.remove("a1壹")
print(lst)
#=====向列表中修改内容=====
#直接使用索引就可以进行修改操作
lst[1] = "123"
print(lst)
#=====向列表中查询内容=====
#直接使用索引就可以进行查询操作
print(lst[3])

#练习
name_list = ["赵敏","张绍刚","赵本山","张无忌","武则天","嬴政","马超"]
print(name_list)
#for item in name_list:
for i in range(len(name_list)): #len(lst)得到列表的长度——>可以直接拿到列表索引的for循环
    item = name_list[i]
    #print(item)
    if item.startswith("张"):
        name_new = "王" + item[1:]
        #print(name_new)
        name_list[i] = name_new
    i = i + 1
print(name_list)

# 补充
# 1.排序
lst = [1, 2, 3, "abc", "def"]   #列表会按照存放的顺序来保存
print(lst)
lst = [159, 454, 548, 659, 812, 217]
print(lst)
lst.sort()  #升序排序
print(lst)
lst.sort(reverse=True)  #降序排序
print(lst)

# 2.嵌套
lst = ["abc", ['d','e','f',[1,2,3]], "ghi", "jkl"]
print(lst[1][3][1])
lst[1][1] = lst[1][1].upper()
print(lst)

# 3.列表的循环删除（示例）
name_list = ["赵敏","张绍刚","张无忌","武则天","嬴政","马超"]
temp = []   #准备一个临时列表，负责存储要删除的内容
print(name_list)
for item in name_list:
    if item.startswith("张"):
        temp.append(item)   #把要删除的内容记录下来
        #lst.remove(item)   #直接在原列表remove会导致删除不净
for item in temp:
    name_list.remove(item)
print(name_list)