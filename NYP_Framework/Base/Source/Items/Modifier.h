///////////////////////////////////////////////////////////////////////////////
/*!
\file   Modifier.h
\author Lin Xin
\par	email: 163320B@mymail.nyp.edu.sg
\brief
Header file for modifier class. Stores basic modifier params.
*/
///////////////////////////////////////////////////////////////////////////////
#pragma once

class Modifier
{
public:
	enum MODIFIER_TYPE
	{
		MT_DAMAGE_OVER_TIME = 0,
		MT_INHIBIT_MOVEMENT,
	};
	Modifier();
	~Modifier();

private:
	//Multitexture based on how many modifiers there are.
	int m_Level;
	MODIFIER_TYPE m_type;
};
