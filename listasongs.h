#ifndef LISTASONGS_H
#define LISTASONGS_H

#include <string>

class Artista;   // forward declaration
class Cancion;   // forward declaration

class ListaSongs
{
public:
    // Constructor
    ListaSongs(const std::string* codigos_iniciales,
               const std::string& codigo_propietario,
               int                capacidad_inicial = 1000
               );

    // Getters básicos
    int         get_num_canciones() const;   // alias de get_tamano()
    int         get_capacidad()     const;
    int         get_tamano()        const;
    std::string get_codigo_prop()   const;
    std::string get_cancion(int idx) const;
    Artista*    get_artista(int idx) const;

    // Búsqueda
    Artista*    bus_art_por_can(const std::string& id_song) const;

    // Modificación
    bool anadir_cancion(Artista& art, const std::string& id9);
    bool eliminar_cancion(Artista& artist, const std::string ident );

    // Regla de tres
    ListaSongs(const ListaSongs& other);            // ctor de copia
    ListaSongs& operator=(const ListaSongs& other); // asignación

    // Destructor
    ~ListaSongs();

private:
    Artista**    lista_artistas;     // punteros paralelos
    std::string* codigo_canciones;   // identificadores (9 dígitos)

    int capacidad;                   // capacidad total
    int tamano;                      // cuántas canciones hay actualmente

    std::string codigo_propietario;  // id de quien “posee” la lista
};

#endif // LISTASONGS_H
