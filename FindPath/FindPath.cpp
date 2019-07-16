#include "pch.h"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <functional>

using namespace std;

enum TILE_OPTION
{
	TO_NONE,
	TO_NOMOVE,
	TO_ITEM,
};

enum VISITED_MODE
{
	VM_VISITED,
	VM_NONEVISITED,
};

struct Edge;
struct Tile2D
{
	int x;
	int y;
	int Weight;
	Tile2D* Prev;
	Tile2D* Next;

	TILE_OPTION Option;
	VISITED_MODE Visited;
	Edge* EdgeList;

	Tile2D()
	{
		x = 0;
		y = 0;
		Weight = 0;
		Option = TO_NONE;
		Visited = VM_NONEVISITED;

		EdgeList = nullptr;
		Prev = nullptr;
		Next = nullptr;
	}
};

struct Edge
{
	Tile2D* From;
	Tile2D* Target;
	Edge* Next;
	int Weight;

	Edge()
	{
		From = nullptr;
		Target = nullptr;
		Next = nullptr;
		Weight = 1;
	}
};

struct Position
{
	int x;
	int y;

	Position()
	{
		x = 0;
		y = 0;
	}
};

class Graph
{
public:
	void SettingData(const vector<vector<int>>& Mase)
	{
		for (int i = 0; i < Mase.size(); i++)
		{
			vector<Tile2D*> TempVec;
			m_vecTile.push_back(TempVec);

			for (int j = 0; j < Mase[i].size(); j++)
			{
				Tile2D* newTile = new Tile2D();
				newTile->x = j;
				newTile->y = i;
				newTile->Option = static_cast<TILE_OPTION>(Mase[i][j]);

				if (newTile->Option == TO_ITEM)
					m_vecItemPos.push_back(newTile);

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
				{
					if(m_vecTile[y][x - 1]->Option != TO_NOMOVE)
						AddEdge(x, y, y, x - 1);
				}

				if (x + 1 < m_vecTile[y].size())
				{
					if(m_vecTile[y][x + 1]->Option != TO_NOMOVE)
						AddEdge(x, y, y, x + 1);
				}

				if (y - 1 >= 0)
				{
					if (m_vecTile[y - 1][x]->Option != TO_NOMOVE)
						AddEdge(x, y, y - 1, x);
				}

				if (y + 1 < m_vecTile.size())
				{
					if(m_vecTile[y + 1][x]->Option != TO_NOMOVE)
						AddEdge(x, y, y + 1, x);
				}
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

	int FindPath(int StartX, int StartY, int EndX, int EndY)
	{
		Tile2D* getStart = m_vecTile[StartY][StartX];
		Tile2D* getEnd = m_vecTile[EndY][EndX];
		int Count = 0;

		if (getEnd->Option == TO_NOMOVE)
			return -1;

		if (m_vecItemPos.empty() == true)
			return -1;

		for (size_t i = 0; i < m_vecItemPos.size(); i++)
		{
			if (m_vecItemPos[i]->EdgeList == nullptr)
				return -1;
		}

		getStart->Weight = 0;
		getStart->Visited = VM_VISITED;

		priority_queue<Tile2D*, vector<Tile2D*>, function<bool(Tile2D*, Tile2D*)>> WeightQueue
		{
			[](Tile2D* Left, Tile2D* Right)
			{
				return Left->Weight > Right->Weight;
			}
		};

		Tile2D* getTile = getStart;
		Tile2D* SelectTile = getStart;
		WeightQueue.push(getStart);

		Edge* getEdge = getStart->EdgeList;

		while (WeightQueue.empty() == false)
		{
			getTile = WeightQueue.top();
			getEdge = getTile->EdgeList;
			WeightQueue.pop();

			if (getEdge == nullptr)
				return -1;

			while (getEdge != nullptr)
			{
				Tile2D* EdgeFrom = getEdge->From;

				if (EdgeFrom != nullptr)
				{
					if (EdgeFrom->Weight <= INT_MAX && EdgeFrom->Visited == VM_NONEVISITED)
					{
						EdgeFrom->Weight = getTile->Weight + getEdge->Weight;
						EdgeFrom->Visited = VM_VISITED;
						EdgeFrom->Prev = getTile;

						if (getTile->Weight + getEdge->Weight < EdgeFrom->Weight)
							EdgeFrom->Weight = getTile->Weight + getEdge->Weight;

						WeightQueue.push(EdgeFrom);
					}
				}
				getEdge = getEdge->Next;
			}
		}

		SelectTile = getEnd;

		stack<Tile2D*> TileStack;
		TileStack.push(getEnd);
		Count++;

		while (SelectTile->Prev != nullptr)
		{
			TileStack.push(SelectTile->Prev);
			SelectTile = SelectTile->Prev;

			if (SelectTile->x == getStart->x && SelectTile->y == getStart->y)
				break;

			Count++;
		}

		for (size_t i = 0; i < m_vecTile.size(); i++)
		{
			for (size_t j = 0; j < m_vecTile[i].size(); j++)
			{
				m_vecTile[i][j]->Visited = VM_NONEVISITED;
				m_vecTile[i][j]->Prev = nullptr;
			}
		}

		return Count;
	}

	Graph()
	{
		m_TileList = new Tile2D();
	}
	~Graph()
	{
		delete m_TileList;

		for (size_t i = 0; i < m_vecTile.size(); i++)
		{
			for (size_t j = 0; j < m_vecTile[i].size(); j++)
				delete m_vecTile[i][j];
		}
	}

public:
	Tile2D* m_TileList;
	vector<vector<Tile2D*>> m_vecTile;
	vector<Tile2D*> m_vecItemPos;
};

int Func(const vector<vector<int>>& Mase, int EndX, int EndY)
{
	Graph* newGraph = new Graph();
	newGraph->SettingData(Mase);
	
	//첫번째 아이템위치 찾기
	Position PrevPos = {};
	PrevPos.x = newGraph->m_vecItemPos[0]->x;
	PrevPos.y = newGraph->m_vecItemPos[0]->y;

	int Distance = newGraph->FindPath(0, 0, PrevPos.x, PrevPos.y);

	if (Distance == -1)
	{
		delete newGraph;
		return -1;
	}

	for (size_t i = 1; i < newGraph->m_vecItemPos.size(); i++)
	{
		int Temp = newGraph->FindPath(PrevPos.x, PrevPos.y, newGraph->m_vecItemPos[i]->x, newGraph->m_vecItemPos[i]->y);

		if (Temp == -1)
		{
			delete newGraph;
			return -1;
		}

		Distance += Temp;
		PrevPos.x = newGraph->m_vecItemPos[i]->x;
		PrevPos.y = newGraph->m_vecItemPos[i]->y;
	}

	Distance += newGraph->FindPath(PrevPos.x, PrevPos.y, EndX, EndY);

	delete newGraph;
	return Distance;  
}

vector<string> split(const string &str);

int main()
{
	vector<vector<int>> Mase;
	int Row = 0;
	int Col = 0;
	int EndX = 0;
	int EndY = 0;
	int Temp1 = 0;

	cout << "행 갯수 입력 : ";
	cin >> Row;
	cout << "열 갯수 입력 : ";
	cin >> Col;

	for (size_t i = 0; i < Row; i++)
	{
		vector<int> TempVec;
		Mase.push_back(TempVec);

		for (size_t j = 0; j < Col; j++)
			Mase[i].push_back(0);
	}

	int Row2 = 0;
	char Temp[255] = {};
	string TempStr;

	getline(cin, TempStr);

	for (size_t i = 0; i < Col; i++, Row2++)
	{
		getline(cin, TempStr);
		vector<string> vecTemp = split(TempStr);
		
		for (size_t j = 0; j < vecTemp.size(); j++)
		{
			Temp1 = stoi(vecTemp[j]);
			
			if(j < Col)
				Mase[Row2][j] = Temp1;
		}
	}

	cout << "목적지 X좌표입력 : ";
	cin >> EndX;
	cout << "목적지 Y좌표입력 : ";
	cin >> EndY;

	cout << Func(Mase, EndX, EndY) << endl;
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