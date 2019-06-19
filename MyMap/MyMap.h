#pragma once
#include "stdafx.h"
#define TrueAssert(p) assert(!(p))

template<typename T1, typename T2>
class MyMap
{
private:
	class Node
	{
	public:
		Node() :Left(NULL), Right(NULL), Top(NULL)
		{
			memset(&Key, 0, sizeof(T1));
			memset(&Data, 0, sizeof(T2));
		}
		Node(const T1& _Key, const T2& _Data) :Key(_Key), Data(_Data), Left(NULL), Right(NULL), Top(NULL) {}
		~Node()
		{
			if (Left != NULL)
			{
				delete Left;
				Left = NULL;
			}
			if (Right != NULL)
			{
				delete Right;
				Right = NULL;
			}
		}

		T1 GetKey() const { return Key; }
		T2 GetData() const { return Data; }

		//전위순회
		void FirstOrder()
		{
			//루트노드의 키 출력
			cout << Key << endl;

			//루트노드의 Left의 FirstOrder실행
			if (Left != NULL)
				Left->FirstOrder();
			//루트노드의 Right의 FirstOrder실행
			if (Right != NULL)
				Right->FirstOrder();

			//재귀적 반복으로 인하여 Left의 Left // Right의 Right 계속 실행하며 순회출력한다.
		}
		//중위순회
		void MidOrder()
		{
			if (Left != NULL)
				Left->MidOrder();

			cout << Key << endl;

			if (Right != NULL)
				Right->MidOrder();
		}
		//후위순회
		void LastOrder()
		{
			if (Left != NULL)
				Left->LastOrder();
			if (Right != NULL)
				Right->LastOrder();

			cout << Key << endl;
		}

		void ReversMid()
		{
			if (Right != NULL)
				Right->ReversMid();

			cout << Key << endl;

			if (Left != NULL)
				Left->ReversMid();
		}

		//Find(재귀)
		Node* Find(const T1& _Key)
		{
			if (Key == _Key)
				return this;

			if (Key > _Key)
			{
				if (Left != NULL)
					return Left->Find(_Key);

				return NULL;
			}
			else if (Key < _Key)
			{
				if (Right != NULL)
					return Right->Find(_Key);

				return NULL;
			}
		}

		T1 Key;
		T2 Data;

		Node *Left;
		Node *Right;
		Node *Top;
	};

public:
	class Iter
	{
	public:
		Iter() : CurNode(NULL) {}
		Iter(Node* const _Node) : CurNode(_Node) {}
		~Iter() {}
		friend class MyMap;

		T1& GetKey() const { return CurNode->Key; }
		T2& GetData() const { return CurNode->Data; }
		void SetKey(const T1& Value) { CurNode->Key = Value; }
		Node* GetNode() const { return CurNode; }

		bool operator!=(const Iter& _Value) const { return CurNode != _Value.CurNode; }
		bool operator >(const Iter& _Value) const { return CurNode > _Value.CurNode; }
		bool operator <(const Iter& _Value) const { return CurNode < _Value.CurNode; }

		Iter& operator++(int) 
		{
			if (CurNode->Right != NULL)	        ///오른쪽체크부터 해야한다. (더 큰수를 체크해야되기때문에)
			{
				CurNode = CurNode->Right;       ///있으면 오른쪽으로 보낸다

				while (CurNode->Left != NULL) 	///오른쪽으로 보낸 후 Left를 체크해서 있으면 Left로 다시 옮긴다
					CurNode = CurNode->Left;
			}
			else
			{
				//현재노드의 Top이 NULL이 아니고(루트노드가 아니고)
				//현재노드의 값이 현재노드의Top의 Right와 같다면
				while (CurNode->Top != NULL && CurNode->Top->Right == CurNode)
					CurNode = CurNode->Top;

				//while문과 상관없이 한칸위로 옮겨줌
				CurNode = CurNode->Top;
			}//else
			return (Iter&)CurNode->Key;
		}//operator++()

	private:
		Node* CurNode;
	};

public:
	MyMap() : Size(0), RootNode(NULL) {}
	~MyMap()
	{
		if (RootNode == NULL)
			return;

		delete RootNode;
		RootNode = NULL;
	}

	//데이터삽입
	void Insert(const T1& Key, const T2& Data)
	{
		Size++;
		Node* NewNode = new Node(Key, Data);

		if (Size == 1) 	//처음추가하는노드 (루트노드)
			RootNode = NewNode;

		else //처음추가하는게 아니라면
		{
			if (RootNode == NULL)
				return;

			Node* TempNode = RootNode;

			for (size_t i = 0; i < Size; i++) 				   ///트리 전체의 사이즈만큼 돈다
			{
				if (TempNode->Key > NewNode->Key)
				{
					if (TempNode->Left == NULL) 			   ///빈공간 찾았다 거기에삽입한다
					{
						TempNode->Left = NewNode;
						NewNode->Top = TempNode;
					}

					TrueAssert(TempNode->Key == NewNode->Key); ///키값이 같다면 터진다. 
					TempNode = TempNode->Left;				   ///다음으로 넘겨라~
				}

				else if (TempNode->Key < NewNode->Key)
				{
					if (TempNode->Right == NULL)			   ///빈공간 찾았다 거기에 삽입한다
					{
						TempNode->Right = NewNode;
						NewNode->Top = TempNode;
					}

					TrueAssert(TempNode->Key == NewNode->Key);
					TempNode = TempNode->Right;
				}
			}//for(size)
		}//else
	}//insert()

