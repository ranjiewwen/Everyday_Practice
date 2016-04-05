//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct node {
//	int key;
//	struct node *LChild, *RChild; //孩子指针
//}BSTNode, *BSTree;   //定义二叉树----查找树
//
//void CreatBST(BSTree *bst);
//BSTree SearchBST(BSTree bst, int key);
//void InsertBST(BSTree *bst, int key);
//BSTNode * DelBST(BSTree t, int k);//以上是函数的声明
//
//void print_bst(BSTree t) //打印
//{
//	if (t)//中序顺序打印
//	{
//		print_bst(t->LChild);
//		printf("%d\t", t->key);
//		print_bst(t->RChild);
//	}
//}
//const int n = 10;
///*创建树*/
//void CreatBST(BSTree *bst)
//{
//	printf("请输入%d个数创建二叉搜索树：",n);
//	int i;
//	int key;
//	*bst = NULL;
//	for (i = 1; i <= n; i++)
//	{
//		scanf("%d", &key);
//		InsertBST(bst, key); //创建   
//	};
//}
///*寻找*/
//BSTree SearchBST(BSTree bst, int key)
//{
//	if (!bst)
//		return nullptr;       //bst为空   
//	else   if (bst->key == key)
//	{
//		printf("查找成功！");
//		return bst;           //找到，返回节点   
//	}
//	else   if (key < bst->key)
//		return SearchBST(bst->LChild, key); //左孩子递归调用查找       
//	else
//		return SearchBST(bst->RChild, key); //右孩子递归
//}
///*插入*/
//void InsertBST(BSTree *bst, int key)
//{
//	BSTree t;
//	if (*bst == NULL)
//	{
//		t = (BSTree)malloc(sizeof(BSTNode)); //树为空，申请空间     
//		t->key = key;
//		t->LChild = NULL;
//		t->RChild = NULL;
//		*bst = t; //插入 
//		//printf("插入成功！");
//	}
//	else if (key <(*bst)->key)
//		InsertBST(&((*bst)->LChild), key); //插到左子树   
//	else if (key>(*bst)->key)
//		InsertBST(&((*bst)->RChild), key); //插到右子树
//}
///*删除*/   //有问题？没有理解！
//BSTNode * DelBST(BSTree t, int k)  //根据LR为0或1,删除T中p所指结点的左或右子树
//{
//	BSTNode *p, *f, *s, *q;
//	p = t;
//	s = t;//
//	f = NULL;
//	while (p) //树非空,先找到key的位置
//	{
//		if (p->key == k) //根节点等于K       
//			break;
//		f = p;          //f记录k所在的节点的 双亲节点
//		if (p->key > k) //向左子树方向         
//			p = p->LChild;
//		else
//			p = p->RChild; //右  
//	}
//	if (p == NULL) //为空     
//		return t;
//	if (p->LChild == nullptr)  //左空 ，下边就是删除过程   
//	{
//		if (f == NULL) //待删除结点为根节点
//			t = p->RChild;
//		else if (f->LChild == p)
//			f->LChild = p->RChild;
//		else
//			f->RChild = p->RChild;
//		free(p); //释放空间   
//	}
//	else //右，下边就是删除过程 
//	{
//		q = p;
//		s = p->LChild;
//		while (s->RChild)
//		{
//			q = s;
//			s = s->RChild;
//		}
//		if (q == p)
//			q->LChild = s->LChild;
//		else
//			q->RChild = s->LChild;
//		p->key = s->key;
//		free(s); //释放空间    
//	}
//	return t;
//}
//
//int main()
//{
//	BSTNode * root=nullptr;
//	int loop, i, data;
//	loop = true;
//	while (loop)
//	{
//		printf("\n***************二叉树操作菜单**************\n");
//		printf(" 1.创建\n");
//		printf(" 2.查找\n");
//		printf(" 3.插入\n");
//		printf(" 4.删除\n");
//		printf(" 5.打印\n");
//		printf(" 0.退出\n");
//		scanf("%d", &i);
//		switch (i)
//		{
//		case 0:
//		{
//				  loop = false;
//				  break;
//		}
//		case 1:
//		{
//				  CreatBST(&root);
//		}break;
//		case 2:
//		{
//				  printf("Please input the data you want search.\n");
//				  scanf("%d", &data);
//				  SearchBST(root, data);
//
//		}break;
//		case 3:
//		{         printf("Please input the data you want insert.\n");
//		          scanf("%d", &data);
//		          InsertBST(&root, data);
//				  printf("插入成功！");
//		}break;
//		case 4:
//		{
//				  printf("Please input the data you want delete.\n");
//				  scanf("%d", &data);
//				  root = DelBST(root, data);
//		}break;
//		case 5:{
//				   printf("\n");
//				   if (root != NULL)
//					   printf("The BSTree's root is:%d\n", root->key);
//				   print_bst(root);
//				   break;
//		}
//		}
//	}
//}


