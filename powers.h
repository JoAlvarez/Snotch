#ifndef __POWERS_H__
#define __POWERS_H__

#include "physics.h"
#include "resourcemgr.h"
#include <vector>
using namespace std;

class Powers
    : public Physics
{
    private:
        string power;
        int angle;
        double damage;
        bool facingRight;

    public:

        Powers(string, Point, double, double, double, double, int, bool);

        void init();
        void update();
        void move();
        void draw();
        void release();

        Point getPos();
        int getAngle();
        string getType();
};
#endif
