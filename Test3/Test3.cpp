#include "pch.h"
#include <iostream>
using namespace std;

//BytePadding
class A
{
	//int a;    //4
	//double b; //8
	//int c[12]; //48
	//char b[255]; //255

	virtual void Print() {};
};

class B 
{
	virtual void Print() {}
};

class C
{

};

class AA
{
public:
	AA() 
	{
		cout << "AA" << endl;
	}

	void Func() { cout << "AA" << endl; }
};

class BB : public AA
{
public:
	BB() 
	{
		cout << "BB" << endl;
	}

	virtual void Func() { cout << "BB" << endl; }
};

class CC : public BB
{
public:
	CC() 
	{
		cout << "CC" << endl;
	}

	void Func() override { cout << "CC" << endl; }
};

int main()
{
	int a = sizeof(A);
	int b = sizeof(B);
	int c = sizeof(C);

	AA* newA = new CC();
	newA->Func();

	//A의 함수호출 
	//A형태로 static_cast된 상태
	//A의 Func와 나머지의 Func는 다른함수다.
}

