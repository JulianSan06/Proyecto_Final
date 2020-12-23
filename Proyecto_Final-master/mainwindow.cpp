#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    srand(time(NULL));
    ui->setupUi(this);

    h_limit = 1500;
    v_limit = 500;

    timer = new QTimer(this);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,h_limit,v_limit);

    ui->graphicsView->setScene(scene);
    ui->centralwidget->adjustSize();
    scene->addRect(scene->sceneRect());
    ui->graphicsView->resize(scene->width(),scene->height());
    this->resize(ui->graphicsView->width()+100,ui->graphicsView->height()+100);

    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));

}

MainWindow::~MainWindow()
{
    delete timer;
    delete scene;
    delete ui;
}

void MainWindow::actualizar()
{

    for (int i = 0;i != bars.size() ;i++ ) {
        bars.at(i)->actualizar(v_limit);
        borderCollision(bars.at(i)->getEsf());
    }

}

void MainWindow::borderCollision(Fisicas *b)
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(Mult == 0){
        Fisicas * b = bars.at(0)->getEsf();
        if(event->key() == Qt::Key_D){
            b->set_vel(25,b->getVY(),b->getPX(),b->getPY());
            bars.at(0)->setRotation(0);
        }
        if(event->key() == Qt::Key_A){
            b->set_vel(-25,b->getVY(),b->getPX(),b->getPY());
            bars.at(0)->setRotation(45); //Esta Rotacion esta mala
        }
        if(event->key() == Qt::Key_W){
            b->set_vel(b->getVX(),80,b->getPX(),b->getPY());
        }
    }

    if(Mult == 1){
        Fisicas * b = bars.at(0)->getEsf();
        Fisicas * a = bars.at(1)->getEsf();

       //movimientos del jugador 1
        if(event->key() == Qt::Key_D){
            b->set_vel(25,b->getVY(),b->getPX(),b->getPY());
            bars.at(0)->setRotation(0);
        }
        if(event->key() == Qt::Key_A){
            b->set_vel(-25,b->getVY(),b->getPX(),b->getPY());
            bars.at(0)->setRotation(-45);  //Esta Rotacion esta mala
        }
        if(event->key() == Qt::Key_W){
            b->set_vel(b->getVX(),80,b->getPX(),b->getPY());
        }

        //Movimientos del jugador 2
        if(event->key() == Qt::Key_L){
            a->set_vel(25,b->getVY(),b->getPX(),b->getPY());
            bars.at(0)->setRotation(0);
        }
        if(event->key() == Qt::Key_J){
            a->set_vel(-25,b->getVY(),b->getPX(),b->getPY());
            bars.at(0)->setRotation(45);    //Esa Rotacion esta mala
        }
        if(event->key() == Qt::Key_I){
            a->set_vel(b->getVX(),80,b->getPX(),b->getPY());
        }

    }



}

void MainWindow::on_MonoJugador_clicked()
{
    timer->start(3);
    bars.push_back(new personajes(1));
    bars.back()->actualizar(v_limit);
    scene->addItem(bars.back());
}



void MainWindow::on_Multijugador_clicked()
{
    timer->start(3);
    //Primer personaje
    bars.push_back(new personajes(1));
    bars.back()->actualizar(v_limit);
    scene->addItem(bars.back());

    //Segundo personaje
    timer->start(3);
    bars.push_back(new personajes(2));
    bars.back()->actualizar(v_limit);
    scene->addItem(bars.back());

    Mult = true;
}
