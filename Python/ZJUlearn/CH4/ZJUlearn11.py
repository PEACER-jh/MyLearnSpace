# B站Python大本营   浙江大学72小时 第四章-函数

"""
函数的返回值:
    函数执行之后，回给调用方的一个结果，即返回值
    函数只要执行到了return，函数会立即停止并返回内容，函数内的return的后续代码不会执行
    1. 如果函数没有return，此时外界收到的时None
    2. 如果写了return：
        1. 只写return，后面不跟数据，此时接收到的依然时None
        2. return 值，此时表示函数有一个返回值，外界能够接收到一个数据
        3. return 值1, 值2, 值3, ……，此时函数有多个返回值，外界收到的时元组，并且元组内存放所有的返回值
"""
def func(a,b):
    print("a+b =",a + b)
    return a + b
ret = func(10, 20)
print("ret =",ret)

def func(a,b):
    print("a+b =",a + b)
    #return a + b   #默认：return None
ret = func(10, 20)
print("ret =",ret)

def func(a,b):
    print("a+b =",a + b)
    return  #让程序停止，后续代码不再继续执行
ret = func(10, 20)
print("ret =",ret)

def func(a,b):
    print("a+b =",a + b)
    return  1,2,3,4
ret = func(10, 20)
print("ret =",ret)
print("ret =",ret[1])