#include "sessionusuario.h"
#include "sistema.h"
#include "usuario.h"
// Incluye el header real de tu Reproductor
// #include "Reproductor.h"
// Incluye lo que necesites para favoritos/anuncios cuando los tengas
// #include "ListaSongs.h"
// #include "Anuncio.h"

using std::string;

// -------------------- Ciclo de vida --------------------

SessionUsuario::SessionUsuario(Usuario* u, Sistema* s)
    : user(u), list_repro(15), sistema_raiz(s) {
    // Inicializa estado efímero de la sesión aquí si hace falta.
    // p.ej., list_repro.reset();
}

SessionUsuario::~SessionUsuario() {
    // La sesión NO es dueña de user ni de sistema_raiz.
    // Solo libera/limpia lo que ella misma haya reservado (si aplica).
}

// -------------------- Modos de inicio --------------------

bool SessionUsuario::iniciar_random_global() {
    // Configura el reproductor para fuente "global" y modo "aleatorio".
    // Ajusta también retroceso permitido (p.ej., 4 para global).
    // TODO: cargar/inyectar las primeras canciones (pushBack) desde catálogo vía sistema_raiz.
    // list_repro.reset();
    // list_repro.set_tipo_y_modo("global","aleatorio"); // si defines setters
    // list_repro.set_retroceso(4);
    return true;
}

bool SessionUsuario::iniciar_random_fav() {
    // Fuente "favoritos", modo "aleatorio", retroceso M=6
    // TODO: obtener lista de favoritos de user y llenar buffer inicial
    return true;
}

bool SessionUsuario::iniciar_secuencial_fav() {
    // Fuente "favoritos", modo "secuencial", retroceso M=6
    // TODO: obtener lista de favoritos de user y llenar buffer inicial en orden
    return true;
}

// -------------------- Estado / control --------------------

bool SessionUsuario::termino() const {
    // Señal para que la UI pueda salir del bucle.
    // Puedes combinar bandera de finalización + buffer vacío, etc.
    // return list_repro.esta_en_finalizacion() || list_repro.vacio();
    return false;
}

bool SessionUsuario::siguiente_cancion() {
    // Premium: respeta repetir_actual (el Reproductor no avanza si está activo).
    // Estándar: solo avanza.
    // TODO: valida permisos según membresía si quieres bloquear acciones.
    // return list_repro.siguiente();
    return true;
}

bool SessionUsuario::retroceder_cancion() {
    // Solo premium; limitado por nprevias/M
    // return list_repro.previa();
    return true;
}

bool SessionUsuario::detener_repro() {
    // Señal de stop. La UI podría consultar termino() después.
    // list_repro.finalizar();
    return true;
}

bool SessionUsuario::iniciar_repro() {
    // Si tienes un estado STOPPED/PLAYING, actívalo aquí.
    return true;
}

// -------------------- Repetir canción actual --------------------

bool SessionUsuario::modo_repetir_cancion() {
    // Toggle: si está activo, desactiva; si no, activa.
    // if (list_repro.esta_repetiendo()) list_repro.desactivar_repetir();
    // else list_repro.activar_repetir();
    return true;
}

bool SessionUsuario::consultar_modo_repro() const {
    // Devuelve true/false según lo que te convenga (p.ej., "es aleatorio?")
    // string modo = list_repro.get_modo_repro();
    // return (modo == "aleatorio");
    return false;
}

// -------------------- Edición de favoritos --------------------

bool SessionUsuario::anadir_cancion_list_fav(const string& idCancion) {
    // Usa user (propia) y, si necesitas buscar la canción, apóyate en sistema_raiz.
    // TODO: deduplicar y persistir vía Sistema si decides guardar en disco aquí.
    return true;
}

bool SessionUsuario::eliminar_cancion_list_fav(const string& idCancion) {
    // TODO: remover de favoritos propios y persistir si aplica.
    return true;
}

bool SessionUsuario::seguir_list_fav(const string& nickUsuario) {
    // Lee la lista del otro usuario (solo-lectura), fusión + deduplicación a la propia.
    // TODO: pedir a sistema_raiz ese usuario y su lista, luego actualizar los propios favoritos.
    return true;
}

// -------------------- Parámetros --------------------

bool SessionUsuario::set_modo_retroceso(int n) {
    // TODO: pásalo al Reproductor si expusiste un setter.
    // list_repro.set_retroceso(n);
    return true;
}

// -------------------- Datos para imprimir --------------------

std::string SessionUsuario::get_datos_cancion(const string& modoCalidad) const {
    // Arma el bloque de texto que la UI imprime:
    // - Mensaje publicitario (si estándar y cada 2 canciones) → coordínalo con Sistema
    // - Cantante, Álbum
    // - Ruta portada
    // - Título + Ruta .ogg (128 o 320 según modoCalidad/premium)
    //
    // Sugerencia: pide al Reproductor el código actual y resuélvelo a rutas con ayuda del Sistema.
    // const string& code = list_repro.get_codigo_actual();
    // TODO: construir y retornar el string final con los campos requeridos.
    return std::string();
}
