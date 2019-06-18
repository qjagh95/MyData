#include "pch.h"
#include <iostream>
using namespace std;

int main()
{
	//숫자뒤집기
	int Number = 1234;
	int Result = 0;
	
	while (Number != 0)
	{
		Result = Number % 10 + Result * 10;
		Number /= 10;
	}

	cout << Result << endl;

	//문자뒤집기
	char Buffer[255];
	strcpy_s(Buffer, "abcdefg");

	size_t last = 0;
	size_t first = 0;

	for (first = 0, last = strlen(Buffer) - 1; first < last; last--, first++)
	{
		char Temp = Buffer[last];
		Buffer[last] = Buffer[first];
		Buffer[first] = Temp;
	}

	cout << Buffer;

}
