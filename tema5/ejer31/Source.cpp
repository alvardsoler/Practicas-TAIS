/*
*TAIS16 Alvar David Soler Rus y Samuel Lapuente Jiménez ejercicio 28
*
*int formasA(i,j) devuelve el numero de formas de obtener una A con el intervalo entre i y j
*int formasB(i,j) devuelve el numero de formas de obtener una B con el intervalo entre i y j
*int formasC(i,j) devuelve el numero de formas de obtener una C con el intervalo entre i y j
*-----------------------------------Recursión--------------------------------------------
*formasA(i,j) = + i <= k <= j-1 {formasC(i,k) * formasA(k+1,j)
*								 +	formasA(i,k) * formasC(k+1,j)
*								 + formasB(i,k) * formasC(k+1,j)}
*
*formasB(i,j) = + i <= k <= j-1 {formasA(i,k) * formasA(k+1,j)
*								 + formasA(i,k) * formasB(k+1,j)
*								  +formasB(i,k) * formasB(k+1,j)}
*
*formasC(i,j) = + i <= k <= j-1 {formasB(i,k) * formasA(k+1,j)
*								 + formasC(i,k) * formasB(k+1,j)
*								 + formasC(i,k) * formasC(k+1,j)}
*---------------------------------Construcción de la Tabla-------------------------------
*la casilla se construye mirando su casilla situada a la izquierda y su casilla inferior, esto es,
*si la casilla a rellenar es la (i,j) miramos la casilla (i-1,j) y (i,j-1) y la solución está en la casilla
*superior derecha de la tabla A.
*Las tablas A, B y C se rellenan simultaneamente y es indiferente el orden, ya que sólo se requieren las casillas
*de la iteración anterior para rellenar cada tabla.
* CB formasA(i,i) = 1 si i=a else = 0
* CB formasB(i,i) = 1 si i=b else = 0
* CB formasC(i,i) = 1 si i=c else = 0
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include "Matriz.h"

int monedas(std::vector<int> & monedas, std::vector<int> & cantidad, int const precio){
	size_t n = monedas.size() - 1;
	Matriz<int> matriz(n + 1, precio + 1, 1e9);
	
	for (size_t i = 0; i <= n; ++i)
		matriz[i][0] = 0;

	for (size_t i = 1; i <= n; ++i){
		for (size_t j = 1; j <= precio; ++j){
			if (monedas[i] > j || cantidad[i] == 0)
				matriz[i][j] = matriz[i - 1][j];
			else{
				if (matriz[i - 1][j] < matriz[i][j - monedas[i]] + 1) matriz[i][j] = matriz[i - 1][j];
				else { matriz[i][j] = matriz[i][j - monedas[i]] + 1; --cantidad[i]; }				
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
		std::vector<int> m(n), cantidades(n);
		for (size_t i = 0; i < n; ++i) std::cin >> m[i];
		for (size_t i = 0; i < n; ++i) std::cin >> cantidades[i];
		std::cin >> C;
		std::cout << monedas(m, cantidades, C) << std::endl;
		std::cin >> n;
	}

#ifndef DOMJUDGE

	std::cin.rdbuf(cinbuf); //reset to standard input again


	system("PAUSE");

#endif

	return 0;
}