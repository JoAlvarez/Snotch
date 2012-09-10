#include "enemy.h"
#include "global.h"
#include "filenames.h"

    #define TURTLE_WALK_SPEED       550.0
    #define TURTLE_MAX_XVEL         150.0
    #define AI_RUNNING_SPEED        20.0
    #define AI_DETECT_RANGE         800.0
    #define AI_VERT_RANGE           800.0
    #define AI_JUMP_FORCE           7000.0


Turtle::Turtle()
    : AI()
{

    currentState = "idle";

}

void Turtle::runAI()
{
    if(wasWalking and (prevX == uLeft.getX() or (snotch->lRight.getY() > uRight.getY() ) ))
    {

       if( yVel == 0 and canJump )
        {

            if( inAir )
                canJump = false;

            inAir = true;
            yVel = AI_JUMP_FORCE / mass;


        }


    }
    wasWalking = false;
    calcState();

    if ( currentState == "idle" )
    {



    }

    else if ( currentState == "follow" )
    {

        if((snotch->getPos()).getX() - (uLeft.getX() + AI_DETECT_RANGE) < 0 and
            (snotch->getPos()).getX() - (uLeft.getX() + AI_DETECT_RANGE) > -AI_DETECT_RANGE)
        {
            if(xVel <= TURTLE_MAX_XVEL)
            {
                xVel += TURTLE_WALK_SPEED * 10 * window->timeSinceLastFrame();
                if(xVel > TURTLE_MAX_XVEL)
                    xVel = TURTLE_MAX_XVEL;


            }
            if( inAir )
                {

                    if( yVel == 0 and canJump )
                    {
                        if( inAir )
                            canJump = false;

                        inAir = true;
                        yVel = AI_JUMP_FORCE / mass;

                    }
                }

        }

        else if ( (snotch->getPos()).getX() - (uLeft.getX() - AI_DETECT_RANGE) > 0 and
                   (snotch->getPos()).getX() - (uLeft.getX() - AI_DETECT_RANGE) < AI_DETECT_RANGE )
        {
            if(xVel >= -TURTLE_MAX_XVEL)
            {
                xVel += -TURTLE_WALK_SPEED * 10 * window->timeSinceLastFrame();
                if(xVel < -TURTLE_MAX_XVEL)
                    xVel = -TURTLE_MAX_XVEL;


            }
            if( inAir )
                {

                    if( yVel == 0 and canJump )
                    {
                        if( inAir )
                            canJump = false;

                        inAir = true;
                        yVel = AI_JUMP_FORCE / mass;

                    }
                }

        }


    }



    /*else if ( currentState == "reset" )
    {
        uLeft = initLoc;
        uRight = Point(initLoc.getX() + width, initLoc.getY());
        lLeft = Point(initLoc.getX(), initLoc.getY() - height);
        lRight = Point(initLoc.getX() + width, initLoc.getY() - height);
    }*/

    prevX = uLeft.getX();

    AI::update();
    if( currentState == "follow" )
        {
            wasWalking = true;

        }
    if(!inAir)
        canJump = true;
    else
        canJump = false;


}

void Turtle::calcState()
{

        bool isInVerticalRange = (snotch->center.getY() < (center.getY() + AI_VERT_RANGE) and snotch->center.getY() > (center.getY() - AI_VERT_RANGE) );
        bool isRangeRight = (snotch->center.getX() < (center.getX() + AI_DETECT_RANGE) and snotch->center.getX() >= (center.getX() - 100));
        bool isRangeLeft = (snotch->center.getX() > (center.getX() - AI_DETECT_RANGE) and snotch->center.getX() <= (center.getX() + 100));
        bool isBehindEnemyOnRight = (snotch->center.getX() > center.getX() and snotch->center.getX() < center.getX() + 200);
        bool isBehindEnemyOnLeft = (snotch->center.getX() < center.getX() and snotch->center.getX() > center.getX() - 200);
        bool isLeftInside = ( (snotch->getPos()).getX() > uLeft.getX() and (snotch->getPos()).getX() < lRight.getX() );
        bool isRightInside = ( (snotch->lRight.getX()) < lRight.getX() and (snotch->lRight.getX()) > uLeft.getX() );


    if( isLeftInside or isRightInside)
    {
        currentState = "idle";
    }


    if( facingRight and ( isInVerticalRange and isRangeRight))
    {

        if(isBehindEnemyOnLeft)
            facingRight = false;
        bool isLeftInside = ( (snotch->getPos()).getX() > uLeft.getX() and (snotch->getPos()).getX() < lRight.getX() );
        bool isRightInside = ( (snotch->lRight.getX()) < lRight.getX() and (snotch->lRight.getX()) > uLeft.getX() );

        if( isLeftInside or isRightInside)
        {
            currentState = "idle";
        }
        else
            currentState = "follow";
    }

    else if(!facingRight and ( isInVerticalRange and isRangeLeft))
    {


        if(isBehindEnemyOnRight)
            facingRight = true;

        bool isLeftInside = ( (snotch->getPos()).getX() > uLeft.getX() and (snotch->getPos()).getX() < lRight.getX() );
        bool isRightInside = ( (snotch->lRight.getX()) < lRight.getX() and (snotch->lRight.getX()) > uLeft.getX() );



        if( isLeftInside or isRightInside)
        {
            currentState = "idle";
        }
        else
            currentState = "follow";
    }

    else
        currentState = "idle";


    //sets state to initial if enemy leaves the screen
   /* if ( uLeft.getX() < window->leftCoord() - 200 || uLeft.getX()  > window->rightCoord() + 200 )
    {
        currentState = "reset";
    }*/

    //Handle animation states
    if( currentState == "follow" )
        animationState = "walk";
    else
        animationState = "idle";

    if( inAir )
    {
        if( yVel > 0 )
            animationState = "inAirUp";
        else
            animationState = "inAirDown";
    }


    //Set animation and correct its size
    animationMgr->setAnimation( animationId, animationState, "loop" );
    AI::adjustSize();

    //update animation

    animationMgr->update( animationId );



}

void Turtle::init()
{
    AI::init();
    resourceMgr->loadImage( FILE_EKIS , "ekis" );
    animationId = animationMgr->newAnimation( "ekis" );
    animationMgr->setScale( animationId, 2.0, 2.0 );
}

void Turtle::draw()
{
    //Find the direction the enemy is facing



    //draw animation


        animationMgr->draw( animationId, facingRight, uLeft );

    /*glBegin(GL_POINTS);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(uLeft.getX(), uLeft.getY());
        glColor3f(1.0,0.0,0.0);
        glVertex2f(uRight.getX(), uRight.getY());
        glColor3f(0.0,1.0,0.0);
        glVertex2f(lRight.getX(), lRight.getY());
        glColor3f(0.0,0.0,1.0);
        glVertex2f(lLeft.getX(), lLeft.getY());
    glEnd();*/
    glColor3f(1.0,1.0,1.0);
}
