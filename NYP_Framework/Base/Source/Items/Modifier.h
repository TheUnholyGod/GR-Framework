///////////////////////////////////////////////////////////////////////////////
/*!
\file   Modifier.h
\author Lin Xin
\par	email: 163320B@mymail.nyp.edu.sg
\brief
Header file for modifier class. Stores basic modifier params.
*/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <iostream>
#include <string>

class IModifier //Interface for modifier
{
public:
	virtual void display() = 0;
	IModifier() {};
	virtual ~IModifier() {};
};

class Modifier : public IModifier //Core of the modifier. Something that all modifiers has.
{	
public:
	Modifier() {};
	~Modifier() {};

	virtual void display()
	{
		std::cout << "Base modifier" << std::endl;
	}

private:
	int m_level;
};

class ModifierDecorator : public IModifier
{
public:
	ModifierDecorator(IModifier& decorator)
		: m_decorator(decorator) {};
	virtual void display() 
	{
		m_decorator.display();
	}

private:
	IModifier& m_decorator;
};

class BleedModifier : public ModifierDecorator
{
public:
	BleedModifier(IModifier& decorator) 
		: ModifierDecorator(decorator){};
	
	virtual void display()
	{
		ModifierDecorator::display();
		std::cout << "Bleeding" << std::endl;
	}
};