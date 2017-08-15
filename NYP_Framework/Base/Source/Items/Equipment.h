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

	virtual bool parseFile(const std::string fileName) = 0;

//Equipment specific variables
private:
	size_t m_max_runes; //Maximum number of runes this equipment can store
	std::vector<Runes*> m_runes; //Stores all equipped runes
};

