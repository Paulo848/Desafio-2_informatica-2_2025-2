#include "Reproductor.h"

using std::string;

static inline bool esVacio(const std::string& s) { return s.empty(); }

// ---------------- Ciclo de vida ----------------

Reproductor::Reproductor(std::string tipo,
                         std::string modo,
                         short int tam_buffer,
                         short int n_previas,
                         short int umbral)
    : tipo_repro(tipo),
    modo_repro(modo),
    repetir_actual(false),
    modo_finalizacion(false),
    tamano_buffer(tam_buffer),
    nprevias(n_previas),
    codigos_canciones(nullptr),
    pos_global(0),
    pos_actual(0),
    umbral_recarga(umbral) {
    if (tamano_buffer < 1) tamano_buffer = 1;
    if ((tamano_buffer & 1) == 0) tamano_buffer += 1; // asegurar impar
    if (nprevias >= tamano_buffer) nprevias = tamano_buffer - 1;

    codigos_canciones = new string[tamano_buffer];
    // slots vacíos = "" (marcador de vacío)
    for (short int i = 0; i < tamano_buffer; ++i) codigos_canciones[i].clear();

    reset();
}

Reproductor::Reproductor(short int tam_buffer)
    : tipo_repro(""),
    modo_repro(""),
    repetir_actual(false),
    modo_finalizacion(false),
    tamano_buffer(tam_buffer),
    nprevias(0),
    codigos_canciones(nullptr),
    pos_global(0),
    pos_actual(0),
    umbral_recarga(0)
{
    if (tamano_buffer < 1) tamano_buffer = 1;
    if ((tamano_buffer & 1) == 0) tamano_buffer += 1; // asegurar impar
    if (nprevias >= tamano_buffer) nprevias = tamano_buffer - 1;

    codigos_canciones = new string[tamano_buffer];
    // slots vacíos = "" (marcador de vacío)
    for (short int i = 0; i < tamano_buffer; ++i) codigos_canciones[i].clear();

    reset();
}

Reproductor::~Reproductor() {
    delete [] codigos_canciones;
    codigos_canciones = nullptr;
}

void Reproductor::reset(void) {
    repetir_actual = false;
    modo_finalizacion = false;
    pos_global = 0;
    pos_actual = 0;
    for (short int i = 0; i < tamano_buffer; ++i) codigos_canciones[i].clear();
}

// ---------------- Consultas de configuración/estado ----------------

std::string Reproductor::get_tipo_repro(void)  { return tipo_repro; }
std::string Reproductor::get_modo_repro(void)  { return modo_repro; }
bool Reproductor::esta_en_finalizacion(void)   { return modo_finalizacion; }
long int Reproductor::get_pos_global(void)     { return pos_global; }
short int Reproductor::get_pos_actual(void)    { return pos_actual; }
short int Reproductor::get_umbral_recarga(void){ return umbral_recarga; }

bool Reproductor::necesita_recarga(void) {
    // Cuenta slots ocupados y compara con umbral (O(n), suficiente para el reto)
    short int ocupados = 0;
    for (short int i = 0; i < tamano_buffer; ++i)
        if (!esVacio(codigos_canciones[i])) ++ocupados;
    return ocupados <= umbral_recarga;
}

// ---------------- Repetición ----------------

void Reproductor::activar_repetir(void)   { repetir_actual = true; }
void Reproductor::desactivar_repetir(void){ repetir_actual = false; }
bool Reproductor::esta_repetiendo(void)   { return repetir_actual; }

// ---------------- Acceso a canción actual ----------------

const std::string& Reproductor::get_codigo_actual(void) {
    return codigos_canciones[pos_actual];
}

// ---------------- Operaciones de ventana ----------------

bool Reproductor::vacio(void) {
    for (short int i = 0; i < tamano_buffer; ++i)
        if (!esVacio(codigos_canciones[i])) return false;
    return true;
}

bool Reproductor::lleno(void) {
    for (short int i = 0; i < tamano_buffer; ++i)
        if (esVacio(codigos_canciones[i])) return false;
    return true;
}

bool Reproductor::siguiente(void) {
    if (repetir_actual) return true; // no avanza

    // Busca el próximo slot no vacío (circular)
    short int intentos = 0;
    short int idx = pos_actual;
    do {
        idx = (short int)((idx + 1) % tamano_buffer);
        ++intentos;
        if (!esVacio(codigos_canciones[idx])) {
            pos_actual = idx;
            ++pos_global;            // solo incrementa si cambió de canción
            return true;
        }
    } while (intentos < tamano_buffer);

    // No hay más canciones en buffer
    if (modo_finalizacion) return false;
    // Si no estás en finalización, la Session debería recargar antes de llamar de nuevo
    return false;
}

bool Reproductor::puede_previa(void) {
    // Verifica si hay al menos una previa disponible dentro del límite nprevias
    short int pasos = 0;
    short int idx = pos_actual;
    while (pasos < nprevias) {
        idx = (short int)((idx - 1 + tamano_buffer) % tamano_buffer);
        if (!esVacio(codigos_canciones[idx])) return true;
        ++pasos;
    }
    return false;
}

bool Reproductor::previa(void) {
    if (!puede_previa()) return false;

    short int pasos = 0;
    short int idx = pos_actual;
    while (pasos < nprevias) {
        idx = (short int)((idx - 1 + tamano_buffer) % tamano_buffer);
        if (!esVacio(codigos_canciones[idx])) {
            pos_actual = idx;
            // Nota: ir a previa NO incrementa pos_global
            return true;
        }
        ++pasos;
    }
    return false;
}

bool Reproductor::pushBack(const std::string& codigo) {
    // Inserta en el primer slot vacío a partir del “final lógico” (después de pos_actual)
    short int idx = pos_actual;
    for (short int k = 0; k < tamano_buffer; ++k) {
        idx = (short int)((idx + 1) % tamano_buffer);
        if (esVacio(codigos_canciones[idx])) {
            codigos_canciones[idx] = codigo;
            return true;
        }
    }
    // Si está lleno, no inserta
    return false;
}

void Reproductor::finalizar(void) {
    modo_finalizacion = true;
}
