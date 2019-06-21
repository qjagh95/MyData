#include "pch.h"
#include <iostream>
#include <random>
#include <time.h>
using namespace std;

void InsertSort(int* Arr, size_t size)
{
	int SIndex = 0;

	for (size_t i = 1; i < size; i++)
	{
		int getData = Arr[i];	
		SIndex = i - 1;

		while (SIndex >= 0 && Arr[SIndex] > getData)
		{
			Arr[SIndex + 1] = Arr[SIndex];
			SIndex--;
		} 

		Arr[SIndex + 1] = getData;
	}
}

int main()
{
	srand(time(0));

	int Arr[100] = {};

	for (size_t i = 0; i < 100; i++)
		Arr[i] = i + 1;

	for (size_t i = 0; i < 100; i++)
	{
		int Dest = rand() % 100;
		int Src = rand() % 100;

		int Temp = Arr[Src];
		Arr[Src] = Arr[Dest];
		Arr[Dest] = Temp;
	}

	//선택정렬
	InsertSort(Arr, 100);

	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
			cout << Arr[i * 10 + j] << '\t';

		cout << endl;
	}
}
