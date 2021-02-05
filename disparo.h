#ifndef DISPARO_H
#define DISPARO_H
#include <QGraphicsItem>
#include<QPainter>
#include <fisicas.h>
#include <enemigos.h>
#include <plataforma.h>


class disparo: public QGraphicsItem
{
public:
    /* iniciamos funciones y parametros para la clase disparo, en donde habran unas caracteristicas especiales
     * heredadas de la clase fisica */
    disparo(float Pos_X, float Pos_Y, float Vel_X, float Vel_Y, float mass, float K, int tipo);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void actualizar(float v_lim);
    Fisicas *getDisparos() const;
    bool desaparecer();

private:
    /* Variables para darle fisicas a los disparos */
    Fisicas *disparos;
    float Pos_X;
    float Pos_Y;
    float Vel_X;
    float Vel_Y;
    float mass;
    float K; //Resistencia del aire
    int Ancho, Alto;
    float escala;
    int tipo = 0;



};

#endif // DISPARO_H

