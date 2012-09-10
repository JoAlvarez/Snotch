#include "aimindicator.h"
#include <SDL/SDL_opengl.h>
#include <cmath>

#define ARROW_TOTAL_WIDTH   32.0
#define ARROW_TOTAL_HEIGHT  16.0
#define ARROW_DRAWN_WIDTH   20.0
#define ARROW_DRAWN_HEIGHT  12.0
#define ARROW_DEFAULT_ANGLE 90.0

AimIndicator::AimIndicator()
{
    red   = 0.0;
    green = 0.0;
    blue  = 0.0;
    resourceMgr = ResourceMgr::getInstance();
}

AimIndicator::AimIndicator( double r, double g, double b )
{
    red   = r;
    green = g;
    blue  = b;
    resourceMgr = ResourceMgr::getInstance();
}

AimIndicator::~AimIndicator()
{
    resourceMgr->release();
}
void AimIndicator::setColor( double r, double g, double b )
{
    red   = r;
    green = g;
    blue  = b;
}

void AimIndicator::draw( Point center, double radius, double angle )
{
    double angleInRadians = angle * ( M_PI / 180.0 );
    double x = ( cos( angleInRadians ) * radius ) + center.getX();
    double y = ( sin( angleInRadians ) * radius ) + center.getY();
    x -= ARROW_DRAWN_WIDTH / 2.0;
    y -= ARROW_DRAWN_HEIGHT / 2.0;

    glColor3f( red, green, blue );
        resourceMgr->drawImage( "arrow", angle - ARROW_DEFAULT_ANGLE,
                                         x, x + ARROW_DRAWN_WIDTH,
                                         y, y + ARROW_DRAWN_HEIGHT,
                                         0.0, ARROW_DRAWN_WIDTH / ARROW_TOTAL_WIDTH,
                                         0.0, ARROW_DRAWN_HEIGHT / ARROW_TOTAL_HEIGHT );
    glColor3f( 1.0, 1.0, 1.0 );

}
