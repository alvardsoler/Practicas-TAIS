/* 
 *
 * TAIS 16 Álvar Soler Rus y Samuel Lapuente Jiménez 
 * Ejercicio 32
 *
 * Explicación:
 * cortes(i,j) := coste mínimo de cortar un liston de tamaño j desde i
 * 
 * Caso base:
 * cortes(i, i+1) = esfuerzo(i,i+1)
 * Caso recursivo:
 * cortes(i, j) = min { cortes(i,j) , (i < k < j) (cortes(i,k) + cortes(k+1, j))}
 *
 */

#include <iostream>
#include <cstdio>
#include "Matriz.h"
#include <fstream>
#include <climits>
#include <algorithm>
#include <cstdlib>


int cortes(const int distancias[], unsigned int n) {
    Matriz<int> matrizEsfuerzos(n + 2, n + 2);
    Matriz<int> matrizCortes(n + 2, n + 2);

    for (int c = 2; c < n + 2; c++) { // diferencia entre i y j
	int j = 0;
	for (int i = 0; i + c < n + 2; i++) {
	    int mejor = INT_MAX;
	    int aux;
	    j = i + c;
	    for (int k = i + 1; k < j; k++) {
		aux = matrizEsfuerzos[i][k] + matrizEsfuerzos[k][j];
		if (aux < mejor) {
		    mejor = aux;
		    matrizCortes[i][j] = k;
		}
	    }
	    mejor += 2 * (distancias[j] - distancias[i]);
	    matrizEsfuerzos[i][j] = mejor;
	}
    }

    return matrizEsfuerzos[0][n + 1];

}

int main() {

#ifndef DOMJUDGE
    std::ifstream in("casos.txt");

    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif
    /* Para cada problema */    
    unsigned int l;
    std::cin >> l;
    int caso = 1;
    unsigned int n;
    std::cin >> n;
    while (l != 0 && n != 0) {

	int distanciaCortes[n + 2];

	for (int i = 1; i <= n; i++) {
	    std::cin >> distanciaCortes[i];
	}

	distanciaCortes[0] = 0;
	distanciaCortes[n + 1] = l;


	std::cout << cortes(distanciaCortes, n) << std::endl;
	caso++;
	std::cin >> l;
	std::cin >> n;
    }
#ifndef DOMJUDGE

    std::cin.rdbuf(cinbuf); //reset to standard input again


    system("PAUSE");

#endif

    return 0;


    return 0;
}
