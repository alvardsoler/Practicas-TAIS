/*
 * Grupo TAIS16, Samuel Lapuente Jiménez, Alvar David Soler Rus
 *
 * Ejercicio 11. Tema 3.
 *
 */


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
#include "Grafo.h"
#include "ManchasCrecientes.h"


void resolverCaso() {
    while (std::cin) {
        int _f, _c;
        std::cin >> _f;
        std::cin >> _c;
        ManchasCrecientes mc(_f, _c);
        std::cout << mc.getComponenteMayor();
        while (mc.leerMancha()) {
            std::cout << mc.getComponenteMayor() << " ";
        }
        std::cout << std::endl;
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
