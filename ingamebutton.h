#ifndef __IN_GAME_BUTTON_H__
#define __IN_GAME_BUTTON_H__

#include "detectable.h"
#include "resourcemgr.h"
#include "animationmgr.h"
#include "point.h"
#include "trigger.h"
#include "levelentities.h"
#include <string>

class InGameButton
    :public LevelEntities, public Trigger
{
    private:
        ResourceMgr*        resourceMgr;
        AnimationMgr*       animationMgr;
        CurrentStateNode*   animationId;
        bool                pressed;
        string              target;

    public:
        InGameButton( Point ul, string target );
        ~InGameButton();
        void press();
        void unPress();
        void draw();
};
#endif
