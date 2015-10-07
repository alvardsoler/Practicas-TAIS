/*
 * Grupo TAIS16, Samuel Lapuente Jim�nez, Alvar David Soler Rus
 * Soluci�n: una funci�n recursiva que recorre el �rbol comprobando que est� ordenado (hijos izquierdos
 * menores que la raiz del padre e hijos derechos mayores que la raiz del padre) y que est� balanceado
 * (la diferencia entre alturas de las ramas no puede ser mayor que uno).
 * 
 *  */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include "BinTree.h"

/**
 * 
 * Creaci�n del �rbol binario
 * @return BinTree construido
 */
BinTree<int> leerArbol() {
    int raiz;
    std::cin >> raiz;
    if (raiz == -1) {
	return
	{
	};
    } else {
	auto iz = leerArbol();
	auto dr = leerArbol();
	return
	{
	    iz, raiz, dr
	};
    }
}

/**
 * Funci�n principal. Si la raiz es vac�a no hay nada que hacer. En otro caso,
 * comprobamos que la raiz est� entre el valor m�nimo y m�ximo (inicializados como el m�ximo  y m�nimo 
 * valor posible de una variable int), y si es as� comprobamos que la diferencia de alturas de las dos ramas
 * cumple la condici�n para ser balanceado. En caso de que alguna de estas condiciones no se cumpla, 
 * sabemos que el �rbol no es AVL.  Complejidad O(n) siendo n el n�mero de nodos.
 * @param arbol que se quiere analizar
 * @param alt altura maxima de las ramas del arbol
 * @param min valor m�nimo entre  el que se tiene que encontrar la raiz
 * @param max valor maximo entre  el que se tiene que encontrar la raiz
 * @return si el arbol es AVL o no
 */
bool resuelve(BinTree<int> const & arbol, int &alt, int min, int max) {
    if (arbol.empty()) {
	return true;
    } else {
	if (arbol.root() < max && arbol.root() > min) {
	    int auxI, auxD;
	    auxI = alt;
	    auxD = alt;
	    if (!resuelve(arbol.left(), auxI, min, arbol.root())) return false;
	    if (!resuelve(arbol.right(), auxD, arbol.root(), max)) return false;
	    if (std::abs(auxI - auxD) <= 1) {
		alt = 1 + std::max(auxI, auxD);
		return true;
	    } else return false;
	} else return false;
    }
}

void resolverCaso() {
    auto arbol = leerArbol();
    int a = 0;
    if (resuelve(arbol, a, INT_MIN, INT_MAX)) {
	std::cout << "SI" << std::endl;
    } else {
	std::cout << "NO" << std::endl;
    }
}

int main() {
#ifndef DOMJUDGE

    std::ifstream in("caso.txt");

    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
	resolverCaso();

#ifndef DOMJUDGE

    std::cin.rdbuf(cinbuf); //reset to standard input again

    system("PAUSE");

#endif

    return 0;
}
