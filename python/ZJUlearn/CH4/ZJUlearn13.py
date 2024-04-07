# B站Python大本营   浙江大学72小时 第四章-函数下

"""
1. 函数的嵌套
2. 变量的作用域
3. 装饰器
4. 迭代器
5. 生成器
6. 推导式
7. 匿名函数
"""

# 作用域；变量的访问权限
"""
总结：里部可以访问外部，外部不能直接访问到里部
"""
a = 10  #全局变量 -> 全局作用域
print(a)
def func(): #全局函数
    b = 20  #局部变量 -> 局部作用域
    print(a, b)
    def func2():
        print(a + b)
    return b
c = func()
#print(b)
print(c)
def func3():
    func()
func3()

# 函数的嵌套：函数可以嵌套函数
"""
总结：
    1.函数可以作为返回值进行返回
    2.函数可以作为参数进行互相传递
函数名实际上就是一个变量名，都表示一个内存地址
"""
def func1():
    pass
def func2():
    func1()     #函数的调用

def func1():
    def func2():    #函数的嵌套
        print("successful")
    func2()     #局部的定义一般都是在局部自己访问使用的
func1()

def func():
    def inner():
        print(123)
    print(inner)
    return inner    #返回一个函数
a = func()
print(a)
a()

def func():
    print("abc")
FUNC =func
FUNC()

def func1(a):
    print(a)
def func2(a):   #代理模式
    a()
def target():
    print("ABC")
func1(target)
func1(target())
func2(target)   #实参可以是函数

"""
global : 在局部引入全局变量
nonlocal : 在局部引入外层的局部变量
"""
a = 10
def func1():
    a = 20  #创建一个局部变量，并没有改变全局变量中的a
func1()
print(a)
def func2():
    global a    # global 把外面的全局变量引入到局部
    a = 20
func2()
print(a)

def func1():
    a = b = 10
    def func2():
        a = 20
    def func3():
        nonlocal b  # nonlocal 向外找一层，查看是否有该变量，若有则引入；若没有则继续向外层寻找直到全局（不包括全局）
        b = 20
    func2()
    func3()
    print(a, b)
func1()

# 闭包：内层函数对外层函数的局部变量的使用，此时内层函数被称为闭包函数
"""
1. 可以让一个变量常驻于内存
2. 可以避免全局变量被修改
"""
def func():
    a = 10
    def inner():
        nonlocal a
        a += 1
        return a
    return inner
ret = func()
print(ret())
print(ret())