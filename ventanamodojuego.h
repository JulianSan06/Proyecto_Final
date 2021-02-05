#ifndef VENTANAMODOJUEGO_H
#define VENTANAMODOJUEGO_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "informacion.h"
#include <QLabel>
#include "ventanaseleccionjuego.h"
#include "loader.h"
#include "comic.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ventanamodojuego; }
QT_END_NAMESPACE

class ventanamodojuego : public QMainWindow
{
    Q_OBJECT

public:
    ventanamodojuego(QWidget *parent = nullptr);
    ~ventanamodojuego();
    QGraphicsScene *scene;
    ventanaseleccionjuego wS; //objeto tipo ventana seleccion del juego
    Comic cM;  //objeto tipo comic

private slots:
    void on_Individual_clicked(); //inicia el juego con location= 1
    void on_Multijugador_clicked(); //inicia el juego con mult = true
    void on_Cargar_clicked();   //carga una parida existente

private:
    Ui::ventanamodojuego *ui;

private:
    Loader load_match; //objeto usado para cargar la partida
    int h_limit; //Limite horizontal de la escena
    int v_limit; //Limite vertical de la escena
    void cambiarVentana();  //funcion para cambiar de ventana a seleccion de juego
    void cambiarVentana2(); //ventana para cambiar a el comic
};
#endif // VENTANAMODOJUEGO_H
