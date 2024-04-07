# B站Python大本营   浙江大学72小时 第二章-int、float、bool、str字符串

"""
python基础数据类型：
    int 整数, float 浮点数, bool 布尔
    str 字符串
    list 列表
    tuple 元组
    set 集合
    dict 字典
    bytes 字节串
    运算符
    文件操作
"""

# 1.int, float, bool
"""
int:整数
float:浮点数
bool:布尔值，用来做条件判断的，只有True和False
    1.非零的数字都是True，零是False
    2.所有的非空字符串都是True，空字符串是False   
"""
#基础数据类型之间的转换
a = "10"
print(type(a))  #字符串
b = int(a)
print(type(b))  #整型
c = bool(a)
print(type(c))  #布尔型
print(bool(" "))
print(bool(""))
print(bool([0]))

# 2.字符串1：字符串格式化
"""
%s:字符串占位(万能：整数、浮点数)
%d:整数占位
%f:浮点数占位
"""
name = "hjh"    #name = input("名字：")
age = 15    #age = int(input("年纪："))
s1 = "我叫%s, 今年%d了" % (name, age)            #方案一（只有一个数据可省略括号）
s2 = "我叫{}, 今年{}了".format(name, age)  #方案二
s3 = f"我叫{name}, 今年{age}了"                  #方案三（f-string)
print("我叫%s，今年%d了" % (name, age))
print(s1)
print(s2)
print(s3)

# 字符串2：索引和切片
""""
索引：按照位置提取元素
切片：从一个字符串中提取一部分内容
s[start:end:step]   从start(从0开始)切到end(取不到end)，每step个取出一个元素
"""
s = "abcdefghijklmn"
print(s[3])     #从0开始
print(s[-1])    #表示倒数地
print(s[2:5])   #s[n:m] 从索引n位置进行切片，切到且不包括m（前闭后开）
print(s[:5])    #若n=0为开头可省略
print(s[5:])    #若m为结尾可省略
print(s[-3:-1]) #倒数从左往右切
print(s[::-1])  #添加步长-1，使从右往左切，若没有步长则默认为1
print(s[::3])   #添加步长

# 3.字符串2：字符串常规操作
"""
字符串的操作一般不会对原字符串产生影响，一般是返回一个新的字符串
"""
#字符串2.1：字符串大小写转换
s = "python"
s0 = s.capitalize() #首字母大写
print(s0)
s = "i am learning python"
s0 = s.title()  #句子每个单词首字母大写
print(s0)
s = "PYTHON"
s0 = s.lower()  #全部变成小写
print(s0)
s = "python"
s0 = s.upper()  #全部变成大写
print(s0)

#字符串2.2：切割和替换
s = "   ab cdef df   "
s0 = s.strip()  #去掉字符串两端的空白符（空格, \t, \n)
print(s0)
s0 = s.replace(" ", "") #字符串替换.replace(old, new)
print(s0)
s = "python_java_c_c++_c#_javascript"
s0 = s.split("_")   #字符串切割.split("切割位置"),切割之后的结果会放在列表中，用什么切就会损失什么
print(s0)

#字符串2.3：查找和判断
s = "abc,def,ghi"
ret = s.find("def") #查找.find("查找内容"),放回查找对象的位置,若为-1则没有该字符串
print(ret)
ret = s.index("def")    #查找.index("查找内容"),若没有则直接报错
print(ret)
print("def" in s)   #in 可以做条件上的判断
print("123" in s)   #存在返回True,不存在返回False
print("def" not in s)
print("123" not in s)
s = "python"
if s.startswith("p"): #首字母判断
    print("YES")
if s.endswith("n"):   #末字母判断
    print("YES")
s = "123456"
if s.isdigit(): #整型判断
#if isinstance(int(s), int):
    money = int(s)
    print("YES %d" %money)
s = "123.456"
if isinstance(float(s), float): #浮点数判断
    money = float(s)
    print("YES %.3f" %money)

#补充: len(), join()
s = "abcde"
length = len(s)   #求取字符串长度
print(length)
lst = ["abc", "def", "ghi"]
s = "_".join(lst)   #将列表中的字符串按"拼接内容"连接
print(s)

"""
总结：
    1.f"{变量}"   f-string格式化字符串
    2.索引和切片：
        索引：从0开始，[]
        切片：s[start: end: step]  end位置的数据永远取不到
    3.相关操作：
        字符串操作对原字符串是不发生改变的
        1. .upper() 在需要忽略大小写的时候
        2. .strip() 可以去掉字符串两端的空白符（空格, \t, \n)
        3. .replace(old, new) 字符串替换
        4. .split("切割位置") 对字符串进行切割
        5. "拼接内容".join(list) 拼接一个列表中的内容成为新的字符串
        6. .startwhith(), .endwith()
    4.字符串的循环和遍历
        for c in s:
            print(c)    #遍历字符串中的每一个字符
    5.关于 in：
        1.判断a是否在A中出现
        2.for循环
"""