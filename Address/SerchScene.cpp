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
		wcout << L"1.�ʼ��˻� 2.�̸��˻� // ��ȣ�� �������ּ��� : ";
		getline(wcin, Input);
		cout << endl;

		while (GetIsNumber(Input) == false)
		{
			wcout << L"���ڸ� �Է����ּ��� 1.�ʼ��˻� 2.�̸��˻� : ";
			getline(wcin, Input);
			cout << endl;
		}

		int getNumber = stoi(Input);
		
		while (getNumber > 2)
		{
			wcout << L"�������� ���� �Է� ���ּ��� : ";
			getline(wcin, Input);
			cout << endl;

			if (GetIsNumber(Input) == false)
				continue;

			getNumber = stoi(Input);
		}

		if (getNumber == 1)
		{
			wcout << L"�˻��� �ʼ��� �Է����ּ���(��,��,��...) : ";
			getline(wcin, Input);
			cout << endl;

			while (Input.size() > 1)
			{
				wcout << L"�� ���ڸ� �Է����ּ��� : ";
				getline(wcin, Input);
				cout << endl;
			}

			getVec = DataManager::Get()->FindData(Input);
			if (getVec == nullptr)
			{
				wcout << L"�ش� �ʼ��� �����Ͱ� �����ϴ�.";
				cout << endl;
				continue;
			}

			wcout << Input << L"(��)�� �˻��� ������" << endl;

			for (size_t i = 0; i < getVec->size(); i++)
			{
				wcout << L"�̸� : " << getVec->at(i)->GetName() << endl;
				wcout << L"�ּ� : " << getVec->at(i)->GetAddress() << endl;
				wcout << L"�ڵ��� : " << getVec->at(i)->GetPhoneName() << endl << endl;
			}

			wcout << L"�ڷ� ���ư��� : BackSpace. �ƹ�Ű�� ��������.";
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
			wcout << L"�˻��� �̸��� �Է����ּ��� : ";
			getline(wcin, Input);
			cout << endl;

			vector<PersonInfo*>* getVector = DataManager::Get()->GetSameName(Input);

			if (getVector == nullptr)
			{
				wcout << L"�ش� �̸��� �����Ͱ� �����ϴ�.";
				continue;
			}

			for (size_t i = 0; i < getVector->size(); i++)
			{
				PersonInfo* getInfo = getVector->at(i);

				wcout << L"�̸� : " << getInfo->GetName() << endl;
				wcout << L"�ּ� : " << getInfo->GetAddress() << endl;
				wcout << L"�ڵ��� : " << getInfo->GetPhoneName() << endl << endl;
			}

			wcout << L"�ڷ� ���ư��� : BackSpace. �ƹ�Ű�� ��������.";
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
