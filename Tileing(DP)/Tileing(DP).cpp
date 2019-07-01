#include "pch.h"
#include <iostream>
using namespace std;

size_t Table[1000001];

//DP문제는 특정한 규칙성을 찾아서 공식을 세우는게 중요하다
//백준 타일링문제1
size_t DP(int Number)
{
	if (Number == 1 || Number == 2)
		return Number;

	if (Table[Number] != 0)
		return Table[Number];

	return Table[Number] = (DP(Number - 1) + DP(Number - 2)) % 10007;
}

//백준 타일링문제2
size_t DP2(int Number)
{
	if (Number == 1) 
		return 1;
	if (Number == 2)
		return 3;

	if (Table[Number] != 0)
		return Table[Number];

	return Table[Number] = (DP2(Number - 1) + 2 * DP2(Number - 2)) % 10007;
}

//백준 타일링문제3
size_t DP3(int Number)
{
	if (Number == 0)
		return 1;
	if (Number == 1)
		return 0;
	if (Number == 2)
		return 3;

	if (Table[Number] != 0)
		return Table[Number];

	size_t Result = 3 * DP3(Number - 2);

	for (size_t i = 3; i < Number; i++)
	{
		if (i % 2 == 0)
			Result += 2 * DP3(Number - i);
	}

	Table[Number] = Result;

	return Table[Number];
}

int main()
{
	cout << DP3(1) << endl;
}

