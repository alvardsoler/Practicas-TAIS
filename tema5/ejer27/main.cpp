/*
 *TAIS16 Alvar David Soler Rus y Samuel Lapuente Jiménez
 *
 *bool parentesisA(i,j) devuelve si es posible obtener una A con el intervalo entre i y j
 *bool parentesisB(i,j) devuelve si es posible obtener una B con el intervalo entre i y j
 *bool parentesisC(i,j) devuelve si es posible obtener una C con el intervalo entre i y j
 *-----------------------------------Recursión--------------------------------------------
 *parentesisA(i,j) = || i <= k <= j-1 {parentesisC(i,k) && parentesisA(k+1,j)
 *								 ||	parentesisA(i,k) && parentesisC(k+1,j)
 *								 || parentesisB(i,k) && parentesisC(k+1,j)}
 *
 *parentesisB(i,j) = || i <= k <= j-1 {parentesisA(i,k) && parentesisA(k+1,j) 
 *								 || parentesisA(i,k) && parentesisB(k+1,j)
 *								 || parentesisB(i,k) && parentesisB(k+1,j)}
 *
 *parentesisC(i,j) = || i <= k <= j-1 {parentesisB(i,k) && parentesisA(k+1,j) 
 *								 || parentesisC(i,k) && parentesisB(k+1,j)
 *								 || parentesisC(i,k) && parentesisC(k+1,j)}
 *---------------------------------Construcción de la Tabla-------------------------------
 *la casilla se construye mirando su casilla situada a la izquierda y su casilla inferior, esto es,
 *si la casilla a rellenar es la (i,j) miramos la casilla (i-1,j) y (i,j-1) y la solución está en la casilla
 *superior derecha de la tabla A.
 *Las tablas A, B y C se rellenan simultaneamente y es indiferente el orden, ya que sólo se requieren las casillas
 *de la iteración anterior para rellenar cada tabla.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include<vector>
#include"Matriz.h"

bool resuelve(std::string & cadena) {
    size_t n = cadena.size();
    Matriz<bool> mA(n + 1, n + 1, false);
    Matriz<bool> mB(n + 1, n + 1, false);
    Matriz<bool> mC(n + 1, n + 1, false);

    for (size_t p = 0; p < n; ++p) {
	if (cadena[p] == 'a') {
	    mA[p + 1][p + 1] = true;
	    mB[p + 1][p + 1] = false;
	    mC[p + 1][p + 1] = false;
	}
	if (cadena[p] == 'b') {
	    mA[p + 1][p + 1] = false;
	    mB[p + 1][p + 1] = true;
	    mC[p + 1][p + 1] = false;
	}
	if (cadena[p] == 'c') {
	    mA[p + 1][p + 1] = false;
	    mB[p + 1][p + 1] = false;
	    mC[p + 1][p + 1] = true;
	}
    }

    for (size_t d = 1; d <= n - 1; ++d) {
	for (size_t i = 1; i <= n - d; ++i) {
	    size_t j = i + d;
	    for (size_t k = i; k <= j - 1; ++k) {
		//a
		bool auxA = mC[i][k] && mA[k + 1][j] || mA[i][k] && mC[k + 1][j] || mB[i][k] && mC[k + 1][j];
		if (auxA) mA[i][j] = auxA;
		//b
		bool auxB = mA[i][k] && mA[k + 1][j] || mA[i][k] && mB[k + 1][j] || mB[i][k] && mB[k + 1][j];
		if (auxB) mB[i][j] = auxB;
		//c
		bool auxC = mB[i][k] && mA[k + 1][j] || mC[i][k] && mB[k + 1][j] || mC[i][k] && mC[k + 1][j];
		if (auxC) mC[i][j] = auxC;

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
	if (resuelve(cadena)) std::cout << "SI" << std::endl;
	else std::cout << "NO" << std::endl;
	getline(std::cin, cadena);
    }

#ifndef DOMJUDGE

    std::cin.rdbuf(cinbuf); //reset to standard input again


    system("PAUSE");

#endif

    return 0;
}
