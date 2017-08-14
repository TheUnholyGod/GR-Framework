///////////////////////////////////////////////////////////////////////////////
/*!
\file   UIManager.h
\author Lin Xin
\par	email: 163320B@mymail.nyp.edu.sg
\brief
Header file for singleton UIManager. This class updates and changes the gamestate,
calls the LevelManager to start and pause levels. Also responsible for printing
various game screens: Menu, Options, Gameover etc.
*/
///////////////////////////////////////////////////////////////////////////////
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