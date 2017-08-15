///////////////////////////////////////////////////////////////////////////////
/*!
\file   RuneBase.cpp
\author Lin Xin
\par	email: 163320B@mymail.nyp.edu.sg
\brief
cpp file for Runes class.
*/
///////////////////////////////////////////////////////////////////////////////
#include "Runes.h"

Runes::Runes(int ID)
{
	this->m_ID = ID;
	parseFile("Assets//Runes.txt");
}

Runes::~Runes()
{
}

bool Runes::parseFile(const std::string fileName)
{
	//Read the file and store: Name, Description, Texture Directory

	//Use loader to read file into vector string
	if (!Loader::GetInstance()->LoadData(fileName))
		return false;

	//Stores the data read by loader
	std::vector<std::string> file_data;

	//Pass vector string into file_data
	file_data = Loader::GetInstance()->GetData();

	//Based on ID, look for the correct row of values.
	std::string rune_data = file_data[this->m_ID];
	std::cout << rune_data << std::endl;

	//Manipulate the data and initialise respective variables
	
	return false;
}
