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

		//������ȸ
		void FirstOrder()
		{
			//��Ʈ����� Ű ���
			cout << Key << endl;

			//��Ʈ����� Left�� FirstOrder����
			if (Left != NULL)
				Left->FirstOrder();
			//��Ʈ����� Right�� FirstOrder����
			if (Right != NULL)
				Right->FirstOrder();

			//����� �ݺ����� ���Ͽ� Left�� Left // Right�� Right ��� �����ϸ� ��ȸ����Ѵ�.
		}
		//������ȸ
		void MidOrder()
		{
			if (Left != NULL)
				Left->MidOrder();

			cout << Key << endl;

			if (Right != NULL)
				Right->MidOrder();
		}
		//������ȸ
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

		//Find(���)
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
			if (CurNode->Right != NULL)	        ///������üũ���� �ؾ��Ѵ�. (�� ū���� üũ�ؾߵǱ⶧����)
			{
				CurNode = CurNode->Right;       ///������ ���������� ������

				while (CurNode->Left != NULL) 	///���������� ���� �� Left�� üũ�ؼ� ������ Left�� �ٽ� �ű��
					CurNode = CurNode->Left;
			}
			else
			{
				//�������� Top�� NULL�� �ƴϰ�(��Ʈ��尡 �ƴϰ�)
				//�������� ���� ��������Top�� Right�� ���ٸ�
				while (CurNode->Top != NULL && CurNode->Top->Right == CurNode)
					CurNode = CurNode->Top;

				//while���� ������� ��ĭ���� �Ű���
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

	//�����ͻ���
	void Insert(const T1& Key, const T2& Data)
	{
		Size++;
		Node* NewNode = new Node(Key, Data);

		if (Size == 1) 	//ó���߰��ϴ³�� (��Ʈ���)
			RootNode = NewNode;

		else //ó���߰��ϴ°� �ƴ϶��
		{
			if (RootNode == NULL)
				return;

			Node* TempNode = RootNode;

			for (size_t i = 0; i < Size; i++) 				   ///Ʈ�� ��ü�� �����ŭ ����
			{
				if (TempNode->Key > NewNode->Key)
				{
					if (TempNode->Left == NULL) 			   ///����� ã�Ҵ� �ű⿡�����Ѵ�
					{
						TempNode->Left = NewNode;
						NewNode->Top = TempNode;
					}

					TrueAssert(TempNode->Key == NewNode->Key); ///Ű���� ���ٸ� ������. 
					TempNode = TempNode->Left;				   ///�������� �Ѱܶ�~
				}

				else if (TempNode->Key < NewNode->Key)
				{
					if (TempNode->Right == NULL)			   ///����� ã�Ҵ� �ű⿡ �����Ѵ�
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

		while (TempNode != NULL)		       ///���°��� ũ�⿡���� Left Right�� �˾Ƽ� ã�ư���.
		{
			if (TempNode->Key == KeyValue)
				return TempNode;

			else if (TempNode->Key < KeyValue)
				TempNode = TempNode->Right;

			else if (TempNode->Key > KeyValue)
				TempNode = TempNode->Left;
		}

		return NULL;
		//��͹�� Find
		//return RootNode->Find(KeyValue);
	}

	void Delete(Iter _Iter)
	{
		Node* EraseNode = _Iter.CurNode;

		if (EraseNode == NULL)
			return;

		if (EraseNode->Left == NULL && EraseNode->Right == NULL && EraseNode->Top != NULL) ///�ڽ��� �ƹ��͵� �������	
		{
			if (EraseNode->Top->Left == EraseNode)
				EraseNode->Top->Left = NULL;
			else if (EraseNode->Top->Left == EraseNode)
				EraseNode->Top->Right = NULL;
			else
				EraseNode = NULL;
		}

		else if (EraseNode->Left == NULL || EraseNode->Right == NULL) ///�ϳ��� �ڽĳ�带 ������ ���
		{
			if (EraseNode->Left != NULL)		///Left�� �����Ҷ�
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

			else if (EraseNode->Right != NULL) ///Right�� �����Ҷ�
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
		else								       ///�ΰ��� �ڽĳ�带 ������ ��� (�ٲ����)
		{
			Node* TempNode = EraseNode->Left;
			Node* TempRoot = EraseNode;

			while (TempNode->Left != NULL)         /// ���� ����Ʈ���� ���� ū���� ã�´�
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

	//������ȸ(�־��� ������� ����)
	void FirstOrder()
	{
		//Node Ŭ�����ȿ��� ����Լ��� �̿��� ������ȸ
		RootNode->FirstOrder();
	}

	//������ȸ(���������� ������� ����)
	void MidOrder()
	{
		//Node Ŭ�����ȿ��� ����Լ��� �̿��� ������ȸ
		RootNode->MidOrder();
	}
	//������ ������ȸ
	void ReversMid()
	{
		RootNode->ReversMid();
	}
	//������ȸ(���������� ������� ���� �� ���ϸ������� ��Ʈ���)
	void LastOrder()
	{
		//Node Ŭ�����ȿ��� ����Լ��� �̿��� ������ȸ
		RootNode->LastOrder();
	}

private:
	Node* RootNode;
	size_t Size;

	//����Լ��� �����ʰ� ��ȸ�� �Ѵٸ� ����������ؾ���
	//���û��� �ڵ嵵 �����ؼ� �׳� ��ͷ��ϴ°� ���ϰ� ����
	stack<Node*> RootStack;
};
