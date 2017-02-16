
# coding: utf-8

#python文件I/O
#打印到屏幕
print "python is a new language."
#读取键盘输入
str=raw_input("raw_input请输入：");
print "输入的内容是：",str;

str=input("input请输入：");
print "你输入的内容为",str;

#打开一个文件
fp=open("foo.txt",'w+');
print "文件名：",fp.name;
print "是否已经关闭:",fp.closed;
print "访问模式：",fp.mode
print "末尾是否强制加空格：",fp.softspace

fp.write("www.baidu.com \nranjiewwen.github.com \n");
fp.close();

#文件读写效果的预计的不一样，可能是文件读写方式造成的，读写分开试试
fp=open("foo.txt","r+")
str=fp.read(8);
print "读取的字符串是：",str
position=fp.tell();
print "当前文件位置：",position

position=fp.seek(0,0) #重新定位到开始
str=fp.read(10);
print "重新读取字符串：",str

fp.close()

import os
os.rename("foo.txt","foo1.txt")
#os.renames("foo1.txt","foo2.txt")
os.remove("foo1.txt")
os.mkdir("test_python_file")
os.rmdir("test_python_file")
os.chdir("F:/")
os.mkdir("test_python_file")
os.rmdir("test_python_file")
print os.getcwd()

#python异常处理
try:
    fh=open("testfile.txt","w")
    fh.write("这是一个测试文件，用于测试异常！")
except IOError:
    print "Error: 没有找到文件。"
else:
    print "文件读取成功！"
    fh.close()

def temp_convert(var):
    try:
        return int(var)
    except ValueError,Argument:
        print "参数没有包含数字\n",Argument

temp_convert(6.3)

# 定义函数
def mye(level):
    if level < 1:
        raise Exception("Invalid level!", level)
        # 触发异常后，后面的代码就不会再执行

try:
    mye(0)   # 触发异常
except "Invalid level!":
    print 1
else:
    print 2