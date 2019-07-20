#include "pch.h"
#include "DeleteScene.h"
#include "DataManager.h"
#include "Logic.h"
#include "PersonInfo.h"


DeleteScene::DeleteScene()
{
}


DeleteScene::~DeleteScene()
{
}

void DeleteScene::Run()
{
	if (DataManager::Get()->GetMap()->empty() == true)
	{
		wcout << L"데이터가 없습니다. 메뉴로 돌아갑니다.";
		Sleep(500);
		Logic::Get()->ChangeScene(SI_MENU);
		return;
	}

	wstring Input;
	vector<PersonInfo*>* getVec = nullptr;

	while (true)
	{
		cout << endl;
		wcout << L"삭제할 이름을 입력해주세요 : ";
		getline(wcin, Input);
		cout << endl;

		getVec = DataManager::Get()->GetSameName(Input);
		if (getVec == nullptr)
		{
			wcout << L"해당 이름의 데이터가 없습니다. 아무키나 입력해주세요 나가기(Q) : ";

			int Key = _getch();
			if (Key == 'Q' || Key == 'q' || Key == 'ㅂ' || Key == 'ㅃ')
			{
				Logic::Get()->ChangeScene(SI_MENU);
				return;
			}
			else
				continue;
		}
		else
			break;
	}

	while(true)
	{
		for (size_t i = 0; i < getVec->size(); i++)
		{
			wcout << i + 1 << ".";
			wcout << L"이름 : " << getVec->at(i)->GetName() << endl;
			wcout << L"주소 : " << getVec->at(i)->GetAddress() << endl;
			wcout << L"핸드폰 : " << getVec->at(i)->GetPhoneName() << endl << endl;
		}

		wstring InputIndex;

		wcout << L"몇 번째 데이터를 삭제하시겠습니까? 보이는데이터 전체삭제(A) 나가기(Q) : ";
		wcin >> InputIndex;
		cout << endl;

		if (InputIndex == L"Q" || InputIndex == L"q" || InputIndex == L"ㅂ" || InputIndex == L"ㅃ")
		{
			Logic::Get()->ChangeScene(SI_MENU);
			break;
		}
		if (InputIndex == L"A" || InputIndex == L"a" || InputIndex == L"ㅁ")
		{
			wcout << L"보이는 전체 데이터를 삭제했습니다. 아무키나 눌러주세요" << endl << endl;
			DataManager::Get()->DeleteMapVector(Input);
			_getch();
			return;
		}

		while (GetIsNumber(InputIndex) == false)
		{
			wcout << L"숫자만 입력하세요 : ";
			wcin >> InputIndex;
		}

		int Convert = stoi(InputIndex);

		if (Convert == VK_BACK)
		{
			Logic::Get()->ChangeScene(SI_MENU);
			break;
		}

		while (Convert - 1 >= getVec->size() || Convert - 1 < 0)
		{
			wcout << L"인덱스를 다시 입력하세요 나가기(Q) : ";
			wcin >> InputIndex;

			if (InputIndex == L"Q" || InputIndex == L"q")
			{
				Logic::Get()->ChangeScene(SI_MENU);
				break;
			}

			while (GetIsNumber(InputIndex) == false)
			{
				wcout << L"숫자만 입력하세요 : ";
				wcin >> InputIndex;
			}

			Convert = stoi(InputIndex);
		}

		DataManager::Get()->DeleteData(getVec->at(Convert - 1)->GetName(), Convert - 1);
		wcout << L"데이터를 삭제했습니다. " << endl << endl;

		if (getVec->size() == 0)
		{
			wcout << L"삭제할 데이터가 없습니다. 메뉴로 돌아갑니다";
			Logic::Get()->ChangeScene(SI_MENU);
			break;
		}
		 
		wcout << L"종료 하시겠습니까? (BackSpace) 아니면 아무키나 눌러주세요" << endl << endl;
		if (_getch() == VK_BACK)
		{
			Logic::Get()->ChangeScene(SI_MENU);
			break;
		}
	}
}
