#include "personajes.h"

/* Constructor de la clase que recibe:
    x
    life
     y asigna valores a las diferentes caracteristicas de la clase. ademas inicia el objeto tipo fisicas*/
personajes::personajes(int x, int life):escala(0.5)  // recibe la opcion del multijugador y de las vidas que tiene el personaje
{
    float posx,posy,velx,vely,mass,r,K,e;
    posx = 0;
    posy = 0;
    r = 18;
    mass = 50;
    velx = 0;
    vely = 0;
    K = 0.5;
    e = 0.01;
    choice = x;
    vida = life;
    esf = new Fisicas(posx,posy,velx,vely,mass,r,K,e);

}

/*Destructor de la clase */
personajes::~personajes()
{
    delete esf;
}

/*Funcion que delimita el rectangulo que definira la imagen del personaje en la escena
*/
QRectF personajes::boundingRect() const
{
    return QRectF(0,-10*escala*esf->getR(),10*escala*esf->getR(),10*escala*esf->getR());
}

/*Funcion usada para asignar imagen al personaje dependiendo de que tipo de jugador es
    tambien selecciona las imagenes usadas por los personajes en el juego*/
void personajes::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(choice == 1){

        QPixmap pixmap;
        pixmap.load("://Imagenes/Diomedes_Normal.png");
        painter->drawPixmap(boundingRect(), pixmap,pixmap.rect());
    }

    if(choice == 2){
        //painter->setBrush(Qt::red);
        //painter->drawEllipse(boundingRect());

        QPixmap pixmap;
        pixmap.load("://Imagenes/M.ELIAS_Normal.png");
        painter->drawPixmap(boundingRect(), pixmap,pixmap.rect());
    }
}

/* Asigna un valor a la escala del personaje esta caracteristica ayudará al determinar el tamaño del
    personaje en la escena*/
void personajes::setEscala(float s)
{
    escala = s;
}

/* llama el metodo de formulas del objeto fisicas, donde se calculan las velocidades y posiciones del objeto
    posteriormente se actualiza la posicion del objeto dentro de la escena*/
void personajes::actualizar(float v_lim)
{
    esf->Formulas();
    setPos(esf->getPX(),v_lim-esf->getPY());
}

/* Retorna el objeto tipo fisicas que es indispensable para la funcion actualizar */
Fisicas *personajes::getEsf()
{
    return esf;
}

/*Resta el metodo de vida al personaje, de darse el case de que la vida del personaje baje a 0
    se elimina el objeto tipo fisicas que acompaña la clase*/
void personajes::Damage(int Co_Damage)
{
    vida -= Co_Damage;

    if(vida == 0)
        delete esf;
}

/* Retorma la vida del personaje*/
int personajes::getVida() const
{
    return vida;
}

/*Retorna el puntaje del personaje */
int personajes::getPuntaje() const
{
    return Puntaje;
}

/*Retorna un true en caso de colision entre el personaje y el enemigo */
bool personajes::colision_enemigo()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0, n=colliding_items.size(); i<n; i++){
        if(typeid (*(colliding_items[i])) == typeid(Enemigos)){
            return true;
        }
        return false;
    }
}
