
# coding: utf-8

# import sqlite3
# conn = sqlite3.connect('test.db')
# cursor = conn.cursor()
# # sqlite创建表时，若id为INTEGER类型且为主键，可以自动递增，在插入数据时id填NULL即可
# # cursor.execute('create table user(id integer primary key, name varchar(25))') #执行一次
# # 插入一条数据
# cursor.execute('insert into user(id,name)values(NULL,"yjc")')
# # 返回影响的行数
# print(cursor.rowcount)
# #提交事务，否则上述SQL不会提交执行
# conn.commit()
# # 执行查询
# cursor.execute('select * from user')
# # 获取查询结果
# print(cursor.fetchall())
# # 关闭游标和连接
# cursor.close()
# conn.close()


import MySQLdb
#from MySQLdb import connect

# print MySQLdb
# #打开数据库连接
# db=MySQLdb.connect( host='localhost', user='root',passwd='ranjiewen',db='testdb',port=3306)
# # 使用cursor()方法获取操作游标
# cursor = db.cursor()
# # 使用execute方法执行SQL语句
# cursor.execute("SELECT VERSION()")
# # 使用 fetchone() 方法获取一条数据库。
# data = cursor.fetchone()
# print "Database version : %s " % data
# # 关闭数据库连接
# db.close()



# 打开数据库连接
db = MySQLdb.connect("localhost","testuser","testuser","testdb" )
# 使用cursor()方法获取操作游标
cursor = db.cursor()
# 如果数据表已经存在使用 execute() 方法删除表。
cursor.execute("DROP TABLE IF EXISTS EMPLOYEE")
# 创建数据表SQL语句
sql = """CREATE TABLE EMPLOYEE (
         FIRST_NAME  CHAR(20) NOT NULL,
         LAST_NAME  CHAR(20),
         AGE INT,
         SEX CHAR(1),
         INCOME FLOAT )"""
cursor.execute(sql)
# 关闭数据库连接
db.close()

