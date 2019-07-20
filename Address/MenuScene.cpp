#include "pch.h"
#include "MenuScene.h"
#include "Logic.h"
#include "DataManager.h"

MenuScene::MenuScene()
{
	m_ScreenIndex = 7;
	m_MaxIndex = m_ScreenIndex + 12;
	m_RealIndex = 1;
}

MenuScene::~MenuScene()
{
}

void MenuScene::Run()
{
//1. �ּҷ� �߰�
//2. �����ϱ�
//3. ��ü����
//4. ����������
//5. �ҷ�����
//6. �˻�, ����
//7. ����

	GoToxy(41, 4);
	wcout << L"��         ��         ��" << endl;

	GoToxy(45, 7);
	wcout << L"1. �ּҷ� �߰�" << endl;

	GoToxy(45, 9);
	wcout << L"2. ������ ����" << endl;

	GoToxy(45, 11);
	wcout << L"3. ��ü ����" << endl;

	GoToxy(45, 13);
	wcout << L"4. ������ ����" << endl;

	GoToxy(45, 15);
	wcout << L"5. �˻�" << endl;

	GoToxy(45, 17);
	wcout << L"6. ��ü����" << endl;

	GoToxy(38, m_ScreenIndex);
	cout << "-->";

	GoToxy(110, 28);
	wcout << L"���� : Q";

	int Key = _getch();

	switch (Key)
	{
	case KEY_UP:
		if (m_ScreenIndex - 2 < 7)
			m_ScreenIndex = m_MaxIndex - 2;
		else
			m_ScreenIndex -= 2;

		if (1 >= m_RealIndex)
			m_RealIndex = 6;
		else
			m_RealIndex--;

		break;

	case KEY_DOWN:
		if (m_ScreenIndex + 2 >= m_MaxIndex)
			m_ScreenIndex = 7;
		else
			m_ScreenIndex += 2;

		if (m_RealIndex > Logic::Get()->GetSceneSize() - 1)
			m_RealIndex = 1;
		else
			m_RealIndex++;
		break;
	case '\r':
	{
		if(m_RealIndex != 6)
			Logic::Get()->ChangeScene(static_cast<SCENE_INDEX>(m_RealIndex));
		else
		{
			GoToxy(45, 20);
			DataManager::Get()->DeleteAll();
			wcout << L"��ü���� �Ϸ�" << endl;

			Sleep(1000);
		}
	}
		break;
	case 'Q':
	case 'q':
	case '��':
	case '��':
		Logic::Get()->SetIsClose(true);
		break;
	}
}
