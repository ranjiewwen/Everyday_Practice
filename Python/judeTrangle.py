# -*- coding: utf-8 -*-
"""
Created on Tue Nov 08 16:40:47 2016

@author: ranjiewen
"""
#==============================================================================

# #from skimage import io
# #img=io.imread('F:/BMP/lena.bmp')
# #io.imshow(img)
#==============================================================================

#==============================================================================
# sd1=int(raw_input('the first side:'))
# 
# sd2=int(raw_input('the second side:'))
# 
# if sd1==sd2:
#     print "the square's area is:%d" %(sd1*sd2)
# else:
#     print "the rectangle's area id:%d" %(sd1*sd2)
#==============================================================================

#==============================================================================
# #计算pi，蒙特卡洛方法
# from __future__ import division  
# from random import random
# from math import sqrt
# from time import clock
# darts=1200;
# hits=0;
# t0=clock();
# for i in range(1,darts):
#     x,y =random(),random()
#     dist=sqrt(x**2+y**2)
#     if dist<=1.0:
#         hits=hits+1
#         
# pi=4*(hits/darts)
# 
# print("pi的值是： %s" %pi);
# print("程序运行时间是 %-5.5s s" %clock);
#==============================================================================

from math import sqrt

def distance(x1_,y1_,x2_,y2_):
    return sqrt((x1_-x2_)**2+(y1_-y2_)**2)
    
def isTrangle(x1_,y1_,x2_,y2_,x3_,y3_):
    a=distance(x1_,y1_,x2_,y2_)
    b=distance(x2_,y2_,x3_,y3_)
    c=distance(x1_,y1_,x3_,y3_)
    if (((a+b)>c) and ((a-b)<c)) or (((a+c)>b) and ((a-c)<b)) or (((c+b)>a) and ((c-b)<a)):
        return True
    
def main():
    print("Please enter(x,y) of three points in turn：")
    #获取用户输入的三个坐标
    x1,y1=(input("Point1:(x,y) ="))  #eval()
    x2,y2=(input("Point2:(x,y) ="))
    x3,y3=(input("Point3:(x,y) ="))
    #判断三个点是否构成三角形
    if (isTrangle(x1,y1,x2,y2,x3,y3)):
        perim=distance(x1,y1,x2,y2)+distance(x2,y2,x3,y3)+distance(x1,y1,x3,y3)
        print("The perimeter of the triangle id:{0:0.2f}".format(perim))
    else:
        print 'kidding me?this is not a triangle'

main()
