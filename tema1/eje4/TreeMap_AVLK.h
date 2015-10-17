//
//  TreeMap_AVL.h
//  Modificado para el ejercicio 4 del tema 1 de TAIS.
// Grupo TAIS16, Samuel Lapuente Jiménez, Alvar David Soler Rus
//  Implementación de tablas <clave, valor> como árboles de búsqueda AVL
//
//  Técnicas Algoritmicas en Ingeniería del Software / Diseño de Algoritmos
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 30/6/15.
//  Copyright (c) 2015 Alberto Verdejo. All rights reserved.
//

#ifndef TREEMAP_AVLK_H_
#define TREEMAP_AVLK_H_

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <utility>

template <typename Clave, typename Valor, typename Comparador = std::less<Clave>>
class TreeMap {
protected:
    using AVLT = TreeMap<Clave, Valor, Comparador>;
public:

    struct ClaveValor {
	const Clave clave;
	Valor valor;

	ClaveValor(Clave const& c, Valor const& v = Valor()) : clave(c), valor(v) {
	};
    };

    TreeMap(Comparador c = Comparador()) : raiz(nullptr), menor(c) {
    };

    TreeMap(AVLT const& other);

    TreeMap(AVLT && other);

    AVLT & operator=(AVLT const& other);

    AVLT & operator=(AVLT && other);

    ~TreeMap();

    void insert(Clave const& clave, Valor const& valor);

    bool empty() const;

    bool contains(Clave const& c) const;

    Valor const& at(Clave const& clave) const;

    void erase(Clave const& c);

    void print(std::ostream& o = std::cout) const;

protected:
    /**
    Clase nodo que almacena internamente la pareja (clave, valor),
    los punteros al hijo izquierdo y al hijo derecho, y la altura.
     */
    class TreeNode;
    using Link = TreeNode *;

    /** Puntero a la raíz de la estructura jerárquica de nodos. */
    Link raiz;

    /** Objeto función que compara elementos. */
    Comparador menor;

public:
    // iterador que recorre los pares <clave, valor> del árbol en inorden

    class Iterator {
    public:
	ClaveValor const& operator*() const;

	Iterator & operator++();
	Iterator operator++(int);

	bool operator==(const Iterator &other) const;

	bool operator!=(const Iterator &other) const;

    protected:
	friend class TreeMap;

	Iterator() : act_(nullptr) {
	}

	Iterator(Link p) {
	    act_ = first(p);
	}

	Link first(Link p);
	void next();

	Link act_;
	std::stack<Link> ancestors;
    };

    Iterator begin() {
	return Iterator(raiz);
    }

    Iterator end() const {
	return Iterator(nullptr);
    }


protected:

    static void liberar(Link a);

    static Link copiar(Link b);

    Link buscar(Clave const& clave, Link a) const;

    static int altura(Link a);

    virtual void insertar(ClaveValor const& cv, Link & a);

    void erase(Clave const& clave, Link & a);

    static void subirMenor(Link & a, Link b, Link padre);

    static void rotaDer(Link & k2);
    static void rotaIzq(Link & k1);
    static void rotaIzqDer(Link & k3);
    static void rotaDerIzq(Link & k1);
    static void reequilibraIzq(Link & a);
    static void reequilibraDer(Link & a);

    static void print(std::ostream & o, int indent, Link r);

};

template <typename Clave, typename Valor, typename Comparador>
inline std::ostream& operator<<(std::ostream & o, TreeMap<Clave, Valor, Comparador> const& a) {
    a.print(o);
    return o;
}

template <typename Clave, typename Valor, typename Comparador>
TreeMap<Clave, Valor, Comparador>::TreeMap(AVLT const& other) {
    raiz = copiar(other.raiz);
}

template <typename Clave, typename Valor, typename Comparador>
TreeMap<Clave, Valor, Comparador>::TreeMap(AVLT && other) : raiz(other.raiz) {
    other.raiz = nullptr;
}

template <typename Clave, typename Valor, typename Comparador>
TreeMap<Clave, Valor, Comparador> & TreeMap<Clave, Valor, Comparador>::operator=(AVLT const& other) {
    if (this != &other) {
	AVLT copia = other;
	std::swap(*this, copia);
    }
    return *this;
}

