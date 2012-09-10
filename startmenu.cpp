#include "startmenu.h"
#include <time.h>

#define MENU_X_MOVEMENT_SPEED 30

StartMenu::StartMenu()
{
    srand( time(NULL) );
    inMenu = false;
    begin = true;
    newXCoord       = ( rand() % 100 ) + 320;
    loadXCoord      = ( rand() % 100 ) + 320;
    optionsXCoord   = ( rand() % 100 ) + 320;
    quitXCoord      = ( rand() % 100 ) + 320;
    newTarX         = ( rand() % 100 ) + 320;
    loadTarX        = ( rand() % 100 ) + 320;
    optionsTarX     = ( rand() % 100 ) + 320;
    quitTarX        = ( rand() % 100 ) + 320;
}

void StartMenu::init()
{
    resourceMgr = ResourceMgr::getInstance();
    input = Input::getInstance();
    window = Window::getInstance();
    resourceMgr->loadFont( "./data/fonts/arial.ttf", "font", 42 );
    resourceMgr->loadImage( "./data/images/startmenubg1.png", "bgpattern1" );
    resourceMgr->loadImage( "./data/images/title.png", "title" );
}

void StartMenu::checkInput()
{
    //If esc is pressed, open menu.
    if( input->getKeyInput() == "s" )
    {
        if( begin == false && inMenu == true )
            inMenu = false;
    }

    for( unsigned int i = 0; i < 4; ++i )
    {
        if( clickableObjects[0].isClicked() )
            inMenu = false;
        if( clickableObjects[3].isClicked() )
            exit( 0 );
    }
}


void StartMenu::update()
{
    //New game movement
    if( newXCoord < newTarX )
    {
        newXCoord += MENU_X_MOVEMENT_SPEED * window->timeSinceLastFrame();
        if( newXCoord > newTarX )
            newTarX = newXCoord;

    }
    else if( newXCoord > newTarX )
    {
        newXCoord += -MENU_X_MOVEMENT_SPEED * window->timeSinceLastFrame();
        if( newXCoord < newTarX )
            newTarX = newXCoord;
    }
    else
        newTarX   = ( rand() % 100 ) + 320;

    //Load movement
    if( loadXCoord < loadTarX )
    {
        loadXCoord += MENU_X_MOVEMENT_SPEED * window->timeSinceLastFrame();
        if( loadXCoord > loadTarX )
            loadTarX = loadXCoord;

    }
    else if( loadXCoord > loadTarX )
    {
        loadXCoord += -MENU_X_MOVEMENT_SPEED * window->timeSinceLastFrame();
        if( loadXCoord < loadTarX )
            loadTarX = loadXCoord;
    }
    else
        loadTarX   = ( rand() % 100 ) + 320;

    //Options movement
    if( optionsXCoord < optionsTarX )
    {
        optionsXCoord += MENU_X_MOVEMENT_SPEED * window->timeSinceLastFrame();
        if( optionsXCoord > optionsTarX )
            optionsTarX = optionsXCoord;

    }
    else if( optionsXCoord > optionsTarX )
    {
        optionsXCoord += -MENU_X_MOVEMENT_SPEED * window->timeSinceLastFrame();
        if( optionsXCoord < optionsTarX )
            optionsTarX = optionsXCoord;
    }
    else
        optionsTarX   = ( rand() % 100 ) + 320;

    //Quit movement
    if( quitXCoord < quitTarX )
    {
        quitXCoord += MENU_X_MOVEMENT_SPEED * window->timeSinceLastFrame();
        if( quitXCoord > quitTarX )
            quitTarX = quitXCoord;

    }
    else if( quitXCoord > quitTarX )
    {
        quitXCoord += -MENU_X_MOVEMENT_SPEED * window->timeSinceLastFrame();
        if( quitXCoord < quitTarX )
            quitTarX = quitXCoord;
    }
    else
        quitTarX   = ( rand() % 100 ) + 320;

    for( unsigned int i = 0; i < 4; ++i )
    {
        if( i == 0 )
            clickableObjects[i] = Clickable( Point( newXCoord, ( window->bottomCoord() + 440 ) - ( i * 40 ) ),
                                             Point( newXCoord + NEW_GAME , ( window->bottomCoord() + 400 ) - ( i * 40 ) ) );
        else if( i == 1 )
            clickableObjects[i] = Clickable( Point( loadXCoord, ( window->bottomCoord() + 440 ) - ( i * 40 ) ),
                                             Point( loadXCoord + LOAD, ( window->bottomCoord() + 400 ) - ( i * 40 ) ) );
        else if( i == 2 )
            clickableObjects[i] = Clickable( Point( optionsXCoord, ( window->bottomCoord() + 440 ) - ( i * 40 ) ),
                                             Point( optionsXCoord + OPTIONS, ( window->bottomCoord() + 400 ) - ( i * 40 ) ) );
        else
            clickableObjects[i] = Clickable( Point( quitXCoord, ( window->bottomCoord() + 440 ) - ( i * 40 ) ),
                                             Point( quitXCoord + QUIT, ( window->bottomCoord() + 400 ) - ( i * 40 ) ) );
    }
}

void StartMenu::draw()
{
    if( !inMenu && begin )
    {
        inMenu = true;
        begin = false;
    }

    if( inMenu && !begin )
    {
        resourceMgr->drawImage( "bgpattern1",
                                window->leftCoord(),
                                window->rightCoord(),
                                window->bottomCoord(),
                                window->topCoord() );


        resourceMgr->drawImage( "title",
                                window->leftCoord() + 240,
                                window->leftCoord() + 752,
                                window->bottomCoord() + 250,
                                window->bottomCoord() + 762 );

        resourceMgr->drawText( "font", "NEW GAME",
                               newXCoord,
                               window->bottomCoord() + 400 );
        resourceMgr->drawText( "font", "LOAD GAME",
                               loadXCoord,
                               window->bottomCoord() + 360 );
        resourceMgr->drawText( "font", "OPTIONS",
                               optionsXCoord,
                               window->bottomCoord() + 320 );
        resourceMgr->drawText( "font", "QUIT",
                               quitXCoord,
                               window->bottomCoord() + 280 );

        //Hover Indicator.
        for( unsigned int i = 0; i < 4; ++i )
        {
            glColor3f( 0, 0.8, 1 );
            if( clickableObjects[0].isMouseOver() )
            {
                resourceMgr->drawText( "font", "NEW GAME",
                                       newXCoord,
                                       window->bottomCoord() + 400 );
            }
            if( clickableObjects[1].isMouseOver() )
            {
                resourceMgr->drawText( "font", "LOAD GAME",
                                       loadXCoord,
                                       window->bottomCoord() + 360 );
            }
            if( clickableObjects[2].isMouseOver() )
            {
                resourceMgr->drawText( "font", "OPTIONS",
                                       optionsXCoord,
                                       window->bottomCoord() + 320 );
            }
            if( clickableObjects[3].isMouseOver() )
            {
                resourceMgr->drawText( "font", "QUIT",
                                       quitXCoord,
                                       window->bottomCoord() + 280 );
            }
            glColor3f( 1, 1, 1 );

        }
    }
}

bool StartMenu::isGameStart()
{
    return begin;
}

bool StartMenu::isMenuOpen()
{
    return inMenu;
}

StartMenu::~StartMenu()
{
    input->release();
    window->release();
    resourceMgr->release();
}
