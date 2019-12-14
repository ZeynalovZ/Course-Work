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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
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
    QPushButton *moveButton;
    QLineEdit *editZ_2;
    QLabel *label_6;
    QFrame *line;
    QCheckBox *checkBox;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QLabel *label_3;
    QLabel *label_7;
    QPushButton *LightButton;
    QLabel *label_8;
    QLineEdit *editZ_3;
    QLabel *label_9;
    QLineEdit *editX_3;
    QLineEdit *editY_3;
    QLabel *label_10;
    QPushButton *ClearButton;
    QLabel *label_11;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1319, 793);
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
        GoButton = new QPushButton(centralWidget);
        GoButton->setObjectName(QString::fromUtf8("GoButton"));
        GoButton->setGeometry(QRect(1050, 720, 111, 51));
        GoButton->setStyleSheet(QString::fromUtf8(""));
        color_label = new QLabel(centralWidget);
        color_label->setObjectName(QString::fromUtf8("color_label"));
        color_label->setGeometry(QRect(900, 510, 41, 40));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(20);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(color_label->sizePolicy().hasHeightForWidth());
        color_label->setSizePolicy(sizePolicy);
        color_label->setMinimumSize(QSize(30, 40));
        color_label->setMaximumSize(QSize(120, 120));
        color_label->setStyleSheet(QString::fromUtf8(""));
        color_button = new QPushButton(centralWidget);
        color_button->setObjectName(QString::fromUtf8("color_button"));
        color_button->setGeometry(QRect(960, 510, 241, 41));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(color_button->sizePolicy().hasHeightForWidth());
        color_button->setSizePolicy(sizePolicy1);
        color_button->setMaximumSize(QSize(1000, 16777215));
        QFont font;
        font.setPointSize(10);
        color_button->setFont(font);
        color_button->setCursor(QCursor(Qt::PointingHandCursor));
        color_button->setAutoDefault(false);
        color_button->setFlat(false);
        Draw = new QPushButton(centralWidget);
        Draw->setObjectName(QString::fromUtf8("Draw"));
        Draw->setGeometry(QRect(900, 720, 141, 51));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 255, 127, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(127, 255, 191, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(63, 255, 159, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(0, 127, 63, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(0, 170, 84, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush2);
        QBrush brush7(QColor(255, 255, 220, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        QBrush brush8(QColor(0, 0, 0, 128));
        brush8.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush8);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush8);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush8);
#endif
        Draw->setPalette(palette);
        Draw->setStyleSheet(QString::fromUtf8(""));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(1100, 10, 211, 311));
        groupBox->setFont(font);
        AngleInfo = new QTextEdit(groupBox);
        AngleInfo->setObjectName(QString::fromUtf8("AngleInfo"));
        AngleInfo->setGeometry(QRect(10, 30, 191, 151));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(AngleInfo->sizePolicy().hasHeightForWidth());
        AngleInfo->setSizePolicy(sizePolicy2);
        AngleInfo->setMaximumSize(QSize(16777215, 200));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 220, 51, 51));
        QFont font1;
        font1.setPointSize(20);
        pushButton->setFont(font1);
        pushButton->setAutoRepeat(true);
        pushButton->setAutoExclusive(false);
        pushButton->setAutoRepeatDelay(0);
        pushButton->setAutoRepeatInterval(40);
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(80, 190, 51, 51));
        pushButton_2->setFont(font1);
        pushButton_2->setAutoRepeat(true);
        pushButton_2->setAutoExclusive(false);
        pushButton_2->setAutoRepeatDelay(0);
        pushButton_2->setAutoRepeatInterval(40);
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(140, 220, 51, 51));
        pushButton_3->setFont(font1);
        pushButton_3->setAutoRepeat(true);
        pushButton_3->setAutoRepeatDelay(0);
        pushButton_3->setAutoRepeatInterval(40);
        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(80, 250, 51, 51));
        pushButton_4->setFont(font1);
        pushButton_4->setAutoRepeat(true);
        pushButton_4->setAutoExclusive(false);
        pushButton_4->setAutoRepeatDelay(0);
        pushButton_4->setAutoRepeatInterval(40);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(890, 10, 211, 311));
        editX = new QLineEdit(groupBox_2);
        editX->setObjectName(QString::fromUtf8("editX"));
        editX->setGeometry(QRect(30, 30, 171, 22));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 60, 21, 21));
        editY = new QLineEdit(groupBox_2);
        editY->setObjectName(QString::fromUtf8("editY"));
        editY->setGeometry(QRect(30, 60, 171, 22));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 30, 31, 21));
        rotate = new QPushButton(groupBox_2);
        rotate->setObjectName(QString::fromUtf8("rotate"));
        rotate->setGeometry(QRect(10, 90, 191, 41));
        rotate->setFont(font);
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 190, 21, 21));
        editX_2 = new QLineEdit(groupBox_2);
        editX_2->setObjectName(QString::fromUtf8("editX_2"));
        editX_2->setGeometry(QRect(30, 160, 171, 22));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 160, 31, 21));
        editY_2 = new QLineEdit(groupBox_2);
        editY_2->setObjectName(QString::fromUtf8("editY_2"));
        editY_2->setGeometry(QRect(30, 190, 171, 22));
        moveButton = new QPushButton(groupBox_2);
        moveButton->setObjectName(QString::fromUtf8("moveButton"));
        moveButton->setGeometry(QRect(10, 250, 191, 41));
        moveButton->setFont(font);
        editZ_2 = new QLineEdit(groupBox_2);
        editZ_2->setObjectName(QString::fromUtf8("editZ_2"));
        editZ_2->setGeometry(QRect(30, 220, 171, 22));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 220, 20, 20));
        line = new QFrame(groupBox_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(10, 140, 191, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(900, 560, 271, 31));
        checkBox->setFont(font);
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(900, 600, 71, 31));
        spinBox->setFont(font);
        spinBox->setMinimum(3);
        spinBox->setMaximum(50);
        spinBox->setValue(40);
        spinBox_2 = new QSpinBox(centralWidget);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setGeometry(QRect(900, 650, 71, 31));
        spinBox_2->setFont(font);
        spinBox_2->setMinimum(3);
        spinBox_2->setValue(10);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(980, 600, 321, 31));
        label_3->setFont(font);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(980, 640, 321, 61));
        label_7->setFont(font);
        LightButton = new QPushButton(centralWidget);
        LightButton->setObjectName(QString::fromUtf8("LightButton"));
        LightButton->setGeometry(QRect(900, 450, 191, 41));
        LightButton->setFont(font);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(900, 360, 31, 21));
        editZ_3 = new QLineEdit(centralWidget);
        editZ_3->setObjectName(QString::fromUtf8("editZ_3"));
        editZ_3->setGeometry(QRect(920, 420, 171, 22));
        editZ_3->setFont(font);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(900, 420, 20, 20));
        editX_3 = new QLineEdit(centralWidget);
        editX_3->setObjectName(QString::fromUtf8("editX_3"));
        editX_3->setGeometry(QRect(920, 360, 171, 22));
        editX_3->setFont(font);
        editY_3 = new QLineEdit(centralWidget);
        editY_3->setObjectName(QString::fromUtf8("editY_3"));
        editY_3->setGeometry(QRect(920, 390, 171, 22));
        editY_3->setFont(font);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(900, 390, 21, 21));
        ClearButton = new QPushButton(centralWidget);
        ClearButton->setObjectName(QString::fromUtf8("ClearButton"));
        ClearButton->setGeometry(QRect(1170, 720, 141, 51));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush2);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush8);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush8);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush8);
