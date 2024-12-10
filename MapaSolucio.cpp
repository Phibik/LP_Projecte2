#include "MapaSolucio.h"
#include "Util.h"
#include "BallTree.h"
#include "GrafSolucio.h"

void MapaSolucio::getPdis(std::vector<PuntDeInteresBase*>& pdis) {
	for (auto it = puntsDeInteres.begin(); it != puntsDeInteres.end(); it++)
	{
		pdis.push_back(*it);
	}
}

void MapaSolucio::getCamins(std::vector<CamiBase*>& camins) {
	for (auto it = camins.begin(); it != camins.end(); it++)
	{
		camins.push_back((*it)->clone());
	}
}

void MapaSolucio::parsejaXmlElements(std::vector<XmlElement>& xmlElements) {
	clearCamins();
	clearPdis();

	for (int i = 0; i < xmlElements.size(); ++i)
	{
		if (xmlElements[i].id_element == "node")
		{
			std::string nom = "", shop = "", cuina = "", horari = "", discapacitat = "";
			bool pdis = true, existeix = false;
			Coordinate coord = { 0, 0 };

			for (int j = 0; j < xmlElements[i].fills.size(); j++)
			{
				if (xmlElements[i].fills[j].first == "tag")
				{
					std::pair<std::string, std::string> valorTag = Util::kvDeTag(xmlElements[i].fills[j].second);

					if (valorTag.first == "name")
					{
						nom = valorTag.second;
						existeix = true;
					}
					else if (valorTag.first == "shop") shop = valorTag.second;
					else if (valorTag.first == "cuisine") cuina = valorTag.second;
					else if (valorTag.first == "opening_hours") horari = valorTag.second;
					else if (valorTag.first == "wheelchair") discapacitat = valorTag.second;
					else if (valorTag.first == "highway" || valorTag.first == "public_transport" ||
						valorTag.first == "access" || valorTag.first == "entrance") pdis = false;
				}
			}

			if (existeix && pdis)
			{
				// std::stod converteix double a string
				for (int j = 0; j < xmlElements[i].atributs.size(); j++)
				{
					if (xmlElements[i].atributs[j].first == "lat")
						coord.lat = std::stod(xmlElements[i].atributs[j].second);
					else if (xmlElements[i].atributs[j].first == "lon")
						coord.lon = std::stod(xmlElements[i].atributs[j].second);
				}

				// Crear PuntDeInteres depenent de si s�n shops, restaurants o normals
				if (shop != "")
					puntsDeInteres.push_back(new PuntDeInteresBotigaSolucio(coord, nom, shop, horari, discapacitat));
				else if (cuina != "")
					puntsDeInteres.push_back(new PuntDeInteresRestaurantSolucio(coord, nom, cuina, discapacitat));
				else
					puntsDeInteres.push_back(new PuntDeInteresBase(coord, nom));
			}
		}

		if (xmlElements[i].id_element == "way")
		{
			bool highway = false;
			std::vector<std::string> nd;
			std::vector<Coordinate> coords;

			for (int j = 0; j < xmlElements[i].fills.size(); j++)
			{
				if (xmlElements[i].fills[j].first == "tag")
				{
					if (xmlElements[i].fills[j].second[0].second == "highway")
						highway = true;
				}
				else if (xmlElements[i].fills[j].first == "nd")
					nd.push_back(xmlElements[i].fills[j].second[0].second);
			}

			// Highway ==> afegir als camins les coordenades dels nodes
			if (highway)
			{
				int j = 0;
				while (j < xmlElements.size() && !nd.empty())
				{
					if (xmlElements[j].id_element == "node")
					{
						Coordinate coord = { 0,0 };
						bool trobat = false;

						// revisar si els fills tenen tag, doncs no son nodes de cami
						for (int k = 0; k < xmlElements[j].atributs.size(); ++k)
						{
							if (xmlElements[j].atributs[k].first == "id")
							{
								if (xmlElements[j].atributs[k].second == nd[0])
								{
									trobat = true;
									nd.erase(nd.begin());
								}
							}
							else if (xmlElements[j].atributs[k].first == "lat")
								coord.lat = std::stod(xmlElements[j].atributs[k].second);
							else if (xmlElements[j].atributs[k].first == "lon")
								coord.lon = std::stod(xmlElements[j].atributs[k].second);
						}

						if (trobat)
						{
							coords.push_back(coord);
							j = -1;
						}
					}

					++j;
				}

				camins.push_back(new CamiSolucio(coords));
			}
		}
	}
}

CamiBase* MapaSolucio::buscaCamiMesCurt(PuntDeInteresBase* desde, PuntDeInteresBase* a) {
	// TODO IMPLEMENTACIO DE LA SEGONA PART
	return nullptr;
}
