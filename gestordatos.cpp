#include "gestordatos.h"
#include "cancion.h"
#include "miembroproduccion.h"
#include "sistema.h"
#include "artista.h"
#include "album.h"
#include "usuario.h"
#include "anuncio.h"
#include "listasongs.h"
#include <fstream>
#include <iostream>


// Si necesitas estas clases, incluye sus headers reales
// #include "Artista.h"
// #include "Usuario.h"
// #include "Anuncio.h"

using std::string;

// ================== Ciclo de vida ==================

GestorDatos::GestorDatos(Sistema* sys,
                         const std::string& rutaBase,
                         char sep,
                         unsigned int tamBuffer,
                         unsigned int seed)
    : sistema_raiz(sys),
    ruta_base(rutaBase),
    separador(sep),
    buffer_linea(nullptr),
    tam_buffer(tamBuffer),
    num_errores(0),
    rng_seed(seed) {
    // (Opcional) reservar buffer simple si quieres
    // buffer_linea = new char[tam_buffer];
}

GestorDatos::~GestorDatos() {
    // if (buffer_linea) { delete [] buffer_linea; buffer_linea = nullptr; }
}

// ================== Configuración ==================

void GestorDatos::set_ruta_base(const std::string& ruta) { ruta_base = ruta; }
void GestorDatos::set_separador(char sep) { separador = sep; }
void GestorDatos::set_seed(unsigned int seed) { rng_seed = seed; }
void GestorDatos::set_buffer(char* buffer_externo, unsigned int tam) {
    buffer_linea = buffer_externo; tam_buffer = tam;
}
unsigned int GestorDatos::errores() const { return num_errores; }

// ================== CARGA (LECTURA) ==================

bool GestorDatos::cargar_todo(const std::string& artistas_csv,
                              const std::string& albums_csv,
                              const std::string& songs_csv,
                              const std::string& miembros_csv,
                              const std::string& ads_csv,
                              const std::string& usuarios_csv,
                              const std::string& favoritos_csv) {
    // Orden recomendado
    if (!cargar_miembros(miembros_csv))   return false;
    if (!cargar_artistas(artistas_csv))   return false;
    if (!cargar_albums(albums_csv))       return false;
    if (!cargar_songs(songs_csv))         return false;
    if (!cargar_ads(ads_csv))             return false;
    if (!cargar_usuarios(usuarios_csv))   return false;
    if (!cargar_favoritos(favoritos_csv)) return false;
    return true;
}

bool GestorDatos::cargar_miembros(const std::string& ruta_csv) {
    std::ifstream f(ruta_csv);
    if (!f.is_open()) return false;

    std::string linea;

    if (!std::getline(f, linea)) return false;

    while (std::getline(f, linea)) {

        if (!linea.empty() && linea.back()=='\r') linea.pop_back();

        std::string campos[4];
        std::size_t n_e = 0;
        std::size_t start = 0;
        while (n_e < 3) {
            std::size_t pos = linea.find(separador, start);
            if (pos == std::string::npos) break;
            campos[n_e++] = linea.substr(start, pos - start);
            start = pos + 1;
        }
        // último campo (o línea con menos comas)
        if (start <= linea.size() && n_e < 4) campos[n_e++] = linea.substr(start);

        if (n_e != 4) { ++num_errores; continue; }

        const std::string& codigo       = campos[0];
        const std::string& nombre       = campos[1];
        const std::string& apellidos    = campos[2];
        const std::string& tipoMiembro  = campos[3];

        // Construye y agrega
        MiembroProduccion mp(codigo, nombre, apellidos, tipoMiembro);

        std::cout << mp.get_codigo() << "|" << mp.get_nombre() << "|"  << mp.get_apellidos() << "|" << mp.get_tipo_miembro() << "|";
        sistema_raiz->anadir_miembro(mp);  // asegúrate de tener este método

        std::cout << "it works" << std::endl;

    }
    return true;
}

