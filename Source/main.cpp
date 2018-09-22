/**
 * Project: Asteroids 
 * 
 * Purpose: Simulate Asteroids, an arcade space shooter realeased in 1979 by Atar
 * 
 * @author Jose Leoberto Soares Filho
 * @version 1.0 19/09/18
 */  

#include "includes.hpp"
#include "asteroid.hpp"
#include "ship.hpp"
#include "shot.hpp"


/* Functions Declarations */

void drawScene( void );

void idleScene( void );

void processKeyboard( int key, int x, int y );

void processMouse( int x, int y );

void processClickMouse( int k, int l, int x, int y );

void update( int val );

void createAsteroids( int val );

void colision( void );

bool colision2obj( std::pair<int,int> obj1, std::pair<int,int> obj2 );


/* Static objects */

Ship ship(20, 0, 0);

std::vector<Shot> shots;

std::vector<Asteroid> asteroids;

/* Variables responsible to save the ship's position */
int incx = 0, incy = 0;

/* Variables responsible to save the mouse's position */
int mousex = 0, mousey = 1;

/* Boolean variables responsible to authorize some functions */
bool drawshot = false, drawasteroid = false, shotok = true;


/* Main Function */
int main( int argc, char *argv[] )
{
    glutInit( &argc, argv );

    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );

    glutInitWindowSize(800, 600);

    glutCreateWindow("Asteroids");

    glutDisplayFunc(drawScene);

    glutIdleFunc(drawScene);

    glutSpecialFunc(processKeyboard);

    glutPassiveMotionFunc(processMouse);

    glutMouseFunc(processClickMouse);

    glutTimerFunc(4000,createAsteroids,0);

    glutTimerFunc(100,update,0);

    glutMainLoop();
}

/* Function responsible to draw the scene */
void drawScene( void )
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400.0,400.0,-300.0,300.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    ship.drawShip(incx, incy, mousex, mousey);

    for(unsigned i = 0; i < shots.size(); ++i)
            shots[i].drawShot(drawshot);
    
    for(unsigned i = 0; i < asteroids.size(); ++i)
            asteroids[i].drawAsteroid(drawasteroid);

    drawshot = false;
    drawasteroid = false;

    colision();
    glFlush();
}

/* Function responsible to get keyboard action */
void processKeyboard( int key, int x, int y )
{
    switch(key)
    {
        case GLUT_KEY_UP:
            incy += 5;
            break;

        case GLUT_KEY_DOWN:
            incy -= 5;
            break;

        case GLUT_KEY_RIGHT:
            incx += 5;
            break;

        case GLUT_KEY_LEFT:
            incx -= 5;
            break;
    }

    glutPostRedisplay();
}

/* Function responsible to get mouse movement */
void processMouse( int x, int y )
{
    mousex = x - 400;
    mousey = -(y - 300);

    glutPostRedisplay();
}

/* Function responsible to get mouse click */
void processClickMouse( int k, int l, int x, int y )
{
    if(shotok)
    {
        Shot shot(2,incx,incy,mousex,mousey);
        shots.emplace_back(shot);
        shotok = false;
        glutPostRedisplay();
    }
    else
        shotok = true;

}

/* Function responsible to call the function to update the scene */
void update( int val )
{
    drawshot = true;
    drawasteroid = true;
    glutPostRedisplay();
    glutTimerFunc(10,update,val);
}

/* Function responsible to create asteroids */
void createAsteroids( int val )
{
    int a = rand() % 2;
    int b = rand() % 2;

    int randx = 0, randy = 0;

    if(a == 0) 
    {
        randx = (rand() % 1600) - 800;
        randy = (b == 0) ? -650 : 650;
    } 
    else 
    {
        randx = (b == 0) ? -850 : 850;
        randy = (rand() % 1200) - 600;
    }
    
    Asteroid asteroid(15,randx,randy,incx,incy);
    asteroids.emplace_back(asteroid);
    
    glutPostRedisplay();
    glutTimerFunc(4000,createAsteroids,val);
}

/* Function responsible to detect colision between shots, asteroids and ship*/
void colision( void )
{
    if(abs(incx) == 400 || abs(incy) == 300) {
        incx = 0; incy = 0;
        glutPostRedisplay();
    }

    for(unsigned i = 0; i < asteroids.size(); ++i) 
    {
        std::pair<int,int> posasteroids = asteroids[i].getPos();
        std::pair<int,int> posship = ship.getPos();

        if(colision2obj(posasteroids,posship))
        {
            asteroids.clear();
            shots.clear();
            incx = 0; incy = 0;
        }

        for(unsigned j = 0; j < shots.size(); ++j) 
        {
            std::pair<int,int> posshot = shots[i].getPos();
            if(colision2obj(posasteroids,posshot))
            {
                asteroids.erase(asteroids.begin()+i);
                shots.erase(shots.begin()+j);
            }
        }
    }
}

/* Auxiliary function responsible to detect colision between 2 position*/
bool colision2obj(std::pair<int,int> obj1, std::pair<int,int> obj2)
{
    if(obj1.first-10 < obj2.first &&  obj1.first+10 > obj2.first)
        if(obj1.second-10 < obj2.second &&  obj1.second+10 > obj2.second)
            return true;

    return false;
}