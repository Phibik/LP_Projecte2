/*#include "pch.h"
#include "GrafSolucio.h"

bool jaEstaAlVector(const std::vector<Coordinate>& nodes, const Coordinate& c)
{
	int i = 0;
	while (i != nodes.size())
	{
		if (nodes[i].lat == c.lat && nodes[i].lon == c.lon)
			return true;
		else
			i++;
	}
	return false;
}

GrafSolucio::GrafSolucio(const std::vector<CamiBase*>& camins)
{
	std::vector<Coordinate> nodes;
	for (int i = 0; i < camins.size(); i++)
	{
		std::vector<Coordinate> temporal = camins[i]->getCamiCoords();
		for (int i = 0; i < temporal.size(); i++)
			if (!jaEstaAlVector(nodes, temporal[i]))
				nodes.push_back(temporal[i]);
	}
	nNodes = m_nodes.size();
	matriu.resize(nNodes, std::vector<int>(nNodes));
	nArestes = nNodes * (nNodes - 1) / 2;
	for (int i = 0; i < nNodes; i++)
	{
		for (int j = 0; j < nNodes; j++)
		{
			matriu[i][j] = Util::DistanciaHaversine(nodes[i], nodes[j]);
			matriu[j][j] = Util::DistanciaHaversine(nodes[i], nodes[j]);
		}
	}
}

GrafSolucio::GrafSolucio(const std::vector<Coordinate>& nodes, const std::vector<std::vector<int>>& matriu_adj)
{
	m_nodes = nodes;
	matriu = matriu_adj;
	for (int i = 0; i < nNodes; i++)
		for (int j = i + 1; j < nNodes; j++)
			if (matriu[i][j] != 0)
				nArestes++;
}

GrafSolucio::GrafSolucio(const std::vector<Coordinate>& nodes, const std::vector<std::vector<int>>& parelles_nodes,
	const std::vector<int>& pesos)
{
	m_nodes = nodes;
	nNodes = m_nodes.size();
	nArestes = parelles_nodes.size();
	crearMatriu(parelles_nodes, pesos);
}

void GrafSolucio::crearMatriu(const std::vector<std::vector<int>>& parelles, const std::vector<int>& pesos)
{
	matriu.resize(nNodes);
	for (size_t i = 0; i < nNodes; i++)
	{
		matriu[i].resize(nNodes, 0);
	}
	for (size_t i = 0; i < parelles.size(); i++)
	{
		matriu[parelles[i][0]][parelles[i][1]] = pesos[i];
		matriu[parelles[i][1]][parelles[i][0]] = pesos[i];
	}
}

void GrafSolucio::inserirAresta(int posNode1, int posNode2, int pes)
{
	matriu[posNode1][posNode2] = pes;
	matriu[posNode2][posNode1] = pes;
}

void GrafSolucio::afegirNode(const Coordinate& node)
{
	m_nodes.push_back(node);
	matriu.push_back(std::vector<int>(nNodes));
	nNodes++;
	for (int i = 0; i < nNodes; i++)
		matriu[i].push_back(0);
}

*/