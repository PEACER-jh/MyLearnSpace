# B站猿来教育    樵夫教你学Python 第五章-模块

"""
shutil模块：
    封装了文件和文件夹的相关操作
    文件复制粘贴、文件移动、文件夹的复制和移动……
"""
import shutil
#文件的移动(先把dir2文件夹中的a.txt文件移动到dir1文件夹中)
#shutil.move('dir1/a.txt', 'dir2')

#文件的复制
#方法一：复制两个文件句柄
f1 = open("dir1/b.txt", mode='rb')
f2 = open("dir1/b_1.txt", mode='wb')
shutil.copyfileobj(f1, f2)
#方法二：执行两个文件路径，进行文件的复制(复制文件的内容)
shutil.copyfile('dir1/b.txt', 'dir1/b_2.txt')   #参数是文件路径
#方法三：复制文件内容和文件权限
shutil.copy('dir1/b.txt', 'dir1/b_3.txt')
#方法四：复制文件内容、文件权限和修改时间
shutil.copy2('dir1/b.txt', 'dir1/b_4.txt')
#方法五：修改时间、文件权限的复制，不复制内容
shutil.copystat('dir1/b.txt', 'dir1/b_5.txt')
#方法六：只复制文件权限
shutil.copymode('dir1/b.txt', 'dir1/b_6.txt')

#文件夹的复制(先把dir3文件夹删除)
shutil.copytree('dir1', 'dir3')

#文件夹的删除(先创建一个dir4文件夹)
shutil.rmtree('dir4')