#include "ventanajuego.h"
#include "ui_ventanajuego.h"
#include <QDebug>

extern infoArchivo infoUsuario;

/*Configuracion de la escena, se encuentra los niveles con sus diferentes objetos graficos, timer, y parametros de cada nivel.
  Adicionalmente se inicial el connect*/

Ventanajuego::Ventanajuego(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ventanajuego)
{
    srand(time(NULL));
    ui->setupUi(this);
    h_limit = 1375;
    v_limit = 600;
    musica->setMedia(QUrl("qrc:/Sonidos/La-plata-remix.mp3"));
    musica->setVolume(10);
    muerte->setMedia(QUrl("qrc:/Sonidos/Muerte.mp3"));
    muerte->setVolume(50);
    disp->setMedia(QUrl("qrc:/Sonidos/disparo_1.mp3"));
    disp->setVolume(50);
    Coin->setMedia(QUrl("qrc:/Sonidos/Moneda.mp3"));
    Coin->setVolume(50);

    if(infoUsuario.int1 == 1){
        //Elemntos graficos del primer nivel


        timer = new QTimer(this);
        scene = new QGraphicsScene(this);
        scene->setSceneRect(0, 0,h_limit,v_limit);
        scene->setBackgroundBrush(QBrush(QImage(":/Imagenes/1 screen.png")));
        ui->graphicsView->setScene(scene);
        scene->addRect(scene->sceneRect());
        ui->graphicsView->resize(scene->width(),scene->height());
        this->resize(ui->graphicsView->width(),ui->graphicsView->height());
        Plataformas_Nivel_1();
        Monedas_Nivel_1();
        moobs_nivel_1();
        connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));

    }
    if(infoUsuario.int1 == 2){
        //Elementos graficos del segundo nivel

        timer = new QTimer(this);
        scene = new QGraphicsScene(this);
        scene->setSceneRect(0,0,h_limit,v_limit);
        scene->setBackgroundBrush(QBrush(QImage(":/Imagenes/nivel 2.png")));
        ui->graphicsView->setScene(scene);
        scene->addRect(scene->sceneRect());
        ui->graphicsView->resize(scene->width(),scene->height());
        this->resize(ui->graphicsView->width()+100,ui->graphicsView->height()+100);
        Plataformas_Nivel_2();
        Monedas_Nivel_2();
        moobs_nivel_2();
        connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));

    }
    if(infoUsuario.int1 == 3){
        //Elementos graficos del tercer nivel
        timer = new QTimer(this);
        scene = new QGraphicsScene(this);
        scene->setSceneRect(0,0,h_limit,v_limit);
        scene->setBackgroundBrush(QBrush(QImage(":/Imagenes/2 screen.png")));
        ui->graphicsView->setScene(scene);
        scene->addRect(scene->sceneRect());
        ui->graphicsView->resize(scene->width(),scene->height());
        this->resize(ui->graphicsView->width()+100,ui->graphicsView->height()+100);
        Plataformas_Nivel_3();
        Monedas_Nivel_3();
        moobs_nivel_3();
        connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));
    }
}

/* Destructor de la clase ventanaJuego
*/
Ventanajuego::~Ventanajuego()
{
    delete timer;
    delete scene;
    delete ui;
}

/*Funcion usada para los movimientos de los personajes, enemigos y disparos, mediante la actualiazcion de los parametros de
  caa clase. */
void Ventanajuego::actualizar()
{
    for (int i = 0; i<bars.size() ; i++) {
        Fisicas *b = bars.at(0)->getEsf();
        bars.at(i)->actualizar(v_limit);
        borderCollision(bars.at(i)->getEsf());
        if(Verificar_Colisiones()){
            b->set_vel(b->getVX(),0,b->getPX(),Pos_Y_collision);
        }

        if(infoUsuario.mult){  //movimiento para el caso del multijugador
            Fisicas *a = bars.at(1)->getEsf();
            if(Verificar_Colisiones_Mult()){
                a->set_vel(a->getVX(),0,a->getPX(),Pos_Y_collision_2);
            }
        }
    }

    for (int j = 0;j<moobs.size(); j++ ) { //movimiento de los enemigos
        Fisicas *m = moobs.at(j)->getEnemigos();
        moobs.at(j)->actualizar(v_limit);
        borderCollision(moobs.at(j)->getEnemigos());
        if(m->getPY() == 200){
            m->set_vel(m->getVX(), 0, m->getPX(), 200);
        }
    }

    for (int d = 0;d<balas.size(); d++) {  //movimiento de las balas
        balas.at(d)->actualizar(v_limit);
        borderCollision(balas.at(d)->getDisparos());
        if(balas.at(d)->desaparecer() == true){
            eliminacion();
        }
    }

}

/*Funcion usada para calcular las colisiones con las barreras que delimita la escena.
*/
void Ventanajuego::borderCollision(Fisicas *b)
{

    if(b->getPX()<b->getR()){
        b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getR(),b->getPY());
    }
    if(b->getPX()>h_limit-b->getR()){
        b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),h_limit-b->getR(),b->getPY());
    }
    if(b->getPY()<b->getR()){
        b->set_vel(b->getVX(),-1*b->getE()*b->getVY(),b->getPX(),b->getR());
    }
    if(b->getPY()>v_limit-b->getR()){
        b->set_vel(b->getVX(),-1*b->getE()*b->getVY(),b->getPX(),v_limit-b->getR());

    }
}

/*Funcion encarga de leer los eventos de tecla y parametrizar los movimientos mediante el SetVel de cada personaje ya se
   multijugador o un solo jugador*/
