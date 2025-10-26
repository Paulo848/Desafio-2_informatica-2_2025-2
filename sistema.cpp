#include "sistema.h"
#include "sessionusuario.h"
#include "artista.h"
#include "usuario.h"
#include "anuncio.h"
#include "miembroproduccion.h"
#include <iostream>

//using std::string;

// ----------------------- Ciclo de vida -----------------------

Sistema::Sistema( const std::string& ciudad_, const std::string& pais_)

    : artistas(nullptr), capacidad_art(1000), tamano_art(0),
    usuarios(nullptr), capacidad_usr(1000), tamano_usr(0),
    anuncios(nullptr), capacidad_ads(50), tamano_ads(0),
    ciudad(ciudad_), pais(pais_) {
    iniciar_array_arts(1000);
    iniciar_array_usrs(1000);
    iniciar_array_ads(50);
}

Sistema::~Sistema() {
    // Libera artistas
    if (artistas) {
        for (int i = 0; i < tamano_art; ++i) {
            delete artistas[i];
        }
        delete [] artistas;
    }
    // Libera usuarios
    if (usuarios) {
        for (int i = 0; i < tamano_usr; ++i) {
            delete usuarios[i];
        }
        delete [] usuarios;
    }
    // Libera anuncios
    if (anuncios) {
        for (int i = 0; i < tamano_ads; ++i) {
            delete anuncios[i];
        }
        delete [] anuncios;
    }
}

// ----------------------- Carga / actualización -----------------------

void Sistema::cargar_datos(const std::string& /*rutaBase*/) {
    // TODO: Implementar la carga/actualización real desde archivos
    // (esta función NO aparece en el menú al usuario final).
}

// ----------------------- Inicialización de arreglos -----------------------

bool Sistema::iniciar_array_arts(int capacidad) {
    if (capacidad <= 0) return false;
    if (artistas) return false; // ya inicializado
    capacidad_art = capacidad;
    tamano_art = 0;
    artistas = new Artista*[capacidad_art];
    for (int i = 0; i < capacidad_art; ++i) artistas[i] = nullptr;
    return true;
}

bool Sistema::iniciar_array_usrs(int capacidad) {
    if (capacidad <= 0) return false;
    if (usuarios) return false;
    capacidad_usr = capacidad;
    tamano_usr = 0;
    usuarios = new Usuario*[capacidad_usr];
    for (int i = 0; i < capacidad_usr; ++i) usuarios[i] = nullptr;
    return true;
}

bool Sistema::iniciar_array_ads(int capacidad) {
    if (capacidad <= 0) return false;
    if (anuncios) return false;
    capacidad_ads = capacidad;
    tamano_ads = 0;
    anuncios = new Anuncio*[capacidad_ads];
    for (int i = 0; i < capacidad_ads; ++i) anuncios[i] = nullptr;
    return true;
}

// ----------------------- Altas -----------------------

bool Sistema::anadir_artista(const Artista& a) {
    if (!artistas || tamano_art >= capacidad_art) return false;
    artistas[tamano_art++] = new Artista(a);
    return true;
}

bool Sistema::anadir_usuario(const Usuario& u) {
    if (!usuarios || tamano_usr >= capacidad_usr) return false;
    usuarios[tamano_usr++] = new Usuario(u);
    return true;
}

bool Sistema::anadir_anuncio(const Anuncio& a) {
    if (!anuncios || tamano_ads >= capacidad_ads) return false;
    anuncios[tamano_ads++] = new Anuncio(a);
    return true;
}

bool Sistema::anadir_miembro(const MiembroProduccion& m){
    if (!miembros || tamano_miem >= capacidad_miem) return false;
    miembros[tamano_miem++] = new MiembroProduccion(m);
    return true;
}

// ----------------------- Getters de tamaños/capacidades -----------------------

int Sistema::get_capacidad_arts() const { return capacidad_art; }
int Sistema::get_tamano_arts()   const { return tamano_art; }

int Sistema::get_capacidad_usrs() const { return capacidad_usr; }
int Sistema::get_tamano_usrs()    const { return tamano_usr; }

int Sistema::get_capacidad_ads() const { return capacidad_ads; }
int Sistema::get_tamano_ads()    const { return tamano_ads; }

// ----------------------- Metadatos del sistema -----------------------

const std::string& Sistema::get_ciudad() const { return ciudad; }
const std::string& Sistema::get_pais()   const { return pais; }

// ----------------------- Acceso por código/ID -----------------------

Usuario* Sistema::get_usuario(const std::string& codUsuario) const {
    // TODO: ajusta el nombre del getter real (p.ej., Usuario::get_codigo_usuario())
    for (int i = 0; i < tamano_usr; ++i) {
        if (usuarios[i] && usuarios[i]->get_codigo_usuario() == codUsuario) {
            return usuarios[i];
        }
    }
    return nullptr;
}

Usuario* Sistema::get_usuario(const std::string& nickname, const std::string& contrasena) const {
    // TODO: ajusta el nombre del getter real (p.ej., Usuario::get_codigo_usuario())
    for (int i = 0; i < tamano_usr; ++i) {
        if (usuarios[i] && usuarios[i]->get_nickname() == nickname && usuarios[i]->get_contra_usuario() == contrasena) {
            return usuarios[i];
        }
    }
    return nullptr;
}

Artista* Sistema::get_artista(const std::string& idArtista) const {
    // TODO: ajusta el getter real (p.ej., Artista::get_cod())
    for (int i = 0; i < tamano_art; ++i) {
        // Cambia por el método correcto en tu clase Artista
        if (artistas[i] && artistas[i]->get_ident() == idArtista) {
            return artistas[i];
        }
    }
    return nullptr;
}

Anuncio* Sistema::get_anuncio(const std::string& idAnuncio) const {
    for (int i = 0; i < tamano_ads; ++i) {
        if (anuncios[i] && anuncios[i]->get_ident() == idAnuncio ) return anuncios[i];
    }
    return nullptr;
}

MiembroProduccion* Sistema::get_miembro(const std::string& idMiembro) const {
    for (int i = 0; i < tamano_miem; ++i) {
        if (miembros[i] && miembros[i]->get_codigo() == idMiembro ) return miembros[i];
    }
    return nullptr;
}

// ----------------------- Login → sesión -----------------------

SessionUsuario* Sistema::loginUsuario(const std::string& nickname, const std::string& contrasena) {
    Usuario* u = get_usuario(nickname,contrasena);
    if(u == nullptr) return nullptr;
    return new SessionUsuario(u, this);
}
