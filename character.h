#ifndef CHARACTER_H
#define CHARACTER_H
#include <animation.h>
#include <QGraphicsPixmapItem>

class Character : public QGraphicsPixmapItem, public QObject
{
    Q_OBJECT ;
public:
    Character(std::shared_ptr<Animation> a);

public slots:
    void animate() ;
private:
    std::shared_ptr<Animation> animation_ ;
};

#endif // CHARACTER_H