void Ventanajuego::keyPressEvent(QKeyEvent *event)
{
    //Un jugador--------------------------------------------------------------------------------------------------------
    if(infoUsuario.mult == 0){
        Fisicas * b = bars.at(0)->getEsf();

        //disparos----------------------------------------------------------------------------------------------
        if(event->key() == Qt::Key_E){
            if(num_disparos_1 != 0){
                disp->play();
                balas.push_back(new disparo(b->getPX(),b->getPY()+70,100, -5, 2, 0.1, 1));
                balas.back()->actualizar(v_limit);
                scene->addItem(balas.back());
                num_disparos_1 -= 1;
            }
        }
        if(event->key() == Qt::Key_Q){
            if(num_disparos_1 != 0){
                disp->play();
                balas.push_back(new disparo(b->getPX(),b->getPY()+70,-100, -10, 2, 0.1, 2));
                balas.back()->actualizar(v_limit);
                scene->addItem(balas.back());
                num_disparos_1 -= 1;
        }

        }
        //Movimientos--------------------------------------------------------------------------------------------

        if(event->key() == Qt::Key_D){

            b->set_vel(20,b->getVY(),b->getPX(),b->getPY());

            //Si el jugador uno se golpea con un moob
            if(bars.at(0)->colision_enemigo() == true){
                Vida_Jugador_1 -= Danio_enemigos;
                ui->Vida_1->setText(QString::number(Vida_Jugador_1));
                if(Vida_Jugador_1 == 0){
                    scene->removeItem(bars.at(0));                   
                    Vidas_jugador_1 -= 1;
                    if(Vidas_jugador_1 != 0){
                        ui->N_Vidas_1->setText(QString::number(Vidas_jugador_1));
                        QMessageBox msgBox;
                        msgBox.setText("presiona comenzar para intentarlo de nuevo");
                        msgBox.exec();
                        Vida_Jugador_1 = 100;
                        scene->addItem(bars.at(0));
                    }
                    else{
                        QMessageBox msgBox;
                        msgBox.setText("GAME OVER CURRAMBA, dale en reiniciar para empezar de nuevo");
                        msgBox.exec();
                        Vida_Jugador_1 = 100;
                        Vidas_jugador_1 = 3;
                        infoUsuario.punt1 = 0;
                    }

                }
            }
            //si el jugador uno recoge una moneda
            if(Recoger_monedas() == 1){
                Coin->play();
                infoUsuario.punt1 +=10;
                ui->Puntaje_1->setText(QString::number(infoUsuario.punt1));
            }
            //Cambio de nivel
            if(coins.empty())
            {
                delete timer;
                scene->removeItem(bars.at(0));
                desaparecer_bala();
                desaparecer_Plataformas();
                moobs.clear();
                if(infoUsuario.int1 < 3){
                    infoUsuario.int1++;
                    Cambiar_nivel();
                }
                else
                    cambiarVentana();
            }
        }
        if(event->key() == Qt::Key_A){

            b->set_vel(-20,b->getVY(),b->getPX(),b->getPY());

            //Si el jugador uno se golpea con un moob
            if(bars.at(0)->colision_enemigo() == true){
                Vida_Jugador_1 -= moobs.at(0)->getDanio_Enemigo();
                ui->Vida_1->setText(QString::number(Vida_Jugador_1));
                if(Vida_Jugador_1 == 0){
                    scene->removeItem(bars.at(0));
                    Vidas_jugador_1 -= 1;
                    if(Vidas_jugador_1 != 0){
                        ui->N_Vidas_1->setText(QString::number(Vidas_jugador_1));
                        QMessageBox msgBox;
                        msgBox.setText("presiona comenzar para intentarlo de nuevo");
                        msgBox.exec();
                        Vida_Jugador_1 = 100;
                        scene->addItem(bars.at(0));
                    }
                    else{
                        QMessageBox msgBox;
                        msgBox.setText("GAME OVER CURRAMBA, dale en reiniciar para empezar de nuevo");
                        msgBox.exec();
                        Vida_Jugador_1 = 100;
                        Vidas_jugador_1 = 3;
                        infoUsuario.punt1 = 0;
                    }

                }
            }
            //si el jugador uno recoge una moneda
            if(Recoger_monedas() == 1){
                Coin->play();
                infoUsuario.punt1 +=10;
                ui->Puntaje_1->setText(QString::number(infoUsuario.punt1));
            }
            if(coins.empty())
            {
                if(infoUsuario.int1 < 3){
                    delete timer;
                    scene->removeItem(bars.at(0));
                    desaparecer_bala();
                    desaparecer_Plataformas();
                    moobs.clear();
                    infoUsuario.int1++;
                    Cambiar_nivel();

                }
                else
                    cambiarVentana();
            }
        }
        if(event->key() == Qt::Key_W){

            b->set_vel(b->getVX(),60,b->getPX(),b->getPY());

            //Si el jugador uno se golpea con un moob
            if(bars.at(0)->colision_enemigo() == true){
                Vida_Jugador_1 -= moobs.at(0)->getDanio_Enemigo();
                ui->Vida_1->setText(QString::number(Vida_Jugador_1));
                if(Vida_Jugador_1 == 0){
                    scene->removeItem(bars.at(0));
                    Vidas_jugador_1 -= 1;
                    if(Vidas_jugador_1 != 0){
                        ui->N_Vidas_1->setText(QString::number(Vidas_jugador_1));
                        QMessageBox msgBox;
                        msgBox.setText("presiona comenzar para intentarlo de nuevo");
                        msgBox.exec();
                        Vida_Jugador_1 = 100;
                        scene->addItem(bars.at(0));
                    }
                    else{
                        QMessageBox msgBox;
                        msgBox.setText("GAME OVER CURRAMBA, dale en reiniciar para empezar de nuevo");
                        msgBox.exec();
                        Vida_Jugador_1 = 100;
                        Vidas_jugador_1 = 3;
                        infoUsuario.punt1 = 0;
                    }

                }
            }
            //si el jugador uno recoge una moneda
            if(Recoger_monedas() == 1){
                Coin->play();
                infoUsuario.punt1 +=10;
                ui->Puntaje_1->setText(QString::number(infoUsuario.punt1));
            }
            if(coins.empty())
            {
                delete timer;
                scene->removeItem(bars.at(0));
                desaparecer_bala();
                desaparecer_Plataformas();
                moobs.clear();
                if(infoUsuario.int1 < 3){
                    infoUsuario.int1++;
                    Cambiar_nivel();
                }
                else if(infoUsuario.int1 == 3){
                    coins.clear();
                    Moneda_final();
                    if(coins_final.size() == 0){
                        cambiarVentana();
                    }
                }
                else
                    cambiarVentana();
            }
        }
    }
    //Multijugador--------------------------------------------------------------------------------------------------------
    if(infoUsuario.mult == 1){
        Fisicas * b = bars.at(0)->getEsf();
        Fisicas * a = bars.at(1)->getEsf();

        //disparos jugador 1----------------------------------------------------------------------------------------------
        if(event->key() == Qt::Key_E){
            if(num_disparos_1 != 0){
                disp->play();
                balas.push_back(new disparo(b->getPX(),b->getPY()+70,100, -5, 2, 0.1, 1));
                balas.back()->actualizar(v_limit);
                scene->addItem(balas.back());
                num_disparos_1 -= 1;
            }
        }
        if(event->key() == Qt::Key_Q){
            if(num_disparos_1 != 0){
                disp->play();
                balas.push_back(new disparo(b->getPX(),b->getPY()+70,-100, -10, 2, 0.1, 2));
                balas.back()->actualizar(v_limit);
                scene->addItem(balas.back());
                num_disparos_1 -= 1;
        }

        }

        //disparos jugador 2----------------------------------------------------------------------------------------------
        if(event->key() == Qt::Key_O){
            if(num_disparos_2 != 0){
                disp->play();
                balas.push_back(new disparo(a->getPX(),a->getPY()+70,100, -5, 2, 0.1, 1));
                balas.back()->actualizar(v_limit);
                scene->addItem(balas.back());
                num_disparos_2 -= 1;
            }
        }
        if(event->key() == Qt::Key_U){
            if(num_disparos_2 != 0){
                disp->play();
                balas.push_back(new disparo(a->getPX(),a->getPY()+70,-100, -10, 2, 0.1, 2));
                balas.back()->actualizar(v_limit);
                scene->addItem(balas.back());
                num_disparos_2 -= 1;
            }
        }

        //movimientos del jugador 1----------------------------------------------------------------------------------------------
        if(event->key() == Qt::Key_D){
            b->set_vel(20,b->getVY(),b->getPX(),b->getPY());

            //Si el jugador uno se golpea con un moob
            if(bars.at(1)->colision_enemigo() == true){
                Vida_Jugador_1 -= moobs.at(0)->getDanio_Enemigo();
                ui->Vida_1->setText(QString::number(Vida_Jugador_1));
                if(Vida_Jugador_1 == 0){
                    scene->removeItem(bars.at(1));
                    Vidas_jugador_1 -= 1;
                    if(Vidas_jugador_1 != 0){
                        ui->N_Vidas_1->setText(QString::number(Vidas_jugador_1));
                        QMessageBox msgBox;
                        msgBox.setText("presiona ok para intentarlo de nuevo");
                        msgBox.exec();
                        Vida_Jugador_1 = 100;
                        scene->addItem(bars.at(1));
                    }
                    else{
                        QMessageBox msgBox;
                        msgBox.setText("GAME OVER CURRAMBA, dale en reiniciar para empezar de nuevo");
                        msgBox.exec();
                        Vida_Jugador_1 = 100;
                        Vidas_jugador_1 = 3;
                        infoUsuario.punt1 = 0;
                    }

                }
            }
            //si el jugador uno recoge una moneda
            if(Recoger_monedas() == 1){
                Coin->play();
                infoUsuario.punt1 +=10;
                ui->Puntaje_1->setText(QString::number(infoUsuario.punt1));
            }
            if(coins.empty())
            {
                delete timer;
                scene->removeItem(bars.at(0));
                scene->removeItem(bars.at(1));
                desaparecer_bala();
                desaparecer_Plataformas();
                moobs.clear();
                if(infoUsuario.int1 < 3){
                    infoUsuario.int1++;
                    Cambiar_nivel();
                }
                else
                    cambiarVentana();
            }
        }
        if(event->key() == Qt::Key_A){
            b->set_vel(-20,b->getVY(),b->getPX(),b->getPY());

            //Si el jugador uno se golpea con un moob
            if(bars.at(1)->colision_enemigo() == true){
                Vida_Jugador_1 -= moobs.at(0)->getDanio_Enemigo();
                ui->Vida_1->setText(QString::number(Vida_Jugador_1));
                if(Vida_Jugador_1 == 0){
                    scene->removeItem(bars.at(1));
                    Vidas_jugador_1 -= 1;
                    if(Vidas_jugador_1 != 0){
                        ui->N_Vidas_1->setText(QString::number(Vidas_jugador_1));
                        QMessageBox msgBox;
                        msgBox.setText("presiona ok para intentarlo de nuevo");
                        msgBox.exec();
                        Vida_Jugador_1 = 100;
                        scene->addItem(bars.at(1));
                    }
                    else{
                        QMessageBox msgBox;
                        msgBox.setText("GAME OVER CURRAMBA, dale en reiniciar para intentar de nuevo");
                        msgBox.exec();
                        Vida_Jugador_1 = 100;
                        Vidas_jugador_1 = 3;
                        infoUsuario.punt1 = 0;
                    }

                }
            }
            //si el jugador uno recoge una moneda
            if(Recoger_monedas() == 1){
                Coin->play();
                infoUsuario.punt1 +=10;
                ui->Puntaje_1->setText(QString::number(infoUsuario.punt1));
            }
            if(coins.empty())
            {
                delete timer;
                scene->removeItem(bars.at(0));
                scene->removeItem(bars.at(1));
                desaparecer_bala();
                desaparecer_Plataformas();
                moobs.clear();
                if(infoUsuario.int1 < 3){
                    infoUsuario.int1++;
                    Cambiar_nivel();
                }
                else
                    cambiarVentana();
            }
        }
        if(event->key() == Qt::Key_W){
            b->set_vel(b->getVX(),60,b->getPX(),b->getPY());

            //Si el jugador uno se golpea con un moob
            if(bars.at(1)->colision_enemigo() == true){
                Vida_Jugador_1 -= moobs.at(0)->getDanio_Enemigo();
                ui->Vida_1->setText(QString::number(Vida_Jugador_1));
                if(Vida_Jugador_1 == 0){
                    scene->removeItem(bars.at(1));
                    Vidas_jugador_1 -= 1;
                    if(Vidas_jugador_1 != 0){
                        ui->N_Vidas_1->setText(QString::number(Vidas_jugador_1));
                        QMessageBox msgBox;
                        msgBox.setText("presiona ok para intentarlo de nuevo");
                        msgBox.exec();
                        Vida_Jugador_1 = 100;
                        scene->addItem(bars.at(1));
                    }
                    else{
                        QMessageBox msgBox;
                        msgBox.setText("GAME OVER CURRAMBA, dale en reiniciar para intentar de nuevo");
                        msgBox.exec();
                        Vida_Jugador_1 = 100;
                        Vidas_jugador_1 = 3;
                        infoUsuario.punt1 = 0;
                    }

                }
            }
            //si el jugador uno recoge una moneda
            if(Recoger_monedas() == 1){
                Coin->play();
                infoUsuario.punt1 +=10;
                ui->Puntaje_1->setText(QString::number(infoUsuario.punt1));
            }
            if(coins.empty())
            {
                delete timer;
                scene->removeItem(bars.at(0));
                scene->removeItem(bars.at(1));
                desaparecer_bala();
                desaparecer_Plataformas();
                moobs.clear();
                if(infoUsuario.int1 < 3){
                    infoUsuario.int1++;
                    Cambiar_nivel();
                }
                else
                    cambiarVentana();
            }
        }

        //Movimientos del jugador 2
        if(event->key() == Qt::Key_L){
            a->set_vel(20,a->getVY(),a->getPX(),a->getPY());

            //Si el jugador uno se golpea con un moob
            if(bars.at(0)->colision_enemigo() == true){
                Vida_Jugador_2 -= moobs.at(0)->getDanio_Enemigo();
                ui->Vida_2->setText(QString::number(Vida_Jugador_2));
                if(Vida_Jugador_2 == 0){
                    scene->removeItem(bars.at(0));
                    Vidas_jugador_2 -= 1;
                    if(Vidas_jugador_2 != 0){
                        ui->N_Vidas_2->setText(QString::number(Vidas_jugador_2));
                        QMessageBox msgBox;
                        msgBox.setText("presiona ok para intentarlo de nuevo");
                        msgBox.exec();
                        Vida_Jugador_2 = 100;
                        scene->addItem(bars.at(0));
                    }
                    else{
                        QMessageBox msgBox;
                        msgBox.setText("GAME OVER CURRAMBA, dale en reiniciar para intentar de nuevo");
                        msgBox.exec();
                        Vida_Jugador_2 = 100;
                        Vidas_jugador_2 = 3;
                        infoUsuario.punt2 = 0;
                    }

                }
            }
            //si el jugador dos recoge una moneda
            if(Recoger_monedas() == 1){
                Coin->play();
                infoUsuario.punt2 +=10;
                ui->Puntaje_2->setText(QString::number(infoUsuario.punt2));
            }
            if(coins.empty())
            {
                delete timer;
                scene->removeItem(bars.at(0));
                scene->removeItem(bars.at(1));
                desaparecer_bala();
                desaparecer_Plataformas();
                moobs.clear();
                if(infoUsuario.int1 < 3){
                    infoUsuario.int1++;
                    Cambiar_nivel();
                }
                else
                    cambiarVentana();
            }
        }
        if(event->key() == Qt::Key_J){
            a->set_vel(-20,a->getVY(),a->getPX(),a->getPY());

            //Si el jugador uno se golpea con un moob
            if(bars.at(0)->colision_enemigo() == true){
                Vida_Jugador_2 -= moobs.at(0)->getDanio_Enemigo();
                ui->Vida_2->setText(QString::number(Vida_Jugador_2));
                if(Vida_Jugador_2 == 0){
                    scene->removeItem(bars.at(0));
                    Vidas_jugador_2 -= 1;
                    if(Vidas_jugador_2 != 0){
                        ui->N_Vidas_2->setText(QString::number(Vidas_jugador_2));
                        QMessageBox msgBox;
                        msgBox.setText("presiona ok para intentarlo de nuevo");
                        msgBox.exec();
                        Vida_Jugador_2 = 100;
                        scene->addItem(bars.at(0));
                    }
                    else{
                        QMessageBox msgBox;
                        msgBox.setText("GAME OVER CURRAMBA, dale en reinicar para empezar de nuevo");
                        msgBox.exec();
                        Vida_Jugador_2 = 100;
                        Vidas_jugador_2 = 3;
                        infoUsuario.punt2 = 0;
                    }

                }
            }
            //si el jugador dos recoge una moneda
            if(Recoger_monedas() == 1){
                Coin->play();
                infoUsuario.punt2 +=10;
                ui->Puntaje_2->setText(QString::number(infoUsuario.punt2));
            }
            if(coins.empty())
            {
                delete timer;
                scene->removeItem(bars.at(0));
                scene->removeItem(bars.at(1));
                desaparecer_bala();
                desaparecer_Plataformas();
                moobs.clear();
                if(infoUsuario.int1 < 3){
                    infoUsuario.int1++;
                    Cambiar_nivel();
                }
                else
                    cambiarVentana();
            }
        }
        if(event->key() == Qt::Key_I){
            a->set_vel(a->getVX(),60,a->getPX(),a->getPY());

            //Si el jugador uno se golpea con un moob
            if(bars.at(0)->colision_enemigo() == true){
                Vida_Jugador_2 -= moobs.at(0)->getDanio_Enemigo();
                ui->Vida_2->setText(QString::number(Vida_Jugador_2));
                if(Vida_Jugador_2 == 0){
                    scene->removeItem(bars.at(0));
                    Vidas_jugador_2 -= 1;
                    if(Vidas_jugador_2 != 0){
                        ui->N_Vidas_2->setText(QString::number(Vidas_jugador_2));
                        QMessageBox msgBox;
                        msgBox.setText("presiona ok para intentarlo de nuevo");
                        msgBox.exec();
                        Vida_Jugador_2 = 100;
                        scene->addItem(bars.at(0));
                    }
                    else{
                        QMessageBox msgBox;
                        msgBox.setText("GAME OVER CURRAMBA, dale en reiniciar para empezar de nuevo");
                        msgBox.exec();
                        Vida_Jugador_2 = 100;
                        Vidas_jugador_2 = 3;
                        infoUsuario.punt2 = 0;
                    }

                }
            }
            //si el jugador dos recoge una moneda
            if(Recoger_monedas() == 1){
                Coin->play();
                infoUsuario.punt2 +=10;
                ui->Puntaje_2->setText(QString::number(infoUsuario.punt2));


            }

            if(coins.empty())
            {
                delete timer;
                scene->removeItem(bars.at(0));
                scene->removeItem(bars.at(1));
                desaparecer_bala();
                desaparecer_Plataformas();
                if(infoUsuario.int1 < 3){
                    infoUsuario.int1++;
                    Cambiar_nivel();
                }
                else
                    cambiarVentana();
            }
        }

    }
}

