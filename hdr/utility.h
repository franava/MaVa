#ifndef UTILITY_H
#define UTILITY_H
#include <Sprite.h>

namespace utility
{
    QPixmap addTransparency(
        const QPixmap &pixmap,
        const QPoint &point) ;

    QPixmap flipPixmap(
        const QPixmap& pixmap,
        bool leftRight,
        bool topBottom);

    void flipSprite(
        const std::vector<QPixmap>& sprite,
        std::vector<QPixmap>& result,
        bool leftRight,
        bool topBottom);

    void flipSprite(
        const Sprite& from,
        Sprite& to,
        bool leftRight,
        bool topBottom);
}


#endif // UTILITY_H
