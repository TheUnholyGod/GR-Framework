///////////////////////////////////////////////////////////////////////////////
/*!
\file   Equipment.cpp
\author Lin Xin
\par	email: 163320B@mymail.nyp.edu.sg
\brief
cpp file for Equipment class.
*/
///////////////////////////////////////////////////////////////////////////////
#include "Equipment.h"

Equipment::Equipment(int ID)
{
	this->m_ID = ID;
	parseFile("Asset//Weapons.txt");
}

Equipment::~Equipment()
{
}

bool Equipment::parseFile(const std::string fileName)
{
	//Use loader to read file into vector string
	if(!Loader::GetInstance()->LoadData(fileName))
		return false;

	//Stores the data read by loader
	std::vector<std::string> file_data;

	//Pass vector string into file_data
	file_data = Loader::GetInstance()->GetData();

	//Manipulate the data and initialise respective variables


	return false;
}
