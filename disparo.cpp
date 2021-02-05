#include "disparo.h"
#include "ventanamodojuego.h"
extern Ventanajuego *juego;

Fisicas *disparo::getDisparos() const
{
    return disparos;
}

bool disparo::desaparecer()
{
    /* Se rumueve el item de la escena cuando colisiona con algun enemigo o borde de la escena */
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0, n=colliding_items.size(); i<n; i++){
        if(typeid (*(colliding_items[i])) == typeid(Enemigos)){
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            return true;
        }
        return false;
    }
}

disparo::disparo(float Pos_X, float Pos_Y, float Vel_X, float Vel_Y, float mass, float K, int tipo): escala(0.3)
{
    /* Se le asingan caracteristicas para darle fisicas al disparo */
    this->Pos_X = Pos_X;
    this->Pos_Y = Pos_Y+200;
    this->Vel_X = Vel_X;  //Velocidad muy alta
    this->Vel_Y = Vel_Y;  //Velocida negativa baja
    this->mass = mass;
    this->K = K;  //Resistencia al aire
    float R = 10;
    float F = 0.2; //Friccion
    Ancho = 10;
    Alto = 5;
    this->tipo = tipo;
    disparos = new Fisicas(Pos_X,Pos_Y,Vel_X,Vel_Y,mass,R,K, F);

}

QRectF disparo::boundingRect() const
{
    /* Se le da forma al disparo */
    return QRectF(0,-5*escala*disparos->getR(),10*escala*disparos->getR(),5*escala*disparos->getR());
}

void disparo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /* Se pintan las balas */
        if(tipo == 1){ //disparo a la derecha
            QPixmap pixmap;
            pixmap.load(":/Imagenes/bala der.png");
            painter->drawPixmap(boundingRect(), pixmap,pixmap.rect());
        }
        if(tipo == 2){ //disparo a la izquierda
            QPixmap pixmap;
            pixmap.load(":/Imagenes/bala izq.png");
            painter->drawPixmap(boundingRect(), pixmap,pixmap.rect());
        }
}

void disparo::actualizar(float v_lim)
{
    /* Se añade las fisicas al disparo */
    disparos->Formulas();
    setPos(disparos->getPX(),v_lim-disparos->getPY());
}
