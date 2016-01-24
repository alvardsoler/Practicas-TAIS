/* 
 *
 * TAIS 16 Álvar Soler Rus y Samuel Lapuente Jiménez 
 * Ejercicio 34
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
#include <fstream>
#include <cstdlib>
#include <vector>
#include "Matriz.h"
#include <algorithm>

int comer(std::vector<int> const & cubos, int const n) {
    Matriz<int> vacas(n, n, 0);

    if (n == 1) return cubos[1];
    if (n == 2) return std::max(cubos[1], cubos[2]);

    for (size_t i = 1; i < n; ++i)
	vacas[i][i + 1] = std::max(cubos[i], cubos[i + 1]);


    for (size_t d = 3; d < n; d += 2) {
	for (size_t i = 1; i <= n - d; ++i) {
	    size_t j = i + d;
	    size_t comoi, comoj;
	    comoi = comoj = 0;
	    if (cubos[j] > cubos[i + 1]) comoi = vacas[i + 1][j - 1];
	    else comoi = vacas[i + 2][j];

	    if (cubos[i] > cubos[j - 1]) comoj = vacas[i + 1][j - 1];
	    else comoj = vacas[i][j - 2];

	    vacas[i][j] = std::max(cubos[i] + comoi, cubos[j] + comoj);
	}
    }

    return vacas[1][n];

}

int main() {

#ifndef DOMJUDGE
    std::ifstream in("casos.txt");

    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif

    unsigned int n;
    std::cin >> n;

    while (n != 0) {
	std::vector<int> cubos(n + 1);
	cubos[0] = 0;
	for (int i = 1; i <= n; i++) {
	    std::cin >> cubos[i];
	}


	std::cout << comer(cubos, n) << std::endl;

	std::cin >> n;
    }

#ifndef DOMJUDGE

    std::cin.rdbuf(cinbuf); //reset to standard input again


    system("PAUSE");

#endif

    return 0;
}

