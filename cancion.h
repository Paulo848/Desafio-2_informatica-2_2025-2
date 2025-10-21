#ifndef CANCION_H
#define CANCION_H

#include <string>

class MiembroProduccion;  // Forward declaration

class Cancion
{
public:
    Cancion();
    Cancion(const std::string& nombre,
            int                duracion,
            const std::string& dir_archivo_premium,
            const std::string& dir_archivo_estandar,
            long int           reproducciones,
            const std::string& id_artista,
            const std::string& id_album,
            const std::string& id_song);

    // Getters
    std::string get_nombre()          const;
    std::string get_dir_archivo_stndr() const; // estándar
    std::string get_dir_archivo_prmm()  const; // premium
    int         get_duracion()        const;
    long int    get_reproducciones()  const;
    MiembroProduccion* get_productores() const;
    std::string  get_ident()        const;

    void aumentar_reproducciones();

    void anadir_ident(const std::string& id_artist,
                              const std::string& id_albm,
                              const std::string& id_song);

    void anadir_miembro_produccion(const std::string& nombre,
                                   const std::string& rol,
                                   const std::string& contacto);

private:
    std::string nombre;
    int         duracion;
    std::string dir_archivo_premium;
    std::string dir_archivo_estandar;
    long int    reproducciones;
    MiembroProduccion* productores;
    std::string identificador;
};

#endif // CANCION_H