bool GestorDatos::cargar_artistas(const std::string& ruta_csv) {
    std::ifstream f(ruta_csv);
    if (!f.is_open()) return false;

    std::string linea;

    if (!std::getline(f, linea)) return false;

    while (std::getline(f, linea)) {

        if (!linea.empty() && linea.back()=='\r') linea.pop_back();

        std::string campos[7];
        std::size_t n_e = 0;
        std::size_t start = 0;
        while (n_e < 6) {
            std::size_t pos = linea.find(separador, start);
            if (pos == std::string::npos) break;
            campos[n_e++] = linea.substr(start, pos - start);
            start = pos + 1;
        }
        // último campo (o línea con menos comas)
        if (start <= linea.size() && n_e < 7) campos[n_e++] = linea.substr(start);

        if (n_e != 7) { ++num_errores; continue; }

        const std::string& identificador       = campos[0];
        const std::string& nickname    = campos[1];
        const std::string& edad  = campos[2];
        const std::string& pais       = campos[3];
        const std::string& seguidores       = campos[4];
        const std::string& ranking_global    = campos[5];
        const std::string& num_albumes  = campos[6];

        // Construye y agrega
        Artista art(nickname, identificador, edad, pais, seguidores, ranking_global, num_albumes);

        std::cout << art.get_ident() << "|" << art.get_nombre() << "|"  << art.get_edad() << "|" << art.get_pais() << "|" << art.get_num_follows() << "|" << art.get_global_rank() << "|" << art.get_num_albumes() << "|";
        sistema_raiz->anadir_artista(art);

        std::cout << "it works" << std::endl;

    }
    return true;
}

bool GestorDatos::cargar_albums(const std::string& ruta_csv) {
    std::ifstream f(ruta_csv);
    if (!f.is_open()) return false;

    std::string linea;

    if (!std::getline(f, linea)) return false;

    while (std::getline(f, linea)) {

        if (!linea.empty() && linea.back()=='\r') linea.pop_back();

        std::string campos[13];
        std::size_t n_e = 0;
        std::size_t start = 0;
        while (n_e < 12) {
            std::size_t pos = linea.find(separador, start);
            if (pos == std::string::npos) break;
            campos[n_e++] = linea.substr(start, pos - start);
            start = pos + 1;
        }
        // último campo (o línea con menos comas)
        if (start <= linea.size() && n_e < 13) campos[n_e++] = linea.substr(start);

        if (n_e != 13) { ++num_errores; continue; }

        const std::string identificadorArtista         = campos[0];
        const std::string identificador                = campos[1];
        const std::string& nickname                     = campos[2];
        const std::string& duracion                     = campos[3];
        const std::string& selloDiscografico             = campos[4];
        const std::string& fechaLanzamiento             = campos[5];
        const std::string& puntuacion                   = campos[6];
        const std::string& dirPortada                   = campos[7];
        const std::string& genero_1                     = campos[8];
        const std::string& genero_2                     = campos[9];
        const std::string& genero_3                     = campos[10];
        const std::string& genero_4                     = campos[11];
        const std::string& numCanciones                 = campos[12];

        std::cout << identificadorArtista << " " << identificador << " " << nickname << " "
                  << duracion << " " << selloDiscografico << " " << fechaLanzamiento << " "
                  << puntuacion << " " << dirPortada << " " << genero_1 << " "
                  << genero_2 << " " << genero_3 << " " << genero_4 << " "
                  << numCanciones << std::endl;

        short int nGen = 0;
        short int valid_str = 0;
        std::string generos[4] ;

        //std::cout << std::endl;
        while(nGen < 4){
            if(campos[8+nGen] != "") generos[valid_str++] = campos[8+nGen];
            nGen++;
        }
        //std::cout << std::endl;

        for(int i = 0; i<valid_str; i++) std::cout << "-" << generos[i] << "-";
        std::cout << std::endl;

        std::string nGener = std::to_string(valid_str);

        // Construye y agrega
        Album albm(nickname, duracion,
                   selloDiscografico, fechaLanzamiento,
                   puntuacion, dirPortada,
                   generos, nGener,
                   numCanciones, identificadorArtista,
                   identificador);

        std::cout << "{nombre:'" << albm.get_nombre()
                  << "', ident:'" << albm.get_ident()
                  << "', duracion:" << albm.get_duracion()
                  << ", sello:'" << albm.get_sell_disc()
                  << "', fecha:'" << albm.get_date_lanzm()
                  << "', puntuacion:" << albm.get_puntuacion()
                  << ", dir_portada:'" << albm.get_dir_portada()
                  << "', num_generos:" << albm.get_num_gen()
                  << "', generos:'" << albm.generos_como_texto()
                  << ", num_canciones:" << albm.get_num_songs()
                  << ", capacidad_can:" << albm.get_capacidad_can()
                  << ", tamano_can:" << albm.get_tamano_can()
                  << "}" << std::endl;


        Artista* art_act = sistema_raiz->get_artista(identificadorArtista);
        bool add_art = art_act->anadir_album(albm);
        if(!add_art) num_errores++;

        std::cout << "\n" << std::endl;

    }
    return true;
}

