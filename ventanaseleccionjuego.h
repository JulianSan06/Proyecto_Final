#ifndef VENTANASELECCIONJUEGO_H
#define VENTANASELECCIONJUEGO_H

#include <QMainWindow>
#include <QLabel>
#include "informacion.h"
#include "ventanajuego.h"
#include "comic.h"

namespace Ui {
class ventanaseleccionjuego;
}

class ventanaseleccionjuego : public QWidget
{
    Q_OBJECT

public:
    explicit ventanaseleccionjuego(QWidget *parent = nullptr);
    ~ventanaseleccionjuego();
    Comic cM; //objeto tipo ventana comic usada en el cambio de pantalla

private slots:
    void on_nueva_Partida_clicked(); //boton de nueva partida

private:
    Ui::ventanaseleccionjuego *ui;

private:
    void cambiarVentana(); //funcion que ayuda en el cambio de ventana
};

#endif // VENTANASELECCIONJUEGO_H
