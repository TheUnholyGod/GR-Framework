///////////////////////////////////////////////////////////////////////////////
/*!
\file   GameStateManager.h
\author Lin Xin
\par	email: 163320B@mymail.nyp.edu.sg
\brief
Header file for singleton GameStateManager. Store and updates the current state
of the game.
*/
///////////////////////////////////////////////////////////////////////////////
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