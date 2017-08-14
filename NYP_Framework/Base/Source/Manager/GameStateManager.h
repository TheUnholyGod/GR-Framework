#pragma once

#include "SingletonTemplate.h"

class GameStateManager : public Singleton<GameStateManager>
{
	friend Singleton<GameStateManager>;
public:
	GameStateManager();
	~GameStateManager();

private:

};

GameStateManager::GameStateManager()
{
}

GameStateManager::~GameStateManager()
{
}