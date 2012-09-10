#include "door.h"

Door::Door()
    :Triggerable(), LevelEntities( "BLOCK", Point( 0, 0 ), Point( 0, 0 ), NULL )
{
    resourceMgr = ResourceMgr::getInstance();
    window      = Window::getInstance();
    Triggerable::init( "" );
}
Door::Door( Point ul, Point lr, string texture, string name )
    :Triggerable(), LevelEntities( "BLOCK", ul, lr, texture )
{
    origUl = ul;
    origLr = lr;
    resourceMgr = ResourceMgr::getInstance();
    window      = Window::getInstance();
    Triggerable::init( name );
}

void Door::trigger()
{
    if( lRight.getY() < origUl.getY() )
    {
        uLeft.move( 0, DOOR_OPEN_SPEED * window->timeSinceLastFrame() );
        lRight.move( 0, DOOR_OPEN_SPEED * window->timeSinceLastFrame() );
        lLeft.move( 0, DOOR_OPEN_SPEED * window->timeSinceLastFrame() );
        uRight.move( 0, DOOR_OPEN_SPEED * window->timeSinceLastFrame() );
        center.move( 0, DOOR_OPEN_SPEED * window->timeSinceLastFrame() );
    }
}

void Door::unTrigger()
{
    if( lRight.getY() > origLr.getY() )
    {
        uLeft.move( 0, -DOOR_OPEN_SPEED * window->timeSinceLastFrame() );
        lRight.move( 0, -DOOR_OPEN_SPEED * window->timeSinceLastFrame() );
        lLeft.move( 0, -DOOR_OPEN_SPEED * window->timeSinceLastFrame() );
        uRight.move( 0, -DOOR_OPEN_SPEED * window->timeSinceLastFrame() );
        center.move( 0, -DOOR_OPEN_SPEED * window->timeSinceLastFrame() );
    }
}

void Door::draw()
{
    resourceMgr->drawImage( "block", uLeft.getX(), lRight.getX(), lRight.getY(), uLeft.getY() );
}


