#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "basedrawer.h"
#include "QDebug"
#include <stdio.h>
#define SCALE 5
using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создание и начальная инициализация объектов
    scene = new Drawer();
    ui->PaintingScene->setScene(scene);



    // Создадим ракету
    _rocket.createRocket(SCALE);
    cameraPosition.setX(0);
    cameraPosition.setY(0);
    cameraPosition.setZ(600);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::render()
{
    scene->clear();
    scene->drawRocket(_rocket, cameraPosition);

}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );

    return d;
}

void MainWindow::on_Draw_clicked()
{
    render();
}

void MainWindow::on_rotate_clicked()
{

    bool ok1 = true, ok2;

    QString x = ui->editX->text();
    int angleX = x.toDouble(&ok1);
    QString y = ui->editY->text();
    int angleY = y.toDouble(&ok2);

    qDebug() << angleY;
    _rocket.rotateX(angleX);
    _rocket.rotateY(angleY);

    render();
}
/*
// добавить камеру,
матрицы поворотов и вращений и переносов,
добавить сцену и добавлять объекты в сцену,
рисовать на QImage и потом переносить на QGraphicsView

*/
