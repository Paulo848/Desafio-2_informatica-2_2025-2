// Album.cpp
#include "Album.h"
#include "cancion.h"

// Constructor por defecto
Album::Album()
    : nombre(),
    identificador(),
    duracion(0),
    selloDiscografico(),
    fecha_lanzamiento(),
    puntuacion(0),
    dir_portada(),
    generos(nullptr),
    num_generos(0),
    canciones(nullptr),
    num_canciones(0)
{}

// Constructor con parámetros (según tu header)
Album::Album(const std::string& nombre,
             short int          duracion,
             const std::string& selloDiscografico,
             const std::string& fecha_lanzamiento,
             short int          puntuacion,
             const std::string& dir_portada,
             std::string*       generos,
             short int          num_generos,
             short int          num_canciones,
             const std::string  id_artista,
             const std::string  id_album
             )
    : nombre(nombre),
    duracion(duracion),
    selloDiscografico(selloDiscografico),
    fecha_lanzamiento(fecha_lanzamiento),
    puntuacion(puntuacion),
    dir_portada(dir_portada),
    generos(generos),          // copia superficial; luego lo manejamos si hace falta
    num_generos(num_generos),
    canciones(nullptr),
    num_canciones(num_canciones),
    capacidad_can(0),
    tamano_can(0)
{
    identificador = id_artista + id_album;
}

bool Album::iniciar_array_cancion(std::size_t n)
{
    if (n == 0) return false;

    canciones = new Cancion*[n];
    capacidad_can = static_cast<int>(n);
    tamano_can = 0;
    num_canciones = 0;

    for (int i = 0; i < capacidad_can; ++i)
        canciones[i] = nullptr;

    return true;
}

bool Album::anadir_cancion(Cancion& cancion)
{
    if (!canciones) return false;                 // no inicializado
    if (tamano_can >= capacidad_can) return false; // arreglo lleno

    canciones[tamano_can] = &cancion;
    tamano_can++;
    num_canciones++;
    return true;
}

Cancion* Album::get_cancion(const std::string& id)
{
    if (!canciones) return nullptr;

    // Normaliza el id a los 2 dígitos de canción
    std::string songId;
    if (id.size() == 2) {
        songId = id;               // id local de canción dentro del álbum
    } else if (id.size() == 9) {
        songId = id.substr(7, 2);  // AAAAAA[CC] (5 artista + 2 álbum + 2 canción)
    } else {
        return nullptr;            // formatos no admitidos aquí
    }

    // Buscar en el arreglo actual (0 .. tamano_can-1)
    for (int i = 0; i < tamano_can; ++i) {
        if (!canciones[i]) continue;

        const std::string& full = canciones[i]->get_ident(); // 9 dígitos
        if (full.size() >= 9) {
            std::string cur = full.substr(7, 2); // últimos 2 = id canción
            if (cur == songId) {
                return canciones[i];
            }
        }
    }

    return nullptr; // no encontrada
}

std::string* Album::get_generos(short int index) const {// Devuelve puntero al género en 'index' (o nullptr si inválido)
    if (!generos || index < 0 || index >= num_generos) return nullptr;
    return &generos[index];
}

// Getters pequeños
int                 Album::get_capacidad_can() const { return capacidad_can; }
int                 Album::get_tamano_can() const { return tamano_can; }
std::string         Album::get_nombre() const        { return nombre; }
std::string         Album::get_ident()         const { return identificador; }
std::string         Album::get_dir_portada() const   { return dir_portada; }
std::string         Album::get_sell_disc() const     { return selloDiscografico; }
int                 Album::get_punt() const          { return static_cast<int>(puntuacion); }
short int           Album::get_num_gen() const       { return num_generos; }
short int           Album::get_num_songs() const     { return num_canciones; }

Album::~Album()
{
    // Si se inicializó con iniciar_array_cancion, liberamos el ARREGLO de punteros.
    // OJO: NO borramos *canciones[i] porque el álbum no es dueño de esas Cancion.
    delete[] canciones;
    canciones = nullptr;
    capacidad_can = 0;
    tamano_can = 0;

    // Liberamos el arreglo de géneros si fue reservado con new[].
    // Esto asume propiedad del array 'generos'. Si lo presta un tercero, elimina esta línea.
    delete[] generos;
    generos = nullptr;
    num_generos = 0;
}
