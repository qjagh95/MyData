#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;

void ConvertNumber(int N)
{
	//제약조건
	if (N <= 2 || N >= pow(10, 5))
		return;

	vector<int> RepeatNumber;
	int Start = 0;
	int End = 0;
	int Num = 1;
	int Index = 0;
	int Table[100000] = {};

	//배열을 -1로 채운다.
	memset(Table, -1, sizeof(int) * 100000);
	
	//첫번째 자리를 구한다.
	int Temp = Num % N * 10;

	cout << "0.";

	//순환점을 구한다.
	while (true)
	{
		//반복해서 자릿수자체를 인덱스로 쓴다.
		Num = Num % N * 10;

		if (Table[Num] != -1)
		{
			Start = Table[Num];
			End = Index;
			break;
		}

		Table[Num] = Index++;
	}

	for (size_t i = 0; i < Start; i++)
	{
		cout << Temp / N;
		Temp = Temp % N * 10;
	}

	//반복되는 숫자.
	for (size_t i = Start; i < End; i++)
	{
		cout << Temp / N;
		RepeatNumber.push_back(Temp / N);

		Temp = Temp % N * 10;
	}

	cout << " ";
	for (size_t i = 0; i < RepeatNumber.size(); i++)
		cout << RepeatNumber[i];
}

int main()
{
	ConvertNumber(3);
}