bool GestorDatos::cargar_songs(const std::string& ruta_csv) {
    std::ifstream f(ruta_csv);
    if (!f.is_open()) return false;

    std::string linea;

    if (!std::getline(f, linea)) return false;

    while (std::getline(f, linea)) {

        if (!linea.empty() && linea.back()=='\r') linea.pop_back();

        std::string campos[13];
        std::size_t n_e = 0;
        std::size_t start = 0;
        while (n_e < 12) {
            std::size_t pos = linea.find(separador, start);
            if (pos == std::string::npos) break;
            campos[n_e++] = linea.substr(start, pos - start);
            start = pos + 1;
        }
        // último campo (o línea con menos comas)
        if (start <= linea.size() && n_e < 13) campos[n_e++] = linea.substr(start);

        if (n_e != 13) { ++num_errores; continue; }

        const std::string& identificadorArtista                     = campos[0];
        const std::string& albumidentificador                       = campos[1];
        const std::string& cancionidentificador                    = campos[2];
        const std::string& nickname                                = campos[3];
        const std::string& duracion                                = campos[4];
        const std::string& direccionpremium                        = campos[5];
        const std::string& direccionestandar                       = campos[6];
        const std::string& reproducciones                          = campos[7];
        const std::string& miembroProduccion_1                     = campos[8];
        const std::string& miembroProduccion_2                     = campos[9];
        const std::string& miembroProduccion_3                     = campos[10];
        const std::string& miembroProduccion_4                     = campos[11];
        const std::string& miembroProduccion_5                     = campos[12];

        std::cout << identificadorArtista << " " << albumidentificador << " " << cancionidentificador << " "
                  << nickname << " " << duracion << " " << direccionpremium << " "
                  << direccionestandar << " " << reproducciones << " "
                  << miembroProduccion_1 << " " << miembroProduccion_2 << " "
                  << miembroProduccion_3 << " " << miembroProduccion_4 << " "
                  << miembroProduccion_5 << std::endl;

        short int valid_str = 0;
        MiembroProduccion* miembros[5] = {nullptr,nullptr,nullptr,nullptr,nullptr};
        for (int i = 0; i < 5; ++i) {
            const std::string& id = campos[8+i];
            if (id.empty()) continue;
            MiembroProduccion* p = sistema_raiz->get_miembro(id);
            if (p) miembros[valid_str++] = p;   // solo si existe
        }
        std::string n_prod = std::to_string(valid_str);

        // Construye y agrega
        Cancion can(nickname, duracion,
                   direccionpremium, direccionestandar,
                   reproducciones, identificadorArtista,
                   albumidentificador, cancionidentificador,
                   miembros, n_prod);

        std::cout << "Cancion { "
                  << "ident=\"" << can.get_ident() << "\", "
                  << "nombre=\"" << can.get_nombre() << "\", "
                  << "duracion=" << can.get_duracion() << "s, "
                  << "premium=\"" << can.get_dir_archivo_prmm() << "\", "
                  << "estandar=\"" << can.get_dir_archivo_stndr() << "\", "
                  << "reproducciones=" << can.get_reproducciones() << ", "
                  << "num_productores=" << can.get_num_productores()
                  << " }" << std::endl;


        Artista* art_act = sistema_raiz->get_artista(identificadorArtista);
        if (!art_act) { ++num_errores; continue; }

        Album* alm_act = art_act->get_album(albumidentificador);
        if (!alm_act) { ++num_errores; continue; }

        bool add_can = alm_act->anadir_cancion(can);
        if(!add_can) num_errores++;

        std::cout << "\n" << std::endl;

    }
    return true;
}