/* Crea los enemigos del nivel 1, asignandolos a una lista que contiene un puntero tipo enemigos y agregandolos a la escena*/
void Ventanajuego::moobs_nivel_1()
{
    moobs.push_back(new Enemigos(400,0));
    scene->addItem(moobs.back());

    moobs.push_back(new Enemigos(800, 0));
    scene->addItem(moobs.back());

}

/* Crea los enemigos del nivel 2, asignandolos a una lista que contiene un puntero tipo enemigos y agregandolos a la escena*/
void Ventanajuego::moobs_nivel_2()
{
    moobs.push_back(new Enemigos(400,0));
    scene->addItem(moobs.back());
    moobs.back()->actualizar(v_limit);

    moobs.push_back(new Enemigos(800, 0));
    scene->addItem(moobs.back());
    moobs.back()->actualizar(v_limit);

    moobs.push_back(new Enemigos(500,200));
    scene->addItem(moobs.back());
    moobs.back()->actualizar(v_limit);

    moobs.push_back(new Enemigos(900, 200));
    scene->addItem(moobs.back());
    moobs.back()->actualizar(v_limit);

    moobs.push_back(new Enemigos(0,200));
    scene->addItem(moobs.back());
    moobs.back()->actualizar(v_limit);

    moobs.push_back(new Enemigos(800, 0));
    scene->addItem(moobs.back());
    moobs.back()->actualizar(v_limit);

    moobs.push_back(new Enemigos(300,200));
    scene->addItem(moobs.back());
    moobs.back()->actualizar(v_limit);

    moobs.push_back(new Enemigos(600, 200));
    scene->addItem(moobs.back());

    moobs.push_back(new Enemigos(400,0));
    scene->addItem(moobs.back());

}

