# B站Python大本营   浙江大学72小时 第四章-函数-递归

"""
递归：
    函数自己调用自己
递归如果没有任何东西拦截的话，它默认就是一个死循环,会超过最大的递归深度
python默认的递归深度是有限制的，默认的最大递归深度是1000
"""
import sys
print(sys.getrecursionlimit())
sys.setrecursionlimit(2000)
print(sys.getrecursionlimit())

def func():
    print(123)
    func()

# 三元表达式
a = 10
b = 20
c = a if a > b else b
print(c)