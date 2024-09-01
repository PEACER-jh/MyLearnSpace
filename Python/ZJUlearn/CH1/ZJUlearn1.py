# B站Python大本营   浙江大学72小时 第一章

"""
编程语言分类：
    1.编译型：一次性把源代码进行翻译
        特点：执行效率高，平台依赖性一般比较高
    2.解释型：逐行对源代码进行翻译和运行
        特点：执行效率较低，源代码一般无法加密，平台依赖性不高
python: 1.爬虫 2.自动化 3.科学计算 4.人工智能
"""

# 1.变量
"""
可以发生改变的一个量，变量是用来区分不同数据的，可以用来区分不同的数据的，可以指向一个内存空间，帮助存储一些数据
命名规则: 
        1.必须是数字或字母或下划线组成
        2.不能是数字开头，不能是纯数字
        3.不能使用python的关键字
        4.不要使用中文,不要太长，要有意义
"""
a = "第一个python程序"
b = 188
print("第一个python程序")
print(a)
print(b)

# 2.常量
"""
约定：认为把所有变量的所有字母为大写是常量
"""
PI = 3.14159
print(123)
print(PI)

# 3.数据类型
"""
作用：区分不同的数据，不同的数据类型应有不同的操作
1.数字int \ float 2.字符串str 3.bool.True/False
"""
a = 10  #整数（int）
b = 0.1 #小数（float）
print(a + b)    #运算
s1 = 'a1壹'  #单引号
s2 = "b2贰"  #双引号
s3 = """c
3
叁"""    #三个双/单引号可多行文本
print(s1)
print(s2)
print(s1 + " " + s2)  #字符串加法,连接字符串
print(s1 * 3)         #字符串乘法,重复次数
print(s3)
a = 100 > 30
b = 100 < 30
print(100 > 30, a) #True
print(100 < 30, b) #False

# 4.用户交互
"""
首先屏幕中显示出提示语，用户输入内容，然后把用户输入的内容交给前面的变量
注意：input()得到的结果是一个字符串
若要得到数字类型需要转化
"""
a=10    #a = input("提示语1,a=")
b=20    #b = input("提示语2,b=")
print(a + b)
print(type(a),type(b))  #type()查看数据类型
print("a+b=",int(a) + int(b))  #强制类型转换

# 5.if条件判断
"""
if语句的语法规则：
    if 条件一:
        if 条件1: 
            pass
        elif 条件2:
            pass 
        else:
            pass
    elif 条件二:
        pass  
    else:
        pass
如果条件成立就执行代码,注意缩进关系,
if语句可以相互嵌套,
elif、else不能独立于if单独存在
"""
#=====第一种======
money = 500
if money > 300:
    print("YES")
print("==========")
#=====第二种======
money = 500 #money = int(input("money="))
if money > 300:
    print("YES")
else:
    print("NO")
print("==========")
#=====第三种======
money = 900
if money > 300:
    if money > 500:
        print("YES1")
    else:
        print("YES2")
else:
    print("NO")
print("==========")
#=====第四种======
money = 900
if money > 1000:
    print("YES1")
elif money > 500:
    print("YES2")
else:
    print("NO")

# 6.while循环语句
"""
    while 条件:
        pass
可以重复执行代码
判断条件是否为真，若为真执行代码，然后再次判断条件，直到条件为假推出循环
"""
#while True 死循环
i = 1
sum = 0
while i <= 10:
    print(i)
    sum += i    #累加运算
    i = i + 1
print(sum)

# 7.break和continue
"""
break:让当前这个循环立即停止
continue:停止当前本次循环，继续执行下一次循环
"""
while True:
    a = 10  #a = int(input("a="))
    if a == 10:
        break   #结束循环
    elif a == 0:
        continue    #下一次循环

# 8.for循环语句
"""
#字符串是可迭代的
#计数需要借助于range()
    for 变量 in 可迭代的东西:
        pass
把可迭代的东西中的每一项内容拿出来，挨个地赋值给变量，每一次赋值都要执行一次循环体
"""
s = "abcde"
for c in s:
    print(c)
for i in range(10): #1.rang(n) 从零数到n,不包括n
    print(i)
for i in range(1,10):   #2.rang(m,n) 从m数到n,不包括n
    print(i)
for i in range(1,10,2):   #3.rang(m,n,s) 从m数到n,不包括n,每次间隔为s
    print(i)

#补充：pass
#作用：代码占位