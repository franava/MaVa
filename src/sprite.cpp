#include <sprite.h>
#include <QDebug>
#include <QBitmap>
#include <algorithm>
#include <utility.h>
#include <QString>
Sprite::Sprite( std::string n )
{
    name_ = n ;
}

Sprite::Sprite( const Sprite &s )
{
    name_ = s.name_ ;
    pMV_ = s.pMV_ ;
    reset() ;
}

Sprite::~Sprite() noexcept
{
}

void Sprite::defineSpriteFrames(
    std::string file,
    QPoint tl,
    QPoint br,
    size_t elements,
    size_t separator)
{
    QPixmap pM(file.c_str()) ;
    defineSpriteFrames(pM, tl, br, elements, separator) ;
}

void Sprite::defineSpriteFrameRemovingBg(
    std::string file,
    QPoint tl,
    QPoint br,
    QPoint rm,
    size_t elements,
    size_t separator)
{
    auto pM = utility::addTransparency(QPixmap(file.c_str()), rm) ;
    defineSpriteFrames(pM, tl, br, elements, separator) ;
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

void Sprite::defineSpriteFrameRemovingBg(
    QPixmap pm,
    QPoint tl,
    QPoint br,
    QPoint rm,
    size_t elements,
    size_t separator)
{
    auto pM = utility::addTransparency(pm, rm) ;
    defineSpriteFrames(pM, tl, br, elements, separator) ;
}

void Sprite::defineFFASpriteFrames(
    std::string pm,
    const std::vector<QRect>& frames)
{
    QPixmap p(pm.c_str()) ;
    defineFFASpriteFrames(p, frames) ;
}

void Sprite::defineFFASpriteFrames(
    QPixmap pm,
    const std::vector<QRect>& frames)
{
    pMV_.reserve(frames.size()) ;

    std::for_each(
        frames.begin(),
        frames.end(),
        [&](auto f)
        {
            pMV_.push_back(pm.copy(f));
        }) ;
    reset() ;
}

void Sprite::defineFFASpriteFrameRemovingBackground(
    std::string pm,
    QPoint rm,
    const std::vector<QRect> &frames)
{
    auto  p = utility::addTransparency( QPixmap(pm.c_str()), rm) ;
    defineFFASpriteFrames(p, frames) ;
}

void Sprite::defineFFASpriteFrameRemovingBackground(
    QPixmap pm,
    QPoint rm,
    const std::vector<QRect> &frames)
{
    auto  p = utility::addTransparency(pm, rm) ;
    defineFFASpriteFrames(p, frames) ;
}

void Sprite::addFrame( QPixmap p )
{
    pMV_.push_back(p) ;
}

void Sprite::addFrames(const std::vector<QPixmap> &v)
{
    for_each(
        v.begin(),
        v.end(),
        [&](auto t)
        {
            addFrame(t);
        });
}

void Sprite::rescaleSprite(
    size_t scale,
    bool isSmooth)
{
    rescaleSprite(scale, scale, isSmooth) ;
}

void Sprite::rescaleSprite(
    size_t scaleX,
    size_t scaleY,
    bool isSmooth)
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
        }) ;
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

Sprite operator+(
    const Sprite& first,
    const Sprite& second)
{
    Sprite res(first.name());
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
    res.reset() ;
    return res ;
}

QPixmap *Sprite::getActive()
{
    return active_;
}

const std::string &Sprite::name() const noexcept
{
    return name_ ;
}

size_t Sprite::size() const noexcept
{
    return pMV_.size() ;
}

void Sprite::name( const std::string &name)
{
    name_ = name ;
}

const std::vector<QPixmap> &Sprite::pmv() const noexcept
{
    return pMV_ ;
}
