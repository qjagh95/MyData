#include "pch.h"
#include "PersonInfo.h"
#include "BinaryReader.h"
#include "BinaryWriter.h"

PersonInfo::PersonInfo()
{
	m_Name = L"None_Name";
	m_PhoneNumber = L"None_Phone";
}

PersonInfo::~PersonInfo()
{
}

void PersonInfo::SetName(const wstring & Name)
{
	m_Name = Name;
}

void PersonInfo::SetAddress(const wstring & Address)
{
	m_Address = Address;
}

void PersonInfo::SetPhoneNumber(const wstring & PhoneNumber)
{
	m_PhoneNumber = PhoneNumber;
}

void PersonInfo::SetData(const wstring & Name, const wstring& Address, const wstring & PhoneNumber)
{
	m_Name = Name;
	m_PhoneNumber = PhoneNumber;
	m_Address = Address;
}

void PersonInfo::Save(BinaryWrite & WriteFile)
{
	const char* Buffer = CW2A(m_Name.c_str());
	WriteFile.WriteData(Buffer);

	Buffer = CW2A(m_PhoneNumber.c_str());
	WriteFile.WriteData(Buffer);

	Buffer = CW2A(m_Address.c_str());
	WriteFile.WriteData(Buffer);
}

void PersonInfo::SaveText(wofstream & WriteFile)
{
	WriteFile << L"이름 : " << m_Name << endl;
	WriteFile << L"주소 : " << m_Address << endl;
	WriteFile << L"핸드폰 : " << m_PhoneNumber << endl << endl;
}

void PersonInfo::Load(BinaryRead & ReadFile)
{
	string getData = ReadFile.ReadString();
	m_Name = CA2W(getData.c_str());

	getData = ReadFile.ReadString();
	m_PhoneNumber = CA2W(getData.c_str());

	getData = ReadFile.ReadString();
	m_Address = CA2W(getData.c_str());
}
