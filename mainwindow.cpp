#include "mainwindow.h"
#include "ui_batawindow.h"

BataWindow::BataWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BataWindow)
{
    ui->setupUi(this);
}

BataWindow::~BataWindow()
{
    delete ui;
}