/* Crea los enemigos del nivel 3, asignandolos a una lista que contiene un puntero tipo enemigos y agregandolos a la escena*/
void Ventanajuego::moobs_nivel_3()
{
    moobs.push_back(new Enemigos(0, 600));
    scene->addItem(moobs.back());
    moobs.back()->actualizar(v_limit);

    moobs.push_back(new Enemigos(300, 200));
    scene->addItem(moobs.back());
    moobs.back()->actualizar(v_limit);

    moobs.push_back(new Enemigos(450, 600));
    scene->addItem(moobs.back());
    moobs.back()->actualizar(v_limit);

    moobs.push_back(new Enemigos(600, 200));
    scene->addItem(moobs.back());
    moobs.back()->actualizar(v_limit);

    moobs.push_back(new Enemigos(900, 200));
    scene->addItem(moobs.back());
    moobs.back()->actualizar(v_limit);

    moobs.push_back(new Enemigos(1050, 200));
    scene->addItem(moobs.back());
    moobs.back()->actualizar(v_limit);

    moobs.push_back(new Enemigos(1200, 200));
    scene->addItem(moobs.back());
    moobs.back()->actualizar(v_limit);

    moobs.push_back(new Enemigos(1200, 200));
    scene->addItem(moobs.back());
    moobs.back()->actualizar(v_limit);

    moobs.push_back(new Enemigos(400, 0));
    scene->addItem(moobs.back());
    moobs.back()->actualizar(v_limit);

    moobs.push_back(new Enemigos(900, 0));
    scene->addItem(moobs.back());
    moobs.back()->actualizar(v_limit);

    moobs.push_back(new Enemigos(1375, 600));
    scene->addItem(moobs.back());
    moobs.back()->actualizar(v_limit);

    moobs.push_back(new Enemigos(700, 600));
    scene->addItem(moobs.back());
    moobs.back()->actualizar(v_limit);

    moobs.push_back(new Enemigos(400, 400));
    scene->addItem(moobs.back());
    moobs.back()->actualizar(v_limit);

}

