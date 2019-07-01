#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;

int JaRitSu(int Number)
{
	int Result = 0;
	int Temp = 0;

	while (true)
	{
		Temp = Number % 10;
		Number /= 10;

		Result += Temp;

		if (Number == 0)
			break;
	}
	return Result;
}

int main()
{
	cout << JaRitSu(1024) << endl;
}

