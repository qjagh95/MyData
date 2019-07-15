#include "pch.h"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <list>

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
	vector<Edge*> VecEdge;

	Tile2D()
	{
		x = 0;
		y = 0;
		Weight = 0;
		Option = TO_NONE;
		Visited = VM_NONEVISITED;
		VecEdge.reserve(4);

		Prev = nullptr;
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
		Weight = 0;
	}
};
class Graph
{
public:
	void SettingData(const vector<vector<int>>& Mase)
	{
		for (size_t i = 0; i < Mase.size(); i++)
		{
			vector<Tile2D*> TempVec;
			m_vecTile.push_back(TempVec);

			for (size_t j = 0; j < Mase[i].size(); j++)
			{
				Tile2D* newTile = new Tile2D();
				newTile->x = i;
				newTile->y = j;

				while (m_TileList->Next != nullptr)
					m_TileList->Next = newTile;
				
				m_vecTile[i].push_back(newTile);
			}
		}
	}

	void AddTile()
	{
		
	}
	void AddEdge()
	{

	}
	int FindPath()
	{
		return 0;
	}

	Graph()
	{

	}
	~Graph()
	{
		for (size_t i = 0; i < m_vecTile.size(); i++)
		{
			for (size_t j = 0; j < m_vecTile[i].size(); j++)
			{
				delete m_vecTile[i][j];
			}
		}
	}


private:
	Tile2D* m_TileList;
	vector<vector<Tile2D*>> m_vecTile;
};


int Func(const vector<vector<int>>& Mase, int EndX, int EndY)
{
	Graph* newGraph = new Graph();
	newGraph->SettingData(Mase);
	int Distance = newGraph->FindPath();

	delete newGraph;
	return Distance;  
}

int main()
{

}

