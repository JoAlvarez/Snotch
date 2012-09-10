#include "detectable.h"

/////////////////////////////////////////////////
//             CONSTRUCTORS
/////////////////////////////////////////////////
Detectable:: Detectable()
{
    type = "undefined";
}

Detectable:: Detectable( Point ul , Point lr )
{
    type   = "Rectangle";

    uLeft  = ul;
    lRight = lr;

    lLeft  = Point( uLeft.getX() , lRight.getY() );

    uRight = Point( lRight.getX(), uLeft.getY()  );

    center = Point( ( uLeft.getX() + lRight.getX() ) / 2  ,
                    ( uLeft.getY() + lRight.getY() ) / 2  );

    height = uLeft.getY() - lRight.getY();
    width  = uRight.getX() - uLeft.getX();
}

Detectable:: Detectable( Point ul , Point lr, string t)
{
    type   = t;

    uLeft  = ul;
    lRight = lr;

    lLeft  = Point( uLeft.getX() , lRight.getY() );

    uRight = Point( lRight.getX(), uLeft.getY()  );

    center = Point( ( uLeft.getX() + lRight.getX() ) / 2  ,
                    ( uLeft.getY() + lRight.getY() ) / 2  );

    height = uLeft.getY() - lRight.getY();
    width  = uRight.getX() - uLeft.getX();
}

Detectable::Detectable(Point center, double radius)
{
    type = "Circle";
    this->center = center;
    height = radius;
    width  = radius;
}

/////////////////////////////////////////////////
//             MEMBER FUNCTIONS
/////////////////////////////////////////////////
void Detectable::setPosition( Point uL )
{
    double moveX = uL.getX() - uLeft.getX();
    double moveY = uL.getY() - uLeft.getY();

    uLeft.move ( moveX, moveY );
    lLeft.move ( moveX, moveY );
    uRight.move( moveX, moveY );
    lRight.move( moveX, moveY );
    center.move( moveX, moveY );
}

/////

bool Detectable:: operator== ( Detectable & o )
{
    if ( this->uLeft.getX()  == o.uLeft.getX()  and
         this->uLeft.getY()  == o.uLeft.getY()  and
         this->lLeft.getX()  == o.lLeft.getX()  and
         this->lLeft.getY()  == o.lLeft.getY()  and
         this->uRight.getX() == o.uRight.getX() and
         this->uRight.getY() == o.uRight.getY() and
         this->lRight.getX() == o.lRight.getX() and
         this->lRight.getY() == o.lRight.getY()  )

            return true;

    else
            return false;
}

/////////////////////////////////////////////////
//             PRIVATE FUNCTIONS
/////////////////////////////////////////////////

bool Detectable::didIntersect(Detectable* o)
{
    if(this->intersects(o))
        return true;
    else
        return o->intersects(this);
}

bool Detectable::intersects(Detectable * o)
{
    double x1 = o->uLeft.getX();
    double x2 = o->uRight.getX();
    double y1 = o->uLeft.getY();
    double y2 = o->lLeft.getY();

    if(x1 >= uLeft.getX() && x1 <= uRight.getX())
    {
        if(y1 >= lLeft.getY() && y1 <= uLeft.getY())
        {
            return true;
        }
        if(y2 >= lLeft.getY() && y2 <= uLeft.getY())
        {
            return true;
        }
    }
    if(x2 >= uLeft.getX() && x2 <= uRight.getX())
    {
        if(y1 >= lLeft.getY() && y1 <= uLeft.getY())
        {
            return true;
        }
        if(y2 >= lLeft.getY() && y2 <= uLeft.getY())
        {
            return true;
        }
    }

    //There may be intersection even though there are no points within each other
    if(x1 >= uLeft.getX() && x1 <= uRight.getX() &&
       x2 >= uLeft.getX() && x2 <= uRight.getX())
    {
        if(y1 >= uLeft.getY() && y2 <= lLeft.getY())
            return true;
    }
    if(y1 >= lLeft.getY() && y1 <= uLeft.getY() &&
       y2 >= lLeft.getY() && y2 <= uLeft.getY() )
    {
        if(x1 <= uLeft.getX() && x2 >= uRight.getX())
            return true;
    }

    return false;
}

