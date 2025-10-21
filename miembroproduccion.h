#ifndef MIEMBROPRODUCCION_H
#define MIEMBROPRODUCCION_H

#include <string>

class MiembroProduccion
{
public:
    MiembroProduccion();
    MiembroProduccion(const std::string& nombre,
                      const std::string& apellidos,
                      const std::string& codigo);

    // Getters
    std::string get_nombre()    const;
    std::string get_apellidos() const;
    std::string get_codigo()    const;

private:
    std::string nombre;
    std::string apellidos;
    std::string codigo;
    std::string tipoMiembro; // productor - compositor - músico.
};

#endif // MIEMBROPRODUCCION_H
