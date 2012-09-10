#include "barrel.h"

Barrel::Barrel(Point ul, double width, double height, double mass)
   :Physics(ul, width, height, mass)
{
    blown = 0;
    hp = 100;
    type = "BLOCK";
    animationMgr = AnimationMgr::getInstance();
}

void Barrel::init()
{
    Physics::init();
}
void Barrel::draw()
{
    resourceMgr->drawImage("barrel", uLeft.getX(), uRight.getX(), lLeft.getY(), uLeft.getY());
}
void Barrel::release()
{
    window->release();
    animationMgr->release();
}
void Barrel::update()
{
    Physics::update();
    if(t.getTimePassed() >= 100)
        blown = true;
}

void Barrel::hit(double damage)
{
    if(blown)
        return;
    hp -= damage;
    if(hp <= 0 && t.getTimePassed() == 0)
        t.start();
}
bool Barrel::isBlown()
{
    return blown;
}

int Barrel::timePassed()
{
        return t.getTimePassed();
}
