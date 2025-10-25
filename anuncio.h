#ifndef ANUNCIO_H
#define ANUNCIO_H

#include <string>

class Anuncio
{
public:
    Anuncio();
    Anuncio(std::string categoria, std::string ruta);
    std::string get_categoria();
    std::string get_ruta();
    std::string get_ident();

private:
    std::string categoria;
    const std::string ruta;
    std::string identificador;
};

#endif // ANUNCIO_H
