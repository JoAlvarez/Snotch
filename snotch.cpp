#include "snotch.h"
#include "image.h"
#include "filenames.h"
#include "global.h"
#include <math.h>
#include <cmath>

//Units measured in pixels per second
#define SNOTCH_WALKING_SPEED    200.0
#define SNOTCH_RUNNING_SPEED    3500.0
#define SNOTCH_JUMP_FORCE       5000.0
#define SNOTCH_LANDING_Y_VEL    -1000.0

#define SNOTCH_MAX_XVEL         350
#define SNOTCH_MAX_YVEL         0

#define SNOTCH_INVUL_TIME       2.0
#define SNOTCH_DEF_LIVES        5
#define SNOTCH_TIME_DEAD        2
#define SNOTCH_PUSH_CD          1.0
#define SNOTCH_FIRE_BALL_CD     1.0

#define JOY_MIN_SENSITIVITY     0.4

Snotch* Snotch::instance = NULL;
int Snotch::referenceCount = 0;

Snotch::Snotch()
{
    currentState        = "idle";
    previousState       = "idle";
    animationType       = "loop";
    type                = "Rectangle";

    //Key bind vars
    setDefaultKeys();

    lives                       = SNOTCH_DEF_LIVES;
    health                      = 100.0;
    previousHealth              = 100.0;
    lastIdleAnimation           = 0.0;
    timeSinceIdleAnim           = 0.0;
    timeDead                    = 0.0;
    previousYVel                = 0.0;
    aimAngle                    = 0.0;
    timeInvulnerable            = 0.0;
    pushCoolDown                = 0.0;
    fireBallCoolDown            = 0.0;
    mass                        = 10.0;
    elasticity                  = 0.1;
    timeSinceGoThroughPlatform  = 0.0;


    dead                    = false;
    facingRight             = true;
    invulnerable            = false;
    canJumpInAir            = true;
    goThroughKeyWasPressed  = false;

    aimIndicator            = AimIndicator( 1.0, 1.0, 0.0 );

    animationMgr            = AnimationMgr::getInstance();
    userInput               = Input::getInstance();
    abilities               = Abilities::getInstance();

    type = "BLOCK";
}

Snotch* Snotch::getInstance()
{
    if(instance == NULL)
    {
        instance = new Snotch();
    }
    ++referenceCount;
    return instance;
}

void Snotch::release()
{
    if( --referenceCount < 1 )
    {
        destroy();
    }
    if(referenceCount < 0)
        referenceCount = 0;
}

void Snotch::destroy()
{
    if(instance)
    {
        //Delete image
        resourceMgr->deleteImage( "snotch" );

        //Delete animation id
        animationMgr->removeAnimation( animationId );

        //Release all singleton instances
        animationMgr->release();
        userInput->release();

        //Destroy physics information
        Physics::destroy();

        //Dlete the instance of Snotch
        instance = NULL;
        delete instance;
    }
}

void Snotch::update( )
{
    animationMgr->update( animationId );

    if( !dead )
    {
        handleJump();
        handleRun();
        handleAiming();
        handlePush();
        handleFireball();
        handleGoThroughPlatforms();
    }

    handleCoolDowns();
    handleInAir();
    handleLanding();
    handleHurt();
    handleIdle();
    handleDead();
    handleInvulnerability();

    animationMgr->setAnimation( animationId, currentState, animationType );

    //Move snotch based on x and y velocities.
    Physics::update();
    adjustSize();

    //Setup the next update
    previousState   = currentState;
    previousYVel    = yVel;
    previousHealth  = health;
    if( currentState != "idleAnimation"  )
    {
        currentState = "idle";
        animationType = "loop";
    }
}

void Snotch::setPos( float x, float y )
{
    setPosition( Point( x, y ) );
}

void Snotch::init( )
{
    //Initializing physics variables
    Physics::init();

    //Handle image loading
    resourceMgr->loadImage( FILE_SNOTCH_CHAR_SHEET, "snotch" );

    //Handle animation
    animationId = animationMgr->newAnimation( "snotch" );
    animationMgr->setScale( animationId, 2.0, 2.0);

    //Adjust size based on animation state
    adjustSize();

    thoughtBubble.init();
    thoughtBubble.setText( "test test. test." );
}

