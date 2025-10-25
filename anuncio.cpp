#include "anuncio.h"

Anuncio::Anuncio() {}
Anuncio::Anuncio(std::string categoria, std::string ruta): categoria(categoria), ruta(ruta)
{}
std::string Anuncio::get_categoria(){ return categoria; }
std::string Anuncio::get_ruta(){ return ruta; }
std::string Anuncio::get_ident(){ return identificador; }
