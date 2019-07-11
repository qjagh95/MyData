//https://www.hackerrank.com/challenges/repeated-string/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=warmup

#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;

unsigned long long repeatedString(string s, unsigned long long n)
{
	if (s.size() > 100 || s.size() < 1)
		return 0;

	if (n < 1 || n > pow(n, 12))
		return 0;
	
	size_t StringSize = s.size();	
	unsigned long long Result = 0;
	unsigned long long Convert = n;
	vector<char> Repeat;

	for (size_t i = 0; i < StringSize; i++)
	{
		if (s[i] == 'a')
			Result++;
	}

	unsigned long long Devide = Convert / s.size();

	Result = Result * Devide;
	Convert %= s.size();

	if (Result < 0)
		return 0;
	
	for (size_t i = 0; i < Convert; i++)
	{
		if (s[i] == 'a')
			Result++;
	}

	return Result;
}

int main()
{
	string a = "bab";

	cout << repeatedString(a, 725261545450);
}
