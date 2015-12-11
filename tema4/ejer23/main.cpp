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
	if (hora < rhs.hora) return hora < rhs.hora;		
    }
};

struct Pelicula {
    Tiempo inicio;
    Tiempo fin;
    bool operator<(const Pelicula& rhs) const { fin < rhs.fin; }
};

int resuelve(std::vector<int> const & pilas, int const V) {
    int total = 0;
    size_t aux = pilas.size() - 1;

    for (size_t i = 0; i < pilas.size() && aux >= 0 && i < aux; ++i) {
	if (pilas[i] + pilas[aux] >= V) {
	    ++total;
	    --aux;
	}
    }

    return total;
}

void resuelveCaso(int const n) {
    std::string hora;
    std::vector<Pelicula> peliculas(n);
    Tiempo aux, auxFin;
    unsigned int duracion;
    for (size_t i = 0; i < n; ++i) {
	std::cin >> hora;
	std::cin >> duracion;
	aux.hora = atoi(hora.substr(0, hora.find(":")).c_str());
	aux.minutos = atoi(hora.erase(0, hora.find(":") + 1).c_str());


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
    
    for (Pelicula pelicula : peliculas){
	std::cout << "Inicio: " << pelicula.inicio.hora << ":" << pelicula.inicio.minutos << " Fin: " << pelicula.fin.hora << ":" << pelicula.fin.minutos << std::endl;
    }
    

//    std::cout << resuelve(pilas, voltaje) << std::endl;

}

int main() {
#ifndef DOMJUDGE

    std::ifstream in("casos.txt");

    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt

#endif
    unsigned int casos;
    std::cin >> casos;
    while (casos != 0){
	resuelveCaso(casos);
	std::cin >> casos;
    }


#ifndef DOMJUDGE

    std::cin.rdbuf(cinbuf); //reset to standard input again

    system("PAUSE");
#endif
    return 0;
}