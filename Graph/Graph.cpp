#include "pch.h"
#include <iostream>
#include "Graph.h"
using namespace std;

int main()
{
	Graph* newGraph = new Graph();

	for (size_t i = 0; i < 10; i++)
		newGraph->AddVertex(i, i + 1);

	for (size_t i = 0; i < 10; i++)
		newGraph->AddEdge(0, i, i + 1);

	newGraph->AddEdge(0, 6, 1);
	newGraph->AddEdge(0, 6, 2); 

	//newGraph->DFS();
	newGraph->BFS();
}