#ifndef CHARACTER_H
#define CHARACTER_H

#include <animation.h>
#include <QGraphicsPixmapItem>

class Character  : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT ;
public:

    Character() ;
    Character(std::shared_ptr<Animation> a) ;
    virtual ~Character()noexcept = default ;
    void animate() ;
    void setAnimation(std::shared_ptr<Animation> a);
    void rotateFrameFromAnimation() ;

public slots:

    void switchAnimationToRandom() ;
    void switchAnimationToNext() ;
    void switchAnimationToSpecific(size_t t) ;
    void switchAnimationToSpecific(const std::string& s) ;
    void setFrame() ;
    void keyPressEvent(QKeyEvent *event) ;
private:
    std::shared_ptr<Animation> animation_ ;
};

#endif // CHARACTER_H
