#include "ship.hpp"

/* Default Constructor */
Ship::Ship( void ) {}

/* Main constructor: Ship */
Ship::Ship( int size, int x, int y ) : x_(x), y_(y), size_(size)
{
    r_ = (sqrt(3)*size_)/2;
    a_ = r_/2;
}

/* Function responsible to draw the ship */
void Ship::drawShip( int movex, int movey, int mousex, int mousey )
{
    x_ = movex;
    y_ = movey;

    glTranslated( movex, movey, 0.0 );

    mousex = mousex - x_;
    mousey = mousey - y_;

    double normship  = sqrt(dirx_*dirx_ + diry_*diry_);
    double normmouse = sqrt(mousex*mousex + mousey*mousey);

    angle_ = dirx_*mousex + diry_*mousey;
    angle_ = angle_/(normship*normmouse);
    angle_ = acos(angle_);
    angle_ = angle_*(180/M_PI);

    if(dirx_ < mousex) angle_ *= -1;

    glRotated( angle_, 0.0, 0.0, 1.0 );

    glBegin(GL_TRIANGLES);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex2d(0,r_);
        glVertex2d(-size_/2.0,-a_);
        glVertex2d(size_/2.0,-a_);
    glEnd();
}

/* Function responsible to return ship's position */
std::pair<int,int> Ship::getPos( void )
{
    return std::make_pair(x_,y_);
}