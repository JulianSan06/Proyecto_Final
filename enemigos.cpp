#include "enemigos.h"


Fisicas *Enemigos::getEnemigos() const
{
    return enemigos;
}

Enemigos::Enemigos(float Pos_X, float Pos_Y):escala(0.5)
{
    /* Se asignan valores para añadirle fisica a los enemigos */
    float mass, velx, vely, K, e, r;
    this->Pos_X = Pos_X;
    this->Pos_Y = Pos_Y;
    Danio_Enemigo = 20;
    mass = 50;
    velx = 0;
    vely = 0;
    r= 18;
    K = 0.9;
    e = 0.9;
    enemigos = new Fisicas(Pos_X,Pos_Y,velx,vely,mass,r,K,e, 0);
}

QRectF Enemigos::boundingRect() const
{
    /* Se le da forma al enemigo */
    return QRectF(0,-10*escala*enemigos->getR(),10*escala*enemigos->getR(),10*escala*enemigos->getR());
}

void Enemigos::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /*Pintamos los enemigos en el juego*/
    QPixmap pixmap;
    pixmap.load(":/Imagenes/BACH_TOMBO.png");
    painter->drawPixmap(boundingRect(), pixmap,pixmap.rect());
}

void Enemigos::actualizar(float v_lim)
{
    /*Aplicamos las formulas a los enemigos para que tengan fisicas*/
    enemigos->Formulas();
    setPos(enemigos->getPX(),v_lim-enemigos->getPY());
}

int Enemigos::getDanio_Enemigo()
{
    return Danio_Enemigo;
}
