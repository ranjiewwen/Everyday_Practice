#include <iostream>
using namespace std;
class Component
{
public:
	//Component();
	//~Component();
public:
	virtual void Operation() = 0;
private:

};


class ConcreteComponent:public Component
{
public:

public:
	void Operation()
	{
		cout << "I am no decorated ConcreteComponent" << endl;
	}
private:

};


class Decorator :public Component
{
public:  //默认为私有属性
	Decorator(Component *pComponent) :m_pComponentObj(pComponent){}
	void Operation()
	{
	   if (m_pComponentObj!=nullptr)
	   {
		   m_pComponentObj->Operation();
	   }
	}
private:
protected:
	Component *m_pComponentObj;

};

class ConcreteDecoratorA : public Decorator
{
public:		
	ConcreteDecoratorA(Component *pDecorator) :Decorator(pDecorator){}
	void Operation()
	{
		AddedBehavior();
		Decorator::Operation();
	}
	void AddedBehavior()
	{
		cout << "This is added behavior A."<<endl;
	}
};

class ConcreteDecoratorB :public Decorator
{
public:
	ConcreteDecoratorB(Component *pDecorator) :Decorator(pDecorator){}
	void Operation()
	{
		AddedBehavior();
		Decorator::Operation();
	}
	void AddedBehavior()
	{
		cout << "This is added behavior B." << endl;
	}
};

int main()
{
	Component *pComponentObj = new ConcreteComponent();
	Decorator *pDecoratorAObj = new ConcreteDecoratorA(pComponentObj);
	pDecoratorAObj->Operation();
	cout << "==============================================="<<endl;
	Decorator *pDecoratorBObj = new ConcreteDecoratorB(pComponentObj);
	pDecoratorBObj->Operation();
	cout<< "=================================================" << endl;
	Decorator *pDecoratorABObj = new ConcreteDecoratorB(pDecoratorAObj);
	pDecoratorABObj->Operation();
	cout << "================================================" << endl;
	delete pDecoratorABObj;
	pDecoratorABObj = nullptr;
	delete pDecoratorAObj;
	pDecoratorAObj = nullptr;
	delete pDecoratorBObj;
	pDecoratorBObj = nullptr;
	delete pComponentObj;
	pComponentObj = nullptr;
	return 0;
}