void Snotch::draw()
{
    //Determine alpha
    double alpha = 1.0;
    if( invulnerable and !dead )
    {
        alpha = 0.5;
        alpha += alpha * ( timeInvulnerable / SNOTCH_INVUL_TIME );
    }
    //Point tempUl = Point ( lLeft.getX(),
    //                     animationMgr->getUpperRight( animationId, lLeft ).getY() );
    glEnable ( GL_BLEND );
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f( 1.0, 1.0, 1.0, alpha );
            animationMgr->draw( animationId, facingRight, uLeft );
        glColor4f( 1.0, 1.0, 1.0, 1.0 );
    glDisable( GL_BLEND );



    /*glBegin(GL_POINTS);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(uLeft.getX(), uLeft.getY());
        glColor3f(1.0,0.0,0.0);
        glVertex2f(uRight.getX(), uRight.getY());
        glColor3f(0.0,1.0,0.0);
        glVertex2f(lRight.getX(), lRight.getY());
        glColor3f(0.0,0.0,1.0);
        glVertex2f(lLeft.getX(), lLeft.getY());
    glEnd();*/
    //glColor3f(1.0,1.0,0.0);
    aimIndicator.draw( center, 80.0, aimAngle );


    //thoughtBubble.draw( Point( uLeft.getX() + 25, lLeft.getY() + 85) );

}

Point Snotch::getPos()
{
    return lLeft;
}

void Snotch::setHealth( double health )
{
    if( health < 0.0 )
    {
        health = 0.0;

        //Only decrease lives if snotch has lives left
        if( lives > 0 )
        {
            dead = true;
            lives--;
        }

        //Only reset health if snotch has lives left.
        if( lives > 0 )
            health = 100.0;
    }

    //Make sure health cannot go above 100%
    if( health > 100.0 )
        health = 100.0;

    //Only modify health if  snotch is not dead/invulnerable or if
    // the health is being increased.
    if( health > previousHealth or ( !invulnerable and !dead ) )
    {
        this->health = health;
    }
}

double Snotch::getHealth()
{
    return health;
}

bool Snotch::isFacingRight()
{
    return facingRight;
}

int Snotch::getIndicatorAngle()
{
    return aimAngle;
}

int Snotch::getLives()
{
    return lives;
}

void Snotch::setKeyRunRight( string key )
{
    keyRunRight = key;
}

void Snotch::setKeyRunLeft( string key )
{
    keyRunLeft  = key;
}
void Snotch::setKeyJump( string key )
{
    keyJump     = key;
}

void Snotch::setKeyAimUp( string key )
{
    keyAimUp    = key;
}

void Snotch::setKeyAimDown( string key )
{
    keyAimDown  = key;
}

void Snotch::setKeyUsePush( string key )
{
    keyUsePush  = key;
}

void Snotch::setKeyUseFireBall( string key )
{
    keyUseFireBall  = key;
}

void Snotch::setKeyGoThroughPlatform( string key )
{
    keyGoThroughPlatform = key;
}

void Snotch::setDefaultKeys()
{
    setKeyRunRight( "right" );
    setKeyRunLeft( "left" );
    setKeyJump( "space" );
    setKeyAimUp( "up" );
    setKeyAimDown( "down" );
    setKeyUsePush( "1" );
    setKeyUseFireBall( "2" );
    setKeyGoThroughPlatform( "down" );
}

void Snotch::adjustSize()
{
    //Adjusts the positions of all the points based on the
    // size of the current animation with the assumption
    // that the lowerLeft point is the fixed point for the
    // characters movement.
    //uRight = lLeft;
    uRight = animationMgr->getUpperRight(animationId, lLeft);
    //uRight.move( 70.0, 78.0 );
    lRight = Point( uRight.getX(), lLeft.getY() );
    uLeft  = Point( lLeft.getX(), uRight.getY() );
    center = Point( ( uLeft.getX() + lRight.getX() ) / 2.0  ,
                    ( uLeft.getY() + lRight.getY() ) / 2.0  );

    width  = uRight.getX() - uLeft.getX();
    height = uLeft.getY() - lLeft.getY();
}

