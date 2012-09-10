#ifndef __LIVES_BAR_H__
#define __LIVES_BAR_H__

#include "draggable.h"
#include "resourcemgr.h"

#define LIFE_IMAGE_WIDTH            52.0
#define LIFE_IMAGE_HEIGHT           64.0
#define LIFE_IMAGE_TOTAL_WIDTH      64.0
#define LIFE_IMAGE_TOTAL_HEIGHT     64.0
#define LIFE_IMAGE_PADDING          15.0
#define LIFE_DEFAULT_UL_X           0.0
#define LIFE_DEFAULT_UL_Y           750.0
#define LIFE_TEXT_ALIAS             "life_text"
#define LIFE_MAX_DISPLAY            4.0

class LivesBar
    :private Draggable
{
    private:
        ResourceMgr*    resourceMgr;
        Window*         window;
        bool            locked;

    public:
        LivesBar();
        ~LivesBar();
        void    lock();
        void    unLock();
        void    update();
        void    draw( int lives );
};

#endif
