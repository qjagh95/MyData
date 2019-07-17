﻿#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
using namespace std;

vector<string> split(const string &str);

enum VISITED_MODE
{
	VM_VISITED,
	VM_NONEVISITED,
};

struct Tile2D;
struct Edge
{
	Edge* Next;
	Tile2D* From;
	Tile2D* Target;

	Edge()
	{
		From = nullptr;
		Target = nullptr;
		Next = nullptr;
	}
};

struct Tile2D
{
	int x;
	int y;
	int Data;
	VISITED_MODE Visited;
	Edge* EdgeList;
	Tile2D* Next;

	Tile2D()
	{
		x = 0;
		y = 0;
		Data = 0;
		Visited = VM_NONEVISITED;
		EdgeList = nullptr;
		Next = nullptr;
	}
};

class Graph
{
public:
	void SettingData(vector<vector<int>>& Mase, int MoveCount)
	{
		m_MoveCount = MoveCount;

		for (size_t i = 0; i < Mase.size(); i++)
		{
			vector<Tile2D*> TempVec;
			m_vecTile.push_back(TempVec);

			for (size_t j = 0; j < Mase[i].size(); j++)
			{
				Tile2D* newTile = new Tile2D();
				newTile->x = i;
				newTile->y = j;
				newTile->Data = Mase[i][j];

				if (m_TileList->Next == nullptr)
					m_TileList->Next = newTile;
				else
				{
					Tile2D* getTile = m_TileList;

					while (getTile->Next != nullptr)
						getTile = getTile->Next;

					getTile->Next = newTile;
				}

				m_vecTile[i].push_back(newTile);
			}
		}

		for (int y = 0; y < m_vecTile.size(); y++)
		{
			for (int x = 0; x < m_vecTile[y].size(); x++)
			{
				if (x - 1 >= 0)
					AddEdge(x, y, x - 1, y);

				if (x + 1 < m_vecTile[y].size())
					AddEdge(x, y, x + 1, y);

				if (y - 1 >= 0)
					AddEdge(x, y, x, y - 1);

				if (y + 1 < m_vecTile.size())
					AddEdge(x, y, x, y + 1);
			}
		}
	}

	void AddEdge(int TargetX, int TargetY, int FromX, int FromY)
	{
		Tile2D* getTarget = m_vecTile[TargetY][TargetX];
		Tile2D* getFrom = m_vecTile[FromY][FromX];

		Edge* newEdge = new Edge();
		newEdge->From = getFrom;
		newEdge->Target = getTarget;

		Edge* getEdge = getTarget->EdgeList;

		if (getEdge == nullptr)
		{
			getTarget->EdgeList = newEdge;
			return;
		}

		while (true)
		{
			if (getEdge->Next == nullptr)
			{
				getEdge->Next = newEdge;
				return;
			}

			getEdge = getEdge->Next;
		}
	}
	
	int FindMax()
	{
		int Max = 0;

		_DFS(m_TileList);

		return Max;
	}

	Graph()
	{
		m_TileList = new Tile2D();

		m_MoveCount = 0;
	}
	~Graph()
	{
		for (size_t i = 0; i < m_vecTile.size(); i++)
		{
			for (size_t j = 0; j < m_vecTile[i].size(); j++)
				delete m_vecTile[i][j];
		}
	}

private:
	int _DFS(Tile2D* Tile)
	{
		int Max = 0;

		cout << "Visited : " << Tile->Data << endl;
		Tile->Visited = VM_VISITED;

		Edge* getEdge = nullptr;
		getEdge = Tile->EdgeList;

		while (getEdge != nullptr)
		{
			Tile2D* TargetTile = getEdge->Target->Next;

			if (TargetTile != nullptr && TargetTile->Visited == VM_NONEVISITED)
				_DFS(TargetTile);

			getEdge = getEdge->Next;
		}

		return Max;
	}

private:
	Tile2D* m_TileList;
	vector<vector<Tile2D*>> m_vecTile;
	int m_MoveCount;
};

int Func(int Number, vector<vector<int>>& Mase)
{
	Graph* newGraph = new Graph();
	newGraph->SettingData(Mase, Number);

	int MaxCount = 0;

	delete newGraph;
	return MaxCount;
}

int main()
{
	int Height = 0;
	int Weight = 0;
	int MoveCount = 0;
	vector<vector<int>> Mase;
	vector<string> vecTempStr;
	string TempStr;
	stack<int> SortValue;

	cout << "세로크기, 가로크기, 키트갯수" << endl;
	getline(cin, TempStr);
	vecTempStr = split(TempStr);

	Height = stoi(vecTempStr[0]);
	Weight = stoi(vecTempStr[1]);
	MoveCount = stoi(vecTempStr[2]);

	for (size_t i = 0; i < Height; i++)
	{
		vector<int> TempVec;
		Mase.push_back(TempVec);

		for (size_t j = 0; j < Weight; j++)
			Mase[i].push_back(0);
	}

	int Temp1 = 0;
	size_t XIndex = 0;

	for (size_t i = 0; i < Height; i++)
	{
		getline(cin, TempStr);
		int Convert = stoi(TempStr);

		while (Convert != 0)
		{
			SortValue.push(Convert % 10);
			Convert /= 10;
		}

		size_t StackSize = SortValue.size();

		for (size_t k = 0; k < StackSize; k++)
		{
			Mase[i][XIndex] = SortValue.top();
			SortValue.pop();
			XIndex++;
		}

		XIndex = 0;
	}

	cout << "최대값은 : ";
	cout << Func(MoveCount, Mase) << endl;
}

vector<string> split(const string &str)
{
	vector<string> tokens;

	string::size_type start = 0;
	string::size_type end = 0;

	while ((end = str.find(" ", start)) != string::npos)
	{
		tokens.push_back(str.substr(start, end - start));

		start = end + 1;
	}

	tokens.push_back(str.substr(start));

	return tokens;
}
