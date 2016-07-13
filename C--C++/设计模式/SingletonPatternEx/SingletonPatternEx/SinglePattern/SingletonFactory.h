#ifndef _SINGLETONFACTORY_H_
#define _SINGLETONFACTORY_H_

#include <iostream>

#include "Constant.h"
using namespace std;

// The singleton factory
class SingletonFactory
{
public:
	static SingletonFactory *GetInstance(FactoryEnum factory);
	virtual void Operation() = 0;

protected:
	SingletonFactory(){}
	virtual ~SingletonFactory(){}

private:
	static SingletonFactory *m_Instance;

	// Just to release the resource
	class GC
	{
	public:
		~GC()
		{
			if (m_Instance != NULL)
			{
				cout<<"GC test"<<endl;
				delete m_Instance;
				m_Instance = NULL;
			}
		}
	};
	static GC gc;
};

#endif