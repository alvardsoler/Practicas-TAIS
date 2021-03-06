/*
 * Grupo TAIS16, Samuel Lapuente Jiménez, Alvar David Soler Rus
 * 
 * Ejercicio 6. Tema 2.
 * 
 */


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
#include "BinTree.h"

/**
 * Creación del árbol binario
 * @return BinTree construido
 */
BinTree<int> leerArbol() {
    int raiz;
    std::cin >> raiz;
    if (raiz == -1) {
	// es un árbol vacío
	return
	{
	};
    } else {
	// leer recursivamente los hijos
	auto iz = leerArbol();
	auto dr = leerArbol();
	return
	{
	    iz, raiz, dr
	};
    }
}

bool resuelve(BinTree<int> const & arbol, int const valPadre, int &alt) {
    if (arbol.empty()) return true;
    else {
	if (arbol.root() >= valPadre) {
	    int auxI, auxD;
	    auxI = alt;
	    auxD = alt;
	    if (!resuelve(arbol.left(), arbol.root(), auxI)) return false;
	    if (!resuelve(arbol.right(), arbol.root(), auxD)) return false;
	    if (auxI == auxD || auxI == auxD + 1) {
		alt = 1 + std::max(auxI, auxD);
		return true;
	    } else return false;
	} else return false;
    }
}

// completo: vacio || (completo(iz) && completo(der) && (altura(iz) == altura(der))
// semi-completo: vacio || ( (completo(arbol) || ( (altura(iz) == altura(der) && completo(iz) && semi-compelto(der)) || (altura(iz) == altura(der) +1 && semicompelto(iz) && compelto(der)) )
// monticulo: vacio || ( semicompleto(arbol) || menor-igual(raiz,iz) && menor-igual(raiz,der) && monticulo(iz) && monticulo(der) )

void resolverCaso() {
    auto arbol = leerArbol();
    int a = 0;
    //    for (int value : arbol)
    //	std::cout << value << std::endl;
    //    std::cout << "---" << std::endl;
    if (resuelve(arbol, INT_MIN, a)) {
	std::cout << "SI" << std::endl;
    } else {
	std::cout << "NO" << std::endl;
    }
}

int main() {
#ifndef DOMJUDGE

    std::ifstream in("casos.txt");

    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
	resolverCaso();

#ifndef DOMJUDGE

    std::cin.rdbuf(cinbuf); //reset to standard input again

    //char ch;

    //std::cin >> ch;

    system("PAUSE");

#endif

    return 0;
}
