
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};
class Solution {
public:
    int TreeDepth(TreeNode* pRoot)
    {
    if(!pRoot)
		return 0;
	else
		return TreeDepth(pRoot->left)>TreeDepth(pRoot->right)?(TreeDepth(pRoot->left)+1):(TreeDepth(pRoot->right)+1);
    }
	
	int TreeDepth(TreeNode* pRoot)
    {
     queue<TreeNode*> q;
        if(!pRoot) return 0;
        q.push(pRoot);
        int level=0;
        while(!q.empty()){
            int len=q.size();
            level++;
            while(len--){
                TreeNode* tem=q.front();
                q.pop();
                if(tem->left) q.push(tem->left);
                if(tem->right) q.push(tem->right);
            }
        }
        return level;
    }
};


#include <iostream>
#include <string>
#include<iterator>

using namespace std;

int main()
{
   string str;
   getline(cin,str);
   auto it=str.cend()-1;
   for(;it!=str.cbegin();it--)
      {
          cout<<*it;
      }
   cout<<*it--;
}


#include<iostream>
#include<string>
using namespace std;
class Reverse {
public:
    string reverseString(string iniString) {
        // write code here
        //string result;
        if(iniString.empty())
        {
            return  iniString;
        }
        //for (int i = iniString.size(); i >0; i--)  //error: control reaches end of non-void function [-Werror,-Wreturn-type]  //没有返回值啊
        //{
        //    cout << iniString[i - 1];
        //}
        //两个数字交换，可以借助第三变量，也可以不借助第三变量；有三种方法，自行总结
        //iniString[i] ^= iniString[j] ^= iniString[i] ^= iniString[j];//交换  
        for (int i = 0; i < iniString.size()/2; i++)
        {
            char temp = iniString[i];
            iniString[i] = iniString[iniString.size() - 1 - i];
            iniString[iniString.size() - 1 - i] = temp;
        }

        return iniString;
    }
};

int main()
{
	string str;
	getline(cin,str);
    Reverse s;
    cout<<s.reverseString(str)<<endl;
    return 0;
}


/*
法一：因为数组从左到右递增，从上到下递增，所以从左下角来看，
      从左到右递增，从下到上递减。在搜索时，当前元素比target大时，指针向右移动；
      当前元素比target小时，指针向上移动；相等时输出true. 
    最坏时间复杂度：O(M+N),N×M的矩阵
*/
      
bool Find(vector<vector<int> > array,int target) {
    int i = array.size() - 1;
    int j = 0;
    //从左下角开始搜索
    while (i>=0 && j<array[i].size()){
        if (array[i][j] == target){
            return true;
        }else if (array[i][j] < target){
            j++;
        }else{
            i--;
        }
    }
    return false;
}
 
/*
    法二：因为每一行都有序，所以对每一行都执行二分查找：O(NlogM),N×M的矩阵
*/ bool Find(vector<vector<int> > array,int target) { for (int i=0; i<(int)array.size(); i++){
            int low = 0;
            int high = array[i].size();
            int mid = (low+high)/2;
            while (low < high){
                if (target == array[i][mid]){
                    return true;
                }
                if (target<array[i][mid]){
                    high = mid - 1;
                }else{
                    low = mid + 1;
                }
                mid = (low + high)/2;
            }
           if (low < array[i].size() && array[i][low] == target){
        return true;
       }
        }//for
        return false;
}
 
/*
    法三：暴力：O(MN)
*/ bool Find(vector<vector<int> > array,int target) 
	{  
	for(int i=0; i<array.size(); i++){
			for (int j=0; j<array[i].size(); j++){ 
				if(array[i][j] == target)  return true; 
				}
			}
		return false;
	}