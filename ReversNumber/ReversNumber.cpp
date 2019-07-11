#include "pch.h"
#include <iostream>
#include <vector>

struct DataInfo
{
	int Value;
	int Acc;

	DataInfo()
	{
		Value = 0;
		Acc = 0;
	}
};

using namespace std;

vector<DataInfo> VecRepeat;

DataInfo* FindInfo(const int& Key)
{
	for (size_t i = 0; i < VecRepeat.size(); i++)
	{
		if (VecRepeat[i].Value == Key)
			return &VecRepeat[i];
	}

	return nullptr;
}

void YekSu(int Number)
{
	if (Number <= 2 || Number >= pow(10, 5))
		return;

	int Num = 1;

	int Index = 0;
	Index++;

	DataInfo newInfo = {};

	int Temp = 1 % Num * 10;
	newInfo.Value = Temp;
	newInfo.Acc = Index;

	cout << "0.";

	for (size_t i = 0; i < 100; i++)
	{
		Num = Num % Number * 10;

		DataInfo* getInfo = FindInfo(Num);

		if (getInfo == nullptr)
		{
			DataInfo newInfo2 = {};
			newInfo2.Value = Num;
			newInfo2.Acc = 1;

			VecRepeat.push_back(newInfo2);
		}
		else
			getInfo->Acc++;
	}

	for (size_t i = 0; i < VecRepeat.size(); i++)
		cout << VecRepeat[i].Value / Number;

	cout << " ";

	for (size_t i = 0; i < VecRepeat.size(); i++)
	{
		if(VecRepeat[i].Acc >= 10)
			cout << VecRepeat[i].Value / Number;
	}
}

int main()
{
	YekSu(56);
	//ConvertNumber(56);
}