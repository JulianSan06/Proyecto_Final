#include "ventanaseleccionjuego.h"
#include "ui_ventanaseleccionjuego.h"
#include<QDebug>

extern infoArchivo infoUsuario;

ventanaseleccionjuego::ventanaseleccionjuego(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ventanaseleccionjuego)
{
    /*Configuracion de la ventana */
    ui->setupUi(this);
    setFixedSize(900,600);
}

ventanaseleccionjuego::~ventanaseleccionjuego()
{
    delete ui;
}

/* Al presionarlo cambia a la ventana de comic*/
void ventanaseleccionjuego::on_nueva_Partida_clicked()
{
    infoUsuario.int1 = 1;
    cambiarVentana();
}


/* Funcion de cambio a la ventana del comic */

void ventanaseleccionjuego::cambiarVentana()
{
    cM.setGeometry(this->geometry());
    this->close();
    cM.setVisible(true);
}






