/*
* File:   ArbolBipartito.h
* Author: Samuel Lapuente Jiménez y Alvar David Soler Rus
*
* Created on 13 de noviembre de 2015, 14:12
*/
#include "GrafoDirigido.h"

#ifndef SERPIENTESESCALERAS_H
#define	SERPIENTESESCALERAS_H



class SerpientesEscaleras {
private:
	
	int saltos;
	
	

	void resuelve(GrafoDirigido const & grafo) {
		std::vector<size_t> vec = grafo.adj(0);
		std::vector<size_t>::iterator it2 = vec.begin();
		
		BreadthFirstDirectedPaths bfdp(grafo, 0);

		Path camino = bfdp.pathTo(grafo.V()-1);
		std::deque<size_t>::iterator it = camino.begin();
		saltos = camino.size() -1 ;
	}

public:

	SerpientesEscaleras(GrafoDirigido const & g) : saltos(0) {
		resuelve(g);
	};

	int getSaltos(){
		return saltos;
	}
};

#endif	/* SERPIENTESESCALERAS_H */
