# B站Python大本营   浙江大学72小时 第四章-函数-生成器

"""
生成器：
    生成器的本质就是迭代器

创建生成器的方案：
    1. 生成器函数
    2. 生成器表达式
"""

"""
generator； 生成器
# 生成器函数
    生成器函数中有一个关键字 yield
    生成器函数执行的时候，得到的是生成器，并不会执行函数
yield: 只要函数中出现了yield，它就是一个生成器函数
    作用：1.可以返回数据
         2.可以分段地执行函数中的内容，通过.__next__()可以执行到下一个yield的位置
"""
def func():
    print(123)
    yield 456   # yield 也有返回的作用
ret = func()
print(ret)
ret.__next__()
ret = func()
print(ret.__next__())   # yield 只有执行到next的时候才会返回数据

def func():
    print('AAA')
    yield 'aaa'
    print('BBB')
    yield 'bbb'
ret = func()
print(ret.__next__())
print(ret.__next__())

#大容量数据使用生成器节省内存
def order():
    lst = []
    for i in range(10000):
        lst.append(f"NO.{i+1}")
        if len(lst) == 50:
            yield lst
            lst = []    #清空列表
gen = order()
print(gen.__next__())
print(gen.__next__())

"""
推导式：简化代码
模板：
    1. 列表推导式
        [数据 for循环 if条件判断]
    2. 集合推导式
        {数据 for循环 if条件判断}
    3. 字典推导式
        {key:value for循环 if条件判断}
    没有元组推导式
    (数据 for循环 if条件判断) ——> 生成器表达式
"""
# 列表推导式
lst1 = [i for i in range(1,10,2)]
print(lst1)
lst2 = [i for i in range(10) if i % 2 == 1]
print(lst2)
lst = [f"NO.{i+1}" for i in range(10)]
print(lst)
lst1 = ['a', 'b', 'c', 'd']
lst2 = [item.upper() for item in lst1]
print(lst2)

# 集合推导式
s = {i for i in range(10)}
print(s)

# 字典推导式
lst = ["abc", "def", "ghi", "jkl"]
dic = {i:lst[i] for i in range(len(lst))}
print(dic)

"""
# 生成器表达式
语法规则：
    (数据 for循环 if条件判断)
"""
gen = (i**2 for i in range(5))
print(gen)
print(gen.__next__())
print(gen.__next__())
gen = (i**2 for i in range(5))
for item in gen:
    print(item)
lst = list(gen)
print(lst)      #一次性
gen = (i ** 2 for i in range(5))
lst = list(gen)
print(lst)