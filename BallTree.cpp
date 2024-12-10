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

Coordinate BallTree::nodeMesProper(Coordinate targetQuery, Coordinate& Q, BallTree* ball)
{
    // NO SE QUE ES "Q", potser s'ha de getionar al principi o algo #################################

    // calcular distàncies entre el pivot i targetQuery | Q
    double d1 = Util::DistanciaHaversine(ball->m_pivot, targetQuery);
    double d2 = Util::DistanciaHaversine(ball->m_pivot, Q);

    if (d1 - ball->m_radi >= d2)
        return Q;

    // si ball es una fulla, actualitza Q si és el node camí més proper al punt d'interès (dels punts de ball)
    if (ball->m_left == nullptr && ball->m_right == nullptr)
    {
        for (auto it = m_coordenades.begin(); it != m_coordenades.end(); ++it)
        {
            if (Util::DistanciaHaversine(targetQuery, *it) < Util::DistanciaHaversine(targetQuery, Q))
            {
                Q.lat = it->lat;
                Q.lon = it->lon;
            }
        }
        return Q;
    }
    else
    {
        
        // distancia pdi respect m_left (da) i m_right (db)
        double da = 99999999;
        double db = 99999999; 

        //// comprobar que no siguin nullptr que sino es lia que te cagas
        if (ball->m_left != nullptr)
            da = Util::DistanciaHaversine(targetQuery, ball->m_left->m_pivot);
        if (ball->m_right != nullptr)
            db = Util::DistanciaHaversine(targetQuery, ball->m_right->m_pivot);

        // si da < db primer cerca per m_left
        if (da < db)
        {
            if (ball->m_left != nullptr)
                nodeMesProper(targetQuery, Q, ball->m_left);
            if (ball->m_right != nullptr)
                nodeMesProper(targetQuery, Q, ball->m_right);
        }
        // si da >= db primer cerca per m_right
        else
        {
            if (ball->m_right != nullptr)
                nodeMesProper(targetQuery, Q, ball->m_right);
            if (ball->m_left != nullptr)
                nodeMesProper(targetQuery, Q, ball->m_left);
        }
    }

    return Q;
}



