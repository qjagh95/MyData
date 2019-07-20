#include "pch.h"
#include "InsertScene.h"
#include "DataManager.h"
#include "Logic.h"

InsertScene::InsertScene()
{
}


InsertScene::~InsertScene()
{
}

void InsertScene::Run()
{
	wstring Count;
	size_t Convert = 0;
	bool isCheck = false;

	wcout << L"몇 명을 추가 하시겠습니까? ";
	wcin >> Count;

	while (GetIsNumber(Count) == false)
	{
		wcout << L"정상값을 입력해주세요(-값 제외) : ";
		wcin >> Count;
	}

	Convert = stoi(Count);

	while (Convert >= 1000)
	{
		wcout << L"1000 이상은 좀... : ";
		wcin >> Count;

		Convert = stoi(Count);
	}

	cout << endl;

	getline(wcin, Count);

	for (size_t i = 0; i < Convert; i++)
	{
		wstring Name = {};
		wstring Phone = {};
		wstring Address = {};

		cout << i + 1 << ".";
		wcout << L"이름 : ";
		getline(wcin, Name);

		cout << i + 1 << ".";
		wcout << L"주소 : ";
		getline(wcin, Address);

		cout << i + 1 << ".";
		wcout << L"핸드폰 번호 : ";
		getline(wcin, Phone);
		cout << endl;

		DataManager::Get()->AddData(Name, Address, Phone);
		DataManager::Get()->Save();

		if (i + 1 < Convert)
		{
			wcout << L"종료 하시겠습니까? (BackSpace) 아니면 아무키나 눌러주세요" << endl << endl;

			if (_getch() == VK_BACK)
			break;
		}
	}
	wcout << L"메뉴로 돌아갑니다...";
	Sleep(1500);
	Logic::Get()->ChangeScene(SI_MENU);
}