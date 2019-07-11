#include "pch.h"
#include <iostream>
#include <vector>
#include <unordered_map>

//https://www.hackerrank.com/challenges/sock-merchant/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=warmup

using namespace std;
unordered_map<int, int> TempMap;
bool FindValue(int Key);

int sockMerchant(int n, vector<int> ar)
{
	if (n > 100 || n == 0)
		return -1;

	int TempCount = 1;
	int Result = 0;
	int StuckValue = 0;

	for (size_t i = 0; i < ar.size(); i++)
	{
		int SelectValue = ar[i];

		if (FindValue(SelectValue) == true)
			continue;

		for (size_t j = 1; j < ar.size(); j++)
		{
			if (SelectValue == ar[j])
			{
				TempMap.insert(make_pair(SelectValue, SelectValue));
				TempCount++;
			}
		}

		if (TempCount >= 2)
			Result += TempCount / 2;

		TempCount = 0;
	}

	return Result;
}

bool FindValue(int Key)
{
	auto FindIter = TempMap.find(Key);

	if (FindIter == TempMap.end())
		return false;
	
	return true;
}

int main()
{
	vector<int> a;
	a.push_back(6);
	a.push_back(5);
	a.push_back(2);
	a.push_back(3);
	a.push_back(5);
	a.push_back(2);
	a.push_back(2);
	a.push_back(1);
	a.push_back(1);
	a.push_back(5);
	a.push_back(1);
	a.push_back(3);
	a.push_back(3);
	a.push_back(3);
	a.push_back(5);

	//for (size_t i = 0; i < 100; i++)
	//{
	//	a.push_back(42);
	//}

	cout << sockMerchant(15, a) << endl;
}