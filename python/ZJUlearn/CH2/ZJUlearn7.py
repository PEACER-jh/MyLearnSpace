# B站Python大本营   浙江大学72小时 第二章-bytes字节串

"""
1.字符集和编码
    ASCII码：编排了128个文字符号，只需要7个0和1就可以表示
            01111111 ——> 1byte ——> 8bit
    ANSI标注：每个字符占用16bit=2byte
            00000000 01111111
    GB2312（中国） ——> gbk编码（windows默认,16bit,2byte） ——> gb18030
    big5（中国台湾）
    JIS（日本）
    Unicode 万国码
    UTF 是可变长度的Unicode，可以进行数据的传输和存储
        UTF-8 最短的字节长度为8bit,1byte（mac默认）
        UTF-16 最短的字节长度为16bit,2byte
"""

"""
2.编码和解码
    bytes
        所有数据的最终单位都是字节byte
    1. str.enconde("编码")    进行编码
    2. bytes.deconde("编码")  进行解码
"""
s = "你好python"
bs1 = s.encode("gbk")       #bytes类型
bs2 = s.encode("utf-8")     #bytes类型
print(bs1)  #英文可以正常显示
print(bs2)  #英文可以正常显示
print("=================")
bs = b'\xc4\xe3\xba\xc3python'
s = bs.decode("gbk")
bs2 = s.encode("utf-8")
print(s)
print(bs2)