#include "plataforma.h"

/* Constructor sobre cargado de la clase asigna
    Pos_Y
    Pos_X
    Ancho
    Alto
    choice*/
plataforma::plataforma(int Pos_X, int Pos_Y, int Ancho, int Alto, int choice)
{
    this->Pos_X = Pos_X;
    this->Pos_Y = Pos_Y;
    this->Ancho = Ancho;
    this->Alto =Alto;
    x = choice;  //define el tipo de plataforma dependiendo el nivel.

    setPos(this->Pos_X, this->Pos_Y);
}

/* Delimita el rectangulo que definira el objeto de plataforma*/
QRectF plataforma::boundingRect() const
{
    return QRectF(Pos_X, Pos_Y, Ancho, Alto);
}

/* asigna la imagen de la plataforma dependiendo del nivel, utiliza el Qpainter*/
void plataforma::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    if(x == 1){
        //Plataformas del nivel 1
        QPixmap pixmap;
        pixmap.load(":/Imagenes/BASE_ONE.png");
        painter->drawPixmap(boundingRect(), pixmap,pixmap.rect());

    }
    else if(x == 2){
        //plataformas del nivel 2
        QPixmap pixmap;
        pixmap.load(":/Imagenes/BASE_TOW.png");
        painter->drawPixmap(boundingRect(), pixmap,pixmap.rect());

    }

    else if(x==3){
        //Plataformas del mivel 3
        QPixmap pixmap;
        pixmap.load(":/Imagenes/BASE_THREE.png");
        painter->drawPixmap(boundingRect(), pixmap,pixmap.rect());
    }

    else if(x ==4){
        //test de medidas

            painter->setBrush(Qt::red);
            painter->drawRect(boundingRect());
    }
}

void plataforma::ColisionBala()
{
    //hace desaparcer la bala al colisionarse
}

/*Retorna la posicion en Y de la plataforma usada para asignar la posicion en y del jugador
    cuando este colisiona con una plataforma*/
int plataforma::getPos_Y() const
{
    return Pos_Y;
}
