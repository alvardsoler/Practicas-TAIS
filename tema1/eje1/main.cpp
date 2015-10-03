/*
 * Grupo TAIS16, Samuel Lapuente Jiménez, Alvar David Soler Rus
 * 
 * Solución: una función recursiva que analiza los dos posibles casos en los 
 * que un árbol estaría equilibrado: que estuviera vacío, o que la diferencia de
 * alturas entre sus hijos sea menor o igual que uno y a la vez ese árbol
 * esté equilibrado. Calculando la altura del árbol, el resto es muy fácil.
 * 
 */


#include <iostream>
#include <fstream>
#include <cstdlib>
#include "BinTree.h"

/**
 * Creación del árbol binario
 * @return BinTree construido
 */
BinTree<char> leerArbol() {
    char raiz;
    std::cin >> raiz;
    if (raiz == '.') {
        // es un árbol vacío
        return
        {
        };
    } else {
        // leer recursivamente los hijos
        auto iz = leerArbol();
        auto dr = leerArbol();
        return
        {
            iz, raiz, dr
        };
    }
}
// dado un árbol binario, calcula su altura
// lineal en el número N de nodos del árbol, O(N)

/**
 * Dado un árbol binario calcula su altura.
 * Lineal en el número N de nodos del aŕbol, O(N)
 * @author Alberto Verdejo
 * @param arbol del que se quiere averiguar la altura
 * @return altura máxima del arbol
 */
int altura(BinTree<char> const & arbol) {
    if (arbol.empty()) {
        return 0;
    } else {
        return 1 + std::max(altura(arbol.left()), altura(arbol.right()));
    }
}

/**
 * Función recursiva principal. Si el árbol es vacío, ese árbol estará equilibrado.
 * Si no lo está, se comprueba si sus hijos están equilibrados. En el caso de 
 * que sea así, se calcula la diferencia de alturas en valor absoluto y
 * si ese valor es menor o igual que 1 quiere decir que está equilibrado.
 * Complejidad cuadrática en el número de nodos N del árbol, O(N²). Ésto es
 * por la función altura.
 * @param arbol a analizar
 * @return true si está equilibrado, false si no
 */
bool resuelve(BinTree<char> const & arbol) {
    if (arbol.empty()) return true;
    if (resuelve(arbol.left()) && resuelve(arbol.right())) {
        int alturaDer = altura(arbol.right());
        int alturaIzq = altura(arbol.left());
        if (std::abs(alturaDer - alturaIzq) <= 1) return true;
        else return false;
    } else {
        return false;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracion, y escribiendo la respuesta

void resolverCaso() {
    auto arbol = leerArbol();
    if (resuelve(arbol)) {
        std::cout << "SI" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
}

int main() {
#ifndef DOMJUDGE

    std::ifstream in("casos.txt");

    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resolverCaso();

#ifndef DOMJUDGE

    std::cin.rdbuf(cinbuf); //reset to standard input again

    //char ch;

    //std::cin >> ch;

    system("PAUSE");

#endif

    return 0;
}
