/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
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
    QPushButton *GoButton;
    QLabel *color_label;
    QPushButton *color_button;
    QPushButton *Draw;
    QGroupBox *groupBox;
    QTextEdit *AngleInfo;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QGroupBox *groupBox_2;
    QLineEdit *editX;
    QLabel *label_2;
    QLineEdit *editY;
    QLabel *label;
    QPushButton *rotate;
    QLabel *label_4;
    QLineEdit *editX_2;
    QLabel *label_5;
    QLineEdit *editY_2;
    QPushButton *rotate_2;
    QLineEdit *editZ_2;
    QLabel *label_6;
    QFrame *line;
    QCheckBox *checkBox;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QLabel *label_3;
    QLabel *label_7;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1319, 793);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 10, 871, 761));
        Layuot = new QVBoxLayout(verticalLayoutWidget_2);
        Layuot->setSpacing(6);
        Layuot->setContentsMargins(11, 11, 11, 11);
        Layuot->setObjectName(QStringLiteral("Layuot"));
        Layuot->setContentsMargins(0, 0, 0, 0);
        GoButton = new QPushButton(centralWidget);
        GoButton->setObjectName(QStringLiteral("GoButton"));
        GoButton->setGeometry(QRect(1080, 680, 161, 41));
        color_label = new QLabel(centralWidget);
        color_label->setObjectName(QStringLiteral("color_label"));
        color_label->setGeometry(QRect(902, 334, 41, 40));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(20);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(color_label->sizePolicy().hasHeightForWidth());
        color_label->setSizePolicy(sizePolicy);
        color_label->setMinimumSize(QSize(30, 40));
        color_label->setMaximumSize(QSize(120, 120));
        color_label->setStyleSheet(QStringLiteral(""));
        color_button = new QPushButton(centralWidget);
        color_button->setObjectName(QStringLiteral("color_button"));
        color_button->setGeometry(QRect(960, 340, 191, 41));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(color_button->sizePolicy().hasHeightForWidth());
        color_button->setSizePolicy(sizePolicy1);
        color_button->setMaximumSize(QSize(1000, 16777215));
        QFont font;
        font.setPointSize(12);
        color_button->setFont(font);
        color_button->setCursor(QCursor(Qt::PointingHandCursor));
        color_button->setAutoDefault(false);
        color_button->setFlat(false);
        Draw = new QPushButton(centralWidget);
        Draw->setObjectName(QStringLiteral("Draw"));
        Draw->setGeometry(QRect(900, 680, 141, 41));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(1100, 10, 211, 311));
        AngleInfo = new QTextEdit(groupBox);
        AngleInfo->setObjectName(QStringLiteral("AngleInfo"));
        AngleInfo->setGeometry(QRect(10, 30, 191, 151));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(AngleInfo->sizePolicy().hasHeightForWidth());
        AngleInfo->setSizePolicy(sizePolicy2);
        AngleInfo->setMaximumSize(QSize(16777215, 200));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(20, 220, 51, 51));
        QFont font1;
        font1.setPointSize(20);
        pushButton->setFont(font1);
        pushButton->setAutoRepeat(true);
        pushButton->setAutoExclusive(false);
        pushButton->setAutoRepeatDelay(0);
        pushButton->setAutoRepeatInterval(40);
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(80, 190, 51, 51));
        pushButton_2->setFont(font1);
        pushButton_2->setAutoRepeat(true);
        pushButton_2->setAutoExclusive(false);
        pushButton_2->setAutoRepeatDelay(0);
        pushButton_2->setAutoRepeatInterval(40);
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(140, 220, 51, 51));
        pushButton_3->setFont(font1);
        pushButton_3->setAutoRepeat(true);
        pushButton_3->setAutoRepeatDelay(0);
        pushButton_3->setAutoRepeatInterval(40);
        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(80, 250, 51, 51));
        pushButton_4->setFont(font1);
        pushButton_4->setAutoRepeat(true);
        pushButton_4->setAutoExclusive(false);
        pushButton_4->setAutoRepeatDelay(0);
        pushButton_4->setAutoRepeatInterval(40);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(890, 10, 211, 311));
        editX = new QLineEdit(groupBox_2);
        editX->setObjectName(QStringLiteral("editX"));
        editX->setGeometry(QRect(30, 30, 171, 22));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 60, 21, 21));
        editY = new QLineEdit(groupBox_2);
        editY->setObjectName(QStringLiteral("editY"));
        editY->setGeometry(QRect(30, 60, 171, 22));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 31, 21));
        rotate = new QPushButton(groupBox_2);
        rotate->setObjectName(QStringLiteral("rotate"));
        rotate->setGeometry(QRect(10, 90, 191, 41));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 190, 21, 21));
        editX_2 = new QLineEdit(groupBox_2);
        editX_2->setObjectName(QStringLiteral("editX_2"));
        editX_2->setGeometry(QRect(30, 160, 171, 22));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 160, 31, 21));
        editY_2 = new QLineEdit(groupBox_2);
        editY_2->setObjectName(QStringLiteral("editY_2"));
        editY_2->setGeometry(QRect(30, 190, 171, 22));
        rotate_2 = new QPushButton(groupBox_2);
        rotate_2->setObjectName(QStringLiteral("rotate_2"));
        rotate_2->setGeometry(QRect(10, 250, 191, 41));
        editZ_2 = new QLineEdit(groupBox_2);
        editZ_2->setObjectName(QStringLiteral("editZ_2"));
        editZ_2->setGeometry(QRect(30, 220, 171, 22));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 220, 20, 20));
        line = new QFrame(groupBox_2);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 140, 191, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(900, 390, 191, 31));
        QFont font2;
        font2.setPointSize(14);
        checkBox->setFont(font2);
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(900, 440, 71, 31));
        spinBox->setFont(font2);
        spinBox_2 = new QSpinBox(centralWidget);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(900, 490, 71, 31));
        spinBox_2->setFont(font2);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(980, 440, 321, 31));
        label_3->setFont(font2);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(980, 480, 321, 61));
        label_7->setFont(font2);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        color_button->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        GoButton->setText(QApplication::translate("MainWindow", "\320\222\320\267\320\273\320\265\321\202", nullptr));
        color_label->setText(QString());
        color_button->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\206\320\262\320\265\321\202 \320\270\321\201\321\202\320\276\321\207\320\275\320\270\320\272\320\260", nullptr));
        Draw->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\200\320\270\321\201\320\276\320\262\320\260\321\202\321\214 \321\201\321\206\320\265\320\275\321\203", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\272\320\260\320\274\320\265\321\200\320\276\320\271", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\342\206\220", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "\342\206\221", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "\342\206\222", nullptr));
        pushButton_4->setText(QApplication::translate("MainWindow", "\342\206\223", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \321\200\320\260\320\272\320\265\321\202\320\276\320\271", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Y", nullptr));
        label->setText(QApplication::translate("MainWindow", "X", nullptr));
        rotate->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\262\320\265\321\200\320\275\321\203\321\202\321\214", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Y", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "X", nullptr));
        rotate_2->setText(QApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\274\320\265\321\201\321\202\320\270\321\202\321\214", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Z", nullptr));
        checkBox->setText(QApplication::translate("MainWindow", "\320\264\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\202\320\265\320\275\320\270", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\263\321\200\320\260\320\275\320\265\320\271 \321\200\320\260\320\272\320\265\321\202\321\213", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\263\321\200\320\260\320\275\320\265\320\271 \321\201\321\202\320\260\321\200\321\202\320\276\320\262\320\276\320\271 \n"
"\320\277\320\273\320\276\321\211\320\260\320\264\320\272\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
