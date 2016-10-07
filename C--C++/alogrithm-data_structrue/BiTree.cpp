
#include <iostream>
using namespace std;

//节点的定义
typedef struct BTNode
{
	int data;
	BTNode* rChild;
	BTNode* lChild;
}BiTNode, *BiTree;


//二叉树的创建，先序创建二叉树
int CreateBiTree(BiTNode** T)
{
	int ch;
	cin >> ch;
	if (ch==-1)
	{
		*T = nullptr;
		return 0;
	}
	else
	{
		//*T = new BiTNode();
		*T = (BiTNode*)malloc(sizeof(BiTNode));
		if (T==nullptr)
		{
			cout << "failed!\n";
			return 0;
		}
		else
		{
			(*T)->data = ch;
			cout << "输入左子节点：";
			//cin >> ch;
			CreateBiTree(&(*T)->lChild);
			cout << endl;
			cout << "输入右子节点：";
			//cin >> ch;
			CreateBiTree(&(*T)->rChild);
		}
	}
	return 1;
}


//先序遍历二叉树
void PreOrderBiTree(BiTNode* T)
{
	if (T == nullptr)
	{
		return;
	}
	else
	{
		cout << T->data<<" ";
		PreOrderBiTree(T->lChild);
		PreOrderBiTree(T->rChild);
	}
}

//中序遍历二叉树
void InOrderBiTree(BiTNode* T)
{
	if (T == nullptr)
	{
		return;
	}
	else
	{
		InOrderBiTree(T->lChild);
		cout << T->data << " ";
		InOrderBiTree(T->rChild);
	}
}

//后续遍历二叉树
void PostOrderBiTree(BiTNode* T)
{
	if (T == nullptr)
	{
		return;
	}
	else
	{
		PostOrderBiTree(T->lChild);
		PostOrderBiTree(T->rChild);
		cout << T->data << " ";
	}
}

//树高....

//叶子节点个数
int LeafCount(BiTNode* T)
{
	static int count = 0;
	if (T!=nullptr)
	{
		if (T->lChild==nullptr&&T->rChild==nullptr)
		{
			count++;
		}
		LeafCount(T->lChild);
		LeafCount(T->rChild);
	}
	return count;
}

//客户端测试
int main()
{
	BiTNode* T;
	int leafCount = 0;
	cout << "请输入第一个节点的值，-1表示没有节点：\n";
	CreateBiTree(&T);

	cout << "先序遍历二叉树：";
	PreOrderBiTree(T);
	cout << endl;

	cout << "中序遍历二叉树：";
	InOrderBiTree(T);
	cout << endl;

	cout << "后序遍历二叉树: ";
	PostOrderBiTree(T);
	cout << endl;

	leafCount = LeafCount(T);
	cout << "叶子节点的个数：" <<leafCount<< endl;


	return 0;
}


