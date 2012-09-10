#ifndef __MENU_H__
#define __MENU_H__

#include <gl/gl.h>
#include "point.h"
#include "input.h"
#include "resourcemgr.h"
#include "clickable.h"
#include "filenames.h"
#include "background.h"

#define FONT_HEIGHT 19
#define PADDING 3
#define OPTIONS_LENGTH 5
#define LOAD_LENGTH 34
#define SAVE_LENGTH 34
#define QUIT_LENGTH 39

class Menu
{
    private:
        bool inMenu;
        Input* input;
        Window* window;
        ResourceMgr* resourceMgr;
        Clickable clickableObjects[6];
        bool soonTemp;
        bool animBox;
        double animBoxdX;
        double animBoxTar;
        Background fog;

        //Animated box behind each menu button.
        void drawBox( double uX, double dX, double uY, double fontHeight )
        {
            glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
            glEnable( GL_BLEND );
            glColor4f( 1, 0, 0, .4 );
            glBegin( GL_QUADS );
                glVertex2f( uX, uY + PADDING );
                glVertex2f( uX + dX, uY + PADDING );
                glVertex2f( uX + dX, ( uY - fontHeight ) - PADDING );
                glVertex2f( uX, ( uY - fontHeight ) - PADDING );
            glEnd();
            glDisable( GL_BLEND );
            glColor3f( 1, 1, 1 );
        }

    public:
        Menu();
        void init();
        void checkInput();
        void draw();
        void update();
        bool isMenuOpen();
        ~Menu();
};

#endif //__MENU_H__
