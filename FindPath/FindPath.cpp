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

struct Edge;
struct Tile2D
{
	int x;
	int y;
	int Weight;
	Tile2D* Prev;
	Tile2D* Next;

	TILE_OPTION Option;
	vector<Edge*> VecEdge;

	Tile2D()
	{
		x = 0;
		y = 0;
		Weight = 0;
		Option = TO_NONE;
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

vector<Tile2D*> VecItem;

int Func(vector<vector<int>> Mase)
{
	int Distance = 0;

	return Distance;
}

int main()
{
}

