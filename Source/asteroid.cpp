#include "asteroid.hpp"

/* Default Constructor */
Asteroid::Asteroid( void ) {}

/* Main constructor: Asteroid */
Asteroid::Asteroid( int size, int x, int y, int shipx, int shipy ) : size_(size), x_(x), y_(y)
{
    dirx_ = shipx - x_;
    diry_ = shipy - y_;

    incx_ = x_;
    incy_ = y_;

    initx_ = x_;
    inity_ = y_;

    a_ = double(diry_) / double(dirx_);
}

/* Function responsible to draw the asteroid */
void Asteroid::drawAsteroid( bool update )
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

/* Function responsible to return asteroid's position */
std::pair<int,int> Asteroid::getPos( void )
{
    return std::make_pair(x_,y_);
}