#include "Usuario.h"
#include "ListaSongs.h"

// -------------------------------------------------------------
// Constructor
// -------------------------------------------------------------
Usuario::Usuario(const std::string& nickname,
                 const std::string& codigo_usuario,
                 const std::string& membresia,
                 const std::string& ciudad,
                 const std::string& pais,
                 const std::string& fecha_subs)
    : nickname(nickname),
    codigo_usuario(codigo_usuario),
    membresia(membresia),
    ciudad(ciudad),
    pais(pais),
    fecha_subs(fecha_subs),
    lista_favoritos(nullptr),   // la lista propia se podrá crear después
    favoritos_otro(nullptr)     // aún no sigue a nadie
{
}

// -------------------------------------------------------------
// Getters
// -------------------------------------------------------------
std::string Usuario::get_nickname() const       { return nickname; }
std::string Usuario::get_codigo_usuario() const { return codigo_usuario; }
std::string Usuario::get_contra_usuario() const { return contrasena; }
std::string Usuario::get_membresia() const      { return membresia; }
std::string Usuario::get_ciudad() const         { return ciudad; }
std::string Usuario::get_pais() const           { return pais; }
std::string Usuario::get_fecha_subs() const     { return fecha_subs; }

ListaSongs* Usuario::get_lista_favoritos() {
    return lista_favoritos;
}

ListaSongs* Usuario::get_lista_favoritos_otro() {
    return favoritos_otro;
}

// -------------------------------------------------------------
// Seguir la lista de otro usuario
// -------------------------------------------------------------
bool Usuario::set_referencia_favoritos(ListaSongs& lista)
{
    favoritos_otro = &lista;
    return true;
}

// -------------------------------------------------------------
// Destructor
// -------------------------------------------------------------
Usuario::~Usuario()
{
    // No destruimos "favoritos_otro" (no es propiedad)
    // Si en tu diseño luego creas "lista_favoritos" con new,
    // aquí podrías hacer delete.
    // Por ahora no destruimos nada -> comportamiento simple y seguro.
}
