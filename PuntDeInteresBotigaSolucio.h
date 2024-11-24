#pragma once
#include "pch.h"

#include <string>
#include "Common.h"
#include "PuntDeInteresBase.h"

class PuntDeInteresBotigaSolucio : public PuntDeInteresBase
{
private:
	std::string shop;
	std::string hores;          // opening_hours
	std::string discapacitat;   // wheelchair
public:

	PuntDeInteresBotigaSolucio() : shop(""), hores(""), discapacitat("") {}
	PuntDeInteresBotigaSolucio(Coordinate coord, const std::string& name, const std::string& shop,
		const std::string& hh, const std::string& disc) : PuntDeInteresBase(coord, name),
		shop(shop), hores(hh), discapacitat(disc) {}

	std::string getName() { return PuntDeInteresBase::getName(); }
	unsigned int getColor();

	PuntDeInteresBotigaSolucio* clone() { return new PuntDeInteresBotigaSolucio(*this); }
};

unsigned int PuntDeInteresBotigaSolucio::getColor()
{
	unsigned int color = PuntDeInteresBase::getColor();
	if (shop == "supermarket")
		color = 0xA5BE00;
	else if (shop == "tobacco")
		color = 0xFFAD69;
	else if (shop == "bakery")
	{
		// find(x) retorna std::string::npos si no troba x
		if ((hores.find("06:00-22:00") != std::string::npos) && (discapacitat == "yes"))
			color = 0x4CB944;
		else
			color = 0xE85D75;
	}
	else
		color = 0xEFD6AC;
	return color;
}