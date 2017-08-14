#pragma once

#include "SingletonTemplate.h"

class HUDManager : public Singleton<HUDManager>
{
	friend Singleton<HUDManager>;
public:
	HUDManager();
	~HUDManager();

private:

};

HUDManager::HUDManager()
{
}

HUDManager::~HUDManager()
{
}