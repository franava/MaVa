#include <sprite.h>
#include <QDebug>
#include <algorithm>

Sprite::Sprite( std::string n)
{
    name_ = n ;
}

Sprite::Sprite(const Sprite &s)
{
    name_ = s.name_ ;
    pMV_ = s.pMV_ ;
    reset() ;
}

Sprite::~Sprite() noexcept
{
}

void Sprite::defineSpriteFrames(
    QPixmap pm,
    QPoint tl,
    QPoint br,
    size_t elements,
    size_t separator)
{
    auto singlePm = pm.copy(QRect(tl, br)) ;
    pMV_.resize(elements) ;
    auto width = (singlePm.width() - (elements -1)* separator) / elements ;
    for (size_t i = 0 ; i < elements ; ++i)
    {
        pMV_[i] = singlePm.copy(i*(width+separator), 0, width, singlePm.height()) ;
    }
    active_ = &pMV_.back() ;
    reset() ;
}

void Sprite::addFrame(QPixmap p)
{
    pMV_.push_back(p) ;
}

void Sprite::rescaleSprite(size_t scale, bool isSmooth)
{
    std::for_each(
        pMV_.begin(),
        pMV_.end(),
        [&](QPixmap& e)
        {
            if(isSmooth)
                e = e.scaled(e.width()*scale, e.height()*scale, Qt::IgnoreAspectRatio, Qt::SmoothTransformation) ;
            else
                e = e.scaled(e.width()*scale, e.height()*scale , Qt::IgnoreAspectRatio) ;
        });
}

void Sprite::rescaleSprite(size_t scaleX, size_t scaleY, bool isSmooth)
{
    std::for_each(
        pMV_.begin(),
        pMV_.end(),
        [&](QPixmap& e)
        {
            if(isSmooth)
                e = e.scaled(e.width()*scaleX, e.height()*scaleY, Qt::IgnoreAspectRatio, Qt::SmoothTransformation) ;
            else
                e = e.scaled(e.width()*scaleX, e.height()*scaleY, Qt::IgnoreAspectRatio) ;
        });
}

void Sprite::defineSpriteFrames(
    const QString& file,
    QPoint tl,
    QPoint br,
    size_t elements,
    size_t separator)
{
    QPixmap pM(file) ;
    defineSpriteFrames(pM, tl, br, elements, separator) ;
}

QPixmap& Sprite::rotateActive()
{
    if(active_ != &pMV_.back())
    {
        ++active_ ;
    }
    else
    {
        active_ = &pMV_.front() ;
    }
    return *active_ ;
}

void Sprite::reset()
{
    if(pMV_.size() > 0)
        active_ = &pMV_.back() ;
}

Sprite operator+(const Sprite& first,const Sprite& second)
{
    Sprite res;
    std::for_each(
        first.pmv().begin(),
        first.pmv().end(),
        [&](auto t)
        {
            res.addFrame(t) ;
        });

    std::for_each(
        second.pmv().begin(),
        second.pmv().end(),
        [&](auto t)
        {
            res.addFrame(t) ;
        });
    return res ;
}
