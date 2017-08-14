#pragma once

#include "SingletonTemplate.h"

class UIManager : public Singleton<UIManager>
{
	friend Singleton<UIManager>;
public:
	UIManager();
	~UIManager();

private:

};

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}