# coding: utf-8

#算术运算符
a=21;
b=10;
c=0;
c=a+b;
print "1-c的值为：",c
c=a-b
print "2-c的值为：",c
c=a*b
print "3-c的值为：",c
c=a/b
print "4-c的值为：",c
c=a%b
print "5-c的值为：",c

#修改变量a,b,c
a=2
b=3
c=a**b
print "6-c的值为：",c

a=10
b=5
c=a//b
print "7-c的值为：",c

#python 比较运算符
if a==b:
    print "1-a等于b"
else:
    print "1-a不等于b"

if a!=b:
    print "2-a不等于b"
else:
    print "2-a等于b"
if  a<>b:
    print "3-a不等于b"
else:
    print "3-a等于b"

#python 赋值运算符
a = 21
b = 10
c = 0

c = a + b
print "1 - c 的值为：", c
c += a
print "2 - c 的值为：", c
c *= a
print "3 - c 的值为：", c
c /= a
print "4 - c 的值为：", c
c = 2
c %= a
print "5 - c 的值为：", c
c **= a
print "6 - c 的值为：", c
c //= a
print "7 - c 的值为：", c

#python 位运算符
a=00111100
b=00001101
print "a^b的值为：",a^b
a = 60            # 60 = 0011 1100
b = 13            # 13 = 0000 1101
c = 0
c = a & b;        # 12 = 0000 1100
print "1 - c 的值为：", c
c = a | b;        # 61 = 0011 1101
print "2 - c 的值为：", c
c = a ^ b;        # 49 = 0011 0001
print "3 - c 的值为：", c
c = ~a;           # -61 = 1100 0011
print "4 - c 的值为：", c
c = a << 2;       # 240 = 1111 0000
print "5 - c 的值为：", c
c = a >> 2;       # 15 = 0000 1111
print "6 - c 的值为：", c

#python 逻辑运算符
a = 10
b = 20
if ( a and b ):
   print "1 - 变量 a 和 b 都为 true"
else:
   print "1 - 变量 a 和 b 有一个不为 true"

if ( a or b ):
   print "2 - 变量 a 和 b 都为 true，或其中一个变量为 true"
else:
   print "2 - 变量 a 和 b 都不为 true"

#python成员运算符
a=10
b=20
if a in list:
    print "1-变量a在列表中list中"
else:
    print "1-变量a不在列表list中"

if (b not in list):
    print "2-变量b不在给定的列表list中"
else:
    print "2-变量b在给定的列表list中"