bool Detectable:: detectFromLeft( Detectable & o )
{
    if ( this->isBiggerThan( &o ) == 2 )
    {
        return o.detectFromRight( *this );

    }
    else
    {

        bool withBothRightPoints = ( ( uRight.getY() < o.uLeft.getY()       and
                                       lRight.getY() > o.lLeft.getY() )     and
                               (     ( o.uLeft.getX() - uRight.getX() ) >= 0 ) );

        bool withUpperRightPoint = ( ( uRight.getY() < o.uLeft.getY()   and
                                       uRight.getY() > o.lLeft.getY() ) and
                                   ( ( o.uLeft.getX() - uRight.getX() ) >= 0 ) );

        bool withLowerRightPoint = ( ( lRight.getY() < o.uLeft.getY()   and
                                       lRight.getY() > o.lLeft.getY() ) and
                                   ( ( o.uLeft.getX() - uRight.getX() ) >= 0 ) );

        bool isOnLeft = lRight.getX() < o.center.getX() and lRight.getX() > o.uLeft.getX();

        if ( (withBothRightPoints or withLowerRightPoint or withUpperRightPoint) and isOnLeft )
            return true;

        else
            return false;

    }
}

bool Detectable:: detectFromRight( Detectable & o )
{
    if ( this->isBiggerThan( &o ) == 2 )
    {
        return o.detectFromLeft( *this );
    }
    else
    {
        bool withBothLeftPoints = ( ( uLeft.getY() < o.uRight.getY()          and
                                      lLeft.getY() > o.lRight.getY() )        and
                                (( o.lRight.getX() - lLeft.getX() ) >= 0 ) );

        bool withUpperLeftPoint = ( ( uLeft.getY() < o.uRight.getY()   and
                                      uLeft.getY() > o.lRight.getY() ) and
                                ( ( o.lRight.getX() - lLeft.getX() ) >= 0 ) );

        bool withLowerLeftPoint = ( ( lLeft.getY() < o.uRight.getY()   and
                                      lLeft.getY() > o.lRight.getY() ) and
                                ( ( o.lRight.getX() - lLeft.getX() ) >= 0 ) );

        bool isOnRight = lLeft.getX() > o.center.getX() and lLeft.getX() < lRight.getX();

        if ( (withBothLeftPoints or withLowerLeftPoint or withUpperLeftPoint) and isOnRight )
            return true;

        else
            return false;
    }
}

bool Detectable:: detectFromTop( Detectable & o )
{
    if ( this->isBiggerThan( &o ) == 1 )
    {
        return o.detectFromBottom( *this );
    }
    else
    {

        bool withBothLowerPoints = ( ( lLeft.getX()  >= o.uLeft.getX()       and
                                       lRight.getX() <= o.uRight.getX() )    and
                                  (( o.uLeft.getY()  - lLeft.getY() )  >= 0 and
                                   ( o.uRight.getY() - lRight.getY() ) >= 0 ) );

        bool withLowerRightPoint = ( ( lRight.getX() >= o.uLeft.getX() and
                                   lRight.getX() <= o.uRight.getX() )  and
                               ((o.uRight.getY() - lRight.getY()) >= 0  ) );

        bool withLowerLeftPoint = ( ( lLeft.getX()  >= o.uLeft.getX()   and
                                     lLeft.getX()  <= o.uRight.getX() ) and
                                 ((o.uLeft.getY() - lLeft.getY() ) >= 0) );

        bool isAbove = lLeft.getY() > o.center.getY() and lLeft.getY() <= o.uLeft.getY() and
                       lRight.getY() > o.center.getY() and lRight.getY() <= o.uRight.getY();

        if (  ( withBothLowerPoints or withLowerLeftPoint or withLowerRightPoint ) and isAbove )
            return true;

        else
            return false;

    }
}

