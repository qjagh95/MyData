#pragma once

class BinaryWrite;
class BinaryRead;
class PersonInfo
{
public:
	PersonInfo();
	~PersonInfo();

	void SetName(const wstring& Name);
	void SetAddress(const wstring& Address);
	void SetPhoneNumber(const wstring& PhoneNumber);
	void SetData(const wstring& Name, const wstring& Address, const wstring& PhoneNumber);
	wstring GetName() const { return m_Name; }
	wstring GetPhoneName() const { return m_PhoneNumber; }
	wstring GetAddress() const { return m_Address; }

	void Save(BinaryWrite& WriteFile);
	void SaveText(wofstream& WriteFile);
	void Load(BinaryRead& ReadFile);

private:
	wstring m_Name;
	wstring m_PhoneNumber;
	wstring m_Address;
};

