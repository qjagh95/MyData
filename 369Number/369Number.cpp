#include "pch.h"
#include <iostream>
using namespace std;

void Output(int Number)
{
	for (size_t i = 1; i < Number + 1; i++)
	{
		cout << i << " : ";

		int getNumber = i;
		while (true)
		{
			if (getNumber % 10 == 3 || getNumber % 10 == 6 || getNumber % 10 == 9)
				cout << "Clap ";

			getNumber /= 10;

			if (getNumber == 0)
				break;
		}

		cout << endl;
	}
}
//
//int GetRevers(int Num)
//{
//	int getNum = Num;
//	int Result = 0;
//
//	while (getNum != 0)
//	{
//		Result = getNum % 10 + Result * 10;
//		getNum /= 10;
//	}
//
//	return Result;
//}
//
//void Func(int Num1, int Num2)
//{
//	int GetNum1 = GetRevers(Num1);
//	int GetNum2 = GetRevers(Num2);
//
//	int Result = GetRevers(GetNum1 + GetNum2);
//
//}

string Get16(int Hex)
{
	string Result;

	switch (Hex)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		Result += itoa(Hex);
		break;
	case 10:
		break;
		Result += "A";
	case 11:
		break;
		Result += "B";

	case 12:
		break;
		Result += "C";

	case 13:
		break;
		Result += "D";

	case 14:
		Result += "E";
		break;

	case 14:
		Result += "F";
		break;
	}

	return Result;
}

string GetHex(int Color)
{
	string Result;
	stack<int> NumStack;
	int getNum = Color;

	while (getNum != 0)
	{
		NumStack.push(getNum % 16);
		getNum /= 16;
	}
	
	if (NumStack.size() == 0)
		Result += "00";
	else if (NumStack.size() == 1)
	{
		Result += "0";
		Result += Get16(NumStack.top());
	}
	else
	{
		size_t StackSize = NumStack.size();
		for (size_t i = 0; i < StackSize; i++)
		{
			Result += Get16(NumStack.top());
			NumStack.pop();
		}
	}
}

string Func(int R, int G, int B)
{
	string Result;
	Result += GetHex(R);
	Result += GetHex(G);
	Result += GetHex(B);

	return Result;
}

int main()
{
	Output(100);
}

