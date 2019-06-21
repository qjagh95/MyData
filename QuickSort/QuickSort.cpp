#include "pch.h"
#include <iostream>
#include <random>
#include <time.h>
using namespace std;

void Sort(int* Arr, size_t left, size_t center, size_t right)
{

}

void QuickSort(int* Arr, size_t left, size_t right)
{

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

	QuickSort(Arr, 0, 100);

	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
			cout << Arr[i * 10 + j] << '\t';

		cout << endl;
	}
}
