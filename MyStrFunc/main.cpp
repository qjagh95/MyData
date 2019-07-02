#include <iostream>
#include "Func.h"

using namespace std;

void main()
{
	char* myStr = "asdb";
	char myStr2[100];

	int a = MyStrlen(myStr);

	MyStrcpy(myStr2, myStr);
	myStr2;

	char* a1 = "asda";
	char* a2 = "asdb";
	int b = MyStrcmp(a1, a2);

	char a3[10] = "abcd";
	MyStrcat(a3, "efg");

	int *ca = new int();
	int cb = 3;

	MyMemcpy(ca, &cb, sizeof(int));

	float fa[4];
	MyMemset(fa, 0, sizeof(float) * 4);

	//memcpy로 연결하기
	char* Src = "Hello";
	char* Dest = "World";

	int Size1 = MyStrlen(Src);
	int Size2 = MyStrlen(Dest);

	char Result[255] = {};
	char* newChar = new char[Size1 + Size2];
	MyMemset(newChar, 0, Size1 + Size2);
	
	MyMemcpy(newChar, Src, Size1);
	MyMemcpy(newChar + Size1, Dest, Size2);

	char* Src1 = "Hello";
	char* Compair = "l";

	const char* get = MyStrstr(Src1, Compair);
}