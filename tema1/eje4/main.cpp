/*
 * Grupo TAIS16, Samuel Lapuente Jiménez, Alvar David Soler Rus
 *Ejercicio 4 del Tema 1.
 * 
 *  */
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <cstdlib>
#include <climits>
#include <sstream>
#include <stdio.h>
#include "TreeMap_AVLK.h"


void resuelve() {
    unsigned int n;
    std::cin >> n;
    int val;
    int m;
    int k;
    while (n != 0) {
	TreeMap<int, int, std::less<int>> arbol;
	for ( int i = 0; i < n; i++) {
	    std::cin >> val;
	    arbol.insert(val, val);
	}
//	arbol.print(std::cout);

	std::cin >> m;
	for ( int j = 0; j < m; j++) {
	    std::cin >> k;
	    std::cout << "k: " << k << std::endl;
	}
	std::cin >> n;
    }

}

int main() {
#ifndef DOMJUDGE

    std::ifstream in("caso.txt");

    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif
    resuelve();

#ifndef DOMJUDGE

    std::cin.rdbuf(cinbuf); //reset to standard input again

    system("PAUSE");

#endif

    return 0;
}