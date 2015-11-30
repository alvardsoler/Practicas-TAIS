/*
 * File:   ManchasCrecientes.h
 * Author: Samuel Lapuente Jiménez y Alvar David Soler Rus
 *
 */

#ifndef MANCHASCRECIENTES_H
#define MANCHASCRECIENTES_H

#include "Grafo.h"

class ManchasCrecientes {
public:

   

    ManchasCrecientes(int f, int c) : g(f*c), _f(f), _c(c),
    hayManchas(false), _marked(f, std::vector<bool>(c, false)), manchas(0),
    marked(f * c, false) {
	leerGrafo();
	if (!hayManchas) tamMax = 0;
	else tamMax = resuelve(g);
	indxMancha = 0;
	leerMancha();
    };

    int getComponenteMayor() {
	return tamMax;
    };

    bool leerMancha() {
	if (indxMancha < manchas.size()) {
	    siguienteMancha();
	    return true;
	} else return false;

    }

private:
    Grafo g;
    unsigned int tamMax;
    unsigned int _f;
    unsigned int _c;
    bool hayManchas;
    std::vector < std::vector<bool>> _marked;
    std::vector<unsigned int> manchas;
    unsigned int indxMancha;
    std::vector<bool> marked;
    unsigned int _count;

    void siguienteMancha() {
	unsigned int mancha = manchas.at(indxMancha);
	++indxMancha;
	unsigned int fila = (mancha / _c);
	unsigned int columna = (mancha % _c);
	if (fila > 0) {
	    if (_marked[fila - 1][columna]) {
		g.ponArista(fila * _c + columna, ((fila - 1) * _c) + columna);
	    }

	}
	if (fila < _f - 1)
	    if (_marked[fila + 1][columna]) {
		g.ponArista(fila * _c + columna, ((fila + 1) * _c) + columna);
	    }
	if (columna > 0)
	    if (_marked[fila][columna - 1]) {
		g.ponArista(fila * _c + columna, fila * _c + (columna - 1));
	    }
	if (columna < _c - 1)
	    if (_marked[fila][columna + 1]) {
		g.ponArista(fila * _c + columna, fila * _c + (columna + 1));
	    }
	//inicializamos _count a 1 porque si no, no se cuenta a si misma como parte de la componente conexca
	_count = 1;
	//Solo realizamos el DFS de la mancha nueva, ya que es la única que ha podido unir dos componentes para formar una mayor de la previamente existente.
	dfs(mancha);
	//volvemos a poner el vector de marcados a false para la siguiente iteración.
	for (unsigned int i = 0; i < marked.size(); ++i) marked[i] = false;

	//si la nueva componente conexa creada es mayor que la que teníamos, la devolvemos, si no, las cosas se dejan como estaban.
	if (_count > tamMax) tamMax = _count;
    };

    // recorrido en profundidad de la componente de v.

    void dfs(size_t v) {
	marked[v] = true;
	for (auto w : g.adj(v)) {
	    if (!marked[w]) {
		++_count;
		dfs(w);
	    }
	}
    }

    void leerGrafo() {

	char _m;

	std::cin.get(_m);
	for (unsigned int i = 0; i < _f; ++i) {
	    for (unsigned int j = 0; j < _c; ++j) {
		std::cin.get(_m);
		if (_m == '#') {
		    hayManchas = true;
		    _marked[i][j] = true;
		    if (i > 0) {
			if (_marked[i - 1][j]) {
			    g.ponArista(i * _c + j, ((i - 1) * _c) + j);
			}
		    }
		    if (j > 0)
			if (_marked[i][j - 1]) {
			    g.ponArista(i * _c + j, i * _c + (j - 1));
			}
		}
	    }
	    std::cin.get(_m);
	}
	if (std::cin) {
	    unsigned int n, a, b;
	    std::cin >> n;

	    for (unsigned int i = 0; i < n; ++i) {
		std::cin >> a; //guardamos filas y columnas del fichero en un vector de manchas
		std::cin >> b;
		manchas.push_back((a - 1) * _c + (b - 1)); //restamos uno a las posiciones ya que en el enunciado empiezan en 1 y no en 0 como nuestros vectores.
	    }
	}

    }

    /*
     * El coste es O(2|V| + |E|), O(|v|+|E|) del DFS que se hace
     * en ComponentesConexas y O(|V|) para sacar el maximo.
     */
    unsigned int resuelve(Grafo const & g) {
	// Utilizamos la clase ComponentesConexas
	// para sacar todas las componentes conexas del grafo 
	ComponentesConexas cc(g);
	unsigned int max = 0;
	// Recorremos todas las componentes conexas del grafo sacando
	// el tamaño máximo de las componentes conexas
	for (unsigned int i = 0; i < g.V(); ++i) {
	    if (max < cc.size(i))
		max = cc.size(i);
	}
	return max;
    }

};

#endif 