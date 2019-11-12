#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawer.h"
#include "paintingwidget.h"
#include "QDebug"
#include <stdio.h>
#include <QKeyEvent>
#define SCALE 1

#define X_SIZE 951
#define Y_SIZE 561
using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создание и начальная инициализация объектов
    scene = new PaintWidget(this);

    // Создадим ракету передав в нее центр основания ракеты и ее масштаб
    Point3D rocketCenter(0, 0, 0);
    _rocket.createRocket(rocketCenter, SCALE);
    Point3D coneCenter(150, 150, 50);
    cone.createCone(coneCenter, 30, 30, 100, 5);
    cameraPosition.setX(0);
    cameraPosition.setY(0);
    cameraPosition.setZ(-1000);

    // todo

    /*
     * добавить кучу алгоритмов лайк построчное заполнение
     * алгоритм использующий z буффер
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
    else if (event->key() == Qt::Key_Q)
    {
        cameraPosition.setX(cameraPosition.x() + 5);
        //cameraPosition.setY(cameraPosition.y() + 5);
        //cameraPosition.setZ(cameraPosition.z() + 5);
        //cameraPosition.setY(cameraPosition.y() - 5);
    }
    else if (event->key() == Qt::Key_C)
    {
        cameraPosition.setX(cameraPosition.x() - 5);
        //cameraPosition.setY(cameraPosition.y() - 5);
        //cameraPosition.setZ(cameraPosition.z() - 5);
        //cameraPosition.setY(cameraPosition.y() - 5);
    }
    else if (event->key() == Qt::Key_Y)
    {
        cameraPosition.setZ(cameraPosition.z() - 5);
        //cameraPosition.setY(cameraPosition.y() - 5);
        //cameraPosition.setZ(cameraPosition.z() - 5);
        //cameraPosition.setY(cameraPosition.y() - 5);
    }
    else if (event->key() == Qt::Key_H)
    {
        cameraPosition.setZ(cameraPosition.z() + 5);
        //cameraPosition.setY(cameraPosition.y() - 5);
        //cameraPosition.setZ(cameraPosition.z() - 5);
        //cameraPosition.setY(cameraPosition.y() - 5);
    }
    else if (event->key() == Qt::Key_Space)
    {
         on_GoButton_clicked();
        //cameraPosition.setY(cameraPosition.y() - 5);
        //cameraPosition.setZ(cameraPosition.z() - 5);
        //cameraPosition.setY(cameraPosition.y() - 5);
    }
    QString str0 = QString::number(CameraAngleX);
    QString str1 = QString::number(CameraAngleY);
    QString str2 = QString::number(CameraAngleZ);
    QString str3 = QString::number(cameraPosition.x());
    QString str4 = QString::number(cameraPosition.y());
    QString str5 = QString::number(cameraPosition.z());

    ui->AngleInfo->setText("Angle X: " + str0 + "\n" + "Angle Y: " + str1 + "\n" + "Angle Z: " + str2 + "\n" +
                           "camera Position is " + str3 + "," + str4 + "," + str5);
    scene->SetCameraAngleS(CameraAngleX, CameraAngleY, CameraAngleZ);
    render();


}

void MainWindow::render()
{

    scene->clear();
    /*
    Point3D first(-400, 0, 0);
    Point3D second(400, 0, 0);
    scene->drawLine3D(first, second);

    first.changeAll(0, -250, 0);
    second.changeAll(0, 250, 0);
    scene->drawLine3D(first, second);

    first.changeAll(0, 0, 400);
    second.changeAll(0, 0, -50);
    scene->drawLine3D(first, second);
    */
    Point3D point(0, 0, -25);

    scene->drawLaunchPad(point);
    scene->drawCone(cone);
    scene->drawRocket(_rocket, cameraPosition);
    //qDebug() << scene->trianglesOnImage.size();
    //scene->fillObject(cone);

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

void MainWindow::MoveRocket()
{

}
/*
// добавить камеру,
матрицы поворотов и вращений и переносов,
добавить сцену и добавлять объекты в сцену,
рисовать на QImage и потом переносить на QGraphicsView

*/

void MainWindow::on_GoButton_clicked()
{
    QTimer t;
    for (int i = 0; i < 100; i++)
    {
        _rocket.moveRocket();
        render();
        t.start(10000 - i * 5);
        repaint();
    }
}
