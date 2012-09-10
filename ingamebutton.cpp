#include "ingamebutton.h"
#include "filenames.h"

#define ALIAS_IN_GAME_BUTTON inGameButton
#define IN_GAME_BUTTON_WIDTH 64.0
#define IN_GAME_BUTTON_HEIGHT 16.0

InGameButton::InGameButton( Point ul, string target )
    :LevelEntities( "BLOCK",
                    ul,
                    Point( ul.getX() + IN_GAME_BUTTON_WIDTH,
                           ul.getY() - IN_GAME_BUTTON_HEIGHT ),
                    "NULL" ),
     Trigger()
{
    resourceMgr     = ResourceMgr::getInstance();
    animationMgr    = AnimationMgr::getInstance();
    pressed         = false;
    this->target    = target;

    resourceMgr->loadImage( FILE_IN_GAME_BUTTON, "button" );
    animationId     = animationMgr->newAnimation( "button" );
}

InGameButton::~InGameButton()
{
    resourceMgr->deleteImage( "button" );
    animationMgr->removeAnimation( animationId );
    resourceMgr->release();
    animationMgr->release();
}

void InGameButton::press()
{
    pressed = true;
    trigger( target );
}

void InGameButton::unPress()
{
    pressed = false;
    unTrigger( target );
}

void InGameButton::draw()
{
    if( pressed )
        animationMgr->setAnimation( animationId, "pressed", "loop" );
    else
        animationMgr->setAnimation( animationId, "notPressed", "loop" );

    animationMgr->update( animationId );
    animationMgr->draw( animationId, true, uLeft );
}

