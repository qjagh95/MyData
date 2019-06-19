#pragma once
#include <assert.h>

template <typename T1, typename T2>
class BineryTree
{
public:
	class Node
	{
	public:
		Node() :m_Left(nullptr), m_Right(nullptr), m_Top(nullptr) {}
		Node(const T1& Key, const T2& Data) :m_Key(Key), m_Data(Data), m_Left(nullptr), m_Right(nullptr), m_Top(nullptr) {}
		~Node() {}

		T1 m_Key;
		T2 m_Data;
		Node* m_Left;
		Node* m_Right;
		Node* m_Top;

		friend BineryTree;
	};

public:
	void Insert(const T1& Key, const T2& Data)
	{
		m_Size++;
		Node* newNode = new Node(Key, Data);

		if (m_Size == 1)
		{
			m_Root = newNode;
			return;
		}

		Node* getNode = m_Root;

		for (size_t i = 0; i < m_Size; i++)
		{
			if (newNode->m_Key == getNode->m_Key)
				assert(false);

			if (newNode->m_Key > m_Root->m_Key)
			{
				if (getNode->m_Left == nullptr)
				{
					getNode->m_Left = newNode;
					newNode->m_Top = getNode;
				}
				getNode = getNode->m_Left;

			}
			else if(newNode->m_Key < m_Root->m_Key)
			{
				if (getNode->m_Right == nullptr)
				{
					getNode->m_Right = newNode;
					newNode->m_Top = getNode;
				}
				getNode = getNode->m_Right;
			}

		}
	}

public:
	BineryTree()
	{
		m_Size = 0;
	}
	~BineryTree() {}


private:
	Node* m_Root;
	size_t m_Size;
};