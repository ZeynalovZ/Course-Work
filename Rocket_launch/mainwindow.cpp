#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "basedrawer.h"
#include "QDebug"

#define SCALE 10
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
    Point3D center(100, 200, 300);
    qreal radius1 = 10;
    qreal radius2 = 20;
    qreal height = 20;

    cone.createCone(center, radius1, radius2, height, SCALE);
    scene->drawCone(cone);
}


void MainWindow::on_pushButton_2_clicked()
{
    scene->clear();
    cone.Rotatey(20);
    cone.Rotatez(20);
    scene->drawCone(cone);
}
