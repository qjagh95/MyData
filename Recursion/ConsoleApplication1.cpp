#include "pch.h"
#include <iostream>

using namespace std;

int Factory(int Number)
{
	if (Number == 0)
		return 1;

	int a = Number;
	int b = Factory(Number - 1);
	int c = a * b;
	return c;
}

int Fibo(int Number)
{
	if (Number == 0)
		return 1;

	else if (Number == 1)
		return 1;

	return Fibo(Number - 1) + Fibo(Number - 2);
}

int BinerySeach(int* Arr, int Size, int FindNumber)
{
	int First = 0;
	int Last = Size - 1;

	while (First <= Last)
	{
		int Center = (First + Last) / 2;
		
		if (Arr[Center] == FindNumber)
			return Center;

		else if (Arr[Center] > FindNumber)
			Last = Center + 1;

		else if (Arr[Center] < FindNumber)
			First = Center - 1;
	}

	return -1;
}

void Hanoi(int Number, char From, char By, char To)
{
	if (Number == 1)
		cout << "원반 1을" << From << "에서" << To << "로 이동" << endl;
	else
	{
		Hanoi(Number - 1, From, To, By);
		cout << "원반 " <<Number<< "을" << From << "에서" << To << "로 이동" << endl;
		Hanoi(Number - 1, By, From, To);
	}
}


int main()
{
	//cout << Factory(3) << endl;
	//for (size_t i = 0; i < 15; i++)
	//	cout << Fibo(i) << endl;d

	//int Arr[10] = { 1, 3, 5, 7, 9, 16, 32, 64, 128, 256 };
	//cout << BinerySeach(Arr, 10, 32) << endl;

	Hanoi(5, 'A', 'B', 'C');
 }
