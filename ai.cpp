#include "AI.h"

//=======================
AI::AI()
//=======================
    :Physics( Point( 4000.0, 300.0 ), 100, 100, 12 )
{
    initLoc = Point(1000.0, 750.0);
    currentState = "idle";
    health = 100.0;
    armor = 1.0;
    animationId = NULL;
    facingRight = false;
    canJump = true;
    wasWalking = false;
}

AI::AI(Point upperleft, double width, double height, double mass)
    :Physics(upperleft, width, height, mass)
{
    facingRight = false;
    canJump = true;
    wasWalking = false;
    initLoc = upperleft;
    currentState = "idle";
    animationId = NULL;
}

AI::~AI()
{
    animationMgr->removeAnimation( animationId );
    animationMgr->release();
    powers->release();
}

void AI::decreaseHealth(double damage)
{
    health -= damage/armor;
}

void AI::setArmor(double armor)
{
    this->armor = armor;
}


void AI::init()
{
    Physics::init();
    snotch = Snotch::getInstance();
    powers = Abilities::getInstance();
    animationMgr = AnimationMgr::getInstance();
}

void AI::runAI()
{
}

void AI::calcState()
{
}
void AI::draw()
{
}

void AI::update()
{
    Physics::update();
}

void AI::adjustSize()
{
    //Adjusts the positions of all the points based on the
    // size of the current animation with the assumption
    // that the lowerLeft point is the fixed point for the
    // characters movement.
    uRight = animationMgr->getUpperRight( animationId, lLeft );
    lRight = Point( uRight.getX(), lLeft.getY() );
    uLeft  = Point( lLeft.getX(), uRight.getY() );
    center = Point( ( uLeft.getX() + lRight.getX() ) / 2.0  ,
                    ( uLeft.getY() + lRight.getY() ) / 2.0  );

    width  = uRight.getX() - uLeft.getX();
    height = uLeft.getY() - lLeft.getY();
}
