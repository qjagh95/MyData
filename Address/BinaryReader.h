#pragma once

class BinaryRead
{
public:
	bool ReadBool();
	int ReadInt();
	float ReadFloat();
	double ReadDouble();
	size_t ReadSizeT();
	string ReadString();
	wstring ReadWString();

	void ReadData(bool& Data);
	void ReadData(int& Data);
	void ReadData(float& Data);
	void ReadData(double& Data);
	void ReadData(size_t& Data);
	void ReadData(string& Data);
	void ReadData(std::string& _Data, int _iSize);
	void ReadData(wstring& Data);

private:
	ifstream m_ReadFile;

public:
	BinaryRead(const wchar_t* FullPath);
	BinaryRead(const char* FullPath);
	~BinaryRead();
};

