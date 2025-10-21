TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    album.cpp \
    artista.cpp \
    cancion.cpp \
    miembroproduccion.cpp

HEADERS += \
    album.h \
    artista.h \
    cancion.h \
    miembroproduccion.h
