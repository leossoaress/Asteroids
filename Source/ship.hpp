#ifndef ASTEROIDS_SHIP_HPP
#define ASTEROIDS_SHIP_HPP

#include "includes.hpp"

class Ship 
{

    public: 

        Ship( void );

        Ship( int size, int x, int y );

        void drawShip( int movex, int movey, int mousex, int mousey );

        std::pair<int,int> getPos();
        
    private:

        int x_ = 0, y_ = 0, size_ = 0;
        int dirx_ = 0, diry_ = 1; 
        double a_ = 0.0, r_ = 0.0, angle_ = 0.0;

};

#endif
