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

		//-0.5가 나오기때문에 float
		float ParentIndex = (m_Size - 1.0f) / 2.0f;

		while (ParentIndex >= 0)
		{
			if (m_CompairFunc(Data, m_Data[static_cast<int>(ParentIndex)]))
			{
				T Temp = m_Data[m_Size];
				m_Data[m_Size] = m_Data[static_cast<int>(ParentIndex)];
				m_Data[static_cast<int>(ParentIndex)] = Temp;
			}

			ParentIndex = (ParentIndex - 1.0f) / 2.0f;
		};

		m_Size++;
	}

	void HeapSort()
	{
		int FirstIndex = 0;
		int LastIndex = m_Size;

		while (true)
		{
			if (LastIndex == 0)
				break;

			int LChildIndex = GetLeftChildIndex(FirstIndex);
			int RChildIndex = GetRightChildIndex(FirstIndex);

			if (m_Data[LChildIndex] > m_Data[RChildIndex])
			{
				T Temp = m_Data[LastIndex];
				m_Data[LastIndex] = m_Data[RChildIndex];
				m_Data[RChildIndex] = Temp;
			}
			else
			{
				T Temp = m_Data[LastIndex];
				m_Data[LastIndex] = m_Data[LChildIndex];
				m_Data[LChildIndex] = Temp;
			}

			m_Size--;
			LastIndex--;
		}

		int a = 0;
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
		return Src > Dest;
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