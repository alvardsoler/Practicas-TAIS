/*
* Grupo TAIS16, Samuel Lapuente Jiménez, Alvar David Soler Rus
*/

#include "TreeMapRango.h"

void resolverCaso(int numElem) {
	TreeMapRango<int, int, std::less<int>> arbol;
	int clave, k1, k2;
	std::vector<int> lista;


	for (int i = 0; i < numElem; i++){
		std::cin >> clave;
		arbol.insert(clave, 0);
	}

	std::cin >> k1 >> k2;

	lista = arbol.rango(k1, k2);


	//Declaramos un iterador para recorrer la lista y poder imprimirla por pantalla
	std::vector<int>::const_iterator it = lista.cbegin();

	if (!lista.empty()){
		while (it != lista.cend()){
			std::cout << *it;
			++it;
			if (it != lista.cend()){
				std::cout << " ";
			}
		}
	}
	std::cout << std::endl;

}

int main() {
	int numCasos;
	std::cin >> numCasos;
	while (numCasos != 0){
		resolverCaso(numCasos);
		std::cin >> numCasos;
	}
	system("pause");
	return 0;
}