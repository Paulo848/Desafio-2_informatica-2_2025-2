#ifndef SESSION_USUARIO_H
#define SESSION_USUARIO_H

#include <string>
#include "reproductor.h"

// Forward declarations
class Sistema;
class Usuario;
class Reproductor;
class ListaSongs;

class SessionUsuario {
private:
    Usuario*     user;
    Reproductor  list_repro;
    Sistema*     sistema_raiz;   // no-ownership

public:
    // Ciclo de vida
    SessionUsuario(Usuario* u, Sistema* s);
    ~SessionUsuario();

    // Inicio de modos
    bool iniciar_random_global();
    bool iniciar_random_fav();
    bool iniciar_secuencial_fav();

    // Estado / control
    bool termino() const;
    bool siguiente_cancion();
    bool retroceder_cancion();
    bool detener_repro();
    bool iniciar_repro();

    // Repetir canción actual (premium)
    bool modo_repetir_cancion();    // toggle on/off
    bool consultar_modo_repro() const;

    // Edición de favoritos (propios)
    bool anadir_cancion_list_fav(const std::string& idCancion);
    bool eliminar_cancion_list_fav(const std::string& idCancion);
    bool seguir_list_fav(const std::string& nickUsuario);

    // Parámetros de sesión
    bool set_modo_retroceso(int n); // p.ej., 4 (global) / 6 (favoritos)

    // Datos para imprimir (incluye rutas y, si aplica, anuncio)
    std::string get_datos_cancion(const std::string& modoCalidad) const;
};

#endif // SESSION_USUARIO_H
