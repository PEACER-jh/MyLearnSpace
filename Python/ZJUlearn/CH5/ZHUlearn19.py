# B站猿来教育    樵夫教你学Python 第五章-模块

"""
模块：
    1. time模块
    2. ⭐datetime模块
    3. ⭐random模块
    4. 序列化-pickle模块
    5. ⭐序列化-json模块
    6. ⭐hashilib模块
    7. shutil模块
    8. ⭐logging模块 -- 异常处理、traceback
    9. zipfile模块
    10. re模块 -- 正则表达式
    11. os模块
    12. sys模块
"""

# time
import time             #导入一个模块整体
time.sleep(0.1)
from time import sleep  #从一个模块中导入一个具体的功能
sleep(0.1)
# sleep() 可以暂停执行一段时间
# time()  可以计算时间差
print(time.time())  #返回结果：时间戳
start = time.time()
for i in range(100000):
    i = i
end = time.time()
print(end - start)

# datetime
from datetime import datetime   #年月日 时分秒
from datetime import date       #年月日
from datetime import time       #时分秒
print(datetime.now())   #打印当前时间
print(datetime(2024, 2, 10, 0, 22, 30)) #创建一个时间
t1 = datetime(2005, 3, 29)
t2 = datetime(2024, 2, 10)
diff = t2 - t1
print(diff)
print(diff.total_seconds())

#格式化一个时间
t = datetime.now()
print(t)
print(t.strftime("%Y年(%y年)%m月%d日 %H小时%M分钟%S秒")) #把时间格式化成一个字符串

#输入两个时间计算时间差
s1 = "2005-03-29 00:00:00"    #s1 = input("第一个时间(YYYY-MM--DD HH:MM:SS)：")
s2 = "2024-02-10 00:00:00"    #s2 = input("第二个时间(YYYY-MM--DD HH:MM:SS)：")
#把输入的字符串转化成时间
t1 = datetime.strptime(s1, "%Y-%m-%d %H:%M:%S")
t2 = datetime.strptime(s2, "%Y-%m-%d %H:%M:%S")
print(t2 - t1)

print(date.today())
print(date(2024, 2, 10))

# random
import random
print(random.random())            #(0, 1)
print(random.uniform(5, 9)) #随机小数字
print(random.randint(3, 8)) #随机整数（能取得边界）

lst = ['A', 'B', 'C', 'D']
print(random.choice(lst))          #随机选择一个
print(random.sample(lst, 2))    #随机选择一部分

#练习：随机生成四位验证码
def rand_num():
    return str(random.randint(0, 9))
def rand_upper():
    return chr(random.randint(65, 90)) #ASCII码转换对应的大写字母
def rand_lower():
    return chr(random.randint(97, 122))
def rand_verify_code(n=4):
    lst = []
    for i in range(4):
        which = random.randint(1, 3)
        if which == 1:
            s = rand_num()
        elif which == 2:
            s = rand_upper()
        elif which == 3:
            s = rand_lower()
        lst.append(s)
    return "".join(lst)
print(rand_verify_code())