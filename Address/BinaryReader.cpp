#include "pch.h"
#include "BinaryReader.h"

BinaryRead::BinaryRead(const wchar_t * FullPath)
{
	m_ReadFile.open(FullPath, ios::binary);
}

BinaryRead::BinaryRead(const char * FullPath)
{
	m_ReadFile.open(FullPath, ios::binary);
}

BinaryRead::~BinaryRead()
{
	m_ReadFile.close();
}

bool BinaryRead::ReadBool()
{
	bool Return;

	m_ReadFile.read((char*)&Return, sizeof(bool));

	return Return;
}

int BinaryRead::ReadInt()
{
	int Temp = INT_MIN;

	m_ReadFile.read((char*)&Temp, sizeof(int));

	if (Temp == INT_MIN)
		return -1;

	return Temp;
}

float BinaryRead::ReadFloat()
{
	float Temp = (float)INT_MIN;

	m_ReadFile.read((char*)&Temp, sizeof(float));

	if (Temp == (float)INT_MIN)
		return -1.0f;

	return Temp;
}

double BinaryRead::ReadDouble()
{
	double Temp = (double)INT_MIN;

	m_ReadFile.read((char*)&Temp, sizeof(double));

	if (Temp == (double)INT_MIN)
		return -1;

	return Temp;
}

size_t BinaryRead::ReadSizeT()
{
	size_t Temp = INT_MAX;

	m_ReadFile.read((char*)&Temp, sizeof(size_t));

	if (Temp == INT_MAX)
		return -1;

	return Temp;
}


string BinaryRead::ReadString()
{
	char getString[255] = {};
	size_t Datalen;

	m_ReadFile.read((char*)&Datalen, sizeof(size_t));
	m_ReadFile.read(getString, Datalen);

	return string(getString);
}

wstring BinaryRead::ReadWString()
{
	char getString[255];
	size_t Datalen;

	m_ReadFile.read((char*)&Datalen, sizeof(size_t));
	m_ReadFile.read(getString, Datalen);

	return wstring(CA2W(getString));
}

void BinaryRead::ReadData(bool & Data)
{
	m_ReadFile.read((char*)&Data, sizeof(bool));
}

void BinaryRead::ReadData(int & Data)
{
	m_ReadFile.read((char*)&Data, sizeof(int));
}

void BinaryRead::ReadData(float & Data)
{
	m_ReadFile.read((char*)&Data, sizeof(float));
}

void BinaryRead::ReadData(double & Data)
{
	m_ReadFile.read((char*)&Data, sizeof(double));
}

void BinaryRead::ReadData(size_t & Data)
{
	m_ReadFile.read((char*)&Data, sizeof(size_t));
}

void BinaryRead::ReadData(string & Data)
{
	size_t DataLen;
	char getData[255] = {};

	m_ReadFile.read((char*)&DataLen, sizeof(size_t));
	m_ReadFile.read(getData, DataLen);

	Data = getData;
}

void BinaryRead::ReadData(std::string & _Data, int _iSize)
{
	char getData[255] = {};

	m_ReadFile.read(getData, _iSize);

	_Data = getData;
}

void BinaryRead::ReadData(wstring & Data)
{
	size_t DataLen;
	char getData[255] = {};

	m_ReadFile.read((char*)&DataLen, sizeof(size_t));
	m_ReadFile.read(getData, DataLen);

	Data = CA2W(getData);
}