#ifndef ENEMIGOS_H
#define ENEMIGOS_H


#include<QGraphicsItem>
#include<QPainter>
#include "fisicas.h"


class Enemigos : public QGraphicsItem
{
private:
    /* Se le da forma a los enemigos */
    int vida_Enemigo = 100;
    int Danio_Enemigo;
    float Pos_X;
    float Pos_Y;
    float Velocidad;
    Fisicas *enemigos;
    float escala;

public:
    /* Caracteristicas para darle fisicas a los enemigos, forma y dibujarlos en la escena */
    Enemigos(float Pos_X, float Pos_Y);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    Fisicas *getEnemigos() const;
    void actualizar(float v_lim);
    int getDanio_Enemigo();
};

#endif // ENEMIGOS_H

