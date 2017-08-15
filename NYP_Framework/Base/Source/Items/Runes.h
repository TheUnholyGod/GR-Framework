///////////////////////////////////////////////////////////////////////////////
/*!
\file   Runes.h
\author Lin Xin
\par	email: 163320B@mymail.nyp.edu.sg
\brief
Header file for runes class. Stores basic Rune params.
*/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <iostream>
#include "ItemBase.h"
#include "Modifier.h"

class Runes : public ItemBase 
{
public:
	//Enums to store the bonus attributes that the rune gives. Each rune will only have one base attribute.
	enum ATTRIBUTE_TYPE
	{
		AT_ATTACK = 0,
		AT_DEFEND,
		AT_SPEED,
	};
	Runes();
	Runes(int ID);
	virtual ~Runes();

private:
	int m_level; //Rune Level
	std::vector<ATTRIBUTE_TYPE> m_attributes; //Rune attributes type vector
	std::vector<float> m_attributes_values; //Rune attributes value vector
	std::vector<Modifier*> m_modifiers; //Rune modifier vector
};