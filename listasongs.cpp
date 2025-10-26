#include "listasongs.h"
#include "artista.h"
#include "album.h"
#include "cancion.h"

// -------------------------------------------------------------
// Constructor
// -------------------------------------------------------------
ListaSongs::ListaSongs(const std::string* codigos_iniciales,
                       const std::string& codigo_propietario,
                       int                capacidad_inicial
                       )
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
// Constructor de copia
// -------------------------------------------------------------
ListaSongs::ListaSongs(const ListaSongs& other)
    : lista_artistas(nullptr),
    codigo_canciones(nullptr),
    capacidad(other.capacidad),
    tamano(other.tamano),
    codigo_propietario(other.codigo_propietario)
{
    if (capacidad <= 0) return;

    codigo_canciones = new std::string[capacidad];
    lista_artistas   = new Artista*[capacidad];

    for (int i = 0; i < capacidad; ++i)
        lista_artistas[i] = nullptr;

    for (int i = 0; i < tamano; ++i) {
        codigo_canciones[i] = other.codigo_canciones[i];
        lista_artistas[i]   = other.lista_artistas[i];
    }
}

// -------------------------------------------------------------
// Operador de asignación por copia
// -------------------------------------------------------------
ListaSongs& ListaSongs::operator=(const ListaSongs& other)
{
    if (this == &other) return *this;

    std::string* nuevos_codigos = nullptr;
    Artista**    nuevos_artistas = nullptr;

    int nueva_capacidad = other.capacidad;
    int nuevo_tamano    = other.tamano;

    if (nueva_capacidad > 0) {
        nuevos_codigos  = new std::string[nueva_capacidad];
        nuevos_artistas = new Artista*[nueva_capacidad];

        for (int i = 0; i < nueva_capacidad; ++i)
            nuevos_artistas[i] = nullptr;

        for (int i = 0; i < nuevo_tamano; ++i) {
            nuevos_codigos[i]  = other.codigo_canciones[i];
            nuevos_artistas[i] = other.lista_artistas[i];
        }
    }

    delete[] codigo_canciones;
    delete[] lista_artistas;

    codigo_canciones   = nuevos_codigos;
    lista_artistas     = nuevos_artistas;
    capacidad          = nueva_capacidad;
    tamano             = nuevo_tamano;
    codigo_propietario = other.codigo_propietario;

    return *this;
}

ListaSongs::~ListaSongs()
{
    delete[] codigo_canciones;
    delete[] lista_artistas;
}


bool ListaSongs::anadir_cancion(Artista& art, const std::string& id9)
{
    // 1) Validaciones básicas
    if (id9.size() != 9) return false;           // AAAAA + AA + AA
    if (tamano >= capacidad) return false;       // sin crecimiento aún
    if (art.get_ident() != id9.substr(0,5)) return false; // consistencia artista↔id

    // 2) Resolver álbum y canción
    Album* alb = art.get_album(id9.substr(5,2)); // usa "AA"
    if (!alb) return false;

    // get_cancion puede aceptar 9 o 2 dígitos según tu implementación
    Cancion* can = alb->get_cancion(id9);
    if (!can) {
        can = alb->get_cancion(id9.substr(7,2)); // "AA" de la canción
        if (!can) return false;
    }

    // (Opcional) deduplicado: si no quieres duplicados, descomenta
    // for (int i = 0; i < tamano; ++i) if (codigo_canciones[i] == id9) return false;

    // 3) Insertar
    codigo_canciones[tamano] = id9;
    lista_artistas[tamano]   = &art;
    ++tamano;

    return true;
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
