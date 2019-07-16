#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;

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

	Tile2D* Prev;

	Tile2D()
	{
		x = 0;
		y = 0;
		Data = 0;
		Prev = nullptr;
		Visited = VM_NONEVISITED;
	}
};

class Graph
{
public:
	void SettingData(int Height, int Weight)
	{
		for (size_t i = 0; i < Height; i++)
		{
			vector<Tile2D*> TempVec;
			m_vecTile.push_back(TempVec);

			for (size_t j = 0; j < Weight; j++)
			{
				Tile2D* newTile = new Tile2D();
				newTile->x = i;
				newTile->y = j;
				m_vecTile[j].push_back(newTile);
			}
		}
	}

private:
	vector<vector<Tile2D*>> m_vecTile;
};

int Func(int Height, int Weight, int Number)
{
	Graph* newGraph = new Graph();

	int MaxCount = 0;

	delete newGraph;
	return MaxCount;
}

int main()
{
}