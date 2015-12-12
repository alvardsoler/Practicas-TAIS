/**
 * TAIS16. Álvar Soler y Samuel Lapuente
 * Ejercicio 23.
 *
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Tiempo {
    unsigned int hora;
    unsigned int minutos;

    bool operator<(const Tiempo& rhs) const {
	if (hora == rhs.hora) return minutos < rhs.minutos;
	return hora < rhs.hora;
    }

    bool operator<=(const Tiempo& rhs) const {
	if (hora == rhs.hora) return minutos <= rhs.minutos;
	return hora <= rhs.hora;
    }
};

struct Pelicula {
    Tiempo inicio;
    Tiempo fin;

    bool operator<(const Pelicula& rhs) const {
	return fin < rhs.fin;
    }

    bool operator<=(const Pelicula& rhs) const {
	return fin <= rhs.fin;
    }
};

void addTiempoDescanso(Tiempo & temp) {
    temp.minutos += 10;
    if (temp.minutos >= 60) {
	temp.minutos -= 60;
	temp.hora += 1;
    }
}

int resuelve(std::vector<Pelicula> const & peliculas) {
    int total = 1;

    Tiempo t;
    t = peliculas[0].fin;
    addTiempoDescanso(t);

    for (size_t i = 1; i < peliculas.size(); ++i) {
	if (t <= peliculas[i].inicio) {
	    ++total;
	    t = peliculas[i].fin;
	    addTiempoDescanso(t);
	}
    }

    return total;
}

void resuelveCaso(int const n) {

    std::vector<Pelicula> peliculas(n);
    Tiempo aux, auxFin;
    int hh, mm, duracion;
    char c;

    for (size_t i = 0; i < n; ++i) {
	std::cin >> hh >> c >> mm;

	std::cin >> duracion;
	aux.hora = hh;
	aux.minutos = mm;

	auxFin.minutos = aux.minutos + (int) (duracion % 60);
	auxFin.hora = aux.hora + (int) (duracion / 60);
	if (auxFin.minutos >= 60) {
	    auxFin.minutos -= 60;
	    ++auxFin.hora;
	}
	Pelicula p;
	p.fin = auxFin;
	p.inicio = aux;
	peliculas[i] = p;
    }

    std::sort(peliculas.begin(), peliculas.end());

    std::cout << resuelve(peliculas) << std::endl;


}

int main() {
#ifndef DOMJUDGE

    std::ifstream in("casos.txt");

    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif
    unsigned int casos;
    std::cin >> casos;
    while (casos != 0) {
	resuelveCaso(casos);
	std::cin >> casos;
	//	std::cout << "---" << std::endl;
    }


#ifndef DOMJUDGE

    std::cin.rdbuf(cinbuf); //reset to standard input again

    system("PAUSE");
#endif
    return 0;
}
