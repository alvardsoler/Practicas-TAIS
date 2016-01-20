/*
*TAIS16 Alvar David Soler Rus y Samuel Lapuente Jiménez ejercicio 27
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
#include <cstdlib>
#include <vector>
#include"Matriz.h"

int formas(std::string & cadena) {
	size_t n = cadena.size();
	Matriz<int> mA(n + 1, n + 1, 0);
	Matriz<int> mB(n + 1, n + 1, 0);
	Matriz<int> mC(n + 1, n + 1, 0);

	for (size_t p = 0; p < n; ++p) {
		if (cadena[p] == 'a') {
			mA[p + 1][p + 1] = 1;
			mB[p + 1][p + 1] = 0;
			mC[p + 1][p + 1] = 0;
		}
		if (cadena[p] == 'b') {
			mA[p + 1][p + 1] = 0;
			mB[p + 1][p + 1] = 1;
			mC[p + 1][p + 1] = 0;
		}
		if (cadena[p] == 'c') {
			mA[p + 1][p + 1] = 0;
			mB[p + 1][p + 1] = 0;
			mC[p + 1][p + 1] = 1;
		}
	}

	for (size_t d = 1; d <= n - 1; ++d) {
		for (size_t i = 1; i <= n - d; ++i) {
			size_t j = i + d;
			for (size_t k = i; k <= j - 1; ++k) {
				//a
				mA[i][j] += mC[i][k] * mA[k + 1][j] + mA[i][k] * mC[k + 1][j] + mB[i][k] * mC[k + 1][j];
				//b
				mB[i][j] += mA[i][k] * mA[k + 1][j] + mA[i][k] * mB[k + 1][j] + mB[i][k] * mB[k + 1][j] ;
				//c
				mC[i][j] += mB[i][k] * mA[k + 1][j] + mC[i][k] * mB[k + 1][j] + mC[i][k] * mC[k + 1][j] ;
			}
		}
	}
	return mA[1][n];
}

int main() {
#ifndef DOMJUDGE

	std::ifstream in("casos.txt");

	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif

	std::string cadena;
	getline(std::cin, cadena);
	while (std::cin) {
		std::cout << formas(cadena) << std::endl;
		getline(std::cin, cadena);
	}

#ifndef DOMJUDGE

	std::cin.rdbuf(cinbuf); //reset to standard input again


	system("PAUSE");

#endif

	return 0;
}
