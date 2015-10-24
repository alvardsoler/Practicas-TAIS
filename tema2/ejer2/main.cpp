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

PriorityQueue<unsigned long int, std::less<unsigned int>> leer(int const n) {
    PriorityQueue<unsigned long int, std::less<unsigned int>> ret;
    int aux;
    for (int i = 0; i < n; i++) {
	std::cin >> aux;
	ret.push(aux);
    }
    return ret;
}

unsigned long resuelve(PriorityQueue<unsigned long int, std::less<unsigned int>> cola) {
    PriorityQueue<unsigned long int, std::less<unsigned int>> colaAux;
    unsigned long int aux1;
    unsigned long int aux2;
    while (cola.size() > 1) {
	aux1 = cola.top();
	cola.pop();
	aux2 = cola.top();
	cola.pop();
	colaAux.push((unsigned long) (aux1 + aux2));
	cola.push((unsigned long) (aux1 + aux2));
    }
    while (colaAux.size() > 1) {
	aux1 = colaAux.top();
	colaAux.pop();
	aux2 = colaAux.top();
	colaAux.pop();
	colaAux.push((unsigned long) (aux1 + aux2));
    }
    return colaAux.top();
}

void resolverCaso() {
    int n;
    std::cin >> n;
    while (n != 0) {
	auto cola = leer(n);
	std::cout << resuelve(cola) << std::endl;
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

    system("PAUSE");

#endif

    return 0;
}
