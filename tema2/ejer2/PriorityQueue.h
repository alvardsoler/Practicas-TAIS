//
//  PriorityQueue.h
//
//  Implementación de colas con prioridad mediante montículos
//
//  Técnicas Algoritmicas en Ingeniería del Software / Diseño de Algoritmos
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 26/6/15.
//  Copyright (c) 2015 Alberto Verdejo. All rights reserved.
//

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>

const size_t TAM_INICIAL = 100;

// Comparator dice cuándo un valor de tipo T es más prioritario que otro
template <typename T = int, typename Comparator = std::less<T>>
class PriorityQueue {
public:

	PriorityQueue(size_t t = TAM_INICIAL, Comparator c = Comparator());

	/** Constructor a partir de un vector de elementos */
	PriorityQueue(std::vector<T> const& v_ini, Comparator c = Comparator());

	PriorityQueue(PriorityQueue<T, Comparator> const&) = default;

//	PriorityQueue(PriorityQueue<T, Comparator> &&) = default;

	PriorityQueue<T, Comparator> & operator=(PriorityQueue<T, Comparator> const&) = default;

//	PriorityQueue<T, Comparator> & operator=(PriorityQueue<T, Comparator> &&) = default;

	~PriorityQueue() = default;


	/** Insertar el elemento x (que incluye su prioridad).
	Si no hay espacio, el array se agranda. */
	void push(T const& x);
	void push(T && x);

	/** Devuelve el número de elementos en la cola. */
	size_t size() const { return numElems; }

	bool empty() const { return (numElems == 0); }

	/* Si la cola no es vacía, devuelve el elemento más prioritario. */
	T const& top() const;

	/* Si la cola no es vacía, elimina el elemento más prioritario. */
	void pop();

	/* Si la cola no es vacía, elimina y devuelve el elemento más prioritario. */
	void pop(T & prim);

	/* Muestra el montículo por la salida o */
	void print(std::ostream& o = std::cout) const;


private:

	/** Vector que contiene los datos */
	std::vector<T> array;     // primer elemento en la posición 1

	/** Número de elementos en el montículo */
	size_t numElems;

	/** Objeto función que sabe comparar elementos.
	* antes(a,b) es cierto si a es más prioritario que b (a debe salir antes que b)
	*/
	Comparator antes;

	/* Flota el elemento situado en la posición n del montículo. */
	void flotar(size_t n);

	/* Hunde el elemento situado en la posición n del montículo. */
	void hundir(size_t n);

	/* convierte un array en un montículo */
	void monticulizar();
};

template <typename T, typename Comparator>
inline std::ostream& operator<<(std::ostream & o, PriorityQueue<T, Comparator> const& a){
	a.print(o);
	return o;
}

/** Función para construir una cola con prioridad cuyo Comparator es una lambda. */
template<typename T, typename Comparator> // el tipo Comparator se deduce a partir de c
inline PriorityQueue<T, Comparator> make_priorityqueue(Comparator c, size_t tam = TAM_INICIAL)
{
	return PriorityQueue<T, Comparator>(tam, c);
}


template <typename T, typename Comparator>
PriorityQueue<T, Comparator>::PriorityQueue(size_t t, Comparator c) :
array(t + 1), numElems(0), antes(c) {};

template <typename T, typename Comparator>
PriorityQueue<T, Comparator>::PriorityQueue(std::vector<T> const& v_ini, Comparator c) :
array(2 * v_ini.size()), numElems(v_ini.size()), antes(c) {
	for (auto i = 0; i < v_ini.size(); ++i)
		array[i + 1] = v_ini[i];
	monticulizar();
};


template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::push(T const& x) {
	if (numElems == array.size() - 1)  // si el array se ha llenado se aumenta el tamaño
		array.resize(array.size() * 2);
	++numElems;
	array[numElems] = x;
	flotar(numElems);
}
template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::push(T && x) {
	if (numElems == array.size() - 1)  // si el array se ha llenado se aumenta el tamaño
		array.resize(array.size() * 2);
	++numElems;
	array[numElems] = std::move(x);
	flotar(numElems);
}

template <typename T, typename Comparator>
T const& PriorityQueue<T, Comparator>::top() const {
	if (empty()) throw std::domain_error("No se puede consultar el primero de una cola vacía.");
	else return array[1];
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::pop() {
	if (empty()) throw std::domain_error("Imposible eliminar el primero de una cola vacía");
	else {
		array[1] = std::move(array[numElems]);
		--numElems;
		hundir(1);
	}
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::pop(T & prim) {
	if (empty()) throw std::domain_error("Imposible eliminar el primero de una cola vacía");
	else {
		prim = std::move(array[1]);
		array[1] = std::move(array[numElems]);
		--numElems;
		hundir(1);
	}
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::print(std::ostream & o) const {
	for (auto i = 1; i <= numElems; ++i)
		o << array[i] << " ";
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::flotar(size_t n) {
	T elem = std::move(array[n]);
	size_t hueco = n;
	while (hueco != 1 && antes(elem, array[hueco / 2])) {
		array[hueco] = std::move(array[hueco / 2]);
		hueco /= 2;
	}
	array[hueco] = std::move(elem);
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::hundir(size_t n) {
	T elem = std::move(array[n]);
	size_t hueco = n;
	size_t hijo = 2 * hueco; // hijo izquierdo, si existe
	while (hijo <= numElems)  {
		// cambiar al hijo derecho si existe y va antes que el izquierdo
		if (hijo < numElems && antes(array[hijo + 1], array[hijo]))
			++hijo;
		// flotar el hijo si va antes que el elemento hundiéndose
		if (antes(array[hijo], elem)) {
			array[hueco] = std::move(array[hijo]);
			hueco = hijo; hijo = 2 * hueco;
		}
		else break;
	}
	array[hueco] = std::move(elem);
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::monticulizar() {
	for (auto i = numElems / 2; i > 0; --i)
		hundir(i);
}


#endif /* PRIORITYQUEUE_H_ */
