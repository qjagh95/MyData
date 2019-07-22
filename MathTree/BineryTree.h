#pragma once

template<typename T>
class BineryTree
{
private:
	class Node
	{
	public:
		Node() :m_Left(nullptr), m_Right(nullptr), m_Top(nullptr) {}
		Node(const T& Data) :m_Data(Data), m_Left(nullptr), m_Right(nullptr), m_Top(nullptr) {}
		~Node() {}

		void PreOrder()
		{
			cout << m_Data << endl;

			if (m_Left != nullptr)
				m_Left->PreOrder();

			if (m_Right != nullptr)
				m_Right->PreOrder();
		}

		void InOrder()
		{
			if (m_Left != nullptr)
				m_Left->InOrder();

			cout << m_Data << endl;

			if (m_Right != nullptr)
				m_Right->InOrder();
		}

		void LastOrder()
		{
			if (m_Left != nullptr)
				m_Left->LastOrder();

			if (m_Right != nullptr)
				m_Right->LastOrder();

			cout << m_Data << endl;
		}

		void Delete()
		{
			if (m_Left != nullptr)
				m_Left->Delete();

			if (m_Right != nullptr)
				m_Right->Delete();

			delete this;
		}

		T m_Data;
		Node* m_Left;
		Node* m_Right;
		Node* m_Top;

		friend BineryTree;
	};

public:
	void InputMathcal(const string& Text) { m_MathCal = Text; }					
	int GetResult() const { return m_ResultValue; }

private:
	string MidToLast(const string& Data);
	int GetOpRank(char Operator);
	OPERATOR_RANK WhoIsFirst(char Src, char Dest);
	bool GetIsNumber(char Data);		

private:
	string m_MathCal;
	int m_ResultValue;

public:
	BineryTree();
	~BineryTree();
};

