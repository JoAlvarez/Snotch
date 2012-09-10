#include "menu.h"
#include "point.h"
#include <shlobj.h>

#define MENU_X_MOVEMENT_SPEED 600

Menu::Menu()
{
    inMenu = false;
    soonTemp = false;
    animBoxdX = 0;
    animBoxTar = 135;
    animBox = false;
}

void Menu::init()
{
    resourceMgr = ResourceMgr::getInstance();
    input = Input::getInstance();
    window = Window::getInstance();
    resourceMgr->loadFont( "./data/fonts/arial.ttf", "TITLE_FONT", 20 );
    resourceMgr->loadFont( "./data/fonts/arial.ttf", "LINK_FONT", 12 );
	resourceMgr->loadImage( FILE_FOG, "fog" );

    for( unsigned int i = 0; i <= 5; ++i )
    {
        if( i == 5 )
            clickableObjects[i] = Clickable( Point( window->leftCoord() + 437, window->bottomCoord() + 603 ),
                                             Point( window->leftCoord() + 578, window->bottomCoord() + 573 ) );
        else
            clickableObjects[i] = Clickable( Point( window->leftCoord() + 15, ( window->bottomCoord() + 209 ) - ( 2 * ( i * 19 ) ) ),
                                             Point( window->leftCoord() + 135, ( window->bottomCoord() + 190 ) - ( 2 * ( i * 19 ) ) ) );
    }
}

void Menu::update()
{
    fog.update();

    //Resume game movement.
    if( animBoxdX < animBoxTar && animBox )
    {
        animBoxdX += MENU_X_MOVEMENT_SPEED * window->timeSinceLastFrame();
        if( animBoxdX > animBoxTar )
            animBoxTar = animBoxdX;
    }
    else if( !animBox )
        animBoxdX = 0;
}

void Menu::checkInput()
{
    //If esc is pressed, open menu.
    if( input->getKeyInput() == "esc" )
    {
        if( inMenu == false )
            inMenu = true;
        else
            inMenu = false;
    }
    for( unsigned int i = 0; i < 5; ++i )
    {
        if( clickableObjects[i].isMouseOver() )
            animBox = true;
    }

}


void Menu::draw()
{
    if( inMenu )
    {

        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glEnable( GL_BLEND );
        glColor4f( 0, 0, 0, .72 );
        glBegin( GL_QUADS );
            glVertex2f( window->leftCoord(),
                        window->topCoord() );
            glVertex2f( window->rightCoord(),
                        window->topCoord() );
            glVertex2f( window->rightCoord(),
                        window->bottomCoord() );
            glVertex2f( window->leftCoord(),
                        window->bottomCoord() );
        glEnd();
        glDisable( GL_BLEND );
        glColor3f( 1, 1, 1 );

        fog.draw();

        //Draw animation behind pause menu buttons
        for( unsigned int i = 0; i < 5; ++i )
        {
            if( animBox )
            {
                if( clickableObjects[0].isMouseOver() )
                    drawBox( window->leftCoord(), animBoxdX,( window->bottomCoord() + 209 ) - ( 2 * ( 0 * 19 ) ), FONT_HEIGHT );
                if( clickableObjects[1].isMouseOver() )
                    drawBox( window->leftCoord(), animBoxdX,( window->bottomCoord() + 209 ) - ( 2 * ( 1 * 19 ) ), FONT_HEIGHT );
                if( clickableObjects[2].isMouseOver() )
                    drawBox( window->leftCoord(), animBoxdX,( window->bottomCoord() + 209 ) - ( 2 * ( 2 * 19 ) ), FONT_HEIGHT );
                if( clickableObjects[3].isMouseOver() )
                    drawBox( window->leftCoord(), animBoxdX,( window->bottomCoord() + 209 ) - ( 2 * ( 3 * 19 ) ), FONT_HEIGHT );
                if( clickableObjects[4].isMouseOver() )
                    drawBox( window->leftCoord(), animBoxdX,( window->bottomCoord() + 209 ) - ( 2 * ( 4 * 19 ) ), FONT_HEIGHT );
                animBox = false;
            }
        }

        //Text for each Menu Button
        glColor3f( 0.8, 0.8, 0.8 );
            resourceMgr->drawTextOverlay( "TITLE_FONT", "SNOTCH", .425 , .75 );
            resourceMgr->drawTextOverlay( "LINK_FONT", "RESUME", .03, .25 );
            resourceMgr->drawTextOverlay( "LINK_FONT", "OPTIONS", .03, .20 );
            resourceMgr->drawTextOverlay( "LINK_FONT", "LOAD", .03, .15 );
            resourceMgr->drawTextOverlay( "LINK_FONT", "SAVE", .03, .10 );
            resourceMgr->drawTextOverlay( "LINK_FONT", "QUIT", .03, .05 );
        glColor3f( 1, 1, 1 );

        //Open Internet Browser if Title Link is clicked.
        if( clickableObjects[5].isClicked() )
        {
            HWND Handle;
            ShellExecute(Handle,
                         "open",
                         "http://ucropengl1.10.forumer.com/index.php?sid=5693bafd0d98463604a087e6754d5a29",
                         NULL,NULL,SW_SHOWDEFAULT);
        }

        //Perform buttons point of existence when is clicked.
        for( unsigned int i = 0; i <= 5; ++i )
        {
            //clickableObjects[ i ].draw();
            glColor3f( 1, 1, 1 );
            if( clickableObjects[0].isMouseOver() )
            {
                resourceMgr->drawTextOverlay( "LINK_FONT", "RESUME", .03, .25 );
            }
            if( clickableObjects[1].isMouseOver() )
            {
                resourceMgr->drawTextOverlay( "LINK_FONT", "OPTIONS", .03, .20 );
            }
            if( clickableObjects[2].isMouseOver() )
            {
                resourceMgr->drawTextOverlay( "LINK_FONT", "LOAD", .03, .15 );
            }
            if( clickableObjects[3].isMouseOver() )
            {
                resourceMgr->drawTextOverlay( "LINK_FONT", "SAVE", .03, .10 );
            }
            if( clickableObjects[4].isMouseOver() )
            {
                resourceMgr->drawTextOverlay( "LINK_FONT", "QUIT", .03, .05 );
            }
            if( clickableObjects[5].isMouseOver() )
            {
                resourceMgr->drawTextOverlay( "TITLE_FONT", "SNOTCH", .425 , .75 );
            }

            //RESUME
            if( clickableObjects[0].isClicked() )
                inMenu = false;

            //OPTIONS MENU
            if( clickableObjects[1].isClicked() )
            {
                //options->load();
            }

            if( clickableObjects[2].isClicked() )
            {
                //LOAD GAME
            }

            if( clickableObjects[3].isClicked() )
            {
                //SAVE GAME
            }

            if( clickableObjects[4].isClicked() )
                exit(0);

            //TITLE BUTTON
            if( clickableObjects[5].isClicked() )
            {
                if( soonTemp == false )
                    soonTemp = true;
                else
                    soonTemp = false;
            }
        }
    }
}


bool Menu::isMenuOpen()
{
    return inMenu;
}

Menu::~Menu()
{
    input->release();
    window->release();
    resourceMgr->release();
}


