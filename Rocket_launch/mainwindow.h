#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QPainter"
#include "basedrawer.h"
#include "point3d.h"
#include "cone.h"
#include "drawer.h"
#include "rocket.h"

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

private slots:
    void on_Draw_clicked();

    void on_rotate_clicked();

private:
    Ui::MainWindow *ui;
    Drawer *scene;
    rocket _rocket;
    Point3D cameraPosition;
};

#endif // MAINWINDOW_H
