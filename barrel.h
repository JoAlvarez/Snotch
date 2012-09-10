#ifndef __BARREL_H__
#define __BARREL_H__

#include "physics.h"
#include "animationmgr.h"
class Barrel
    :public Physics
{
    private:

        double hp;
        bool blown;

        Timer t;

        AnimationMgr* animationMgr;

    public:

        Barrel(Point,double,double,double);

        void init();
        void draw();
        void update();
        void release();
        void hit(double);
        int timePassed();
        bool isBlown();
};

#endif
