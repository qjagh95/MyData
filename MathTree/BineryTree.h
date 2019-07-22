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
	int GetResult() const
	{
		return m_ResultValue; 
	}

	void Insert(T& Data)
	{
		Node* newNode = new Node(Data);

		if (m_Size == 0)
		{
			m_Size++;
			m_Root = newNode;
			return;
		}

		Node* getNode = m_Root;

		for (size_t i = 0; i < m_Size; i++)
		{
			if (newNode->m_Data == getNode->m_Data)
				return;

			if (newNode->m_Data < m_Root->m_Data)
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
			else if (newNode->m_Data > m_Root->m_Data)
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

private:
	void Cal(char Operator, float Src, float Dest, stack<float>& Stack)
	{

		switch (Operator)
		{
		case '+':
			Stack.push(Src + Dest);
			break;
		case '-':
			Stack.push(Src - Dest);
			break;
		case '*':
			Stack.push(Src * Dest);
			break;
		case '/':
			Stack.push(Src / Dest);
			break;
		}
	}

	void Calculator()
	{
		if (m_Size == 0)
			return;
		
		if (m_Root == nullptr)
			return;

		if (m_MathCal.empty() == true)
			return;

		for (size_t i = 0; i < m_MathCal.size(); i++)
		{
			char GetChar = Data[i];

			size_t Index = i;

			if (GetIsNumber(GetChar) == true)
			{
				string NumberString;
				while (true)
				{
					if (GetIsNumber(m_MathCal[Index]) == false)
					{
						i = Index;
						break;
					}
					NumberString += m_MathCal[Index];
					Index++;
				}

				int Number = stoi(NumberString);
				m_NumberStack.push(static_cast<float>(Number));
			}
		}
	}

	string MidToLast(const string& Data)
	{
		string Convert;
		stack<char> OperatorStack;

		for (size_t i = 0; i < Data.size(); i++)
		{
			char GetChar = Data[i];

			if (GetIsNumber(GetChar) == true)
			{
				size_t Index = i;
				while (true)
				{
					if (GetIsNumber(Data[Index]) == false)
					{
						i = Index - 1;  //넘어가면 ++ 되기때문에 -1
						Convert += " "; //자릿수 공백
						break;
					}

					Convert += Data[Index];
					Index++;
				}
			}
			else
			{
				if (GetChar == ')')
				{
					char Top = m_OperatorStack.top();
					m_OperatorStack.pop();

					Convert += Top;
				}

				else if (GetChar == '+' || GetChar == '-' || GetChar == '*' || GetChar == '/')
				{
					//연산자 우선순위 비교
					while (m_OperatorStack.empty() == false && WhoIsFirst(m_OperatorStack.top(), GetChar) > OR_SAME)
					{
						Convert += m_OperatorStack.top();
						m_OperatorStack.pop();
					}
					m_OperatorStack.push(GetChar);
				}
			}
		}

		size_t StackSize = m_OperatorStack.size();
		for (size_t i = 0; i < StackSize; i++)
		{
			Convert += m_OperatorStack.top();
			m_OperatorStack.pop();
		}

		return Convert;
	}

	int GetOpRank(char Operator)
	{
		switch (Operator)
		{
		case '(':
			return 10;
			break;

		case '+':
		case '-':
			return 20;
			break;

		case '*':
		case '/':
			return 30;
			break;

		default:
			return -10;
			break;
		}

		return -10;
	}

	OPERATOR_RANK WhoIsFirst(char Src, char Dest)
	{
		int SrcRank = GetOpRank(Src);
		int DestRank = GetOpRank(Dest);

		if (SrcRank > DestRank)
			return OR_SRC;

		else if (DestRank > SrcRank)
			return OR_DEST;

		else
			return OR_SAME;
	}

	bool GetIsNumber(char Data)
	{
		if (Data >= '0' && Data <= '9')
			return true;

		return false;
	}
	void PreOrder() { m_Root->PreOrder(); }
	void InOrder() { m_Root->InOrder(); }
	void LastOrder() { m_Root->LastOrder(); }
	void Delete() { m_Root->Delete(); }

private:
	string m_MathCal;
	int m_ResultValue;
	stack<int> m_NumberStack;
	stack<char> m_OperatorStack;
	int m_Size;
	Node* m_Root;

public:
	BineryTree()
	{
		m_Size = 0;
	}
	~BineryTree() {}
};

