#include <witch.h>
#include <QGraphicsScene>

Witch::Witch(QTimer* qt)
    : Character()
{
    std::shared_ptr<Animation> a = std::make_shared<Animation>() ;

    Sprite attack("attack") ;
    attack.defineSpriteFrames(
         ":/animations/Res/witch.png",
        QPoint(1, 100),
        QPoint(363, 131),
        11,
        1);

    attack.rescaleSprite(10);


    Sprite d1 ;
    d1.defineSpriteFrames(
        ":/animations/Res/witch.png",
        QPoint(1, 298),
        QPoint(494, 329),
        15,
        1) ;

    Sprite d2 ;
    d2.defineSpriteFrames(
        ":/animations/Res/witch.png",
        QPoint(1, 332),
        QPoint(164, 362),
        5,
        1) ;

    Sprite death = (d1 + d2 );
    death.reset() ;
    death.name("death");
    death.rescaleSprite(10);

    a->addSprite(attack, attack.name()) ;
    a->addSprite(death, death.name());
    timer() = qt ;
    setAnimation(a) ;
}
