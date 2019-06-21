#pragma once
#include <functional>
using namespace std;

template<typename T>
class MyHeap
{
public:
	void SetSortFunc(bool(*Func)(const T&, const T&))
	{
		m_CompairFunc = bind(Func, placeholders::_1, placeholders::_2);
	}

	template <typename Type>
	void SetSortFunc(Type* Caller, bool(Type::*Func)(const T&, const T&))
	{
		m_CompairFunc = bind(Func, Caller, placeholders::_1, placeholders::_2);
	}

	void Resize(int Size)
	{
		if (Size <= m_Capacity)
			return;

		m_Capacity = Size;

		T* newData = new T[m_Capacity];
		memcpy(newData, m_Data, sizeof(T) * m_Size);

		delete[] m_Data;

		m_Data = newData;
	}

	void Insert(const T& Data)
	{
		Resize();

		//항상 배열의 마지막에 넣는다.
		m_Data[m_Size] = Data;

		if (m_Size == 0)
		{
			m_Size++;
			return;
		}

		int ParentIndex = (m_Size - 1) / 2;
	
		while (ParentIndex > 0)
		{
			if (m_CompairFunc(Data, m_Data[ParentIndex]))
			{
				T Temp = m_Data[m_Size];
				m_Data[m_Size] = m_Data[ParentIndex];
				m_Data[ParentIndex] = Temp;
			}

			//부모를 계속 타고들어감
			ParentIndex = ParentIndex / 2;
		};

		m_Size++;
	}
private:
	void Resize()
	{
		if (m_Size <= m_Capacity)
			return;

		m_Capacity *= 2;

		T* newData = new T[m_Capacity];
		memcpy(newData, m_Data, sizeof(T) * m_Size);

		delete[] m_Data;

		m_Data = newData;
	}

	static bool DefaultSort(const T& Src, const T& Dest)
	{
		return Src < Dest;
	}

	size_t GetParentIndex(size_t Index) { return Index / 2; }
	size_t GetLeftChildIndex(size_t Index) { return Index * 2 + 1; }
	size_t GetRightChildIndex(size_t Index) { return Index * 2 + 2; }

public:
	MyHeap()
	{
		m_Capacity = 100;
		m_Size = 0;
		m_Data = new T[m_Capacity];
		SetSortFunc(MyHeap<T>::DefaultSort);
	}
	~MyHeap() { delete[] m_Data; }

private:
	T* m_Data;
	function<bool(const T&, const T&)> m_CompairFunc;

	size_t m_Size;
	size_t m_FirstSize;
	size_t m_Capacity;
};