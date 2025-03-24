#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QBoxLayout>
#include "aspectwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    centralWidget->setLayout(mainLayout);
    AspectWidget *gameBoardWidget = new AspectWidget(new QHBoxLayout(this), 1,this);
    mainLayout->addWidget(gameBoardWidget);
    gameBoardWidget->setStyleSheet("background-color: blue;");

    QWidget *a = new QWidget(gameBoardWidget);
    gameBoardWidget->layout()->addWidget(a);
    QWidget *b = new QWidget(gameBoardWidget);
    gameBoardWidget->layout()->addWidget(b);
    b->setStyleSheet("background-color: green;");
    // a->parentWidget()->layout()->setContentsMargins(20,20,20,20);
    // a->setStyleSheet("background-color: blue;");

}

MainWindow::~MainWindow()
{
    delete ui;
}
