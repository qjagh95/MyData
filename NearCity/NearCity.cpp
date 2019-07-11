#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>

using namespace std;

struct DataInfo
{
	string CityName;
	int xPos;
	int yPos;
	vector<DataInfo*> XSames;
	vector<DataInfo*> YSames;
	vector<string> NearCitys;

	void XPush(DataInfo* Data) { XSames.push_back(Data); }
	void YPush(DataInfo* Data) { YSames.push_back(Data); }
	void SPush(const string& Data)
	{
		NearCitys.push_back(Data);
		sort(NearCitys.begin(), NearCitys.end());
	}

	DataInfo()
	{
		xPos = 0;
		yPos = 0;
		CityName = "NONE";
	}

	bool operator==(const DataInfo& Data)
	{
		return xPos == Data.xPos && yPos == Data.yPos;
	}

	DataInfo operator+(const DataInfo& Data)
	{
		DataInfo Temp;
		Temp.xPos = xPos + Data.xPos;
		Temp.yPos = yPos + Data.yPos;

		return Temp;
	}

	DataInfo operator-(const DataInfo& Data)
	{
		DataInfo Temp;
		Temp.xPos = xPos - Data.xPos;
		Temp.yPos = yPos - Data.yPos;

		return Temp;
	}
};

vector<DataInfo*> VecInfo;
vector<string> VecOut;

void SettingData(vector<string>& Citys, vector<int>& xPos, vector<int>& yPos)
{
	for (size_t i = 0; i < Citys.size(); i++)
	{
		DataInfo* newInfo = new DataInfo();
		newInfo->CityName = Citys[i];
		newInfo->xPos = xPos[i];
		newInfo->yPos = yPos[i];

		VecInfo.push_back(newInfo);
	}
}

void DeleteInfo()
{
	for (size_t i = 0; i < VecInfo.size(); i++)
	{
		if (VecInfo[i] != nullptr)
			delete VecInfo[i];
	}
}

int GetDistance(DataInfo* Left, DataInfo* Right)
{
	int Distance = 0;
	int X = Right->xPos - Left->xPos;
	int Y = Right->yPos - Left->yPos;

	Distance = abs(X * X) + abs(Y * Y);

	return sqrt(static_cast<int>(Distance));
}

vector<string> Func(vector<string>& Citys, vector<int>& xPos, vector<int>& yPos)
{
	SettingData(Citys, xPos, yPos);

	size_t Size = VecInfo.size();

	for (size_t i = 0; i < Size ; i++)
	{
		for (size_t j = 0; j < Size; j++)
		{
			if (i == j)
				continue;

			if (VecInfo[i] == VecInfo[j])
				VecInfo[i]->NearCitys.push_back(VecInfo[j]->CityName);

			else if (VecInfo[i]->xPos == VecInfo[j]->xPos)
				VecInfo[i]->XPush(VecInfo[j]);

			else if(VecInfo[i]->yPos == VecInfo[j]->yPos)
				VecInfo[i]->YPush(VecInfo[j]);
		}
	}

	for (size_t i = 0; i < Size; i++)
	{
		if (VecInfo[i]->XSames.empty() == false)
		{
			int Small = INT_MAX;
			DataInfo getInfo = DataInfo();

			for (size_t j = 0; j < VecInfo[i]->XSames.size(); j++)
			{
				int Temp = GetDistance(VecInfo[i], VecInfo[i]->XSames[j]);

				if (Temp < Small)
				{
					Small = Temp;
					getInfo = *VecInfo[i]->XSames[j];
				}
			}

			VecInfo[i]->SPush(getInfo.CityName);
		}
		else if (VecInfo[i]->YSames.empty() == false)
		{
			int Small = INT_MAX;
			DataInfo getInfo = DataInfo();

			for (size_t j = 0; j < VecInfo[i]->YSames.size(); j++)
			{
				int Temp = GetDistance(VecInfo[i], VecInfo[i]->YSames[j]);

				if (Temp < Small)
				{
					Small = Temp;
					getInfo = *VecInfo[i]->YSames[j];
				}
			}
			VecInfo[i]->SPush(getInfo.CityName);
		}
	}

	for (size_t i = 0; i < Size; i++)
	{
		cout << VecInfo[i]->CityName << "와 가까운 도시는 : ";

		if (VecInfo[i]->NearCitys.empty() == true)
		{
			cout << "NONE" << " ";
			VecOut.push_back("NONE");
			continue;
		}
		
		for (size_t j = 0; j < VecInfo[i]->NearCitys.size(); j++)
		{
			cout << VecInfo[i]->NearCitys[j] << " ";
			VecOut.push_back(VecInfo[i]->NearCitys[j]);
		}

		cout << endl;
	}

	DeleteInfo();

	return VecOut;
}

int main()
{
	int CityCount = 0;
	vector<string> Citys;
	vector<int> xPos;
	vector<int> yPos;

	cout << "도시의 갯수 입력 : ";
	cin >> CityCount;

	int Index = 0;
	while (Index < CityCount)
	{
		char Buffer[255] = {};
		cin >> Buffer;

		Citys.push_back(Buffer);

		Index++;
	}

	cout << "X Pos 갯수입력 : ";
	cin >> CityCount;

	Index = 0;
	while (Index < CityCount)
	{
		int newX = 0;
		cin >> newX;

		xPos.push_back(newX);

		Index++;
	}


	cout << "Y Pos 갯수입력 : ";
	cin >> CityCount;

	Index = 0;
	while (Index < CityCount)
	{
		int newY = 0;
		cin >> newY;

		yPos.push_back(newY);

		Index++;
	}

	Func(Citys, xPos, yPos);
}
