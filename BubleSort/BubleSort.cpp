#include "pch.h"
#include <iostream>
#include <random>
#include <time.h>
using namespace std;

void BubbleSort(int* Arr, size_t size)
{
	for (size_t i = 0; i < size - 1; i++)
	{
		for (size_t j = 1; j < size - i; j++)
		{
			if (Arr[j] < Arr[j - 1])
			{
				int Temp = Arr[j];
				Arr[j] = Arr[j - 1];
				Arr[j - 1] = Temp;
			}
		}
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
	BubbleSort(Arr, 100);

	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
			cout << Arr[i * 10 + j] << '\t';

		cout << endl;
	}
}
