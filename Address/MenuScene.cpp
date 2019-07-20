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
//1. 주소록 추가
//2. 삭제하기
//3. 전체보기
//4. 데이터저장
//5. 불러오기
//6. 검색, 수정
//7. 수정

	GoToxy(41, 4);
	wcout << L"주         소         록" << endl;

	GoToxy(45, 7);
	wcout << L"1. 주소록 추가" << endl;

	GoToxy(45, 9);
	wcout << L"2. 데이터 삭제" << endl;

	GoToxy(45, 11);
	wcout << L"3. 전체 보기" << endl;

	GoToxy(45, 13);
	wcout << L"4. 데이터 수정" << endl;

	GoToxy(45, 15);
	wcout << L"5. 검색" << endl;

	GoToxy(45, 17);
	wcout << L"6. 전체삭제" << endl;

	GoToxy(38, m_ScreenIndex);
	cout << "-->";

	GoToxy(110, 28);
	wcout << L"종료 : Q";

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
			wcout << L"전체삭제 완료" << endl;

			Sleep(1000);
		}
	}
		break;
	case 'Q':
	case 'q':
	case 'ㅂ':
	case 'ㅃ':
		Logic::Get()->SetIsClose(true);
		break;
	}
}