/* Crea las plataformas del nivel 1, asignandolas a una lista que contiene un puntero tipo plataformas y agregandolas a
 * la escena*/
void Ventanajuego::Plataformas_Nivel_1()
{
    Plataform.push_back(new plataforma(100, 200, 120, 20, 1));
    scene->addItem(Plataform.back());

    Plataform.push_back(new plataforma(300, 200, 200, 20, 1));
    scene->addItem(Plataform.back());

    Plataform.push_back(new plataforma(600, 200, 90, 20, 1));
    scene->addItem(Plataform.back());

}

/* Crea las plataformas del nivel 2, asignandolas a una lista que contiene un puntero tipo plataformas y agregandolas a
 * la escena*/
void Ventanajuego::Plataformas_Nivel_2()
{
    Plataform.push_back(new plataforma(0, 200, 200, 20, 2));
    scene->addItem(Plataform.back());

    Plataform.push_back(new plataforma(270, 200, 200, 20, 2));
    scene->addItem(Plataform.back());

    Plataform.push_back(new plataforma(573, 200, 200, 20, 2));
    scene->addItem(Plataform.back());

    Plataform.push_back(new plataforma(150, 200, 100, 20, 2));
    scene->addItem(Plataform.back());

    Plataform.push_back(new plataforma(450, 200, 100, 20, 2));
    scene->addItem(Plataform.back());

}

