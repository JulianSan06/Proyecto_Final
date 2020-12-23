#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "fisicas.h"
#include "personajes.h"
//
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void actualizar();

private slots:
    void on_MonoJugador_clicked();

    void on_Multijugador_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QGraphicsScene *scene;
    float dt;
    int h_limit;
    int v_limit;
    void borderCollision(Fisicas *b);
    void keyPressEvent(QKeyEvent *event);
    QList<personajes *> bars;
    bool Mult = false;
};
#endif // MAINWINDOW_H
