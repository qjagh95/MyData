#include "pch.h"
#include "BinaryWriter.h"

BinaryWrite::BinaryWrite(const wchar_t * FullPath)
{
	m_WriteFile.open(FullPath, ios::binary);
}

BinaryWrite::BinaryWrite(const char * FullPath)
{
	m_WriteFile.open(FullPath, ios::binary);
}

BinaryWrite::~BinaryWrite()
{
	m_WriteFile.close();
}

void BinaryWrite::WriteData(const bool& Data)
{
	m_WriteFile.write((char*)&Data, sizeof(bool));
}

void BinaryWrite::WriteData(const int& Data)
{
	m_WriteFile.write((char*)&Data, sizeof(int));
}

void BinaryWrite::WriteData(const float& Data)
{
	m_WriteFile.write((char*)&Data, sizeof(float));
}

void BinaryWrite::WriteData(const double& Data)
{
	m_WriteFile.write((char*)&Data, sizeof(double));
}

void BinaryWrite::WriteData(const size_t & Data)
{
	m_WriteFile.write((char*)&Data, sizeof(size_t));
}

void BinaryWrite::WriteData(const string & _Data, int _iSize)
{
	m_WriteFile.write(_Data.c_str(), _iSize);
}

void BinaryWrite::WriteData(const wstring & Data)
{
	wstring Temp = Data.c_str();
	size_t Datalen = Data.length();

	m_WriteFile.write((char*)&Datalen, sizeof(size_t));
	m_WriteFile.write(CW2A(Temp.c_str()), Datalen);
}

void BinaryWrite::WriteData(const char * Data)
{
	string Temp = Data;
	size_t Datalen = Temp.length();

	m_WriteFile.write((char*)&Datalen, sizeof(size_t));
	m_WriteFile.write(Data, Datalen);
}

void BinaryWrite::WriteData(const wchar_t * Data)
{
	wstring Temp = Data;
	size_t Datalen = Temp.length();

	m_WriteFile.write((char*)&Datalen, sizeof(size_t));
	m_WriteFile.write(CW2A(Temp.c_str()), Datalen);
}
