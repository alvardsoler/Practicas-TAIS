#ifndef COLAURGENCIAS_H
#define	COLAURGENCIAS_H
#include <iostream>
#include <queue>          // std::priority_queue
#include <vector>         // std::vector

const size_t TAM_INICIAL = 100;

class ColaUrgencias {
private:

    struct Enfermo {
	int gravedad;
	std::string nombre;
	int indice;

	bool operator<(const Enfermo& rhs) const {
	    return (this->gravedad == rhs.gravedad) ? (this->indice > rhs.indice) : (this->gravedad < rhs.gravedad);
	}

    };
    std::priority_queue<Enfermo, std::vector<Enfermo>> elementos;

    int contador;

public:

    /** Constructor:  */
    ColaUrgencias() {
	contador = 0;
    }

    void insertar(std::string nombre, int gravedad);

    bool esVacia() const;

    std::string nombrePrimero() const;

    void quitarPrimero();

};

void ColaUrgencias::insertar(std::string nombre, int gravedad) {
    Enfermo e;
    e.gravedad = gravedad;
    e.nombre = nombre;
    e.indice = contador;
    ++contador;
    elementos.push(e);
}

bool ColaUrgencias::esVacia() const {
    return elementos.empty();
}

std::string ColaUrgencias::nombrePrimero() const {
    return elementos.top().nombre;
}

void ColaUrgencias::quitarPrimero() {
    elementos.pop();--contador;
}

#endif	/* COLAURGENCIAS_H */

