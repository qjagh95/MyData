#include "pch.h"
#include "AllViewScene.h"
#include "DataManager.h"
#include "PersonInfo.h"
#include "Logic.h"

AllViewScene::AllViewScene()
{
}

AllViewScene::~AllViewScene()
{
}

void AllViewScene::Run()
{
	if (DataManager::Get()->GetMap()->empty() == true)
	{
		wcout << L"주소록이 비어있습니다. 메뉴로 돌아갑니다.";
		Sleep(1000);
		Logic::Get()->ChangeScene(SI_MENU);
		return;
	}

	auto StartIter = DataManager::Get()->GetMap()->begin();
	auto EndIter = DataManager::Get()->GetMap()->end();

	for (; StartIter != EndIter; StartIter++)
	{
		wcout << StartIter->first << L"." << endl;

		for (size_t i = 0; i < StartIter->second.size(); i++)
		{
			wcout << L"이름 : " << StartIter->second[i]->GetName() << " " << endl;
			wcout << L"주소 : " << StartIter->second[i]->GetAddress() << " " << endl;
			wcout << L"핸드폰 : " << StartIter->second[i]->GetPhoneName() << endl << endl;
		}
		cout << endl;
	}

	wcout << L"메뉴로 돌아가기 : BackSpace" << endl;

Back:
	int Key = _getch();

	if (Key == VK_BACK)
		Logic::Get()->ChangeScene(SI_MENU);
	else
		goto Back; 

	//어쩔수없이 goto문 사용..
}
