///////////////////////////////////////////////////////////////////////////////
/*!
\file   Equipment.h
\author Lin Xin
\par	email: 163320B@mymail.nyp.edu.sg
\brief
Header file for equipment class. Stores basic equipment params.
*/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ItemBase.h"
#include "Runes.h"

class Equipment : public ItemBase
{
public:
	Equipment();
	virtual ~Equipment();

protected:
	/*Reads the file for information:
	ID,Name,Description,TextureDirectory*/
	bool parseFile(const std::string fileName) = 0;

	/*Returns this equipment's rune vector*/
	std::vector<Runes*> getRunes();
	/*Returns the max rune slot of this weapon*/
	int getMaxRunes();
	/*Sets the max rune slot of this weapon*/
	void setMaxRunes(int num_slot);

	/*Add to the runes of this weapon
	Returns true if same type rune doesn't exist
	Returns false if same type rune exists*/
	bool addRune(Runes* new_rune);

	/*Removes the same type runes
	Returns true if removed successfully
	Returns false if no rune of the specified type exists*/
	bool removeRune(Runes::ATTRIBUTE_TYPE type);

	/*Replaces the existing rune with this rune
	Returns true if replaced successfully. If runes doesnt exist, add it in.
	Returns false if replace failed*/
	bool replaceRune(Runes* new_rune);

	size_t m_max_runes; //Maximum number of runes this equipment can store
	std::vector<Runes*> m_runes; //Equipment's runes
};

