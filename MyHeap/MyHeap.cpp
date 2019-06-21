#include "pch.h"
#include <iostream>
#include "MyHeap.h"
#include <queue>
#include <vector>

using namespace std;

int main()
{
	priority_queue<int> a;
	a.push(3);
	a.push(2);
	a.push(4);
	a.push(1);
	a.push(5);

	MyHeap<int> b;

	b.Insert(3);
	b.Insert(2);
	b.Insert(4);
	b.Insert(1);
	b.Insert(5);

}

