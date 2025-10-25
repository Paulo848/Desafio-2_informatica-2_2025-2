TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    album.cpp \
    anuncio.cpp \
    artista.cpp \
    cancion.cpp \
    gestordatos.cpp \
    listasongs.cpp \
    miembroproduccion.cpp \
    reproductor.cpp \
    sessionusuario.cpp \
    sistema.cpp \
    usuario.cpp

HEADERS += \
    album.h \
    anuncio.h \
    artista.h \
    cancion.h \
    gestordatos.h \
    listasongs.h \
    miembroproduccion.h \
    reproductor.h \
    sessionusuario.h \
    sistema.h \
    usuario.h
