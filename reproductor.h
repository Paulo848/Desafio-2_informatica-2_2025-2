#ifndef REPRODUCTOR_H
#define REPRODUCTOR_H

#include <string>

class Reproductor {
private:
    // Configuración
    std::string tipo_repro;     // "global" | "favoritos"
    std::string modo_repro;     // "aleatorio" | "secuencial"
    bool        repetir_actual;
    bool        modo_finalizacion;

    // Ventana/buffer
    short int   tamano_buffer;   // impar
    short int   nprevias;        // < tamano_buffer
    std::string* codigos_canciones; // [0..tamano_buffer-1]

    // Punteros/estado
    long int    pos_global;      // total reproducidas
    short int   pos_actual;      // pos_global % tamano_buffer
    short int   umbral_recarga;  // cuando size() <= umbral → recargar

public:
    // Ciclo de vida
    Reproductor(std::string, std::string, short int, short int, short int);
    Reproductor(short int tam_buffer);
    ~Reproductor();

    void reset(void);

    // Consultas de configuración/estado
    std::string get_tipo_repro(void);
    std::string get_modo_repro(void);
    bool  esta_en_finalizacion(void);
    bool  necesita_recarga(void);
    long int  get_pos_global(void);
    short int get_pos_actual(void);
    short int get_umbral_recarga(void);

    // Repetición de la canción actual
    void activar_repetir(void);
    void desactivar_repetir(void);
    bool esta_repetiendo(void);

    // Acceso a la canción actual
    const std::string& get_codigo_actual(void);

    // Operaciones de ventana
    bool vacio(void);
    bool lleno(void);
    bool siguiente(void);
    bool previa(void);
    bool puede_previa(void);
    bool pushBack(const std::string&);
    void finalizar(void);

    // No copiable (opcional, evita dobles liberaciones)
    Reproductor(const Reproductor&) = delete;
    Reproductor& operator=(const Reproductor&) = delete;
};

#endif // REPRODUCTOR_H
