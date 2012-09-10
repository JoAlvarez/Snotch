#ifndef __SNOTCH_H__
#define __SNOTCH_H__

#include "input.h"
#include "timer.h"
#include "animationmgr.h"
#include "resourcemgr.h"
#include "physics.h"
#include "object.h"
#include "aimindicator.h"
#include "thoughtbubble.h"
#include <SDL/SDL_opengl.h>
#include <string>
#include "levelobjects.h"
#include "abilities.h"

class Snotch
    : public Physics
{
    private:
        static              Snotch* instance;
        static              int referenceCount;

        string              currentState;
        string              previousState;
        string              animationType;

        //Key bind vars
        string              keyRunRight;
        string              keyRunLeft;
        string              keyJump;
        string              keyAimUp;
        string              keyAimDown;
        string              keyUsePush;
        string              keyUseFireBall;
        string              keyGoThroughPlatform;

        unsigned int        lives;
        double              health;
        double              previousHealth;
        double              lastIdleAnimation;
        double              timeSinceIdleAnim;
        double              timeDead;
        double              previousYVel;
        double              aimAngle;
        double              timeInvulnerable;
        double              pushCoolDown;
        double              fireBallCoolDown;
        double              timeSinceLastKeyStroke;
        double              timeSinceGoThroughPlatform;

        bool                dead;
        bool                facingRight;
        bool                invulnerable;
        bool                canJumpInAir;
        bool                goThroughKeyWasPressed;

        AimIndicator        aimIndicator;

        AnimationMgr*       animationMgr;
        CurrentStateNode*   animationId;
        Input*              userInput;
        Abilities*          abilities;
        ThoughtBubble       thoughtBubble;

        //Singleton functions
        void                destroy();

        void                adjustSize();


        //Update handles
        void                handleAiming();
        void                handleInAir();
        void                handleLanding();
        void                handleHurt();
        void                handleDead();
        void                handleIdle();
        void                handleInvulnerability();
        void                handleJump();
        void                handleRun();
        void                handlePush();
        void                handleFireball();
        void                handleCoolDowns();
        void                handleGoThroughPlatforms();


    public:
        Snotch();
        //Singleton functions
        static Snotch*  getInstance();
        void            release();


        void            init();
        void            update();
        void            setPos( float x, float y );
        void            draw();
        void            setHealth( double health );

        //Set key binds
        void            setKeyRunRight( string key );
        void            setKeyRunLeft( string key );
        void            setKeyJump( string key );
        void            setKeyAimUp( string key );
        void            setKeyAimDown( string key );
        void            setDefaultKeys();
        void            setKeyUsePush( string key );
        void            setKeyUseFireBall( string key );
        void            setKeyGoThroughPlatform( string key );

        Point           getPos();
        double          getHealth();
        bool            isFacingRight();
        int             getIndicatorAngle();
        int             getLives();


};

#endif
