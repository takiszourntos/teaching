#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_myEMBTButton0_clicked()
{
    static bool toggle = false;

    if (!toggle)
    {
        ui->label0->setText("Hello World!"); // changes message to Hello World!
    }
    else
    {
        ui->label0->setText("Goodbye Again!"); // changes message to Goodbye Again!
    }
    toggle=!toggle;

}
