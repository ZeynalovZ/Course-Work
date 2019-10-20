#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "basedrawer.h"
#include "QDebug"

#define SCALE 2
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создание и начальная инициализация объектов
    scene = new Drawer();
    ui->PaintingScene->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Point3D center(100, 200, 1010);
    qreal radius1 = 2;
    qreal radius2 = 30;
    qreal height = 30;

    cone.createCone(center, radius1, radius2, height, SCALE);
    scene->drawCone(cone);

    center.setX(100);
    center.setY(200);
    center.setZ(880);
    radius1 = 30;
    radius2 = 30;
    height = 100;

    cone.createCone(center, radius1, radius2, height, SCALE);
    scene->drawCone(cone);

    center.setX(100);
    center.setY(200);
    center.setZ(760);
    radius1 = 30;
    radius2 = 40;
    height = 20;

    cone.createCone(center, radius1, radius2, height, SCALE);
    scene->drawCone(cone);

    center.setX(100);
    center.setY(200);
    center.setZ(590);
    radius1 = 40;
    radius2 = 40;
    height = 150;

    cone.createCone(center, radius1, radius2, height, SCALE);
    scene->drawCone(cone);

    center.setX(100);
    center.setY(200);
    center.setZ(420);
    radius1 = 40;
    radius2 = 30;
    height = 20;

    cone.createCone(center, radius1, radius2, height, SCALE);
    scene->drawCone(cone);

    center.setX(100);
    center.setY(200);
    center.setZ(370);
    radius1 = 30;
    radius2 = 40;
    height = 30;

    cone.createCone(center, radius1, radius2, height, SCALE);
    scene->drawCone(cone);
}


void MainWindow::on_pushButton_2_clicked()
{
    scene->clear();
    scene->drawCone(cone);
}
