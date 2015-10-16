/* 
 * File:   TreeMap_AVLRef.h
 * Author: furia
 *
 * Created on 16 de octubre de 2015, 18:51
 */

#ifndef TREEMAP_AVLREF_H
#define	TREEMAP_AVLREF_H
#include "TreeMap_AVL.h"

template <typename Clave, typename Valor, typename Comparador = std::less<Clave>>
class TreeMap_AVLRef : public TreeMap<Clave, Valor, Comparador> {
public:

    TreeMap_AVLRef(Comparador c = Comparador()) : TreeMap<Clave, Valor, Comparador>(c) {
    };

    
    TreeMap<Clave, Valor, Comparador>::TreeNode &operator[](const Clave &clave) {
	/* Lo ideal sería que le pedimos la palabra a buscar, si no está, devuelve un puntero vacío y entonces insertamos.
	 * Si sí está, devuelve el puntero al TreeNode donde está insertado, y así podríamos añadir el nuevo valor sin copiar datos */

	TreeNode * ret = this->buscar(clave, this->raiz);
	//
	if (ret == NULL) {
	    //
	    //	    // No está, lo añadimos y vemos dónde
	    //
	    //	    // quedó. Hay formas más eficientes para evitar
	    //
	    //	    // recorridos por el árbol.
	    //
	    this->insert(clave, Valor());
	    //
	    ret = this->buscar(clave, this->raiz);
	    //
	}
	//
	return ret; //cv.valor;
    }

protected:
    using TreeNode = typename TreeMap<Clave, Valor, Comparador>::TreeNode;
    using Link = TreeNode *;
};

#endif	/* TREEMAP_AVLREF_H */

