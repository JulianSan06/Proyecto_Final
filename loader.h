#ifndef LOADER_H
#define LOADER_H

#include "informacion.h"
#include <QTextStream>
#include <QDebug>

class Loader
{

public:
    Loader();
    void Guardar_Partida(infoArchivo infoJuego);   // Funcion para guardar partida en el juego
    infoArchivo Cargar_Partida();                  // Funcion para cargar partida
};

#endif // LOADER_H
