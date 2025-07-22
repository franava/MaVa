#include "animation.h"
#include <QGraphicsPixmapItem>
#include <QTimer>

Animation::Animation() {}

Animation::~Animation() noexcept
{
    delete timer_ ;
}

void Animation::addSprite(Sprite s, std::string d)
{
    sprites_.push_back(std::make_shared<Sprite>(s)) ;
    descriptions_.push_back(d);
}

void Animation::addSprite(std::shared_ptr<Sprite> s, std::string d)
{
    sprites_.push_back(s) ;
    descriptions_.push_back(d);
}

void Animation::setActiveSprite(size_t id)
{
    if(activeSprite_ != nullptr)
    {
        activeSprite_->reset() ;
    }
    activeSprite_ = getSprite(id);
}
void Animation::setActiveSprite(std::string d)
{
    if(activeSprite_ != nullptr)
    {
        activeSprite_->reset() ;
    }
    activeSprite_ = getSprite(d);
}

QPixmap Animation::getFirstPixmapForInit()
{
    return activeSprite_->rotateActive() ;
}

void Animation::rotatePixmap()
{
    pmI_->setPixmap(activeSprite_->rotateActive()) ;
}

void Animation::switchActiveSprite(size_t i)
{
    if(activeSprite_ != nullptr)
        activeSprite_->reset() ;
    activeSprite_ = sprites_[i] ;
}

void Animation::switchActiveSprite(std::string s)
{
    if(activeSprite_ != nullptr)
        activeSprite_->reset() ;
    for(size_t i = 0 ; i < descriptions_.size() ; ++i)
    {
        if(descriptions_[i] == s)
            activeSprite_ = sprites_[i] ;

    }
}

void Animation::randomActiveSprite()
{
    if(activeSprite_ != nullptr)
        activeSprite_->reset() ;

    auto j = rand() % sprites_.size() ;
    activeSprite_ = sprites_[j] ;
}

void Animation::initTimer(size_t msec)
{
    if(timer_ == nullptr)
    {
        timer_ = new QTimer  ;
        timer_->start(msec) ;
    }
    else
    {
        qDebug() << "Timer already set: no initTimer taking place" ;
    }
}

std::shared_ptr<Sprite> Animation::getSprite(std::string d)
{
    for(size_t i = 0 ; i < descriptions_.size() ; ++i)
    {
        if (descriptions_[i] == d)
            return sprites_[i] ;
    }
    auto e = std::exception();
    throw(e) ;
}

std::shared_ptr<Sprite> Animation::getSprite(size_t id)
{
    return sprites_.at(id) ;
}

