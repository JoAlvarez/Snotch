#include "clickable.h"
#include <SDL/SDL_opengl.h>

Clickable:: Clickable()
{
    getInstances( );
}

Clickable:: Clickable( Point uL, Point lR )
{
    upperLeft  = uL;
    lowerRight = lR;

    lowerLeft  = Point( upperLeft.getX()  , lowerRight.getY() );
    upperRight = Point( lowerRight.getX() , upperLeft.getY()  );
    getInstances( );
}

Clickable::~Clickable()
{
    input->release();
    window->release();
}

bool Clickable:: isClicked()
{
    double left  = upperLeft.getX() + window->leftCoord();
    double right = lowerRight.getX() + window->leftCoord();
    double upper = upperLeft.getY() + window->bottomCoord();
    double lower = lowerRight.getY() + window->bottomCoord();
    if (
         input->getMouseXloc() >= left   and
         input->getMouseXloc() <= right  and
         input->getMouseYloc() >= lower  and
         input->getMouseYloc() <= upper  and
         input->getMouseInput() == "Left Up"
       )
        return true;
    else
        return false;
}

void Clickable:: getInstances()
{
    input = Input::getInstance();
    window = Window::getInstance();
}

bool Clickable:: isMouseOver()
{
    double left  = upperLeft.getX() + window->leftCoord();
    double right = lowerRight.getX() + window->leftCoord();
    double upper = upperLeft.getY() + window->bottomCoord();
    double lower = lowerRight.getY() + window->bottomCoord();
    if (
         input->getMouseXloc() >= left   and
         input->getMouseXloc() <= right  and
         input->getMouseYloc() >= lower  and
         input->getMouseYloc() <= upper
       )
        return true;
    else
        return false;
}

void Clickable:: draw()
{
    double alpha;
    double left  = upperLeft.getX() + window->leftCoord();
    double right = lowerRight.getX() + window->leftCoord();
    double upper = upperLeft.getY() + window->bottomCoord();
    double lower = lowerRight.getY() + window->bottomCoord();

    //Find the alpha of the box
    if( isMouseOver() )
        alpha = 0.8;
    else
        alpha = 0.3;

    if( isClicked() )
        alpha = 0.5;

    glEnable ( GL_BLEND );
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //Draw box
    glColor4f( 0.0, 0.0, 1.0, alpha );
        glBegin( GL_QUADS );
            glVertex2f( left,  upper );
            glVertex2f( right, upper );
            glVertex2f( right, lower );
            glVertex2f( left,  lower );
        glEnd();
    //Draw outline
    glColor4f( 1.0, 1.0, 1.0, 1.0 );
        glBegin( GL_LINE_LOOP );
            glVertex2f( left,  upper );
            glVertex2f( right, upper );
            glVertex2f( right, lower );
            glVertex2f( left,  lower );
        glEnd();
    //Reset color and alpha blending
    glColor4f( 1.0, 1.0, 1.0, 1.0 );
    glDisable( GL_BLEND );
    glEnd();
}

void Clickable:: move( double dX, double dY )
{
    upperLeft.move( dX, dY );
    lowerLeft.move( dX, dY );
    upperRight.move( dX, dY );
    lowerRight.move( dX, dY );
}

Point Clickable:: getMouseLoc()
{
    return Point( input->getMouseXloc(),
                  input->getMouseYloc() );
}
