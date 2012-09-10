#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "physics.h"

class Object
    :public Physics
{
    private:

    public:

        Object();
        Object(string,Point, double, double, double);

        void init();
        void update();
        void draw();
        void release();

        string getType();
};
#endif
