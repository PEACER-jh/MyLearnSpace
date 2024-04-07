# B站Python大本营   浙江大学72小时 第四章-函数

"""
函数的概念：
    对某一个特定的功能或者代码块进行封装
    在需要使用该功能时直接调用即可
定义：
    def 函数的名字():
        被封装的功能或者代码块 ——> 函数体
调用：
    函数的名字()
意义：让程序简洁，代码更加合理
"""
def func():     #定义函数
    print("123")
    print("abc")
    print("ABC")
func()

"""
函数的参数：
    可以在函数调用的时候，给函数传递一些信息
    1.形参：在函数定义的时候，需要准备一些变量来接受信息
    2.实参：实际在调用的时候传递的信息  
"""
def func(name, num):           #形参
    print("%s = %d" % (name, num))
func("wang2", 18)   #实参

"""
实参：
    1.位置参数：  按照位置进行参数传递
    2.关键字参数：按照参数的名字进行参数传递
    3.混合参数：  位置参数在前面，关键字参数在后面
#实参在执行的时候，必须保证形参有数据
"""
def func(A, B, C, D):
    print(A, B, C, D)
func(1, 2, 3, 4)    #位置参数
func(A=1, C=2, D=3, B=4)        #关键字参数
func(1, 2, D=3, C=4)      #混合参数

"""
形参：
    1.位置参数：按照位置一个一个地去声明变量
    2.默认值参数：在函数声明的时候给变量一个默认值，如果实参不传递信息，此时默认值生效
        (声明函数时默认值参数放在位置参数后面)
    3.动态传承：
        1. *args : 表示接收所有的位置参数的动态传参
        2. **kwargs: 表示接收所有的关键字参数的动态传参 
混合使用时的定义顺序，可以随意搭配使用：
    位置 ——> *args位置动态参数 ——> 默认值参数 ——> **kwargs关键字动态参数
"""
def func(name, age, gender="male"):
    print(name, age, gender)
func("小明", 17)
func("小红", 18, "female")

def func(*num):     # * 表示位置参数的动态传参，接收到的值为被统一放在一个元组里
    print(num)
func(1, 2, 3)
func(1, 2, 3, 4, 5)

def func(**letter):     # ** 表示接收关键字的动态传参，接收到的值会被处理为字典
    print(letter)
func(A='a', B='b')
func(A='a', B='b', C='c', D='d')

def func(a, b, *args, DV="default value", **kwargs):
    print(a, b, args, DV, kwargs)
func('A', 'B', 1,2,3, DV="DV", 一='壹',二='贰')
func('A', 'B', 1,2,3, 一='壹',二='贰')

def func(*args, **kwargs):  #没有限制地接收任何参数
    print(args, kwargs)
func()
func(1, 2, 3)
func(α='a', β='b', θ='c')
func(1,2,3, α='a',β='b',θ='c')

lst = ['a', 'b', 'c', 'd', 'e', 'f']
dct = {'A':'a', 'B':'b', 'C':'c'}
def func(*args, **kwargs):
    print(args, kwargs)
func(lst)
func(*lst)      # *  在实参位置把列表分解成位置参数进行传递
func(dct)
func(**dct)     # ** 在实参位置把字典分解成关键字参数进行传递