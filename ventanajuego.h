#ifndef VENTANAJUEGO_H
#define VENTANAJUEGO_H

#include <QWidget>
#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "loader.h"
#include "informacion.h"
#include "fisicas.h"
#include "personajes.h"
#include "disparo.h"
#include "enemigos.h"
#include "plataforma.h"
#include "moneda.h"
#include "comic.h"

extern infoArchivo infoUsuario;

QT_BEGIN_NAMESPACE
namespace Ui { class Ventanajuego; }
QT_END_NAMESPACE

class Ventanajuego : public QWidget
{
    Q_OBJECT

public:
    Ventanajuego(QWidget *parent = nullptr);
    ~Ventanajuego();
    unsigned short getLocation() const;
    void setMult(bool value);
    QTimer *timer;
    QGraphicsScene *scene;
    QList<Enemigos *> moobs;
    QList<disparo*> balas;

public slots:
    void actualizar();


private slots:
    void on_Iniciar_Juego_clicked(); //boton para iniciar el juego
    void on_Pausa_Juego_clicked();  //boton para pausar el juego
    void on_Guardar_clicked();  //boton para guardar el codigo
    void on_Musica_clicked();    //boton que inicia la musica

    void on_reiniciar_clicked(); //boton de reinicio del juego

    void on_Instrucciones_clicked();    //boton de intrucciones

private:
    Ui::Ventanajuego *ui;

private:

    float dt; //diferencial de tiempo para calcular los movimientos
    int h_limit;    //limite horizontal de la escena de juego
    int v_limit;    //limite vertical de la escena del juego

    int Vida_Jugador_1 = 100; //vida jugador 1
    int Vida_Jugador_2 = 100;   //vida jugador 2

    int Vidas_jugador_1; //numero de vidas del jugador 1
    int Vidas_jugador_2;    //numero de vidas del personaje 2

    void Cambiar_nivel(); //funcion para cambiar de nivel
    void cambiarVentana(); //funcion para cambiar de ventana

    //Apartado Jugadores-------------------------------------------
    void borderCollision(Fisicas *b); //calcula colisiones con los limites de la escena
    void keyPressEvent(QKeyEvent *event); //recibe y ejecuta eventos de tecla
    QList<personajes *> bars; //Lista donde es almacenada los personajes


    //Apartado de Enemigos------------------------------------------

    void move_Moobs(Fisicas *m); //funcion para mover los enemigos
    int Danio_enemigos = 20; //coeficiente de daño al impactar con un enemigo
    void moobs_nivel_1();   //enemigos del nivel 1
    void moobs_nivel_2();   //enemigos del nivel 2
    void moobs_nivel_3();   //enemigos del nivel 3
    int Eliminar_moob;  //variable usada en la eliminacion de moobs

    //Niveles--------------------------------------------------------
    void cambiar_ventana();

    //administracion de partida
    Loader Load_Match;  //objeto para cargar partida
    Loader Save_Match;  //objeto para guardar partida
    bool Game_estate = false; //booleano que indica el estado del juego true = jugando, false = no jugando


    //elementos del mapa (plataformas y monedas)--------------------------
    QList<plataforma*> Plataform;
    void Plataformas_Nivel_1(); //plataformas del nivel 1
    void Plataformas_Nivel_2(); //plataformas del nivel 2
    void Plataformas_Nivel_3(); //plataformas del nivel 3

    QList<Moneda *> coins;  //lista donde se guardan las monedas de cada nivel
    QList<Moneda *> coins_final; //Lista donde se guardan las monedas del nivel final
    void Monedas_Nivel_1();  //monedas del nivel 1
    void Monedas_Nivel_2(); //monedas del nivel 2
    void Monedas_Nivel_3(); //monedas del nivel 3
    void Moneda_final();    //monedas del nivel final

    bool Recoger_monedas(); //funcion que determina si el personaje recogio una moneda
    bool Verificar_Colisiones();    //funcion que verifica las colisiones con plataformas en un solo jugador
    bool Verificar_Colisiones_Mult();   //funcion que verifica las colisiones con plataformas en multtijugador
    int Pos_Y_collision;   //posicion de la colision con plataformas un solo jugador
    int Pos_Y_collision_2;  //posicion de la colision con plataformas para un segundo jugador

    //Disparos------------------------------------------------------------
    void eliminacion();  //funcion que elimina balas y enemigos que colisiones
    int num_disparos_1 = 3; //Limite de disparos del primer jugador
    int num_disparos_2 = 3; //Limite de disparos del segundo jugador
    void desaparecer_bala(); //funcion que limpia la lista de balas para pasar de nivel
    void desaparecer_Plataformas(); //funcion que limpia la lista de plataformas para pasar de nivel

    //Sonido---------------------------------------------------------------

    QMediaPlayer *musica = new QMediaPlayer(); //musica de fondo del videojuego
    QMediaPlayer *muerte = new QMediaPlayer();  //musica que suena en la muerte de un enemigo
    QMediaPlayer *disp = new QMediaPlayer();    //musica que genera el disparar
    QMediaPlayer *Coin = new QMediaPlayer();    //musica de recoleccion de monedas
};

#endif // VENTANAJUEGO_H
