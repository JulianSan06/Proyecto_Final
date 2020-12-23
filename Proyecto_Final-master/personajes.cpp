#include "personajes.h"

//
personajes::personajes(int x):escala(1)
{
    float posx,posy,velx,vely,mass,r,K,e;
    posx = 0;
    posy = 0;
    r = 20;
    mass = 50;
    velx = 0;
    vely = 0;
    K = 0.08;
    e = 0.2;
    choice = x;
    esf = new Fisicas(posx,posy,velx,vely,mass,r,K,e);
}

personajes::~personajes()
{
    delete esf;
}

QRectF personajes::boundingRect() const
{
    return QRectF(0,-10*escala*esf->getR(),10*escala*esf->getR(),10*escala*esf->getR());
}

void personajes::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(choice == 1){
        //painter->setBrush(Qt::blue);
        //painter->drawEllipse(boundingRect());

        QPixmap pixmap;
        pixmap.load(":/imagenes/Diomedes_Normal.png");
        painter->drawPixmap(boundingRect(), pixmap,pixmap.rect());
    }

    if(choice == 2){
        //painter->setBrush(Qt::red);
        //painter->drawEllipse(boundingRect());

        QPixmap pixmap;
        pixmap.load(":/imagenes/M.ELIAS_Normal.png");
        painter->drawPixmap(boundingRect(), pixmap,pixmap.rect());
    }
}

void personajes::setEscala(float s)
{
    escala = s;
}

void personajes::actualizar(float v_lim)
{
    esf->Formulas();
    setPos(esf->getPX(),v_lim-esf->getPY());
}

Fisicas *personajes::getEsf()
{
    return esf;
}
