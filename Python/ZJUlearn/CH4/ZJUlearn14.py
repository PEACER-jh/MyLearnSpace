# B站Python大本营   浙江大学72小时 第四章-函数-装饰器

"""
回顾：
    1. 函数可以作为参数进行传递
    2. 函数可以作为返回值进行返回
    3. 函数名称可以当作变量进行复制操作
"""
def func1():
    print("abc123")
def func2(fu):
    fu()
func2(func1)

def func():
    def inner():
        print("abc123")
    return inner
ret = func()
ret()

def func1():
    print("Aa1")
def func2():
    print("Bb2")
func1 = func2
func1()

"""
装饰器：
    装饰器本质上是一个闭包
    作用：在不改变原有函数调用的情况下，给函数增加新的功能
    1. 用户登录
    2. 日志
    3. …………
装饰器模板：
    def wrapper(func):  #wrapper:装饰器 func:目标函数
        def inner(*args, **kwargs):
            #在目标函数之前……
            ret = func(*args, **kwargs)  #执行目标函数
            #在目标函数之后……
            return ret
        return innner   #返回内层函数
    
    @wrapper
    def terget():
        pass
        
    target()
        
return inner()  #此处错误，该句返回的是内存函数返回的结果
"""
# 1
def manage(func):
    def inner():
        print("OPEN")
        func()
        print("CLOSE")
    return inner
def func1():        #功能性函数
    print("Aa1")
def func2():        #功能性函数
    print("Bb2")
func1 = manage(func1)   #把原来的函数重新封装，再替换原来的函数
func1()
func2 = manage(func2)
func2()

# 2
def manage(func):
    def inner():
        print("OPEN")
        func()
        print("CLOSE")
    return inner
@manage
def func1():        #功能性函数
    print("Cc3")
@manage
def func2():        #功能性函数
    print("Dd4")
func1()
func2()

"""
被装饰函数的参数问题
"""
def manage(func):
    def inner(*args, **kwargs):     #inner函数添加了参数，args是一个元组，kwargs是一个字典
            # */** 表示接收所有参数，打包成元组和字典
        print("OPEN")
        func(*args, **kwargs)
            # */** 表示把args元组和kwargs字典打散成位置参数和关键字参数传递进去
        print("CLOSE")
    return inner
@manage
def func1(usrname, passward):
    print("usrname:%s passward:%s : Cc3" %(usrname, passward))
@manage
def func2(usrname, passward, gender):
    print("usrname:%s passward:%s gender:%s : Dd4" %(usrname, passward, gender))
func1('usr1', '123456')
func2('usr2', '654321', 'men')

"""
装饰器的返回值问题
"""
def manage(func):
    def inner(*args, **kwargs):
        print("OPEN")
        ret = func(*args, **kwargs)   #目标函数的执行，能够取得从目标函数返回的返回值
        print("CLOSE")
        return  ret
    return inner
@manage
def func1(usrname, passward):
    print("usrname:%s passward:%s : Cc3" %(usrname, passward))
    return "func1 successfully work"       #函数返回值
@manage
def func2(usrname, passward, gender):
    print("usrname:%s passward:%s gender:%s : Dd4" %(usrname, passward, gender))
    return "func2 successfully work"        #函数返回值
ret1 = func1('usr1', '123456')
print(ret1)
ret2 = func2('usr2', '654321', 'men')
print(ret2)

"""
一个函数被多个装饰器修饰
"""
def wrapper1(func):
    def inner(*args, **kwargs):
        print("wrapper1 successfully open")
        ret = func(*args, **kwargs)   #目标函数的执行，能够取得从目标函数返回的返回值
        print("wrapper1 successfully close")
        return  ret
    return inner
def wrapper2(func):
    def inner(*args, **kwargs):
        print("wrapper2 successfully open")
        ret = func(*args, **kwargs)
        print("wrapper2 successfully close")
        return  ret
    return inner
@wrapper1   # target1 = wrapper1(wrapper2.inner) ——> target1 : wrapper1.inner
@wrapper2   # target1 = wrapper2(target1)        ——> target1 : wrapper2.inner
def target1(usrname, passward):
    print("usrname:%s passward:%s : Cc3" %(usrname, passward))
    return "target1 successfully work"
ret1 = target1('usr1', '123456')
print(ret1)
@wrapper2   # target2 = wrapper2(wrapper1.inner) ——> target2 : wrapper2.inner
@wrapper1   # target2 = wrapper1(target2)        ——> target2 : wrapper1.inner
def target2(usrname, passward):
    print("usrname:%s passward:%s : Cc3" %(usrname, passward))
    return "target2 successfully work"
ret2 = target2('usr1', '123456')
print(ret2)

# 练习
login_flag = False
def login_verify(func):
    def inner(*args, **kwargs):
        global login_flag
        if not login_flag:
            print("……登录校验……")
            while True:
                usrname =      input("  账号：")
                password = int(input("  密码："))
                if usrname=="usr" and password==123456:
                    print("登录成功！")
                    login_flag = True
                    break
                else:
                    print("登录失败！")
        ret = func(*args, **kwargs)
        return ret
    return inner

@login_verify
def add():
    print("添加员工信息")
@login_verify
def delete():
    print("删除员工信息")
@login_verify
def update():
    print("修改员工信息")
@login_verify
def search():
    print("查询员工信息")

add()
update()