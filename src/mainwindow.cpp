#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <animation.h>
#include <character.h>
#include <knight.h>
#include <witch.h>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    qS_ = new QGraphicsScene(this) ;
    ui_->graphicsView->setScene(qS_) ;
    timer_ = new QTimer(this) ;
    timer_->start(100);
    
    connect(ui_->actionKnightAnimation, &QAction::triggered, this, &MainWindow::onActionAnimationKnightTriggered) ;
    connect(ui_->actionWitchAnimation, &QAction::triggered, this, &MainWindow::onActionAnimationWitchTriggered) ;
}

void MainWindow::onActionAnimationKnightTriggered()
{
    disconnect(ui_->actionKnightAnimation, &QAction::triggered, this, &MainWindow::onActionAnimationKnightTriggered) ;
    disconnect(ui_->actionWitchAnimation, &QAction::triggered, this, &MainWindow::onActionAnimationWitchTriggered) ;

    k_ = new Knight(timer_) ;
    qS_->addItem(k_);
    k_->setFlag(QGraphicsItem::ItemIsFocusable);
    k_->setFocus();
    k_->animate() ;
}

void MainWindow::onActionAnimationWitchTriggered()
{
    disconnect(ui_->actionKnightAnimation, &QAction::triggered, this, &MainWindow::onActionAnimationKnightTriggered) ;
    disconnect(ui_->actionWitchAnimation, &QAction::triggered, this, &MainWindow::onActionAnimationWitchTriggered) ;

    k_ = new Witch(timer_) ;
    qS_->addItem(k_);
    k_->setFlag(QGraphicsItem::ItemIsFocusable);
    k_->setFocus();
    k_->animate() ;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space)
    {
        k_->switchAnimationToNext() ;
    }
}

MainWindow::~MainWindow()
{
    delete ui_;
}

