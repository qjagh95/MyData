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
		wcout << L"�ּҷ��� ����ֽ��ϴ�. �޴��� ���ư��ϴ�.";
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
			wcout << L"�̸� : " << StartIter->second[i]->GetName() << " " << endl;
			wcout << L"�ּ� : " << StartIter->second[i]->GetAddress() << " " << endl;
			wcout << L"�ڵ��� : " << StartIter->second[i]->GetPhoneName() << endl << endl;
		}
		cout << endl;
	}

	wcout << L"�޴��� ���ư��� : BackSpace" << endl;

Back:
	int Key = _getch();

	if (Key == VK_BACK)
		Logic::Get()->ChangeScene(SI_MENU);
	else
		goto Back; 

	//��¿������ goto�� ���..
}
