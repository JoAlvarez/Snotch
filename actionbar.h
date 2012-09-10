#ifndef __ACTIONBAR_H__
#define __ACTIONBAR_H__

#include "point.h"
#include "input.h"
#include "resourcemgr.h"
#include "filenames.h"
#include "cooldown.h"

#define percentLeftX  .46
#define percentRightX .52
#define percentLowerY .0
#define percentUpperY .08

class ActionBar
{
    private:
        Input* input;
        Window* window;
        ResourceMgr* resourceMgr;
        bool startPushCd;
        Point uL;
        Cooldown* cdTimer;

    public:
        ActionBar();
        void init();
        void checkInput();
        void update();
        void draw();
        ~ActionBar();
};

#endif
