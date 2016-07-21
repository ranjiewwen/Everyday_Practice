/*****************************************************
* \file PrototypePatternDemo.cpp
* \date 2016/07/21 21:17
* \author ranjiewen
* \contact: ranjiewen@outlook.com 

//原型模式和建造者模式、工厂方法模式一样，都属于创建型模式的一种。简单的来说，我们使用原型模式，就是为了创建对象。
//如果某个类需要实现Clone功能，就只需要继承Prototype类，然后重写自己的默认复制构造函数就好了。

*****************************************************/

#include <iostream>
using namespace std;

//接口
class Prototype
{
public:
	Prototype(){}
	virtual ~Prototype(){}
	virtual Prototype* clone() = 0;
};
//实现
class ConcretePrototype :public Prototype
{
public:
	ConcretePrototype(){}
	virtual ~ConcretePrototype(){}
	//拷贝构造函数
	ConcretePrototype(const ConcretePrototype& rhs)
	{
		this->m_counter = rhs.m_counter;
	}
	virtual ConcretePrototype* clone()
	{
	//调用拷贝构造函数
		return new ConcretePrototype(*this);
	}
private:
	int m_counter;
};

int main()
{
	ConcretePrototype* conProA = new ConcretePrototype();
	ConcretePrototype* conProB = conProA->clone();
	delete conProA;
	conProA = nullptr;
	delete conProB;
	conProB = nullptr;
	return 0;
}