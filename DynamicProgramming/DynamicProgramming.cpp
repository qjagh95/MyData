#include "pch.h"
#include <iostream>
using namespace std;

//어떤 문제가 여러 단계의 반복되는 부분문제로 이뤄질 때
//각 단계에 있는 부분문제의 답을 기반으로 전체문제의 답을 구하는 방법
//분할정복과 비슷하지만 다르다.
//분할정복은 위에서부터 아래로 쪼개는 방법이지만
//동적계획법은 제일 작은부분부터 상위로 올라간다.

//피보나치 동적계획법으로 하기
int Fibo(int Number)
{
	if (Number == 0 || Number == 1)
		return Number;

	size_t Result;
	size_t* FiboTable;

	FiboTable = new size_t[Number + 1];
	FiboTable[0] = 0;
	FiboTable[1] = 1;

	for (size_t i = 2; i <= Number; i++)
		FiboTable[i] = FiboTable[i - 1] + FiboTable[i - 2];

	Result = FiboTable[Number];

	delete[] FiboTable;

	return static_cast<int>(Result);
}

int main()
{
	cout << Fibo(46) << endl;
}
