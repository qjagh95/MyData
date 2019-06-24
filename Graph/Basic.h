#pragma once
//간선 구조체
struct Edge
{
	int m_Weight;
	Edge* m_Next;
	struct Vertex* m_From;
	struct Vertex* m_Target;

	Edge()
	{
		m_From = nullptr;
		m_Target = nullptr;
		m_Next = nullptr;
		m_Weight = 0;
	}
};

//정점구조체
struct Vertex
{
	int m_Key;
	int m_Data;
	int m_Visited;
	int m_Index;

	Vertex* m_Next;
	Edge* m_AdjList;

	Vertex()
	{
		m_Next = nullptr;
		m_AdjList = nullptr;
		m_Visited = 1;
		m_Index = -1;
	}
};