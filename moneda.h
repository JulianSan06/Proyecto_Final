#ifndef MONEDA_H
#define MONEDA_H
#include<QGraphicsItem>
#include<QPainter>

class Moneda : public QGraphicsItem
{
private:
private:
    int Pos_X; //Posicion en x
    int Pos_Y;  //Posicion en y
    int Ancho;  //Ancho de la imagen
    int Alto; //Alto de la imagen
    int x; // Asigna el valor para cambiar el tipo de moneda dependiendo del nivel

public:
    /* Funciones para añadir la moneda a la escena */
    Moneda(int Pos_X, int Pos_Y, int Ancho, int Alto, int ch0ice);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
};

#endif // MONEDA_H
