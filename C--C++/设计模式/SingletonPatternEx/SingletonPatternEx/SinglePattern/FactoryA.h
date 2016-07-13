#ifndef _FACTORYA_H_
#define _FACTORYA_H_

#include <iostream>
#include "SingletonFactory.h"

using namespace std;

// Factory A
class FactoryA : public SingletonFactory
{
	friend class SingletonFactory;

public:
	void Operation()
	{
		cout<<"I'm from FactoryA"<<endl;
	}

protected:
	FactoryA(){}
	virtual ~FactoryA(){}
};

#endif