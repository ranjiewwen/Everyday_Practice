
//已知集合A和B的元素分别用不含头结点的单链表存储，函数difference()用于求解集合A与B的差集，并将结果保存在集合A的单链表中。
//例如，若集合A = { 5, 10, 20, 15, 25, 30 }，集合B = { 5, 15, 35, 25 }，完成计算后A = { 10, 20, 30 }。

#include<stdio.h>
#include<stdlib.h>
struct node
{
	int elem;
	node* next;
};

void difference(node** LA, node* LB)
{
	node *pa, *pb, *pre, *q;
	pre = nullptr;
	pa = *LA; //1   
	while (pa)  
	{
		pb = LB;
		while (pb&&pb->elem!=pa->elem)   //2   
			pb = pb->next;
		if (pb)    //不为空，说明有相同的，为空即没有相同的             
		{
			if (!pre)  //为空
				*LA = pa->next;     //4   
			else
				*LA = pre->next;     //5
			q = pa;
			pa = pa->next;
			free(q);
		}
		else  
		{
			pre=pa;             //6   
			pa = pa->next;
		}
	}
}


