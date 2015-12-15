/**
 * TAIS16. Álvar Soler y Samuel Lapuente
 * Ejercicio 25.
 *
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Trabajo {
    int comienzo;
    int fin;

    bool operator<(const Trabajo & rhs) const {
	return comienzo < rhs.comienzo;
    }

    bool operator<=(const Trabajo & rhs) const {
	return comienzo <= rhs.comienzo;
    }
};

int resuelve(std::vector<Trabajo> const & t, Trabajo intervalo) {
    Trabajo candidato;
    candidato.comienzo = t[0].comienzo;
    candidato.fin = t[0].fin;
    int intervalos = 0;

    for (size_t i = 1; i < t.size(); ++i) {
	if (candidato.fin <= t[i].fin) {
	    if (t[i].comienzo <= intervalo.comienzo) {
		candidato = t[i]; //este es mejor candidato, sigue completando por la izquierda y rellena más por la derecha
	    } else if (t[i].comienzo > intervalo.comienzo) {
		intervalos++; //el que teniamos como candidato ya sabemos que es necesario.
		intervalo.comienzo = candidato.fin; //ya lo que nos falta por rellenar va desde el final de nuestro candidato puesto hasta el final
		candidato = t[i]; //este en el que estamos puede ser también necesario en el siguiente tramo, sin completar al anterior por la izquierda.
	    }

	}
	if (intervalo.comienzo >= intervalo.fin)
	    return intervalos;

	if (candidato.comienzo > intervalo.comienzo)
	    return 0; //ya no vamos a poder rellenar ese hueco

    }

    if (candidato.comienzo <= intervalo.comienzo && candidato.fin >= intervalo.fin)
	++intervalos; //si con el candidato que vamos a considerar lo completamos, es correcto

    return intervalos;
}

void resuelveCaso(unsigned int const a, unsigned int const b, unsigned int const n) {
    std::vector<Trabajo> trabajos(n);
    int c, f;
    Trabajo intervalo, aux;
    intervalo.comienzo = a;
    intervalo.fin = b;
    for (size_t i = 0; i < n; ++i) {
	std::cin >> c >> f;
	aux.comienzo = c;
	aux.fin = f;
	trabajos[i] = aux;
    }

    std::sort(trabajos.begin(), trabajos.end()); //ordenamos por comienzo.
    int r = resuelve(trabajos, intervalo);
    if (r == 0) {
	std::cout << "Imposible" << std::endl;
    } else {
	std::cout << r << std::endl;
    }
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif
    unsigned int a, b, casos;
    std::cin >> a >> b >> casos;
    while (casos != 0) {
	resuelveCaso(a, b, casos);
	std::cin >> a >> b >>casos;
    }


#ifndef DOMJUDGE

    std::cin.rdbuf(cinbuf); //reset to standard input again

    system("PAUSE");
#endif
    return 0;
}