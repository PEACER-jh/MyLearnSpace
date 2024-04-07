# B站猿来教育    樵夫教你学Python 第五章-模块

"""
hashlib模块:
    MD5:一种不可逆的加密算法
"""
import hashlib
#创建MD5对象
obj = hashlib.md5()
#把要加密的信息传递给obj
obj.update("Aa1壹一".encode("utf-8")) #需要传入字节
#从obj中拿到密文
ret = obj.hexdigest()
print(ret)

#正常默认的加密过程是容易撞库的
#解决撞库的方法：加盐
obj = hashlib.md5(b'djfgklhag') #乱码
obj.update("Aa1壹一".encode("utf-8"))
print(obj.hexdigest())

#实践
def func(salt, str):
    obj = hashlib.md5(salt.encode('utf-8'))
    obj.update(str.encode('utf-8'))
    return obj.hexdigest()
#用户注册：
# usrname = "user"    #usrname = input("用户名：")
# password = "123456"    #password = input("密码：")
# password_md5 = func(usrname, password)  #动态加盐
# f_w = open('hashlib_test.txt', mode='w', encoding='utf-8')
# f_w.write(usrname)
# f_w.write("\n")
# f_w.write(password_md5)
#用户登录：
usrname = "user"    #usrname = input("用户名：")
password = "123456"    #password = input("密码：")
f_r = open('hashlib_test.txt', mode='r', encoding='utf-8')
uname = f_r.readline().strip()
upwd = f_r.readline().strip()
pwd_md5 = func(usrname, password)
if usrname == uname and pwd_md5 == upwd:
    print("SUCCESS!")
else:
    print("FAIL!")

#文件MD5加密
#判断文件的一致性
obj = hashlib.md5(b'abcd')
f = open('hashlib_test.txt', mode='rb')
for line in f:
    obj.update(line)
print(obj.hexdigest())
#当上传文件的时候，首先计算上传文件的MD5，
#用这个值在网盘的数据库中搜索有没有相同的MD5，
#若有，则直接就是已经上传过，已经保存起来了