#include "pch.h"
#include <iostream>
using namespace std;

void Output(int Number)
{
	for (size_t i = 1; i < Number + 1; i++)
	{
		cout << i << " : ";

		int getNumber = i;
		while (true)
		{
			if (getNumber % 10 == 3 || getNumber % 10 == 6 || getNumber % 10 == 9)
				cout << "Clap ";

			getNumber /= 10;

			if (getNumber == 0)
				break;
		}

		cout << endl;
	} 

}

int main()
{
	Output(100);
}

