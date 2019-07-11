#include "pch.h"
#include <iostream>
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
	size_t j = 0;
	vector<int> newVec;
	newVec.push_back(1);

	for (size_t i = 2; i <= Number; i++)
	{
		unsigned long long Temp = 0;

		for (j = 0; j < newVec.size(); j++)
		{
			 Temp += newVec[j] * i;

			 newVec[j] = Temp % 10;
			 Temp /= 10;
		}

		while (Temp != 0)
		{
			newVec.push_back(Temp % 10);
			Temp /= 10;
		}

	}

	for (int i = newVec.size() - 1; i >= 0; i--)
		cout << newVec[i];
}

//GM
void Out3(int64_t Number)
{
	std::vector<int64_t> v{};
	v.push_back(1);

	for (int64_t i = 2; i <= Number; ++i)
	{
		for (int64_t j = 0; j < v.size() - 1; ++j)
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
	Out2(100000);
}
