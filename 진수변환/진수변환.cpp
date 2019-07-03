#include "pch.h"
#include <iostream>
#include <stack>
using namespace std;

void ConvertJinSu(int Number)
{
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

	int Index = 0;

	stack<int> myStack;

	//2진수
	cout << "2 진수로 " << Number << "변환" << endl;
	while (TwoJinSu > 0)
	{
		myStack.push(TwoJinSu % 2);
		TwoJinSu /= 2;
	}

	size_t sSize = myStack.size();
	for (size_t i = 0; i < sSize; i++)
	{
		cout << myStack.top()<<" ";
		myStack.pop();
	}

	cout << endl << endl;

	cout << "16 진수로 " << Number << "변환" << endl;

	while (HexJinSu > 0)
	{
		myStack.push(HexJinSu % 16);
		HexJinSu /= 16;
	}

	sSize = myStack.size();
	for (size_t i = 0; i < sSize; i++)
	{
		switch (myStack.top())
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
			cout << myStack.top() << " ";
			break;
		}
		myStack.pop();
	}

	cout << endl << endl;

	cout << "8 진수로 " << Number << "변환" << endl;
	while (OctalJinSu > 0)
	{
		myStack.push(OctalJinSu % 8);
		OctalJinSu /= 8;
	}

	sSize = myStack.size();
	for (size_t i = 0; i < sSize; i++)
	{
		cout << myStack.top() << " ";
		myStack.pop();
	}
}

int main()
{
	ConvertJinSu(1035);
}
