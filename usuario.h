#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class ListaSongs;  // forward declaration

class Usuario
{
public:
    // Constructor
    Usuario(const std::string& nickname,
            const std::string& codigo_usuario,
            const std::string& membresia,
            const std::string& ciudad,
            const std::string& pais,
            const std::string& fecha_subs);

    // Getters
    std::string get_nickname()      const;
    std::string get_codigo_usuario() const;
    std::string get_contra_usuario() const;
    std::string get_membresia()     const;
    std::string get_ciudad()        const;
    std::string get_pais()          const;
    std::string get_fecha_subs()    const;

    // Acceso a sus listas de favoritos
    ListaSongs* get_lista_favoritos();     // propia
    ListaSongs* get_lista_favoritos_otro(); // seguida

    // Asociación para seguir otra lista
    bool set_referencia_favoritos(ListaSongs& lista);

    ~Usuario(); // (manejo mínimo, no destruye listas ajenas)

private:
    std::string nickname;
    std::string codigo_usuario;
    std::string contrasena;
    std::string membresia;
    std::string ciudad;
    std::string pais;
    std::string fecha_subs;

    ListaSongs* lista_favoritos;     // Propia → creada/propiedad del usuario
    ListaSongs* favoritos_otro;      // Solo referencia → no se destruye
};

#endif // USUARIO_H
