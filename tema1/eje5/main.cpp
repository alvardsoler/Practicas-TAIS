/*
 * Grupo TAIS16, Samuel Lapuente Jiménez, Alvar David Soler Rus
 *
 * 
 *  */
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <cstdlib>
#include <climits>
#include <sstream>
#include <stdio.h>



#include "TreeMap_AVLRef.h"

int main() {
#ifndef DOMJUDGE

    std::ifstream in("caso.txt");

    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif
    int n;
    std::cin >> n;
    while (n != 0) {
	std::string line;
	TreeMap_AVLRef<std::string, std::list<std::string>, std::less < std::string>> arbol;

	std::getline(in, line);
	std::istringstream iss(line);
	for (int i = 0; i < n; i++) {
	    std::getline(in, line);
	    iss.rdbuf();
	    std::istringstream iss(line);
	    std::string word;
	    if (iss >> word) {
		//		arbol.insert(word, std::to_string(i));
		std::list<std::string> aux = arbol[word];
		
		if (aux.empty()) {
		    //		    std::cout << "palabra no encontrada: " << word << "  " << arbol[word] << std::endl;
		    aux.push_back(std::to_string(i));
		    arbol.insert(word, aux);
		} else if (!aux.back().compare(std::to_string(i))) {
		    aux.push_back(std::to_string(i));
		    arbol.insert(word, aux);
		}
		//		std::cout << word << "  " << i << std::endl;
		while (iss >> word) {
		    aux = arbol[word];
		    if (aux.empty()) {				
			aux.push_back(std::to_string(i));
			arbol.insert(word, aux);
		    } else if (!aux.back().compare(std::to_string(i))) {
			aux.push_back(std::to_string(i));
			arbol.insert(word, aux);
		    }
		    //		    std::cout << word << "  " << i << std::endl;
		}

	    }

	    //	if (!(iss >> word)) {
	    //	    break;
	    //	} // error


	    //do
	}
	
//	arbol.print(std::cout);
//	TreeMap_AVLRef<std::string, std::list<std::string>, std::less < std::string>>::Iterator it(arbol.end());
//	do {
//	    TreeMap_AVLRef<std::string, std::list<std::string>, std::less < std::string>>::ClaveValor cv (it*);
//	    //	    std::cout << it*.clave << it*.valor << std::endl;
//	} while ();
//	
	std::cout << "----" << std::endl;
	std::cin >> n;
    }




#ifndef DOMJUDGE

    std::cin.rdbuf(cinbuf); //reset to standard input again

    system("PAUSE");

#endif

    return 0;
}