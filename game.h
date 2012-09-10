///////////////////////////////////////////////////////////////////////////////
// File:                 game.h
//
// Original Author:      Roby Atadero (RA)
//
// Creation Date:        April 29th, 2007
//
// Last Edited:          April 29th, 2007 - Implementation
//
// Purpose:              Header for the Game class that holds the information
//                       for a game and how to control it.
///////////////////////////////////////////////////////////////////////////////

#ifndef __GAME_H__
#define __GAME_H__

#include "window.h"
#include "input.h"
#include "point.h"
#include "mathfunctions.h"
#include "resourcemgr.h"
#include "snotch.h"
#include "ai.h"
#include "enemy.h"
#include "menu.h"
#include "object.h"
#include "barrel.h"
#include "levelobjects.h"
#include "healthbar.h"
#include "livesbar.h"
#include "currentstatenode.h"
#include "animationmgr.h"
#include "ingamebutton.h"
#include "door.h"
#include "abilities.h"
#include "background.h"
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include "cursor.h"
#include "startmenu.h"
#include "actionbar.h"

#include "trigger.h"
#include "triggerable.h"

#define QUIT_SIGNAL_RECEIVED false

//Define all image identifiers here so that it is much easier to
//understand what image is being used in the game class.

class Game
{
  private:

    Window*             window;             //Window that handles all the windowing
                                            //inputs, framerate counting, etc.
    bool                gameover;           //Whether or not the game is now over

    Input*              input;
    ResourceMgr*        resourceMgr;
    Snotch*             snotch;
    StartMenu*          startMenu;
    Menu*               pauseMenu;
    Abilities*          abilities;
    vector<Object*>     objects;
    vector<Barrel*>     barrels;
    vector<AI*>         enemies;
    HealthBar           healthBar;
    LivesBar            livesBar;
    AnimationMgr*       animationMgr;
    CurrentStateNode*   testAnimationId;
    Cursor*             cursor;
    InGameButton*       button;
    Trigger             trigger;
    Background          bg;
    ActionBar*          actionbar;

    double              fpsTime;

    void            checkAbilitiesOnAllEntities();
    void            updateEnemies();
    void            checkTriggers();
    void            updateGameObjects();
    void            updateUI();
    void            levelDetectionChecks();
    void            updateCoordinateSystem();

    void            drawLevel();
    void            drawEnemies();
    void            drawUI();
    void            drawGameObjects();

    void            calcFrameRate();
    void            handleLogic();
    void            renderGame();
    void            checkInput();
    void            addObject(string, int, int, int, Point);
    void            blowBarrel();

    LevelObjects    currentLevel;

    bool showMouseCoords;
    bool    wasFired;

  public:

    Game();

    ~Game();

    void init();

    void play();

};

#endif
