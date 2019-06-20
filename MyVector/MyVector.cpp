#include "pch.h"
#include <iostream>
#include <list>
#include "MyVector.h"
using namespace std;

int main()
{
	MyVector<int> a;

	cout << "Push_Back" << endl;
	for (int i = 0; i < 10; i++)
		a.Push_Back(i);

	for (int i = 0; i < 10; i++)
		cout << a[i] << endl;

	cout << "Front_Back" << endl << endl;
	a.Front_Back(123);

	for (int i = 0; i < 10; i++)
		cout << a[i] << endl;
	
	a.Erase(0);

	cout << "Erase" << endl << endl;

	for (size_t i = 0; i < 10; i++)
		cout << a[i] << endl;

	cout << "Insert" << endl << endl;

	a.Insert(4, 46564);

	for (size_t i = 0; i < 10; i++)
		cout << a[i] << endl;
}
