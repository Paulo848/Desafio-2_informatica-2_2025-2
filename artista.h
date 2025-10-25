#ifndef ARTISTA_H
#define ARTISTA_H

#include <string>

class Album; // Forward declaration

class Artista
{
public:
    Artista();
    Artista(const std::string& nickname,
            const std::string& identificador,
            int                edad,
            const std::string& pais,
            long int           numSeguidores,
            long int           rankingGlobal,
            short int          numAlbumes);
    Artista(const std::string& nickname,
            const std::string& identificador,
            const std::string& edad,
            const std::string& pais,
            const std::string& numSeguidores,
            const std::string& rankingGlobal,
            const std::string& numAlbumes);

    // Agregar/Unir un álbum (firma literal del diagrama)
    void unir_album(const std::string&,
                    const std::string&,
                    short int,
                    const std::string&,
                    const std::string&,
                    short int,
                    const std::string&,
                    const std::string*,
                    short int,
                    short int,
                    short int);

    // Nuevo: gestión del arreglo de álbumes
    bool iniciar_array_album(std::size_t n); // crea arreglo vacío de punteros
    bool anadir_album(Album& album);         // agrega puntero si hay espacio

    // Getters
    std::string get_nom()          const;
    std::string  get_ident()        const;
    int         get_edad()         const;
    std::string get_pais()         const;
    long int    get_num_follows()  const;
    long int    get_global_rank()  const;
    short int   get_num_albumes()  const;
    int         get_capacidad_alb()const;
    int         get_tamano_alb()   const;
    std::string get_nombre() const;
    Album* get_album(const std::string&);

    //Destructor para la memoria dinamica
    ~Artista();

private:

    static bool parse_long(const std::string& s, long& out);
    static int   to_int  (const std::string& s, int def = 0);
    static long  to_long (const std::string& s, long def = 0);
    static short to_short(const std::string& s, short def = 0);

    std::string nickname;
    std::string identificador;
    int         edad;
    std::string pais;
    long int    numSeguidores;
    long int    rankingGlobal;
    Album**     albumes;
    short int   numAlbumes;
    int         capacidad_alb;
    int         tamano_alb;
};

#endif // ARTISTA_H

