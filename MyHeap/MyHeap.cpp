#include "pch.h"
#include <iostream>
#include "MyHeap.h"
#include <queue>
#include <vector>

using namespace std;

int main()
{
	priority_queue<int> a;
	a.push(123);
	a.push(456);
	a.push(12);
	a.push(136);
	a.push(420);

	for (size_t i = 0; i < 5; i++)
	{
		cout << a.top() << endl;
		a.pop();
	}

	cout << endl;

	MyHeap<int> b;

	b.Insert(123);
	b.Insert(456);
	b.Insert(12);
	b.Insert(136);
	b.Insert(420);

	//for (size_t i = 0; i < 5; i++)
	//{
	//	cout << b.Top() << endl;
	//	b.Pop();
	//}
}

