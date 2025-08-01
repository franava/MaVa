#include "animation.h"
#include <QGraphicsPixmapItem>
#include <QTimer>

Animation::Animation() {}

Animation::~Animation() noexcept
{
    delete timer_ ;
}

void Animation::addSprite(
    Sprite s,
    std::string d)
{
    sprites_.push_back(std::make_shared<Sprite>(s)) ;
    if(activeSpriteIndex_ == size_t(-1))
    {
        activeSpriteIndex_ = 0 ;
        activeSprite_ = sprites_.front() ;
    }
    descriptions_.push_back(d) ;
}

void Animation::addSprite(
    std::shared_ptr<Sprite> s,
    std::string d)
{
    sprites_.push_back(s) ;
    if(activeSpriteIndex_ == size_t(-1))
    {
        activeSpriteIndex_ = 0 ;
        activeSprite_ = sprites_.front() ;
    }
    descriptions_.push_back(d) ;
}

void Animation::setActiveSprite(size_t id)
{
    if(activeSprite_ != nullptr)
    {
        activeSprite_->reset() ;
    }
    activeSprite_ = getSprite(id) ;
    activeSpriteIndex_ = id ;
}
void Animation::setActiveSprite(std::string d)
{
    if(activeSprite_ != nullptr)
    {
        activeSprite_->reset() ;
    }
    activeSprite_ = getSprite(d) ;
    auto id = getSpriteIdFromDescription(d) ;
    activeSpriteIndex_ = id ;
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

void Animation::switchActiveSprite( std::string s)
{
    if(activeSprite_ != nullptr)
        activeSprite_->reset() ;
    for(size_t i = 0 ; i < descriptions_.size() ; ++i)
    {
        if(descriptions_[i] == s)
            activeSprite_ = sprites_[i] ;
    }
}

void Animation::startAnimation()
{
    if(timer_ == nullptr )
        initTimer(100) ;
    timer_->start(100) ;
    connect(timer_, &QTimer::timeout, this, &Animation::rotatePixmap) ;
}

void Animation::stopAnimation()
{
    if(timer_ != nullptr)
        timer_->stop() ;
}

void Animation::randomActiveSprite()
{
    if(activeSpriteIndex_ != size_t(-1))
        activeSprite_->reset() ;

    {
        auto j = rand() % sprites_.size() ;
        activeSpriteIndex_ = j ;
    }
    activeSprite_ = sprites_[activeSpriteIndex_] ;
}

//

void Animation::nextSprite()
{
    if(activeSpriteIndex_ != size_t(-1) )
        activeSprite_->reset() ;

    activeSpriteIndex_ = activeSpriteIndex_ == sprites_.size() -1 ? 0 : activeSpriteIndex_+1 ;
    activeSprite_ = sprites_[activeSpriteIndex_] ;
}

void Animation::initTimer(size_t msec)
{
    if(timer_ == nullptr)
    {
        timer_ = new QTimer  ;
        timer_->start(msec) ;
        isInnerTimer_ = true ;
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
    auto e = std::exception() ;
    throw(e) ;
}

size_t Animation::getSpriteIdFromDescription(std::string d)
{
    size_t rv(-1) ;
    for (size_t i = 0; i < descriptions_.size() ; ++i)
    {
        if (descriptions_[i] == d )
        {
            rv = i ;
        }
    }
    return rv ;
}

std::shared_ptr<Sprite> Animation::getSprite(size_t id)
{
    return sprites_.at(id) ;
}

QGraphicsPixmapItem *&Animation::pmi()
{
    return pmI_ ;
}

QPixmap Animation::getActivePixmap()
{
    return *activeSprite_->getActive() ;
}

void Animation::setTimer(QTimer *t)
{
    timer_ = t ;
}
