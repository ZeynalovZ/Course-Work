#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include "basedrawer.h"
#include "point3d.h"
#include "cone.h"
#include "drawer.h"
#include "rocket.h"
#include "paintingwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void render();
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_Draw_clicked();

    void on_rotate_clicked();

    void MoveRocket();

    void on_GoButton_clicked();

public:
    int CameraAngleX = 0;
    int CameraAngleY = 0;
    int CameraAngleZ = 0;

private:
    Ui::MainWindow *ui;
    rocket _rocket;
    Point3D cameraPosition;
    Point3D cameraVisPosition;
    QPainter *painter;
    PaintWidget *scene;
    //Drawer *drawer;
    Cone cone;
    QColor RocketColor = QColor(Qt::gray);
};

#endif // MAINWINDOW_H
