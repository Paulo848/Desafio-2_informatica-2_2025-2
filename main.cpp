#include <iostream>
#include "MiembroProduccion.h"
#include "Cancion.h"
#include "Album.h"
#include "Artista.h"

int main() {
    // Artista 12345
    Artista ar("NombreArtista", "12345", 30, "Pais", 1000, 1, 0);
    ar.iniciar_array_album(2);  // capacidad para 2 albumes

    // Álbum 01 del artista 12345 (sin géneros de momento)  En el nullptr irian los generos pero, falta implementar esa parte
    Album a1("Album Uno", 0, "Sello", "2024-01-01", 10, "portada1.png", nullptr, 0, 0, "12345", "01");
    a1.iniciar_array_cancion(2); // capacidad para 2 canciones

    // Álbum 02 del artista 12345 (sin géneros de momento)  En el nullptr irian los generos pero, falta implementar esa parte
    Album a2("Album Dos", 0, "Sello", "2024-02-01", 9, "portada2.png", nullptr, 0, 0, "12345", "02");
    a2.iniciar_array_cancion(2); // capacidad para 2 canciones

    // Canciones: id completo = AAAAA + AA + CC
    // artista   : "12345"
    // albumes   : "01" y "02"
    // cancion   : "01" y "02"
    // Creando las canciones "01" y "02" para el album "01"
    Cancion c11("Tema 1-1", 180, "prem1", "std1", 100, "12345","01","01");
    Cancion c12("Tema 1-2", 200, "prem2", "std2",  50, "12345","01","02");

    // Creando la cancion "01" para el album "02"
    Cancion c21("Tema 2-1", 210, "prem3", "std3", 300, "12345","02","01");

    // Añadir canciones a sus álbumes
    a1.anadir_cancion(c11);
    a1.anadir_cancion(c12);

    a2.anadir_cancion(c21);

    // Añadir álbumes al artista
    ar.anadir_album(a1);
    ar.anadir_album(a2);

    // --- Pruebas de acceso ---
    //
    // Búsqueda de ÁLBUM:
    // - Acepta identificadores de 2, 7 o 9 dígitos.
    //   * 2 dígitos  -> id local del álbum dentro del artista (AA)
    //   * 7 dígitos  -> id completo de álbum (AAAAA + AA)
    //   * 9 dígitos  -> id completo de canción (AAAAA + AA + CC) del que extraemos AAAAAAA
    //
    if (Album* pa = ar.get_album("1234501")) {   // 7 dígitos: AAAAA + AA (artista + álbum)
        std::cout << "Album encontrado: " << pa->get_nombre() << "\n";

        // Búsqueda de CANCIÓN dentro del álbum encontrado:
        // - 9 dígitos -> id completo de canción (AAAAA + AA + CC)
        if (Cancion* pc = pa->get_cancion("123450101")) { // canción 01 del álbum 01 del artista 12345
            std::cout << "Cancion: " << pc->get_nombre() << "\n";
        }

        // - 2 dígitos -> id local de canción dentro del álbum (CC)
        if (Cancion* pc2 = pa->get_cancion("02")) {
            std::cout << "Cancion local 02: " << pc2->get_nombre() << "\n";
        }
    }

    // También puedes buscar un álbum pasando SOLO su id local (2 dígitos: AA):
    if (Album* pb = ar.get_album("02")) {
        std::cout << "Album 02: " << pb->get_nombre() << "\n";
    }


    return 0;
}
