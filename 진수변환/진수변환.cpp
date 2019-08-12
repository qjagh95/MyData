#include "pch.h"
#include <iostream>
#include <stack>
#include <vector>
#include <list>
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
	list<int> minusVec;

	int getNumber = Number;
	bool isMinus = false;

	if (Number <= 0)
	{
		Number *= -1;
		isMinus = true;
	}

	int TwoJinSu = Number;
	int TenJinSu = Number;
	int HexJinSu = Number;
	int OctalJinSu = Number;

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
		auto StartIter = minusVec.rbegin();
		auto EndIter = minusVec.rend();

		for (; StartIter != EndIter; StartIter++)
		{
			if (*StartIter == 1)
				*StartIter = 0;
			else
			{
				*StartIter = 1;
				break;
			}
		}

		while (minusVec.size() % 4 != 0)
			minusVec.push_front(1);

		auto StartIter1 = minusVec.begin();
		auto EndIter1 = minusVec.end();

		for ( ;StartIter1 != EndIter1; StartIter1++)
			cout << *StartIter1 << " ";
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

		auto StartIter = minusVec.rbegin();
		auto EndIter = minusVec.rend();

		for (; StartIter != EndIter ; StartIter++ )
		{
			if (*StartIter == 1)
				Value += *StartIter * Num;

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

		if (sSize % 3 != 0)
			minusVec.push_front(1);

		int Num = 1; 
		int Value = 0;
		vector<int> OcaVec;

		auto StartIter = minusVec.rbegin();
		auto EndIter = minusVec.rend();

		for (;StartIter != EndIter; StartIter++)
		{
			if (*StartIter == 1)
				Value += *StartIter * Num;

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
	ConvertJinSu(0);
}