/* Crea las plataformas del nivel 3, asignandolas a una lista que contiene un puntero tipo plataformas y agregandolas a
 * la escena*/
void Ventanajuego::Plataformas_Nivel_3()
{

    Plataform.push_back(new plataforma(0, 200, 120, 20, 3));
    scene->addItem(Plataform.back());

    Plataform.push_back(new plataforma(150, 200, 120, 20, 3));
    scene->addItem(Plataform.back());

    Plataform.push_back(new plataforma(300, 200, 120, 20, 3));
    scene->addItem(Plataform.back());

    Plataform.push_back(new plataforma(450, 200, 120, 20, 3));
    scene->addItem(Plataform.back());

    Plataform.push_back(new plataforma(573, 200, 200, 20, 3));
    scene->addItem(Plataform.back());

}

/* Crea las monedas del nivel 1, asignandolas a una lista que contiene un puntero tipo monedas y agregandolas a
 * la escena*/
void Ventanajuego::Monedas_Nivel_1()
{
    coins.push_back(new Moneda(200, 275, 50, 50, 1));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(100, 185, 50, 50, 1));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(200, 115, 50, 50, 1));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(500, 115, 50, 50, 1));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(300, 185, 50, 50, 1));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(500, 275, 50, 50, 1));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(620, 180, 50, 50, 1));
    scene->addItem(coins.back());
}

/* Crea las monedas del nivel 2, asignandolas a una lista que contiene un puntero tipo monedas y agregandolas a
 * la escena*/
void Ventanajuego::Monedas_Nivel_2()
{
    coins.push_back(new Moneda(10, 113, 50,50, 1));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(10, 55, 50,50, 1));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(640, 55, 50,50, 1));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(640, 180, 50,50, 1));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(310, 180, 50,50, 1));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(310, 55, 50,50, 1));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(640, 250, 50,50, 1));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(310, 250, 50,50, 1));
    scene->addItem(coins.back());


}

/* Crea las monedas del nivel 3, asignandolas a una lista que contiene un puntero tipo monedas y agregandolas a
 * la escena*/
void Ventanajuego::Monedas_Nivel_3()
{
    coins.push_back(new Moneda(10, 180, 50, 50, 2));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(10, 85, 50, 50, 2));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(630, 85, 50, 50, 2));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(150, 85, 50, 50, 2));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(450, 85, 50, 50, 2));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(300, 85, 50, 50, 2));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(10, 180, 50, 50, 2));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(630, 180, 50, 50, 2));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(150, 180, 50, 50, 2));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(450, 180, 50, 50, 2));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(300, 180, 50, 50, 2));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(10, 250, 50, 50, 2));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(630, 250, 50, 50, 2));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(150, 250, 50, 50, 2));
    scene->addItem(coins.back());

    coins.push_back(new Moneda(450, 250, 50, 50, 2));
    scene->addItem(coins.back());
}

/* Crea las monedas finales, asignandolas a una lista que contiene un puntero tipo monedas y agregandolas a
 * la escena*/
void Ventanajuego::Moneda_final()
{
    coins_final.push_back(new Moneda(180, 180, 50,50, 2));
    scene->addItem(coins_final.back());

}

