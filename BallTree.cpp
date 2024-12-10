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
    std::stack<BallTree*> stack; // Pila para almacenar nodos
    BallTree* current = this;    // Comienza en el nodo actual (raíz)

    while (current != nullptr || !stack.empty()) {
        // Ve lo más a la izquierda posible
        while (current != nullptr) {
            stack.push(current);
            current = current->m_left; // Mueve al hijo izquierdo
        }

        // Obtén el nodo más a la izquierda de la pila
        current = stack.top();
        stack.pop();

        // Procesa el nodo actual
        std::list<Coordinate> listCoordenades(current->m_coordenades.begin(), current->m_coordenades.end());
        out.push_back(listCoordenades);

        // Mueve al subárbol derecho
        current = current->m_right;
    }
}
void BallTree::preOrdre(std::vector<std::list<Coordinate>>& out) {
    std::stack<BallTree*> stack; // Pila para almacenar los nodos
    stack.push(this);            // Empieza con el nodo raíz

    while (!stack.empty()) {
        // Obtén el nodo superior de la pila
        BallTree* current = stack.top();
        stack.pop();

        // Procesa el nodo actual: pasa sus coordenadas a la lista y luego al vector
        std::list<Coordinate> listCoordenades(current->m_coordenades.begin(), current->m_coordenades.end());
        out.push_back(listCoordenades);

        // Agrega el hijo derecho a la pila primero (se procesará después del izquierdo)
        if (current->m_right != nullptr) {
            stack.push(current->m_right);
        }

        // Agrega el hijo izquierdo a la pila
        if (current->m_left != nullptr) {
            stack.push(current->m_left);
        }
    }
}

void BallTree::postOrdre(std::vector<std::list<Coordinate>>& out) {
    if (this == nullptr) return; // Caso base: árbol vacío

    std::stack<BallTree*> stack1; // Primera pila para recorrer el árbol
    std::stack<BallTree*> stack2; // Segunda pila para almacenar nodos en orden post-order
    stack1.push(this);            // Empieza con el nodo raíz

    // Recorre el árbol
    while (!stack1.empty()) {
        BallTree* current = stack1.top();
        stack1.pop();
        stack2.push(current); // Empuja el nodo actual a la segunda pila

        // Agrega los hijos del nodo actual a la primera pila
        if (current->m_left != nullptr) {
            stack1.push(current->m_left);
        }
        if (current->m_right != nullptr) {
            stack1.push(current->m_right);
        }
    }

    // Procesa los nodos de la segunda pila
    while (!stack2.empty()) {
        BallTree* current = stack2.top();
        stack2.pop();

        // Convierte las coordenadas del nodo actual a una lista y las agrega a 'out'
        std::list<Coordinate> listCoordenades(current->m_coordenades.begin(), current->m_coordenades.end());
        out.push_back(listCoordenades);
    }
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



