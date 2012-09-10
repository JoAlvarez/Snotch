#ifndef __HEALTH_BAR_H__
#define __HEALTH_BAR_H__

#include "resourcemgr.h"
#include "draggable.h"
#include "window.h"

class HealthBar
    :public Draggable
{
    private:
        double          totalWidth;
        double          totalHeight;
        double          drawnWidth;
        double          drawnHeight;
        bool            locked;
        ResourceMgr*    resourceMgr;

    public:
        HealthBar();
        ~HealthBar();
        void    unLock();
        void    lock();
        void    update();
        void    draw( double healthPercentage );
};

#endif
