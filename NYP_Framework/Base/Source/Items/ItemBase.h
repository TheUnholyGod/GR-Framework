///////////////////////////////////////////////////////////////////////////////
/*!
\file   ItemBase.h
\author Lin Xin
\par	email: 163320B@mymail.nyp.edu.sg
\brief
Header file for base item class. Stores basic item params.
*/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>
#include <vector>
#include "Loader.h"

class ItemBase
{
public:
	ItemBase();
	~ItemBase();

protected:
	int m_ID;
	std::string m_name;
	std::string m_description;
	std::string m_textureLocation;
};

