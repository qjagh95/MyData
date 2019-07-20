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
		wcout << L"�����Ͱ� �����ϴ�. �޴��� ���ư��ϴ�.";
		Sleep(500);
		Logic::Get()->ChangeScene(SI_MENU);
		return;
	}

	wstring Input;
	vector<PersonInfo*>* getVec = nullptr;

	while (true)
	{
		cout << endl;
		wcout << L"������ �̸��� �Է����ּ��� : ";
		getline(wcin, Input);
		cout << endl;

		getVec = DataManager::Get()->GetSameName(Input);
		if (getVec == nullptr)
		{
			wcout << L"�ش� �̸��� �����Ͱ� �����ϴ�. �ƹ�Ű�� �Է����ּ��� ������(Q) : ";

			int Key = _getch();
			if (Key == 'Q' || Key == 'q' || Key == '��' || Key == '��')
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
			wcout << L"�̸� : " << getVec->at(i)->GetName() << endl;
			wcout << L"�ּ� : " << getVec->at(i)->GetAddress() << endl;
			wcout << L"�ڵ��� : " << getVec->at(i)->GetPhoneName() << endl << endl;
		}

		wstring InputIndex;

		wcout << L"�� ��° �����͸� �����Ͻðڽ��ϱ�? ���̴µ����� ��ü����(A) ������(Q) : ";
		wcin >> InputIndex;
		cout << endl;

		if (InputIndex == L"Q" || InputIndex == L"q" || InputIndex == L"��" || InputIndex == L"��")
		{
			Logic::Get()->ChangeScene(SI_MENU);
			break;
		}
		if (InputIndex == L"A" || InputIndex == L"a" || InputIndex == L"��")
		{
			wcout << L"���̴� ��ü �����͸� �����߽��ϴ�. �ƹ�Ű�� �����ּ���" << endl << endl;
			DataManager::Get()->DeleteMapVector(Input);
			_getch();
			return;
		}

		while (GetIsNumber(InputIndex) == false)
		{
			wcout << L"���ڸ� �Է��ϼ��� : ";
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
			wcout << L"�ε����� �ٽ� �Է��ϼ��� ������(Q) : ";
			wcin >> InputIndex;

			if (InputIndex == L"Q" || InputIndex == L"q")
			{
				Logic::Get()->ChangeScene(SI_MENU);
				break;
			}

			while (GetIsNumber(InputIndex) == false)
			{
				wcout << L"���ڸ� �Է��ϼ��� : ";
				wcin >> InputIndex;
			}

			Convert = stoi(InputIndex);
		}

		DataManager::Get()->DeleteData(getVec->at(Convert - 1)->GetName(), Convert - 1);
		wcout << L"�����͸� �����߽��ϴ�. " << endl << endl;

		if (getVec->size() == 0)
		{
			wcout << L"������ �����Ͱ� �����ϴ�. �޴��� ���ư��ϴ�";
			Logic::Get()->ChangeScene(SI_MENU);
			break;
		}
		 
		wcout << L"���� �Ͻðڽ��ϱ�? (BackSpace) �ƴϸ� �ƹ�Ű�� �����ּ���" << endl << endl;
		if (_getch() == VK_BACK)
		{
			Logic::Get()->ChangeScene(SI_MENU);
			break;
		}
	}
}
