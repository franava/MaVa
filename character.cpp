#include "character.h"

Character::Character(std::shared_ptr<Animation> a)
{
    animation_ = a ;
    setPixmap(animation_->getFirstPixmapForInit()) ;
}

void Character::animate()
{
    animation_->rotatePixmap() ;
    setPixmap(animation_->getActivePixmap()) ;
}
