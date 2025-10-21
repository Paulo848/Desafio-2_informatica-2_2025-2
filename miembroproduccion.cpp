#include "miembroproduccion.h"
// MiembroProduccion.cpp

// Constructor por defecto (inicializa a vacío)
MiembroProduccion::MiembroProduccion()
    : nombre(), apellidos(), codigo(), tipoMiembro() {}

// Constructor con parámetros (según tu header: nombre, apellidos, codigo)
MiembroProduccion::MiembroProduccion(const std::string& nombre,
                                     const std::string& apellidos,
                                     const std::string& codigo)
    : nombre(nombre),
    apellidos(apellidos),
    codigo(codigo),
    tipoMiembro() {} // puedes asignar un valor si lo deseas

// Getters
std::string MiembroProduccion::get_nombre() const    { return nombre; }
std::string MiembroProduccion::get_apellidos() const { return apellidos; }
std::string MiembroProduccion::get_codigo() const    { return codigo; }
