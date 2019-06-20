#include "pch.h"
#include <iostream>
using namespace std;

class A
{
public:
	A() { cout << "A" << endl; }
	virtual ~A() { cout << "~A" << endl; }

	//함수뒤에 const가 붙으면 this에 const가 붙기때문에 멤버변수 조작 불가
	void AAA() const
	{
		cout << "AAA()" << endl; 
		//this->a1 = 123;
		//this->a2 = 123;
		//this->a3 = 123;

	}

	void B()
	{
		cout << "B()" << endl;
		a1 = 0;

	}

	virtual void Attack()
	{
		cout << "A - Attack" << endl;
	}

	int a1 = 0;
	int a2 = 1;
	int a3 = 2;

};

class B : public A
{
public:
	B() { cout << "B" << endl; }
	virtual ~B() { cout << "~B" << endl; }

	void Attack() override
	{
		cout << "B - Attack" << endl;
	}
};

class Middle : public A
{
public:
	Middle() { cout << "Middle" << endl; }
	virtual ~Middle() { cout << "~Middle" << endl; }

	void Attack() override
	{
		cout << "Middle - Attack" << endl;
	}
};

class C : public B
{
public:
	C() { cout << "C" << endl; }
	virtual ~C() { cout << "~C" << endl; }
};


void CCC()
{
	//static변수는 함수가 처음 호출되는 시점에 초기화
	static A asd;
	cout << "CCC()" << endl;
}

int main()
{
	CCC();
	
	A newA;
	newA.AAA();
	newA.B();

	//int const* a = new int();
	//int* const b = new int();

	//a = b;
	//*b = 10;
	//*a = 10;

	B* newB1 = new B();
	newB1->Attack();
	Middle* newB2 = (Middle*)newB1;
	newB2->Attack();

	delete newB1;
	delete newB2;

}

