#ifndef ANIMATION_H
#define ANIMATION_H

#include <Sprite.h>
#include <vector>

class Animation
{
public:
    Animation();
    ~Animation() noexcept;
    //adds Sprite to animation
    void addSprite(
        Sprite s,                   // sprite to be added
        std::string d) ;            // description
    //adds Sprite to animation
    void addSprite(
        std::shared_ptr<Sprite> s,  // sprite to be added
        std::string d) ;            // description

    //sets the active sprite via description (Self-consistent)
    void setActiveSprite(std::string s) ;
    //sets the active sprite via id (Consistency up to the developer)
    void setActiveSprite(size_t id) ;

    //returns the sprite associated to the provided id
    std::shared_ptr<Sprite> getSprite(size_t id) ;
    //returns the sprite associated to the provided description
    std::shared_ptr<Sprite> getSprite(std::string d) ;
    //returns a spriteId associated to the provided description
    size_t getSpriteIdFromDescription(std::string d) ;

    void switchActiveSprite(size_t i) ;
    void switchActiveSprite(std::string s) ;
    QPixmap getActivePixmap() ;

public:
    QPixmap& rotatePixmap() ;
    void randomActiveSprite() ;
    void nextSprite() ;

private:
    std::vector<std::shared_ptr<Sprite>> sprites_ ;
    std::vector<std::string> descriptions_ ;
    std::shared_ptr<Sprite> activeSprite_ {nullptr} ;
    size_t activeSpriteIndex_ = -1 ;
    bool isInnerTimer_{false} ;
} ;

#endif // ANIMATION_H
