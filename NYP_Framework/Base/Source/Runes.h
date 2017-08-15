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

#include "ItemBase.h"

class Runes : public ItemBase
{
public:
	Runes(int ID);
	virtual ~Runes();

	virtual bool parseFile(const std::string fileName);

private:
	//Rune specific variables


};