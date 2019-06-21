#include "pch.h"
#include <iostream>
#include <random>
#include <time.h>
using namespace std;

void QuickSort(int* Arr, int left, int right)
{
	if (right - left < 1)
		return;

	int Pivot = left;
	int i = left + 1;
	int j = right;

	while (i <= j)
	{
		//왼쪽부터 키값보다 큰 값의 인덱스 탐색
		while (Arr[i] <= Arr[Pivot])
			i++;

		//오른쪽부터 키값보다 작은 인덱스 탐색
		while (Arr[j] > Arr[Pivot])
			j--;

		//엇갈렸다면
		if (i > j)
		{
			int Temp = Arr[j];
			Arr[j] = Arr[Pivot];
			Arr[Pivot] = Temp;
		}
		else
		{
			int Temp = Arr[i];
			Arr[i] = Arr[j];
			Arr[j] = Temp;
		}
	}

	QuickSort(Arr, left, j - 1);
	QuickSort(Arr, j + 1, right);
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

	for (size_t i = 0; i < 100; i++)
		cout << Arr[i] << endl;

}
