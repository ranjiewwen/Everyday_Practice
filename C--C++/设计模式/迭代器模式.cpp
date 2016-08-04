#include<iostream>
using namespace std;

typedef struct tagNode{

	int value;
	tagNode* pNext;
}Node;

class JTList   //定义的容器
{
private:
	Node* m_pHead, *m_pTail;
public:
	JTList() :m_pHead(nullptr), m_pTail(nullptr){}
	JTList(const JTList&);
	~JTList();
	JTList &operator=(const JTList&);

	long getCount()const;
	Node* get(const long index)const;
	Node* first()const;
	Node* last()const;
	bool includes(const int&)const;

	void Append(const int&);
	void Remove(Node* pNode);
	void RemoveAll();
private:
	long m_lCount;
};

JTList::~JTList()
{
	Node* pCurrent = m_pHead;
	Node* pNextNode = nullptr;
	while (pCurrent)
	{
		pNextNode = pCurrent->pNext;
		delete pCurrent;
		pCurrent = pNextNode;
	}
}

long JTList::getCount()const
{
	return m_lCount;
}

Node* JTList::get(const long index)const
{
	if (index > m_lCount - 1 || index < 0)
	{
		return nullptr;
	}
	int iPosTemp = 0;
	Node* pNodeTemp = m_pHead;
	while (pNodeTemp)
	{
		if (index==iPosTemp++)
		{
			return pNodeTemp;
		}
		pNodeTemp = pNodeTemp->pNext;
	}
	return nullptr;
}

Node* JTList::first()const
{
	return m_pHead;
}

Node*JTList::last()const
{
	return m_pTail;
}

bool JTList::includes(const int& value)const
{
	Node* pNodeTemp = m_pHead;
	while (pNodeTemp)
	{
		if (pNodeTemp->value==value)
		{
			return true;
		}
		pNodeTemp = pNodeTemp->pNext;
	}
	return false;
}

void JTList::Append(const int& value)
{
	Node* pInsertNode = new Node;
	pInsertNode->value = value;
	pInsertNode->pNext = nullptr;

	if (m_pHead==nullptr)
	{
		m_pHead=m_pTail = pInsertNode;
	}
	else  //在尾部插入元素
	{
		m_pTail->pNext = pInsertNode;
		m_pTail = pInsertNode;
	}
	++m_lCount;
}


void JTList::Remove(Node* pNode)
{
	if (pNode==nullptr||m_pHead==nullptr||m_pTail==nullptr)
	{
		return;
	}
	if (m_pHead==pNode)
	{
		Node* pNewNode = m_pHead->pNext; //记下头节点后面的元素记住
		m_pHead = pNewNode;
	}
	else
	{
		//To get the deleting node's previous node
		Node* m_previousNode = nullptr;
		Node* pCurrentNode = m_pHead;
		while (pCurrentNode)
		{
			if (pCurrentNode==pNode)
			{
				break;
			}
			m_previousNode = pCurrentNode;
			pCurrentNode = pCurrentNode->pNext;
		}
		//To get the deleting node's next node
		Node* m_nextNode = pCurrentNode->pNext;
		//if m_nextNode is null, it means the deleting node is the tail node, we should change the m_pTail pointer
		if (m_nextNode==nullptr)
		{
			m_pTail = m_previousNode;
		}
		m_previousNode->pNext = m_nextNode;
	}
	delete pNode;
	pNode = nullptr;
	--m_lCount;
}

void JTList::RemoveAll()
{
	delete this;
}


class Iterator
{
public:
	virtual void first() = 0;;
	virtual void next() = 0;
	virtual bool isDone()const = 0;
	virtual Node* currentItem()const = 0;
};

class JTListIterator :public Iterator
{
private:
	JTList* m_pJTList;
	Node* m_pCurrent;
public:
	JTListIterator(JTList* pList) :m_pJTList(pList), m_pCurrent(nullptr){}
	virtual void first();
	virtual void next();
	virtual bool isDone()const;
	Node *currentItem()const;
};

void JTListIterator::first()
{
	m_pCurrent = m_pJTList->first();
}
void JTListIterator::next()
{
	m_pCurrent = m_pCurrent->pNext;
}

bool JTListIterator::isDone()const
{
	return m_pCurrent == m_pJTList->last()->pNext;
}

Node* JTListIterator::currentItem()const
{
	return m_pCurrent;
}

//客户端
int main()
{
	JTList* pJTList = new JTList;
	pJTList->Append(10);
	pJTList->Append(20);
	pJTList->Append(30);
	pJTList->Append(40);
	pJTList->Append(50);
	pJTList->Append(60);
	pJTList->Append(70);
	pJTList->Append(80);
	pJTList->Append(90);
	pJTList->Append(100);

	Iterator* pIterator = new JTListIterator(pJTList);

	for (pIterator->first(); !pIterator->isDone();pIterator->next())
	{
		cout << pIterator->currentItem()->value << "-->";
	}
	cout << "NULL" << endl;

	Node* pDeleteNode = nullptr;

	for (pIterator->first(); !pIterator->isDone();pIterator->next())
	{
		pDeleteNode = pIterator->currentItem();
		if (pDeleteNode->value==100)
		{
			pJTList->Remove(pDeleteNode);
			break;
		}
	}

	for (pIterator->first(); !pIterator->isDone();pIterator->next())
	{
		cout << pIterator->currentItem()->value << "-->";
	}
	cout <<"NULL" << endl;

	delete pJTList;
	delete pIterator;
	return 0;
}