#ifndef __DETECTABLE_H__
#define __DETECTABLE_H__

#include "point.h"
#include <string>

#define TOP_DETECTED 0
#define LEFT_DETECTED 1
#define RIGHT_DETECTED 1
#define BOTTOM_DETECTED 0
#define NOTHING_DETECTED -1

using namespace std;

class Detectable
{
    public:

        Detectable();

        //Constructor for a circle
        //non-functional
        Detectable(Point, double);

        //Constructor for a rectangle
        Detectable( Point ul, Point lr );

        Detectable(Point ul, Point lr, string type);

        //Are-Equal Operator ( to compare two detectable objects
        bool operator==( Detectable & o );

        // Single Side Detection
        bool detectFromLeft          ( Detectable & o );
        bool detectFromRight         ( Detectable & o );
        bool detectFromTop           ( Detectable & o );
        bool detectFromBottom        ( Detectable & o );

        //Double sided detection functions
        int detectFromTopAndLeft    ( Detectable & o );
        int detectFromTopAndRight   ( Detectable & o );
        int detectFromBottomAndLeft ( Detectable & o );
        int detectFromBottomAndRight( Detectable & o );

        bool didIntersect(Detectable * o);

        void setPosition( Point uL );

        // check if the implicit object is greater than
        // the explicit parameter
        int isBiggerThan( Detectable* o );

        Point uLeft;
        Point lRight;
        Point lLeft;
        Point uRight;
        Point center;

        double height;
        double width;

        string getType();

        virtual void draw() = 0;

    protected:

        string type;

        bool intersects(Detectable* o);
};

#endif
