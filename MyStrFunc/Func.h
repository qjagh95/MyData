#pragma once
#include <iostream>

int MyStrlen(const char* Src)
{
	int Size = 0;

	while (Src[Size] != NULL)
		Size++;

	return Size;
} 

void MyStrcpy(char* Dest, const char* Src)
{
	int Size = 0;

	while (Src[Size] != NULL)
	{
		Dest[Size] = Src[Size];
		Size++;
	}

	Dest[Size] = NULL;
}

void MyStrcat(char* Src, const char* Dest)
{
	int srcSize = MyStrlen(Src);
	int destSize = 0;

	while (Dest[destSize] != 0)
	{
		Src[srcSize++] = Dest[destSize++];
	}
}

int MyStrcmp(const char* Src, const char* Dest)
{
	int Size = 0;

	while (Src[Size] != NULL && Dest[Size] != NULL)
	{
		if (Src[Size] > Dest[Size])
			return 1;
		else if (Src[Size] < Dest[Size])
			return -1;

		Size++;
	}
	return 0;
}

void MyMemcpy(void* pSrc, void* pDest, size_t CopySize)
{
	char* Src = (char*)pSrc;
	char* Dest = (char*)pDest;

	for (size_t i = 0; i < CopySize; i++)
		Src[i] = Dest[i];
}

void MyMemset(void* pSrc, int Value, size_t SettingSize)
{
	char* Src = (char*)pSrc;

	for (size_t i = 0; i < SettingSize; i++)
		Src[i] = Value;

}