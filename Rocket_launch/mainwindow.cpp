#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "basedrawer.h"
#include "QDebug"
#include <stdio.h>
#include <QKeyEvent>
#define SCALE 5

#define X_SIZE 951
#define Y_SIZE 561
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
    cameraPosition.setZ(-100000);

    // todo

    /*
     * добавить кучу алгоритмов лайк построчное заполнение
     * алгоритм использующий z буффер
     * добавить движние ракеты
     * перевести все к экранным координатам
     *
     */

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_S)
    {
        CameraAngleX -= 5;
        //cameraPosition.setZ(cameraPosition.z() + 5);
    }
    else if (event->key() == Qt::Key_D)
    {
        CameraAngleY += 5;
        //cameraPosition.setX(cameraPosition.x() + 5);
    }
    else if (event->key() == Qt::Key_A)
    {
        CameraAngleY -= 5;
        //cameraPosition.setX(cameraPosition.x() - 5);
    }
    else if (event->key() == Qt::Key_W)
    {
        CameraAngleX += 5;
        //cameraPosition.setZ(cameraPosition.z() - 5);
    }
    else if (event->key() == Qt::Key_E)
    {
        CameraAngleZ += 5;
        //cameraPosition.setY(cameraPosition.y() + 5);
    }
    else if (event->key() == Qt::Key_Z)
    {
        CameraAngleZ -= 5;
        //cameraPosition.setY(cameraPosition.y() - 5);
    }
    QString str0 = QString::number(CameraAngleX);
    QString str1 = QString::number(CameraAngleY);
    QString str2 = QString::number(CameraAngleZ);
    ui->AngleInfo->setText("Angle X: " + str0 + "\n" + "Angle Y: " + str1 + "\n" + "Angle Z: " + str2 + "\n");
    scene->SetCameraAngleS(CameraAngleX, CameraAngleY, CameraAngleZ);
    render();


}

void MainWindow::render()
{

    scene->clear();


    Point3D first(-400, 0, 0);
    Point3D second(400, 0, 0);
    scene->drawLine3D(first, second);

    first.changeAll(0, -250, 0);
    second.changeAll(0, 250, 0);
    scene->drawLine3D(first, second);

    first.changeAll(0, 0, 400);
    second.changeAll(0, 0, -50);
    scene->drawLine3D(first, second);


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
