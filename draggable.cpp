#include "draggable.h"


Draggable::Draggable()
    : Clickable()
{
    draggable = false;
}
Draggable::Draggable( Point upperLeft, Point lowerRight )
    : Clickable( upperLeft, lowerRight )
{
    draggable = false;
}

void Draggable::update()
{
    newMouseLoc = getMouseLoc();

    //Check to see if the object can be dragged
    if( isClicked() )
        draggable = !draggable;

    //Move the draggable object
    if( draggable )
    {
        double dX = newMouseLoc.getX() - origMouseLoc.getX();
        double dY = newMouseLoc.getY() - origMouseLoc.getY();

        //Make sure the object is not dragged outside of
        // the window.
        //Left
        if( ( dX + upperLeft.getX() ) < 0 )
            dX = -1.0 * upperLeft.getX();
        //Right
        if( ( dX + lowerRight.getX() ) >
            ( window->rightCoord() - window->leftCoord() ) )
            dX = window->rightCoord() -
                 window->leftCoord() -
                 lowerRight.getX() - 1;
        //Bottom
        if( ( dY + lowerRight.getY() ) < 0 )
            dY = -1.0 * lowerRight.getY();
        //Top
        if( ( dY + upperLeft.getY() ) >
            ( window->topCoord() - window->bottomCoord() ) )
            dY = window->topCoord() -
                 window->bottomCoord() -
                 upperLeft.getY() - 1.0;


        move( dX, dY );
    }

    origMouseLoc = getMouseLoc();
}