#endif
        ClearButton->setPalette(palette1);
        ClearButton->setStyleSheet(QString::fromUtf8(""));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(900, 330, 191, 19));
        label_11->setFont(font);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        color_button->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        GoButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\267\320\273\320\265\321\202", nullptr));
        color_label->setText(QString());
        color_button->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\206\320\262\320\265\321\202 \320\270\321\201\321\202\320\276\321\207\320\275\320\270\320\272\320\260", nullptr));
        Draw->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\200\320\270\321\201\320\276\320\262\320\260\321\202\321\214 \321\201\321\206\320\265\320\275\321\203", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\272\320\260\320\274\320\265\321\200\320\276\320\271", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\342\206\220", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\342\206\221", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\342\206\222", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\342\206\223", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \321\200\320\260\320\272\320\265\321\202\320\276\320\271", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        rotate->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\262\320\265\321\200\320\275\321\203\321\202\321\214", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        moveButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\274\320\265\321\201\321\202\320\270\321\202\321\214", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "\320\264\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\202\320\265\320\275\320\270", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\263\321\200\320\260\320\275\320\265\320\271 \321\200\320\260\320\272\320\265\321\202\321\213", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\263\321\200\320\260\320\275\320\265\320\271 \321\201\321\202\320\260\321\200\321\202\320\276\320\262\320\276\320\271 \n"
"\320\277\320\273\320\276\321\211\320\260\320\264\320\272\320\270", nullptr));
        LightButton->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\277\320\276\320\267\320\270\321\206\320\270\321\216", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        editZ_3->setPlaceholderText(QCoreApplication::translate("MainWindow", "1000", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        editX_3->setPlaceholderText(QCoreApplication::translate("MainWindow", "0", nullptr));
        editY_3->setPlaceholderText(QCoreApplication::translate("MainWindow", "1000", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        ClearButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \321\201\321\206\320\265\320\275\321\203", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\267\320\270\321\206\320\270\321\217 \320\270\321\201\321\202\320\276\321\207\320\275\320\270\320\272\320\260 \321\201\320\262\320\265\321\202\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
