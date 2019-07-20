#include "pch.h"
#include "SerchScene.h"
#include "PersonInfo.h"
#include "DataManager.h"
#include "Logic.h"

SerchScene::SerchScene()
{
}

SerchScene::~SerchScene()
{
}

void SerchScene::Run()
{
	wstring Input;
	vector<PersonInfo*>* getVec = nullptr;

	while (true)
	{
		wcout << L"1.초성검색 2.이름검색 // 번호를 선택해주세요 : ";
		getline(wcin, Input);
		cout << endl;

		while (GetIsNumber(Input) == false)
		{
			wcout << L"숫자만 입력해주세요 1.초성검색 2.이름검색 : ";
			getline(wcin, Input);
			cout << endl;
		}

		int getNumber = stoi(Input);
		
		while (getNumber > 2)
		{
			wcout << L"정상적인 값을 입력 해주세요 : ";
			getline(wcin, Input);
			cout << endl;

			if (GetIsNumber(Input) == false)
				continue;

			getNumber = stoi(Input);
		}

		if (getNumber == 1)
		{
			wcout << L"검색할 초성을 입력해주세요(ㄱ,ㄴ,ㄷ...) : ";
			getline(wcin, Input);
			cout << endl;

			while (Input.size() > 1)
			{
				wcout << L"한 글자만 입력해주세요 : ";
				getline(wcin, Input);
				cout << endl;
			}

			getVec = DataManager::Get()->FindData(Input);
			if (getVec == nullptr)
			{
				wcout << L"해당 초성의 데이터가 없습니다.";
				cout << endl;
				continue;
			}

			wcout << Input << L"(으)로 검색한 데이터" << endl;

			for (size_t i = 0; i < getVec->size(); i++)
			{
				wcout << L"이름 : " << getVec->at(i)->GetName() << endl;
				wcout << L"주소 : " << getVec->at(i)->GetAddress() << endl;
				wcout << L"핸드폰 : " << getVec->at(i)->GetPhoneName() << endl << endl;
			}

			wcout << L"뒤로 돌아가기 : BackSpace. 아무키나 누르세요.";
			cout << endl;

			if (_getch() == VK_BACK)
			{
				Logic::Get()->ChangeScene(SI_MENU);
				break;
			}
			else
				continue;
		}
		else
		{
			wcout << L"검색할 이름을 입력해주세요 : ";
			getline(wcin, Input);
			cout << endl;

			vector<PersonInfo*>* getVector = DataManager::Get()->GetSameName(Input);

			if (getVector == nullptr)
			{
				wcout << L"해당 이름의 데이터가 없습니다.";
				continue;
			}

			for (size_t i = 0; i < getVector->size(); i++)
			{
				PersonInfo* getInfo = getVector->at(i);

				wcout << L"이름 : " << getInfo->GetName() << endl;
				wcout << L"주소 : " << getInfo->GetAddress() << endl;
				wcout << L"핸드폰 : " << getInfo->GetPhoneName() << endl << endl;
			}

			wcout << L"뒤로 돌아가기 : BackSpace. 아무키나 누르세요.";
			cout << endl;

			if (_getch() == VK_BACK)
			{
				Logic::Get()->ChangeScene(SI_MENU);
				break;
			}
			else
				continue;
		}
	}
}
