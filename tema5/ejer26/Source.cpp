/**
* TAIS16. Álvar Soler y Samuel Lapuente
* Ejercicio 26.
*
**/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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
	Matriz<bool> posible(varillas.size(), L + 1, false);
	for (size_t i = 0; i < varillas.size(); ++i) {
		posible[i][0] = true;
	}
	for (size_t i = 1; i <= varillas.size() - 1; ++i) {
		for (size_t j = 1; j <= L; ++j) {
			if (varillas[i] > j) {
				posible[i][j] = posible[i - 1][j];
			}
			else {
				posible[i][j] = (posible[i - 1][j]) ? posible[i - 1][j] : posible[i - 1][j - varillas[i]];

			}
		}
	}
	return posible[varillas.size() - 1][L];
}

/*
* formas(i,j) devuelve la cantidad de formas de construir una varilla de tamaño j usando varillas desde la 1 hasta la i.
* formas(i-1,j) si li>j
* formas(i-1,j) + formas(i-1,j-li) si li<=j
* C.B. formas(0,j) = 0
* C.B. formas(i,0) = 1
* Llamada inicial formas(n,L) (que es donde estará nuestra solución en la tabla)
* la tabla se genera de izquierda a derecha y de arriba a abajo, ya que necesitamos las casillas de encima y encima a la izquierda para generar la
* casilla actual
*/
int formas(std::vector<int> const &varillas, const int L) {
	Matriz<int> formas(varillas.size(), L + 1, 0);
	for (size_t i = 0; i < varillas.size(); ++i) {
		formas[i][0] = 1;
	}
	for (size_t i = 1; i <= varillas.size() - 1; ++i) {
		for (size_t j = 1; j <= L; ++j) {
			if (varillas[i] > j) {
				formas[i][j] = formas[i - 1][j];
			}
			else {
				formas[i][j] = formas[i - 1][j] + formas[i - 1][j - varillas[i]];

			}
		}
	}
	return formas[varillas.size() - 1][L];
}

/*
* nVarillas(i,j) devuelve el minimo número de varillas para construir una varilla de tamaño j usando varillas desde la 1 hasta la i.
* nVarillas(i-1,j) si li>j
* minimo (nVarillas(i-1,j), nVarillas(i-1,j-li) si li<=j)
* C.B. nVarillas(0,j) = infinito
* C.B. nVarillas(i,0) = 0
* Llamada inicial nVarillas(n,L) (que es donde estará nuestra solución en la tabla)
* la tabla se genera de izquierda a derecha y de arriba a abajo, ya que necesitamos las casillas de encima y encima a la izquierda para generar la
* casilla actual
*/

int nVarillas(std::vector<int> const &varillas, const int L) {
	Matriz<int> nVarillas(varillas.size(), L + 1, 1e9);
	for (size_t i = 0; i < varillas.size(); ++i) {
		nVarillas[i][0] = 0;
	}
	for (size_t i = 1; i <= varillas.size() - 1; ++i) {
		for (size_t j = 1; j <= L; ++j) {
			if (varillas[i] > j) {
				nVarillas[i][j] = nVarillas[i - 1][j];
			}
			else {
				nVarillas[i][j] = std::min(nVarillas[i - 1][j], nVarillas[i - 1][j - varillas[i]] + 1);
			}
		}
	}
	return nVarillas[varillas.size() - 1][L];
}

/*
* precio(i,j) devuelve el minimo precio para construir una varilla de tamaño j usando varillas desde la 1 hasta la i.
* precio(i-1,j) si li>j
* minimo (precio(i-1,j), precio(i-1,j-li) si li<=j)
* C.B. precio(0,j) = infinito
* C.B. precio(i,0) = 0
* Llamada inicial precio(n,L) (que es donde estará nuestra solución en la tabla)
* la tabla se genera de izquierda a derecha y de arriba a abajo, ya que necesitamos las casillas de encima y encima a la izquierda para generar la
* casilla actual
*/

int precio(std::vector<int> const &varillas, const int L, std::vector<int> const &precios) {
	Matriz<int> precio(varillas.size(), L + 1, 1e9);
	for (size_t i = 0; i < varillas.size(); ++i) {
		precio[i][0] = 0;
	}
	for (size_t i = 1; i <= varillas.size() - 1; ++i) {
		for (size_t j = 1; j <= L; ++j) {
			if (varillas[i] > j) {
				precio[i][j] = precio[i - 1][j];
			}
			else {
				precio[i][j] = std::min(precio[i - 1][j], precio[i - 1][j - varillas[i]] + precios[i]);
			}
		}
	}
	return precio[varillas.size() - 1][L];
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif
	int n, L;
	std::cin >> n >> L;
	while (std::cin) {
	std::vector<int> v(n + 1, 0);
	std::vector<int> p(n + 1, 0);
	for (size_t i = 1; i < n + 1; ++i) {
		std::cin >> v[i];
		std::cin >> p[i];
	}

	if (esPosible(v, L)) std::cout << "SI " << formas(v, L) << " " << nVarillas(v, L) << " " << precio(v, L, p) << std::endl;
	else std::cout << "NO" << std::endl;
	std::cin >> n >> L;
	}


#ifndef DOMJUDGE

	std::cin.rdbuf(cinbuf); //reset to standard input again

	system("PAUSE");
#endif
	return 0;
}
