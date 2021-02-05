#ifndef INFORMACION_H
#define INFORMACION_H
#include<iostream>
#include<QList>

using namespace std;

struct infoArchivo
{
    int mult;  //modo de juego M = multijador, I = individual
    int int1;  //nivel
    int punt1;  //puntaje personaje1
    int punt2; //puntaje personaje2
    int click_comic;  //Cuenta los click con el cual la historia inicia
};
#endif // INFORMACION_H
