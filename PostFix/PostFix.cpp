#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <Windows.h>

using namespace std;

enum OPERATOR_RANK
{
	OR_SAME = 0,
	OR_SRC = 1,
	OR_DEST = -1,
};

string MidToLast(const string& Data);									//중위식 -> 후위식 변환
int GetOpRank(char Operator);											//연산자 우선순위를 반환한다
OPERATOR_RANK WhoIsFirst(char Src, char Dest);							//누가 우선순위가 더 큰지 반환값으로 판단한다
bool GetIsNumber(char Data);											//char데이터가 문자형 데이터인지 판별한다
float Result(const string& Data);										//변환된 후위식을 계산한다.
void Cal(char Operator, float Src, float Dest, stack<float>& Stack);    //연산자에따라 스택에 Push 함수.

int main()
{
	string Input;
	float Out = 0;

	while (true)
	{
		cout << "수식을 입력하세요 (종료 : Q) : ";
		getline(cin, Input);

		if (Input == "Q" || Input == "q" || Input == "ㅃ" || Input == "ㅂ")
			return 0;

		string PostFix = MidToLast(Input);
		Out = Result(PostFix);

		printf_s("결과는 : %.4f \n", Out);
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
				char Top = OperatorStack.top();
				OperatorStack.pop();

				Convert += Top;
			}

			else if (GetChar == '+' || GetChar == '-' || GetChar == '*' || GetChar == '/')
			{
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

float Result(const string & Data)
{
	stack<float> NumberStack;
	float Value = 0.0f;

	for (size_t i = 0; i < Data.size(); i++)
	{
		char GetChar = Data[i];

		size_t Index = i;
		if (GetIsNumber(GetChar) == true)
		{
			string NumberString;
			while (true)
			{
				if (GetIsNumber(Data[Index]) == false)
				{
					i = Index;
					break;
				}
				NumberString += Data[Index];
				Index++;
			}

			int Number = stoi(NumberString);
			NumberStack.push(static_cast<float>(Number));
		}
		else
		{
			float Dest = NumberStack.top();
			NumberStack.pop();

			float Src = NumberStack.top();
			NumberStack.pop();

			Cal(GetChar, Src, Dest, NumberStack);
		}
	}

	return NumberStack.top();
}

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