# -*- coding: utf-8 -*-
"""
Created on Mon Jan 16 09:33:29 2017

@author: ranjiewen
"""

#import sys
#reload(sys)
#sys.setdefaultencoding('utf8')
##把 str 编码由 ascii 改为 utf8 (或 gb18030)


#python 基础语法
print "hello world!"

if True:
    print "True"
else:
    print "False"
    
total = 'item_one' + \
        'item_two' + \
        'item_three'
        
days=['Monday','Tuesday','Wednesday',
      'Thursday','Friday']
      
word='word'
sentence="这是一个句子"
paragrah=""" 这是一个段落。
包含多个语句"""

#raw_input("\nPress the enter  key to exit.")

#import sys; x='runoob'; sys.stdout.write(x+'\n')
#import sys
#print '参数个数为：',len(sys.argv),'个参数。'
#print '参数列表：',str(sys.argv)

##python 变量类型
#counter =100 #复制整型变量
#miles=1000.0 #浮点型
#name='John'  #字符串
#print miles
##多个变量赋值
#a=b=c=1
#a,b,c=1,2,"John"


#str = 'Hello World!'
#print str           # 输出完整字符串
#print str[0]        # 输出字符串中的第一个字符
#print str[2:5]      # 输出字符串中第三个至第五个之间的字符串
#print str[2:]       # 输出从第三个字符开始的字符串
#print str * 2       # 输出字符串两次
#print str + "TEST"  # 输出连接的字符串


#list=['runoob',768,2.23,'John',70.2]
#tinylist=[123,'John']
#print list
#print list[0]
#print list[1:3]
#print list[2:]
#print list+tinylist 

#元组用"()"标识。内部元素用逗号隔开。但是元组不能二次赋值，相当于只读列表。
tuple=('runoob',786,2.23,'John',70.2)
tinytuple=(123,'john')
# 列表是有序的对象结合，字典是无序的对象集合。
dict={}
dict['one']="This is one"
dict[2]="This is two"
tinydict={'name':"John",'code':6734,'dept':'sales'}

print dict['one']
print dict[2]
print tinydict
print tinydict.keys()
print tinydict.values()















