#pragma once
#include <list>
using namespace std;

enum VISIT_MODE
{
	VM_VISITED,
	VM_NOTVISITED,
};

template<typename T>
class Graph
{
public:
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
		T m_Data;
		int m_Visited;
		int m_Index;

		Vertex* m_Next;
		list<Edge*> m_vecAdjList;

		Vertex()
		{
			m_Next = nullptr;
			m_Visited = VM_NOTVISITED;
			m_Index = -1;
		}
	};

	void AddVertex()
	{
		Vertex* newVertex = new Vertex();
		m_vecVertex.push_back(newVertex);

		newVertex->m_Index = m_Size++;
	}
	void AddEdge()
	{
		Edge* newEdge = new Edge();


	}
	void PrintGraph()
	{

	}

private:
	list<Vertex*> m_vecVertex;
	int m_Size;

public:
	Graph()
	{
		m_Size = 0;
		
		Vertex* newVertex = new Vertex();
		m_vecVertex.push_back(newVertex);
	}
	~Graph()
	{
		auto StartIter = m_vecVertex.begin();
		auto EndIter = m_vecVertex.end();

		for (; StartIter != EndIter; StartIter++)
			delete *StartIter;
	}
};
