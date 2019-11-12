#-------------------------------------------------
#
# Project created by QtCreator 2019-09-08T17:09:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Rocket_launch
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    fire.cpp \
        main.cpp \
        mainwindow.cpp \
    basedrawer.cpp \
    controller.cpp \
    drawer.cpp \
    point3d.cpp \
    baseobject.cpp \
    cone.cpp \
    scene/scene.cpp \
    rocket.cpp \
    edges.cpp \
    camera.cpp \
    matrix.cpp \
    transfor_matrix.cpp \
    paintingwidget.cpp \
    triangle.cpp
HEADERS += \
    fire.h \
        mainwindow.h \
    basedrawer.h \
    controller.h \
    drawer.h \
    point3d.h \
    baseobject.h \
    cone.h \
    scene/scene.h \
    rocket.h \
    edges.h \
    camera.h \
    matrix.h \
    transfor_matrix.h \
    paintingwidget.h \
    triangle.h

FORMS += \
        mainwindow.ui
