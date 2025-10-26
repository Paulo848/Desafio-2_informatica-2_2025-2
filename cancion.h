#ifndef CANCION_H
#define CANCION_H

#include <string>

class MiembroProduccion;  // Forward declaration

class Cancion
{
public:
    Cancion();
    Cancion(const std::string& nombre,
            int duracion,
            const std::string& dir_archivo_premium,
            const std::string& dir_archivo_estandar,
            long int reproducciones,
            const std::string& id_artista,
            const std::string& id_album,
            const std::string& id_song,
            MiembroProduccion** productores_in,
            short int n_produtc);

    Cancion(const std::string& nombre_,
            const std::string& duracionStr,
            const std::string& dir_archivo_premium_,
            const std::string& dir_archivo_estandar_,
            const std::string& reproduccionesStr,
            const std::string& id_artista,
            const std::string& id_album,
            const std::string& id_song,
            MiembroProduccion** productores_in,
            const std::string& n_produtc);

    // Getters
    std::string get_nombre()          const;
    std::string get_dir_archivo_stndr() const; // estándar
    std::string get_dir_archivo_prmm()  const; // premium
    int         get_duracion()        const;
    long int    get_reproducciones()  const;
    MiembroProduccion* get_productores() const;
    short int get_num_productores() const;
    std::string  get_ident()        const;

    void aumentar_reproducciones();

    void anadir_ident(const std::string& id_artist,
                              const std::string& id_albm,
                              const std::string& id_song);

    void anadir_miembro_produccion(const std::string& nombre,
                                   const std::string& rol,
                                   const std::string& contacto);

    Cancion(const Cancion& other);
    Cancion& operator=(const Cancion& other);

    ~Cancion();

private:
    static bool  parse_long (const std::string& s, long& out);
    static long  to_long    (const std::string& s, long  def = 0);
    static int   to_int     (const std::string& s, int   def = 0);
    static short to_short   (const std::string& s, short def = 0);

    std::string nombre;
    int         duracion;
    std::string dir_archivo_premium;
    std::string dir_archivo_estandar;
    long int    reproducciones;
    MiembroProduccion** productores;
    short int num_productores;
    std::string identificador;

};

#endif // CANCION_H
