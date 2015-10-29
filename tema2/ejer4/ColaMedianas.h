/* 
 * File:   ColaMedianas.h
 * Author: Álvar D. Soler Rus
 * 
 * Ejercicio 1 de la práctica 1 de TAIS.
 *
 * Created on 3 de noviembre de 2014, 17:31
 */

#include <string>
#include <iostream>
#include <queue>          // std::priority_queue

#ifndef COLAMEDIANAS_H
#define	COLAMEDIANAS_H

class ColaMedianas {
private:

    std::priority_queue<unsigned long long int, std::vector<unsigned long long int>, std::less<unsigned long long int>>colaMin;
    std::priority_queue<unsigned long long int, std::vector<unsigned long long int>, std::greater<unsigned long long int>> colaMax; // La raiz será la mediana

    void equilibrar() {
	if (colaMax.size() == (colaMin.size() + 2)) {
	    colaMin.push(colaMax.top());
	    colaMax.pop();
	} else if (colaMin.size() == (colaMax.size() + 1)) {
	    colaMax.push(colaMin.top());
	    colaMin.pop();
	}
    }

public:

    ColaMedianas() {

    }

    int mediana() {
	return colaMax.top();
    }

    void inserta(unsigned long long int elem) {
	// si es el primer elemento a insertar se inserta en colaMax
	if (colaMax.empty()) colaMax.push(elem);
	else { // en caso contrario, se introduce en un monticulo u otro
	    if (elem > colaMax.top()) colaMax.push(elem);
	    else colaMin.push(elem);
	    equilibrar();
	}

    }

    void quitaMediana() {
	colaMax.pop();
	equilibrar();
    }

};


#endif	/* COLAMEDIANAS_H */