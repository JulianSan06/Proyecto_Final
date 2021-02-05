QT       += core gui \
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    comic.cpp \
    disparo.cpp \
    enemigos.cpp \
    fisicas.cpp \
    loader.cpp \
    main.cpp \
    moneda.cpp \
    personajes.cpp \
    plataforma.cpp \
    ventanajuego.cpp \
    ventanamodojuego.cpp \
    ventanaseleccionjuego.cpp

HEADERS += \
    comic.h \
    disparo.h \
    enemigos.h \
    fisicas.h \
    informacion.h \
    loader.h \
    moneda.h \
    personajes.h \
    plataforma.h \
    ventanajuego.h \
    ventanamodojuego.h \
    ventanaseleccionjuego.h

FORMS += \
    comic.ui \
    ventanajuego.ui \
    ventanamodojuego.ui \
    ventanaseleccionjuego.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Comic.qrc \
    Imagenes.qrc \
    Sonidos.qrc
