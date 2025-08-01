#ifndef CHARACTER_H
#define CHARACTER_H

#include <animation.h>
#include <QGraphicsPixmapItem>

class Character  : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT ;
public:
    Character(std::shared_ptr<Animation> a) ;
    void animate() ;

public slots:
    void switchAnimationToRandom() ;
    void switchAnimationToNext() ;
    void switchAnimationToSpecific(size_t t) ;
    void switchAnimationToSpecific(const std::string& s) ;
private:
    std::shared_ptr<Animation> animation_ ;
};

#endif // CHARACTER_H
