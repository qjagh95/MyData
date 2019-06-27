#include "pch.h"
#include <iostream>
#include <vector>

#define min(a,b)            (((a) < (b)) ? (a) : (b))
using namespace std;

int GetDivisor(int Input)
{
	int Number = Input;
	int Result = 0;
	int Divide = 2;

	while (true)
	{
		if (Number % Divide == 0)
			Result += Divide;

		Divide++;

		if (Divide == Number)
			break;
	}

	Result += Number;

	return Result;
}

int GetSoSu(int Input, vector<int> commend)
{
	vector<int> DevideVec;

	int Number = Input;
	int Result = 0;
	int Divide = 2;

	for (int i = 1; i <= Input; i++)
	{
		if (i < 10)
		{
			if (i == 2 || i == 3 || i == 5 || i == 7)
				DevideVec.push_back(i);
		}
		else
		{
			if (i % 2 != 0 && i % 3 != 0 && i % 5 != 0 && i % 7 != 0)
				DevideVec.push_back(i);
		}
	}

	int Num1 = commend[0];
	int Num2 = commend[1];

	for (size_t j = 0; j < DevideVec.size(); j++)
	{
		if (Num1 >= j && Num2 <= j)
			continue;
		else
			Result += DevideVec[j];
	}
	return Result;
}

//최대 공약수
int GreatestCommon(int Number1, int Number2)
{
	while (Number2 > 0)
	{
		int temp = Number2;
		Number2 = Number1 % Number2;
		Number1 = temp;
	}
	return Number1;
}

//최소 공배수
int CommonMultiple(int Number1, int Number2)
{
	return (Number1 * Number2) / GreatestCommon(Number1, Number2);
}

int main()
{
	//약수구하기
	//cout << GetDivisor(10) << endl;

	//소수구하기
	//cout << GetSoSu(20, {0, 0}) << endl;

	//최대 공약수
	//cout << GreatestCommon(5, 10) << endl;

	//최소 공배수
	cout << CommonMultiple(5, 10) << endl;
}
