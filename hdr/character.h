#ifndef CHARACTER_H
#define CHARACTER_H

#include <animation.h>
#include <QGraphicsPixmapItem>

class QTimer;

class Character :
    public QObject,
    public QGraphicsPixmapItem
{
    Q_OBJECT ;
public:

    Character() ;

    virtual ~Character()noexcept = default ;
    void animate() ;
    void setAnimation(std::shared_ptr<Animation> a);
    void rotateFrameFromAnimation() ;
    QTimer*& timer() ;

public slots:

    void switchAnimationToRandom() ;
    void switchAnimationToNext() ;
    void switchAnimationToSpecific(size_t t) ;
    void switchAnimationToSpecific(const std::string& s) ;
    void setFrame() ;
    void keyPressEvent(QKeyEvent *event) ;

private:
    std::shared_ptr<Animation> animation_ ;
    QTimer* t_ ;
};

#endif // CHARACTER_H
