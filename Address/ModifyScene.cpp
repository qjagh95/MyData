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
		wcout << L"������ �������� �ʼ�, �̸��˻� �� �ϳ��� ���� ���ּ���" << endl;
		wcout << L"1.�ʼ��˻� 2.�̸��˻� 3.������ : ";
		getline(wcin, Input);
		cout << endl;

		while (GetIsNumber(Input) == false)
		{
			wcout << L"���ڸ� �Է����ּ��� : ";
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
				wcout << i + 1 << L"." << endl;
				wcout << L"�̸� : " << getVec->at(i)->GetName() << endl;
				wcout << L"�ּ� : " << getVec->at(i)->GetAddress() << endl;
				wcout << L"�ڵ��� : " << getVec->at(i)->GetPhoneName() << endl << endl;
			}

			int Index = 0;
			wcout << L"���° �����͸� �����Ͻðڽ��ϱ�? ";
			wcin >> Index;

			while (Index - 1 > getVec->size() || Index - 1 < 0)
			{
				wcout << L"�ٽ� �Է����ּ��� : ";
				wcin >> Index;
			}

			Index -= 1;

			int Select = 0;
			bool isCheck = false;

			while (isCheck == false)
			{
				wcout << L"� �����͸� �����Ͻðڽ��ϱ�? (1.�̸� 2.�ּ� 3.�ڵ��� 4.���Ѵ�) : ";
				wcin >> Select;

				while (Select != 1 && Select != 2 && Select != 3 && Select != 4)
				{
					wcout << L"�ٽ� �Է����ּ��� : ";
					wcin >> Select;
				}

				wstring InputString;
				getline(wcin, InputString);

				switch (Select)
				{
				case 1:
				{
					wcout << L"�̸� : ";
					getline(wcin, InputString);
					getVec->at(Index)->SetName(InputString);
				}
				break;
				case 2:
				{
					wcout << L"�ּ� : ";
					getline(wcin, InputString);
					getVec->at(Index)->SetAddress(InputString);
				}
				break;
				case 3:
				{
					wcout << L"�ڵ��� : ";
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
				wcout << i + 1 << L"." << endl;
				wcout << L"�̸� : " << getVector->at(i)->GetName() << endl;
				wcout << L"�ּ� : " << getVector->at(i)->GetAddress() << endl;
				wcout << L"�ڵ��� : " << getVector->at(i)->GetPhoneName() << endl << endl;
			}

			int Select = 0;
			bool isCheck = false;

			if (getVector->size() == 0 || getVector == nullptr)
			{
				wcout << L"�ش� �̸��� �����Ͱ� �����ϴ�." << endl;
				continue;
			}

			int Index = 0;
			wcout << L"���° �����͸� �����Ͻðڽ��ϱ�? ";
			wcin >> Index;

			while (Index - 1 > getVector->size() || Index - 1 < 0)
			{
				wcout << L"�ٽ� �Է����ּ���";
				wcin >> Index;
			}

			Index -= 1;

			while (isCheck == false)
			{
				wcout << L"� �����͸� �����Ͻðڽ��ϱ�? (1.�̸� 2.�ּ� 3.�ڵ��� 4.���Ѵ�) : ";
				wcin >> Select;

				while (Select != 1 && Select != 2 && Select != 3 && Select != 4)
				{
					wcout << L"�ٽ� �Է����ּ��� : ";
					wcin >> Select;
				}

				PersonInfo* getInfo = getVector->at(Index);
				wstring InputString;
				getline(wcin, InputString);

				switch (Select)
				{
				case 1:
				{
					wcout << L"�̸� : ";
					getline(wcin, InputString);
					getInfo->SetName(InputString);
				}
				break;
				case 2:
				{
					wcout << L"�ּ� : ";
					getline(wcin, InputString);
					getInfo->SetAddress(InputString);
				}
				break;
				case 3:
				{
					wcout << L"�ڵ��� : ";
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

		wcout << L"���� �Ͻðڽ��ϱ�? (BackSpace) �ƴϸ� �ƹ�Ű�� �����ּ���" << endl << endl;

		if (_getch() == VK_BACK)
		{
			Logic::Get()->ChangeScene(SI_MENU);
			break;
		}
		else
			continue;
	}
}
