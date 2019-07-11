#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void Swap(int& a, int& b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}

int main()
{
	ifstream InputFile;
	InputFile.open("Test.txt", ios::in);

	int a = 0;
	float b = 0;
	string c;

	char Buffer[255] = {};
	InputFile.getline(Buffer, 10);

	string Temp = Buffer;
	Temp.erase(0, Temp.find_last_of(" "));
	a = stoi(Temp);

	InputFile.getline(Buffer, 10);

	Temp = Buffer;
	Temp.erase(0, Temp.find_last_of(" "));
	b = stoi(Temp);

	InputFile.getline(Buffer, 20);

	Temp = Buffer;
	Temp.erase(0, Temp.find_last_of(" "));
	c = Temp;

	int ccc = 100;
	int ddd = 200;
	Swap(ccc, ddd);
}