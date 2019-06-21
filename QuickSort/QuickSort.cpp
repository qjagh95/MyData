#include "pch.h"
#include <iostream>
#include <random>
#include <time.h>
using namespace std;

int Partition(int* Arr, size_t left, size_t right)
{
	int Pivot = Arr[right];
	int i = left - 1;

	for (size_t j = left; j < right; j++)
	{
		if (Arr[j] > Pivot)
		{
			int Temp = Arr[i];
			Arr[i] = Arr[j];
			Arr[j] = Temp;
			i++;
		}
	}

	int Temp = Arr[i + 1];
	Arr[i + 1] = Arr[right];
	Arr[right] = Temp;

	return i + 1;
}

void QuickSort(int* Arr, size_t left, size_t right)
{
	if (left > right)
		return;

	int Part = Partition(Arr, left, right);

	QuickSort(Arr, left, Part - 1);
	QuickSort(Arr, Part + 1, right);
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

	QuickSort(Arr, 0, 99);

	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
			cout << Arr[i * 10 + j] << '\t';

		cout << endl;
	}
}
