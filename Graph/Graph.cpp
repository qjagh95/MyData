#include "pch.h"
#include <iostream>
#include "Graph.h"

using namespace std;

enum
{
	A = 1, B, C, D, E, F, G, H, I
};

int main()
{
	Graph* newGraph = new Graph();

	for (size_t i = 0; i < 10; i++)
		newGraph->AddVertex(i + 1, i + 1);

	newGraph->AddEdge(35, B, A);
	newGraph->AddEdge(126, B, C);
	newGraph->AddEdge(117, C, D);
	newGraph->AddEdge(247, A, E);
	newGraph->AddEdge(82, F, E);
	newGraph->AddEdge(98, E, H);
	newGraph->AddEdge(120, F, H);
	newGraph->AddEdge(162, C, F);
	newGraph->AddEdge(220, C, G);
	newGraph->AddEdge(154, F, G);
	newGraph->AddEdge(106, G, I);

	list<Vertex*>* a = newGraph->Dijkstra(1, 3);

	auto StartIter = a->begin();
	auto EndIter = a->end();

	for (; StartIter != EndIter; StartIter++)
		cout << (*StartIter)->m_Key << " ";


	//newGraph->DFS();
	//newGraph->BFS();
}