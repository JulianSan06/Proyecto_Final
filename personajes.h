#ifndef PERSONAJES_H
#define PERSONAJES_H


#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "fisicas.h"
#include <enemigos.h>
#include <stdlib.h>
#include <time.h>

class personajes: public QGraphicsItem
{
    /* Se dibuja, se le agregan las fisicas, se evaluan colisiones con otros objetos
     * y se le da forma al personaje */
public:
    personajes(int x, int life);
    ~personajes();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    void setEscala(float s);
    void actualizar(float v_lim);
    Fisicas *getEsf();
    void Damage(int Co_Damage);
    int getVida() const;
    int getPuntaje() const;
    bool colision_enemigo();

private:
    int vida; //Vida del personaje
    Fisicas * esf; //objeto propio de la clase tipo fisicas
    float escala; //Escala del objeto
    int choice = 0; //tipo de skin del personaje
    int Puntaje = 0;  //Puntuacion del personaje
};


#endif // PERSONAJES_H
