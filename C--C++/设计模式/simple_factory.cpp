#include <iostream>
using namespace std;

class COperator   //运算类的基类
{
public:  //
	int m_first;
	int m_second;
public:
	virtual double getResult() = 0;
	//int add(){ return m_second + m_first; } //私有成员在本类可以访问和在子类的内部和外部都不能访问；保护型成员在子类内部可以访问，外部不能访问；公有成员在子类内部和外部都能访问；前提为公有继承
};

class AddOperator : public COperator
{
public:
	virtual double getResult() override
	{
		return m_first + m_second;
	}
};

class SubOperator:public COperator
{
public:
	virtual double getResult() override
	{
		return m_first - m_second;
	}
};

//简单工厂类
class CSimpleFactory
{
public:
	static COperator* create(char ope);
};
COperator* CSimpleFactory::create(char ope)
{
	COperator* op = nullptr;
	switch (ope)
	{
	case '+':
		op = new AddOperator(); break;
	case '-':
		op = new SubOperator(); break;
	default:
		break;
	}
	return op;
}


//客户端
int main()
{
	int a, b;
	cin >> a >> b;
	COperator* op = CSimpleFactory::create('+');
	op->m_first = a;
	op->m_second = b;
	cout << op->getResult() << endl;
	return 0;
}