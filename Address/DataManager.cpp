#include "pch.h"
#include "DataManager.h"
#include "PersonInfo.h"
#include "Logic.h"
#include "BinaryReader.h"
#include "BinaryWriter.h"

DataManager* DataManager::m_Instance = nullptr;

DataManager::DataManager()
{
	m_Cho = new wstring[19];
	
	m_Cho[0] = L"ㄱ";
	m_Cho[1] = L"ㄲ";
	m_Cho[2] = L"ㄴ";
	m_Cho[3] = L"ㄷ";
	m_Cho[4] = L"ㄸ";
	m_Cho[5] = L"ㄹ";
	m_Cho[6] = L"ㅁ";
	m_Cho[7] = L"ㅂ";
	m_Cho[8] = L"ㅃ";
	m_Cho[9] = L"ㅅ";
	m_Cho[10] = L"ㅆ";
	m_Cho[11] = L"ㅇ";
	m_Cho[12] = L"ㅈ";
	m_Cho[13] = L"ㅉ";
	m_Cho[14] = L"ㅊ";
	m_Cho[15] = L"ㅋ";
	m_Cho[16] = L"ㅌ";
	m_Cho[17] = L"ㅍ";
	m_Cho[18] = L"ㅎ";

	vector<PersonInfo*> newVector;
	m_PersionMap.insert(make_pair(L"기타", newVector));
}

DataManager::~DataManager()
{
	delete[] m_Cho;

	auto StartIter = m_PersionMap.begin();
	auto EndIter = m_PersionMap.end();

	for (; StartIter != EndIter; StartIter++)
	{
		for (size_t i = 0; i < StartIter->second.size(); i++)
		{
			if (StartIter->second[i] != nullptr)
				delete StartIter->second[i];
		}
	}
}

DataManager * DataManager::Get()
{
	if (m_Instance == nullptr)
		m_Instance = new DataManager();

	return m_Instance;
}

void DataManager::Delete()
{
	delete m_Instance;
}

void DataManager::AddData(const wstring& PersonName, const wstring& Address, const wstring& PhoneNumber)
{
	PersonInfo* newInfo = new PersonInfo();
	newInfo->SetName(PersonName);
	newInfo->SetPhoneNumber(PhoneNumber);
	newInfo->SetAddress(Address);

	wstring Chosung = ConvertChoSung(PersonName);
	auto getVector = FindData(Chosung);

	if (getVector == nullptr)
	{
		if (Chosung == L"")
		{
			getVector = FindData(L"기타");
			getVector->push_back(newInfo);
			return;
		}

		vector<PersonInfo*> newVector;
		newVector.push_back(newInfo);
		m_PersionMap.insert(make_pair(Chosung, newVector));
		return;
	}

	getVector->push_back(newInfo);
}

vector<PersonInfo*>* DataManager::FindData(const wstring & Vowel)
{
	auto FindIter = m_PersionMap.find(Vowel);

	if (FindIter == m_PersionMap.end())
		return nullptr;

	return &FindIter->second;
}

vector<PersonInfo*>* DataManager::GetPersonData(const wstring & PersionName)
{
	wstring Chosung = ConvertChoSung(PersionName);
	auto getVector = FindData(Chosung);

	return getVector;
}

vector<PersonInfo*>* DataManager::GetSameName(const wstring & PersonName)
{
	vector<PersonInfo*>* TempVec;
	m_ReturnVec.clear();

	wstring getChosung = ConvertChoSung(PersonName);

	TempVec = FindData(getChosung);
	
	if (TempVec == nullptr)
		return nullptr;

	for (size_t i = 0; i < TempVec->size(); i++)
	{
		if (TempVec->at(i)->GetName() == PersonName)
			m_ReturnVec.push_back(TempVec->at(i));
	}

	if (m_ReturnVec.empty() == true)
		return nullptr;

	return &m_ReturnVec;
}

//초성변환 코드 (구글링코드)
wstring DataManager::ConvertChoSung(const wstring& Text)
{
	int chName = Text[0];

	if (chName >= 0xAC00)
	{
		int uniVal = chName - 0xAC00;
		int cho = ((uniVal - (uniVal % 28)) / 28) / 21;

		return m_Cho[cho];
	}

	return L"";
}

