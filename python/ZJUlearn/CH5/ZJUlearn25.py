# B站猿来教育    樵夫教你学Python 第五章-模块

"""
zipfile模块：
    封装了和zip压缩包相关的功能
    1.打包一个压缩包
    2.用程序解压缩
"""
import zipfile
#创建压缩包
f = zipfile.ZipFile('zip/zip_try.zip', mode='w')
f.write('zip/1.txt', '1.txt')
f.write('zip/2.txt', '2.txt')
f.close()
#进行解压缩
f = zipfile.ZipFile('zip/zip_try.zip', mode='r')
#直接全部解压缩
f.extractall('zip/zip_try1')
#逐个解压缩
print(f.namelist())
for name in f.namelist():
    f.extract(name, 'zip/zip_try2')