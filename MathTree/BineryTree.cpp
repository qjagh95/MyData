#include "pch.h"
#include "BineryTree.h"

BineryTree::BineryTree()
{
	m_ResultValue = 0;
}

BineryTree::~BineryTree()
{
}

string BineryTree::MidToLast(const string & Data)
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
				char Top = OperatorStack.top();
				OperatorStack.pop();

				Convert += Top;
			}

			else if (GetChar == '+' || GetChar == '-' || GetChar == '*' || GetChar == '/')
			{
				//연산자 우선순위 비교
				while (OperatorStack.empty() == false && WhoIsFirst(OperatorStack.top(), GetChar) > OR_SAME)
				{
					Convert += OperatorStack.top();
					OperatorStack.pop();
				}
				OperatorStack.push(GetChar);
			}
		}
	}

	size_t StackSize = OperatorStack.size();
	for (size_t i = 0; i < StackSize; i++)
	{
		Convert += OperatorStack.top();
		OperatorStack.pop();
	}

	return Convert;
}

int BineryTree::GetOpRank(char Operator)
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

OPERATOR_RANK BineryTree::WhoIsFirst(char Src, char Dest)
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

bool BineryTree::GetIsNumber(char Data)
{
	if (Data >= '0' && Data <= '9')
		return true;

	return false;
}
