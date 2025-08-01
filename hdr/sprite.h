#ifndef SPRITE_H
#define SPRITE_H

#include <QPixmap>

class Sprite
{
public:
    Sprite(std::string n) ;
    Sprite() = default ;
    Sprite(const Sprite&) ;
    ~Sprite()noexcept ;


    //This method takes a SpriteSheet as input, as well as a rectangle (defined by TL/BR corners)
    //and splits it into equal size. if a separation among frames exists, takes it into account
    void defineSpriteFrames(
        const QString& file,    //Filename - path in resource file
        QPoint tl,              //TopLeft corner of Sprite
        QPoint br,              //BottomRight corner of Sprite
        size_t elements,        //Number of elements in Sprite
        size_t separator=0) ;   //Size of separation among sprites (if any)

    //This method takes a SpriteSheet as input, as well as a rectangle (defined by TL/BR corners)
    //and splits it into equal size. if a separation among frames exists, takes it into account.
    //rm pixel's value is taken as the value to be removed
    void defineSpriteFrameRemovingBg(
        const QString& file,    //Pixmap class main input
        QPoint tl,              //TopLeft corner of Sprite
        QPoint br,              //BottomRight corner of Sprite
        QPoint rm,              //Pixel who's value is to be removed from image
        size_t elements,        //Number of elements in Sprite
        size_t separator=0) ;   //Size of separation among sprites (if any)

    //This method takes a SpriteSheet as input, as well as a rectangle (defined by TL/BR corners)
    //and splits it into equal size. if a separation among frames exists, takes it into account
    void defineSpriteFrames(
        QPixmap pm,             //Pixmap class main input
        QPoint tl,              //TopLeft corner of Sprite
        QPoint br,              //BottomRight corner of Sprite
        size_t elements,        //Number of elements in Sprite
        size_t separator=0) ;   //Size of separation among sprites (if any)

    //This method takes a SpriteSheet as input, as well as a rectangle (defined by TL/BR corners)
    //and splits it into equal size. if a separation among frames exists, takes it into account.
    //rm pixel's value is taken as the value to be removed
    void defineSpriteFrameRemovingBg(
        QPixmap pm,             //Pixmap class main input
        QPoint tl,              //TopLeft corner of Sprite
        QPoint br,              //BottomRight corner of Sprite
        QPoint rm,              //Pixel who's value is to be removed from image
        size_t elements,        //Number of elements in Sprite
        size_t separator=0) ;   //Size of separation among sprites (if any)

    //This method takes a Spriteshjeet as input, as well as a list of Rectangle
    //and extracts each rectangle as a new frame of a sprite.
    void defineFFASpriteFrames(
        const QString&  pm,                 //Pixmap main Input
        const std::vector<QRect>& frames) ; //vector of frames

    //This method takes a Spriteshjeet as input, as well as a list of Rectangle
    //and extracts each rectangle as a new frame of a sprite.
    void defineFFASpriteFrames(
        QPixmap pm,                         //Pixmap main Input
        const std::vector<QRect>& frames) ; //vector of frames

    //This method takes a Spriteshjeet as input, as well as a list of Rectangle
    //and extracts each rectangle as a new frame of a sprite.
    //rm pixel's value is taken as the value to be removed
    void defineFFASpriteFrameRemovingBackground(
        const QString&  pm,                 //Pixmap main Input
        QPoint rm,                          //Pixel who's value is to be removed from image
        const std::vector<QRect>& frames) ; //vector of frames

    //This method takes a Spriteshjeet as input, as well as a list of Rectangle
    //and extracts each rectangle as a new frame of a sprite.
    //rm pixel's value is taken as the value to be removed
    void defineFFASpriteFrameRemovingBackground(
        QPixmap pm,                         //Pixmap main Input
        QPoint rm,                          //Pixel who's value is to be removed from image
        const std::vector<QRect> &frames) ; //vector of frames

    //Returns the next frame of a sprite making it the active frame
    QPixmap& rotateActive() ;

    //resets the activeFrame_ to the last frame (this means that rotateActive will return the first frame upon call
    void reset() ;

    //rescales each frame of the Sprite by a scale by scale value
    void rescaleSprite(
        size_t scale,           // scaling factor
        bool isSmooth=false) ;  // is the transformation smoothed or rough (false == rough)
    //rescales each frame of the Sprite by a scaleX by scaleY value
    void rescaleSprite(
        size_t scaleX,          // scaling factor
        size_t scaleY,          // scaling factor
        bool isSmooth=false) ;  // is the transformation smoothed or rough (false == rough)

    QPixmap addTransparency(
        const QPixmap &pixmap,
        const QPoint &point) ;

    /************************************
     * Methods needed for Debug purpose *
     ************************************/
    //returns activeFrame_
    QPixmap *getActive() ;
    //returns Sprite's n ame
    const std::string &name() const noexcept ;
    //returns the number of frames that compose the sprite
    size_t size() const noexcept ;
    //sets name_ variable
    void name(const std::string &name) ;

    /************************************************
     * Methods needed for Composite-Sprite Creation *
     ************************************************/
    //Adds a single frame to the spite. the burden to create a proper frame is upon the developer
    void addFrame(QPixmap p) ;

    //returns the vector of frames. the reference is constant.
    const std::vector<QPixmap> &pmv() const noexcept ;

private:
    std::string name_{} ;
    std::vector<QPixmap> pMV_{} ;
    QPixmap* active_ {nullptr} ;
};

//adds Two sprites in one
Sprite operator+(const Sprite& first, const Sprite& second) ;


#endif // SPRITE_H
