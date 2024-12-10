#include "BallTree.h"

// funció recursiva
void BallTree::construirArbre(const std::vector<Coordinate>& coordenades)
{
    // condició de parada
    // no fa falta perquè tot i que es recursiu el vector de coords es cada vegada més petit
    
    // inicilitzar m_coords y m_pivot
    m_coordenades = coordenades;
    m_pivot = Util::calcularPuntCentral(m_coordenades);

    // calcular totes les distancies respecte el pivot i buscar punt A
    std::vector<double> distancies;
    int indexA = 0;   // index del punt A (més llunyà)
    for (int i = 0; i < m_coordenades.size(); ++i)
    {
        double dis = Util::DistanciaHaversine(m_pivot, coordenades[i]);
        distancies.push_back(dis);

        // actulitzar index A per ser la distància més gran
        if (dis > distancies[indexA])
            indexA = i;
    }

    m_radi = distancies[indexA];

    // Aquí es para la recrusivitat si no hi ha suficients nodes per fer més BallTrees fills
    if (m_coordenades.size() >= 2)
    {
        // calcular totes les distancies respecte A i buscar punt B
        std::vector<double> distanciesA;
        Coordinate coordA = { m_coordenades[indexA].lat, m_coordenades[indexA].lon };
        int indexB = 0;   // index del punt B (més llunyà a A)

        for (int i = 0; i < m_coordenades.size(); ++i)
        {
            double dis = Util::DistanciaHaversine(coordA, coordenades[i]);
            distanciesA.push_back(dis);

            // actulitzar index B per ser la distància més gran
            if (dis > distancies[indexB])
                indexB = i;
        }

        Coordinate coordB = { m_coordenades[indexB].lat, m_coordenades[indexB].lon };

        // Reperir nodes entre els fills A i B que estiguin més propers
        std::vector<Coordinate> coordenadesA, coordenadesB;
        for (int i = 0; i < m_coordenades.size(); ++i)
        {
            // aprofito vector distanciesA
            if (distanciesA[i] < Util::DistanciaHaversine(coordB, coordenades[i]))
                coordenadesA.push_back(coordenades[i]);
            else
                coordenadesB.push_back(coordenades[i]);
        }

        // crear fill_esquerra, fill_dret...
        m_left = new BallTree();
        m_right = new BallTree();
        m_left->m_root = this;
        m_right->m_root = this;

        m_left->construirArbre(coordenadesA);
        m_right->construirArbre(coordenadesB);
    }
}

void BallTree::inOrdre(std::vector<std::list<Coordinate>>& out) {
    // TODO: TASCA 2
}
void BallTree::preOrdre(std::vector<std::list<Coordinate>>& out) {
    // TODO: TASCA 2
}

void BallTree::postOrdre(std::vector<std::list<Coordinate>>& out) {
    // TODO: TASCA 2
}

Coordinate BallTree::nodeMesProper(Coordinate targetQuery, Coordinate& Q, BallTree* ball) {
    // TODO: TASCA 3
    return { 2,2 };
}



