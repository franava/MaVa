#include <character.h>
#include <QKeyEvent>
#include <QTimer>

Character::Character()
{
}

Character::Character(std::shared_ptr<Animation> a)
{
    animation_ = a ;
    setPixmap(animation_->rotatePixmap()) ;
}

void Character::animate()
{
    connect(&animation_->timer(), &QTimer::timeout, this, &Character::setFrame) ;
}

void Character::setAnimation(std::shared_ptr<Animation> a)
{
    animation_ = a ;
}

void Character::switchAnimationToRandom()
{
    animation_->randomActiveSprite() ;
}

void Character::switchAnimationToNext()
{
    animation_->nextSprite() ;
}

void Character::switchAnimationToSpecific(size_t t)
{
    animation_->setActiveSprite(t) ;
}

void Character::switchAnimationToSpecific(const std::string& s)
{
    animation_->setActiveSprite(s) ;
}

void Character::setFrame()
{
    setPixmap(animation_->rotatePixmap());
}

void Character::rotateFrameFromAnimation()
{
    connect(&animation_->timer(), &QTimer::timeout, this, &Character::setFrame ) ;
}

void Character::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space)
    {
        switchAnimationToNext() ;
    }
}
