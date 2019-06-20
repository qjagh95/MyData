#pragma once

template<typename T>
class MyHeap
{
private:


public:
	MyHeap()
	{
		m_Data = new T[1];
	}
	~MyHeap()
	{
		delete[] m_Data;
	}


public:
	T* m_Data;
	size_t m_Size;
};