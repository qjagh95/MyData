#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;

void ConvertNumber(int N)
{
	if (N <= 2 || N >= pow(10, 5))
		return;

	vector<int> RepeatNumber;
	int Start = 0;
	int End = 0;
	int Num = 1;
	int Index = 0;
	int Table[100000] = {};
	memset(Table, -1, sizeof(int) * 100000);

	for (size_t i = 0; i < N; i++)
	{
		int Temp = Num % N * 10;
		Start = 0;
		End = 0;

		while (true)
		{
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

		for (size_t i = Start; i < End; i++)
		{
			cout << Temp / N;
			Temp = Temp % N * 10;
		}
	}

}

int a, b, k, t, start, finish;
int c[100001];

int main()
{
	//ConvertNumber(56);
	//t = N
	//k = Index


	cin >> t;

	k = 0;
	memset(c, -1, sizeof(c));
	cin >> a >> b;
	start = finish = 0;

	printf("%d.", (a / t));
	int temp = a % t * 10;

	while (true) 
	{ //순환되는 부분까지 찾기
		a = a % t * 10;

		if (c[a] != -1)
		{
			start = c[a];
			finish = k;
			break;
		}
		c[a] = k++;
	}

	for (int i = 0; i < start; i++)
	{
		printf("%d", temp / t);
		temp = temp % t * 10;
	}

	printf("(");

	for (int i = start; i < finish; i++)
	{
		printf("%d", temp / t);
		temp = temp % t * 10;
	}

	printf(")\n");

	return 0;
}
