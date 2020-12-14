#include "mainwindow.h"
#include "proj_classes.h"	// main templated class
#include "student.h"
#include <string>
#include <QApplication>


DB<Student> myStudentDB;
MainWindow w;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    w.show();

    return a.exec();
}
