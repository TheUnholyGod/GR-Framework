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

	Runes(int ID);
	virtual ~Runes();

	virtual bool parseFile(const std::string fileName);

	//Calculates the attribute values based on level and rarity
	int calculateAttribute(int lv, int rarity);

private:
	//Rune specific variables
	int m_level;
	std::vector<ATTRIBUTE_TYPE> m_attributes;
	std::vector<float> m_attributes_values;
	std::vector<Modifier*> m_modifiers;
};