// Cancion.cpp
#include "Cancion.h"
#include "MiembroProduccion.h"

// Constructor por defecto
Cancion::Cancion()
    : nombre(),
    duracion(0),
    dir_archivo_premium(),
    dir_archivo_estandar(),
    reproducciones(0),
    productores(nullptr),
    identificador() {}

// Constructor con parámetros
Cancion::Cancion(const std::string& nombre,
                 int                duracion,
                 const std::string& dir_archivo_premium,
                 const std::string& dir_archivo_estandar,
                 long int           reproducciones,
                 const std::string& id_artista,
                 const std::string& id_album,
                 const std::string& id_song)
    : nombre(nombre),
    duracion(duracion),
    dir_archivo_premium(dir_archivo_premium),
    dir_archivo_estandar(dir_archivo_estandar),
    reproducciones(reproducciones),
    productores(nullptr)
{
    // Creamos el identificador concatenando los 3 ids
    identificador = id_artista + id_album + id_song;
}

// Getters
std::string Cancion::get_nombre() const {
    return nombre;
}

std::string Cancion::get_dir_archivo_stndr() const {
    return dir_archivo_estandar;
}

std::string Cancion::get_dir_archivo_prmm() const {
    return dir_archivo_premium;
}

int Cancion::get_duracion() const {
    return duracion;
}

long int Cancion::get_reproducciones() const {
    return reproducciones;
}

// Reproducciones
void Cancion::aumentar_reproducciones() {
    ++reproducciones;
}

// Identificador
std::string Cancion::get_ident() const {
    return identificador;
}

void Cancion::anadir_ident(const std::string& id_artist,
                                   const std::string& id_albm,
                                   const std::string& id_song)
{
    identificador = id_artist + "-" + id_albm + "-" + id_song;
}
