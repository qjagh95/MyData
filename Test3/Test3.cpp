#include "pch.h"
#include <iostream>
#include <vector>
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
	AA() { 	cout << "AA" << endl; }
	~AA() { cout << "~AA" << endl; }

	void Test() {}
	void FuncA() { cout << "FAA" << endl; }
};

class BB : public AA
{
public:
	BB() { cout << "BB" << endl; }
	virtual ~BB() { cout << "~BB" << endl; }

	//AA에는 virtual이 없다.
	//AA* newA = new CC();
	//delete newA
	//의 결과는 터진다
	
	//virtual이 없기때문에 가상함수테이블이 생성되지 않았기때문에
	//nullptr을 가르키고있다.
	//즉 nullptr을 참조해서 지우기때문에 터진다.

	virtual void Test() {}
	void FuncB() { cout << "FBB" << endl; }
};

class CC : public BB
{
public:
	CC() { cout << "CC" << endl; }
	~CC() { cout << "~CC" << endl;}
};

int main()
{
	int a = sizeof(A);
	int b = sizeof(B);
	int c = sizeof(C);

	//AA* newA = new CC();
	//newA->Func();

	//A의 함수호출 
	//A형태로 static_cast된 상태
	//A의 Func와 나머지의 Func는 다른함수다.

	//AA* newA = new BB();
	//BB* convert = reinterpret_cast<BB*>(newA);

	//convert->FuncB();

	AA* newA = static_cast<AA*>(new CC);

	delete newA;
}

