#include "pch.h"
#include "Logic.h"
#include "Scene.h"

#include "MenuScene.h"
#include "DeleteScene.h"
#include "InsertScene.h"
#include "AllViewScene.h"
#include "SerchScene.h"
#include "ModifyScene.h"

Logic* Logic::m_Instance = nullptr;

Logic::Logic()
{
	m_isClose = false;
}

Logic::~Logic()
{
	for (size_t i = 0; i < m_vecScene.size(); i++)
	{
		if (m_vecScene[i] != nullptr)
			delete m_vecScene[i];
	}
}

Logic * Logic::Get()
{
	if (m_Instance == nullptr)
		m_Instance = new Logic();

	return m_Instance;
}

void Logic::Delete()
{
	delete m_Instance;
}

void Logic::Init()
{
	//실행파일 경로
	wchar_t Path[255] = {};
	GetModuleFileNameW(nullptr, Path, 255);
	m_DefultPath = Path;

	m_DefultPath.erase(m_DefultPath.find_last_of(L"\\"), m_DefultPath.find_last_of(L"\\"));
	m_DefultPath += L"\\";

	//1. 주소록 추가
	//2. 삭제하기
	//3. 전체보기
	//4. 데이터저장
	//5. 불러오기
	//6. 검색, 수정
	//7. 수정
	AddScene<MenuScene>(L"MenuScene");

	AddScene<InsertScene>(L"InsertScene");
	AddScene<DeleteScene>(L"DeleteScene");
	AddScene<AllViewScene>(L"AllViewScene");
	AddScene<ModifyScene>(L"ModifyScene");
	AddScene<SerchScene>(L"SerchScene");

	m_CurScene = m_vecScene[0];
}

void Logic::Run()
{
	m_CurScene->Run();
}

void Logic::ChangeScene(const wstring& SceneName)
{
	Scene* getScene = FindScene(SceneName);

	if (getScene == nullptr)
		return;

	m_CurScene = getScene;
}

void Logic::ChangeScene(SCENE_INDEX Index)
{
	if (static_cast<int>(Index) > m_vecScene.size())
		return;

	m_CurScene = m_vecScene[static_cast<int>(Index)];
}

Scene * Logic::FindScene(const wstring & SceneName)
{
	auto FindIter = m_SceneMap.find(SceneName);

	if (FindIter == m_SceneMap.end())
		return nullptr;
	
	return FindIter->second;
}