#pragma once
#include "pch.h"

#include <string>
#include "Common.h"
#include "PuntDeInteresBase.h"

class PuntDeInteresRestaurantSolucio : public PuntDeInteresBase {

private:
	std::string cuina;          // cuisine
	std::string discapacitat;   // wheelchair
public:
	PuntDeInteresRestaurantSolucio() : cuina(""), discapacitat("") {}
	PuntDeInteresRestaurantSolucio(Coordinate coord, const std::string& name, const std::string& cuina,
		std::string disc) : PuntDeInteresBase(coord, name), cuina(cuina), discapacitat(disc) {}

	std::string getName() { return PuntDeInteresBase::getName(); }
	unsigned int getColor();

	PuntDeInteresRestaurantSolucio* clone() { return new PuntDeInteresRestaurantSolucio(*this); }
};

unsigned int PuntDeInteresRestaurantSolucio::getColor()
{
	unsigned int color = PuntDeInteresBase::getColor();

	if (cuina == "pizza" && discapacitat == "yes")
		color = 0x03FCBA;
	else if (cuina == "chinese")
		color = 0xA6D9F7;
	else if (discapacitat == "yes")
		color = 0x251351;

	return color;
}