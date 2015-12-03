/**
* TAIS16. Álvar Soler y Samuel Lapuente
* Ejercicio 19.
*
**/

#include <iostream>
#include <vector>
#include <fstream>


int  resuelve(std::vector<int > const & agujeros, int const longitud){
	int r = 1;
	int  anterior = agujeros[0];
	for (std::size_t i = 1; i < agujeros.size(); ++i){
		if (agujeros[i] - anterior > longitud){
			anterior = agujeros[i];
			++r;
		}
	}
	return r;
}

bool resuelveCaso() {
	std::size_t nAgujeros = 0, longitud = 0;
	int aux;
	std::cin >> nAgujeros;
	if (nAgujeros == 0) return false;
	std::cin >> longitud;
	std::vector<int > agujeros(nAgujeros);
	for (std::size_t i = 0; i < nAgujeros; ++i){
		std::cin >> agujeros[i];
	}

	 int  nParches = resuelve(agujeros, longitud);
	std::cout << nParches << std::endl;
	return true;
}


int main() {
#ifndef DOMJUDGE

	std::ifstream in("casos.txt");

	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif
	while (resuelveCaso()){

	}

#ifndef DOMJUDGE

	std::cin.rdbuf(cinbuf); //reset to standard input again

	system("PAUSE");

#endif

	return 0;
}
