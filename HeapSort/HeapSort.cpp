#include "pch.h"
#include <iostream>
#include <random>
#include <time.h>
using namespace std;

void heapify(int* arr, int size, int mid) 
{
	int parent_node = mid; 
	int left_node = parent_node * 2 + 1; 
	int right_node = parent_node * 2 + 2;
	int largest_node = parent_node;
	int temp;

	if (left_node < size && arr[left_node] > arr[largest_node]) 
		largest_node = left_node;
	if (right_node < size && arr[right_node] > arr[largest_node]) 
		largest_node = right_node;
	
	if (parent_node != largest_node) 
	{
		temp = arr[largest_node];
		arr[largest_node] = arr[parent_node];
		arr[parent_node] = temp;
		heapify(arr, size, largest_node);
	}
}

void buildMaxHeap(int* arr, int size)
{
	int mid = size / 2 - 1;

	for (mid; mid >= 0; mid--) 
		heapify(arr, size, mid);
}


void heapSort(int* arr, int size)
{
	buildMaxHeap(arr, size);

	int temp;
	while (size > 1) 
	{
		temp = arr[0];
		arr[0] = arr[size - 1];
		arr[size - 1] = temp;

		size--;
		heapify(arr, size, 0);
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

	heapSort(Arr, 100);

	for (size_t i = 0; i < 100; i++)
	{
		for (size_t j = 0; j < 10; j++)
			cout << Arr[i * 100 + j] << '\t';

		cout << endl;
	}
}
