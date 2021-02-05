#ifndef COMIC_H
#define COMIC_H

#include <QWidget>
#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMessageBox>
#include "ventanajuego.h"
#include "informacion.h"

extern infoArchivo infoUsuario;

namespace Ui { class Comic; }

class Comic : public QWidget
{
    Q_OBJECT

public:
    explicit Comic(QWidget *parent = nullptr);
    ~Comic();

private slots:
    void on_Siguiente_clicked();             /*Boton para darle continuidad a la historia*/

private:
    /* Generamos la escena para el comic
     * Delimitamos la escena
     * Cambiamos la imagen de la historieta
     * Cambiamos la ventana por la del juego */
    QTimer *timer;
    QGraphicsScene *scene;
    int h_limit;
    int v_limit;
    void cambio_historia();
    void cambio_ventana();

private:
    Ui::Comic *ui;
};

#endif // COMIC_H
