# coding: utf-8

def printer (str):
    "打印传入的字符串到标准显示设备上："
    print str
    return

#调用函数
printer("调用用户自定义函数！")
printer("再次调用同一函数")
#关键字参数
printer(str="My string! ")


def changme(mylist):
    mylist.append([1,2,3,4])
    print "函数内取值",mylist
    return

#调用函数
mylist=[10,20,30]
changme(mylist)
print "执行函数后的值：",mylist

def printinfo(name ,age=24):
    "打印任何传入的字符串"
    print "name:",name
    print "age:",age
    return

#使用关键字参数顺序不重要
printinfo(age=50,name="Alice")
#缺省参数，使用默认参数
printinfo(name='derrick')

def printinfo_(arg,*vartuple):
    "打印任何传入的参数"
    print "输出："
    print arg
    for var in vartuple:
        print var
    return
#调用不定长参数函数
printinfo_(10,23,45)

sum=lambda arg1,arg2:arg1+arg2
print "相加的值为：",sum(10,34)
print "相加的值为：",sum(23,45)


def sum(arg1,arg2):
    #返回两个参数的和
    toatal=arg1+arg2
    print '函数内：',toatal
    return  toatal

total=sum(12,11)


Money = 2000
def AddMoney():
    # 想改正代码就取消以下注释:
    global Money
    Money = Money + 1
print Money
AddMoney()
print Money

#dir()函数
import  math
content = dir(math)
print content