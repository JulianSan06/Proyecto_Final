#include "moneda.h"

Moneda::Moneda(int Pos_X, int Pos_Y, int Ancho, int Alto, int choice)
{
    /* Se le da forma a la moneda y tambien se le da posiciones */
    this->Pos_X = Pos_X;
    this->Pos_Y = Pos_Y;
    this->Ancho = Ancho;
    this->Alto = Alto;
    x = choice;
    setPos(Pos_X, Pos_Y);
}

QRectF Moneda::boundingRect() const
{
    /* Se le da forma a la moneda */
    return QRectF(Pos_X, Pos_Y, Ancho, Alto);
}

void Moneda::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /* Se dibuja la moneda para agregarla a la escena */
    if(x == 1){
        QPixmap pixmap;
        pixmap.load(":/Imagenes/moneda.png");
        painter->drawPixmap(boundingRect(), pixmap,pixmap.rect());

    }
    else if(x == 2){
        QPixmap pixmap;
        pixmap.load("://Imagenes/Mic.png");
        painter->drawPixmap(boundingRect(), pixmap,pixmap.rect());

    }
}
