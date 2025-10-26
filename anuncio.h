#ifndef ANUNCIO_H
#define ANUNCIO_H

#include <string>

class Anuncio
{
public:
    Anuncio();
    Anuncio(std::string identificador, std::string categoria, std::string mensaje, std::string ruta);
    std::string get_ident();
    std::string get_categoria();
    std::string get_mensaje();
    std::string get_ruta();

private:
    std::string identificador;
    std::string categoria;
    std::string mensaje;
    const std::string ruta;
};

#endif // ANUNCIO_H
