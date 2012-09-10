#include "healthbar.h"

#define HEALTH_BAR_DRAWN_WIDTH  77.0
#define HEALTH_BAR_DRAWN_HEIGHT 154.0
#define HEALTH_BAR_TOTAL_WIDTH  128.0
#define HEALTH_BAR_TOTAL_HEIGHT 256.0

HealthBar::HealthBar()
    :Draggable( Point( 0, HEALTH_BAR_DRAWN_HEIGHT ),
                Point( HEALTH_BAR_DRAWN_WIDTH, 0 ) )
{
    totalWidth = 0.0;
    totalHeight = 0.0;
    drawnWidth = 0.0;
    drawnHeight = 0.0;
    locked = true;

    resourceMgr = ResourceMgr::getInstance();
}

HealthBar::~HealthBar()
{
    resourceMgr->release();
}

void HealthBar::unLock()
{
    locked = false;
}

void HealthBar::lock()
{
    locked = true;
}

void HealthBar::update()
{
    if( !locked )
        Draggable::update();
}

void HealthBar::draw( double healthPercentage )
{
    double textureHeight = HEALTH_BAR_DRAWN_HEIGHT * healthPercentage / 100.0;
    double textureRightPerentage = HEALTH_BAR_DRAWN_WIDTH / HEALTH_BAR_TOTAL_WIDTH;
    double textureLeft = 0.0;
    double textureRight = textureRightPerentage;

    double windowCenterX = ( ( window->rightCoord() - window->leftCoord() ) / 2 ) +
                           window->leftCoord();
    double healthBarX = window->leftCoord() + upperLeft.getX();

    if( healthBarX >= windowCenterX )
    {
        textureLeft = textureRightPerentage;
        textureRight = 0.0;
    }
    resourceMgr->drawImage( "healthBarBw" ,
                            window->leftCoord() + upperLeft.getX(),
                            window->leftCoord() + upperLeft.getX() + HEALTH_BAR_DRAWN_WIDTH,
                            window->bottomCoord() + lowerRight.getY(),
                            window->bottomCoord() + lowerRight.getY() + HEALTH_BAR_DRAWN_HEIGHT,
                            textureLeft,
                            textureRight,
                            ( HEALTH_BAR_TOTAL_HEIGHT - HEALTH_BAR_DRAWN_HEIGHT ) / ( HEALTH_BAR_TOTAL_HEIGHT ),
                            1.0 );
    resourceMgr->drawImage( "healthBar" ,
                            window->leftCoord() + upperLeft.getX(),
                            window->leftCoord() + upperLeft.getX() + HEALTH_BAR_DRAWN_WIDTH,
                            window->bottomCoord() + lowerRight.getY(),
                            window->bottomCoord() + lowerRight.getY() + textureHeight,
                            textureLeft,
                            textureRight,
                            ( HEALTH_BAR_TOTAL_HEIGHT - textureHeight ) / ( HEALTH_BAR_TOTAL_HEIGHT ),
                            1.0 );
    if( !locked )
        Clickable::draw();
}
