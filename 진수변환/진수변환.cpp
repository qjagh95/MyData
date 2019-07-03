#include "pch.h"
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

void OutPut16(int Number)
{
	switch (Number)
	{
	case 10:
		cout << 'A' << " ";
		break;
	case 11:
		cout << 'B' << " ";
		break;
	case 12:
		cout << 'C' << " ";
		break;
	case 13:
		cout << 'D' << " ";
		break;
	case 14:
		cout << 'E' << " ";
		break;
	case 15:
		cout << 'F' << " ";
		break;
	default:
		cout << Number << " ";
		break;
	}
}

void ConvertJinSu(int Number)
{
	stack<int> myStack;
	vector<int> minusVec;
	int getNumber = Number;
	bool isMinus = false;

	if (Number <= 0)
	{
		Number *= -1;
		isMinus = true;
		minusVec.push_back(1);
	}

	int TwoJinSu = Number;
	int TenJinSu = Number;
	int HexJinSu = Number;
	int OctalJinSu = Number;

	int Index = 0;

	//2진수
	cout << "2 진수로 " << getNumber << "변환" << endl;
	while (TwoJinSu > 0)
	{
		myStack.push(TwoJinSu % 2);
		TwoJinSu /= 2;
	}

	size_t sSize = myStack.size();

	if (isMinus == true)
	{
		for (size_t i = 0; i < sSize; i++)
		{
			if (myStack.top() == 0)
				minusVec.push_back(1);
			else
				minusVec.push_back(0);

			myStack.pop();
		}
	}

	if (isMinus == false)
	{
		for (size_t i = 0; i < sSize; i++)
		{
			cout << myStack.top() << " ";
			myStack.pop();
		}
	}
	else
	{
		sSize = minusVec.size();

		for (size_t i = sSize - 1; i > 0; i--)
		{
			if (minusVec[i] == 1)
				minusVec[i] = 0;
			else
			{
				minusVec[i] = 1;
				break;
			}
		}

		for (size_t i = 0; i < sSize; i++)
			cout << minusVec[i] << " ";
	}

	cout << endl << endl;
	cout << "16 진수로 " << getNumber << "변환" << endl;

	while (HexJinSu > 0)
	{
		myStack.push(HexJinSu % 16);
		HexJinSu /= 16;
	}

	sSize = myStack.size();

	if (isMinus == false)
	{
		for (size_t i = 0; i < sSize; i++)
		{
			OutPut16(myStack.top());
			myStack.pop();
		}
	}
	else
	{
		sSize = myStack.size();

		for (size_t i = 0; i < sSize; i++)
			myStack.pop();

		sSize = minusVec.size();
		int Num = 1;
		int Value = 0;
		vector<int> HexVec;

		for (size_t i = sSize - 1; i > 0; i--)
		{
			if (minusVec[i] == 1)
				Value += minusVec[i] * Num;

			Num *= 2;
		}

		while (Value > 0)
		{
			HexVec.push_back(Value % 16);
			Value /= 16;
		}

		for (size_t i = HexVec.size(); i > 0; i--)
			OutPut16(HexVec[i - 1]);
	}

	cout << endl << endl;
	cout << "8 진수로 " << getNumber << "변환" << endl;
	while (OctalJinSu > 0)
	{
		myStack.push(OctalJinSu % 8);
		OctalJinSu /= 8;
	}

	sSize = myStack.size();

	if (isMinus == false)
	{
		for (size_t i = 0; i < sSize; i++)
		{
			cout << myStack.top() << " ";
			myStack.pop();
		}
	}
	else
	{
		sSize = myStack.size();

		for (size_t i = 0; i < sSize; i++)
			myStack.pop();

		sSize = minusVec.size();
		int Num = 1; 
		int Value = 0;
		vector<int> OcaVec;

		for (size_t i = sSize; i > 0; i--)
		{
			if (minusVec[i - 1] == 1)
				Value += minusVec[i - 1] * Num;

			Num *= 2;
		}

		while (Value > 0)
		{
			OcaVec.push_back(Value % 8);
			Value /= 8;
		}

		for (size_t i = OcaVec.size(); i > 0; i--)
			cout << OcaVec[i - 1] << " ";
	}
}

int main()
{
	ConvertJinSu(-150);
}
