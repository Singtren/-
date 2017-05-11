#include<iostream>
#include<Windows.h>
using namespace std;
typedef int semaphore;
semaphore chopstick[5] = { 1,1,1,1,1 };
int Swait(semaphore &S1, semaphore &S2)
{
	while (true)
	{
		if (S1 >= 1 && S2 >= 1)
		{
			S1--;
			S2--;
			break;

		}
		else
		{
			;
		}

	}
	return 0;
}
int Ssignal(semaphore &S1, semaphore &S2)
{
	S1++;
	S2++;

	return 0;
}
DWORD WINAPI P(LPVOID lpParameter)
{
	int *i = (int *)(lpParameter);
	do {
		
		Swait(chopstick[(*i + 1) % 5], chopstick[*i]);
		cout << "philosopher " << *i + 1 << " start eating\n";
		Sleep(2000);		//eating
		cout << "philosopher " << *i + 1 << " start thinking\n";
		Sleep(100);//put down the chopsticks
		Ssignal(chopstick[(*i + 1) % 5], chopstick[*i]);
		Sleep(3000);		//thinking
	} while (true);
}

int main()
{
	int philosopher[5] = { 0,1,2,3,4 };
	HANDLE handle[5];
	for (int i = 0; i < 5; i++)
	{
		handle[i] = CreateThread(NULL, 0, P, &philosopher[i], 0, NULL);
		Sleep(50);
	}
	WaitForMultipleObjects(5, handle, 1, -1);
	return 0;
}