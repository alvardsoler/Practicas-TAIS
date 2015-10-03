
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include "BinTree.h"

/**
* Creaci�n del �rbol binario
* @return BinTree construido
*/

/* Vamos a aprovechar nuestra soluci�n del ejercicio anterior ya que una de las condiciones necesarias es que el �rbol sea un �rbol equilibrado.
Como esta situaci�n la tenemos contemplada en estas funciones y ya es correcto, podremos centrarnos en la otra condici�n para que sea un �rbol AVL, esto es, 
que sea de b�squeda (los elementos de la izquierda menores que la r��z y los de la derecha mayores)*/

BinTree<int> leerArbol() {
	int raiz;
	std::cin >> raiz;
	if (raiz == -1) {
		// es un �rbol vac�o
		return
		{};
	}
	else {
		// leer recursivamente los hijos
		auto iz = leerArbol();
		auto dr = leerArbol();
		return
		{
			iz, raiz, dr
		};
	}
}

int altura(BinTree<int> const & arbol) {
	if (arbol.empty()) {
		return 0;
	}
	else {
		return 1 + std::max(altura(arbol.left()), altura(arbol.right()));
	}
}

bool resuelveAltura(BinTree<int> const & arbol) {
	if (arbol.empty()) return true;
	if (resuelveAltura(arbol.left()) && resuelveAltura(arbol.right())) {
		int alturaDer = altura(arbol.right());
		int alturaIzq = altura(arbol.left());
		if (std::abs(alturaDer - alturaIzq) <= 1) return true;
		else return false;
	}
	else {
		return false;
	}
}

/*Ahora comenzamos a comprobar que sea de b�squeda. Este m�todo ya comprueba que adem�s est� balanceado, si no devuelve false*/

bool resuelveBusqueda(BinTree<int> const & arbol) {
	if (resuelveAltura(arbol) == true) {
		if (arbol.empty()) return true;
		if (resuelveBusqueda(arbol.left()) && resuelveBusqueda(arbol.right())) {
			if ((arbol.root() > arbol.left().root()) && (arbol.root() < arbol.right().root())) return true;
			else return false;
		}
	}
	else return false;
}

void resolverCaso() {
	auto arbol = leerArbol();
	if (resuelveBusqueda(arbol)) {
		std::cout << "SI" << std::endl;
	}
	else {
		std::cout << "NO" << std::endl;
	}
}

int main() {
#ifndef DOMJUDGE

	std::ifstream in("caso.txt"); //no s� por qu� no lee nada del archivo y s� que est� bien colocado

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