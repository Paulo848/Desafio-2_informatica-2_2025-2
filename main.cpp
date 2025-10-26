#include "sistema.h"
#include "gestordatos.h"
#include <iostream>
//#include "MiembroProduccion.h"

int main() {

    Sistema *sistem = new Sistema("Medellin","Colombia");
    unsigned int tam_b = 1000;
    std::string path = "datos/";
    char sep = ',';

    GestorDatos g_datos(sistem,path,sep, tam_b);

    bool carga_m = g_datos.cargar_miembros();
    bool carga_art = g_datos.cargar_artistas();
    bool carga_alb = g_datos.cargar_albums();
    bool carga_can = g_datos.cargar_songs();
    bool carga_usr = g_datos.cargar_usuarios();
    bool carga_ads = g_datos.cargar_ads();
    bool carga_fav = g_datos.cargar_favoritos();
    if( carga_m && carga_art && carga_alb && carga_can && carga_usr && carga_ads && carga_fav) std::cout << "fin melo " << std::endl;

    return 0;
}