void Snotch::handleAiming()
{
    bool aimingRight    = false;
    bool aimingLeft     = false;
    bool aimingUp       = false;
    bool aimingDown     = false;

    //Handle aiming input
    if( userInput->isKeyDown( keyRunRight ) || userInput->isHatDirPressed("Joy0 HatRIGHT") )
    {
        aimingRight = true;
    }
    if( userInput->isKeyDown( keyRunLeft ) || userInput->isHatDirPressed("Joy0 HatLEFT") )
    {
        aimingLeft = true;
    }
    if( userInput->isKeyDown( keyAimUp ) || userInput->isHatDirPressed("Joy0 HatUP") )
    {
        aimingUp = true;
    }
    if( userInput->isKeyDown( keyAimDown ) || userInput->isHatDirPressed("Joy0 HatDOWN") )
    {
        aimingDown = true;
    }

    //Handle aiming whe nothing is being pressed
    if( facingRight )
        aimAngle = 0;
    else
        aimAngle = 180;

    /*
    //This makes it so the joystick isnt too sensitive
    if( ( abs( userInput->getJoystickAxisPos(JOYSTICK_0, X_AXIS_RIGHT) ) > JOY_MIN_SENSITIVITY ) or
        ( abs( userInput->getJoystickAxisPos(JOYSTICK_0, Y_AXIS_RIGHT) ) > JOY_MIN_SENSITIVITY ))
    {
        //Handle aiming for joystick
        aimAngle = atan2( userInput->getJoystickAxisPos(JOYSTICK_0, Y_AXIS_RIGHT),
                          userInput->getJoystickAxisPos(JOYSTICK_0, X_AXIS_RIGHT) );
        aimAngle *= 180.0 / M_PI;

    }
    */

    //Handle aiming for key presses
    if( aimingUp && facingRight)
        aimAngle = 45;
    else if( aimingUp && !facingRight )
        aimAngle = 135;
    else if( aimingDown && aimingLeft )
        aimAngle = 225;
    else if( aimingDown && aimingRight )
        aimAngle = 315;
    else if( aimingUp )
        aimAngle = 90;
    else if( aimingLeft )
        aimAngle = 180;
    else if( aimingDown )
        aimAngle = 270;
    else if( aimingRight )
        aimAngle = 0;
}

void Snotch::handleInAir()
{
    if( inAir )
    {
        //Check if snotch is going up or down.
        if( yVel >= 0 )
            currentState = "inAirUp";
        else
            currentState = "inAirDown";

        animationType = "loop";
    }
}

void Snotch::handleLanding()
{
    //Set the current state to landing depending on
    // how fast hes falling
    if( !inAir and previousState == "inAirDown" and
        previousYVel <= SNOTCH_LANDING_Y_VEL )
    {
        currentState = "landing";
        animationType = "single";
    }

    //Continue making the state landing until the animation
    // is over
    if( previousState == "landing" )
    {
        if( !animationMgr->isAnimationOver( animationId ) )
            currentState = "landing";
            animationType = "single";
    }
}

void Snotch::handleHurt()
{
    if( health < previousHealth )
    {
        currentState = "hurt";
        animationType = "singleFull";
    }
}

void Snotch::handleDead()
{
    if( dead )
    {
        timeDead += window->timeSinceLastFrame();
        currentState  = "dead";
        animationType = "loop";

        //Make it so he revives as invulnerable
        // after a certain amount of time has passed
        if( timeDead <= SNOTCH_TIME_DEAD )
        {
            dead          = true;
        }
        else if( lives > 0 )
        {
            timeDead      = 0.0;
            dead          = false;
            currentState  = "idle";
            animationType = "loop";
            health        = 100.0;
            invulnerable  = true;
        }
    }
}

void Snotch::handleIdle()
{
     if( currentState == "idleAnimation" )
    {
        if( animationMgr->isAnimationOver( animationId ) )
        {
            currentState        = "idle";
            animationType       = "loop";
            timeSinceIdleAnim   = 0.0;
        }
    }

    if( currentState == "idle" )
    {
        timeSinceIdleAnim += window->timeSinceLastFrame();
        if( timeSinceIdleAnim > 2.0 )
        {
            currentState    = "idleAnimation";
            animationType   = "single";
        }
    }

    if( previousState == "idleAnimation" and
        currentState != "idleAnimation" )
        timeSinceIdleAnim   = 0.0;
}

void Snotch::handleInvulnerability()
{
    if( invulnerable or health < previousHealth )
    {
        invulnerable = true;
        timeInvulnerable += window->timeSinceLastFrame();

        //Only have snotch be invulnerable for a certain amount
        // of time.
        if( timeInvulnerable >= SNOTCH_INVUL_TIME )
        {
            timeInvulnerable = 0.0;
            invulnerable = false;
        }
    }
}

