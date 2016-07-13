/*****************************************************
* \file     SingletonPatternDemo.cpp
* \date     2016/07/13 18:20
* \author   ranjiewen
* \contact: ranjiewen@outlook.com 
*****************************************************/

#include <iostream>
using namespace  std;
class Singleton
{
public:
	static Singleton* GetInstance()
	{
		if (m_Instance == nullptr)
		{
			//Lock(); // C++没有直接的Lock操作，请使用其它库的Lock，比如Boost，此处仅为了说明
			m_Instance = new Singleton();
			//UnLock();
		}
		return m_Instance;
	}
	//第二种方式
	static Singleton* GetInstance()
	{
		return const_cast<Singleton*>m_Instance;
	}

	static void Destory()
	{
		if (m_Instance != nullptr)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}
	//this is just a operation example
	int GetTest()
	{
		return m_test;
	}
private:
	//在类中，要构造一个实例，就必须调用类的构造函数，如此，为了防止在外部调用类的构造函数而构造实例，
	//需要将构造函数的访问权限标记为protected或private；
	Singleton(int _test = 10) :m_test(_test){}  //构造函数  
	int m_test;
	static Singleton* m_Instance;
	//static int point;
	//第二种方式
	static const Singleton* m_Instance;
};

Singleton *Singleton::m_Instance = nullptr;
const Singleton *Singleton::m_Instance = new Singleton();
//int Singleton::point=0;


int main(int argc, char* argv[])
{
	Singleton* singletonObj = Singleton::GetInstance();
	std::cout << singletonObj->GetTest() << std::endl;
	Singleton::Destory();
	return 0;
}


