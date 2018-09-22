#include "shot.hpp"

/* Default Constructor */
Shot::Shot( void ) {}

/* Main constructor: Shot */
Shot::Shot( int size, int x, int y, int mousex, int mousey ) : size_(size), x_(x), y_(y)
{
    dirx_ = mousex - x_;
    diry_ = mousey - y_;

    incx_ = x_;
    incy_ = y_;

    initx_ = x_;
    inity_ = y_;

    a_ = double(diry_) / double(dirx_);
}

/* Function responsible to draw the shot */
void Shot::drawShot( bool update )
{
    if(update)
    {
        if(fabs(dirx_) > fabs(diry_))
        {
            x_ = (dirx_ < 0) ? incx_-- : incx_++;
            y_ = a_*(x_-initx_) + inity_;
        }
        else
        {
            y_ = (diry_ < 0) ? incy_-- : incy_++;
            x_ = (y_-inity_)/a_ + initx_;
        }
    }
    
    glLoadIdentity();

    glBegin(GL_QUADS);
        glVertex2d(x_-size_,y_);
        glVertex2d(x_+size_,y_);
        glVertex2d(x_+size_,y_+size_);
        glVertex2d(x_-size_,y_+size_);
    glEnd();

    glLoadIdentity();
}

/* Function responsible to return shot's position */
std::pair<int,int> Shot::getPos( void )
{
    return std::make_pair(x_,y_);
}