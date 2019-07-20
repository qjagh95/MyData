#pragma once
class Scene
{
public:
	virtual void Run() = 0;

protected:
	Scene();
	virtual ~Scene();

	bool GetIsNumber(const wstring& Text);

public:
	friend class Logic;
};