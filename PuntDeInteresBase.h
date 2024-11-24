#pragma once
#include "pch.h"

#include <string>
#include "Common.h"

class PuntDeInteresBase
{
private:
	Coordinate m_coord;
	std::string m_name;
	std::string id;

public:		
	PuntDeInteresBase();
	PuntDeInteresBase(Coordinate coord, std::string name);

	virtual std::string getName();
	Coordinate getCoord();
	virtual unsigned int getColor();

	virtual PuntDeInteresBase* clone() { return new PuntDeInteresBase(m_coord, m_name); }
	void setId(const std::string& id) { this->id = id; }
};