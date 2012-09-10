/*
    Original Author:    Andy Amaya
    Date Created:       August 20, 2008

    Purpose:            This clickable class was designed specifically for TB
                        Tic Tac Toe. However, with a simple modification you
                        can use this with Roby's SDL Package to make any image
                        into a button.

    PLEASE GIVE CREDIT TO ORIGINAL AUTHORS IF THIS CLASS IS USED.

    P.S.
    Don't forget that in order to use this Clickable Class you need
    the three #included Classes which may require other Classes as well.
    This also requires SDL support.

*/

#ifndef __CLICKABLE_H__
#define __CLICKABLE_H__

#include "point.h"
#include "input.h"
#include "image.h"
#include "window.h"

class Clickable
{
    public:

        // Default Constructor
        Clickable();

        // Constructor with two points.
        Clickable( Point upperLeft, Point lowerRight );

        ~Clickable();

        // Returns true if the button was clicked
        bool isClicked();

        // returns true if the mouse is hovering over the button
        bool isMouseOver();

        // BRANDON... THIS is the main thing you would need to
        // change to make it work with the new SDL package
        void getInstances();       // sets the location of the input object in the game

        // Renders the passed image within the button. ( Makes an image into a button)
        //void renderImageWithin( GLuint & image );
        // BRANDON THIS FUNCTION NEED TO BE CHANGED TO USE ROBY'S new package
        void draw();

        void move( double dX, double dY );

        Point getMouseLoc();

    //protected:

        // Input pointer that holds the address of the input
        // object being used
        Input* input;
        Window* window;

        // Four points of the clickable object
        Point upperLeft;
        Point lowerLeft;
        Point upperRight;
        Point lowerRight;

};

#endif

