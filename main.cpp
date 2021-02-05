#include "ventanamodojuego.h"

#include <QApplication>

infoArchivo infoUsuario;
Ventanajuego *juego;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ventanamodojuego w;
    w.show();
    return a.exec();
}
