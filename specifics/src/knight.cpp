#include <knight.h>
#include <QGraphicsScene>
#include <utility.h>

Knight::Knight(QTimer* qt)
    : Character()
{
    std::shared_ptr<Animation> a = std::make_shared<Animation>() ;
    QString knightResource = ":/animations/Res/warrior.png" ;
    std::vector<Sprite> sprites;

    auto slash_1_r = Sprite("slash_1_r") ;
    slash_1_r.defineSpriteFrames(
        knightResource,
        QPoint(1,133),
        QPoint(296,164),
        9,
        1);
    slash_1_r.rescaleSprite(10) ;
    sprites.push_back(slash_1_r);

    auto slash_2_r = std::make_shared<Sprite>("slash_2_r") ;
    slash_2_r->defineSpriteFrames(
        knightResource,
        QPoint(1,166),
        QPoint(296,197),
        9,
        1);
    slash_2_r->rescaleSprite(10) ;
    sprites.push_back(*slash_2_r);

    auto slash_3_r = std::make_shared<Sprite>("slash_3_r") ;
    slash_3_r->defineSpriteFrames(
        knightResource,
        QPoint(1,199),
        QPoint(297,230),
        9,
        1);
    slash_3_r->rescaleSprite(10) ;
    sprites.push_back(*slash_3_r);

    auto stance_1_r = std::make_shared<Sprite>("stance_1_r") ;
    stance_1_r->defineSpriteFrames(
        knightResource,
        QPoint(1,232),
        QPoint(297,263),
        9,
        1);
    stance_1_r->rescaleSprite(10) ;
    sprites.push_back(*stance_1_r);

    auto stance_2_r = std::make_shared<Sprite>("stance_2_r") ;
    stance_2_r->defineSpriteFrames(
        knightResource,
        QPoint(1,265),
        QPoint(330,296),
        10,
        1);
    stance_2_r->rescaleSprite(10) ;
    sprites.push_back(*stance_2_r);

    Sprite death_1("death_1") ;
    death_1.defineSpriteFrames(
        knightResource,
        QPoint(1,298),
        QPoint(494,329),
        15,
        1);

    Sprite death_2("death_2") ;
    death_2.defineSpriteFrames(
        knightResource,
        QPoint(1,331),
        QPoint(494,362),
        15,
        1);

    Sprite death_r = ( death_1 + death_2) ;
    death_r.name("death_r");
    death_r.rescaleSprite(10) ;
    death_r.reset() ;
    sprites.push_back(death_r);

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
        knightResource,
        frames
        );
    shield_bash_r.rescaleSprite(10) ;
    sprites.push_back(shield_bash_r);

    Sprite stand_r("stand_r");
    stand_r.defineSpriteFrames(
        knightResource,
        QPoint(1,1),
        QPoint(165, 32),
        5,
        1);
    stand_r.rescaleSprite(10);
    sprites.push_back(stand_r);

    Sprite block_r("block_r");
    block_r.defineSpriteFrames(
        knightResource,
        QPoint(1,34),
        QPoint(66, 65),
        2,
        1);
    block_r.rescaleSprite(10);
    sprites.push_back(block_r);

    Sprite stone_r("stone_r");
    stone_r.defineSpriteFrames(
        knightResource,
        QPoint(34,67),
        QPoint(65, 98),
        1,
        1);
    stone_r.rescaleSprite(10);
    sprites.push_back(stone_r);

    Sprite freeze_r("freeze_r");
    freeze_r.defineSpriteFrames(
        knightResource,
        QPoint(1,67),
        QPoint(32, 98),
        1,
        1);
    freeze_r.rescaleSprite(10);
    sprites.push_back(freeze_r);
    utility::ingestSprites(*a, sprites) ;

    timer() = qt ;
    setAnimation(a) ;
}
