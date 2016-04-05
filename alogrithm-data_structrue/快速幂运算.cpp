//矩阵快速幂

//矩阵的快速幂是用来高效地计算矩阵的高次方的。将朴素的o（n）的时间复杂度，降到log（n）。

#include<iostream>
using namespace std;
int N;
struct matrix
{
	int a[3][3];
}origin,res;

matrix multiply(matrix x, matrix y)
{
	matrix temp;
	memset(temp.a,0,sizeof(temp.a));
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			for (size_t k = 0; k < 3; k++)
			{
				temp.a[i][j] += x.a[i][k] * y.a[k][j];
			}
		}
	}
	return temp;
}

void init()
{
	printf("随机数组如下：\n");
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			origin.a[i][j] = rand() % 10;
			printf("%d",origin.a[i][j]);
			printf("\t");
		}
		printf("\n");
	}
	printf("\n");
	memset(res.a,0,sizeof(res.a));
	res.a[0][0] = res.a[1][1] = res.a[2][2]=1; //初始化为单位矩阵
}

void calc(int n)
{
	printf("%d次幂结果如下：\n", n);
	while (n)
	{
		if (n&1)
		{
			res = multiply(res,origin);  //单位矩阵和任何矩阵相乘等于矩阵本身 A^156=>(A^4)*(A^8)*(A^16)*(A^128) 提取有用的origin进行相乘
		}
		n >>= 1;
		origin = multiply(origin, origin);  //这里还是在累乘
	}

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			printf("%d",res.a[i][j]);
			printf("\t");
		}
		printf("\n");
	}
	printf("\n");
}

int main()
{
	while (cin>>N)
	{
		init();
		calc(N);
	}
	return 0;
}