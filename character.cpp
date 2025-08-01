#include "character.h"

Character::Character(std::shared_ptr<Animation> a)
{
    animation_ = a ;
    setPixmap(animation_->getFirstPixmapForInit()) ;
}

void Character::animate()
{
    animation_->startAnimation() ;
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
