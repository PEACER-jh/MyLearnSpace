# B站Python大本营   浙江大学72小时 第四章-函数-匿名函数、内置函数2

"""
匿名函数：
    lambda表达式
    语法：
        变量 = lambda 参数1, 参数2,…… : 返回值
"""
def func1(a, b):
    return a + b
ret1 = func1(10, 20)
print(func1)
print(ret1)

func2 = lambda a, b : a + b
print(func2)
ret2 = func2(10, 20)
print(ret2)

"""
内置函数
"""
# 数据结构相关
# zip
lst1 = ['A', 'B', 'C', 'D']
lst2 = [1, 2 ,3, 4]
lst3 = ['a', 'b', 'c', 'd']

result = []
for i in range(len(lst1)):
    fir = lst1[i]
    sec = lst2[i]
    thr = lst3[i]
    result.append((fir, sec, thr))
print(result)

result = zip(lst1, lst2, lst3)
lst = list(result)
print(lst)

result = zip(lst1, lst2, lst3)
print(result)
for item in result:
    print(item)

# 作用域相关
# locals & globals
"""
locals : 函数会以字典的类型返回当前位置的所有局部变量
globals ： 函数以字典的类型返回所有的全局变量
"""
a = 10
print(locals()) #此时locals被写在了全局作用域范围内，此时看到的就是全局作用域中的内容
def func1():
    b = 20
    print(locals()) #此时locals被放在局部作用域范围，看到的就是局部作用域的内容
func1()
print(globals())    #globals看到的是全局作用域中的内容
def func2():
    c = 30
    print(globals())
func2()

# 和数据结构相关
# sorted 排序
lst = [16, 50, 87, 51, 31]
s1 = sorted(lst)
print(s1)
s2 = sorted(lst, reverse=True)    # reverse 翻转
print(s2)

lst = ["aaaaa", "bb", "cccccccc", "d"]
def func(item):
    return len(item)
# func = lambda item : len(item)
s1 = sorted(lst, key=func)   # key 排序函数(不能加括号)
print(s1)
s2 = sorted(lst, key=lambda i : len(i), reverse=True)
print(s2)

# filter 筛选
lst = ["a12", "a34", "a56", "b78", "b90"]
f1 = filter(lambda i : i.startswith('a'), lst)
f2 = filter(lambda i : not i.startswith('a'), lst)
print(f1, f2)
print(list(f1))
print(list(f2))

# map 映射
lst = [1, 2, 3, 4, 5, 6, 7, 8, 9]
res1 = [i**2 for i in lst]
print(res1)
res2 = map(lambda i : i*i, lst)
print(res2)
print(list(res2))