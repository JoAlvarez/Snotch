#include "physics.h"
#include "global.h"

Physics::Physics()
    :Detectable()
{
    mass = 0;
    xVel = 0;
    yVel = 0;
    inAir = false;
    friction = 200.0;
    elasticity = 0.4;
    goThroughPlatform = false;
}

Physics::Physics(Point ul, double wid, double h, double m)
    :Detectable( ul , Point( ul.getX() + wid, ul.getY() - h ) )
{
    mass = m;
    xVel = 0;
    yVel = 0;
    inAir = false;
    friction = 200.0;
    elasticity = 0.4;
    goThroughPlatform = false;
}

void Physics::init()
{
    window = Window::getInstance();
    resourceMgr = ResourceMgr::getInstance();
}

void Physics::destroy()
{
    window->release();
    resourceMgr->release();
}

Physics::Physics(Point center, double rad, double m)
    :Detectable(center, rad)
{
    width = rad;
    mass = m;
    type = "circle";
    window = Window::getInstance();
    xVel = 0;
    yVel = 0;
    inAir = false;
    friction = 200.0;
}

void Physics::update()
{
    move();
    if(!inAir)
    {
        if(xVel < 0)
        {
            xVel += mass * friction * window->timeSinceLastFrame();
            if(xVel > 0)
                xVel = 0;
        }
        else if(xVel > 0)
        {
            xVel -= mass * friction * window->timeSinceLastFrame();
            if(xVel < 0)
                xVel = 0;
        }
    }
    if(inAir)
        yVel += GRAVITY * window->timeSinceLastFrame();


}

double Physics::getElasticity()
{
    return elasticity;
}

void Physics::move()
{
    double xMove = xVel * window->timeSinceLastFrame();
    double yMove = yVel * window->timeSinceLastFrame();

    uLeft.move(xMove, yMove);
    uRight.move(xMove, yMove);
    lLeft.move(xMove, yMove);
    lRight.move(xMove, yMove);
    center.move(xMove, yMove);
}
void Physics::transferEnergy(double force, double angle)
{
    if(angle != 90 && angle != 270)
        xVel += force/mass * cos(angle * DEGREES_TO_RAD);

    if(angle != 180 && angle != 0)
        yVel += force/mass * sin(angle * DEGREES_TO_RAD);

    if(angle > 0 && angle < 180)
        inAir = true;
}

double Physics:: getXVel()
{
    return xVel;
}

double Physics:: getYVel()
{
    return yVel;
}

void Physics:: setYVel( double yV )
{
    yVel = yV;
}

void Physics:: setXVel ( double xV )
{
    xVel = xV;
}

void Physics::setInAir(bool newInAir)
{
    inAir = newInAir;
}
void Physics::addVel(double xVel, double yVel)
{
    this->xVel +=xVel;
    this->yVel +=yVel;
    if(yVel > 0)
        inAir = true;
}
void Physics::setFriction(double fric)
{
    friction = fric;
}
double Physics::getFriction()
{
    return friction;
}

bool Physics::canGoThroughPlatform()
{
    return goThroughPlatform;
}

void Physics::radialForce(Physics* ph, double distance, double power)
{
    int d = distBetween(center, ph->center);
    if(d >distance)
        return;
    else
    ph->transferEnergy(power*(distance-d)/distance,calcAngle(center,ph->center)* RAD_TO_DEGREES);
}

bool Physics::getInAir()
{
    return inAir;
}
