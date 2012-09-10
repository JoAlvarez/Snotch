#ifndef __START_MENU_H__
#define __START_MENU_H__

#include <gl/gl.h>
#include "point.h"
#include "input.h"
#include "resourcemgr.h"
#include "clickable.h"

#define NEW_GAME 310
#define LOAD 330
#define OPTIONS 250
#define QUIT 130

class StartMenu
{
    private:
        bool inMenu;
        Input* input;
        Window* window;
        ResourceMgr* resourceMgr;
        Clickable clickableObjects[4];
        double fade;
        bool begin;
        double newXCoord;
        double loadXCoord;
        double optionsXCoord;
        double quitXCoord;
        double newTarX;
        double loadTarX;
        double optionsTarX;
        double quitTarX;

    public:
        StartMenu();
        void init();
        void checkInput();
        void draw();
        void update();
        bool isGameStart();
        bool isMenuOpen();
        ~StartMenu();
};

#endif
