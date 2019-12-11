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
    timerForRocket = new QTimer();
    timerForRocket->setSingleShot(true);

    timerForFire = new QTimer();
    timerForFire->setSingleShot(true);

    connect(timerForRocket, SIGNAL(timeout()), this, SLOT(MoveRocket()));
    connect(timerForFire, SIGNAL(timeout()), this, SLOT(updateFire()));



    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::yellow);

    ui->color_label->setAutoFillBackground(true);
    ui->color_label->setPalette(Pal);


    // todo

    /*
     *
     *
     */

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // это для точки, представляющей точку
    int CameraVisAngleX = 0;
    int CameraVisAngleY = 0;
    int CameraVisAngleZ = 0;
    if (event->key() == Qt::Key_S)
    {
        CameraAngleX -= 5;
        CameraVisAngleX = -5;
        //cameraPosition.setZ(cameraPosition.z() + 5);
    }
    else if (event->key() == Qt::Key_D)
    {
        CameraAngleY += 5;
        CameraVisAngleX = 5;
        //cameraPosition.setX(cameraPosition.x() + 5);
    }
    else if (event->key() == Qt::Key_A)
    {
        CameraAngleY -= 5;
        CameraVisAngleY = -5;
        //cameraPosition.setX(cameraPosition.x() - 5);
    }
    else if (event->key() == Qt::Key_W)
    {
        CameraAngleX += 5;
        CameraVisAngleY = 5;
        //cameraPosition.setZ(cameraPosition.z() - 5);
    }
    else if (event->key() == Qt::Key_E)
    {
        CameraAngleZ += 5;
        CameraVisAngleZ = 5;
        //cameraPosition.setY(cameraPosition.y() + 5);
    }
    else if (event->key() == Qt::Key_Z)
    {
        CameraAngleZ -= 5;
        CameraVisAngleZ = -5;
        //cameraPosition.setY(cameraPosition.y() - 5);
    }
    else if (event->key() == Qt::Key_Q)
    {
        cameraPosition.setX(cameraPosition.x() + 5);
        cameraVisPosition.setX(cameraVisPosition.x() + 5);
        //cameraPosition.setY(cameraPosition.y() + 5);
        //cameraPosition.setZ(cameraPosition.z() + 5);
        //cameraPosition.setY(cameraPosition.y() - 5);
    }
    else if (event->key() == Qt::Key_C)
    {
        cameraPosition.setX(cameraPosition.x() - 5);
        cameraVisPosition.setX(cameraVisPosition.x() - 5);
        //cameraPosition.setY(cameraPosition.y() - 5);
        //cameraPosition.setZ(cameraPosition.z() - 5);
        //cameraPosition.setY(cameraPosition.y() - 5);
    }
    else if (event->key() == Qt::Key_Y)
    {
        cameraPosition.setZ(cameraPosition.z() - 5);
        cameraVisPosition.setZ(cameraVisPosition.z() - 5);
        //cameraPosition.setY(cameraPosition.y() - 5);
        //cameraPosition.setZ(cameraPosition.z() - 5);
        //cameraPosition.setY(cameraPosition.y() - 5);
    }
    else if (event->key() == Qt::Key_H)
    {
        cameraPosition.setZ(cameraPosition.z() + 5);
        cameraVisPosition.setZ(cameraVisPosition.z() + 5);
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
    //qDebug() << CameraVisAngleX;
    //scene->changeVisCamera(CameraVisAngleX, CameraVisAngleY, CameraVisAngleZ);
    render();


}

void MainWindow::render()
{

    scene->clear();

    //    Point3D cam_pos = scene->_camera.getPosition();
    //    scene->changeCameraPos(cam_pos);
    //    scene->_visibleCamera.setPosition(cam_pos);
    //    first.changeAll(0, 0, 0);
    //    //qDebug() << cam_pos.x() << cam_pos.y() << cam_pos.z() << "hi";
    //    second.changeAll(cam_pos.x(), cam_pos.y(), cam_pos.z());
    //    scene->painter->setPen(QColor(Qt::black));
    //    scene->drawLine3D(first, second);

    //scene->makeFire();

    if (ui->checkBox->isChecked())
    {
        scene->fillShadow = true;
    }
    else
    {
        scene->fillShadow = false;
    }
    Point3D point(0, 0, -25); // launchpad center
    scene->_camera.setPosition(cameraPosition);
    //sqDebug() << scene->_visibleCamera.x() << scene->_visibleCamera.y() << scene->_visibleCamera.z() << "dots";
    scene->ZBuffer.fillbuffer();
    scene->ZBufferShadows.fillbuffer();


    //scene->drawCone(cone);
    //scene->drawCone(cone1);

    // TODO: rotate firepoint
    //scene->rotateCamera(scene->firePoint);


    scene->drawRocket(_rocket);
    //scene->drawRocket(_rocket2);
    scene->drawLaunchPad(point, edgesCountOfLP);



    //scene->fillShadow = false;
    //scene->drawRocket(_rocket2);

    //scene->drawCone(LightCone);

    //scene->drawCone(LightCone);

    Point3D first(0, 0, 0);
    Point3D second(400, 0, 0);
    scene->painter->setPen(QColor(Qt::red));
    scene->drawLine3D(first, second);

    first.changeAll(0, 0, 0);
    second.changeAll(0, 250, 0);
    scene->painter->setPen(QColor(Qt::blue));
    scene->drawLine3D(first, second);

    first.changeAll(0, 0, 0);
    second.changeAll(0, 0, 400);
    scene->painter->setPen(QColor(Qt::yellow));
    scene->drawLine3D(first, second);

    //    Point3D p1(427, 357, 0);
    //    Point3D p2(423, 374, 0);
    //    Point3D p3(427, 357, 0);

    //    scene->fillObject(p1, p2, p3);
    //qDebug() << scene->trianglesOnImage.size();
    //scene->fillObject(cone);

}

