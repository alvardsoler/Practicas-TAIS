/*
 * File:   ArbolBipartito.h
 * Author: Samuel Lapuente Jiménez y Alvar David Soler Rus
 *
 * Created on 13 de noviembre de 2015, 14:12
 */

#ifndef MANCHAS_H
#define	MANCHAS_H

#include "Grafo.h"

class Manchas {
public:

    Manchas(Grafo const &g) {

	tamMax = resuelve(g);
    };

    int getComponenteMayor() {
	return tamMax;
    };
private:

    int tamMax;

    int resuelve(Grafo const & g) {
	
	ComponentesConexas cc(g);
	int max = 0;
	for (auto i = 0; i < cc.count(); ++i) {
	    if (max < cc.size(i)) 
		max = cc.size(i);
	}
	return max;
    };
};


#endif	/* MANCHAS_H */

