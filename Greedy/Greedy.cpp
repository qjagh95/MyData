#include "pch.h"
#include <iostream>
#include <Windows.h>
using namespace std;

//매번 가장 좋아보이는 답을 선택하는 알고리즘
//대표적으로 거스름돈 문제

int main()
{
	int Price = 0;

	cout << "거스름돈을 입력하세요 : ";
	cin >> Price;
	cout << endl;

	cout << "5000 : " << Price / 5000 << endl;
	Price %= 5000;

	cout << "1000 : " << Price / 1000 << endl;
	Price %= 1000;

	cout << "100 : " << Price / 100 << endl;
	Price %= 100;

	cout << "10 : " << Price / 10 << endl;
	Price %= 10;
}