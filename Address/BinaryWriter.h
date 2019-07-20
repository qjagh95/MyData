#pragma once

class BinaryWrite
{
public:
	void WriteData(const bool& Data);
	void WriteData(const int& Data);
	void WriteData(const float& Data);
	void WriteData(const double& Data);
	void WriteData(const size_t& Data);
	void WriteData(const std::string& _Data, int _iSize);
	void WriteData(const wstring& Data);
	void WriteData(const char* Data);
	void WriteData(const wchar_t* Data);
private:
	ofstream m_WriteFile;

public:
	BinaryWrite(const wchar_t* FullPath);
	BinaryWrite(const char* FullPath);
	~BinaryWrite();
};