void Snotch::handleJump()
{
    if( !inAir )
        canJumpInAir = true;

    if( userInput->getKeyInput() == keyJump or ( userInput->getJoyInput() == "Joy0 But1" ) )
    {
        if( !inAir or canJumpInAir )
        {
            if( inAir )
                canJumpInAir = false;

            currentState = "jump";
            inAir = true;
            yVel = SNOTCH_JUMP_FORCE / mass;
        }
    }
}

void Snotch::handleRun()
{
    if( userInput->isKeyDown( keyRunRight ) or userInput->isHatDirPressed("Joy0 HatRIGHT") )
    {
        currentState = "run";
        facingRight = true;
        if(xVel <= SNOTCH_MAX_XVEL)
        {
            if( previousState != "landing" )
                xVel += SNOTCH_RUNNING_SPEED * window->timeSinceLastFrame();

            //Gives a max x velocity you can attain by running
            if( xVel > SNOTCH_MAX_XVEL )
                xVel = SNOTCH_MAX_XVEL;
        }
    }
    if( userInput->isKeyDown( keyRunLeft ) or userInput->isHatDirPressed("Joy0 HatLEFT") )
    {
        currentState = "run";
        facingRight = false;
        if(xVel >= -SNOTCH_MAX_XVEL)
        {
            if( previousState != "landing" )
                xVel += -SNOTCH_RUNNING_SPEED * window->timeSinceLastFrame();

            //Gives a max x velocity you can attain by running
            if( xVel < -SNOTCH_MAX_XVEL )
                xVel = -SNOTCH_MAX_XVEL;
        }
    }
}

void Snotch::handlePush()
{
        if( ( userInput->getKeyInput() == keyUsePush or
              userInput->isJoyButtonDown("Joy0 But5") ) and
              pushCoolDown <= 0.0 )
        {
            abilities->usePower("push", lLeft, aimAngle, facingRight );
            addVel( -cos( aimAngle * DEGREES_TO_RAD ) * 450,
                    -sin( aimAngle * DEGREES_TO_RAD ) * 350 );


            if( aimAngle > 190 )
                setInAir(true);

            pushCoolDown    = SNOTCH_PUSH_CD;
            currentState    = "push";
            animationType   = "singleFull";
        }
}

void Snotch::handleFireball()
{
        if( ( userInput->getKeyInput() == keyUseFireBall or
              userInput->isJoyButtonDown("Joy0 But7") )and
              fireBallCoolDown <= 0.0 )
        {
            abilities->usePower("fireball", lLeft, aimAngle, facingRight );
            fireBallCoolDown    = SNOTCH_FIRE_BALL_CD;
            currentState        = "push";
            animationType       = "singleFull";
        }
}

void Snotch::handleCoolDowns()
{
    pushCoolDown -= window->timeSinceLastFrame();
    if( pushCoolDown < 0.0 )
        pushCoolDown = 0.0;

    fireBallCoolDown -= window->timeSinceLastFrame();
    if( fireBallCoolDown < 0.0 )
        fireBallCoolDown = 0.0;
}

void Snotch::handleGoThroughPlatforms()
{
    timeSinceLastKeyStroke += window->timeSinceLastFrame();

    //Reset if key hasnt been pressed again
    // within the time limit
    if( timeSinceLastKeyStroke > 1.0 )
        goThroughKeyWasPressed = false;

    if( goThroughPlatform )
    {
        timeSinceGoThroughPlatform += window->timeSinceLastFrame();
        if(timeSinceGoThroughPlatform > 0.25)
        {
            goThroughPlatform = false;
        }
    }

    //If the key was last pressed within the time limit
    //  and is being pressed again now.
    if( goThroughKeyWasPressed and
        userInput->getKeyInput() == keyGoThroughPlatform )
    {
        goThroughPlatform = true;
        goThroughKeyWasPressed = false;
        timeSinceLastKeyStroke = 0.0;
        timeSinceGoThroughPlatform = 0.0;
    }

    //If the key is pressed and check to make sure a double
    // tap hasn't just happened
    if( userInput->getKeyInput() == keyGoThroughPlatform and
        timeSinceLastKeyStroke != 0.0 && !inAir)
    {
        timeSinceLastKeyStroke = 0.0;
        goThroughKeyWasPressed = true;
    }
}
