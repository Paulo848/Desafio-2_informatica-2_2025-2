#include "anuncio.h"

Anuncio::Anuncio() {}
Anuncio::Anuncio(std::string identificador, std::string categoria,
        std::string mensaje, std::string ruta)
        :identificador(identificador),categoria(categoria),
        mensaje(mensaje),ruta(ruta)
{}

std::string Anuncio::get_ident() { return identificador; }
std::string Anuncio::get_categoria() { return categoria; }
std::string Anuncio::get_mensaje() { return mensaje; }
std::string Anuncio::get_ruta() { return ruta; }
