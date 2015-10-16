/*
* Grupo TAIS16, Samuel Lapuente Jim�nez, Alvar David Soler Rus
*/
//  TreeMapRango.h
//
//  Extensi�n de tablas <clave, valor> como �rboles de b�squeda AVL
//  con una operaci�n para consultar las claves en un rango
//

#ifndef TREEMAPRANGO_H_
#define TREEMAPRANGO_H_

#include <vector>

#include "TreeMap_AVL.h"

template <typename Clave, typename Valor, typename Comparador = std::less<Clave>>
class TreeMapRango : public TreeMap<Clave, Valor, Comparador> {
public:
	
	TreeMapRango(Comparador c = Comparador()) : TreeMap<Clave, Valor, Comparador>(c) {};

	std::vector<Clave> rango(Clave const& k1, Clave const& k2) const {
		std::vector<Clave> lista;
		rango(k1, k2, this->raiz, lista);
		return lista;
	}

protected:
	using TreeNode = typename TreeMap<Clave, Valor, Comparador>::TreeNode;
	using Link = TreeNode *;

	/*Lo primero que comprobamos es que el �rbol exista. Una vez tenemos �rbol nos vamos al elemento m�s peque�o (izquierda del �rbol) o hasta que encontramos un elemento m�s peque�o que k1.
		Una vez estamos en la izquierda del todo, si el elemento en el que estamos situados es menor o igual que k2 y mayor o igual que k1 lo insertamos en la lista. No es necesario comprobar el orden ya 
		que los vamos insertando de menor a mayor. Una vez hemos mirado ese elemento, si donde estamos el elemento no es m�s grande que k2, miramos el �rbol derecho.
		
		El coste de esta funci�n es, en su caso peor, lineal en el n�mero de nodos del �rbol (en el caso que todos los elementos contenidos por este est�n dentro del rango de k1 y k2), pero gracias a estas
		comprobaciones que hacemos no ser� lo habitual, as� que ser� lineal siempre pero con suerte menor que los nodos del �rbol*/

	void rango(Clave const& k1, Clave const& k2, Link a, std::vector<Clave> & lista) const {
		if (a != nullptr){ 
			if (!this->menor(a->cv.clave, k1))rango(k1, k2, a->iz, lista);
			if ((this->menor(k1, a->cv.clave) || a->cv.clave == k1) && (this->menor(a->cv.clave, k2) || a->cv.clave == k2)) {
				lista.push_back(a->cv.clave);
			}
			if (!this->menor(k2, a->cv.clave)) rango(k1, k2, a->dr, lista);
		}
	}
};



#endif /* TREEMAPRANGO_H_ */
