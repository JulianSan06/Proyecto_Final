#include "loader.h"
#define RUTA_ARCHIVO "Partidas.txt"

Loader::Loader()
{

}

void Loader::Guardar_Partida(infoArchivo infoJuego)
{
    if (infoJuego.mult==0){
        if (infoJuego.click_comic==7){    // Se le disminuye dos debido a que cuando quedaba en este valor especifico no mostraba el comic correctamente
            infoJuego.click_comic-=2;
        }
        else if (infoJuego.click_comic==10){
            infoJuego.click_comic-=2;
        }
        /* Guardamos los datos que estan en la clase informacion en un archivo de texto
         * llamado datos, se va guardando cada variable independiente de la otra
         * esto con la ayuda de la ',' la cual nos ayuda a distinguir entre un valor
         * y otro. */
        QString datos=QString::number(infoJuego.mult) + "," + QString::number(infoJuego.int1) + "," + QString::number(infoJuego.punt1) + "," + QString::number((infoJuego.click_comic));
        QFile file("Partidas.txt");
        QTextStream write(&file);
        file.open((QIODevice::WriteOnly | QIODevice::Text));
        write << datos;
        file.close();
        datos.clear();
    }
    else{
        if (infoJuego.click_comic==7){
            infoJuego.click_comic-=2;
        }
        else if (infoJuego.click_comic==10){
            infoJuego.click_comic-=2;
        }
        QString datos=QString::number(infoJuego.mult) + "," + QString::number(infoJuego.int1) + "," + QString::number(infoJuego.punt1) + "," + QString::number(infoJuego.punt2) + "," + QString::number((infoJuego.click_comic));
        QFile file("Partidas.txt");
        QTextStream write(&file);
        file.open((QIODevice::WriteOnly | QIODevice::Text));
        write << datos;
        file.close();
        datos.clear();
    }
}

infoArchivo Loader::Cargar_Partida()
{
    /* Funcion para cargar la partida desde el boton de ventanamodojuego,
     * esta funcion va ligada totalmente a la clase informacion debido
     * a que esta se encarga de pasarle los valores guardados en el
     * archivo de texto cuyo nombre es partidas.txt */
    infoArchivo Datos;
    QString info;
    QFile file(RUTA_ARCHIVO);
    file.open(QIODevice::ReadOnly);
    QTextStream read(&file);
    read >> info;
    file.close();
    QStringList datos = info.split(QLatin1Char(','));
    if (datos.size()==4){
        Datos.mult=datos[0].toInt();
        Datos.int1=datos[1].toInt();
        Datos.punt1=datos[2].toInt();
        Datos.click_comic=datos[3].toInt();
    }
    else {
        Datos.mult=datos[0].toInt();
        Datos.int1=datos[1].toInt();
        Datos.punt1=datos[2].toInt();
        Datos.punt2=datos[3].toInt();
        Datos.click_comic=datos[4].toInt();
    }
    return Datos;
}
