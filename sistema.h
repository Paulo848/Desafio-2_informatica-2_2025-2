#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>

// Forward declarations (evita dependencias circulares)
class Artista;
class Usuario;
class Anuncio;
class SessionUsuario;
class MiembroProduccion;

class Sistema {
private:
    // Catálogo y datos globales (dueño de la memoria)
    Artista**      artistas;
    int            capacidad_art;
    int            tamano_art;

    Usuario**      usuarios;
    int            capacidad_usr;
    int            tamano_usr;

    Anuncio**      anuncios;
    int            capacidad_ads;
    int            tamano_ads;

    MiembroProduccion**     miembros;
    int                     capacidad_miem;
    int                     tamano_miem;

    // Metadatos del sistema
    std::string    ciudad;
    std::string    pais;

public:
    // Ciclo de vida
    Sistema( const std::string& ciudad_, const std::string& pais_);
    ~Sistema();

    // Carga/actualización (fuera del menú de usuario)
    void cargar_datos(const std::string& rutaBase);

    // Inicialización de arreglos
    bool iniciar_array_arts(int capacidad);
    bool iniciar_array_usrs(int capacidad);
    bool iniciar_array_ads(int capacidad);
    bool iniciar_array_miem(int capacidad);

    // Altas (Sistema es dueño de los objetos almacenados)
    bool anadir_artista(const Artista& a);
    bool anadir_usuario(const Usuario& u);
    bool anadir_anuncio(const Anuncio& a);
    bool anadir_miembro(const MiembroProduccion& m);

    // Getters de capacidad/tamaño
    int get_capacidad_arts() const;
    int get_tamano_arts() const;
    int get_capacidad_usrs() const;
    int get_tamano_usrs() const;
    int get_capacidad_ads() const;
    int get_tamano_ads() const;
    int get_capacidad_miem() const;
    int get_tamano_miem() const;

    // Metadatos del sistema
    const std::string& get_ciudad() const;
    const std::string& get_pais() const;

    // Acceso por código/ID (no devuelve copias grandes)
    Usuario* get_usuario(const std::string& codUsuario) const;
    Usuario* get_usuario(const std::string& nombre, const std::string& contrasena) const;
    Artista* get_artista(const std::string& codArtista) const;
    Anuncio* get_anuncio(const std::string& idAnuncio) const;
    MiembroProduccion* get_miembro(const std::string& idMiembro) const;

    // Login: crea y devuelve una sesión ya conectada a este Sistema
    SessionUsuario* loginUsuario(const std::string& nickname, const std::string& contrasena);

};

#endif // SISTEMA_H
