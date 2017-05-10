#include<iostream>
#include<windows.h>
using namespace std;
typedef int semaphore;
semaphore rmutex=1,wmutex=1;
int readcount=0;
int signal(semaphore &S)
{
	S++;
	return 0;
}
int wait(semaphore &S)
{
	while(S<=0);
	S--;
	return 0;
}
DWORD WINAPI Reader(LPVOID lpParameter)
{
	do{
		wait(rmutex);
		if(readcount==0)wait(wmutex);
		readcount++;
		signal(rmutex);
		cout<<"Reading...\n";
		Sleep(2000);
		wait(rmutex);
		readcount--;
		if(readcount==0)
			signal(wmutex);
		signal(rmutex);

	}while(true);
	return 0;
}

DWORD WINAPI Writer(LPVOID lpParameter)
{
	do{
		wait(wmutex);
		cout<<"Writing...\n";
		Sleep(3000);
		signal(wmutex);
	
	}while(true);

}
int main()
{
	HANDLE handle[2];
	handle[0]=CreateThread(NULL,0,Reader,NULL,0,NULL);
	handle[1]=CreateThread(NULL,0,Writer,NULL,0,NULL);
	WaitForMultipleObjects(2,handle,true,-1);
	return 0;
}