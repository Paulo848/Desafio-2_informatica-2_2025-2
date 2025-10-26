#ifndef ALBUM_H
#define ALBUM_H

#include <string>

class Cancion; // Forward declaration

class Album
{
public:
    Album();
    Album(const std::string& name,
          short int          duracion,
          const std::string& selloDiscografico,
          const std::string& fecha_lanzamiento,
          short int          puntuacion,
          const std::string& dir_portada,
          std::string*       generos,
          short int          num_generos,
          short int          num_canciones,
          const std::string  id_artista,
          const std::string  id_album
          );

    Album(const std::string& name,
          const std::string& duracion,
          const std::string& selloDiscografico,
          const std::string& fecha_lanzamiento,
          const std::string& puntuacion,
          const std::string& dir_portada,
          std::string*       generos,
          const std::string& num_generos,
          const std::string& num_canciones,
          const std::string  id_artista,
          const std::string  id_album
          );

    // Getters
    std::string  get_nombre()       const;
    short int    get_duracion()     const;
    std::string  get_sell_disc()    const;
    std::string  get_date_lanzm()   const;
    short int    get_puntuacion()   const;
    std::string  get_dir_portada()  const;
    std::string* get_generos(short int index) const;
    short int    get_num_gen()      const;
    short int    get_num_songs()    const;
    std::string  get_ident()        const;

    int get_capacidad_can() const;
    int get_tamano_can() const;
    Cancion* get_cancion(const std::string& id);

    std::string generos_como_texto(const std::string& sep = ", ") const;

    // Gestión de canciones (firma literal del diagrama)
    void unir_cancion(const std::string&,
                      int,
                      const std::string&,
                      const std::string&,
                      int,
                      const std::string&,
                      const std::string&,
                      const std::string&);

    bool iniciar_array_cancion(std::size_t n);
    bool anadir_cancion(const Cancion& cancion);

    void aumentar_duracion();

    Album(const Album& other);
    Album& operator=(const Album& other);

    ~Album();

private:

    static bool  parse_long (const std::string& s, long& out);
    static long  to_long    (const std::string& s, long  def = 0);
    static int   to_int     (const std::string& s, int   def = 0);
    static short to_short   (const std::string& s, short def = 0);

    // Atributos según el diagrama
    std::string nombre;
    std::string identificador;
    short int   duracion;
    std::string selloDiscografico;
    std::string fecha_lanzamiento;
    short int   puntuacion;
    std::string dir_portada;

    std::string* generos;
    short int    num_generos;

    Cancion**     canciones;
    short int    num_canciones;

    // capacidad y tamaño efectivos del arreglo de punteros de canciones
    int         capacidad_can;
    int         tamano_can;
};

#endif // ALBUM_H
