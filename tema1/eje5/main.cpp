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
#include "TreeMap_AVL.h"


// trim from end

static inline std::string rtrim(std::string s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

int main() {
#ifndef DOMJUDGE

    std::ifstream in("caso.txt");

    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif
    int n;
    std::cin >> n;
    while (n != 0) {
	std::string line;
	TreeMap<std::string, std::string, std::less < std::string>> arbol;

	std::getline(in, line);
	std::istringstream iss(line);
	for (std::size_t i = 1; i < n + 1; i++) {
	    std::getline(in, line);
	    iss.rdbuf();
	    std::istringstream iss(line);
	    std::string word;
	    while (iss >> word) {
		if (word.length() > 2) {
		    try {
			word[0] = std::tolower(word[0]);
			std::string aux = arbol.at(word);
			std::size_t aux2 = aux.find(std::to_string(i));

			//		    std::cout << std::to_string(aux2) << std::endl;
			if (!aux.empty() && aux2 != i) {
			    aux += " " + std::to_string(i);
			    arbol.insert(word, aux);
			}
		    } catch (std::out_of_range e) {
			arbol.insert(word, std::to_string(i));
		    }

		}
	    }
	}
	TreeMap<std::string, std::string, std::less < std::string>>::Iterator it(arbol.begin());
	while (it != arbol.end()) {
	    TreeMap<std::string, std::string, std::less < std::string>>::ClaveValor cv(it.operator *());
	    std::cout << cv.clave << " " << cv.valor << std::endl;
	    it.operator ++();
	}
	std::cout << "----" << std::endl;
	std::cin >> n;
    }

    //	if (!(iss >> word)) {
    //	    break;
    //	} // error


    //do


    //	arbol.print(std::cout);
    //	TreeMap_AVLRef<std::string, std::list<std::string>, std::less < std::string>>::Iterator it(arbol.end());
    //	do {
    //	    TreeMap_AVLRef<std::string, std::list<std::string>, std::less < std::string>>::ClaveValor cv (it*);
    //	    //	    std::cout << it*.clave << it*.valor << std::endl;
    //	} while ();






#ifndef DOMJUDGE

    std::cin.rdbuf(cinbuf); //reset to standard input again

    system("PAUSE");

#endif

    return 0;
}