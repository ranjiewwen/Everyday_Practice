#include "SingletonFactory.h"
#include "FactoryA.h"
#include "FactoryB.h"

SingletonFactory *SingletonFactory::m_Instance = NULL;
SingletonFactory::GC SingletonFactory::gc;

SingletonFactory *SingletonFactory::GetInstance(FactoryEnum factory)
{
	if (m_Instance == NULL)
	{
		switch (factory)
		{
		case kFactory_A:
			m_Instance = new FactoryA();
			break;

		case kFactory_B:
			m_Instance = new FactoryB();

		default:
			// This is the default, you can change the implementation
			m_Instance = new FactoryA();
		}
	}
	return m_Instance;
}