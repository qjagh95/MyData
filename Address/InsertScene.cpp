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

	wcout << L"�� ���� �߰� �Ͻðڽ��ϱ�? ";
	wcin >> Count;

	while (GetIsNumber(Count) == false)
	{
		wcout << L"������ �Է����ּ���(-�� ����) : ";
		wcin >> Count;
	}

	Convert = stoi(Count);

	while (Convert >= 1000)
	{
		wcout << L"1000 �̻��� ��... : ";
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
		wcout << L"�̸� : ";
		getline(wcin, Name);

		cout << i + 1 << ".";
		wcout << L"�ּ� : ";
		getline(wcin, Address);

		cout << i + 1 << ".";
		wcout << L"�ڵ��� ��ȣ : ";
		getline(wcin, Phone);
		cout << endl;

		DataManager::Get()->AddData(Name, Address, Phone);
		DataManager::Get()->Save();

		if (i + 1 < Convert)
		{
			wcout << L"���� �Ͻðڽ��ϱ�? (BackSpace) �ƴϸ� �ƹ�Ű�� �����ּ���" << endl << endl;

			if (_getch() == VK_BACK)
			break;
		}
	}
	wcout << L"�޴��� ���ư��ϴ�...";
	Sleep(1500);
	Logic::Get()->ChangeScene(SI_MENU);
}