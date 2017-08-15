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

class Runes : public ItemBase
{
public:
	//Enums to store the bonus attributes that the rune gives. Each rune will only have one attribute.
	enum ATTRIBUTE_TYPE
	{
		AT_ATTACK = 0,
		AT_DEFEND,
		AT_SPEED,
	};

	Runes(int ID);
	virtual ~Runes();

	virtual bool parseFile(const std::string fileName);

private:
	//Rune specific variables
	ATTRIBUTE_TYPE m_attrib_type;
};