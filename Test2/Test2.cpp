#include "pch.h"
#include <iostream>
using namespace std;

class A
{
public:
	void Print() { cout << "A 프린트" << endl; }
};

class AA
{
public:
	virtual void Print() { cout << "AA" << endl; }
	AA() { Print(); }

};
class BB : public AA
{
public:
	void Print() override { cout << "BB" << endl; }
	BB() { Print(); }

};
class CC : public BB
{
public:
	void Print() override { cout << "CC" << endl; }
	CC() { Print(); }
};

int main()
{
	//A* newA = nullptr;
	//실행됨(this콜 함수내에서 참조하는 변수가 없기때문에 실행가능)
	//newA->Print(); 

	AA* newAA = new CC();
	//함수 뒤 this가 붙기때문에 AA BB CC CC실행

	newAA->Print();

	AA* getAA = dynamic_cast<CC*>(newAA);

	CC* newCC = new CC();

	AA* getCC = dynamic_cast<AA*>(newCC);

	delete newAA;
}