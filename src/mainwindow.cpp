#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <animation.h>
#include <character.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    qS_ = new QGraphicsScene(this) ;
    ui_->graphicsView->setScene(qS_) ;

    std::shared_ptr<Animation> a = std::make_shared<Animation>() ;

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

    Sprite death_1("death") ;
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

    Sprite death = ( death_1 + death_2) ;
    death.reset() ;

    Sprite shield_bash("shield_bash") ;
    std::vector<QRect> frames ;
    {
        frames.push_back(QRect(QPoint(1,100), QPoint(32, 131)));
        frames.push_back(QRect(QPoint(34,100), QPoint(65, 131)));
        frames.push_back(QRect(QPoint(67,100), QPoint(98, 131)));
        frames.push_back(QRect(QPoint(100,100), QPoint(131, 131)));
        frames.push_back(QRect(QPoint(133,100), QPoint(164, 131)));
        frames.push_back(QRect(QPoint(166,100), QPoint(197, 131)));
        frames.push_back(QRect(QPoint(199,100), QPoint(230, 131)));
        frames.push_back(QRect(QPoint(232,100), QPoint(263, 131)));
    }

    shield_bash.defineFFASpriteFrames(
        ":/animations/Res/warrior.png",
        frames
        );

    slash_1->rescaleSprite(10) ;
    a->addSprite(slash_1, slash_1->name()) ;
    slash_2->rescaleSprite(10) ;
    a->addSprite(slash_2, slash_2->name()) ;
    death.rescaleSprite(10) ;
    a->addSprite(death, death.name()) ;
    shield_bash.rescaleSprite(10) ;
    a->addSprite(shield_bash, shield_bash.name());
    Sprite walk("walk") ;
    walk.defineSpriteFrameRemovingBg(
        ":/animations/Res/bunny.png",
        QPoint(0,146),
        QPoint(640, 224),
        QPoint(0,0),
        8,
        0);

    walk.rescaleSprite(4);
    a->addSprite(walk, walk.name()) ;

    Sprite walk_2("walk_2") ;
    walk_2.defineSpriteFrameRemovingBg(
        ":/animations/Res/bunny.png",
        QPoint(0,68),
        QPoint(644,146),
        QPoint(0,0),
        8,
        0);
    walk_2.rescaleSprite(4);
    a->addSprite(walk_2, walk_2.name()) ;

    //    a->setActiveSprite(walk.name()) ;
    a->pmi() = qS_->addPixmap(a->getFirstPixmapForInit());

    timer_ = new QTimer(this) ;
    timer_->start(100);
    a->setTimer(timer_);
    c_ = new Character(a) ;

    connect(ui_->actionAnimation, &QAction::triggered, this, &MainWindow::onActionAnimationTriggered) ;
}

void MainWindow::onActionAnimationTriggered()
{
    disconnect(ui_->actionAnimation, &QAction::triggered, this, &MainWindow::onActionAnimationTriggered) ;
    c_->animate() ;
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        c_->switchAnimationToNext() ;
    }
}
