#include <utility.h>
#include <QBitmap>

QPixmap utility::addTransparency(
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

QPixmap utility::flipPixmap(
    const QPixmap &pixmap,
    bool leftRight,
    bool topBottom)
{
    auto lr = leftRight ? -1 : 1 ;
    auto tb = topBottom ? -1 : 1 ;
    return pixmap.transformed(QTransform().scale(lr, tb));
}

void utility::flipSprite(
    const std::vector<QPixmap> &sprite,
    std::vector<QPixmap>& result,
    bool leftRight,
    bool topBottom)
{

    result.resize(sprite.size());
    for(size_t i = 0 ; i < result.size() ; ++i)
        result[i] = flipPixmap(sprite[i], leftRight, topBottom);
}

void utility::flipSprite(
    const Sprite &from,
    Sprite &to,
    bool leftRight,
    bool topBottom)
{
    auto& f = from.pmv() ;
    std::vector<QPixmap> t ;
    flipSprite(f, t, leftRight, topBottom);
    to.addFrames(t) ;
}
