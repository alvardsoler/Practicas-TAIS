/*
 * Grupo TAIS16, Samuel Lapuente Jiménez, Alvar David Soler Rus
 *
 * Ejercicio 8. Tema 2.
 *
 */
#include <fstream>
#include <cstdlib>
#include "ColaUrgencias.h"

void resolverCaso() {
    unsigned int n;
    std::cin >> n;
    std::string nombre;
    unsigned int gravedad;
    char t;
    while (n != 0) {
	ColaUrgencias cola;
	for (unsigned int i = 0; i < n; ++i) {
	    std::cin >> t;
	    if (t == 'I') {
		std::cin >> nombre;
		std::cin >> gravedad;
		cola.insertar(nombre, gravedad);
	    } else if (t == 'A') {
		std::cout << cola.nombrePrimero() << std::endl;
		cola.quitarPrimero();
	    }
	}
	std::cout << "----" << std::endl;
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