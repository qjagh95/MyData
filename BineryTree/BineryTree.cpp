#include "pch.h"
#include <iostream>
#include "BineryTree.h"
using namespace std;

int main()
{
	BineryTree<int, int> a;
	
	a.Insert(10, 1);
	a.Insert(6, 1);
	a.Insert(11, 1);
	a.Insert(4, 1);
	a.Insert(7, 1);
	a.Insert(3, 1);
	a.Insert(5, 1);
	a.Insert(8, 1);
	a.Insert(13, 1);
	a.Insert(17, 1);


	a.InOrder();
}
