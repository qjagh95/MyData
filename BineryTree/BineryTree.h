#pragma once
#include <assert.h>
#include <iostream>
using namespace std;

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

		void PreOrder()
		{
			cout << m_Key << endl;

			if (m_Left != nullptr)
				m_Left->PreOrder();

			if (m_Right != nullptr)
				m_Right->PreOrder();
		}
		
		void InOrder()
		{
			if (m_Left != nullptr)
				m_Left->InOrder();

			cout << m_Key << endl;

			if (m_Right != nullptr)
				m_Right->InOrder();
		}

		void LastOrder()
		{
			if (m_Left != nullptr)
				m_Left->LastOrder();

			if (m_Right != nullptr)
				m_Right->LastOrder();

			cout << m_Key << endl;
		}

		void Delete()
		{
			if (m_Left != nullptr)
				m_Left->Delete();

			if (m_Right != nullptr)
				m_Right->Delete();

			delete this;
		}


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
		Node* newNode = new Node(Key, Data);

		if (m_Size == 0)
		{
			m_Size++;
			m_Root = newNode;
			return;
		}

		Node* getNode = m_Root;

		for (size_t i = 0; i < m_Size; i++)
		{
			if (newNode->m_Key == getNode->m_Key)
				assert(false);

			if (newNode->m_Key < m_Root->m_Key)
			{
				if (getNode->m_Left == nullptr)
				{
					getNode->m_Left = newNode;
					newNode->m_Top = getNode;
					m_Size++;
					return;
				}
				getNode = getNode->m_Left;

			}
			else if(newNode->m_Key > m_Root->m_Key)
			{
				if (getNode->m_Right == nullptr)
				{
					getNode->m_Right = newNode;
					newNode->m_Top = getNode;
					m_Size++;
					return;
				}
				getNode = getNode->m_Right;
			}
		}

	}

	T2& Find(const T1& Key)
	{
		Node* getNode = m_Root;

		while (true)
		{
			if (getNode->m_Key == Key)
				return getNode->m_Data;

			else if (getNode->m_Key > Key)
				getNode = getNode->m_Right;
			
			else if (getNode->m_Key < Key)
				getNode = getNode->m_Left;
		}
	}

public:
	BineryTree()
	{
		m_Size = 0;
	}
	~BineryTree() {}

	void PreOrder() { m_Root->PreOrder(); }
	void InOrder() { m_Root->InOrder(); }
	void LastOrder() { m_Root->LastOrder(); }
	void Delete() { m_Root->Delete(); }

private:
	Node* m_Root;
	size_t m_Size;
};