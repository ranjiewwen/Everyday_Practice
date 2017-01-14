
#include <iostream>
#include <cmath>
#include <ctime>
#include <windows.h>

using namespace std;

//得到循环0xFFFFFFFF次用的秒数
unsigned int test()
{
	unsigned int c = 0xFFFFFFFF;

	time_t t1, t2;
	time(&t1);

	for (unsigned int i = 0; i < c; i++)
		;
	time(&t2);
	return (unsigned int)(t2 - t1);

}

#define T  20000                                          //周期时间 20秒
#define C  100                                            //采样点时间间隔
#define PI 3.1415                                         //PI

const unsigned int _count = 0xFFFFFFFF / (test() * 1000);    //采样间隔可以执行的循环数目
const unsigned int N = T / C;                                //周期内采样点数目
unsigned int v[N] = { 0 };                                   //所有采样点连续执行循环数
unsigned int mt[N] = { 0 };                                  //所有采样点休眠毫秒数

int main()
{
	//指定运行CPU
	SetThreadAffinityMask(GetCurrentThread(), 1);
	
	////正弦cpu
	//for (int i = 0; i < N; i++)
	//{
	//	double x = 2 * PI * i / N;
	//	double r = (sin(x) + 1) / 2;

	//	mt[i] = C - r * C;
	//	v[i] = r * C * _count;
	//}
	//for (;;)
	//{
	//	for (int i = 0; i < N; i++)
	//	{
	//		for (int j = 0; j < v[i]; j++)
	//			;
	//		Sleep(mt[i]);
	//	}
	//}

	//直线cpu
	for (int i = 0; i < N; i++)
	{
		double x = 2 * PI * i / N;
		x = 0;
		double r = (sin(x) + 1) / 2;

		mt[i] = C - r * C;
		v[i] = r * C * _count;
	}
	for (;;)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < v[i]; j++) 
				;
			Sleep(mt[i]);
		}
	}
}

//没有考虑现在系统cpu使用情况
//#include <windows.h>
//#include <math.h>
//int main(void)
//{
//	SetThreadAffinityMask(GetCurrentProcess(), 1);
//	const double SPLIT = 0.01;
//	const int COUNT = 200;
//	const double PI = 3.14159265;
//	const int INTERVAL = 300;
//	DWORD busySpan[COUNT]; //array of busy time
//	DWORD idleSpan[COUNT]; //array of idle time
//	int half = INTERVAL / 2;
//	double radian = 0.0;
//	for (int i = 0; i < COUNT; i++)
//	{
//		busySpan[i] = (DWORD)(half + (sin(PI*radian)*half));
//		idleSpan[i] = INTERVAL - busySpan[i];
//		radian += SPLIT;
//	}
//	DWORD startTime = 0;
//	int j = 0;
//	while (true)
//	{
//		j = j%COUNT;
//		startTime = GetTickCount();
//		while ((GetTickCount() - startTime) <= busySpan[j])
//			;
//		Sleep(idleSpan[j]);
//		j++;
//	}
//	return 0;
//}