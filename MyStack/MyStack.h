#pragma once

template<typename T>
class MyStack
{
public:
	MyStack()
	{
		m_Size = 0;
		m_Data = new T[1];
	}

	MyStack(size_t size)
	{
		if (m_Size <= 0 || m_Data != nullptr)
			return;

		m_Size = size;
		m_Data = new T[m_Size];
	}

	~MyStack()
	{
		if (m_Data == nullptr)
			return;

		delete[] m_Data;
		m_Data = nullptr;
	}

	void Pop() 
	{
		if (m_Data == nullptr)
			return;

		m_Data[m_Size--];
	}

	void Push(const T& _Data)
	{
		if (m_Data == nullptr)
			return;

		m_Size++;
		T* newData = new T[m_Size];

		memcpy(newData, m_Data, sizeof(T) * m_Size);

		if (m_Data != nullptr)
		{
			delete m_Data;
			m_Data = nullptr;
		}

		m_Data = newData;
		m_Data[m_Size - 1] = _Data;
	}

	T& Top() { return m_Data[m_Size - 1]; }

	bool Empty() { return m_Size == 0; }
	size_t GetSize() const { return m_Size; }

private:
	T* m_Data;
	size_t m_Size;
};
