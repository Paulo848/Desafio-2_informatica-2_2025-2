// Artista.cpp
#include "artista.h"
#include "album.h"

Artista::Artista()
    : nickname(),
    identificador(),
    edad(0),
    pais(),
    numSeguidores(0),
    rankingGlobal(0),
    albumes(nullptr),
    numAlbumes(0),
    capacidad_alb(0),
    tamano_alb(0)
{}

Artista::Artista(const std::string& nickname,
                 const std::string& identificador,
                 int                edad,
                 const std::string& pais,
                 long int           numSeguidores,
                 long int           rankingGlobal,
                 short int          numAlbumes)
    : nickname(nickname),
    identificador(identificador),
    edad(edad),
    pais(pais),
    numSeguidores(numSeguidores),
    rankingGlobal(rankingGlobal),
    albumes(nullptr),
    numAlbumes(numAlbumes),
    capacidad_alb(0),
    tamano_alb(0)
{
    this->iniciar_array_album(this->get_num_albumes());
}

Artista::Artista(const std::string& nickname_,
                 const std::string& identificador_,
                 const std::string& edadStr,
                 const std::string& pais_,
                 const std::string& numSegStr,
                 const std::string& rankStr,
                 const std::string& numAlbStr)
    : Artista(nickname_,
              identificador_,
              to_int(edadStr),
              pais_,
              to_long(numSegStr),
              to_long(rankStr),
              to_short(numAlbStr)) {}

bool Artista::iniciar_array_album(std::size_t n)
{
    if (n == 0) return false;
    albumes = new Album*[n];   // arreglo de punteros
    capacidad_alb = static_cast<int>(n);
    tamano_alb = 0;

    // se inicializa en nullptr para evitar basura
    for (int i = 0; i < capacidad_alb; ++i)
        albumes[i] = nullptr;

    return true;
}

bool Artista::anadir_album(const Album& album) {
    if (!albumes || tamano_alb >= capacidad_alb) return false;
    albumes[tamano_alb++] = new Album(album);
    return true;
}

Artista::~Artista() {
    if (albumes) {
        for (int i = 0; i < tamano_alb; ++i) delete albumes[i];
        delete [] albumes;
    }
}

Album* Artista::get_album(const std::string& id)
{
    if (!albumes) return nullptr;

    std::string albumId7; // AAAAAAA (5 artista + 2 álbum)
    std::string albumId2; // AA (solo álbum)

    if (id.size() == 2) {
        albumId2 = id;                  // id local de álbum
    } else if (id.size() == 7) {
        albumId7 = id;                  // id completo de álbum
    } else if (id.size() == 9) {
        albumId7 = id.substr(0, 7);     // de canción → AAAAAAA
    } else {
        return nullptr;                 // formato no soportado
    }

    for (int i = 0; i < tamano_alb; ++i) {
        if (!albumes[i]) continue;

        const std::string& cur = albumes[i]->get_ident(); // debe ser 7 dígitos
        if (cur.size() >= 7) {
            if (!albumId7.empty() && cur == albumId7) {
                return albumes[i];
            }
            if (!albumId2.empty() && cur.substr(5, 2) == albumId2) {
                return albumes[i];
            }
        }
    }
    return nullptr;
}

bool Artista::parse_long(const std::string& s, long& out) {
    long val = 0;
    int sign = 1;
    size_t i = 0, n = s.size();

    // saltar espacios simples (sin <cctype>)
    while (i < n && (s[i] == ' ' || s[i] == '\t')) ++i;
    if (i == n) return false;

    if (s[i] == '+') { ++i; }
    else if (s[i] == '-') { sign = -1; ++i; }

    bool anyDigit = false;
    for (; i < n; ++i) {
        char c = s[i];
        if (c < '0' || c > '9') {
            while (i < n && (s[i] == ' ' || s[i] == '\t')) ++i;
            return anyDigit && i == n ? (out = val * sign, true) : false;
        }
        anyDigit = true;

        // acumulación sin comprobar overflow (luego saturamos en los to_*)
        val = val * 10 + (c - '0');
    }
    if (!anyDigit) return false;
    out = val * sign;
    return true;
}

long Artista::to_long(const std::string& s, long def) {
    long v;
    if (!parse_long(s, v)) return def;
    return v; // sin límites (long es el destino)
}

int Artista::to_int(const std::string& s, int def) {
    long v;
    if (!parse_long(s, v)) return def;

    // saturación manual a rango de int de 32 bits
    const long INT_MIN_L = -2147483648L;
    const long INT_MAX_L =  2147483647L;
    if (v < INT_MIN_L) v = INT_MIN_L;
    if (v > INT_MAX_L) v = INT_MAX_L;
    return static_cast<int>(v);
}

short Artista::to_short(const std::string& s, short def) {
    long v;
    if (!parse_long(s, v)) return def;

    // saturación manual a rango de short
    if (v < -32768L) v = -32768L;
    if (v >  32767L) v =  32767L;
    return static_cast<short>(v);
}

Artista::Artista(const Artista& o)
    : nickname(o.nickname),
    identificador(o.identificador),
    edad(o.edad),
    pais(o.pais),
    numSeguidores(o.numSeguidores),
    rankingGlobal(o.rankingGlobal),
    albumes(nullptr),
    numAlbumes(o.numAlbumes),
    capacidad_alb(o.capacidad_alb),
    tamano_alb(0)
{
    if (capacidad_alb > 0) {
        albumes = new Album*[capacidad_alb];
        for (int i = 0; i < capacidad_alb; ++i) albumes[i] = nullptr;
        for (int i = 0; i < o.tamano_alb; ++i) {
            if (o.albumes[i]) albumes[i] = new Album(*o.albumes[i]);
        }
        tamano_alb = o.tamano_alb;
    }
}

Artista& Artista::operator=(const Artista& o) {
    if (this == &o) return *this;

    // copiar triviales
    nickname      = o.nickname;
    identificador = o.identificador;
    edad          = o.edad;
    pais          = o.pais;
    numSeguidores = o.numSeguidores;
    rankingGlobal = o.rankingGlobal;
    numAlbumes    = o.numAlbumes;

    // liberar estado actual
    if (albumes) {
        for (int i = 0; i < tamano_alb; ++i) delete albumes[i];
        delete [] albumes;
        albumes = nullptr;
    }

    capacidad_alb = o.capacidad_alb;
    tamano_alb    = 0;

    // copiar álbumes (deep)
    if (capacidad_alb > 0) {
        albumes = new Album*[capacidad_alb];
        for (int i = 0; i < capacidad_alb; ++i) albumes[i] = nullptr;
        for (int i = 0; i < o.tamano_alb; ++i) {
            if (o.albumes[i]) albumes[i] = new Album(*o.albumes[i]);
        }
        tamano_alb = o.tamano_alb;
    }
    return *this;
}


// Getters
std::string Artista::get_nom()         const { return nickname; }
std::string Artista::get_ident()         const { return identificador; }
int         Artista::get_edad()        const { return edad; }
std::string Artista::get_pais()        const { return pais; }
long int    Artista::get_num_follows() const { return numSeguidores; }
long int    Artista::get_global_rank() const { return rankingGlobal; }
short int   Artista::get_num_albumes() const { return numAlbumes; }

int Artista::get_capacidad_alb() const { return capacidad_alb; }
int Artista::get_tamano_alb() const { return tamano_alb; }

// Alias opcional
std::string Artista::get_nombre() const { return nickname; }
