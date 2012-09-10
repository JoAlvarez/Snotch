#ifndef __COOL_DOWN_H__
#define __COOL_DOWN_H__

#include <gl/gl.h>
#include "window.h"
#include "point.h"

class Cooldown
{
    private:
        Window* window;
        bool phase1, phase2, phase3, phase4, end;
        Point phase1pt, phase2pt, phase3pt, phase4pt, phase5pt;
        double midX, midY, leftX, rightX, upperY, lowerY;
        double begin;

    public:
        Cooldown();
        void init();
        void update();
        void draw( );
        void start( double, double, double, double, double );
        bool isEnd();
        ~Cooldown();
};
#endif