bool GestorDatos::cargar_ads(const std::string& ruta_csv) {
    std::ifstream f(ruta_csv);
    if (!f.is_open()) return false;

    std::string linea;

    // descarta encabezado
    if (!std::getline(f, linea)) return false;

    while (std::getline(f, linea)) {
        if (linea.empty()) continue;
        if (!linea.empty() && linea.back() == '\r') linea.pop_back();

        // Esperamos 4 columnas:
        // ad_id,categoria,mensaje,ruta
        std::string campos[4];
        std::size_t n_e = 0;
        std::size_t start = 0;

        while (n_e < 3) { // lee 3 comas; el 4º campo sale al final
            std::size_t pos = linea.find(separador, start);
            if (pos == std::string::npos) break;
            campos[n_e++] = linea.substr(start, pos - start);
            start = pos + 1;
        }
        if (start <= linea.size() && n_e < 4) campos[n_e++] = linea.substr(start);

        if (n_e != 4) { ++num_errores; continue; }

        const std::string& id     = campos[0];
        const std::string& cat    = campos[1];
        const std::string& msg    = campos[2];
        const std::string& ruta   = campos[3];

        std::cout << "id=" << id
                  << " cat=" << cat
                  << " msg=" << msg
                  << " ruta=" << ruta
                  << std::endl;

        if (id.empty() || cat.empty() || ruta.empty()) { ++num_errores; continue; }

        Anuncio a(id, cat, msg, ruta);

        if (!sistema_raiz->anadir_anuncio(a)) {
            ++num_errores;
            continue;
        }
    }
    return true;
}


bool GestorDatos::cargar_usuarios(const std::string& ruta_csv) {
    std::ifstream f(ruta_csv);
    if (!f.is_open()) return false;

    std::string linea;

    // descarta encabezado
    if (!std::getline(f, linea)) return false;

    while (std::getline(f, linea)) {
        if (linea.empty()) continue;
        if (!linea.empty() && linea.back() == '\r') linea.pop_back();

        // Esperamos 8 columnas:
        // codigo_usuario,nickname,contrasena,membresia,ciudad,pais,fecha_subs,seguir_a
        std::string campos[8];
        std::size_t n_e = 0;
        std::size_t start = 0;

        while (n_e < 7) { // extrae 7 comas; el último campo va fuera del bucle
            std::size_t pos = linea.find(separador, start);
            if (pos == std::string::npos) break;
            campos[n_e++] = linea.substr(start, pos - start);
            start = pos + 1;
        }
        if (start <= linea.size() && n_e < 8) campos[n_e++] = linea.substr(start);

        if (n_e != 8) { ++num_errores; continue; }

        const std::string& codigo     = campos[0];
        const std::string& nick       = campos[1];
        const std::string& pass       = campos[2];
        const std::string& memb       = campos[3];
        const std::string& ciudad     = campos[4];
        const std::string& pais       = campos[5];
        const std::string& fecha_subs = campos[6];
        // const std::string& seguir_a = campos[7]; // se ignora en esta etapa

        std::cout << "codigo=" << codigo
                  << " nick=" << nick
                  << " pass=" << pass
                  << " memb=" << memb
                  << " ciudad=" << ciudad
                  << " pais=" << pais
                  << " fecha_subs=" << fecha_subs
                  << std::endl;

        if (codigo.empty() || nick.empty()) { ++num_errores; continue; }

        // Construcción “stringy” (el ctor valida membresía internamente)
        Usuario u(nick, codigo, pass, memb, ciudad, pais, fecha_subs);

        // Insertar en Sistema (copia en heap; respeta capacidad 1000)
        if (!sistema_raiz->anadir_usuario(u)) {
            ++num_errores;
            continue;
        }
    }
    return true;
}