	Iter Begin()
	{
		Node* TempNode = RootNode;

		while (TempNode->Left != NULL)
			TempNode = TempNode->Left;

		return TempNode;
	}

	Iter End()
	{
		return NULL;
	}

	Iter Find(const T1& KeyValue)
	{
		Node* TempNode = RootNode;

		while (TempNode != NULL)		       ///들어온값의 크기에따라 Left Right를 알아서 찾아간다.
		{
			if (TempNode->Key == KeyValue)
				return TempNode;

			else if (TempNode->Key < KeyValue)
				TempNode = TempNode->Right;

			else if (TempNode->Key > KeyValue)
				TempNode = TempNode->Left;
		}

		return NULL;
		//재귀방식 Find
		//return RootNode->Find(KeyValue);
	}

	void Delete(Iter _Iter)
	{
		Node* EraseNode = _Iter.CurNode;

		if (EraseNode == NULL)
			return;

		if (EraseNode->Left == NULL && EraseNode->Right == NULL && EraseNode->Top != NULL) ///자식이 아무것도 없을경우	
		{
			if (EraseNode->Top->Left == EraseNode)
				EraseNode->Top->Left = NULL;
			else if (EraseNode->Top->Left == EraseNode)
				EraseNode->Top->Right = NULL;
			else
				EraseNode = NULL;
		}

		else if (EraseNode->Left == NULL || EraseNode->Right == NULL) ///하나의 자식노드를 가지는 경우
		{
			if (EraseNode->Left != NULL)		///Left가 존재할때
			{
				EraseNode->Left->Top = EraseNode->Top;

				if (EraseNode->Top->Left != NULL)
				{
					if (EraseNode->Top != RootNode)
						EraseNode->Top->Left = EraseNode->Left;

					if (EraseNode->Top == RootNode && EraseNode->GetKey() < RootNode->GetKey())
						RootNode->Left = EraseNode->Left;
				}

				else
					EraseNode->Top->Right = EraseNode->Left;

				EraseNode->Left = NULL;
			}

			else if (EraseNode->Right != NULL) ///Right가 존재할때
			{
				EraseNode->Right->Top = EraseNode->Top;

				if (EraseNode->Top->Left != NULL)
				{
					if (EraseNode->Top != RootNode)
						EraseNode->Top->Left = EraseNode->Left;

					if (EraseNode->Top == RootNode && EraseNode->GetKey() > RootNode->GetKey())
						RootNode->Right = EraseNode->Right;
				}

				else
					EraseNode->Top->Right = EraseNode->Left;

				EraseNode->Right = NULL;
			}//else if
		} //else(Node->Left || Right != NULL)
		else								       ///두개의 자식노드를 가지는 경우 (바꿔야함)
		{
			Node* TempNode = EraseNode->Left;
			Node* TempRoot = EraseNode;

			while (TempNode->Left != NULL)         /// 왼쪽 서브트리의 가장 큰값을 찾는다
			{
				EraseNode = TempNode;
				TempNode = TempNode->Right;
			}

			if (EraseNode->Left == TempNode)
				EraseNode->Left = TempNode->Left;

			else if (EraseNode->Right == TempNode)
				EraseNode->Right = TempNode->Left;

			EraseNode->Key = TempNode->Key;
			EraseNode = TempNode;
		}//else

		delete EraseNode;
		EraseNode = NULL;
	}

	//전위순회(넣어준 순서대로 나옴)
	void FirstOrder()
	{
		//Node 클래스안에서 재귀함수를 이용한 전위순회
		RootNode->FirstOrder();
	}

	//중위순회(작은수부터 순서대로 정렬)
	void MidOrder()
	{
		//Node 클래스안에서 재귀함수를 이용한 중위순회
		RootNode->MidOrder();
	}
	//리버스 중위순회
	void ReversMid()
	{
		RootNode->ReversMid();
	}
	//후위순회(작은수부터 순서대로 나온 후 제일마지막에 루트노드)
	void LastOrder()
	{
		//Node 클래스안에서 재귀함수를 이용한 후위순회
		RootNode->LastOrder();
	}

private:
	Node* RootNode;
	size_t Size;

	//재귀함수를 쓰지않고 순회를 한다면 스택을사용해야함
	//스택사용시 코드도 복잡해서 그냥 재귀로하는게 편하고 좋다
	stack<Node*> RootStack;
};
