#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <animation.h>
#include <character.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qS_ = new QGraphicsScene(this) ;
    ui->graphicsView->setScene(qS_) ;

    auto animation = std::make_shared<Animation>() ;

    auto slash_1 = std::make_shared<Sprite>("slash_1") ;
    slash_1->defineSpriteFrames(
        ":/animations/Res/warrior.png",
        QPoint(1,133),
        QPoint(296,164),
        9,
        1);

    auto slash_2 = std::make_shared<Sprite>("slash_2") ;
    slash_2->defineSpriteFrames(
        ":/animations/Res/warrior.png",
        QPoint(1,166),
        QPoint(296,197),
        9,
        1);

    Sprite death_1("death_1") ;
    death_1.defineSpriteFrames(
        ":/animations/Res/warrior.png",
        QPoint(1,298),
        QPoint(494,329),
        15,
        1);

    Sprite death_2("death_2") ;
    death_2.defineSpriteFrames(
        ":/animations/Res/warrior.png",
        QPoint(1,331),
        QPoint(494,362),
        15,
        1);

    Sprite s = ( death_1 + death_2) ;
    s.reset() ;
    slash_1->rescaleSprite(10) ;
    animation->addSprite(slash_1, slash_1->name()) ;
    slash_2->rescaleSprite(10) ;
    animation->addSprite(slash_2, slash_2->name()) ;
    s.rescaleSprite(10) ;
    animation->addSprite(s, "death") ;
    animation->setActiveSprite(0);
    animation->pmi() = qS_->addPixmap(animation->getFirstPixmapForInit());

    timer_ = new QTimer(this) ;
    timer_->start(100);
    animation->setTimer(timer_);

    Character c(animation) ;

    connect(ui->actionAnimation, &QAction::triggered, this, &MainWindow::onActionAnimationTriggered) ;
}

void MainWindow::onActionAnimationTriggered()
{
    qDebug() << "onActionAnimationTriggered" ;
    disconnect(ui->actionAnimation, &QAction::triggered, this, &MainWindow::onActionAnimationTriggered) ;
    a_->startAnimation() ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "keyPressEvent" ;
    if (event->key() == Qt::Key_Space)
    {
        a_->randomActiveSprite() ;
    }
}
