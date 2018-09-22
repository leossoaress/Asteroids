#ifndef ASTEROIDS_SHOT_HPP
#define ASTEROIDS_SHOT_HPP

#include "includes.hpp"

class Shot
{
    public:

        Shot( void );

        Shot( int size, int x, int y, int mousex, int mousey );

        void drawShot( bool update );

        std::pair<int,int> getPos( void );

    private:

        int x_ = 0, y_ = 0, incx_ = 0, incy_ = 0, size_ = 0;
        int initx_ = 0, inity_ = 0;
        int dirx_ = 0, diry_ = 1;
        double a_ = 0.0;     
};

#endif