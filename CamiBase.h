#pragma once

#include "Common.h"
#include <vector>

class CamiBase
{
public:
    virtual std::vector<Coordinate> getCamiCoords() = 0;
    virtual CamiBase* clone() = 0;
};

class CamiSolucio : public CamiBase
{
private:
    std::string nom;
    std::vector<Coordinate> camins;

public:
    CamiSolucio() { camins = getCamiCoords(); }
    CamiSolucio(const std::vector<Coordinate>& caminoCoords) { camins = caminoCoords; }

    std::vector<Coordinate> getCamiCoords();
    CamiSolucio* clone() { return new CamiSolucio(*this); }
};

inline std::vector<Coordinate> CamiSolucio::getCamiCoords()
{
    std::vector<Coordinate> caminoCoords;

    for (int i = 0; i < camins.size(); ++i)
        caminoCoords.push_back(camins[i]);

    return caminoCoords;
}