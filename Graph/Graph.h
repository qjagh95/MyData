#pragma once
#include <unordered_map>
#include <iostream>
#include "Basic.h"
#include <queue>

using namespace std;

enum VISIT_MODE
{
	VM_VISITED,
	VM_NOTVISITED,
};

class Graph
{
public:
	Vertex* GetVertexList() const { return m_VertexList; }

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
		newVertex->m_Visited = VM_NOTVISITED;
		m_VertexMap.insert(make_pair(Key, newVertex));

		Vertex* getVertex = m_VertexList;

		while (getVertex->m_Next != nullptr)
			getVertex = getVertex->m_Next;

		getVertex->m_Next = newVertex;
	}

	void AddEdge(int Weight, int Src, int Dest)
	{
		Vertex* FromVertex = FindVertex(Dest);
		Vertex* TargetVertex = FindVertex(Src);

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

	//깊이우선 탐색
	void DFS()
	{
		_DFS(m_VertexList);
	}

	//너비우선 탐색
	void BFS()
	{
		//큐 or 스택을 사용해야함.
		cout << "Visited : " << m_VertexList->m_Key << endl;
		m_VertexList->m_Visited = VM_VISITED;

		m_BFSQueue.push(m_VertexList);

		Vertex* getVertex = m_VertexList;
		Edge* getEdge = m_VertexList->m_AdjList;

		while (m_BFSQueue.empty() == false)
		{
			getVertex = m_BFSQueue.front();
			getEdge = getVertex->m_AdjList;
			m_BFSQueue.pop();

			while (getEdge != nullptr)
			{
				Vertex* TargetNext = getEdge->m_Target->m_Next;

				if (TargetNext != nullptr && TargetNext->m_Visited == VM_NOTVISITED)
				{
					TargetNext->m_Visited = VM_VISITED;
					cout << "Visited : " << TargetNext->m_Key << endl;
					m_BFSQueue.push(TargetNext);
				}
				getEdge = getEdge->m_Next;
			}
		}
	}

	Vertex* FindVertex(int Key)
	{
		auto FindIter = m_VertexMap.find(Key);

		if (FindIter == m_VertexMap.end())
			return nullptr;

		return FindIter->second;
	}

private:
	void _DFS(Vertex* vertex)
	{
		cout << "Visited : " << vertex->m_Key << endl;
		vertex->m_Visited = VM_VISITED;

		Edge* getEdge = nullptr;
		getEdge = vertex->m_AdjList;

		while (getEdge != nullptr)
		{
			Vertex* TargetNext = getEdge->m_Target->m_Next;

			if (TargetNext != nullptr && TargetNext->m_Visited == VM_NOTVISITED)
				_DFS(TargetNext);

			getEdge = getEdge->m_Next;
		}
	}

private:
	Vertex* m_VertexList;
	unordered_map<int, Vertex*> m_VertexMap;
	int m_Size;
	queue<Vertex*> m_BFSQueue;

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
