#ifndef __OPTIONS_MENU_H__
#define __OPTIONS_MENU_H__
#include "clickable.h"
#define NUM_BUTTONS 5

class OptionsMenu
{
    public:
        Clickable   clickableObjs[ NUM_BUTTONS ];

    public:
        OptionsMenu();
        OptionsMenu( Point, Point, string );
        void draw();
        void init();
        bool isMenuOpen();
        void setuL( Point );
        void setlR( Point );
        void setColor( string );
};

#endif
