#include "pch.h"
#include <iostream>
using namespace std;

int ViralMarketing(int days)
{
	int Date = days;
	int Number = 3;
	int Next = 0;
	int Result = 0;
	int Select = 5;

	for (int i = 1; i <= days; i++)
	{
		int Divide = Select / 2;
		Next = Divide * 3;
		Result += Divide;
		Select = Next;
	}

	cout << Result << endl;
	return Result;
}

int main()
{
	ViralMarketing(3);
}

