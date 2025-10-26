// Cancion.cpp
#include "cancion.h"
#include "miembroproduccion.h"

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
                 const std::string& id_song,
                 MiembroProduccion** productores_in,
                 short int          n_produtc)
    : nombre(nombre),
    identificador(id_artista + id_album + id_song),
    duracion(duracion),
    dir_archivo_premium(dir_archivo_premium),
    dir_archivo_estandar(dir_archivo_estandar),
    reproducciones(reproducciones),
    productores(nullptr),
    num_productores( (n_produtc < 0) ? 0 : ((n_produtc > 5) ? 5 : n_produtc) ) // cap opcional
{
    if (num_productores > 0) {
        productores = new MiembroProduccion*[num_productores];
        for (int i = 0; i < num_productores; ++i) {
            productores[i] = productores_in[i]; // copiamos el puntero (NO propiedad)
        }
    }
}

Cancion::Cancion(const std::string& nombre_,
                 const std::string& duracionStr,
                 const std::string& dir_archivo_premium_,
                 const std::string& dir_archivo_estandar_,
                 const std::string& reproduccionesStr,
                 const std::string& id_artista,
                 const std::string& id_album,
                 const std::string& id_song,
                 MiembroProduccion** productores_in,
                 const std::string& n_produtc)
    : Cancion(nombre_,
              to_int(duracionStr),
              dir_archivo_premium_,
              dir_archivo_estandar_,
              to_long(reproduccionesStr),
              id_artista,
              id_album,
              id_song,
              productores_in,
              to_short(n_produtc))
{}


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

short int Cancion::get_num_productores() const{ return num_productores; }

Cancion::Cancion(const Cancion& o)
    : nombre(o.nombre),
    identificador(o.identificador),
    duracion(o.duracion),
    dir_archivo_premium(o.dir_archivo_premium),
    dir_archivo_estandar(o.dir_archivo_estandar),
    reproducciones(o.reproducciones),
    productores(nullptr),
    num_productores(o.num_productores)
{
    if (num_productores > 0) {
        productores = new MiembroProduccion*[num_productores];
        for (int i = 0; i < num_productores; ++i) {
            productores[i] = o.productores[i]; // copiar puntero (shallow)
        }
    }
}

Cancion& Cancion::operator=(const Cancion& o) {
    if (this == &o) return *this;

    // copiar triviales
    nombre            = o.nombre;
    identificador             = o.identificador;
    duracion          = o.duracion;
    dir_archivo_premium  = o.dir_archivo_premium;
    dir_archivo_estandar = o.dir_archivo_estandar;
    reproducciones    = o.reproducciones;

    // reemplazar arreglo de punteros (NO borrar los objetos apuntados)
    if (productores) { delete [] productores; productores = nullptr; }
    num_productores = o.num_productores;

    if (num_productores > 0) {
        productores = new MiembroProduccion*[num_productores];
        for (int i = 0; i < num_productores; ++i) {
            productores[i] = o.productores[i]; // copiar puntero (shallow)
        }
    }
    return *this;
}

Cancion::~Cancion() {
    if (productores) { delete [] productores; productores = nullptr; }
}

void Cancion::anadir_ident(const std::string& id_artist,
                                   const std::string& id_albm,
                                   const std::string& id_song)
{
    identificador = id_artist+ id_albm + id_song;
}

bool Cancion::parse_long(const std::string& s, long& out) {
    long val = 0;
    int sign = 1;
    size_t i = 0, n = s.size();

    // espacios iniciales simples
    while (i < n && (s[i] == ' ' || s[i] == '\t')) ++i;
    if (i == n) return false;

    if (s[i] == '+') { ++i; }
    else if (s[i] == '-') { sign = -1; ++i; }

    bool any = false;
    for (; i < n; ++i) {
        char c = s[i];
        if (c < '0' || c > '9') {
            // permitir espacios finales
            while (i < n && (s[i] == ' ' || s[i] == '\t')) ++i;
            if (i == n && any) { out = val * sign; return true; }
            return false;
        }
        any = true;
        val = val * 10 + (c - '0'); // sin control de overflow aquí
    }
    if (!any) return false;
    out = val * sign;
    return true;
}

long Cancion::to_long(const std::string& s, long def) {
    long v;
    if (!parse_long(s, v)) return def;
    return v; // destino es long
}

int Cancion::to_int(const std::string& s, int def) {
    long v;
    if (!parse_long(s, v)) return def;
    // saturación manual al rango int de 32 bits
    const long I_MIN = -2147483648L;
    const long I_MAX =  2147483647L;
    if (v < I_MIN) v = I_MIN;
    if (v > I_MAX) v = I_MAX;
    return static_cast<int>(v);
}

short Cancion::to_short(const std::string& s, short def) {
    long v;
    if (!parse_long(s, v)) return def;
    if (v < -32768L) v = -32768L;
    if (v >  32767L) v =  32767L;
    return static_cast<short>(v);
}
