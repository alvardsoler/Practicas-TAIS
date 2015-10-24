/*
 * Grupo TAIS16, Samuel Lapuente Jiménez, Alvar David Soler Rus
 * 
 * Ejercicio 6. Tema 2.
 * 
 */


#include <iostream>
#include <fstream>
#include <cstdlib>
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

bool resuelve(BinTree<int> const & arbol, int const valPadre, int const altIzq , int const altDer) {    
    if (arbol.empty()) return true;
    
    if (arbol.left().empty() && arbol.right().empty()) return true;
    if (arbol.left().empty() && !arbol.right().empty()) return false;
    if (arbol.root() < valPadre) return false;
    else {	
	if (resuelve(arbol.left(), arbol.root()) && resuelve(arbol.right(), arbol.root())) return true;

    }



}

// completo: vacio || (completo(iz) && completo(der) && (altura(iz) == altura(der))
// semi-completo: vacio || ( (completo(arbol) || ( (altura(iz) == altura(der) && completo(iz) && semi-compelto(der)) || (altura(iz) == altura(der) +1 && semicompelto(iz) && compelto(der)) )
// monticulo: vacio || ( semicompleto(arbol) || menor-igual(raiz,iz) && menor-igual(raiz,der) && monticulo(iz) && monticulo(der) )


bool esCompleto(BinTree<int> const & arbol){
    
}

void resolverCaso() {
    auto arbol = leerArbol();
    int a = 0;
    //    for (int value : arbol)
    //	std::cout << value << std::endl;
    //    std::cout << "---" << std::endl;
    if (resuelve(arbol, arbol.root())) {
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