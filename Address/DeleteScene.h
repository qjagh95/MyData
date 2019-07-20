#pragma once
#include "Scene.h"
class DeleteScene : public Scene
{
public:
	DeleteScene();
	~DeleteScene();

	void Run() override;
};

