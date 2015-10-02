/* 
 * File:   main.cpp
 * Author: furia
 *
 * Created on 2 de octubre de 2015, 15:05
 */

#include <cstdlib>
#include "BinTree.h"

//using namespace std;

/*
 * Ejercicio 1 del tema 1 de TAIS.
 */
int main() {
#ifndef DOMJUDGE

    std::ifstream in("casos.txt");

    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif

    int numCasos;

    std::cin >> numCasos;

    for (int i = 0; i < numCasos; ++i)
	casoDePrueba();

#ifndef DOMJUDGE

    std::cin.rdbuf(cinbuf); //reset to standard input again

    //char ch;

    //std::cin >> ch;

    system("PAUSE");

#endif
    return 0;
}

void casoDePrueba(){
    char aux;
    std::cin >> aux;
    while (aux != 'R' || aux != '.' ){
	aux >> std::cout;
    }
    std::endl >> std::cout;
}
