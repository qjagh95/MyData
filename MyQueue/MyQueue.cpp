#include "pch.h"
#include <iostream>
#include <queue>
#include "MyQueue.h"
using namespace std;

int main()
{
	queue<int> a;
	for (size_t i = 0; i < 10; i++)
		a.push(i);
	for (size_t i = 0; i < 10; i++)
	{
		cout << a.front() << endl;
		a.pop();
	}

	cout << endl;

	MyQueue<int> b;
	for (size_t i = 0; i < 10; i++)
		b.Push(i);
	for (size_t i = 0; i < 10; i++)
	{
		cout << b.Front() << endl;
		b.Pop();
	}
}

