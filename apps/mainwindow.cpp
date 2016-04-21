#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    //ui->setupUi(this);

    this->setFixedSize (800, 480);

    mainStackWidget = new QStackedWidget(this);
    mainStackWidget->setGeometry(rect());
    mainStackWidget->lower();

    silenceInterface = new SilenceInterface();

    mainStackWidget->addWidget (silenceInterface);
    mainStackWidget->setCurrentWidget (silenceInterface);
}

MainWindow::~MainWindow()
{
    delete ui;
}
