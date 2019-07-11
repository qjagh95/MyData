#include "pch.h"
#include <iostream>
#include <memory>
using namespace std;

int main()
{
	//unique - 하나만 존재하는 포인터 
	//포인터이동시 move함수로 이동시켜야함.
	unique_ptr<int> a;



	weak_ptr<int> b;

	//일반적인 래퍼런스 카운트방식의 스마트포인터.
	//어떤객체가 참조시 카운트 + 1
	//소멸시 - 1
	shared_ptr<int> c;
}
