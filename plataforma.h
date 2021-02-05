#ifndef PLATAFORMA_H
#define PLATAFORMA_H
#include <QGraphicsItem>
#include <QPainter>

class plataforma: public QGraphicsItem
{
public:
    plataforma(int Pos_X,int Pos_Y, int Ancho, int Alto, int choice);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    void ColisionBala();

    int getPos_Y() const;

private:
    int Pos_X; //Posicion del objeto en x
    int Pos_Y;  //Posicion del objeto en y
    int Ancho;  //Ancho de la imagen
    int Alto;   //Alto del objeto
    int x;  //Variable que asigna el tipo de plataforma dependiendo del nivel

};

#endif // PLATAFORMA_H
