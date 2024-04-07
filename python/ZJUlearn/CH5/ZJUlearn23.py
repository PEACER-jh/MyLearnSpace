# B站猿来教育    樵夫教你学Python 第五章-模块

"""
logging模块：
    创建日志系统：
    1.导入logging模块
    2.配置一下logging
    3.出现异常的时候(except)，向日志里写错误信息
"""
import logging
# filename : 文件名
# format : 数据的格式化输出，最终在日志文件中的格式
#       时间-名称-级别-模块: 错误信息
# datafmt : 时间的格式
# level :错误的级别权重，当错误的级别权重大于等于level的时候才会写入文件
logging.basicConfig(filename='logging/log_test.txt',
                    format='%(asctime)s - %(name)s - %(levelname)s - %(module)s: %(message)s',
                    datefmt='%Y-%m-%d %H:%M:%S',
                    level=0)    #记入文件中的日志的最低等级

# logging 日志记录
#调整logging.basicConfig中的level等级查看日志记录情况
logging.critical("ERROR! ERROR! ERROR!")  #最高级别的日志信息 50
logging.error("BUG! BUG! BUG!")           #普通的程序错误，俗称bug 40
logging.warning("WARNING! WARNING! WARNING!")   #警告 30
logging.info("MESSAGE! MESSAGE! MESSAGE!")      #消息 20
logging.debug("DEBUG! DEBUG! DEBUG!")     #最低等级的消息 10

#把日志记录在不同的文件中
#创建一个操作日志的对象logger（依赖FileHandler）
file_handler1 = logging.FileHandler('logging/l1.log', 'a', encoding='utf-8')
file_handler1.setFormatter(logging.Formatter(fmt='%(asctime)s - %(name)s - %(levelname)s - %(module)s: %(message)s'))
logger1 = logging.Logger('s1', level=logging.ERROR) #创建日志对象
logger1.addHandler(file_handler1)   #给日志对象设置文件信息
logger1.error('here is system A')
#在创建一个操作日志对象logger（依赖FileHandler）
file_handler2 = logging.FileHandler('logging/l2.log', 'a', encoding='utf-8')
file_handler2.setFormatter(logging.Formatter(fmt='%(asctime)s - %(name)s - %(levelname)s - %(module)s: %(message)s'))
logger2 = logging.Logger('s2', level=logging.ERROR) #创建日志对象
logger2.addHandler(file_handler2)
logger2.error('here is system B')

logger1.error('s1 error!')
logger2.error('s2 error!')
logger1.log(9999, 'custom log')