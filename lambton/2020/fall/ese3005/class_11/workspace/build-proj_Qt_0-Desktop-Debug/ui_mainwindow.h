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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *textConsole;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *addButton;
    QPushButton *delButton;
    QPushButton *displayButton;
    QTextBrowser *textBrowser;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menubar;
    QMenu *menuTemplated_Class_Project;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        textConsole = new QTextEdit(centralwidget);
        textConsole->setObjectName(QString::fromUtf8("textConsole"));
        textConsole->setGeometry(QRect(20, 220, 421, 331));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(170, 100, 98, 89));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        addButton = new QPushButton(layoutWidget);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        verticalLayout->addWidget(addButton);

        delButton = new QPushButton(layoutWidget);
        delButton->setObjectName(QString::fromUtf8("delButton"));

        verticalLayout->addWidget(delButton);

        displayButton = new QPushButton(layoutWidget);
        displayButton->setObjectName(QString::fromUtf8("displayButton"));

        verticalLayout->addWidget(displayButton);

        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(460, 40, 311, 501));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(460, 20, 131, 17));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 200, 151, 17));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuTemplated_Class_Project = new QMenu(menubar);
        menuTemplated_Class_Project->setObjectName(QString::fromUtf8("menuTemplated_Class_Project"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuTemplated_Class_Project->menuAction());

        retranslateUi(MainWindow);
        QObject::connect(delButton, SIGNAL(clicked()), textConsole, SLOT(update()));
        QObject::connect(displayButton, SIGNAL(clicked()), textBrowser, SLOT(update()));
        QObject::connect(addButton, SIGNAL(clicked()), textConsole, SLOT(update()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        addButton->setText(QApplication::translate("MainWindow", "Add Element", nullptr));
        delButton->setText(QApplication::translate("MainWindow", "Del Element", nullptr));
        displayButton->setText(QApplication::translate("MainWindow", "Display DB", nullptr));
        label->setText(QApplication::translate("MainWindow", "Display Console", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Text Entry Console", nullptr));
        menuTemplated_Class_Project->setTitle(QApplication::translate("MainWindow", "Templated_Class_Project", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