/* Funcion encargada de eliminar las monedas con las que el jugador colisione retorna un true para cuestiones de suma de puntos
*/
bool Ventanajuego::Recoger_monedas()
{
    QList<Moneda*>::iterator it;

    for(it = coins.begin(); it != coins.end(); it++){
        for (int i = 0; i<bars.size() ; i++) {
            if(bars.at(i)->collidesWithItem(*it)){
                scene->removeItem(*it);
                coins.removeOne(*it);
                return true;
            }
        }
    }
    return false;
}

/* retorna un booleano para conocer el estado de colisiones con plataformas y jugador, asi mismo asigna a una varible el valor de la
   la posicion en y de la plataforma donde debe subir el jugador*/
bool Ventanajuego::Verificar_Colisiones()
{
        for(int j = 0; j< Plataform.size(); j++){
            if(bars.at(0)->collidesWithItem(Plataform.at(j))){
                Pos_Y_collision = Plataform.at(j)->getPos_Y();
            return true;
            }
        }
        return false;
}

/* Retorna un booleano para conocer el estado de las colisiones con las plataformas y jugador, usada en el multijugador
   asi mismo asigna la posicion en y de la plataforma a la que debe subir el segundo jugador*/
bool Ventanajuego::Verificar_Colisiones_Mult()
{
    for(int j = 0; j< Plataform.size(); j++){
        if(bars.at(1)->collidesWithItem(Plataform.at(j))){
            Pos_Y_collision_2 = Plataform.at(j)->getPos_Y();
        return true;
        }
    }
    return false;

}

/* Elimina las balas y el enemigo que colisionaron de la lista en donde estan respectivamente almacenados*/
void Ventanajuego::eliminacion()
{
    for(int i = 0; i<moobs.size(); i++){
        for(int j = 0; j<balas.size(); j++){
            if(moobs.at(i)->collidesWithItem(balas.at(j))){
                muerte->play();
                moobs.removeAt(i);
                balas.removeAt(j);
            }
        }
    }
}

/* limpia la lista de balas para hacer efectivo el cambio de nivel*/
void Ventanajuego::desaparecer_bala()
{
    for(int i = 0; i<balas.size() ; i++){
        scene->removeItem(balas.at(i));
    }
    balas.clear();
}

/* Limpia la lista de enemigos para hacer efectivo el cambio de nivel */
void Ventanajuego::desaparecer_Plataformas()
{
    for(int i = 0; i<Plataform.size() ; i++){
        scene->removeItem(Plataform.at(i));
    }
    Plataform.clear();
    Pos_Y_collision = 0;
}

/*Retorna la variable location, que indica el nivel en el que se encuentra actualmente el jugador */
unsigned short Ventanajuego::getLocation() const
{
    return infoUsuario.int1;
}

/*inicia el juego, y quita la pause, si la lista de personajes esta vacia dibuja nuevos personajes
   adicionalmente se agrega el timer y los elementos graficos de cada nivel, y los indicaadores
    de vida y puntaje*/
void Ventanajuego::on_Iniciar_Juego_clicked()
{
    if(infoUsuario.mult == false){
        timer->start(3);
        if(bars.size() == 0){
            ui->Vida_1->setText(QString::number(Vida_Jugador_1));
            ui->Puntaje_1->setText(QString::number(infoUsuario.punt1));
            Vidas_jugador_1 = 3;
            ui->N_Vidas_1->setText(QString::number(Vidas_jugador_1));
            bars.push_back(new personajes(1, 3));
            bars.back()->actualizar(v_limit);
            scene->addItem(bars.back());
        }
    }
    if(infoUsuario.mult == true){
        timer->start(3);
        Vida_Jugador_1 = 100;
        Vida_Jugador_2 = 100;
        if(bars.size() == 0){
            ui->Vida_1->setText(QString::number(Vida_Jugador_1));
            ui->Puntaje_1->setText(QString::number(infoUsuario.punt1));
            ui->Vida_2->setText(QString::number(Vida_Jugador_2));
            ui->Puntaje_2->setText(QString::number(infoUsuario.punt2));
            Vidas_jugador_1 = 3;
            ui->N_Vidas_1->setText(QString::number(Vidas_jugador_1));
            Vidas_jugador_2 = 3;
            ui->N_Vidas_2->setText(QString::number(Vidas_jugador_2));

            bars.push_back(new personajes(1,3));
            bars.back()->actualizar(v_limit);
            scene->addItem(bars.back());

            //Creación del Segundo personaje
            bars.push_back(new personajes(2, 3));
            bars.back()->actualizar(v_limit);
            scene->addItem(bars.back());
        }
    }


}

/* Elimina el timer con lo que el juego y los movimientos de los elementos en escena entran en pausa*/
void Ventanajuego::on_Pausa_Juego_clicked()
{
    timer->stop();
}

/* tiene las indicaciones del cambio de nivel cumplidas algunas especificaciones, agrega elemenos graficos
    configura la escena grafica, resetea los disparos,  agrega nuevos jugadores, inicia el connect en el
    nuevo nivel.*/
