/*
 * Grupo TAIS16, Samuel Lapuente Jiménez, Alvar David Soler Rus
 * 
 * Ejercicio 10. Tema 3.
 * 
 */


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
#include "Grafo.h"

/**
 * Creación del grafo
 * @return Grafo construido
 */
Grafo leerGrafo(int const _v) {
    int e, v, w;
    std::cin >> e;
    Grafo g(_v);
    for (int i = 0; i < e; ++i) {
	std::cin >> v;
	std::cin >> w;
	g.ponArista(v, w);
    }

    return g;

}

/**
 * Función recursiva para comprobar si un grafo es un Árbol libre. Se hace una especie de recorrido en anchura
 * del grafo, comprobando que no existan ciclos (_marked) y que sea conexo (count). La complejidad es
 * O(|v|) , siendo |v| el número de vértices del grafo.
 * @param grafo sobre el que se quiere saber
 * @param s indice del nodo
 * @param count número de nodos visitados
 * @param last ultimo nodo visitado
 * @param _marked vector para conocer si los nodos han sido visitados previamente
 * @return 
 */
bool resuelve(Grafo const & grafo, size_t s, size_t &count, int const last, std::vector<bool> _marked) {
    ++count;
    if (count > grafo.V()) return false;
    _marked[s] = true;
    for (auto w : grafo.adj(s)) {
	if (w != last)
	    if (!_marked[w]) {
		if (!resuelve(grafo, w, count, s, _marked)) return false;
	    } else return false;

    }
    return true;
}

bool resuelve(Grafo const & grafo) {
    std::vector<bool> _marked(grafo.V());
    size_t s = 0, count = 0;

    if (resuelve(grafo, s, count, 0, _marked)) {
	if (count == grafo.V()) return true;
	else return false;
    } else return false;
}

void resolverCaso() {
    int v;
    std::cin >> v;
    while (std::cin) {
	auto grafo = leerGrafo(v);
	if (resuelve(grafo)) {
	    std::cout << "SI" << std::endl;
	} else {
	    std::cout << "NO" << std::endl;
	}
	std::cin >> v;
    }
}

int main() {
#ifndef DOMJUDGE

    std::ifstream in("casos.txt");

    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif

    resolverCaso();

#ifndef DOMJUDGE

    std::cin.rdbuf(cinbuf); //reset to standard input again

    //char ch;

    //std::cin >> ch;

    system("PAUSE");

#endif

    return 0;
}