void MainWindow::on_Draw_clicked()
{
    scene->clear();
    edgesCountOfRocket = ui->spinBox->value();
    edgesCountOfLP = ui->spinBox_2->value();
    qDebug() << edgesCountOfRocket << edgesCountOfLP;
    // Создадим ракету передав в нее центр основания ракеты и ее масштаб
    Point3D rocketCenter(0, 0, 0);
    _rocket.createRocket(rocketCenter, SCALE, edgesCountOfRocket);
    rocketCenter.changeAll(-100, 0, 0);
    _rocket2.createRocket(rocketCenter, SCALE, edgesCountOfRocket);
    Point3D coneCenter(150, 150, 50);
    //Отдельный цилиндр рядом с ракетой
    QColor treeColor;
    treeColor.setRed(139);
    treeColor.setGreen(69);
    treeColor.setBlue(19);
    cone.createCone(coneCenter, 30, 30, 100, 10, treeColor);
    coneCenter.changeAll(-150, 150, 150);
    cone1.createCone(coneCenter, 50, 50, 70, 10, QColor(Qt::darkGreen));

    coneCenter.changeAll(0, 1000, 800);
    LightCone.createCone(coneCenter, 50, 50, 70, 10, QColor(Qt::white));

    cameraPosition.setX(0);
    cameraPosition.setY(0);
    cameraPosition.setZ(1000);
    cameraVisPosition.changeAll(0, 0, 1000);
    render();
}

void MainWindow::on_rotate_clicked()
{

    bool ok1 = true, ok2;

    QString x = ui->editX->text();
    int angleX = x.toDouble(&ok1);
    QString y = ui->editY->text();
    int angleY = y.toDouble(&ok2);
    if (ok1 && ok2)
    {
        _rocket.rotateX(angleX);
        _rocket.rotateY(angleY);

        render();
    }

}

void MainWindow::MoveRocket()
{
    //qDebug() << "moving ...";
    //thread tr(_rocket.moveRocket());
    _rocket.moveRocket();
    _rocket2.moveRocket();
    //    std::thread tr1(&rocket::moveRocket, std::ref(_rocket));
    //    std::thread tr2(&MainWindow::render, this);
    //    std::thread tr3(&PaintWidget::makeFire, std::ref(scene));
    render();
    scene->makeFire();
    scene->firePoint.setY(scene->firePoint.y() - 1);
    //scene->PerspectiveProjection(scene->firePoint);

    //    tr1.join();
    //    tr2.join();
    //    tr3.join();
    if (!timerForRocket->isActive())
    {
        if (timer > 1)
            timer--;
        timerForRocket->start(timer);
    }


}

void MainWindow::updateFire()
{
    //    scene->makeFire();
    //    if (!timerForFire->isActive())
    //    {
    //        timerForFire->start(timer);
    //    }
}
/*
// добавить камеру,
матрицы поворотов и вращений и переносов,
добавить сцену и добавлять объекты в сцену,
рисовать на QImage и потом переносить на QGraphicsView

*/



void MainWindow::on_GoButton_clicked()
{

    timerForRocket->start(timer);

    timerForFire->start(timer);
    //render();
}

void MainWindow::on_color_button_clicked()
{
    scene->lightColor = QColorDialog::getColor(scene->lightColor, this);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, scene->lightColor);
    ui->color_label->setAutoFillBackground(true);
    ui->color_label->setPalette(Pal);
    ui->color_label->show();
    render();
}

void MainWindow::on_pushButton_2_clicked()
{
    CameraAngleX += 5;
    scene->SetCameraAngleS(CameraAngleX, CameraAngleY, CameraAngleZ);
    render();
}

void MainWindow::on_pushButton_3_clicked()
{
    CameraAngleY += 5;
    scene->SetCameraAngleS(CameraAngleX, CameraAngleY, CameraAngleZ);
    render();
}

void MainWindow::on_pushButton_clicked()
{
    CameraAngleY -= 5;
    scene->SetCameraAngleS(CameraAngleX, CameraAngleY, CameraAngleZ);
    render();
}

void MainWindow::on_pushButton_4_clicked()
{
    CameraAngleX -= 5;
    scene->SetCameraAngleS(CameraAngleX, CameraAngleY, CameraAngleZ);
    render();
}

void MainWindow::on_LightButton_clicked()
{
    bool ok1 = true, ok2 = true, ok3 = true;

    QString x = ui->editX_3->text();
    int X = x.toDouble(&ok1);
    QString y = ui->editY_3->text();
    int Y = y.toDouble(&ok2);
    QString z = ui->editZ_3->text();
    int Z = z.toDouble(&ok3);
    if (ok1 && ok2 && ok3)
    {
        Point3D P(X, Y, Z);
        scene->lightSource.setPosition(P);
        scene->findLightAngles(P);
        render();
    }
    else
    {
        qDebug() << "light input is not right";
    }
}
