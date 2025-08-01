#include <sprite.h>
#include <QDebug>
#include <QBitmap>
#include <algorithm>

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
    const QString& file,
    QPoint tl,
    QPoint br,
    size_t elements,
    size_t separator)
{
    QPixmap pM(file) ;
    defineSpriteFrames(pM, tl, br, elements, separator) ;
}

void Sprite::defineSpriteFrameRemovingBg(
    const QString &file,
    QPoint tl,
    QPoint br,
    QPoint rm,
    size_t elements,
    size_t separator)
{
    auto pM = addTransparency(QPixmap(file), rm) ;
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
    auto pM = addTransparency(pm, rm) ;
    defineSpriteFrames(pM, tl, br, elements, separator) ;
}

void Sprite::defineFFASpriteFrames(
    const QString &pm,
    const std::vector<QRect>& frames)
{
    QPixmap p(pm) ;
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
    const QString &pm,
    QPoint rm,
    const std::vector<QRect> &frames)
{
    auto  p = addTransparency( QPixmap(pm), rm) ;
    defineFFASpriteFrames(p, frames) ;
}

void Sprite::defineFFASpriteFrameRemovingBackground(
    QPixmap pm,
    QPoint rm,
    const std::vector<QRect> &frames)
{
    auto  p = addTransparency(pm, rm) ;
    defineFFASpriteFrames(p, frames) ;
}

void Sprite::addFrame( QPixmap p )
{
    pMV_.push_back(p) ;
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

QPixmap Sprite::addTransparency(
    const QPixmap &pixmap,
    const QPoint &point)
{
    QImage image = pixmap.toImage().convertToFormat(QImage::Format_ARGB32) ;

    // Get the color to make transparent
    QRgb target = image.pixel(point) ;

    // Create a mask where this color is black (mask=0) and everything else is white (mask=1)
    QBitmap mask = QBitmap::fromImage(image.createMaskFromColor(target, Qt::MaskOutColor)) ;

    // Apply the mask to the image
    image.setAlphaChannel(mask.toImage()) ;

    return QPixmap::fromImage(image) ;
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
