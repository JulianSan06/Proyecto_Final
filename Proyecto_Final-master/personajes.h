#ifndef PERSONAJES_H
#define PERSONAJES_H
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "fisicas.h"
#include <stdlib.h>
#include <time.h>
//
class personajes: public QGraphicsItem
{
public:
    personajes(int x);
    ~personajes();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    void setEscala(float s);
    void actualizar(float v_lim);
    Fisicas *getEsf();

private:
    Fisicas * esf;
    float escala;
    int choice = 0;
};




#endif // PERSONAJES_H