bool DataManager::DeleteData(const wstring & PersonName, int Index)
{
	vector<PersonInfo*>* getDeleteVec = GetSameName(PersonName);
	wstring Chosung = ConvertChoSung(PersonName);
	vector<PersonInfo*>* getMapVector = FindData(Chosung);

	if (getMapVector == nullptr)
		return false;

	for (size_t i = 0; i < getMapVector->size(); i++)
	{
		if (getMapVector->at(i)->GetName() == PersonName)
			getMapVector->erase(getMapVector->begin() + i);
	}

	if (getDeleteVec == nullptr)
		return false;

	PersonInfo* getInfo = getDeleteVec->at(Index);
	getDeleteVec->erase(getDeleteVec->begin() + Index);
	
	delete getInfo;

	if (getMapVector->empty() == true)
		m_PersionMap.erase(Chosung);

	Save();
	return true;
}

void DataManager::DeleteMapVector(const wstring & PersonName)
{
	wstring Chosong = ConvertChoSung(PersonName);
	auto getVector = FindData(Chosong);

	if (getVector == nullptr)
		return;

	for (size_t i = 0; i < getVector->size(); i++)
	{
		auto getInfo = getVector->at(i);

		if(getInfo != nullptr)
			delete getInfo;	
	}

	m_PersionMap.erase(Chosong);
	Save();
}

void DataManager::DeleteKeyData()
{
	auto StartIter = m_PersionMap.begin();
	auto EndIter = m_PersionMap.end();

	for (; StartIter != EndIter; )
	{
		if (StartIter->second.empty() == false)
			StartIter++;
		else
			m_PersionMap.erase(StartIter++);
	}
}

void DataManager::DeleteAll()
{
	if (m_PersionMap.empty() == true)
		return;

	auto StartIter = m_PersionMap.begin();
	auto EndIter = m_PersionMap.end();

	for (; StartIter != EndIter;)
	{
		for (size_t i = 0; i < StartIter->second.size(); i++)
		{
			PersonInfo* getInfo = StartIter->second[i];
			StartIter->second.erase(StartIter->second.begin() + i);
			delete getInfo;
		}

		m_PersionMap.erase(StartIter++);
	}

	Modifly();
}

void DataManager::Save(const wstring& FileName, const wstring& TextFileName)
{
	DeleteKeyData();

	wstring FilePath = Logic::Get()->GetDefaultPath();
	FilePath += L"SaveData\\";
	FilePath += FileName;

	BinaryWrite Writer(FilePath.c_str());

	size_t PersonSize = m_PersionMap.size();
	Writer.WriteData(PersonSize);

	auto StartIter = m_PersionMap.begin();
	auto EndIter = m_PersionMap.end();

	for (; StartIter != EndIter; StartIter++)
	{
		const char* Buffer = CW2A(StartIter->first.c_str());
		Writer.WriteData(Buffer);

		size_t VecSize = StartIter->second.size();
		Writer.WriteData(VecSize);

		for (size_t i = 0; i < StartIter->second.size(); i++)
			StartIter->second[i]->Save(Writer);
	}
}

void DataManager::Load(const wstring& FileName)
{
	wstring FilePath = Logic::Get()->GetDefaultPath();
	FilePath += L"SaveData\\";
	FilePath += FileName;

	BinaryRead Reader(FilePath.c_str());

	size_t getMapSize = 0;
	Reader.ReadData(getMapSize);

	for (size_t i = 0; i < getMapSize; i++)
	{
		string getChosung = Reader.ReadString();
		wstring Convert;
		Convert = CA2W(getChosung.c_str());

		size_t vectorSize = Reader.ReadSizeT();

		if (Convert == L"")
			continue;

		vector<PersonInfo*> newVector;
		newVector.reserve(vectorSize);

		for (size_t i = 0; i < vectorSize; i++)
		{
			PersonInfo* newInfo = new PersonInfo();
			newInfo->Load(Reader);
			newVector.push_back(newInfo);
		}
		m_PersionMap.insert(make_pair(Convert, newVector));
	}

	DeleteKeyData();
}

//수정될때 위치 재지정.
void DataManager::Modifly()
{
	auto StartIter1 = m_PersionMap.begin();
	auto EndIter1 = m_PersionMap.end();

	for (; StartIter1 != EndIter1; StartIter1++)
	{
		for (size_t i = 0; i < StartIter1->second.size(); i++)
		{
			PersonInfo* getInfo = StartIter1->second[i];
			wstring Chosung = ConvertChoSung(getInfo->GetName());

			if (Chosung != StartIter1->first)
			{
				StartIter1->second.erase(StartIter1->second.begin() + i);

				auto getVector = FindData(Chosung);

				if (getVector == nullptr)
				{
					vector<PersonInfo*> newVector;
					newVector.push_back(getInfo);

					m_PersionMap.insert(make_pair(Chosung, newVector));
				}
				else
					getVector->push_back(getInfo);
			}
		}
	}

	Save();
}
