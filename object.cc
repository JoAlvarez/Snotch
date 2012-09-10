#include "object.h"
#include "global.h"
Object::Object()
    :Physics()
{
    type = "BOX";
    inAir = false;
}
Object::Object(string type, Point ul, double width, double height, double mass)
    :Physics(ul, width, height, mass)
{
    this->type = type;
}
void Object::draw()
{
    if(type == "BOX")
        resourceMgr->drawImage("crate", uLeft.getX(), uRight.getX(), lLeft.getY(), uLeft.getY());
    if(type == "health")
        resourceMgr->drawImage("health", uLeft.getX(), uRight.getX(), lLeft.getY(), uLeft.getY());
}
void Object::init()
{
    Physics::init();
}

void Object::update()
{
    Physics::update();
}

void Object::release()
{
    window->release();
}
string Object::getType()
{
    return type;
}
