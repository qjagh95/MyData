#include "pch.h"
#include <iostream>
#include "MyList.h"

using namespace std;

int main()
{
	MyList<int> a;

	for (size_t i = 0; i < 10; i++)
		a.Push_Back(i);

	MyList<int>::Iterator StartIter = a.Begin();
	MyList<int>::Iterator EndIter = a.End();

	for (; StartIter != EndIter; StartIter++)
	{
		cout << (*StartIter) << endl;
	}
}
