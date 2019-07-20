#pragma once
#include "Scene.h"

class MenuScene : public Scene
{
public:
	MenuScene();
	~MenuScene();

	void Run() override;

private:
	int m_ScreenIndex;
	int m_RealIndex;
	int m_MaxIndex;
};

