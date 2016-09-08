
#include <iostream>
using namespace std;

#define MAX 26
typedef struct TrieNode
{
	bool isStr; //标记该节点处是否构成单词
	struct TrieNode *next[MAX];//儿子分支
}Trie;

void insert(Trie *root,const char *s)
{
	if (root==nullptr||*s=='\0')
	{
		return;
	}
	int i;
	Trie *p = root;
	while (*s!='\0')
	{
		if (p->next[*s-'a']==nullptr)
		{
			Trie *temp = (Trie*)malloc(sizeof(Trie));
			for (i = 0; i < MAX;i++)
			{
				temp->next[i] = nullptr;
			}
			temp->isStr = false;
			p->next[*s - 'a'] = temp;
			p = p->next[*s - 'a'];
		}
		else
		{
			p = p->next[*s - 'a'];
		}
		s++;
	}
	p->isStr = true;//单词结束的位置标记此处可以构成一个单词
}

int search(Trie* root, const char *s)
{
	Trie *p = root;
	while (p!=nullptr&&*s!='\0')
	{
		p = p->next[*s-'a'];
		s++;
	}
	return (p!=nullptr&&p->isStr==true);
}

void del(Trie *root)
{
	for (int i = 0; i < MAX;i++)
   {
		if (root->next[i]!=nullptr)
		{
			del(root->next[i]);
		}
   }
	free(root);
}



int main(int argc, char *argv[])
{
	int n, m;//n为建立Trie树输入的单词数；m为要查找的单词数
	FILE *p;
	char s[100];
	Trie *root = (Trie*)malloc(sizeof(Trie));
	for (int i = 0; i < MAX;++i)
	{
		root->next[i] = nullptr;
	}
	root->isStr = false;
	cout << "输入n:\n";
	cin >> n;
	//getchar();
	cout << "输入"<<n<<"个单词：\n";
	for (int i = 0; i < n;++i)
	{
		cin >> s;
		insert(root, s);
		
	}
	while (scanf("%d",&m)!=EOF)
	{
		cout << "输入m个单词查找，并显示结果：\n";
		for (int i = 0; i < m;++i)
		{
			cin >> s;
			if (search(root,s)==1)
			{
				cout << "YES\n";
			}
			else
			{
				cout << "NO\n";
			}
		}
	}
	del(root);
	return 0;
}



//int main()
//{
//	char str='a';
//	cout << (int)str << endl;
//}