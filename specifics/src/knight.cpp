#include <knight.h>
#include <QGraphicsScene>
#include <utility.h>

Knight::Knight(QTimer* qt)
    : Character()
{
    std::shared_ptr<Animation> a = std::make_shared<Animation>() ;

    auto slash_1_r = std::make_shared<Sprite>("slash_1_r") ;
    slash_1_r->defineSpriteFrames(
        ":/animations/Res/warrior.png",
        QPoint(1,133),
        QPoint(296,164),
        9,
        1);
    slash_1_r->rescaleSprite(10) ;

    auto slash_2_r = std::make_shared<Sprite>("slash_2_r") ;
    slash_2_r->defineSpriteFrames(
        ":/animations/Res/warrior.png",
        QPoint(1,166),
        QPoint(296,197),
        9,
        1);
    slash_2_r->rescaleSprite(10) ;

    auto slash_3_r = std::make_shared<Sprite>("slash_3_r") ;
    slash_3_r->defineSpriteFrames(
        ":/animations/Res/warrior.png",
        QPoint(1,199),
        QPoint(297,230),
        9,
        1);
    slash_3_r->rescaleSprite(10) ;

    auto stance_1_r = std::make_shared<Sprite>("stance_1_r") ;
    stance_1_r->defineSpriteFrames(
        ":/animations/Res/warrior.png",
        QPoint(1,232),
        QPoint(297,263),
        9,
        1);
    stance_1_r->rescaleSprite(10) ;

    auto stance_2_r = std::make_shared<Sprite>("stance_2_r") ;
    stance_2_r->defineSpriteFrames(
        ":/animations/Res/warrior.png",
        QPoint(1,265),
        QPoint(330,296),
        10,
        1);
    stance_2_r->rescaleSprite(10) ;

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

    Sprite death_r = ( death_1 + death_2) ;
    death_r.name("death_r");
    death_r.rescaleSprite(10) ;
    death_r.reset() ;

    Sprite shield_bash_r("shield_bash_r") ;
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

    shield_bash_r.defineFFASpriteFrames(
        ":/animations/Res/warrior.png",
        frames
        );
    shield_bash_r.rescaleSprite(10) ;

    Sprite stand_r("stand_r");
    stand_r.defineSpriteFrames(
        ":/animations/Res/warrior.png",
        QPoint(1,1),
        QPoint(165, 32),
        5,
        1);
    stand_r.rescaleSprite(10);

    Sprite block_r("block_r");
    block_r.defineSpriteFrames(
        ":/animations/Res/warrior.png",
        QPoint(1,34),
        QPoint(66, 65),
        2,
        1);
    block_r.rescaleSprite(10);

    Sprite stone_r("stone_r");
    stone_r.defineSpriteFrames(
        ":/animations/Res/warrior.png",
        QPoint(34,67),
        QPoint(65, 98),
        1,
        1);
    stone_r.rescaleSprite(10);

    Sprite freeze_r("freeze_r");
    freeze_r.defineSpriteFrames(
        ":/animations/Res/warrior.png",
        QPoint(1,67),
        QPoint(32, 98),
        1,
        1);
    freeze_r.rescaleSprite(10);


    a->addSprite(stand_r      , stand_r.name());
    Sprite stand_l("stand_l");
    utility::flipSprite(stand_r, stand_l, true, false);
    a->addSprite(stand_l      , stand_l.name());

    a->addSprite(block_r      , block_r.name());
    Sprite block_l("block_l");
    utility::flipSprite(block_r, block_l, true, false);
    a->addSprite(block_l      , block_l.name());


    a->addSprite(slash_1_r    , slash_1_r->name()) ;
    Sprite slash_1_l("slash_1_l");
    utility::flipSprite(*slash_1_r, slash_1_l, true, false);
    a->addSprite(slash_1_l      , slash_1_l.name());

    a->addSprite(slash_2_r    , slash_2_r->name()) ;
    Sprite slash_2_l("slash_2_l");
    utility::flipSprite(*slash_2_r, slash_2_l, true, false);
    a->addSprite(slash_2_l      , slash_2_l.name());

    a->addSprite(slash_3_r    , slash_3_r->name()) ;
    Sprite slash_3_l("slash_3_l");
    utility::flipSprite(*slash_3_r, slash_3_l, true, false);
    a->addSprite(slash_3_l      , slash_3_l.name());

    a->addSprite(stance_1_r   , stance_1_r->name()) ;
    Sprite stance_1_l("stance_1_l");
    utility::flipSprite(*stance_1_r, stance_1_l, true, false);
    a->addSprite(stance_1_l      , stance_1_l.name());

    a->addSprite(stance_2_r   , stance_2_r->name()) ;
    Sprite stance_2_l("stance_2_l");
    utility::flipSprite(*stance_2_r, stance_2_l, true, false);
    a->addSprite(stance_2_l      , stance_2_l.name());

    a->addSprite(shield_bash_r, shield_bash_r.name()) ;
    Sprite shield_bash_l("stance_2_l");
    utility::flipSprite(shield_bash_r, shield_bash_l, true, false);
    a->addSprite(shield_bash_l      , shield_bash_l.name());


    a->addSprite(freeze_r     , freeze_r.name()) ;
    Sprite freeze_l("freeze_l");
    utility::flipSprite(freeze_r, freeze_l, true, false);
    a->addSprite(freeze_l      , freeze_l.name());

    a->addSprite(stone_r      , stone_r.name()) ;
    Sprite stone_l("freeze_l");
    utility::flipSprite(stone_r, stone_l, true, false);
    a->addSprite(stone_l      , stone_l.name());

    a->addSprite(death_r      , death_r.name()) ;
    Sprite death_l("death_l");
    utility::flipSprite(death_r, death_l, true, false);
    a->addSprite(death_l      , death_l.name());

    a->setTimer(qt) ;
    setAnimation(a) ;
}
