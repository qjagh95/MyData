#include "pch.h"
#include "ModifyScene.h"
#include "Logic.h"
#include "PersonInfo.h"
#include "DataManager.h"

ModifyScene::ModifyScene()
{
}


ModifyScene::~ModifyScene()
{
}

void ModifyScene::Run()
{
	wstring Input;
	vector<PersonInfo*>* getVec = nullptr;

	while (true)
	{
		wcout << L"수정할 데이터의 초성, 이름검색 중 하나를 선택 해주세요" << endl;
		wcout << L"1.초성검색 2.이름검색 3.나가기 : ";
		getline(wcin, Input);
		cout << endl;

		while (GetIsNumber(Input) == false)
		{
			wcout << L"숫자를 입력해주세요 : ";
			getline(wcin, Input);
			cout << endl;
		}

		int getNumber = stoi(Input);

		if (getNumber == 3)
		{
			Logic::Get()->ChangeScene(SI_MENU);
			break;
		}

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
				wcout << i + 1 << L"." << endl;
				wcout << L"이름 : " << getVec->at(i)->GetName() << endl;
				wcout << L"주소 : " << getVec->at(i)->GetAddress() << endl;
				wcout << L"핸드폰 : " << getVec->at(i)->GetPhoneName() << endl << endl;
			}

			int Index = 0;
			wcout << L"몇번째 데이터를 수정하시겠습니까? ";
			wcin >> Index;

			while (Index - 1 > getVec->size() || Index - 1 < 0)
			{
				wcout << L"다시 입력해주세요 : ";
				wcin >> Index;
			}

			Index -= 1;

			int Select = 0;
			bool isCheck = false;

			while (isCheck == false)
			{
				wcout << L"어떤 데이터를 수정하시겠습니까? (1.이름 2.주소 3.핸드폰 4.안한다) : ";
				wcin >> Select;

				while (Select != 1 && Select != 2 && Select != 3 && Select != 4)
				{
					wcout << L"다시 입력해주세요 : ";
					wcin >> Select;
				}

				wstring InputString;
				getline(wcin, InputString);

				switch (Select)
				{
				case 1:
				{
					wcout << L"이름 : ";
					getline(wcin, InputString);
					getVec->at(Index)->SetName(InputString);
				}
				break;
				case 2:
				{
					wcout << L"주소 : ";
					getline(wcin, InputString);
					getVec->at(Index)->SetAddress(InputString);
				}
				break;
				case 3:
				{
					wcout << L"핸드폰 : ";
					getline(wcin, InputString);
					getVec->at(Index)->SetPhoneNumber(InputString);
				}
				break;
				case 4:
					isCheck = true;
					break;
				}

				DataManager::Get()->Modifly();
			}
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
				wcout << i + 1 << L"." << endl;
				wcout << L"이름 : " << getVector->at(i)->GetName() << endl;
				wcout << L"주소 : " << getVector->at(i)->GetAddress() << endl;
				wcout << L"핸드폰 : " << getVector->at(i)->GetPhoneName() << endl << endl;
			}

			int Select = 0;
			bool isCheck = false;

			if (getVector->size() == 0 || getVector == nullptr)
			{
				wcout << L"해당 이름의 데이터가 없습니다." << endl;
				continue;
			}

			int Index = 0;
			wcout << L"몇번째 데이터를 수정하시겠습니까? ";
			wcin >> Index;

			while (Index - 1 > getVector->size() || Index - 1 < 0)
			{
				wcout << L"다시 입력해주세요";
				wcin >> Index;
			}

			Index -= 1;

			while (isCheck == false)
			{
				wcout << L"어떤 데이터를 수정하시겠습니까? (1.이름 2.주소 3.핸드폰 4.안한다) : ";
				wcin >> Select;

				while (Select != 1 && Select != 2 && Select != 3 && Select != 4)
				{
					wcout << L"다시 입력해주세요 : ";
					wcin >> Select;
				}

				PersonInfo* getInfo = getVector->at(Index);
				wstring InputString;
				getline(wcin, InputString);

				switch (Select)
				{
				case 1:
				{
					wcout << L"이름 : ";
					getline(wcin, InputString);
					getInfo->SetName(InputString);
				}
				break;
				case 2:
				{
					wcout << L"주소 : ";
					getline(wcin, InputString);
					getInfo->SetAddress(InputString);
				}
				break;
				case 3:
				{
					wcout << L"핸드폰 : ";
					getline(wcin, InputString);
					getInfo->SetPhoneNumber(InputString);
				}
				break;
				case 4:
					isCheck = true;
					break;
				}
			}
			DataManager::Get()->Modifly();
		}

		wcout << L"종료 하시겠습니까? (BackSpace) 아니면 아무키나 눌러주세요" << endl << endl;

		if (_getch() == VK_BACK)
		{
			Logic::Get()->ChangeScene(SI_MENU);
			break;
		}
		else
			continue;
	}
}
