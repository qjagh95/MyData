#pragma once

template<typename T>
class MyList
{
private:
	class Node
	{
	public:
		Node() :m_Next(nullptr), m_Prev(nullptr) {}
		Node(const T& Data) :m_Data(Data), m_Next(nullptr), m_Prev(nullptr) {}
		~Node() {}

		T m_Data;
		Node* m_Next;
		Node* m_Prev;

		friend MyList;
	};

public:
	class Iterator
	{
	public:
		Iterator(const Iterator& Iter) { m_CurNode = Iter; }
		Iterator(Node* node) { m_CurNode = node; }

		Iterator& operator++(int) 
		{ 
			m_CurNode = m_CurNode->m_Next;
			return *this;
		}
		Iterator& operator++()
		{
			m_CurNode = m_CurNode->m_Next;
			return *this;
		}
		Iterator& operator--() 
		{ 
			m_CurNode = m_CurNode->m_Prev;
			return *this;
		}
		bool operator!=(const Iterator& Iter) { return m_CurNode != Iter.m_CurNode; }
		T& operator*() { return m_CurNode->m_Data; }

	private:
		Node* m_CurNode;
		friend MyList;
	};

public:
	MyList()
	{
		m_Size = 0;

		m_First.m_Next = &m_Last;
		m_First.m_Prev = nullptr;

		m_Last.m_Prev = &m_First;
		m_Last.m_Next = nullptr;
	}

	void Push_Back(const T& Data)
	{
		Node* newData = new Node(Data);

		newData->m_Prev = m_Last.m_Prev;
		newData->m_Next = &m_Last;

		m_Last.m_Prev->m_Next = newData;
		m_Last.m_Prev = newData;
	}

	void Front_Back(const T& Data)
	{
		Node* newData = new Node(Data);

		newData->m_Next = m_First.m_Next;
		newData->m_Prev = &m_First;

		m_First.m_Next = newData;
		m_First.m_Next->m_Prev = newData;
	}

	void Insert(Iterator& Iter, const T& Data)
	{
		Node* newData = new Node(Data);
		Node* getNode = Iter.m_CurNode;

		newData->m_Prev = getNode;
		newData->m_Next = getNode->m_Next;

		getNode->m_Next = newData;
		getNode->m_Next->m_Prev = newData;
	}

	void Erase(Iterator& Iter)
	{
		Node* DeleteNode = Iter.m_CurNode;

		DeleteNode->m_Next->m_Prev = DeleteNode->m_Prev;
		DeleteNode->m_Prev->m_Next = DeleteNode->m_Next;
	}

	Iterator Begin() { return m_First.m_Next; }
	Iterator End() { return &m_Last; }

private:
	Node m_First;
	Node m_Last;
	size_t m_Size;
};
