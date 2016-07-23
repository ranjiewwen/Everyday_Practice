/*!
 * \file ProxyPatternDemo.cpp
 * \date 2016/07/22 8:58
 *
 * \author ranjiewen
 * \contact: ranjiewen@outlook.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note   智能指针使用引用计数实现时，就是最好的使用代理模式的例子
*/


#include<iostream>
using namespace  std;

#define  SAFE_DELETE(p)    if (p){delete p;p=nullptr;}

class CSubject
{
public:
	CSubject(){}
	virtual ~CSubject(){}
	virtual void	Request() = 0;
};

class CRealSubject{
public:
	CRealSubject(){}
	~CRealSubject(){}
	void Request(){
		cout << "CRealSubject Request." << endl;
	}
};

class CProxy :public CSubject{
private:
	CRealSubject* m_realSubject;
public:
	CProxy() :m_realSubject(nullptr){}
	~CProxy(){  SAFE_DELETE(m_realSubject); }
	void Request(){
	if (m_realSubject==nullptr)
	{
		m_realSubject = new CRealSubject();
	}
	cout << "CProxy Request" << endl;
	m_realSubject->Request();
	}
};


int main()
{
	CSubject* pSubject = new CProxy();
	pSubject->Request();
	SAFE_DELETE(pSubject);
}