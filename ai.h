
#ifndef __AI_H__
#define __AI_H__

#include "physics.h"
#include "snotch.h"
#include "animationmgr.h"
#include "timer.h"
#include "window.h"
#include "abilities.h"

using namespace std;

class AI
    : public Physics
{

    protected:

        Point initLoc;
        bool                    facingRight;
        bool                    canJump;
        bool                    wasWalking;
        double                  prevX;
        string                  currentState;
        string                  animationState;
        Snotch*                 snotch;
        Abilities*              powers;
        AnimationMgr*           animationMgr;
        CurrentStateNode*       animationId;

        double                  armor;


    public:
        AI();
        AI(Point, double, double, double);
        ~AI();
        void                    decreaseHealth( double );
        void                    setArmor( double );
        virtual void            init() = 0;
        virtual void            runAI() = 0;
        virtual void            calcState() = 0;
        virtual void            draw() = 0;
        void                    adjustSize();
        void                    update();
        double                  health;
};

#endif
