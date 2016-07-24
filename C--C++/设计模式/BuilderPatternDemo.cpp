/*****************************************************
* \file BuilderPatternDemo.cpp
* \date 2016/07/24 15:57
* \author ranjiewen
* \contact: ranjiewen@outlook.com 

*****************************************************/

#include<iostream>
using namespace  std;

typedef enum MANTYPETag
{
	kFatMan,
	kThinMa,
	kNormal
}MANTYPE;


class Man{
public:
	void SetHead(MANTYPE type){ m_Type = type; }
	void SetBody(MANTYPE type){ m_Type = type; }
	void SetLeftHand(MANTYPE type){ m_Type = type; }
	void SetRightHand(MANTYPE type){ m_Type = type; }
	void SetLeftFoot(MANTYPE type){ m_Type = type; }
	void SetRightFoot(MANTYPE type){ m_Type = type; }
	void ShowMan()
	{
		switch (m_Type)
		{
		case kFatMan:
			cout << "I'm a fat man!";
			break;
		case kThinMa:
			cout << "I'm a thin man!";
			break;
		default:
			cout << "I'm a normal man!";
			break;
		}
	}
private:
    MANTYPE	m_Type;
};

class Builder{

public:
	virtual void buildHead() = 0;
	virtual void buildBody() = 0;
	virtual void buildLeftHand() = 0;
	virtual void buildRightHand() = 0;
	virtual void buildLeftFoot() = 0;
	virtual void buildRightFoot() = 0;
	virtual Man* getMan() = 0;
};

class FatBuilder :public Builder{
public:
	FatBuilder() { m_FatMan = new Man(); }
	void buildHead(){ m_FatMan->SetHead(kFatMan); }
	void buildBody(){ m_FatMan->SetBody(kFatMan); }
	void buildLeftHand(){ m_FatMan->SetLeftHand(kFatMan); }
	void buildRightHand(){ m_FatMan->SetRightHand(kFatMan); }
	void buildLeftFoot(){ m_FatMan->SetLeftFoot(kFatMan); }
	void buildRightFoot(){ m_FatMan->SetRightFoot(kFatMan); }
	Man* getMan(){ return m_FatMan; }
private:
	Man* m_FatMan;
};

class ThinBuilder :public Builder
{
private:
	Man* m_ThinMan;
	ThinBuilder(){ m_ThinMan = new Man(); }
	void buildHead(){ m_ThinMan->SetHead(kThinMa); }
	void buildBody(){ m_ThinMan->SetBody(kThinMa); }
	void buildLeftHand(){m_ThinMan->SetLeftHand(kThinMa); }
	void buildRightHand(){ m_ThinMan->SetRightHand(kThinMa); }
	void buildLeftFoot(){ m_ThinMan->SetLeftFoot(kThinMa); }
	void buildRightFoot(){ m_ThinMan->SetRightFoot(kThinMa); }
	Man* getMan(){ return m_ThinMan; }
};

class Director{

private:
	Builder* m_Builder;
public:
	Director(Builder *builder):m_Builder(builder){}
	void CreateMan();
};

void Director::CreateMan(){
	m_Builder->buildHead();
	m_Builder->buildBody();
	m_Builder->buildLeftHand();
	m_Builder->buildRightHand();
	m_Builder->buildLeftFoot();
	m_Builder->buildRightFoot();
}

int main(){
	Builder* builderObj = new FatBuilder();
	Director directorObj(builderObj);
	directorObj.CreateMan();

	Man* manObj = builderObj->getMan();
	if (manObj!=nullptr)
	{
		manObj->ShowMan();
	}

	delete manObj;
	manObj = nullptr;

	delete builderObj;
	builderObj = nullptr;
	return 0;
}