#include "abilities.h"

#define PUSH_POWER_FORCE 10000
#define FIRE_POWER_FORCE 2500
Abilities* Abilities::instance = NULL;
int Abilities::referenceCount = 0;

Abilities::Abilities()
{
}
void Abilities::init()
{
    window = Window::getInstance();
}
void Abilities::usePower(string s, Point ul, int angle, bool facingRight)
{
    if(s == "push")
    {
        power.push_back( new Powers(s,Point(ul.getX(), ul.getY() + 60) , 50,60 , 10,10 , angle, facingRight));
        power[power.size() -1]->init();
    }
    if(s == "fireball")
    {
        power.push_back( new Powers(s,Point(ul.getX(), ul.getY() + 60) , 30,30 , 10,10 , angle, facingRight));
        power[power.size() -1]->init();
    }
    if( s == "spike")
    {
        power.push_back( new Powers(s, Point(ul.getX(),ul.getY() + 60) , 50,60,10,10,angle,facingRight));
        power[power.size() -1]->init();
    }
}
void Abilities::draw()
{
    for(int i = 0; i < power.size(); i++)
        power[i]->draw();
}
void Abilities::release()
{
    for(int i = 0; i < power.size(); i++)
        power[i]->release();
    window->release();
}
void Abilities::update()
{
    for(int i = 0; i < power.size(); i++)
        {
            power[i]->update();
            if(power[i]->getPos().getX() > window->rightCoord()|| power[i]->getPos().getX() < window->leftCoord() ||
               power[i]->getPos().getY() > window->topCoord() || power[i]->getPos().getY() < window->bottomCoord() )
            {
                 delete power[i];
                 power.erase(power.begin()+i);
                 i-=1;
            }
        }
}

void Abilities::checkHit(Physics* obj)
{
   for(int i = 0; i < power.size();i++)
   {
       if(power[i]->didIntersect(obj))
       {
           if(power[i]->getType() == "push")
                obj->transferEnergy(PUSH_POWER_FORCE, power[i]->getAngle());
           if(power[i]->getType() == "fireball")
                obj->transferEnergy(FIRE_POWER_FORCE, power[i]->getAngle());
           delete power[i];
           power.erase(power.begin()+i);
           i-=1;
        }
   }
}

Abilities* Abilities::getInstance()
{
    if(instance == NULL)
    {
        instance = new Abilities();
    }
    ++referenceCount;
    return instance;
}
