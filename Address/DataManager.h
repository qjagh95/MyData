#pragma once

class PersonInfo;
class DataManager
{
public:
	void AddData(const wstring& PersionName, const wstring& Address,const wstring& PhoneNumber);
	map<wstring, vector<PersonInfo*>>* GetMap() { return &m_PersionMap; }
	vector<PersonInfo*>* GetPersonData(const wstring& PersionName);
	vector<PersonInfo*>* GetSameName(const wstring& PersonName);
	wstring ConvertChoSung(const wstring& Text);
	bool DeleteData(const wstring& PersionName, int Index = 0);
	void DeleteMapVector(const wstring& PersonName);
	void DeleteAll();

	void Save(const wstring& FileName = L"SaveBinery.Jesu", const wstring& TextFileName = L"SaveData.txt");
	void Load(const wstring& FileName = L"SaveBinery.Jesu");

	void Modifly();
	vector<PersonInfo*>* FindData(const wstring& Vowel /*¸ðÀ½*/);

private:
	void DeleteKeyData();

public:
	static DataManager* Get();
	static void Delete();

private:
	static DataManager* m_Instance;
	map<wstring, vector<PersonInfo*>> m_PersionMap;
	wstring* m_Cho;

	wofstream m_WriteFile;
	vector<PersonInfo*> m_ReturnVec;

private:
	DataManager();
	~DataManager();
};

