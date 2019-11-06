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
    //scene = new Drawer(this);

//    drawer = new Drawer();
//    scene = new QPixmap(X_SIZE, Y_SIZE);
//    scene->fill(QColor(Qt::white));
//    painter = new QPainter(this);
//    painter->setPen(QColor(Qt::black));

//    ui->PaintingScene->setPixmap(*scene);
    scene = new PaintWidget(this);

    //    QPixmap scene1(951, 561);
    //    scene1.fill(QColor(Qt::white));
    //    QPainter painter(&scene1);
    //    painter.setPen(Qt::red);
    //    painter.drawLine(100, 100, 300, 300);
    //    scene->addPixmap(scene1);

    //ui->PaintingScene->setScene(scene);
    //ui->PaintingScene->render(painter);
    //ui->PaintingScene->setBackgroundBrush(img);
    //ui->PaintingScene->setCacheMode(QGraphicsView::CacheBackground);
    // Создадим ракету передав в нее центр основания ракеты и ее масштаб
    Point3D rocketCenter(0, 0, 0);
    _rocket.createRocket(rocketCenter, SCALE);
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

void MainWindow::MoveRocket()
{

}
/*
// добавить камеру,
матрицы поворотов и вращений и переносов,
добавить сцену и добавлять объекты в сцену,
рисовать на QImage и потом переносить на QGraphicsView

*/

void MainWindow::on_pushButton_clicked()
{
    QTimer t;
    for (int i = 0; i < 1000; i++)
    {
        _rocket.moveRocket();
        render();
        t.start(1000000);
        repaint();
    }
}
