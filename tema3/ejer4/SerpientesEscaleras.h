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
	GrafoDirigido grafo;
	int saltos;
	std::vector<bool> _visited;
	std::vector<bool> _colors;

	void resuelve(std::vector<int> const & atajos) {
		std::vector<size_t> vec = grafo.adj(0);
		std::vector<size_t>::iterator it2 = vec.begin();
		
		BreadthFirstDirectedPaths bfdp(grafo, 0);

		Path camino = bfdp.pathTo(grafo.V() - 1);
		std::deque<size_t>::iterator it = camino.begin();
		saltos = camino.size() -1 ;
		while (it != camino.end()){
			//std::cout << *it << " ";
			for (size_t k = 0; k < atajos.size(); ++k){
				if (*it == atajos[k]){
					--saltos; break;
				}
			}
			it++;
			
		}
		//std::cout << std::endl;


		
	}

public:

	SerpientesEscaleras(GrafoDirigido g, std::vector<int> const & atajos) : grafo(g), saltos(0), _visited(g.V(), false), _colors(g.V(), false) {
		resuelve(atajos);
	};

	int getSaltos(){
		return saltos;
	}
};

#endif	/* SERPIENTESESCALERAS_H */