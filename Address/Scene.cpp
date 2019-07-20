#include "pch.h"
#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

bool Scene::GetIsNumber(const wstring & Text)
{
	bool isCheck = false;

	for (size_t i = 0; i < Text.size(); i++)
	{
		if ((Text[i] >= '0' && Text[i] <= '9') || (Text[i] >= '-1' && Text[i] <= '-9'))
			isCheck = true;
		else
			return false;
	}

	return isCheck;
}
