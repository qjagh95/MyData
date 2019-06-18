#pragma once

template <typename T>
class MyVector
{
public:
	MyVector()
	{
		m_Capacity = 10;
		m_Size = 0;

		m_Data = new T[m_Capacity];
	}

	~MyVector()
	{
		if (m_Data != nullptr)
		{
			delete m_Data;
			m_Data = nullptr;
		}
	}

	void Push_Back(const T& Data)
    {
		m_Data[m_Size] = Data;

		m_Size++;
		Resize();
	}

	void Erase(int Index)
	{
		int Convert = Index - 1;

		for (size_t i = Convert; i < m_Size; i++)
			m_Data[i] = m_Data[i + 1];

		m_Size--;
	}

	void Front_Back(const T& Data)
	{
		for (size_t i = m_Size - 1; i > 0; i--)
			m_Data[i] = m_Data[i - 1];

		m_Data[0] = Data;

		m_Size++;
		Resize();
	}

	void Clear()
	{
		m_Size = 0;
	}

	void Insert(size_t Index, const T& Data)
	{
		m_Size++;
		Resize();

		for (size_t i = m_Size - 1; i > Index; i--)
			m_Data[i] = m_Data[i - 1];

		m_Data[Index] = Data;
	}

	void Resize(size_t Size)
	{
		if (m_Size > Size)
			return;

		if (m_Capacity > Size)
			return;

		T* newData = new T[Size];

		memcpy(newData, m_Data, sizeof(T) * m_Size);

		if (m_Data != nullptr)
		{
			delete[] m_Data;
			m_Data = nullptr;
		}

		m_Data = newData;
	}

	T& operator[](int i) const{ return m_Data[i]; }
	size_t GetSize() const { return m_Size; }
	size_t GetCapacity() const { return m_Capacity; }

private:
	void Resize()
	{
		if (m_Capacity != m_Size)
			return;

		m_Capacity *= 2;

		T* newData = new T[m_Capacity];

		memcpy(newData, m_Data, sizeof(T*) * m_Size);

		if (m_Data != nullptr)
		{
			delete[] m_Data;
			m_Data = nullptr;
		}

		m_Data = newData;
	}

private:
	size_t m_Capacity;
	size_t m_Size;

	T* m_Data;
};