# B站Python大本营   浙江大学72小时 第三章-文件操作

"""
1.找到对应文件，并打开
    open(文件路径, mode="", encoding="")
        文件路径：
            1.绝对路径
            2.相对路径（相对于当前程序的文件夹）
"""
f = open("txt/zju9.txt", mode='r', encoding='utf-8')
content = f.read()  #全部读取
print(content)

"""
mode=
        1. r : read读取
"""
f = open("txt/zju9.txt", mode='r', encoding='utf-8')
line = f.readline().strip()    #第一次读取第一行,去除字符串左右两端的空白符
print(line)
line = f.readline()   #第二次读取第二行，文件内部隐藏有换行符
print(line)
line = f.readline()   #第…次读取第…行
print(line)
content = f.readlines()
print(content)
f = open("txt/zju9.txt", mode='r', encoding='utf-8')
for line in f:  #从文件中读取到每一行数据
    print(line.strip())
f.close()

"""
mode=
        2. w : write写入
    w模式下，如果文件不存在，会自动创建一个文件
    w模式下，每一次open都会清空掉文件中的内容
"""
f = open("txt/zju9.2.txt", mode='w', encoding='utf-8')
f.write("1234567")
f.close()   #关闭文件
#练习：准备一个列表，把列表中的每一项内容写入到文件中
lst = ["123", "abc", "ABC"]
f = open("txt/zju9.2.txt", mode='w', encoding='utf-8')
for item in lst:
    f.write("%s \n" %item)
f.close()

"""
mode=
        3. a : append追加
"""
f = open("txt/zju9.3.txt", mode='a', encoding='utf-8')
#f.write("123 \n")
#f.write("ABC \n")
#f.write("abc \n")
f.close()

"""
with：上下文，不需要手动去关闭一个文件
不需要f.close()
"""
with open("txt/zju9.txt", mode='r', encoding='utf-8') as f:
    for line in f:
        print(line.strip())

"""
#读取图片
#读写非文本文件时要加上b
mode=
        4. b : bytes读写的是非文本文件
"""
with open("txt/2024月历/1.jpg", mode='rb') as p:
    for line in p:
#       print(line)
        pass

"""
#文件的复制
#从源文件中读取内容，写入到新路径去
"""
with open("txt/2024月历/1.jpg", mode='rb') as p1, \
    open("txt/新一月.jpg", mode="wb") as p2:   # \ 表示前后两行代码是同一行代码(python为解释型)
    for line in p1:
        p2.write(line)

"""
#文件的修改
#将连并修改内容写入新的文件中，写完之后覆盖源文件
"""
with open("txt/zju9.4.txt", mode='r', encoding='utf-8') as f1, \
    open("txt/zju9.4_$.txt", mode='w', encoding='utf-8') as f2:
    for line in f1:
        line = line.strip() #去空白符
        if line.startswith("王"):
            line = line.replace("王", "wang")    #修改
        f2.write("%s \n" %line) #写入副本
import os   #引入和操作系统相关的模块
import time #引入和时间相关的模块
time.sleep(3)
os.remove("txt/zju9.4.txt") #删除源文件
time.sleep(3)
os.rename("txt/zju9.4_$.txt", "txt/zju9.4.txt") #把副本文件重命名成源文件