#pragma once

template<typename T>
class MyQueue
{
public:
	MyQueue()
	{
		m_Size = 0;
		m_FirstSize = 0;
		m_Data = new T[1];
	}

	~MyQueue()
	{
		if (m_Data != nullptr)
		{
			delete[] m_Data;
			m_Data = nullptr;
		}
	}

	void Push(const T& Data)
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
		m_Data[m_Size - 1] = Data;
	}

	const T& Front()
	{
		return m_Data[m_FirstSize];
	}
	const T& Back()
	{
		return m_Data[m_Size];
	}
	void Pop()
	{
		m_FirstSize++;
	}
	bool Empty()
	{
		return m_Size == 1;
	}

private:
	T* m_Data;
	size_t m_Size;
	size_t m_FirstSize;
};