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

class Equipment : public ItemBase
{
public:
	Equipment(int ID);
	virtual ~Equipment();

	virtual bool parseFile(const std::string fileName);

private:
	//Equipment specific variables

};

