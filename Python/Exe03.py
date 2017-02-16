# coding: utf-8

#python 条件语句

flag = False
name = 'jiewen'
if name=='python':
    flag=True
    print "welcome boss"
else:
    print name

num = 5
if num == 3:
    print "boss"
elif num == 2:
    print "user"
elif num == 1:
    print "worker"
elif num<0:
    print "error"
else:
    print "roadman"

#if 语句多个条件
if num >= 0 and num <=10:
    print 'hello'
else:
    print "undefine"
if (num>=0 and num<=5) or (num>=5 and num <= 15):
    print "hello"
else:
    print "undefine"

var = 100
if var==100: print "var 的值为100 "
print "Good bye!"

#python 循环语句
count = 0
while count < 9:
    print "the count is :",count
    count+=1
print "Good bye!"

count = 0
while count < 5:
    print count,"is less than 5"
    count=count+1
else:
    print count, 'is not less than 5'

# flag=1
# while (flag):print "hello world."

for letter in 'python':
    print '当前字母：',letter

fruits=['banana','apple','mango']
for fruit in fruits:
    print '当前字母：',fruit
#通过序列索引迭代
fruits=['banana','apple','mango']
for index in range(len(fruits)):
    print '当前水果是：',fruits[index]
for num in range(10,20):
    for i in range(2,num):
        if num%i == 0:
            j=num/i
            print "%d 等于 %d * %d" % (num,i,j)
            break
    else:
        print num,'是一个质数'


#以下实例使用了嵌套循环输出2~100之间的素数
i=2
while i<100 :
    j=2
    while j<=(i/j):
        if not(i%j):
            break
        j+=1
    if  j>i/j:
        print i,'是素数'
    i+=1
print "Good bye!"

#python break语句
for letter in 'python':
    if letter == 'h':
        break
    print 'Current Letter:',letter

var = 10
while var>0:
    print 'Current Variable value:',var
    var = var -1
    if  var==5:
        break
print "Good bye!"

#python continue 语句
for letter in 'python':
    if letter=='h':
        continue
    print '当前字母：',letter

var=10
while var>0 :
    var=var-1
    if var==5:
        continue
    print '当前变量值：',var
print 'Good bye!'

#python pass语句
for letter in 'python':
    if letter =='h':
        pass
        print '这是pass块'
    print '当前字母：',letter

print 'Good bye!'

