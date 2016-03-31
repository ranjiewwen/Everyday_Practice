//有一棵二叉树，树上每个点标有权值，权值各不相同，请设计一个算法算出权值最大的叶节点到权值最小的叶节点的距离。
//二叉树每条边的距离为1，一个节点经过多少条边到达另一个节点为这两个节点之间的距离。
//给定二叉树的根节点root，请返回所求距离。


#include<iostream>
using namespace std;
#include<vector>
struct TreeNode {

	int val;

	struct TreeNode *left;

	struct TreeNode *right;

	TreeNode(int x) :

		val(x), left(nullptr), right(nullptr) {
	}
};


//1注意点 权值最大的叶子节点到权值最小的叶子节点,不是所有的节点,是叶子结点
//2.用俩个变量标记俩个节点的位置,求出根节点到他们的路径,如果有重复的路径就减去重复的路径的长度.

class Tree {
	void Inorder(TreeNode *root, vector<int>&v, int &small, int &big){
		//中序遍历获得最小的叶节点和最大的叶节点的索引
		if (!root)
			return;
		Inorder(root->left, v, small, big);
		v.push_back(root->val);
		if (root->left == NULL&&root->right == NULL){    //叶子节点   //跟着遍历的过程走，第一个叶子结点，samll=big，v里面加值，
			if (small == -1 || big == -1)
				small = big = (int)v.size() - 1;
			else{                                                    //第二个叶子结点，samll=big！=-1，v里面有第一个节点到到第二个叶子结点的路径值，比较改变samll和big的值
				if (root->val<v[small]) small = (int)v.size() - 1;
				if (root->val>v[big])   big = (int)v.size() - 1;
			}
		}
		Inorder(root->right, v, small, big);
	}
public:
	int getDis(TreeNode* root) {
		int small = -1, big = -1;
		vector<int>v;
		Inorder(root, v, small, big);  //v里面为中序遍历的节点值
		TreeNode * p = root;
		vector<int>v1, v2;
		int pos;
		while (true) {    //寻找路径
			pos = (int)(find(v.begin(), v.end(), p->val) - v.begin());//找到根节点的索引
			v1.push_back(v[pos]);  //存储的是根节点到最小目标节点的路径值
			if (small>pos)         //索引比较
				p = p->right;
			else if (small<pos)
				p = p->left;
			else
				break;
		}
		p = root;
		while (true) {
			pos = (int)(find(v.begin(), v.end(), p->val) - v.begin());
			v2.push_back(v[pos]);
			if (big>pos)
				p = p->right;
			else if (big<pos)
				p = p->left;
			else
				break;
		}
		int i, j;
		for (i = 0, j = 0; j<v2.size() - 1 && i<v1.size() - 1; ++i, ++j) {   //去重
			if (!(v1[i] == v2[j] && v1[i + 1] == v2[j + 1]))
				break;
		}
		return (int)v1.size() - 1 + (int)v2.size() - 1 - 2 * i;  //i为前面有几个相同的
	}
};
