//
//智能指针：它的一种通用实现方法是采用引用计数的方法。智能指针将一个计数器与类指向的对象相关联，引用计数跟踪共有多少个类对象共享同一指针。
//
//每次创建类的新对象时，初始化指针并将引用计数置为1；
//当对象作为另一对象的副本而创建时，拷贝构造函数拷贝指针并增加与之相应的引用计数；
//对一个对象进行赋值时，赋值操作符减少左操作数所指对象的引用计数（如果引用计数为减至0，则删除对象），并增加右操作数所指对象的引用计数；这是因此左侧的指针指向了右侧指针所指向的对象，因此右指针所指向的对象的引用计数 + 1；
//调用析构函数时，构造函数减少引用计数（如果引用计数减至0，则删除基础对象）。
//实现智能指针有两种经典策略：一是引入辅助类，二是使用句柄类。这里主要讲一下引入辅助类的方法，看下面的例子：

//class Point  //基础对象类，要做一个对point类的智能指针
//{
//public:
//	Point(int xVal=0,int yVal=0):x(xVal),y(yVal){}
//	~Point();
//	int getX()const { return x; }
//	int getY()const { return y; }
//	void setX(int xVal) { x = xVal; }
//	void setY(int yVal) { y = yVal; }
//private:
//	int x, y;
//};
//
//Point::~Point()
//{
//}
//
//class RefPtr    //辅助类
//{  //该类的成员访问权限全部为private,因为不想让用户直接使用该类
//
//private:
//	friend class  SmartPtr;//定义智能指针类为友元，因为智能指针类需要直接操作辅助类
//	RefPtr(Point *ptr):p(ptr), count(1){}
//	~RefPtr(){ delete p; }
//
//private:
//	int count;//引用计数
//	Point *p; //基础对象指针
//};
//
//
//
//class SmartPtr   //智能指针类
//{
//public:
//	SmartPtr(Point *ptr) :rp(new RefPtr(ptr)){}  //构造函数
//	SmartPtr(const SmartPtr &sp):rp(sp.rp){ ++rp->count; } //复制构造函数
//	SmartPtr& operator=(const SmartPtr& rhs)  //重载赋值操作符
//	{
//		++rhs.rp->count;  //首先将右操作数引用计数加1
//		if (--rp->count==0)//然后将引用计数减1，可以应对自赋值；
//		{
//			delete rp;
//		}
//		rp = rhs.rp;
//		return *this;
//	}
//	~SmartPtr()  //析构函数
//	{
//		if (--rp->count==0)//当引用计数减为0时，删除辅助类对象指针，从而删除基础对象
//		{
//			delete rp;
//		}
//	}
//
//private:
//	RefPtr *rp;//辅助类对象指针
//};
//
//int main()
//{
//	Point *p1 = new Point(10,8);
//	SmartPtr sp1(p1); //sp1->count=1
//	SmartPtr sp2(sp1);
//	Point *p2 = new Point(5,5);
//	SmartPtr sp3(p2);
//	sp3 = sp1;
//	return 0;
//}

/*********测试类来辅助分析*******************************************************************************************/
#include<iostream>

class Simple {
public:
	Simple(int param = 0) {
		number = param;
		std::cout << "Simple: " << number << std::endl;
	}

	~Simple() {
		std::cout << "~Simple: " << number << std::endl;
	}

	void PrintSomething() {
		std::cout << "PrintSomething: " << info_extend.c_str() << std::endl;  //c_str()函数返回一个指向正规C字符串的指针, 内容与本string串相同. 
	}

	std::string info_extend;
	int number;
};

void TestAutoPtr() {
	std::auto_ptr<Simple> my_memory(new Simple(1));   // 创建对象，输出：Simple：1
	if (my_memory.get()) {                            // 判断智能指针是否为空
		my_memory->PrintSomething();                    // 使用 operator-> 调用智能指针对象中的函数
		my_memory.get()->info_extend = "Addition";      // 使用 get() 返回裸指针，然后给内部对象赋值
		my_memory->PrintSomething();                    // 再次打印，表明上述赋值成功
		(*my_memory).info_extend += " other";           // 使用 operator* 返回智能指针内部对象，然后用“.”调用智能指针对象中的函数
		my_memory->PrintSomething();                    // 再次打印，表明上述赋值成功
	}
}                                                   // my_memory 栈对象即将结束生命期，析构堆对象 Simple(1)
//执行结果为：
//   Simple : 1
//	 PrintSomething :
//	 PrintSomething : Addition
//	 PrintSomething : Addition other
//	 ~Simple : 1    //正确析构
void TestAutoPtr2() {
	std::auto_ptr<Simple> my_memory(new Simple(1));
	if (my_memory.get()) {
		std::auto_ptr<Simple> my_memory2;   // 创建一个新的 my_memory2 对象     
		my_memory2 = my_memory;             // 复制旧的 my_memory 给 my_memory2    //原因：罪魁祸首是“my_memory2 = my_memory”，这行代码，my_memory2 完全夺取了 my_memory 的内存管理所有权，导致 my_memory 悬空，最后使用时导致崩溃。
		my_memory2->PrintSomething();       // 输出信息，复制成功
		my_memory->PrintSomething();        // 崩溃
	}
}

void TestAutoPtr3() {
	std::auto_ptr<Simple> my_memory(new Simple(1));

	if (my_memory.get()) {
		my_memory.release();
	}
}
//执行结果为：
//Simple : 1  
//没有输出“~Simple: 1”，导致内存泄露

//正确的代码应该为：
void TestAutoPtr3() {
	std::auto_ptr<Simple> my_memory(new Simple(1));
	if (my_memory.get()) {
		Simple* temp_memory = my_memory.release();
		delete temp_memory;
	}
}
//或
void TestAutoPtr3() {
	std::auto_ptr<Simple> my_memory(new Simple(1));
	if (my_memory.get()) {
		my_memory.reset();  // 释放 my_memory 内部管理的内存
	}
}
//namespace boost
//#include<boost/smart_ptr.hpp>
#inlcude<memory>

void TestScopedPtr() {
	boost::scoped_ptr<Simple> my_memory(new Simple(1));
	if (my_memory.get()) {
		my_memory->PrintSomething();
		my_memory.get()->info_extend = "Addition";
		my_memory->PrintSomething();
		(*my_memory).info_extend += " other";
		my_memory->PrintSomething();

		my_memory.release();           // 编译 error: scoped_ptr 没有 release 函数
		std::auto_ptr<Simple> my_memory2;
		my_memory2 = my_memory;        // 编译 error: scoped_ptr 没有重载 operator=，不会导致所有权转移
	}
}