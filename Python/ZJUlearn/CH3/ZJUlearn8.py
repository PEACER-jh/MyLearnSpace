# B站Python大本营   浙江大学72小时 第三章-运算符

"""
1. 算数运算     + - * / % //
2. 比较运算     > < >= <= == !=
3. 赋值运算     = += -= *= /= %= //=
4. 逻辑运算
              1. and 并且：左右两端同时成立，结果才成立
              2. or  或者：左右两端有一个成立，结果就成立
              3. not 非 ： 非真既假，非假既真
5. 成员运算
              1. in     : 判断A是否在B中出现
              2. not in : 判断A是否不在B中出现
"""

# 1.算数运算
a = 10
b = 3
print(a // b)   #相除取整
print(a % b)    #相除取余
print(a / b)

# 2.比较运算
a = 10
b = 20
print(a == b)
print(a != b)

# 3.赋值运算
a = 10
b = 20
print("a=%d, b=%d" %(a, b))
#temp = a
#a = b
#b = temp
a,b = b,a   #互换（解构）
print("a=%d, b=%d" %(a, b))
a += b  #a = a + b
print(a)
a -= b  #a = a - b
print(a)
a *= b  #a = a * b
print(a)
a /= b  #a = a / b
print(a)
a %= (b-2)  #a = a % (b-2)
print(a)
a //= b     #a= a // b
print(a)

# 4.逻辑运算
print(True and False)
print(True or False or False)
print(not False, not True)
#当and和not同时出现的时候，最好加上括号，不会产生歧义
#运算顺序： 括号 -> not -> and -> or

# 5.成员运算
lst = [1, 2, 3, 4, 5]
print(3 in lst)
print(3 not in lst)