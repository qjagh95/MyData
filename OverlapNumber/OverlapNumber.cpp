#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;

void Output(int Arr1[4], int Arr2[4], int Arr3[4])
{
	vector<int> OverlapNum;
	//1번
	for (size_t i = 0; i < 4; i++)
	{
		int Index = i + 1;

		if (i >= 3)
			Index = 3;

		if (Arr1[i] == Arr1[Index] && Index != 3)
			OverlapNum.push_back(Arr1[i]);

		for (size_t j = 0; j < 4; j++)
		{
			if (Arr1[i] == Arr2[j])
				OverlapNum.push_back(Arr1[i]);
		}

		for (size_t k = 0; k < 4; k++)
		{
			if (Arr1[i] == Arr3[k])
				OverlapNum.push_back(Arr1[i]);
		}
	}

	for (size_t i = 0; i < 4; i++)
	{
		int Index = i + 1;

		if (i >= 3)
			Index = 3;

		if (Arr2[i] == Arr2[Index] && Index != 3)
			OverlapNum.push_back(Arr2[Index]);

		for (size_t j = 0; j < 4; j++)
		{
			if (Arr2[i] == Arr1[j])
				OverlapNum.push_back(Arr2[i]);
		}

		for (size_t k = 0; k < 4; k++)
		{
			if (Arr2[i] == Arr3[k])
				OverlapNum.push_back(Arr2[i]);
		}
	}

	for (size_t i = 0; i < 4; i++)
	{
		int Index = i + 1;

		if (i >= 3)
			Index = 3;

		if (Arr3[i] == Arr3[Index] && Index != 3)
			OverlapNum.push_back(Arr3[i]);

		for (size_t j = 0; j < 4; j++)
		{
			if (Arr3[i] == Arr1[j])
				OverlapNum.push_back(Arr3[i]);
		}

		for (size_t k = 0; k < 4; k++)
		{
			if (Arr3[i] == Arr2[k])
				OverlapNum.push_back(Arr3[i]);
		}
	}

	cout << "Arr1 : ";
	bool isCompair = false;
	for (size_t i = 0; i < 4; i++)
	{
		isCompair = false;

		for (size_t j = 0; j < OverlapNum.size(); j++)
		{
			if (Arr1[i] == OverlapNum[j])
			{
				isCompair = true;
				break;
			}
		}

		if (isCompair == false)
			cout << Arr1[i] << " ";
	}
	cout << endl;

	cout << "Arr2 : ";
	isCompair = false;
	for (size_t i = 0; i < 4; i++)
	{
		isCompair = false;

		for (size_t j = 0; j < OverlapNum.size(); j++)
		{
			if (Arr2[i] == OverlapNum[j])
			{
				isCompair = true;
				break;
			}
		}

		if (isCompair == false)
			cout << Arr2[i] << " ";
	}
	cout << endl;

	cout << "Arr3 : ";
	isCompair = false;
	for (size_t i = 0; i < 4; i++)
	{
		isCompair = false;

		for (size_t j = 0; j < OverlapNum.size(); j++)
		{
			if (Arr3[i] == OverlapNum[j])
			{
				isCompair = true;
				break;
			}
		}

		if (isCompair == false)
			cout << Arr3[i] << " ";
	}
	cout << endl;
}


int main()
{
	int Arr1[4] = {5, 6, 7, 8};
	int Arr2[4] = {1, 3, 5, 7};
	int Arr3[4] = {2, 3, 8, 9};
	
	Output(Arr1, Arr2, Arr3);

	/*
	기대 결과
	Arr1 : 6
	Arr2 : 1 
	Arr3 : 2 9
	*/
}
