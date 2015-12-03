/**
* TAIS16. Álvar Soler y Samuel Lapuente
* Ejercicio 21.
*
**/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
int resuelve(std::vector<int> const & enemigos, std::vector<int> const & defensores){
	int total = 0;
	size_t aux = 0;
	for (size_t i = 0; i < defensores.size(); ++i){
		for (size_t j = aux; j < enemigos.size(); ++j){
			++aux;
			if (defensores[i] >= enemigos[j]){
				++total;
				break;
			}
		}
	}

	return total;
}

bool mayor(int a, int b){ return a > b; }

bool resuelveCaso(){
	int num = 0;
	std::cin >> num;
	std::vector<int> enemigos(num);
	std::vector<int> defensores(num);
	if (num == 0) return false;
	for (int i = 0; i < num; ++i) {
		std::cin >> enemigos[i];
	}
	for (int i = 0; i < num; ++i) {
		std::cin >> defensores[i];
	}
	std::sort(enemigos.begin(), enemigos.end(), mayor);
	std::sort(defensores.begin(), defensores.end(), mayor);
	std::cout << resuelve(enemigos, defensores) << std::endl;
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
