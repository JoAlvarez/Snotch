#include "cooldown.h"

Cooldown::Cooldown()
{
    phase1 = phase2 = phase3 = phase4 = true;
    end = false;
}

void Cooldown::init()
{
    window = Window::getInstance();
}

void Cooldown::update()
{
    if( phase1pt.getX() <= phase2pt.getX() )
    {
        phase1pt.move( phase2pt.getX() * ( window->timeSinceLastFrame() * 0.5 ), 0 );

        if( phase1pt.getX() > phase2pt.getX() )
            phase1 = false;
    }
    if( phase2pt.getY() >= phase3pt.getY() && !phase1 )
    {
        phase2pt.move( 0, -phase3pt.getX() * ( window->timeSinceLastFrame() * 0.5 ) );

        if( phase2pt.getY() < phase3pt.getY() )
            phase2 = false;
    }
    if( phase3pt.getX() >= phase4pt.getX() && !phase2 )
    {
        phase3pt.move( - phase4pt.getX() * ( window->timeSinceLastFrame() * 0.5 ), 0 );

        if( phase3pt.getX() < phase4pt.getX() )
            phase3 = false;
    }
    if( phase4pt.getY() <= phase5pt.getY() && !phase3 )
    {
        phase4pt.move( 0, phase5pt.getX() * ( window->timeSinceLastFrame() * 0.5 )  );

        if( phase4pt.getY() > phase5pt.getY() )
            phase4 = false;
    }
    if( phase5pt.getX() <= begin && !phase4 )
    {
        phase5pt.move( begin* window->timeSinceLastFrame() * 1, 0 );

        if( phase5pt.getX() > begin )
            end = true;
    }
}

void Cooldown::start( double time, double percentLeftX, double percentRightX,
                      double percentLowerY, double percentUpperY )
{
    double left, right, lower, upper;
    left  = window->leftCoord();
    right = window->rightCoord();
    lower = window->bottomCoord();
    upper = window->topCoord();

    window->setCoord(0, window->getWidth(), 0, window->getHeight());

    begin = window->getWidth()  * ( percentLeftX + percentRightX ) / 2.0;

    phase1pt = Point( window->getWidth()  * ( ( percentLeftX + percentRightX ) / 2.0 ),
                      window->getHeight() * percentUpperY );
    phase2pt = Point( window->getWidth()  * percentRightX,
                      window->getHeight() * percentUpperY );
    phase3pt = Point( window->getWidth()  * percentRightX,
                      window->getHeight() * percentLowerY );
    phase4pt = Point( window->getWidth()  * percentLeftX,
                      window->getHeight() * percentLowerY );
    phase5pt = Point( window->getWidth()  * percentLeftX,
                      window->getHeight() * percentUpperY );

    midX    = window->getWidth()  * ( ( percentLeftX + percentRightX ) / 2.0 );
    midY    = window->getHeight() * ( ( percentUpperY + percentLowerY ) / 2.0 );
    leftX   = window->getWidth()  * percentLeftX;
    rightX  = window->getWidth()  * percentRightX;
    lowerY  = window->getHeight() * percentLowerY;
    upperY  = window->getHeight() * percentUpperY;

    window->setCoord(left, right, lower, upper);

    end = false;
    phase1 = phase2 = phase3 = phase4 = true;
}

void Cooldown::draw( )
{
    double left, right, lower, upper;
    left  = window->leftCoord();
    right = window->rightCoord();
    lower = window->bottomCoord();
    upper = window->topCoord();

    window->setCoord(0, window->getWidth(), 0, window->getHeight());

    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable( GL_BLEND );
    glColor4f( 0, 0, 0, .75 );
    glBegin( GL_TRIANGLES );

    //5 Triangle pieces covering particular action icon to represent cooldown timer.
    //First triangle top right portion of icon.
    //   ___
    //  | |/|
    //  |___|
    //
        glVertex2f( midX, midY );
        glVertex2f( phase1pt.getX(), phase1pt.getY() );
        glVertex2f( rightX, upperY );

    //Second triangle left half of icon.
    //   ___
    //  |  /|
    //  |__\|
    //
        glVertex2f( midX, midY );
        glVertex2f( phase2pt.getX(), phase2pt.getY() );
        glVertex2f( rightX, lowerY );

    //Third triangle bottom half of icon.
    //   ___
    //  |   |
    //  |/_\|
    //
        glVertex2f( midX, midY );
        glVertex2f( phase3pt.getX(), phase3pt.getY() );
        glVertex2f( leftX, lowerY );

    //Fourth triangle left half of icon.
    //   ___
    //  |\  |
    //  |/__|
    //
        glVertex2f( midX, midY );
        glVertex2f( phase4pt.getX(), phase4pt.getY() );
        glVertex2f( leftX, upperY );

    //Fifth triangle top right portion of icon.
    //   ___
    //  |\| |
    //  |___|
    //
        glVertex2f( midX, midY );
        glVertex2f( phase5pt.getX(), phase5pt.getY() );
        glVertex2f( midX, upperY );

    glEnd();
    glDisable( GL_BLEND );
    glColor4f( 1, 1, 1, 1 );

    window->setCoord(left, right, lower, upper);
}

bool Cooldown::isEnd()
{
    return end;
}

Cooldown::~Cooldown()
{
    window->release();
}
