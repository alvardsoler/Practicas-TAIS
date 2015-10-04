
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include "BinTree.h"

/**
* Creación del árbol binario
* @return BinTree construido
*/

/* Vamos a aprovechar nuestra solución del ejercicio anterior ya que una de las condiciones necesarias es que el árbol sea un árbol equilibrado.
Como esta situación la tenemos contemplada en estas funciones y ya es correcto, podremos centrarnos en la otra condición para que sea un árbol AVL, esto es, 
que sea de búsqueda (los elementos de la izquierda menores que la ráíz y los de la derecha mayores)*/

BinTree<int> leerArbol() {
	int raiz;
	std::cin >> raiz;
	if (raiz == -1) {
		// es un árbol vacío
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


/*Con este método vamos comprobando que la parte derecha del árbol es mayor que su raíz. Es necesario comprobar dos veces que no sea vacío tal y como lo estamos implementando para no entrar en la excepción*/

bool mayor(BinTree<int> const & arbol) {
	if (arbol.empty()) {
		return true;
	}
	else if (!arbol.right().empty()) {
		if (arbol.right().root() < arbol.root()) return false;
		else return mayor(arbol.right());
	}
	else return true;
}  

/*Este método es equivalente a mayor pero mirando que la parte izquierda sea menor que la raíz*/

bool menor(BinTree<int> const & arbol) {
	if (arbol.empty()) {
		return true;
	}
	else if (!arbol.left().empty()) {
		if (arbol.left().root() > arbol.root()) return false;
		else return menor(arbol.left());
	}
	else return true;
}

/*Ahora comenzamos a comprobar que sea de búsqueda. Este método ya comprueba que además esté balanceado, si no devuelve false*/

bool resuelveBusqueda(BinTree<int> const & arbol) {
	if (resuelveAltura(arbol) == true) {
		if (arbol.empty()) return true;
		if ((mayor(arbol.right())) && menor(arbol.left())) return true;
		else return false;
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