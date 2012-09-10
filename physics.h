#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "detectable.h"
#include "point.h"
#include <string>
#include "window.h"
#include "resourcemgr.h"
#include <cmath>
#include "mathfunctions.h"
using namespace std;

class Physics
    :public Detectable
{
    protected:

        double mass;
        double xVel;
        double yVel;
        double friction;
        double elasticity;
        bool inAir;
        bool goThroughPlatform;

        Window* window;
        ResourceMgr* resourceMgr;

    public:

        Physics();
        Physics(Point, double, double, double);
        Physics(Point, double, double);

        virtual void init() = 0;
        void update();
        void move();
        void destroy();

        void transferEnergy(double, double);
        void setYVel( double );
        void setXVel( double );
        void setInAir(bool);
        void addVel(double, double);
        void setFriction(double);
        void radialForce(Physics*, double, double);

        double getElasticity();
        double getFriction();
        double getXVel();
        double getYVel();

        bool canGoThroughPlatform();
        bool getInAir();
};

#endif
