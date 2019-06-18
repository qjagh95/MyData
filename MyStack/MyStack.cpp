#include "pch.h"
#include <iostream>
#include <stack>
#include "MyStack.h"

using namespace std;

int main()
{
	stack<int> a;
	for (size_t i = 0; i < 10; i++)
		a.push(i);
	for (size_t i = 0; i < 10; i++)
	{
		cout << a.top() << endl;
		a.pop();
	}

	cout << endl;

	MyStack<int> b;

	for (size_t i = 0; i < 10; i++)
		b.Push(i);

	for (size_t i = 0; i < 10; i++)
	{
		cout << b.Top() << endl;
		b.Pop();
	}
}

