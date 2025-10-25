#include "ListaSongs.h"
//#include "Cancion.h"
#include "Artista.h"

// -------------------------------------------------------------
// Constructor
// -------------------------------------------------------------
ListaSongs::ListaSongs(const std::string* codigos_iniciales,
                       int                capacidad_inicial,
                       const std::string& codigo_propietario)
    : lista_artistas(nullptr),
    codigo_canciones(nullptr),
    capacidad(capacidad_inicial),
    tamano(0),
    codigo_propietario(codigo_propietario)
{
    if (capacidad <= 0) return;

    codigo_canciones = new std::string[capacidad];
    lista_artistas   = new Artista*[capacidad];

    // inicializamos punteros de artista
    for (int i = 0; i < capacidad; ++i)
        lista_artistas[i] = nullptr;

    // si se pasan códigos iniciales, se copian
    if (codigos_iniciales) {
        // asumimos que la cantidad inicial es la misma que la capacidad dada
        tamano = capacidad;
        for (int i = 0; i < tamano; ++i) {
            codigo_canciones[i] = codigos_iniciales[i];
        }
    }
}

// -------------------------------------------------------------
// Getters básicos
// -------------------------------------------------------------
int ListaSongs::get_num_canciones() const {
    return tamano;
}

int ListaSongs::get_capacidad() const {
    return capacidad;
}

int ListaSongs::get_tamano() const {
    return tamano;
}

std::string ListaSongs::get_codigo_prop() const {
    return codigo_propietario;
}

std::string ListaSongs::get_cancion(int idx) const {
    if (idx < 0 || idx >= tamano) return "";
    return codigo_canciones[idx];
}

Artista* ListaSongs::get_artista(int idx) const {
    if (idx < 0 || idx >= tamano) return nullptr;
    return lista_artistas[idx];
}

// -------------------------------------------------------------
// Búsqueda por código
// -------------------------------------------------------------
Artista* ListaSongs::bus_art_por_can(const std::string& id_song) const
{
    for (int i = 0; i < tamano; ++i) {
        if (codigo_canciones[i] == id_song)
            return lista_artistas[i];
    }
    return nullptr;
}

// -----------------------
