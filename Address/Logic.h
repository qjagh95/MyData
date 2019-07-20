#pragma once

class Scene;
class Logic
{
public:
	void Init();
	
	template<typename T>
	void AddScene(const wstring& KeyName)
	{
		T* newScene = new T();

		m_SceneMap.insert(make_pair(KeyName, newScene));
		m_vecScene.push_back(newScene);
	}

	void Run();
	void ChangeScene(const wstring& SceneName);
	void ChangeScene(SCENE_INDEX Index);
	size_t GetSceneSize() const { return m_vecScene.size(); }
	Scene* GetCurScene() const { return m_CurScene; }
	bool GetIsClose() const { return m_isClose; }
	void SetIsClose(bool Value) { m_isClose = Value; }
	wstring GetDefaultPath() const { return m_DefultPath; }

private:
	Scene* FindScene(const wstring& SceneName);

private:
	Scene* m_CurScene;
	unordered_map<wstring, Scene*> m_SceneMap;
	vector<Scene*> m_vecScene;
	bool m_isClose;
	wstring m_DefultPath;

private:
	Logic();
	~Logic();
	
public:
	static Logic* m_Instance;
	static Logic* Get();
	static void Delete();
};