#include <iostream>
#include <cstring>
using namespace std;

typedef int KeyType;
#define NUM 11

class BinStree;
class BinSTreeNode
{
public:
	KeyType key;
	BinSTreeNode *lchild;
	BinSTreeNode *rchild;
	BinSTreeNode()
	{
		lchild = NULL;
		rchild = NULL;
	}
};

class BinSTree
{
public:
	BinSTreeNode *root;
	BinSTree()
	{
		root = NULL;
	}
	~BinSTree()
	{
		//delete root;
	}
	BinSTreeNode *BSTreeSearch(BinSTreeNode *bt, KeyType k, BinSTreeNode *&p);
	void BSTreeInsert(BinSTreeNode *&bt, KeyType k);
	int BSTreeDelete(BinSTreeNode *&bt, KeyType k);
	void BSTreePreOrder(BinSTreeNode *bt);
	bool IsEmpty()
	{
		return root == NULL;
	}
};

/**
*  二叉树排序查找算法
*  在根指针为bt的二叉排序树中查找元素k的节点，若查找成功，则返回指向该节点的指针
*  参数p指向查找到的结点，否则返回空指针，参数p指向k应插入的父结点
*/
BinSTreeNode* BinSTree::BSTreeSearch(BinSTreeNode *bt, KeyType k, BinSTreeNode *&p)
{
	BinSTreeNode *q = NULL;
	q = bt;
	while (q)
	{
		p = q;
		if (q->key == k)
		{
			return(p);
		}
		if (q->key > k)
			q = q->lchild;
		else
			q = q->rchild;
	}
	return NULL;
}

/**
*  二叉排序树的插入节点算法
*  bt指向二叉排序树的根结点，插入元素k的结点
*/
void BinSTree::BSTreeInsert(BinSTreeNode *&bt, KeyType k)
{
	BinSTreeNode *p = NULL, *q;
	q = bt;
	if (BSTreeSearch(q, k, p) == NULL)
	{
		BinSTreeNode *r = new BinSTreeNode;
		r->key = k;
		r->lchild = r->rchild = NULL;
		if (q == NULL)
		{
			bt = r;         //被插入节点做为树的根节点
		}
		if (p && k < p->key)
			p->lchild = r;
		else if (p)
			p->rchild = r;
	}
}
/**
* 先序遍历
*/
void BinSTree::BSTreePreOrder(BinSTreeNode *bt)
{
	if (bt != NULL)
	{
		cout << bt->key << " ";
		BSTreePreOrder(bt->lchild);
		BSTreePreOrder(bt->rchild);
	}
}
/**
* 二叉排序树的删除结点算法
* 在二叉排序树中删除元素为k的结点，*bt指向二叉排序树的根节点
* 删除成功返回1，不成功返回0.
*/
int BinSTree::BSTreeDelete(BinSTreeNode *&bt, KeyType k)
{
	BinSTreeNode *f, *p, *q, *s;
	p = bt;
	f = NULL;
	//查找关键字为k的结点，同时将此结点的双亲找出来
	while (p && p->key != k)
	{
		f = p;  //f为双亲
		if (p->key > k)
			p = p->lchild;
		else
			p = p->rchild;
	}
	if (p == NULL)   //找不到待删除的结点时返回
		return 0;
	if (p->lchild == NULL)  //待删除结点的左子树为空
	{
		if (f == NULL)  //待删除结点为根节点
			bt = p->rchild;
		else if (f->lchild == p)  //待删结点是其双亲结点的左节点
			f->lchild = p->rchild;
		else
			f->rchild = p->rchild;  //待删结点是其双亲结点的右节点
		delete p;
	}
	else                    //待删除结点有左子树，相当于有二个节点
	{
		q = p;
		s = p->lchild;
		while (s->rchild)  //在待删除结点的左子树中查找最右下结点
		{
			q = s;
			s = s->rchild;  //找左子树的最大值
		}
		if (q == p)
			q->lchild = s->lchild;
		else
			q->rchild = s->lchild;

		p->key = s->key;
		delete s;
	}
	return 1;
}
int main(void)
{
	int a[NUM] = { 34, 18, 76, 13, 52, 82, 16, 67, 58, 73, 72 };
	int i;
	BinSTree bst;
	BinSTreeNode *pBt = NULL, *p = NULL, *pT = NULL;

	for (i = 0; i < NUM; i++)
	{
		bst.BSTreeInsert(pBt, a[i]); //创建二叉排序树
	}
	pT = bst.BSTreeSearch(pBt, 52, p); //搜索排序二叉树
	bst.BSTreePreOrder(pBt);
	cout << endl;
	bst.BSTreeDelete(pBt, 13);   //删除无左孩子的情况
	bst.BSTreePreOrder(pBt);
	cout << endl;
	bst.BSTreeDelete(pBt, 76);   //删除有左孩子的情况
	bst.BSTreePreOrder(pBt);
	cout << endl;
	return 0;
}