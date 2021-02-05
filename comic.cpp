#include "comic.h"
#include "ui_comic.h"

extern infoArchivo infoUsuario;

Comic::Comic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Comic)
{
    ui->setupUi(this);
    h_limit = 900;
    v_limit = 600;
    /* Se genera la escena y se pregunta si los click en el boton siguiente es igual
     * al valor correspondiente al if, esto con el fin de ir avanzando en el comic
     * segun la cantidad de clicks que tenga el contador click_comic */
    if (infoUsuario.click_comic==0){
        scene = new QGraphicsScene(this);
        scene->setSceneRect(0, 0,h_limit,v_limit);
        scene->setBackgroundBrush(QBrush(QImage(":/Comic/Historia 1.png")));
        ui->graphicsView->setScene(scene);
        scene->addRect(scene->sceneRect());
        ui->graphicsView->resize(scene->width(),scene->height());
        this->resize(ui->graphicsView->width(),ui->graphicsView->height());
    }
    setFixedSize(900,600);
}

Comic::~Comic()
{
    delete ui;
}

void Comic::on_Siguiente_clicked()
{
    /*Boton para intercambiar entre imagenes en el comic */
    infoUsuario.click_comic++;
    cambio_historia();
}

void Comic::cambio_historia()
{
    /* Funcion donde segun la cantidad de clicks muestra una imagen correspondiente al numero de la historieta */
    if (infoUsuario.click_comic==1){
        scene = new QGraphicsScene(this);
        scene->setSceneRect(0, 0,h_limit,v_limit);
        scene->setBackgroundBrush(QBrush(QImage(":/Comic/Historia 2.png")));
        ui->graphicsView->setScene(scene);
        scene->addRect(scene->sceneRect());
        ui->graphicsView->resize(scene->width(),scene->height());
        this->resize(ui->graphicsView->width(),ui->graphicsView->height());
    }
    if (infoUsuario.click_comic==2){
        scene = new QGraphicsScene(this);
        scene->setSceneRect(0, 0,h_limit,v_limit);
        scene->setBackgroundBrush(QBrush(QImage(":/Comic/Historia 3.png")));
        ui->graphicsView->setScene(scene);
        scene->addRect(scene->sceneRect());
        ui->graphicsView->resize(scene->width(),scene->height());
        this->resize(ui->graphicsView->width(),ui->graphicsView->height());
    }
    if (infoUsuario.click_comic==3){
        scene = new QGraphicsScene(this);
        scene->setSceneRect(0, 0,h_limit,v_limit);
        scene->setBackgroundBrush(QBrush(QImage(":/Comic/Historia 4.png")));
        ui->graphicsView->setScene(scene);
        scene->addRect(scene->sceneRect());
        ui->graphicsView->resize(scene->width(),scene->height());
        this->resize(ui->graphicsView->width(),ui->graphicsView->height());
        QMessageBox msgBox;
        msgBox.setText("Por favor lee las instrucciones antes de jugar, estas se encuentran ubicadas en la esquina inferior derecha, gracias");
        msgBox.exec();
    }
    if (infoUsuario.click_comic==4){
        cambio_ventana();
    }
    if (infoUsuario.click_comic==5){
        scene = new QGraphicsScene(this);
        scene->setSceneRect(0, 0,h_limit,v_limit);
        scene->setBackgroundBrush(QBrush(QImage(":/Comic/Historia 5.png")));
        ui->graphicsView->setScene(scene);
        scene->addRect(scene->sceneRect());
        ui->graphicsView->resize(scene->width(),scene->height());
        this->resize(ui->graphicsView->width(),ui->graphicsView->height());
    }
    if (infoUsuario.click_comic==6){
        scene = new QGraphicsScene(this);
        scene->setSceneRect(0, 0,h_limit,v_limit);
        scene->setBackgroundBrush(QBrush(QImage(":/Comic/Historia 6.png")));
        ui->graphicsView->setScene(scene);
        scene->addRect(scene->sceneRect());
        ui->graphicsView->resize(scene->width(),scene->height());
        this->resize(ui->graphicsView->width(),ui->graphicsView->height());
    }
    if (infoUsuario.click_comic==7){
        cambio_ventana();
    }
    if (infoUsuario.click_comic==8){
        scene = new QGraphicsScene(this);
        scene->setSceneRect(0, 0,h_limit,v_limit);
        scene->setBackgroundBrush(QBrush(QImage(":/Comic/Historia 7.png")));
        ui->graphicsView->setScene(scene);
        scene->addRect(scene->sceneRect());
        ui->graphicsView->resize(scene->width(),scene->height());
        this->resize(ui->graphicsView->width(),ui->graphicsView->height());
    }
    if (infoUsuario.click_comic==9){
        scene = new QGraphicsScene(this);
        scene->setSceneRect(0, 0,h_limit,v_limit);
        scene->setBackgroundBrush(QBrush(QImage(":/Comic/Historia 8.png")));
        ui->graphicsView->setScene(scene);
        scene->addRect(scene->sceneRect());
        ui->graphicsView->resize(scene->width(),scene->height());
        this->resize(ui->graphicsView->width(),ui->graphicsView->height());
    }
    if (infoUsuario.click_comic==10){
        cambio_ventana();
    }
    if (infoUsuario.click_comic==11){
        scene = new QGraphicsScene(this);
        scene->setSceneRect(0, 0,h_limit,v_limit);
        scene->setBackgroundBrush(QBrush(QImage(":/Comic/Historia 9.png")));
        ui->graphicsView->setScene(scene);
        scene->addRect(scene->sceneRect());
        ui->graphicsView->resize(scene->width(),scene->height());
        this->resize(ui->graphicsView->width(),ui->graphicsView->height());
    }
    if (infoUsuario.click_comic==12){
        scene = new QGraphicsScene(this);
        scene->setSceneRect(0, 0,h_limit,v_limit);
        scene->setBackgroundBrush(QBrush(QImage(":/Comic/Historia 10.png")));
        ui->graphicsView->setScene(scene);
        scene->addRect(scene->sceneRect());
        ui->graphicsView->resize(scene->width(),scene->height());
        this->resize(ui->graphicsView->width(),ui->graphicsView->height());
    }
    if (infoUsuario.click_comic==13){
        QMessageBox msgBox;
        msgBox.setText("Felicidades, has completado nuestro juego, hiciste que Eliodoro y Joaquin fueran los mejores cantantes vallenateros en el mundon y tu te haz convertido en toda una leyenda vallenata ¡¡CELEBRALO CURRAMBA!");
        msgBox.exec();
    }
    if (infoUsuario.click_comic==14)
        this->close();
}

void Comic::cambio_ventana()
{
    /* Funcion para cambiar a la ventana del juego */
    Ventanajuego *ventana = new Ventanajuego;
    this->setVisible(false);
    ventana->show();
}

