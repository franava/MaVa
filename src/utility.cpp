#include <utility.h>
#include <QBitmap>
#include <QDebug>
#include <algorithm>

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
    if(
        leftRight == true &&
        topBottom == true )
    {
        to = from ;
        return ;
    }
    auto& f = from.pmv() ;
    std::vector<QPixmap> t ;
    flipSprite(f, t, leftRight, topBottom);
    to.addFrames(t) ;
}

namespace
{

void produceAppendixes(const std::string& appendix, appendixes_t& appendixes)
{
    if(2 == appendix.size())
    {
        if( "_r" == appendix )
        {
            appendixes.push_back(std::make_tuple("_r", false, false)) ;
            appendixes.push_back(std::make_tuple("_l", true,  false)) ;
        }
        else if( "_l" == appendix )
        {
            appendixes.push_back(std::make_tuple("_r", true,  false)) ;
            appendixes.push_back(std::make_tuple("_l", false, false)) ;
        }
        else if("_t" == appendix )
        {
            appendixes.push_back(std::make_tuple("_t", false, false)) ;
            appendixes.push_back(std::make_tuple("_b", false,  true)) ;
        }
        else if("_b" == appendix )
        {
            appendixes.push_back(std::make_tuple("_t", false,  true)) ;
            appendixes.push_back(std::make_tuple("_b", false, false)) ;
        }
        else
        {
//            qDebug() << "no side appendixes" ;
            appendixes.push_back(std::make_tuple(appendix, false, false)) ;
        }
    }
}

}


void utility::ingestSprite(
    Animation &a,
    Sprite s)
{
    auto appendix = s.name().substr(s.name().size()-2, std::string::npos);

    if(
        appendix == "_r" ||
        appendix == "_l" ||
        appendix == "_t" ||
        appendix == "_b" )
    {
        appendixes_t appendixes ;
        produceAppendixes(appendix, appendixes);
        auto base = s.name().substr(0, s.name().size()-2) ;

        std::for_each(
            appendixes.begin(),
            appendixes.end(),
            [&](auto app)
            {
                Sprite ss(base + std::get<0>(app)) ;
                flipSprite(s,ss, get<1>(app), get<2>(app)) ;
                a.addSprite(ss, ss.name());
            });
    }
    else
    {
        a.addSprite(s, s.name()) ;
    }
}

void utility::ingestSprites(
    Animation &a,
    const std::vector<Sprite> &sv)
{
    std::for_each(
        sv.begin(),
        sv.end() ,
        [&](auto s)
        {
            ingestSprite(a, s);
        });
}
