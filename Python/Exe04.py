
# coding: utf-8

var1 = 1
var2 = 10
del var1

#var3=ceil(4.3)
var3='hello world!'
var4='Python Rundo!'

print 'var1[0]:',var3[0]
print 'var2[1:5]:',var4[1:5]

var5='hello world!'
print '更新字符串：-',var5[:6]+'Runoob'

a='hello'
b='python'
print a+b

print 'H' in a
print 'M' not in a
print  r'\n'
print 'my name is %s and weight is %d kg!' % ('derrick',52)

'''
python  三引号 triple quotes
'''
print u'hello world!'
list1 = ['physics','chemistry',1997,2000]
print 'list1[1:5]',list1[1:3]
list1[2]=2001
print list1
print len(list1)
print min(list1)

#python 元组
tup1=('physics','chemistry','1997','2001')
tup2=(1,2,3,4,5,6,7)
print "tup1[0]:",tup1[0]
print "tup2[1:3]:",tup1[1:3]
print tup1+tup2

print tup1;
del tup1
print "after deleting tup1:"
#print tup1
tup3=tuple(list1)
print tup3

#python 字典
dict = {'Alice':'2341','beth':'9102','ceil':'3258'}

## -*- coding: utf-8 -*-

dict = {'Alice': '2341', 'Beth': '9102', 'Cecil': '3258'}

dict = {'name':'zara','age':7,'class':'First'}
print 'dict[name]:',dict['name']
#print dict['Alice']

dict['age']=10
dict['School']='DSP school'

print dict

print len(dict)
print str(dict)
print type(dict)

import time; #引入time模块

ticks=time.time()
print '当前时间戳为：',ticks
localtime=time.localtime(time.time())
print '本地时间为：',localtime
localtime1=time.asctime(time.localtime(time.time()))
print '本地时间为：',localtime1
#格式为时间
print time.strftime("%Y-%m-%d %H:%M:%S",time.localtime())

import calendar
cal=calendar.month(2016,1)
print "2016年1月的日历：\n",cal