void Ventanajuego::Cambiar_nivel()
{
    if(infoUsuario.int1 == 1){
        //Elemntos graficos del primer nivel
        timer = new QTimer(this);
        scene = new QGraphicsScene(this);
        scene->setSceneRect(0, 0,h_limit,v_limit);
        scene->setBackgroundBrush(QBrush(QImage(":/Imagenes/1 screen.png")));
        ui->graphicsView->setScene(scene);
        scene->addRect(scene->sceneRect());
        ui->graphicsView->resize(scene->width(),scene->height());
        this->resize(ui->graphicsView->width(),ui->graphicsView->height());
        Plataformas_Nivel_1();
        Monedas_Nivel_1();
        moobs_nivel_1();
        num_disparos_1 = 5;
        num_disparos_2 = 5;
        scene->addItem(bars.at(0));
        if(infoUsuario.mult == 1)
            scene->addItem(bars.at(1));
        connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));
    }

    if(infoUsuario.int1 == 2){
        //Elementos graficos del segundo nivel
        cambiarVentana();
        timer = new QTimer(this);
        scene = new QGraphicsScene(this);
        scene->setSceneRect(0,0,h_limit,v_limit);
        scene->setBackgroundBrush(QBrush(QImage(":/Imagenes/nivel 2.png")));
        ui->graphicsView->setScene(scene);
        scene->addRect(scene->sceneRect());
        ui->graphicsView->resize(scene->width(),scene->height());
        this->resize(ui->graphicsView->width(),ui->graphicsView->height());
        Plataformas_Nivel_2();
        Monedas_Nivel_2();
        moobs_nivel_2();
        num_disparos_1 = 5;
        num_disparos_2 = 5;
        scene->addItem(bars.at(0));
        if(infoUsuario.mult == 1)
            scene->addItem(bars.at(1));
        connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));

    }

    if(infoUsuario.int1 == 3){
        cambiarVentana();
        //Elementos graficos del tercer nivel
        timer = new QTimer(this);
        scene = new QGraphicsScene(this);
        scene->setSceneRect(0,0,h_limit,v_limit);
        scene->setBackgroundBrush(QBrush(QImage(":/Imagenes/2 screen.png")));
        ui->graphicsView->setScene(scene);
        scene->addRect(scene->sceneRect());
        ui->graphicsView->resize(scene->width(),scene->height());
        this->resize(ui->graphicsView->width(),ui->graphicsView->height());
        Plataformas_Nivel_3();
        Monedas_Nivel_3();
        moobs_nivel_3();
        num_disparos_1 = 5;
        num_disparos_2 = 5;
        scene->addItem(bars.at(0));
        if(infoUsuario.mult == 1)
            scene->addItem(bars.at(1));
        connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));


    }
}

/* Cambia de ventanaJuego a ventana de comic dado el caso, usa memoria dinamica para el cambio de escena*/
void Ventanajuego::cambiarVentana()
{
    Comic *historia = new Comic;
    this->setVisible(false);
    historia->show();
}

/* Guarda la partida mediante el uso del un metodo en el objeto tipo loader. Recibe un infousuario que es la estructura
    de datos usada para el guardado y cargado de la partida*/
void Ventanajuego::on_Guardar_clicked()
{
    Save_Match.Guardar_Partida(infoUsuario);
}

/* Inicia la musica en el videojuego*/
void Ventanajuego::on_Musica_clicked()
{
    if(musica->state() == QMediaPlayer::PlayingState){
        musica->stop();
    }
    else if(musica->state() == QMediaPlayer::StoppedState){
        musica->play();
    }
}

/*Reinicia el juego, borrando todos los datos que se tenian y asignando location como 1 y puntajes = 0
    */
void Ventanajuego::on_reiniciar_clicked()
{
    delete timer;
    scene->removeItem(bars.at(0));
    coins.clear();
    desaparecer_Plataformas();
    infoUsuario.int1 = 1;
    infoUsuario.punt1 = 0;
    infoUsuario.punt2 = 0;
    infoUsuario.click_comic = 0;
    Cambiar_nivel();
}

/*Ventana emergente que indica las instrucciones para el correcto funcionamiento del videojuego.*/
void Ventanajuego::on_Instrucciones_clicked()
{
    timer->stop();
    if (infoUsuario.mult==0){
    QMessageBox msgBox;
    msgBox.setText("Bienvenido a las instrucciones de Das Land Des Sittich" "\n"
                   "-La idea principal del juego es coger todos los pericos y esquivar a los enemigos (Tombos), con el fin de conseguir el SITTICH" "\n"
                   "-ACTIVA LA MUSICA CON EL BOTON MUSICA ON/OFF" "\n"
                   "-AGRANDA LA PANTALLA PARA UNA MEJOR EXPERIENCIA DE JUEGO" "\n"
                   "-Puedes moverte con las teclas A y D, la tecla A es para moverte hacia la izquierda y la tecla D es para moverte hacia la derecha" "\n"
                   "-Puedes disparar con las teclas Q y E, pero ten cuidado solo tienes 3 proyectiles" "\n"
                   "-Con la tecla Q disparas hacia la izquierda y con la tecla E disparas hacia la derecha" "\n"
                   "Que te diviertas y que logres conseguir el SITTICH, !Mucha suerte aventurero!");
    msgBox.exec();
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Bienvenido a las instrucciones de Das Land Des Sittich" "\n"
                       "-La idea principal del juego es coger todos pericos y esquivar los enemigos (Tombos), con el fin de conseguir el SITTICH" "\n"
                       "-ACTIVA LA MUSICA CON EL BOTON MUSICA ON/OFF" "\n"
                       "-AGRANDA LA PANTALLA PARA UNA MEJOR EXPERIENCIA DE JUEGO" "\n"
                       "-Para mover a Eliodoro utiliza las teclas A y D. Para mover a Joaquin utiliza las teclas J y L" "\n"
                       "-Con las teclas A y J los personajes se muevan a la izquierda y con las teclas D y L los personajes se muevan a la derecha" "\n"
                       "-Con las teclas Q y U los personajes disparan hacia la izquierda y con las teclas E y O los personajes disparan hacia la derecha" "\n"
                       "-Con la tecla Q disparas hacia la izquierda y con la tecla E disparas hacia la derecha" "\n"
                       "Que te diviertas y que logres conseguir el SITTICH, !Mucha suerte aventurero!");
        msgBox.exec();
    }
}
