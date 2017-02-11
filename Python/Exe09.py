
# coding: utf-8

###python 多线程
# import thread
# import  time
#
# def print_time(threadName,delay):
#     count=0
#     while count<5:
#         time.sleep(delay)
#         count+=1
#         print "%s:%s" % (threadName,time.ctime(time.time()))
#
# try:
#     thread.start_new_thread(print_time,("Thread-1",1,))
#     thread.start_new_thread(print_time,("Thread-2",2,))
# except:
#     print "Error:unable to start thread."
#
# while 1:
#     pass

# import threading
# import time
#
# exitFlag = 0
#
# class myThread (threading.Thread):   #继承父类threading.Thread
#     def __init__(self, threadID, name, counter):
#         threading.Thread.__init__(self)
#         self.threadID = threadID
#         self.name = name
#         self.counter = counter
#     def run(self):                   #把要执行的代码写到run函数里面 线程在创建后会直接运行run函数
#         print "Starting " + self.name
#         print_time(self.name, self.counter, 5)
#         print "Exiting " + self.name
#
# def print_time(threadName, delay, counter):
#     while counter:
#         if exitFlag:
#             threading.exit()
#         time.sleep(delay)
#         print "%s: %s" % (threadName, time.ctime(time.time()))
#         counter -= 1
#
# # 创建新线程
# thread1 = myThread(1, "Thread-1", 1)
# thread2 = myThread(2, "Thread-2", 2)
#
# # 开启线程
# thread1.start()
# thread2.start()
#
# print "Exiting Main Thread"


####python GUI
from Tkinter import *           # 导入 Tkinter 库
root = Tk()                     # 创建窗口对象的背景色
                                # 创建两个列表
li     = ['C','python','php','html','SQL','java']
movie  = ['CSS','jQuery','Bootstrap']
listb  = Listbox(root)          #  创建两个列表组件
listb2 = Listbox(root)
for item in li:                 # 第一个小部件插入数据
    listb.insert(0,item)

for item in movie:              # 第二个小部件插入数据
    listb2.insert(0,item)

listb.pack()                    # 将小部件放置到主窗口中
listb2.pack()
root.mainloop()               # 进入消息循环