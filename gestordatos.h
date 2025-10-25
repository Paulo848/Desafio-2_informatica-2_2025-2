#ifndef GESTOR_DATOS_H
#define GESTOR_DATOS_H

#include <string>

// Forward declarations (evita dependencias circulares)
class Sistema;
class Artista;
class Usuario;
class Anuncio;
class ListaSongs;

class GestorDatos {
private:
    // Contexto / configuración
    Sistema*      sistema_raiz;     // no-ownership
    std::string   ruta_base;        // carpeta base donde viven CSV y assets
    char          separador;        // normalmente ','
    char*         buffer_linea;     // buffer de lectura/escritura
    unsigned int  tam_buffer;       // tamaño del buffer_linea
    unsigned int  num_errores;      // contaje básico de errores
    unsigned int  rng_seed;         // semilla para generación

    // --- Helpers de parsing (privados) ---
    int  contar_filas(const std::string& ruta_csv) const;
    int  leer_linea(int fd, char* dst, unsigned int maxlen) const;
    int  partir_campos(const char* linea, int len, char** out, int max_campos) const;
    unsigned int to_uint(const char* s) const;
    void trim_inplace(char* s) const;
    void zfill_inplace(char* s, int width) const;     // rellena con ceros a la izquierda
    void construir_codigo9(const char* a5, const char* b2, const char* c2, char* out9) const;
    void log_error(const char* msg);

    // --- Helpers de escritura/generación (privados) ---
    bool escribir_csv_linea(int fd, const char* linea, int len) const;
    unsigned int rng_next();                           // PRNG simple con rng_seed
    std::string  slugify(const std::string& s) const;  // si decides usar slugs más adelante
    std::string  ruta_portada(const std::string& slug_artista,
                             const std::string& slug_album) const;
    std::string  ruta_ogg128(const std::string& slug_artista,
                            const std::string& slug_song) const;
    std::string  ruta_ogg320(const std::string& slug_artista,
                            const std::string& slug_song) const;

public:
    // --- Ciclo de vida ---
    GestorDatos(Sistema* sys,
                const std::string& rutaBase,
                char sep = ',',
                unsigned int tamBuffer = 4096,
                unsigned int seed = 12345);
    ~GestorDatos();

    // Configuración
    void set_ruta_base(const std::string& ruta);
    void set_separador(char sep);
    void set_seed(unsigned int seed);
    void set_buffer(char* buffer_externo, unsigned int tam); // opcional si compartes buffer

    unsigned int errores() const;

    // ================== CARGA (LECTURA) ==================
    // Carga todo en orden correcto; devuelve true si todas las fases fueron OK.
    bool cargar_todo(const std::string& artistas_csv,
                     const std::string& albums_csv,
                     const std::string& songs_csv,
                     const std::string& miembros_csv,
                     const std::string& ads_csv,
                     const std::string& usuarios_csv,
                     const std::string& favoritos_csv);

    bool cargar_miembros(const std::string& ruta_csv = "Dataset/miembrosProduccion.csv");
    bool cargar_artistas(const std::string& ruta_csv = "Dataset/artistas.csv");
    bool cargar_albums(const std::string& ruta_csv = "Dataset/albumes.csv");
    bool cargar_songs(const std::string& ruta_csv = "Dataset/songs.csv");
    bool cargar_ads(const std::string& ruta_csv = "Dataset/ads.csv");
    bool cargar_usuarios(const std::string& ruta_csv = "Dataset/usuarios.csv");
    bool cargar_favoritos(const std::string& ruta_csv = "Dataset/favoritos.csv");

    // ================== GENERACIÓN (ESCRITURA) ==================
    // Genera archivos CSV/estructura sintética en ruta_base (o rutas recibidas).
    bool gen_artistas(const std::string& ruta_csv,
                      unsigned int n_artistas);
    bool gen_albums(const std::string& ruta_csv,
                    unsigned int albums_por_artista_min,
                    unsigned int albums_por_artista_max);
    bool gen_songs(const std::string& ruta_csv,
                   unsigned int songs_por_album_min,
                   unsigned int songs_por_album_max);
    bool gen_usuarios(const std::string& ruta_csv,
                      unsigned int n_premium,
                      unsigned int n_estandar);
    bool gen_favoritos(const std::string& ruta_csv,
                       unsigned int max_por_usuario);
    bool gen_ads(const std::string& ruta_csv,
                 unsigned int n_ads);  // p.ej., 50

    // (Opcional) generación de assets vacíos para pruebas
    bool gen_assets_portadas();  // crea placeholders .png
    bool gen_assets_audios();    // crea placeholders .ogg

    // No copiable (opcional; descomenta si prefieres evitar copias)
    // GestorDatos(const GestorDatos&) = delete;
    // GestorDatos& operator=(const GestorDatos&) = delete;
};

#endif // GESTOR_DATOS_H
