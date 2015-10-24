/*
 * Grupo TAIS16, Samuel Lapuente Jiménez, Alvar David Soler Rus
 * 
 * Ejercicio 6. Tema 2.
 * 
 */


#include <iostream>
#include <fstream>
#include <cstdlib>
#include "PriorityQueue.h"

void resolverCaso() {
    int n;
    std::cin >> n;
    unsigned long aux1;
    unsigned long aux2;

    while (n != 0) {
	PriorityQueue<unsigned long, std::less<unsigned int>> cola;
	PriorityQueue<unsigned long, std::less<unsigned int>> colaAux;
	int aux;
	for (int i = 0; i < n; i++) {
	    std::cin >> aux;
	    cola.push(aux);
	}
	while (cola.size() > 1) {
	    aux1 = cola.top();
	    cola.pop();
	    aux2 = cola.top();
	    cola.pop();
	    colaAux.push((aux1 + aux2));
	    cola.push((aux1 + aux2));
	}
	while (colaAux.size() > 1) {
	    aux1 = colaAux.top();
	    colaAux.pop();
	    aux2 = colaAux.top();
	    colaAux.pop();
	    colaAux.push((aux1 + aux2));
	}
	std::cout << colaAux.top() << std::endl;
	std::cin >> n;
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
