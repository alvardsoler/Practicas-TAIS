/*
*
* TAIS 16 Álvar Soler Rus y Samuel Lapuente Jiménez
* Ejercicio 34
*
* Explicación: comer(i,j) cantidad máxima que come Listilla de los cubos desde el cubo i hasta el cubo j
*
* CB par -> comer(i,i+1) return max(cubos[i][i+1]
* CB impar -> comer(i,i) return cubos[i]
*
* Recursión
* comer(i, j) = max { cubos[i] + comer(i+1, j-1), cubos[j] + comer(i+1, j-1)}
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
    Matriz<int> vacas(n+1, n+1, 0);

    if (n == 1) return cubos[1];
    if (n == 2) return std::max(cubos[1], cubos[2]);
    size_t f = 0;
   
    if (n % 2 == 0){ // pares
        for (size_t i = 1; i < n; ++i)
            vacas[i][i + 1] = std::max(cubos[i], cubos[i + 1]);
        f = 3;
    }
    else{ //impares
        for (size_t i = 1; i < n; ++i)
            vacas[i][i] = cubos[i];
        f = 2;       
    }

    for (size_t d = f; d < n; d += 2) {
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
