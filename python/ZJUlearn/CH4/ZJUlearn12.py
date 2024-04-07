# B站Python大本营   浙江大学72小时 第四章-函数-内置函数1

"""
内置函数:
    1.反射相关
    2.基础数据类型相关
    3.作用域相关
    4.面向对象相关
    5.迭代器/生成器相关
    6.其他
"""

# 基础数据类型相关

#数据类型
num = '123'
print(int(num))
print(str(num))
print(float(num))
print(bool(num))
print(complex(num))

#进制转换
num = 18
print(bin(num)) #二进制 0b
print(oct(num)) #八进制 0o
print(hex(num)) #十六进制 0x
num_bin = 0b10010
num_oct = 0o22
num_hex  = 0x12
print(int(num_bin))
print(int(num_oct))
print(int(num_hex))

#数学运算
a = 10
b = 30
c = -10
d = 3.1415
lst = [1, 2, 3, 4, 5]
print(abs(c))                   # a的绝对值
print(divmod(a, b))             # 返回(a//b, a%b)
print(round(d)," = ",round(d,0))# 四舍五入至最接近的整数
print(round(d, 2))              # 四舍五入至对应小数位数
print(round(d, -1))             # 对小数点左侧四舍五入
print(pow(a, b), " = ", a**b)   # a的b次方
print(min(a, b, c))             # a、b……的最小值
print(max(a, b, c))             # a、b……的最大值
print(min(lst))                 # 列表最小值
print(max(lst))                 # 列表最大值
print(sum(lst))                 # 列表求和

#数据结构

# 序列-列表 & 元组
s1 = "abc"
lst1 = list(s1)
lst2 = list("123")
print(lst1)
print(lst2)
lst2.reverse()
print(lst2) #反转，并返回None
lst = [1, 2, 3, 4, 5, 6, 7, 8, 9]
s = slice(1, 6, 2)
print(lst[s], " = ", lst[1:6:2])

# 序列-字符串
#format 格式化
a = 18
print(format(a, 'b'))   #二进制
print(format(a, '08b')) #八位二进制数，用0补齐
print(format(a, 'o'))   #八进制
print(format(a, 'x'))   #十六进制
a = "壹"  #python的内存中使用的时Unicode
b = 22777
print(ord(a))   #Unicode编码位置
print(chr(b))   #给出编码位置，展示对应文字
#for i in range(65536):
#    print(chr(i), end=' ')

# 数据集合-字典 & 集合
a = ['a', 'b', 'c', 'd']
fs = frozenset(a)
print(a)

#相关内置函数
lst = ['a', 'b', 'b', 'd', 'e', 'f']
l = len(lst)  #长度
print(l)
print(all([0, '1', '壹']))   # and
print(any([0, '1', '壹']))   # or
for item in enumerate(lst):
    print(item)
for index,item in enumerate(lst, 1):    #index从1开始
    print(index, item)
for i in range(len(lst)):
    print(i, lst[i])

c = "壹"
print(hash(c))  #哈希
print(id(c))    #地址
#print(help(str))
#print(dir(c))