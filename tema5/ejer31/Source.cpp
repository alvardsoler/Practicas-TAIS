/*
 * TAIS16 Alvar David Soler Rus y Samuel Lapuente Jiménez ejercicio 31
 * 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include "Matriz.h"

/*
 * 
 * monedas(i,j) = monedas(i-1,j) si vi > j
 * 
 * 
 * 
 * 
monedas(i,j) = min(mon(i-1,j),mon(i-1,j - k*v[i])+k 1<=k<=cantida(i)
si j<=tipo(i)
monedas(i,j)=monedas(i-1,j);
desde k=1 hasta cantidad(i){
    temp = mon(i-1,j - k*v[i])+k 1<=k<=cantida(i);
    if(temp < monedas(i,j)){
        monedas(i,j)=temp
}
}
	
 */

int monedas(std::vector<int> & monedas, std::vector<int> & cantidad, int const precio) {
    size_t n = monedas.size() - 1;
    Matriz<int> matriz(n + 1, precio + 1, 1e9);

    for (size_t i = 1; i <= n; ++i)
        matriz[i][0] = 0;

    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= precio; ++j) {
            if (j < monedas[i]) {
                matriz[i][j] = matriz[i - 1][j];
            } else {
                size_t temp = 0;
                int aux = (int) ((int) precio / (int) monedas[i]);
                if (aux > cantidad[i]) aux = cantidad[i];

                for (size_t k = 0; k <= aux; ++k) {
                    temp = matriz[i - 1][j - k * monedas[i]] + k;
                    if (temp < matriz[i][j])
                        matriz[i][j] = temp;
                }

            }
        }
    }

    return matriz[n][precio];
}

int main() {
#ifndef DOMJUDGE

    std::ifstream in("casos.txt");

    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif

    int n, C;
    std::cin >> n;
    while (std::cin) {
        std::vector<int> m(n + 1), cantidades(n + 1);
        for (size_t i = 1; i <= n; ++i) std::cin >> m[i];
        for (size_t i = 1; i <= n; ++i) std::cin >> cantidades[i];
        std::cin >> C;
        size_t r = monedas(m, cantidades, C);
        if (r != 1e9)
            std::cout << "SI " << r << std::endl;
        else
            std::cout << "NO" << std::endl;
        std::cin >> n;
    }

#ifndef DOMJUDGE

    std::cin.rdbuf(cinbuf); //reset to standard input again


    system("PAUSE");

#endif

    return 0;
}
