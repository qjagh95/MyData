#include "pch.h"
#include <iostream>
#include "BineryTree.h"
using namespace std;

int main()
{
	BineryTree<int, int> a;
	
	a.Insert(20, 1);
	a.Insert(23, 1);
	a.Insert(19, 1);
	a.Insert(15, 1);
	a.Insert(1, 1);
	a.Insert(26, 1);

	a.InOrder();
}