bool Detectable:: detectFromBottom( Detectable & o )
{
    if ( this->isBiggerThan( &o ) == 1 )
        return o.detectFromTop( *this );

    else
    {
        bool withBothUpperPoints = ( ( uLeft.getX() > o.lLeft.getX()          and
                                       uRight.getX() < o.lRight.getX() )      and
                                   ( ( uLeft.getY() - o.lLeft.getY() ) >= 0   and
                                     ( uRight.getY() - o.lRight.getY() ) >= 0 ) );

        bool withUpperLeftPoint = ( ( uLeft.getX() > o.lLeft.getX()    and
                                      uLeft.getX() < o.lRight.getX() ) and
                                   (( uLeft.getY() - o.lLeft.getY() ) >= 0 )) ;

        bool withUpperRightPoing = ( ( uRight.getX() > o.lLeft.getX()   and
                                      uRight.getX() < o.lRight.getX() ) and
                                    ((uRight.getY() - o.lRight.getY() ) >= 0 ) );

        bool isBelow = uLeft.getY() < o.center.getY() and uLeft.getY() >= o.lLeft.getY() and
                       uRight.getY() < o.center.getY() and uRight.getY() >= o.lRight.getY();

        if ( ( withBothUpperPoints or withUpperLeftPoint or withUpperRightPoing )  and isBelow )
            return true;

        else
            return false;
    }
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
// DOUBLE SIDED DETECTION FUNCTIONS

int Detectable:: detectFromTopAndLeft( Detectable & o )
{
    if ( this->isBiggerThan( &o ) == 3 )
        return o.detectFromBottomAndRight( *this );

    bool lowerRightDetected = false;
    bool lowerLeftDetected = false;
    bool upperRightDetected = false;

    lowerRightDetected = (lRight.getX() >= o.lLeft.getX() &&
                         lRight.getX() < o.lRight.getX() &&
                          lRight.getY() <= o.uRight.getY() &&
                          lRight.getY() > o.lRight.getY());

    lowerLeftDetected = (lLeft.getX() >= o.lLeft.getX() &&
                          lLeft.getX() < o.lRight.getX() &&
                          lLeft.getY() <= o.uRight.getY() &&
                          lLeft.getY() > o.lRight.getY());

    upperRightDetected = (uRight.getX() >= o.lLeft.getX() &&
                          uRight.getX() < o.lRight.getX() &&
                          uRight.getY() < o.uRight.getY() &&
                          uRight.getY() > o.lRight.getY());

    //If his lower left is in the box, then there's no way he could've hit the right side
    if(lowerLeftDetected)
    {
        return TOP_DETECTED;
    }
    //If the upper right is detected, then it is for sure not landing on the object.
    if( upperRightDetected )
    {
        return LEFT_DETECTED;
    }
    if(lowerRightDetected)
    {
        //If the right side is in more than it is in downwards, then assume it hit from the top.
        if ( ( o.uLeft.getY() - lRight.getY() ) > ( lRight.getX() - o.uLeft.getX() ) )
        {
            return LEFT_DETECTED;
        }
        else
        {
            return TOP_DETECTED;
        }
    }

    //If nothing hit, return NOTING_DETECTED so no moving gets done.
    return NOTHING_DETECTED;
}

int Detectable:: detectFromTopAndRight( Detectable & o )
{
    if ( this->isBiggerThan( &o ) == 3 )
        return o.detectFromBottomAndLeft( * this );

        bool lowerRightDetected = false;
        bool lowerLeftDetected = false;
        bool upperLeftDetected = false;

        lowerRightDetected = (lRight.getX() > o.lLeft.getX() &&
                          lRight.getX() < o.lRight.getX() &&
                          lRight.getY() <= o.uRight.getY() &&
                          lRight.getY() >= o.lRight.getY());

        lowerLeftDetected = (lLeft.getX() > o.lLeft.getX() &&
                          lLeft.getX() < o.lRight.getX() &&
                          lLeft.getY() < o.uRight.getY() &&
                          lLeft.getY() >  o.lRight.getY());

        upperLeftDetected = (uLeft.getX() > o.lLeft.getX() &&
                          uLeft.getX() < o.lRight.getX() &&
                          uLeft.getY() <= o.uRight.getY() &&
                          uLeft.getY() > o.lRight.getY());

       if( lowerRightDetected )
       {
           return TOP_DETECTED;
       }
       if( upperLeftDetected )
       {
           return RIGHT_DETECTED;
       }
       if(lowerLeftDetected)
       {
           if ( ( o.uRight.getY() - lLeft.getY() ) < ( o.uRight.getX() - lLeft.getX() ) )
           {
               return TOP_DETECTED;
           }
           else if ( ( o.uRight.getY() - lLeft.getY() ) > ( o.uRight.getX() - lLeft.getX() ) )
           {
               return RIGHT_DETECTED;
           }
       }
       return NOTHING_DETECTED;
}

int Detectable:: detectFromBottomAndLeft( Detectable & o )
{
    if ( this->isBiggerThan( &o ) == 3 )
        return o.detectFromTopAndRight( *this );

    bool upperRightDetected = false;
    bool upperLeftDetected = false;
    bool lowerRightDetected = false;

    upperRightDetected = (uRight.getX() > o.lLeft.getX() &&
                      uRight.getX() < o.lRight.getX() &&
                      uRight.getY() <= o.uRight.getY() &&
                      uRight.getY() >= o.lRight.getY());

    upperLeftDetected = (uLeft.getX() > o.lLeft.getX() &&
                      uLeft.getX() < o.lRight.getX() &&
                      uLeft.getY() <= o.uRight.getY() &&
                      uLeft.getY() >= o.lRight.getY());

    lowerRightDetected = (lRight.getX() > o.lLeft.getX() &&
                      lRight.getX() < o.lRight.getX() &&
                      lRight.getY() <= o.uRight.getY() &&
                      lRight.getY() >= o.lRight.getY());

    if(upperLeftDetected)
    {
        return BOTTOM_DETECTED;
    }
    if(lowerRightDetected)
    {
        return LEFT_DETECTED;
    }
    if(upperRightDetected)
    {
        if (  ( uRight.getY() - o.lRight.getY()) < ( uRight.getX() - o.lLeft.getX() ) )
        {
            return BOTTOM_DETECTED;
        }
        else if ( ( uRight.getY() - o.lRight.getY() ) > ( uRight.getX() - o.lLeft.getX() ) )
        {
            return LEFT_DETECTED;
        }
    }

    return NOTHING_DETECTED;
}

int Detectable:: detectFromBottomAndRight( Detectable & o )
{
    if ( this->isBiggerThan( &o ) == 3 )
        return o.detectFromTopAndLeft( *this );

       bool upperRightDetected = false;
       bool upperLeftDetected = false;
       bool lowerLeftDetected = false;

       upperRightDetected = (uRight.getX() >  o.lLeft.getX()  &&
                             uRight.getX() <  o.lRight.getX() &&
                             uRight.getY() <= o.uRight.getY() &&
                             uRight.getY() >= o.lRight.getY() );

       upperLeftDetected = (uLeft.getX() >  o.lLeft.getX()  &&
                            uLeft.getX() <  o.lRight.getX() &&
                            uLeft.getY() <= o.uRight.getY() &&
                            uLeft.getY() >= o.lRight.getY() );

        lowerLeftDetected = (lLeft.getX() >  o.lLeft.getX()  &&
                             lLeft.getX() <  o.lRight.getX() &&
                             lLeft.getY() <= o.uRight.getY() &&
                             lLeft.getY() >= o.lRight.getY() );

       if(upperRightDetected)
       {
            return BOTTOM_DETECTED;
       }
       if(lowerLeftDetected)
       {
            return RIGHT_DETECTED;
       }
       else if(upperLeftDetected)
       {
           if ( ( uLeft.getY() - o.lRight.getY() ) < ( o.lRight.getX() - uLeft.getX() ) )
           {
               return BOTTOM_DETECTED;
           }
           else if ( ( uLeft.getY() - o.lRight.getY() ) > ( o.lRight.getX() - uLeft.getX() ) )
           {
               return RIGHT_DETECTED;
           }
       }

       return NOTHING_DETECTED;
}

////////////////////////////

int Detectable:: isBiggerThan( Detectable* o )
{
    if (  height > o->height and  width > o->width )
        return 3;
    else if ( width > o->width )
        return 1;

    else if ( height > o->height )
        return 2;

    else
        return 0;
}

string Detectable::getType()
{
    return type;
}
