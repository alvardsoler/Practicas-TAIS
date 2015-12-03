/**
* TAIS16. Álvar Soler y Samuel Lapuente
* Ejercicio 20.
*
**/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
int resuelve(std::vector<int> const & esquiadores, std::vector<int> const & esquies){
	int total = 0;
	for (size_t i = 0; i < esquiadores.size(); ++i){
		total += std::abs((esquiadores[i] - esquies[i]));
	}
	return total;
}

bool resuelveCaso(){
	int num;
	std::cin >> num;
	std::vector<int> esquiadores(num);
	std::vector<int> esquies(num);
	if (num == 0) return false;
	for (int i = 0; i < num; ++i) {
		std::cin >> esquiadores[i];
	}
	for (int i = 0; i < num; ++i) {
		std::cin >> esquies[i];
	}
	std::sort(esquiadores.begin(), esquiadores.end());
	std::sort(esquies.begin(), esquies.end());
	std::cout << resuelve(esquiadores, esquies) << std::endl;
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
