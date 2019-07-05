#pragma once
#include <unordered_map>
#include <iostream>
#include "Basic.h"
#include <queue>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

enum VISIT_MODE
{
	VM_VISITED,
	VM_NOTVISITED,
};

struct DijkstraInfo
{
	Vertex* Target;
	bool Visited;
	int Weight;
	DijkstraInfo* Prev;
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
			m_DeleteVec.push_back(m_VertexList);
			return;
		}

		newVertex = new Vertex();
		newVertex->m_Index = m_Size++;
		newVertex->m_Data = Data;
		newVertex->m_Key = Key;
		newVertex->m_Visited = VM_NOTVISITED;
		m_VertexMap.insert(make_pair(Key, newVertex));
		m_DeleteVec.push_back(newVertex);

		Vertex* getVertex = m_VertexList;

		while (getVertex->m_Next != nullptr)
			getVertex = getVertex->m_Next;

		getVertex->m_Next = newVertex;
	}

	void AddEdge(int Weight, int SrcKey, int DestKey)
	{
		Vertex* FromVertex = FindVertex(DestKey);
		Vertex* TargetVertex = FindVertex(SrcKey);

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
		queue<Vertex*> BFSQueue;
		//큐 or 스택을 사용해야함.
		cout << "Visited : " << m_VertexList->m_Key << endl;
		m_VertexList->m_Visited = VM_VISITED;

		BFSQueue.push(m_VertexList);

		Vertex* getVertex = m_VertexList;
		Edge* getEdge = m_VertexList->m_AdjList;
		   
		while (BFSQueue.empty() == false)
		{
			getVertex = BFSQueue.front();
			getEdge = getVertex->m_AdjList;
			BFSQueue.pop();

			while (getEdge != nullptr)
			{
				Vertex* TargetNext = getEdge->m_Target->m_Next;

				if (TargetNext != nullptr && TargetNext->m_Visited == VM_NOTVISITED)
				{
					TargetNext->m_Visited = VM_VISITED;
					cout << "Visited : " << TargetNext->m_Key << endl;
					BFSQueue.push(TargetNext);
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

	list<Vertex*>* Dijkstra(int StartKey, int TargetKey)
	{
		Vertex* Start = FindVertex(StartKey);
		Vertex* Target = FindVertex(TargetKey);

		if (Start == nullptr || Target == nullptr)
			return nullptr;

		queue<Vertex*> BFSQueue;
		DijkstraInfo* newNode = new DijkstraInfo[m_Size];

		priority_queue<pair<int, DijkstraInfo>> WeightQueue;
		int StartIndex = 0;
		int EndIndex = 0;

		for (size_t i = 0; i < m_Size; i++)
		{
			newNode[i].Prev = nullptr;
			newNode[i].Visited = false;
			newNode[i].Weight = INT_MIN;
			newNode[i].Target = m_DeleteVec[i];

			if (m_DeleteVec[i]->m_Key == StartKey)
				StartIndex = i;

			if (m_DeleteVec[i]->m_Key == TargetKey)
				EndIndex = i;
		}

		pair<int, DijkstraInfo> TempPair = pair<int, DijkstraInfo>(newNode[StartIndex].Weight, newNode[StartIndex]);
		WeightQueue.push(TempPair);

		while (WeightQueue.empty() == false)
		{
			DijkstraInfo getInfo = {};
			int	Weight = 0;

			Weight = WeightQueue.top().first;
			getInfo = WeightQueue.top().second;

			while (true)
			{
				Edge* getEdge = getInfo.Target->m_AdjList;

				if (getInfo.Target->m_Visited == VM_VISITED)
					continue;

				int EdgeWeight = 0;

			}

		}

		return &m_PathList;
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
	vector<Vertex*> m_DeleteVec;
	int m_Size;
	list<Vertex*> m_PathList;

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
