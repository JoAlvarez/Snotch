#include "livesbar.h"

LivesBar::LivesBar()
    :Draggable( Point( LIFE_DEFAULT_UL_X, LIFE_DEFAULT_UL_Y ),
                Point( LIFE_DEFAULT_UL_X + ( LIFE_IMAGE_PADDING * LIFE_MAX_DISPLAY ) +
                       lowerLeft.getX() + LIFE_IMAGE_WIDTH * LIFE_MAX_DISPLAY,
                       LIFE_DEFAULT_UL_Y - LIFE_IMAGE_HEIGHT )
              )
{
    resourceMgr = ResourceMgr::getInstance();
    window      = Window::getInstance();
    locked = true;
    resourceMgr->loadFont( "./data/fonts/arial.ttf", LIFE_TEXT_ALIAS, 24 );
}

LivesBar::~LivesBar()
{
    resourceMgr->deleteFont( LIFE_TEXT_ALIAS );
    resourceMgr->release();
    window->release();
}

void LivesBar::unLock()
{
    locked = false;
}

void LivesBar::lock()
{
    locked = true;
}

void LivesBar::update()
{
    if( !locked )
        Draggable::update();
}

void LivesBar::draw( int lives )
{
        double lifeLeftX    = window->leftCoord() + lowerLeft.getX() + LIFE_IMAGE_PADDING;
        double lifeUpperY   = window->bottomCoord() + upperLeft.getY();
        resourceMgr->drawImage( "life", lifeLeftX,
                                        lifeLeftX + LIFE_IMAGE_TOTAL_WIDTH,
                                        lifeUpperY - LIFE_IMAGE_TOTAL_HEIGHT,
                                        lifeUpperY );
        resourceMgr->drawText( LIFE_TEXT_ALIAS, "x",
                               lifeLeftX + LIFE_IMAGE_TOTAL_WIDTH, window->bottomCoord() + lowerLeft.getY() );
        resourceMgr->drawText( LIFE_TEXT_ALIAS, lives,
                               lifeLeftX + LIFE_IMAGE_TOTAL_WIDTH + 25, window->bottomCoord() + lowerLeft.getY() );

    if( !locked )
        Clickable::draw();
}
