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

PriorityQueue<unsigned long long int> leer(int const n) {
    PriorityQueue<unsigned long long int,std::less<unsigned long long int>> ret;
    int aux;
    for (int i = 0; i < n; i++) {
	std::cin >> aux;
	ret.push(aux);
    }
    return ret;
}

unsigned long resuelve(PriorityQueue<unsigned long long int, std::less<unsigned long long int>> &cola) {
    if (cola.size() == 1) return 0;
//    PriorityQueue<unsigned long long int> colaAux;
    unsigned long long int aux1;
    unsigned long long int aux2;
    unsigned long long int tot = 0;
    while (cola.size() > 1) {
	aux1 = cola.top();
	cola.pop();
	aux2 = cola.top();
	cola.pop();
//	colaAux.push((aux1 + aux2));
	cola.push((aux1 + aux2));
	tot += aux1 + aux2;
    }
//    while (colaAux.size() > 1) {
//	aux1 = colaAux.top();
//	colaAux.pop();
//	aux2 = colaAux.top();
//	colaAux.pop();
//	colaAux.push((aux1 + aux2));
//    }

//    return colaAux.top();
    return tot;
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
