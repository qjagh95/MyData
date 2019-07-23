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
	bool isCheck2 = false;

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
		else if (i == 0 && GetChar == '-')
		{
			int Temp = 0;
			bool isCheck = false;

			while (true)
			{
				Convert += Data[Temp];
				Temp++;

				isCheck = true;

				if (GetIsNumber(Data[Temp]) == false && isCheck == true)
				{
					Convert += " ";
					break;
				}
			}

			i = Temp - 1;
		}
		else
		{
			if (GetChar == '(')
				isCheck2 = true;

			if (OperatorStack.size() == 1 && OperatorStack.top() == '-' && isCheck2 == false)
			{
				string Temp;
				vector<float> vecData;

				OperatorStack.pop();
				OperatorStack.push(GetChar);

				for (size_t i = 0; i < Convert.size(); i++)
				{
					Temp += Convert[i];

					if (Convert[i] == ' ')
					{
						float Temp2 = stof(Temp);
						vecData.push_back(Temp2);
						Temp.clear();
						continue;
					}
				}

				if (vecData.size() == 1)
					break;

				char Buffer[255] = {};
				float Value = vecData[0] - vecData[1];
				_itoa_s(Value, Buffer, 255, 10);
				Convert = Buffer;
				Convert+= " ";
			}

			else if (GetChar == ')')
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
	bool isCheck = false;

	for (size_t i = 0; i < Data.size(); i++)
	{
		char GetChar = Data[i];

		size_t Index = i;
		if (GetIsNumber(GetChar) == true || (i == 0 && GetChar == '-' && isCheck == false))
		{
			string NumberString;

			if (i == 0 && GetChar == '-')
			{
				int Temp = 0;
				string TempStr;
				while (Data[Temp] != ' ')
				{
					TempStr += Data[Temp];
					Temp++;
				}
				Index = Temp;

				int Value = stoi(TempStr);

				char Buffer[255] = { };
				_itoa_s(Value, Buffer, 255, 10);
				NumberString = Buffer;
				isCheck = true;
			}

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