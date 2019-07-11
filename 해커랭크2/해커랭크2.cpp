#include "pch.h"
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

//https://www.hackerrank.com/challenges/jumping-on-the-clouds/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=warmup

int jumpingOnClouds(vector<int> c) 
{
	int Result = 0;
	int TempIdx = 1;
	int SelectIndex = 0;

	for (size_t i = 0; i < c.size() - 1; )
	{
		if (c[i + 2] == 0)
		{
			i = i + 2;
			Result++;
		}
		else if (c[i + 1] == 0)
		{
			i = i + 1;
			Result++;
		}
		else if (c[i + 1] == 1)
		{
			while (c[i + TempIdx])
				TempIdx++;

			i = i + TempIdx;
		}

	}

	return Result;
}

int main()
{
	vector<int> a;
	a.push_back(0);
	a.push_back(0);
	a.push_back(1);
	a.push_back(0);
	a.push_back(0);
	a.push_back(1);
	a.push_back(0);

	cout << jumpingOnClouds(a) << endl;

}