#ifndef __DRAGGABLE_H__
#define __DRAGGABLE_H__

#include "clickable.h"
class Draggable
    :public Clickable
{
    private:
        Point   origMouseLoc;
        Point   newMouseLoc;
        bool    draggable;

    public:
        Draggable();
        Draggable( Point upperLeft, Point upperRight );
        void update();
};

#endif
