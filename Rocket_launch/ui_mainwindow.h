/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *Layuot;
    QSplitter *splitter;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *control;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_3;
    QLineEdit *editZ;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label;
    QLineEdit *editX;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_2;
    QLineEdit *editY;
    QPushButton *rotate;
    QPushButton *Draw;
    QHBoxLayout *horizontalLayout_13;
    QTextEdit *AngleInfo;
    QPushButton *GoButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1153, 794);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 10, 871, 761));
        Layuot = new QVBoxLayout(verticalLayoutWidget_2);
        Layuot->setSpacing(6);
        Layuot->setContentsMargins(11, 11, 11, 11);
        Layuot->setObjectName(QString::fromUtf8("Layuot"));
        Layuot->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(890, 10, 251, 721));
        splitter->setOrientation(Qt::Horizontal);
        verticalLayoutWidget = new QWidget(splitter);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        control = new QVBoxLayout(verticalLayoutWidget);
        control->setSpacing(6);
        control->setContentsMargins(11, 11, 11, 11);
        control->setObjectName(QString::fromUtf8("control"));
        control->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_15->addWidget(label_3);

        editZ = new QLineEdit(verticalLayoutWidget);
        editZ->setObjectName(QString::fromUtf8("editZ"));

        horizontalLayout_15->addWidget(editZ);


        control->addLayout(horizontalLayout_15);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_14->addWidget(label);

        editX = new QLineEdit(verticalLayoutWidget);
        editX->setObjectName(QString::fromUtf8("editX"));

        horizontalLayout_14->addWidget(editX);


        control->addLayout(horizontalLayout_14);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_20->addWidget(label_2);

        editY = new QLineEdit(verticalLayoutWidget);
        editY->setObjectName(QString::fromUtf8("editY"));

        horizontalLayout_20->addWidget(editY);


        control->addLayout(horizontalLayout_20);

        rotate = new QPushButton(verticalLayoutWidget);
        rotate->setObjectName(QString::fromUtf8("rotate"));

        control->addWidget(rotate);

        Draw = new QPushButton(verticalLayoutWidget);
        Draw->setObjectName(QString::fromUtf8("Draw"));

        control->addWidget(Draw);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));

        control->addLayout(horizontalLayout_13);

        AngleInfo = new QTextEdit(verticalLayoutWidget);
        AngleInfo->setObjectName(QString::fromUtf8("AngleInfo"));

        control->addWidget(AngleInfo);

        GoButton = new QPushButton(verticalLayoutWidget);
        GoButton->setObjectName(QString::fromUtf8("GoButton"));

        control->addWidget(GoButton);

        splitter->addWidget(verticalLayoutWidget);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        rotate->setText(QCoreApplication::translate("MainWindow", "change POS", nullptr));
        Draw->setText(QCoreApplication::translate("MainWindow", "Draw", nullptr));
        GoButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\273\320\265\321\202\320\265\320\273\320\270!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
