#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QHBoxLayout>
#include "aspectwidget.h"
#include "gameboard.h"
#include "previewboard.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    centralWidget->setLayout(mainLayout);
    auto gameLayout=new QHBoxLayout(this);
    AspectWidget *gameBoardWidget = new AspectWidget(gameLayout, 1,this);
    mainLayout->addWidget(gameBoardWidget);
    gameBoardWidget->setStyleSheet("background-color: blue;");
    gameLayout->setSpacing(0);
    PreviewBoard *a = new PreviewBoard(1,gameBoardWidget); //5*3
    gameLayout->addWidget(a,1);

    GameBoard *b = new GameBoard(gameBoardWidget); //10*20
    gameLayout->addWidget(b,2);
    PreviewBoard *c = new PreviewBoard(5,gameBoardWidget);//5*(3*n) n=5
    gameLayout->addWidget(c,1);

    a->setPreviewPiece(b->holdPieceTypePtr());
    c->setPreviewBag(b->nextsPtr());
    connect(b,&GameBoard::enginePieceTypeChanged,a,QOverload<>::of(&QWidget::update));
    connect(b,&GameBoard::enginePieceTypeChanged,c,QOverload<>::of(&QWidget::update));

    a->setStyleSheet("background-color: green;");
    c->setStyleSheet("background-color: green;");
    // a->parentWidget()->layout()->setContentsMargins(20,20,20,20);
    // a->setStyleSheet("background-color: blue;");

}

MainWindow::~MainWindow()
{
    delete ui;
}
