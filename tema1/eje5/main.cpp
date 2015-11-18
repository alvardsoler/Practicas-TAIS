/*
 * Grupo TAIS16, Samuel Lapuente Jiménez, Alvar David Soler Rus
 *Ejercicio 5 del Tema 1.
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
#include "TreeMap_AVL.h"

/**
 * Se carga el número de líneas del caso de prueba, y si no es el caso de salida, comenzamos:
 * se crea un arbol AVL con clave un string y como valor una lista de enteros sin signo. Si la palabra leída
 * no está introducida previamente en el árbol, la introducimos con una lista cuyo único valor es esa línea del
 * texto. En caso de ya estar introducida y que el último valor de la lista no coincida con la línea del texto
 * donde está la palabra, añadimos esa línea al final de la lista. Al final de leer todo el texto, recorremos
 * el árbol en inorden mostrando la clave y sus valores asociados. El coste estimamos que es O(2*logN) el bucle
 * +O(N) de leer para la salida, siendo N el número de nodos.
 */
void resuelve() {
    unsigned int n;
    std::cin >> n;
    std::string line;
    std::string word;
    while (n != 0) {
	TreeMap<std::string, std::list<unsigned int>, std::less < std::string>> arbol;
	std::getline(std::cin, line);
	for (std::size_t i = 1; i < n + 1; i++) {
	    std::getline(std::cin, line);	   
	    std::istringstream iss(line);
	    while (iss >> word) {
		if (word.length() > 2) {
		    try {
			std::transform(word.begin(), word.end(), word.begin(), ::tolower);
			std::list<unsigned int> aux = arbol.at(word);
			unsigned int aux2 = aux.back();
			if (!aux.empty() && aux2 != i) {
			    aux.push_back(i);
			    arbol.insert(word, aux);
			}
		    } catch (std::out_of_range e) {
			std::list<unsigned int> list;
			list.push_back(i);
			arbol.insert(word, list);
		    }
		}
	    }
	}
	TreeMap<std::string, std::list<unsigned int>, std::less < std::string>>::Iterator it(arbol.begin());
	while (it != arbol.end()) {
	    TreeMap<std::string, std::list<unsigned int>, std::less < std::string>>::ClaveValor cv(it.operator*());
	    std::cout << cv.clave;
	    for (std::list<unsigned int>::iterator it = cv.valor.begin(); it != cv.valor.end(); ++it)
		std::cout << ' ' << *it;
	    std::cout << std::endl;
	    it.operator++();
	}
	arbol.~TreeMap();
	std::cout << "----" << std::endl;
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
