#pragma once
#include "pch.h"

#include "Util.h"
#include "Common.h"
#include "PuntDeInteresBase.h"
#include "PuntDeInteresBotigaSolucio.h"
#include "PuntDeInteresRestaurantSolucio.h"
#include "CamiBase.h"
#include <vector>
#include "MapaBase.h"

class MapaSolucio : public MapaBase
{
private:
	std::vector<PuntDeInteresBase*> puntsDeInteres;
	std::vector<CamiBase*> camins;

public:
	void clearCamins();
	void clearPdis();

	void getPdis(std::vector<PuntDeInteresBase*>&) override;
	void getCamins(std::vector<CamiBase*>&) override;

	void parsejaXmlElements(std::vector<XmlElement>& xmlElements) override;

	CamiBase* buscaCamiMesCurt(PuntDeInteresBase* desde, PuntDeInteresBase* a) override;
};


inline void MapaSolucio::clearCamins()
{
	while (!camins.empty())
	{
		delete camins.front();
		camins.erase(camins.begin());
	}
}

inline void MapaSolucio::clearPdis()
{
	while (!puntsDeInteres.empty())
	{
		delete puntsDeInteres.front();
		puntsDeInteres.erase(puntsDeInteres.begin());
	}
}
