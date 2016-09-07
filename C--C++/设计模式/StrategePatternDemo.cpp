/*!
 * \file StrategePatternDemo.cpp
 * \date 2016/08/14 19:56
 *
 * \author ranjiewen
 * \contact: ranjiewen@outlook.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#include <iostream>
using namespace std;

typedef enum StrategyType
{
	StrategyA,
	StrategyB,
	StrategyC
};

class Strategy
{
public:
	virtual void AlgorithmInterface() = 0;
	virtual ~Strategy() = 0; //基类申请为虚析构函数

};
Strategy::~Strategy(){}

class ConcreteStrategyA :public Strategy
{
public:
	void AlgorithmInterface()
	{
		cout << "I'm from ConcreteStrategyA." << endl;
	}
	~ConcreteStrategyA(){}

};

class ConcreteStrategyB :public Strategy
{
public:
	void AlgorithmInterface()
	{
		cout << "I'm from ConcreteStrategyB." << endl;
	}
	~ConcreteStrategyB(){}
};

class ConcreteStrategyC :public Strategy
{
public:
	void AlgorithmInterface()
	{
		cout << "I'm from ConcreteStrategyC." << endl;
	}
	~ConcreteStrategyC(){}
};

class Context
{
private:
	Strategy* pStrategy;
public:
	Context(StrategyType strategyType)
	{
		switch (strategyType)
		{
		case StrategyA:
			pStrategy = new ConcreteStrategyA;
			break;
		case StrategyB:
			pStrategy = new ConcreteStrategyB;
			break;
		case StrategyC:
			pStrategy = new ConcreteStrategyC;
			break;
		default:
			break;
		}
	}
	~Context()
	{
		if (pStrategy)
		{
			delete pStrategy;
		}
	}

	void ContextInterface()
	{
		if (pStrategy)
		{
			pStrategy->AlgorithmInterface();
		}
	}
};

int main()
{
	Context* pContext = new Context(StrategyA);
	pContext->ContextInterface();
	return 0;
}
