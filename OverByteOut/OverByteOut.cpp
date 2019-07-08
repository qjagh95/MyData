#include "pch.h"
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int Out(int Number)
{
	if (Number == 1)
		return 1;

	return Out(Number - 1) * Number;
}

void Out2(int Number)
{
	stack<int> newVec;

	unsigned long long Num1 = 0;
	unsigned long long Num2 = 0;
	unsigned long long Sum = 0;

	int Index = 0;

	//for (size_t i = Number; i > 0; i--)
	//	Result *= i;

	while (Index < Number)
	{
		Num1 = Index * (Index - 1);
		Num2 = 

		Sum = Num1 + Num2;

		while (Sum != 0)
		{
			newVec.push(Sum % 10);
			Sum /= 10;
		}
		Index++;
	}

	size_t Size = newVec.size();
	for (size_t i = 0; i < Size; i++)
	{
		cout << newVec.top();
		newVec.pop();
	}
}

void Out3(int64_t Number)
{
	std::vector<int64_t> v{};
	v.push_back(1);

	for (int64_t i = 2; i <= Number; ++i)
	{
		for (int64_t j = 0; j < v.size(); ++j)
		{
			int64_t tmp = v[j] * i;

			if (tmp > 10)
			{
				if (j == v.size() - 1)
					v.push_back(0);

				v[j + 1] = tmp / 10;
				v[j] = tmp % 10;
			}
			else
				v[j] = tmp;
		}
	}

	for (auto const& e : v)
		cout << e;
}

int main()
{
	Out3(10);
}
