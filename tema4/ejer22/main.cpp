/**
* TAIS16. Álvar Soler y Samuel Lapuente
* Ejercicio 22.
*
**/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
int resuelve(std::vector<int> const & pilas, int const V){
	int total = 0;
	size_t aux = pilas.size()-1;

	for (size_t i = 0; i < pilas.size() && aux >= 0 && i < aux; ++i){
		if (pilas[i] + pilas[aux] >= V) {
			++total;
			--aux;
		}
	}

	return total;
}

bool mayor(int a, int b){ return a > b; }

void resuelveCaso(){
	int num = 0;
	std::cin >> num;
	int voltaje;
	std::cin >> voltaje;
	std::vector<int> pilas(num);

	for (int i = 0; i < num; ++i) {
		std::cin >> pilas[i];
	}

	std::sort(pilas.begin(), pilas.end());

	std::cout << resuelve(pilas, voltaje) << std::endl;

}

int main() {
#ifndef DOMJUDGE

	std::ifstream in("casos.txt");

	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif
	unsigned int casos;
	std::cin >> casos;
	for (size_t i = 0; i < casos; ++i)
		resuelveCaso();


#ifndef DOMJUDGE

	std::cin.rdbuf(cinbuf); //reset to standard input again

	system("PAUSE");
#endif
	return 0;
}
