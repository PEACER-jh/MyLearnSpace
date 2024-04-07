# B站Python大本营   浙江大学72小时 第四章-函数-迭代器

"""
回顾：
    for 变量 in 可迭代：
        pass
"""
for c in str(123):
    print(c)

"""
iterable: 可迭代
iterator: 迭代器
可迭代：
    str, list, tuple, dict, set, open()文件, ……
    可迭代的数据类型都会提供迭代器， 可以把数据类型中的所有数据逐一取得
获取迭代器的方案：
    1. iter() 内置函数可直接取得迭代器
    2. .__iter__() 
从迭代器中取得数据：
    1. next() 内置函数
    2. .__next__()
for里面一定是要拿迭代器，所有不可迭代的东西不能用for循环
"""
it = iter("abcd")
print(it)
print(next(it))
print(it.__next__())
#StopIteration: 迭代已经停止，不可以再从迭代器中拿取数据
it = "ABCD".__iter__()
print(it)
print(next(it))
print(it.__next__())

# 模拟for循环的工作原理：
s = "1234"
it = iter(s)    # it = s.__iter__()
while 1:
    try:
        data = it.__next__()   # data = next(it)
        print(data)     #for循环的循环体
    except StopIteration:   #检测错误及其原因，终止循环
        break

"""
总结：迭代器统一了所有不同数据类型的遍历工作

补充：
    1.迭代器本身也是可以迭代的
    2.迭代器的特性：
        （1）只能向下拿取，不能反复
        （2）节省内存
        （3）惰性机制
"""
s = "abcd"
it = s.__iter__()
for i in it:
    print(i)