/*
 * File:   ManchasCrecientes.h
 * Author: Samuel Lapuente Jiménez y Alvar David Soler Rus
 *
 * Created on 13 de noviembre de 2015, 14:12
 */

#ifndef MANCHASCRECIENTES_H
#define MANCHASCRECIENTES_H

#include "Grafo.h"

class ManchasCrecientes {
private:
    Grafo g;
    int tamMax;
    int _f;
    int _c;
    bool hayManchas;
    std::vector < std::vector<bool>> _marked;
    std::vector<int> manchas;
    int indxMancha;

    void siguienteMancha() {
        int mancha = manchas.at(indxMancha);
        ++indxMancha;
        int fila = (mancha / _c);
        int columna = (mancha % _c);
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
        _count = 0;

        dfs(mancha);
        if (_count > tamMax) tamMax = _count;
    };
    std::vector<bool> marked;
    int _count;
    // recorrido en profundidad de la componente de v

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
        for (int i = 0; i < _f; ++i) {
            for (int j = 0; j < _c; ++j) {
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
            int n, a, b;
            std::cin >> n;
           // manchas.resize(n);

            for (int i = 0; i < n; ++i) {
                std::cin >> a;
                std::cin >> b;
                manchas.push_back(a * _c + b);
            }
        }

    }

    /*
     * El coste es O(2|V| + |E|), O(|v|+|E|) del DFS que se hace
     * en ComponentesConexas y O(|V|) para sacar el maximo.
     */
    int resuelve(Grafo const & g) {
        // Utilizamos la clase ComponentesConexas
        // para sacar todas las componentes conexas del grafo
        ComponentesConexas cc(g);
        int max = 0;
        // Recorremos todas las componentes conexas del grafo sacando
        // el tamaño máximo de las componentes conexas
        for (auto i = 0; i < g.V(); ++i) {
            if (max < cc.size(i))
                max = cc.size(i);
        }
        return max;
    }
public:

    ManchasCrecientes(int f, int c) : _f(f), _c(c), g(f*c), _marked(f, std::vector<bool>(c, false)), marked(_f * _c, false), manchas(0) {
        //        g(_f*_c);
        hayManchas = false;
        leerGrafo();
        if (!hayManchas) tamMax = 0;
        else tamMax = resuelve(g);
        indxMancha = 0;
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
};



#endif / MANCHASCRECIENTES_H /
