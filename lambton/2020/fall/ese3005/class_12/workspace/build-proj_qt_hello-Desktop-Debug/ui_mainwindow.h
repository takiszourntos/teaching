/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *myEMBTButton0;
    QRadioButton *radioButton0;
    QLabel *label0;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        myEMBTButton0 = new QPushButton(centralwidget);
        myEMBTButton0->setObjectName(QString::fromUtf8("myEMBTButton0"));
        myEMBTButton0->setGeometry(QRect(280, 200, 151, 25));
        radioButton0 = new QRadioButton(centralwidget);
        radioButton0->setObjectName(QString::fromUtf8("radioButton0"));
        radioButton0->setGeometry(QRect(290, 250, 112, 23));
        label0 = new QLabel(centralwidget);
        label0->setObjectName(QString::fromUtf8("label0"));
        label0->setGeometry(QRect(490, 200, 111, 17));
        label0->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(myEMBTButton0, SIGNAL(clicked()), label0, SLOT(update()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        myEMBTButton0->setText(QApplication::translate("MainWindow", "myEMBTButton0", nullptr));
        radioButton0->setText(QApplication::translate("MainWindow", "Don't Select!", nullptr));
        label0->setText(QApplication::translate("MainWindow", "Goodbye?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
