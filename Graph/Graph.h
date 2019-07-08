#pragma once
#include <unordered_map>
#include <iostream>
#include "Basic.h"
#include <queue>
#include <algorithm>
#include <functional>
#include <stack>

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
		m_PathList.clear();

		Vertex* Start = FindVertex(StartKey);
		Vertex* Target = FindVertex(TargetKey);

		if (Start == nullptr || Target == nullptr)
			return nullptr;

		queue<Vertex*> BFSQueue;
		priority_queue<Vertex*, vector<Vertex*>, function<bool(Vertex*, Vertex*)>> WeightQueue
		{ 
			[](Vertex* Left, Vertex* Right) 
			{
			return Left->m_Weight > Right->m_Weight;
			} 
		};

		BFSQueue.push(Start);

		Vertex* getVertex = Start;
		Vertex* SelectVertex = Start;
		Start->m_Weight = 0;
		WeightQueue.push(SelectVertex);

		Edge* getEdge = Start->m_AdjList;
		stack<Vertex*> VertexStack;

		while (WeightQueue.empty() == false)
		{
			getVertex = WeightQueue.top();
			getEdge = getVertex->m_AdjList;
			WeightQueue.pop();

			while (getEdge != nullptr)
			{
				Vertex* EdgeFrom = getEdge->m_From;

				if (EdgeFrom != nullptr)
				{
					if (EdgeFrom->m_Weight <= INT_MAX && (getVertex->m_Weight + getEdge->m_Weight) < EdgeFrom->m_Weight)
					{
						EdgeFrom->m_Weight = getVertex->m_Weight + getEdge->m_Weight;
						EdgeFrom->m_Prev = getVertex;
					}

					WeightQueue.push(EdgeFrom);
				}
				getEdge = getEdge->m_Next;
			}
		}

		size_t StackSize = VertexStack.size();

		for (size_t i = 0; i < StackSize; i++)
		{

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
