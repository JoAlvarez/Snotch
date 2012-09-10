#include "powers.h"
#include "global.h"

#define PUSH_POWER_SPEED 600

Powers::Powers(string type, Point ul, double width , double height, double mass, double damage , int angle, bool facingRight)
    :Physics(ul, width, height, mass)
{
    power = type;
    this->damage = damage;
    this->angle = angle;
    this->facingRight = facingRight;
    xVel = PUSH_POWER_SPEED * cos(angle * DEGREES_TO_RAD);
    yVel = PUSH_POWER_SPEED * sin(angle * DEGREES_TO_RAD);
}
void Powers::init()
{
     Physics::init();
     resourceMgr->loadImage("./data/images/push.png", "push");
     resourceMgr->loadImage("./data/images/fireball.png","fireball");
}

void Powers::update()
{

    Physics::move();
}
void Powers::draw()
{
    if(power == "push")
    {
        glColor4f(1, 1, 1, 0.8);

        resourceMgr->drawImage("push", angle, uLeft.getX(), uLeft.getX() + 50,
                               uLeft.getY() - 60, uLeft.getY());
    }
    if(power == "fireball")
    {
        resourceMgr->drawImage("fireball", angle,uLeft.getX(), uLeft.getX() + 30,
                               uLeft.getY() - 30, uLeft.getY());
    }
    if(power == "spike")
    {

    }
    glColor4f(1,1,1,1);
}

void Powers::release()
{
    window->release();
}

Point Powers::getPos()
{
    return uLeft;
}

int Powers::getAngle()
{
    return angle;
}

string Powers::getType()
{
    return power;
}
