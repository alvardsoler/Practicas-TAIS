//
//  grafo.h
//
//  Implementación de grafos no dirigidos y clases que los exploran
//
//  Técnicas Algoritmicas en Ingeniería del Software / Diseño de Algoritmos
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 26/6/15.
//  Copyright (c) 2015 Alberto Verdejo. All rights reserved.
//

#ifndef GRAFO_H_
#define GRAFO_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stdexcept>


using Adys = std::vector<size_t>;  // lista de adyacentes a un vértice
using Path = std::deque<size_t>;   // para representar caminos

class Grafo {
public:
    
    /**
     * Crea un grafo con V vértices.
     */
    Grafo(size_t v) : _V{v}, _E{0}, _adj(_V) {}
    
    /**
     * Crea un grafo a partir de un fichero de entrada.
     */
    Grafo(std::string file);
        
    /**
     * Devuelve el número de vértices del grafo.
     */
    size_t V() const { return _V; }
    
    /**
     * Devuelve el número de aristas del grafo.
     */
    size_t E() const { return _E; }
    
    /**
     * Añade la arista v-w al grafo.
     * @throws invalid_argument si algún vértice no existe
     */
    void ponArista(size_t v, size_t w);
    
    /**
     * Devuelve la lista de adyacencia de v.
     * @throws invalid_argument si v no existe
     */
    const Adys& adj(size_t v) const;
    
    /**
     * Muestra el grafo en el stream de salida o
     */
    void print(std::ostream & o = std::cout) const;
    
private:
    size_t _V;   // número de vértices
    size_t _E;   // número de aristas
    std::vector<Adys> _adj;   // vector de listas de adyacentes
    
};

/**
 * Para mostrar grafos por la salida estándar.
 */
std::ostream& operator<<(std::ostream & o, Grafo const& g);

/**
 * Recorrido en profundidad de un grafo a partir de un vértice origen.
 */

class DepthFirstSearch {
public:
    DepthFirstSearch(Grafo const& G, size_t s);
    
    // hay camino del origen a v?
    bool marked(size_t v) const {
        return _marked[v];
    }
    
    // número de vértices conectados a s
    size_t count() const {
        return _count;
    }
    
private:
    std::vector<bool> _marked;    // marked[v] = hay camino s-v?
    size_t _count;      // número de vértices conectados a s
    
    // recorrido en profundidad desde v
    void dfs(Grafo const& G, size_t v);
};


/**
 * Recorrido en profundidad de un grafo a partir de un vértice origen.
 * Permite recuperar los caminos desde el origen a todos los vértices alcanzables.
 */

class DepthFirstPaths {
public:
    DepthFirstPaths(Grafo const& G, size_t s);
    
    // Hay camino del origen a v?
    bool hasPathTo(size_t v) const {
        return marked[v];
    }
    
    // Devuelve un camino desde el origen a v (vacío si no están conectados).
    Path pathTo(size_t v) const;
    
private:
    std::vector<bool> marked;    // marked[v] = hay camino s-v?
    std::vector<size_t> edgeTo;  // edgeTo[v] = último vértice antes de llegar a v
    size_t s;                    // vértice origen
    
    // recorrido en profundidad desde v
    void dfs(Grafo const& G, size_t v);
};

/**
 * Recorrido en anchura de un grafo a partir de un vértice origen.
 * Permite recuperar los caminos más cortos desde el origen a todos los vértices alcanzables.
 */
class BreadthFirstPaths {
public:
    BreadthFirstPaths(Grafo const& G, size_t s);
    
    // Hay camino del origen a v?
    bool hasPathTo(size_t v) const {
        return marked[v];
    }
    
    // Devuelve el camino más corto desde el origen a v (vacío si no están conectados).
    Path pathTo(size_t v) const;
    
    // Devuelve el número de aristas en el camino más corto a v
    size_t distance(size_t v) const {
        return distTo[v];
    }
    
private:
    std::vector<bool> marked;     // marked[v] = hay camino s-v?
    std::vector<size_t> edgeTo;   // edgeTo[v] = último vértice antes de llegar a v
    std::vector<size_t> distTo;   // distTo[v] = número de aristas en el camino s-v más corto
    size_t s;                     // vértice origen
    
    void bfs(Grafo const& G, size_t s);
};

/**
 * Componentes conexas de un grafo.
 */
class ComponentesConexas {
public:
    ComponentesConexas(Grafo const& G);
    
    // identificador de la componente que contiene a v
    size_t id(size_t v) const {
        return _id[v];
    }
    
    // tamaño de la componente que contiene a v
    size_t size(size_t v) const {
        return _size[_id[v]];
    }
    
    // número de componentes conexas
    size_t count() const {
        return _count;
    }
    
    // están v y w en la misma componente conexa?
    bool areConnected(size_t v, size_t w) const {
        return id(v) == id(w);
    }
    
private:
    std::vector<bool> marked;     // marked[v] = se ha visitado el vértice v?
    std::vector<size_t> _id;      // id[v] = identificador de la componente que contiene a v
    std::vector<size_t> _size;    // size[id] = número de vértices en la componente id
    size_t _count;                // número de componentes conexas
    
    // recorrido en profundidad de la componente de v
    void dfs(Grafo const& G, size_t v);
};

#endif /* GRAFO_H_ */
