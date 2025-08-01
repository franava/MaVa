#ifndef SPRITE_H
#define SPRITE_H

#include <QPixmap>

class Sprite
{
public:
    Sprite(std::string n);
    Sprite() = default;
    Sprite(const Sprite&) ;
    ~Sprite()noexcept ;


    //This method takes a SpriteSheet as input, as well as a rectangle (defined by TL/BR corners)
    //and splits it into equal size. if a separation among frames exists, takes it into account
    void defineSpriteFrames(
        const QString& file, //Filename - path in resource file
        QPoint tl, //TopLeft corner of Sprite
        QPoint br, //BottomRight corner of Sprite
        size_t elements, //Number of elements in Sprite
        size_t separator=0) ; //Size of separation among sprites (if any)

    //This method takes a SpriteSheet as input, as well as a rectangle (defined by TL/BR corners)
    //and splits it into equal size. if a separation among frames exists, takes it into account.
    //rm pixel's value is taken as the value to be removed
    void defineSpriteFrameRemovingBg(
        const QString& file, //Pixmap class main input
        QPoint tl, //TopLeft corner of Sprite
        QPoint br, //BottomRight corner of Sprite
        QPoint rm, //Pixel who's value is to be removed from image
        size_t elements, //Number of elements in Sprite
        size_t separator=0);

    //This method takes a SpriteSheet as input, as well as a rectangle (defined by TL/BR corners)
    //and splits it into equal size. if a separation among frames exists, takes it into account
    void defineSpriteFrames(
        QPixmap pm, //Pixmap class main input
        QPoint tl, //TopLeft corner of Sprite
        QPoint br, //BottomRight corner of Sprite
        size_t elements, //Number of elements in Sprite
        size_t separator=0) ; //Size of separation among sprites (if any)

    //This method takes a SpriteSheet as input, as well as a rectangle (defined by TL/BR corners)
    //and splits it into equal size. if a separation among frames exists, takes it into account.
    //rm pixel's value is taken as the value to be removed
    void defineSpriteFrameRemovingBg(
        QPixmap pm, //Pixmap class main input
        QPoint tl, //TopLeft corner of Sprite
        QPoint br, //BottomRight corner of Sprite
        QPoint rm, //Pixel who's value is to be removed from image
        size_t elements, //Number of elements in Sprite
        size_t separator=0);

    //This method takes a Spriteshjeet as input, as well as a list of Rectangle
    //and extracts each rectangle as a new frame of a sprite.
    void defineFFASpriteFrames(
        const QString&  pm,
        const std::vector<QRect>& frames) ;

    //This method takes a Spriteshjeet as input, as well as a list of Rectangle
    //and extracts each rectangle as a new frame of a sprite.
    void defineFFASpriteFrames(
        QPixmap pm,
        const std::vector<QRect>& frames) ;

    //This method takes a Spriteshjeet as input, as well as a list of Rectangle
    //and extracts each rectangle as a new frame of a sprite.
    //rm pixel's value is taken as the value to be removed
    void defineFFASpriteFrameRemovingBackground(
        const QString&  pm,
        QPoint rm,
        const std::vector<QRect>& frames) ;

    //This method takes a Spriteshjeet as input, as well as a list of Rectangle
    //and extracts each rectangle as a new frame of a sprite.
    //rm pixel's value is taken as the value to be removed
    void defineFFASpriteFrameRemovingBackground(
        QPixmap pm,
        QPoint rm,
        const std::vector<QRect> &frames);

    //Returns the next frame of a sprite making it the active frame
    QPixmap& rotateActive() ;

    //resets the activeFrame_ to the last frame (this means that rotateActive will return the first frame upon call
    void reset() ;

    //rescales each frame of the Sprite by a scale by scale value
    void rescaleSprite(size_t scale, bool isSmooth=false) ;
    //rescales each frame of the Sprite by a scaleX by scaleY value
    void rescaleSprite(size_t scaleX, size_t scaleY, bool isSmooth=false) ;

    QPixmap addTransparency(const QPixmap &pixmap, const QPoint &point) ;

    /************************************
     * Methods needed for Debug purpose *
     ************************************/
    //returns activeFrame_
    QPixmap* getActive() {return active_ ;}
    //returns Sprite's name
    const std::string& name() const noexcept {return name_ ; }
    //returns the number of frames that compose the sprite
    size_t size() const noexcept {return pMV_.size() ;}
    //sets name_ variable
    void name(const std::string &name) { name_ = name ;}


    /************************************************
     * Methods needed for Composite-Sprite Creation *
     ************************************************/
    //Adds a single frame to the spite. the burden to create a proper frame is upon the developer
    void addFrame(QPixmap p) ;

    //returns the vector of frames. the reference is constant.
    const std::vector<QPixmap>& pmv()const noexcept{ return pMV_ ;}


private:
    std::string name_{} ;
    std::vector<QPixmap> pMV_{} ;
    QPixmap* active_ {nullptr};
};

//adds Two sprites in one
Sprite operator+(const Sprite& first, const Sprite& second) ;


#endif // SPRITE_H
