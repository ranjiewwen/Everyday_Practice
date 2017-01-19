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

