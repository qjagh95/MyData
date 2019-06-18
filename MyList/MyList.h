#pragma once

template<typename T>
class MyList
{
	class Node
	{
		Node(const T& Data)
		{

		}
		Node(T* Data)
		{

		}

	private:
		T Data;
		Node* m_Next;
	};

};
