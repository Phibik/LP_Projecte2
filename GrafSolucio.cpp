#include "pch.h"
#include "GrafSolucio.h"

static bool estaEnVector(const std::vector<Coordinate>& nodes, const Coordinate& c) {
    int index = 0;
    while (index != nodes.size())
    {
        if (nodes[index].lat == c.lat && nodes[index].lon == c.lon)
            return true; // La coordenada ya existe en el vector.
        else
            ++index; // Incrementar índice.
    }
    return false; // No se encontró la coordenada en el vector.
}

GrafSolucio::GrafSolucio(const std::vector<CamiBase*>& camins) {
    std::vector<Coordinate> uniqueNodes; // Vector para almacenar las coordenadas únicas.

    for (int i = 0; i < camins.size(); ++i)
    {
        std::vector<Coordinate> tempCoords = camins[i]->getCamiCoords();
        for (int j = 0; j < tempCoords.size(); ++j)
        {
            if (!estaEnVector(uniqueNodes, tempCoords[j]))
                uniqueNodes.push_back(tempCoords[j]);   // Añade coordenada si no está en el vector.
        }
    }

    nNodes = m_nodes.size();                            // Número de nodos.
    matriu.resize(nNodes, std::vector<int>(nNodes));    // Inicializa la matriz.
    nArestes = nNodes * (nNodes - 1) / 2;               // Número de aristas.

    for (int i = 0; i < nNodes; ++i)
    {
        for (int j = 0; j < nNodes; ++j)
        {
            matriu[i][j] = Util::DistanciaHaversine(uniqueNodes[i], uniqueNodes[j]);
            matriu[j][j] = Util::DistanciaHaversine(uniqueNodes[i], uniqueNodes[j]);
        }
    }
}

/*GrafSolucio::GrafSolucio(const std::vector<Coordinate>& nodes, const std::vector<std::vector<int>>& matriu_adj) {
    m_nodes = nodes;
    matriu = matriu_adj;
    for (int i = 0; i < nNodes; ++i) {
        for (int j = i + 1; j < nNodes; ++j) {
            if (matriu[i][j] != 0)
                ++nArestes;
        }
    }
}

GrafSolucio::GrafSolucio(const std::vector<Coordinate>& nodes, const std::vector<std::vector<int>>& parelles_nodes,
    const std::vector<int>& pesos) {
    m_nodes = nodes;
    nNodes = m_nodes.size();
    nArestes = parelles_nodes.size();
    crearMatriu(parelles_nodes, pesos);
}*/

void GrafSolucio::crearMatriu(const std::vector<std::vector<int>>& parelles, const std::vector<int>& pesos) {
    matriu.resize(nNodes);
    for (size_t i = 0; i < nNodes; ++i) {
        matriu[i].resize(nNodes, 0); // Inicializa la matriz con ceros.
    }
    for (size_t i = 0; i < parelles.size(); ++i) {
        matriu[parelles[i][0]][parelles[i][1]] = pesos[i];
        matriu[parelles[i][1]][parelles[i][0]] = pesos[i];
    }
}

void GrafSolucio::inserirAresta(int posNode1, int posNode2, int pes) {
    matriu[posNode1][posNode2] = pes;
    matriu[posNode2][posNode1] = pes;
}

void GrafSolucio::afegirNode(const Coordinate& node) {
    m_nodes.push_back(node); // Añade el nodo al vector de nodos.
    matriu.push_back(std::vector<int>(nNodes)); // Añade una nueva fila en la matriz.
    ++nNodes;
    for (int i = 0; i < nNodes; ++i) {
        matriu[i].push_back(0); // Añade una nueva columna con ceros.
    }
}
