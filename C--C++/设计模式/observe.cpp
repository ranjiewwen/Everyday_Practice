#include <iostream>
#include <list>
using namespace std;

class Observer
{
public:
	virtual void Update(int) = 0;
};

class Subject
{
public:
	virtual void Attach(Observer *) = 0;
	virtual void Detach(Observer *) = 0;
	virtual void Notify() = 0;
};

class ConcreteObserver : public Observer
{
public:
	ConcreteObserver(Subject *pSubject) : m_pSubject(pSubject){}

	void Update(int value)
	{
		cout << "ConcreteObserver get the update. New State:" << value << endl;
	}

private:
	Subject *m_pSubject;
};

class ConcreteObserver2 : public Observer
{
public:
	ConcreteObserver2(Subject *pSubject) : m_pSubject(pSubject){}

	void Update(int value)
	{
		cout << "ConcreteObserver2 get the update. New State:" << value << endl;
	}

private:
	Subject *m_pSubject;
};

class ConcreteSubject : public Subject
{
public:
	void Attach(Observer *pObserver);
	void Detach(Observer *pObserver);
	void Notify();

	void SetState(int state)
	{
		m_iState = state;
	}

private:
	std::list<Observer *> m_ObserverList;
	int m_iState;
};

void ConcreteSubject::Attach(Observer *pObserver)
{
	m_ObserverList.push_back(pObserver);
}

void ConcreteSubject::Detach(Observer *pObserver)
{
	m_ObserverList.remove(pObserver);
}

void ConcreteSubject::Notify()
{
	std::list<Observer *>::iterator it = m_ObserverList.begin();
	while (it != m_ObserverList.end())
	{
		(*it)->Update(m_iState);
		++it;
	}
}

int main()
{
	// Create Subject
	ConcreteSubject *pSubject = new ConcreteSubject();

	// Create Observer
	Observer *pObserver = new ConcreteObserver(pSubject);
	Observer *pObserver2 = new ConcreteObserver2(pSubject);

	// Change the state
	pSubject->SetState(2);

	// Register the observer
	pSubject->Attach(pObserver);
	pSubject->Attach(pObserver2);

	pSubject->Notify();

	// Unregister the observer
	pSubject->Detach(pObserver);

	pSubject->SetState(3);
	pSubject->Notify();

	delete pObserver;
	delete pObserver2;
	delete pSubject;
}