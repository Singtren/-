#include<iostream>
#include <windows.h>
using namespace std;
const int n=5;
int in=0,out=0;
typedef int item;
typedef int semaphore;
semaphore mutex=1,Empty=n,full=0;
item buffer[n];
void wait (semaphore &S)
{
	while(S<=0);
	S--;
}
void signal (semaphore &S)
{
	S++;
}
DWORD WINAPI producer (LPVOID lpParameter)
{
	do
	{
		item  nextp=rand();
		Sleep(1000);
		wait (Empty);
		wait (mutex);
		buffer[in]=nextp;
		cout<<"producer an item: "<<nextp<<" in buffer "<<in<<endl;
		in=(in+1)%n;
		signal(mutex);
		signal(full);

	}while (TRUE);
	return 0;
}
DWORD WINAPI concumer (LPVOID lpParameter)
{
	do
	{
		
		wait (full);
		wait (mutex);
		item nextc=buffer[out];
		cout<<"concumer an item: "<<nextc<<" in buffer "<<out<<endl;
		Sleep(2000);
		out=(out+1)%n;
		signal(mutex);
		signal(Empty);

	}while (TRUE);
	return 0;
}
int main()
{
	HANDLE handle[2];
	handle[0]=CreateThread(NULL,0,producer,NULL,0,NULL);//创建线程
	handle[1]=CreateThread(NULL,0,concumer,NULL,0,NULL);
	WaitForMultipleObjects(2,handle,TRUE,-1);//等待线程
	return 0;
}
