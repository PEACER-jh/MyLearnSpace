# B站猿来教育    樵夫教你学Python 第五章-模块

"""
异常处理
    try:
        pass
    except 错误1 as 变量1:
        pass(1)
    except 错误2 as 变量2:
        pass(2)
    …………
    except Exception as e:
        pass(最终)
    finall：     #不论是否出错都要执行finally
        pass
"""
try:
    print(1/0)
except:
    print("error")

try:
    print(1/0)
except ZeroDivisionError as z:
    print("除数为零")
except FileNotFoundError as f:
    print("文件不存在")
except Exception as e:
    print("系统错误")
finally:
    print("错误1")

try:
    open("Exception Handling", mode='r').read()
except ZeroDivisionError as z:
    print("除数为零")
except FileNotFoundError as f:
    print("文件不存在")
except Exception as e:
    print("系统错误")
finally:
    print("错误2")

try:
    lst = []
    lst.__iter__().__next__()
except ZeroDivisionError as z:
    print("除数为零")
except FileNotFoundError as f:
    print("文件不存在")
except Exception as e:
    print("系统错误")   #万能的错误接收
finally:
    print("错误3")

#程序可以自己抛出异常
def func(a, b):
    if type(a) == int and type(b) == int:
        return a + b
    else:
        raise Exception("ERROR!")   #抛出异常，谁调用的该函数，谁接收该异常
func(10, 20)
# func(1.0, 2.0)

"""
traceback模块：
    
"""
import traceback
try:
    print(1/0)
except:
    print("error")
    print(traceback.format_exc())

#实践
import traceback
import logging
logging.basicConfig(filename='logging/log_traceback.txt',
                    format='%(asctime)s - %(name)s - %(levelname)s - %(module)s: %(message)s',
                    datefmt='%Y-%m-%d %H:%M:%S',
                    level=0)
try:
    print(1/0)
except:
    print("error")
    logging.error(traceback.format_exc())