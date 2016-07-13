#ifndef _FACTORYB_H_
#define _FACTORYB_H_

#include <iostream>
#include "SingletonFactory.h"

using namespace std;

// Factory B
class FactoryB : public SingletonFactory
{
	friend class SingletonFactory;

public:
	void Operation()
	{
		cout<<"I'm from FactoryB"<<endl;
	}

protected:
	FactoryB(){}
	virtual ~FactoryB(){}
};
#endif