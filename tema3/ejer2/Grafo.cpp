
#include "Grafo.h"

Grafo::Grafo(std::string file) {
    std::ifstream entrada(file);
    if (entrada.fail()) 
        throw std::runtime_error("Error en fichero");
    entrada >> _V;
    _E = 0;
    _adj.resize(_V);
    size_t e;
    entrada >> e;
    size_t v, w;
    for (auto i = 0; i < e; ++i) {
        entrada >> v;
        entrada >> w;
        ponArista(v, w);
    }
    entrada.close();
}

void Grafo::ponArista(size_t v, size_t w) {
    if (v >= _V || w >= _V) throw std::invalid_argument("Vértice inexistente");
    ++_E;
    _adj[v].push_back(w);
    _adj[w].push_back(v);
}

const Adys& Grafo::adj(size_t v) const {
    if (v >= _V) throw std::invalid_argument("Vértice inexistente");
    return _adj[v];
}

/**
 * Muestra el grafo en el stream de salida o
 */
void Grafo::print(std::ostream & o) const {
    o << _V << " vértices, " << _E << " aristas\n";
    for (auto v = 0; v < _V; ++v) {
        o << v << ": ";
        for(auto w : _adj[v]) {
            o << w << " ";
        }
        o << "\n";
    }
}

std::ostream& operator<<(std::ostream & o, Grafo const& g){
    g.print(o);
    return o;
}

/**
 * Recorrido en profundidad de un grafo a partir de un vértice origen.
 */


DepthFirstSearch::DepthFirstSearch(Grafo const& G, size_t s) : _count(0), _marked(G.V(), false) {
    dfs(G, s);
}

void DepthFirstSearch::dfs(Grafo const& G, size_t v) {
    ++_count;
    _marked[v] = true;
    for (auto w : G.adj(v)) {
        if (!_marked[w]) {
            dfs(G, w);
        }
    }
}


DepthFirstPaths::DepthFirstPaths(Grafo const& G, size_t s) : marked(G.V(), false),
edgeTo(G.V()), s(s) {
    dfs(G, s);
}


// Devuelve un camino desde el origen a v (vacío si no están conectados).
Path DepthFirstPaths::pathTo(size_t v) const {
    Path path;
    if (!hasPathTo(v)) return path;
    for (auto x = v; x != s; x = edgeTo[x])
        path.push_front(x);
    path.push_front(s);
    return path;
}


// recorrido en profundidad desde v
void DepthFirstPaths::dfs(Grafo const& G, size_t v) {
    marked[v] = true;
    for (auto w : G.adj(v)) {
        if (!marked[w]) {
            edgeTo[w] = v;
            dfs(G, w);
        }
    }
}


/**
 * Recorrido en anchura de un grafo a partir de un vértice origen.
 * Permite recuperar los caminos más cortos desde el origen a todos los vértices alcanzables.
 */

BreadthFirstPaths::BreadthFirstPaths(Grafo const& G, size_t s)
: marked(G.V(), false), edgeTo(G.V()), distTo(G.V()), s(s) {
    bfs(G, s);
}

// Devuelve el camino más corto desde el origen a v (vacío si no están conectados).
Path BreadthFirstPaths::pathTo(size_t v) const {
    Path path;
    if (!hasPathTo(v)) return path;
    for (auto x = v; x != s; x = edgeTo[x])
        path.push_front(x);
    path.push_front(s);
    return path;
}


void BreadthFirstPaths::bfs(Grafo const& G, size_t s) {
    std::queue<size_t> q;
    distTo[s] = 0;
    marked[s] = true;
    q.push(s);
    while (!q.empty()) {
        auto v = q.front(); q.pop();
        for (auto w : G.adj(v)) {
            if (!marked[w]) {
                edgeTo[w] = v;
                distTo[w] = distTo[v] + 1;
                marked[w] = true;
                q.push(w);
            }
        }
    }
}


/**
 * Componentes conexas de un grafo.
 */

ComponentesConexas::ComponentesConexas(Grafo const& G) : marked(G.V(), false), _id(G.V()),
    _size(G.V(),0), _count(0) {
        for (auto v = 0; v < G.V(); ++v) {
            if (!marked[v]) { // se recorre una nueva componente conexa
                dfs(G, v);
                ++_count;
            }
        }
    }
    

// recorrido en profundidad de la componente de v
void ComponentesConexas::dfs(Grafo const& G, size_t v) {
        marked[v] = true;
        _id[v] = _count;
        ++_size[_count];
        for (auto w : G.adj(v)) {
            if (!marked[w]) {
                dfs(G, w);
            }
        }
    }