bool GestorDatos::cargar_favoritos(const std::string& ruta_csv) {
    std::ifstream f(ruta_csv);
    if (!f.is_open()) return false;

    std::string linea;

    // Encabezado
    if (!std::getline(f, linea)) return false;

    Usuario*     u_actual      = nullptr;
    std::string  codigo_actual;

    while (std::getline(f, linea)) {

        if (!linea.empty() && linea.back()=='\r') linea.pop_back();

        std::string campos[4];
        std::size_t n_e   = 0;
        std::size_t start = 0;

        // Partir por separador (esperamos 4 campos)
        while (n_e < 3) {
            std::size_t pos = linea.find(separador, start);
            if (pos == std::string::npos) break;
            campos[n_e++] = linea.substr(start, pos - start);
            start = pos + 1;
        }
        if (start <= linea.size() && n_e < 4) campos[n_e++] = linea.substr(start);

        if (n_e != 4) { ++num_errores; continue; }

        const std::string& codUser = campos[0]; // codigo_usuario
        const std::string& idArt   = campos[1]; // 5 dígitos
        const std::string& idAlb   = campos[2]; // 2 dígitos
        const std::string& idCan   = campos[3]; // 2 dígitos

        std::cout << "codUser=" << codUser
                  << " idArt=" << idArt
                  << " idAlb=" << idAlb
                  << " idCan=" << idCan
                  << std::endl;

        // Cacheo de usuario para líneas consecutivas
        if (!u_actual || codUser != codigo_actual) {
            u_actual = sistema_raiz->get_usuario(codUser);
            codigo_actual = codUser;
        }
        if (!u_actual) { ++num_errores; continue; }

        // Asegurar que el usuario tiene su ListaSongs creada
        ListaSongs* lista = u_actual->get_lista_favoritos();
        if (!lista) {
            // Construimos una lista vacía con capacidad por defecto (1000)
            ListaSongs vacia(/*codigos_iniciales*/nullptr,
                             /*codigo_propietario*/u_actual->get_codigo_usuario());
            u_actual->set_lista_favoritos(vacia);
            lista = u_actual->get_lista_favoritos();
            if (!lista) { ++num_errores; continue; }
        }

        // Resolver artista
        Artista* art = sistema_raiz->get_artista(idArt);
        if (!art) { ++num_errores; continue; }

        // Construir identificador de 9 dígitos AAAAAAABB (5+2+2)
        const std::string id9 = idArt + idAlb + idCan;

        // Añadir a favoritos (sin deduplicar en esta fase)
        const bool ok = lista->anadir_cancion(*art, id9);
        if (!ok) ++num_errores;
    }

    return true;
}

// ================== Helpers de parsing (privados) ==================

// Implementa estos cuando los necesites; por ahora stubs mínimos.

int GestorDatos::contar_filas(const std::string& ruta_csv) const {
    (void)ruta_csv;
    return 0; // TODO: contar líneas útiles (sin encabezado)
}

int GestorDatos::leer_linea(int /*fd*/, char* /*dst*/, unsigned int /*maxlen*/) const {
    // TODO: lectura por descriptor/FILE* si decides no usar iostreams
    return -1;
}

int GestorDatos::partir_campos(const char* /*linea*/, int /*len*/,
                               char** /*out*/, int /*max_campos*/) const {
    // TODO: split muy simple por 'separador'
    return 0;
}

unsigned int GestorDatos::to_uint(const char* /*s*/) const {
    // TODO: parseo sencillo de entero
    return 0u;
}

void GestorDatos::trim_inplace(char* /*s*/) const {
    // TODO: recortar espacios extremos
}

void GestorDatos::zfill_inplace(char* /*s*/, int /*width*/) const {
    // TODO: rellenar con ceros a la izquierda hasta 'width'
}

void GestorDatos::construir_codigo9(const char* /*a5*/, const char* /*b2*/,
                                    const char* /*c2*/, char* /*out9*/) const {
    // TODO: concatenar 5+2+2 en 'out9'
}

void GestorDatos::log_error(const char* /*msg*/) {
    // TODO: incrementar num_errores y si quieres imprimir
}

// ================== Helpers de escritura/generación (privados) ==================

bool GestorDatos::escribir_csv_linea(int /*fd*/, const char* /*linea*/, int /*len*/) const {
    // TODO: para cuando implementes generación
    return false;
}

unsigned int GestorDatos::rng_next() {
    // PRNG lineal mínimo (cuando lo necesites para generación)
    rng_seed = 1664525u * rng_seed + 1013904223u;
    return rng_seed;
}

std::string GestorDatos::slugify(const std::string& s) const {
    // TODO: opcional (si decides usar slugs)
    return s;
}

std::string GestorDatos::ruta_portada(const std::string& a,
                                      const std::string& b) const {
    // TODO: opcional
    return "/data/" + a + "/image/" + b + ".png";
}

std::string GestorDatos::ruta_ogg128(const std::string& a,
                                     const std::string& s) const {
    // TODO: opcional
    return "/data/" + a + "/audio/" + s + "_128.ogg";
}

std::string GestorDatos::ruta_ogg320(const std::string& a,
                                     const std::string& s) const {
    // TODO: opcional
    return "/data/" + a + "/audio/" + s + "_320.ogg";
}