template <typename Clave, typename Valor, typename Comparador>
TreeMap<Clave, Valor, Comparador> & TreeMap<Clave, Valor, Comparador>::operator=(AVLT && other) {
    std::swap(raiz, other.raiz);
    return *this;
}

template <typename Clave, typename Valor, typename Comparador>
TreeMap<Clave, Valor, Comparador>::~TreeMap() {
    liberar(raiz);
    raiz = nullptr;
};

template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::insert(Clave const& clave, Valor const& valor) {
    insertar({clave, valor}, raiz);
}

template <typename Clave, typename Valor, typename Comparador>
bool TreeMap<Clave, Valor, Comparador>::empty() const {
    return raiz == nullptr;
}

template <typename Clave, typename Valor, typename Comparador>
bool TreeMap<Clave, Valor, Comparador>::contains(Clave const& c) const {
    return buscar(c, raiz) != nullptr;
}

template <typename Clave, typename Valor, typename Comparador>
Valor const& TreeMap<Clave, Valor, Comparador>::at(Clave const& clave) const {
    Link p = buscar(clave, raiz);
    if (p == nullptr)
	throw std::out_of_range("La clave no se puede consultar");
    return p->cv.valor;
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::erase(Clave const& c) {
    erase(c, raiz);
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::print(std::ostream& o) const {
    if (raiz != nullptr) {
	print(o, 0, raiz);
    } else
	o << "vacio\n";
}

template <typename Clave, typename Valor, typename Comparador>
class TreeMap<Clave, Valor, Comparador>::TreeNode {
public:
    ClaveValor cv;
    Link iz;
    Link dr;
    int altura;
    int tam_i;

    TreeNode(ClaveValor e, Link i = nullptr, Link d = nullptr, int alt = 1, int t_i = 1)
    : cv(e), iz(i), dr(d), altura(alt), tam_i(t_i){
    }
};

template <typename Clave, typename Valor, typename Comparador>
typename TreeMap<Clave, Valor, Comparador>::ClaveValor const& TreeMap<Clave, Valor, Comparador>::Iterator::operator*() const {
    if (act_ == nullptr) throw std::out_of_range("No hay elemento a consultar");
    return act_->cv;
}

template <typename Clave, typename Valor, typename Comparador>
typename TreeMap<Clave, Valor, Comparador>::Iterator & TreeMap<Clave, Valor, Comparador>::Iterator::operator++() {
    next();
    return *this;
}

template <typename Clave, typename Valor, typename Comparador>
typename TreeMap<Clave, Valor, Comparador>::Iterator TreeMap<Clave, Valor, Comparador>::Iterator::operator++(int) {
    Iterator ret(*this);
    operator++();
    return ret;
}

template <typename Clave, typename Valor, typename Comparador>
bool TreeMap<Clave, Valor, Comparador>::Iterator::operator==(const Iterator &other) const {
    return act_ == other.act_;
}

template <typename Clave, typename Valor, typename Comparador>
bool TreeMap<Clave, Valor, Comparador>::Iterator::operator!=(const Iterator &other) const {
    return !(this->operator==(other));
}

template <typename Clave, typename Valor, typename Comparador>
typename TreeMap<Clave, Valor, Comparador>::Link TreeMap<Clave, Valor, Comparador>::Iterator::first(Link p) {
    if (p == nullptr)
	return nullptr;

    while (p->iz != nullptr) {
	ancestors.push(p);
	p = p->iz;
    }
    return p;
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::Iterator::next() {
    if (act_ == nullptr) throw std::out_of_range("El iterador no se puede avanzar");

    // Si hay hijo derecho, saltamos al primero
    // en inorden del hijo derecho
    if (act_->dr)
	act_ = first(act_->dr);
    else {
	// Si no, vamos al primer ascendiente
	// no visitado. Para eso consultamos
	// la pila; si ya est· vacÌa, no quedan
	// ascendientes por visitar
	if (ancestors.empty())
	    act_ = nullptr;
	else {
	    act_ = ancestors.top();
	    ancestors.pop();
	}
    }
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::liberar(Link a) {
    if (a != nullptr) {
	liberar(a->iz);
	liberar(a->dr);
	delete a;
    }
}

template <typename Clave, typename Valor, typename Comparador>
typename TreeMap<Clave, Valor, Comparador>::Link
TreeMap<Clave, Valor, Comparador>::copiar(Link b) {
    if (b == nullptr) return nullptr;
    else return new TreeNode(b->cv,
	    copiar(b->iz),
	    copiar(b->dr),
	    b->altura);
}

template <typename Clave, typename Valor, typename Comparador>
typename TreeMap<Clave, Valor, Comparador>::Link
TreeMap<Clave, Valor, Comparador>::buscar(Clave const& clave, Link a) const {
    if (a == nullptr)
	return nullptr;
    else if (menor(clave, a->cv.clave))
	return buscar(clave, a->iz);
    else if (menor(a->cv.clave, clave))
	return buscar(clave, a->dr);
    else // clave == a->cv.clave
	return a;
}

template <typename Clave, typename Valor, typename Comparador>
int TreeMap<Clave, Valor, Comparador>::altura(Link a) {
    if (a == nullptr) return 0;
    else return a->altura;
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::insertar(ClaveValor const& cv, Link & a) {
    if (a == nullptr) {
	a = new TreeNode(cv);
    } else if (menor(cv.clave, a->cv.clave)) {
	insertar(cv, a->iz);
	a->tam_i++;
	reequilibraDer(a);
    } else if (menor(a->cv.clave, cv.clave)) {
	insertar(cv, a->dr);
	reequilibraIzq(a);
    } else { // la clave ya está, se actualiza el valor asociado
	a->cv.valor = cv.valor;
    }
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::erase(Clave const& clave, Link & a) {
    if (a != nullptr) {
	if (menor(clave, a->cv.clave)) {
	    erase(clave, a->iz);
	    a->tam_i--;
	    reequilibraIzq(a);
	} else if (menor(a->cv.clave, clave)) {
	    erase(clave, a->dr);
	    reequilibraDer(a);
	} else // a->cv.clave == clave
	    if (a->iz == nullptr || a->dr == nullptr) {
	    Link aux = a;
	    a = a->iz == nullptr ? a->dr : a->iz;
	    delete aux;
	} else { // tiene dos hijos
	    subirMenor(a, a->dr, nullptr);
	    // reequilibraDer(a);
	}
    }
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::subirMenor(Link & a, Link b, Link padre) {
    if (b->iz != nullptr) {
	subirMenor(a, b->iz, b);
	reequilibraIzq(b);
    } else {
	if (padre != nullptr) {
	    padre->iz = b->dr;
	    b->dr = a->dr;
	}
	b->iz = a->iz;
	delete a;
	a = b;
	a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
    }
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::rotaDer(Link & k2) {
    Link k1 = k2->iz;
    k2->iz = k1->dr;
    k1->dr = k2;
    k2->tam_i--;
    k2->altura = std::max(altura(k2->iz), altura(k2->dr)) + 1;
    k1->altura = std::max(altura(k1->iz), altura(k1->dr)) + 1;
    k2 = k1;
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::rotaIzq(Link & k1) {
    Link k2 = k1->dr;
    k1->dr = k2->iz;
    k2->iz = k1;
    k2->tam_i++;    
    k1->altura = std::max(altura(k1->iz), altura(k1->dr)) + 1;
    k2->altura = std::max(altura(k2->iz), altura(k2->dr)) + 1;
    k1 = k2;
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::rotaIzqDer(Link & k3) {
    rotaIzq(k3->iz);
    rotaDer(k3);
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::rotaDerIzq(Link & k1) {
    rotaDer(k1->dr);
    rotaIzq(k1);
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::reequilibraIzq(Link & a) {
    if (altura(a->dr) - altura(a->iz) > 1) {
	if (altura(a->dr->iz) > altura(a->dr->dr))
	    rotaDerIzq(a);
	else rotaIzq(a);
    } else a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::reequilibraDer(Link & a) {
    if (altura(a->iz) - altura(a->dr) > 1) {
	if (altura(a->iz->dr) > altura(a->iz->iz))
	    rotaIzqDer(a);
	else rotaDer(a);
    } else a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::print(std::ostream & o, int indent, Link r) {
    if (r != nullptr) {
	print(o, indent + 2, r->dr);
	for (auto i = 0; i < indent; ++i) o << " ";
	o << "(" << r->cv.clave << "," << r->cv.valor <<", " << r->tam_i <<")\n";
	print(o, indent + 2, r->iz);
    }
}



#endif /* TREEMAP_AVL_H_ */
