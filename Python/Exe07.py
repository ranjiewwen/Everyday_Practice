
# coding: utf-8

#python 面向对象

class Employee:
    '所有员工的基类'
    enmCount = 0;

    def __init__(self,name, salary):
        self.name=name
        self.salary=salary
        Employee.enmCount+=1

    def displayCount(self):
        print "Total Employee %d " %Employee.enmCount

    def displayEmployee(self):
        print "Name:",self.name,",Salary",self.salary

"创建 Employee类的第一个对象"
emp1 = Employee("zara",2000)
emp2 = Employee("kara",5000)
emp1.displayEmployee()
emp2.displayEmployee()
print "Total Employee %d" %Employee.enmCount

emp1.age=7   #添加一个‘age’属性
hasattr(emp1,'age')
getattr(emp1,'age')
setattr(emp1,'age',25)

print "Employee.__doc__:",Employee.__doc__
print "Employee.__name__:",Employee.__name__
print "Employee.__module__:",Employee.__module__
print "Employee.__dict__:",Employee.__dict__

class Point:
    def __init__(self,x=0,y=0):
        self.x=x
        self.y=y
    def __del__(self):
        class_name=self.__class__.__name__
        print class_name,"销毁"

pt1=Point()
pt2=pt1
pt3=pt1
print id(pt1),id(pt2),id(pt3)
del pt1
del pt2
del pt3

class Parent:        # 定义父类
   parentAttr = 100
   def __init__(self):
      print "调用父类构造函数"

   def parentMethod(self):
      print '调用父类方法'

   def setAttr(self, attr):
      Parent.parentAttr = attr

   def getAttr(self):
      print "父类属性 :", Parent.parentAttr

class Child(Parent): # 定义子类
   def __init__(self):
      print "调用子类构造方法"

   def childMethod(self):
      print '调用子类方法 child method'

c = Child()          # 实例化子类
c.childMethod()      # 调用子类的方法
c.parentMethod()     # 调用父类方法
c.setAttr(200)       # 再次调用父类的方法
c.getAttr()          # 再次调用父类的方法

class  Vector:
    def __init__(self,a,b):
        self.a=a
        self.b=b
    def __str__(self):
        return 'Vector (%d,%d)' %(self.a,self.b)
    def __add__(self, other):
        return Vector(self.a+other.a,self.b+other.b)

v1=Vector(2,10)
v2=Vector(5,-2)
print v1+v2

class JustCounter:
	__secretCount = 0  # 私有变量
	publicCount = 0    # 公开变量

	def count(self):
		self.__secretCount += 1
		JustCounter.publicCount += 1
		print self.__secretCount

counter = JustCounter()
counter.count()
counter.count()
print counter.publicCount
#print counter.__secretCount  # 报错，实例不能访问私有变量

import re
print (re.match("www","www.baidu.com").span())
print(re.match('com', 'www.runoob.com'))         # 不在起始位置匹配

line = "Cats are smarter than dogs"

matchObj = re.match( r'(.*) are (.*?) .*', line, re.M|re.I)
if matchObj:
   print "matchObj.group() : ", matchObj.group()
   print "matchObj.group(1) : ", matchObj.group(1)
   print "matchObj.group(2) : ", matchObj.group(2)
else:
   print "No match!!"

print(re.search('www', 'www.runoob.com').span())  # 在起始位置匹配
print(re.search('com', 'www.runoob.com').span())  # 不在起始位置匹配

matchObj = re.search( r'dogs', line, re.M|re.I)
if matchObj:
   print "search --> matchObj.group() : ", matchObj.group()
else:
   print "No match!!"

phone = "2004-959-559 #这是一个国外电话号码"

#删除字符串中的python注释
num=re.sub(r'#.*$','',phone)
print "电话号码是：",num
#删除非数字（-）的字符串
num=re.sub(r'\D','',phone)
print "电话号码是：",num