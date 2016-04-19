#include <iostream.h>
#include<time.h>
#include<windows.h>
#include<string.h>
#include<stdio.h>
const int max_linjiequ_num=77;     
const int max_thread_num=88;        

struct thread      
{
	int flag;                                 //标记进程是否已执行
	int num;                                 //进程号
	char p_c;                                
	int time;                                //进程等待时间
	int thread_request[max_thread_num];      
	int request_num;                         
};

struct linjiequ     
{
	int biaoji;     //用以标记临界区状态，-1表示该缓冲区为空，1表该缓冲区将被生产者进程使用
	int p_num;      
};

linjiequ linjiequ[max_linjiequ_num];    //用该数组模拟缓冲区序列
thread thread[max_thread_num];      
int thread_num;                    //实际进程数
int linjiequ_num;                  


int findposition()         
{
	int n;int mutex;                         //模拟互斥信号量
	for(int i=0;i<max_linjiequ_num;i++)
	{
		if(linjiequ[i].biaoji==-1)
		{
			n=i;
			linjiequ[i].biaoji=1;  
			break;
		}
	}
	return n;
}

bool otherrequest(int n)         //判断是否还有对同一产品的消费请求未执行
{
	for(int i=0;i<thread_num;i++)
		for(int j=0;j<thread[i].request_num;j++)
		{
			if(thread[i].thread_request[j]==n)
				return true;
			break;
		}
	return false;
}

int little()
{
	int f=0;
	while(thread[f].flag==1)
	{
		f++;
	}
	int a=f,l=thread[f].time;
	for(int w=0;w<thread_num;w++)
	{
		if(thread[w].time<l&&thread[w].flag==0)
		{
			l=thread[w].time;
			a=w;
		}
	}
	return a;
}
void produce()
{
	int m=findposition();
	Sleep(thread[little()].time*1000);
	cout<<thread[little()].num<<"号生产者已经进行了生产，产品放于"<<m<<"号缓冲区中!"<<endl;
	thread[little()].flag=1;
}
void consumer()
{
	int l=thread[little()].request_num;
	for(int i=0;i<=l;i++)
	{
		if(i<l)
		{
			int temp=thread[little()].thread_request[i]-1;
			if(thread[temp].flag==1)
			{
				cout<<thread[little()].num<<"号消费者已成功消费了"<<temp+1<<"号产品!"<<endl;
				if(!otherrequest(temp+1))
				{
					cout<<"已无其他消费者消费"<<temp+1<<"号产品!"<<endl;
					for(int j=0;j<linjiequ_num;j++)
					{
						if(linjiequ[j].p_num==temp+1)
						{
							linjiequ[j].biaoji=-1;
							cout<<temp+1<<"号产品所存放的"<<j+1<<"号临界区已释放!"<<endl;
						}
					}
				}
			}
			else
			{
				cout<<thread[little()].num<<"号消费者需消费的"<<temp+1<<"号产品未生产需等待!"<<endl;
				thread[little()].time++;
				i=l+1;
			}
		}
		else
			thread[little()].flag=1;	
	}
	
}
void main()
{
	//初始化缓冲区
	for(int i=0;i<max_linjiequ_num;i++)
	{
		linjiequ[i].biaoji=-1;
	}
	//初始化线程请求队列，及请求进程的个数
	for(int m=0;m<max_thread_num;m++)
	{
		for(int n=0;n<max_thread_num;n++)            //初始化线程请求队列
			thread[m].thread_request[n]=-1;
		thread[m].request_num=0;                  //初始化请求进程的个数
		thread[m].flag=0;
	}
	
	thread_num=5;
	linjiequ_num=3;

	thread[0].num=1;
	thread[0].p_c='p';
	thread[0].time=3;

	thread[1].num=2;
	thread[1].p_c='p';
	thread[1].time =4;

	thread[2].num=3;
	thread[2].p_c='c';
	thread[2].time=4;
	thread[2].thread_request[0]=1;
	thread[2].request_num=1;

	thread[3].num=4;
	thread[3].p_c='p';
	thread[3].time=2;

	thread[4].num=5;
	thread[4].p_c='c';
	thread[4].time=3;
	thread[4].thread_request[0]=1;
	thread[4].thread_request[1]=2;
	thread[4].thread_request[2]=4;
	thread[4].request_num=3;

	linjiequ[0].p_num=1;

	linjiequ[1].p_num=2;

	linjiequ[2].p_num=4;

	
	cout<<"************生产者-消费者问题****************"<<endl<<endl;

	cout<<"该程序缓冲区总个数为："<<max_linjiequ_num<<endl;

	cout<<endl;

	cout<<"生产者消费者进程信息如下："<<endl;   //回显生产者消费者进程信息
	for(int p=0;p<thread_num;p++)
	{
		cout<<thread[p].num<<'\t'<<thread[p].p_c<<'\t'<<thread[p].time<<'\t';
		if(thread[p].request_num!=0)
		{
			for(int j=0;j<thread[p].request_num;j++)
			{
				cout<<thread[p].thread_request[j]<<'\t';
			}
		}
		cout<<endl<<endl;
	}                                          

	int sum=0;
	for(int q=0;q<thread_num;q++)
	{
		sum+=thread[q].flag;
	}

	while(sum<thread_num)
	{
		int b;
		b=little();
		if(thread[b].p_c=='p')
			produce();
		else
			consumer();	
		sum=0;
		for(int q=0;q<thread_num;q++)
		{
			sum+=thread[q].flag;
		}
	}

}



