#ifndef __DOOR_H__
#define __DOOR_H__

#include "point.h"
#include "triggerable.h"
#include "resourcemgr.h"
#include "window.h"
#include "levelentities.h"

#define DOOR_OPEN_SPEED 50

class Door
    :public Triggerable, public LevelEntities
{
    private:
        Point           origUl;
        Point           origLr;
        ResourceMgr*    resourceMgr;
        Window*         window;

    public:
        Door();
        Door( Point ul, Point lr, string texture, string name );
        void trigger();
        void unTrigger();
        void draw();


};

#endif
