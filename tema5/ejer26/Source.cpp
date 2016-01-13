/**
* TAIS16. Álvar Soler y Samuel Lapuente
* Ejercicio 25.
*
**/
#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"


/*
* posible(i,j) devuelve si se puede construir la varilla de tamaño j usando varillas desde la 1 hasta la i.
* posible(i-1,j) si li>j
* posible(i-1,j) || posible(i-1,j-li) si li<=j
* C.B. posible(0,j) = false
* C.B. posible(i,0) = true
* Llamada inicial posible(n,L) (que es donde estará nuestra solución en la tabla)
* la tabla se genera de izquierda a derecha y de arriba a abajo, ya que necesitamos las casillas de encima y encima a la izquierda para generar la 
* casilla actual
*/
bool esPosible(std::vector<int> const &varillas, const int L) {
	Matriz<bool> posible(varillas.size(), L+1, false);
	for (size_t i = 0; i < varillas.size(); ++i) {
		posible[i][0] = true;
	}
	for (size_t i = 1; i <= varillas.size() - 1; ++i) {
		for (size_t j = 1; j <= L; ++j) {
			if (varillas[i] > j) {
				posible[i][j] = posible[i - 1][j];
			}
			else {
				posible[i][j] = (posible[i - 1][j]) ? posible[i - 1][j] : posible[i - 1][j-varillas[i]];

			}
		}
	}
	return posible[varillas.size() - 1][L];
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif
	int n, L, a, b;
	std::cin >> n >> L;
	std::vector<int> v(n+1,0);
	for (size_t i = 1; i < n+1; ++i) {
		std::cin >> v[i];
		std::cin >> a;
	}
	if (esPosible(v,L)) std::cout << "si" << std::endl;
	else std::cout << "no" << std::endl;

#ifndef DOMJUDGE

	std::cin.rdbuf(cinbuf); //reset to standard input again

	system("PAUSE");
#endif
	return 0;
}