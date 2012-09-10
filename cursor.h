#ifndef __CURSOR_H__
#define __CURSOR_H__

#include "resourcemgr.h"
#include "input.h"
#include "window.h"

class Cursor
{
    private:
        ResourceMgr* resourceMgr;
        Window* window;
        Input* input;
        bool shown;

    public:
        Cursor();
        void init();
        void draw();
        void setShown( bool );
        bool isShown();
        ~Cursor();
};

#endif //__CURSOR_H__
