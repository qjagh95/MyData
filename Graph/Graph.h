#pragma once
#include <unordered_map>
#include <iostream>
#include "Basic.h"

using namespace std;

enum VISIT_MODE
{
	VM_VISITED,
	VM_NOTVISITED,
};

class Graph
{
public:
	void AddVertex(int Key, const int& Data)
	{
		Vertex* newVertex = FindVertex(Key);

		if (newVertex != nullptr)
			return;

		if (m_Size == 0)
		{
			m_VertexList->m_Index = m_Size++;
			m_VertexList->m_Data = Data;
			m_VertexList->m_Key = Key;
			m_VertexMap.insert(make_pair(Key, m_VertexList));
			return;
		}

		newVertex = new Vertex();
		newVertex->m_Index = m_Size++;
		newVertex->m_Data = Data;
		newVertex->m_Key = Key;
		m_VertexMap.insert(make_pair(Key, newVertex));

		Vertex* getVertex = m_VertexList;

		while (getVertex->m_Next != nullptr)
			getVertex = getVertex->m_Next;

		getVertex->m_Next = newVertex;
	}

	void AddEdge(int Weight, int Target, int From)
	{
		Vertex* FromVertex = FindVertex(From);
		Vertex* TargetVertex = FindVertex(Target);

		if (FromVertex == nullptr)
			return;

		if (TargetVertex == nullptr)
			return;

		Edge* newEdge = new Edge();
		newEdge->m_From = FromVertex;
		newEdge->m_Target = TargetVertex;
		newEdge->m_Weight = Weight;

		Edge* getEdge = TargetVertex->m_AdjList;

		if (getEdge == nullptr)
		{
			TargetVertex->m_AdjList = newEdge;
			return;
		}

		while (true)
		{
			if (getEdge->m_Next == nullptr)
			{
				getEdge->m_Next = newEdge;
				return;
			}

			getEdge = getEdge->m_Next;
		}
	}

	//±íÀÌ¿ì¼± Å½»ö
	void BFS()
	{

	}
	//³Êºñ¿ì¼± Å½»ö
	void DFS()
	{
	}


	
private:
	Vertex* FindVertex(int Key)
	{
		auto FindIter = m_VertexMap.find(Key);

		if (FindIter == m_VertexMap.end())
			return nullptr;

		return FindIter->second;
	}

private:
	Vertex* m_VertexList;
	unordered_map<int, Vertex*> m_VertexMap;
	int m_Size;

public:
	Graph()
	{
		m_Size = 0;
		m_VertexList = new Vertex();
	}
	~Graph()
	{
		delete[] m_VertexList;
	}
};
