#include "pch.h"
#include <iostream>
#include <random>
#include <time.h>
using namespace std;

void Sort(int* Arr, size_t left, size_t center, size_t right)
{
	int TempArr[1000] = {};

	int i = left;
	int j = center + 1;
	int k = 0;

	while (i <= center && j <= right)
	{
		if (Arr[i] < Arr[j])
		{
			TempArr[k] = Arr[i];
			i++;
			k++;
		}
		else
		{
			TempArr[k] = Arr[j];
			j++;
			k++;
		}
	}

	while (i <= center)
	{
		TempArr[k] = Arr[i];
		i++;
		k++;
	}

	while (j <= right)
	{
		TempArr[k] = Arr[j];
		j++;
		k++;
	} 

	for (size_t i = 0; i < right - left + 1; i++)
		Arr[i + left] = TempArr[i];
}

void MergeSort(int* Arr, size_t left, size_t right)
{
	if (right - left <= 0)
		return;

	int Center = (right + left) / 2;

	//분할
	MergeSort(Arr, left, Center);
	MergeSort(Arr, Center + 1, right);

	//정복
	Sort(Arr, left, Center, right);
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

	MergeSort(Arr, 0, 100);

	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
			cout << Arr[i * 10 + j] << '\t';

		cout << endl;
	}
}
