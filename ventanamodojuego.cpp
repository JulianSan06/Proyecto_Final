#include "ventanamodojuego.h"
#include "ui_ventanamodojuego.h"
#include <QDebug>

extern infoArchivo infoUsuario;

ventanamodojuego::ventanamodojuego(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ventanamodojuego)
{
    /* Configuración de la ventana*/
    ui->setupUi(this);
    setFixedSize(900,600);
}

ventanamodojuego::~ventanamodojuego()
{
    delete ui;
}


void ventanamodojuego::on_Individual_clicked()
{
    /* Cambia a la ventana de Seleccion de Juego, asigna el multijugador en falso*/
    infoUsuario.mult = 0;
    cambiarVentana();
}

void ventanamodojuego::on_Multijugador_clicked()
{
    /* Cambia a la ventana de Seleccion de Juego, asigna el multijugador en true*/
    infoUsuario.mult = 1;
    cambiarVentana();
}

void ventanamodojuego::on_Cargar_clicked()
{
    /* Carga la partida y los datos del infousuario, adicionalmente cambia a la ventana del comic segun la localiacion del infousuario.int1*/
    infoUsuario=load_match.Cargar_Partida();
    cambiarVentana2();
}

void ventanamodojuego::cambiarVentana()
{
    /* Funcion encargada en Cambiar a la ventana de Seleccion de Juego*/
    wS.setGeometry(this->geometry());
    this->close();
    wS.setVisible(true);
}

void ventanamodojuego::cambiarVentana2()
{
    /* Funcion encargada en Cambiar a la ventana del comic dependiendo del nivel que cargue a infousuario.int1*/
    cM.setGeometry(this->geometry());
    this->close();
    cM.setVisible(true);
}
