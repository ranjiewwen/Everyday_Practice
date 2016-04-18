#include<Windows.h>
#include<iostream>
using namespace std;
DWORD WINAPI Fun1Proc(LPVOID lpParameter);
DWORD WINAPI Fun2Proc(LPVOID lpParameter);
int index=0;
int tickets=100;
void main()
{
	HANDLE hThread1;
	HANDLE hThread2;
	hThread1=CreateThread(NULL,0,Fun1Proc,NULL,0,NULL);
	hThread2=CreateThread(NULL,0,Fun2Proc,NULL,0,NULL);
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	system("pause");
}
DWORD WINAPI Fun1Proc(LPVOID lpParameter)
{
	while(TRUE)
	{
		if(tickets>0)
			cout<<"thread1 sell ticket:"<<tickets--<<endl;
		else 
			break;
	}
	return 0;
}
DWORD WINAPI Fun2Proc(LPVOID lpParameter)
{
	while(TRUE)
	{
		if(tickets>0)
			cout<<"thread2 sell ticket:"<<tickets--<<endl;
		else 
			break;
	}
	return 0;
}