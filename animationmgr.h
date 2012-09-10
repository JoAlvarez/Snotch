#ifndef __ANIMATION_MGR__
#define __ANIMATION_MGR__

#include "animationsheet.h"
#include "currentstatenode.h"
#include "point.h"
#include "resourcemgr.h"
#include <SDL/SDL_opengl.h>

using namespace std;

class AnimationMgr
{
    private:
        CurrentStateNode*           head;
        CurrentStateNode*           tail;
        ResourceMgr*                resourceMgr;
        Window*                     window;
        vector<AnimationSheet>      sheets;
        static                      AnimationMgr* instance;
        static                      int referenceCount;

        /////////////////////////////////////
        //Mutators
        /////////////////////////////////////
        void                destroy();
        void                removeNode( CurrentStateNode* animationId );
        void                handleInput( string type, string input );
        int                 stringToInt( string toConvert );
        double              stringToDouble( string toConvert );
        CurrentStateNode*   insertNode( string sheetName );

        /////////////////////////////////////
        //Accessors
        /////////////////////////////////////
        int     getSheetIndex( string sheet );

    public:
        /////////////////////////////////////
        //Constructors/Destructors
        /////////////////////////////////////
        AnimationMgr();
        ~AnimationMgr();

        /////////////////////////////////////
        //Acessors
        /////////////////////////////////////
        static  AnimationMgr* getInstance();
        bool    isAnimationOver( CurrentStateNode* animationId );
        bool    draw( CurrentStateNode* animationId, bool facingRight, Point ul );
        Point   getLowerRight( CurrentStateNode* animationId, Point ul );
        Point   getUpperRight( CurrentStateNode* animationId, Point ll );

        /////////////////////////////////////
        //Mutators
        /////////////////////////////////////
        void release();

        //This function will read in chracter sheet infro derived
        //from sheetInfo.ini and load the information into the
        //character sheet vector.
        void init();

        //This is used to load a new instance of an animation
        //into the currentStateNode list. Nodes store things
        //such as the current frame, a timer, or animation type
        //of a specific animation. More generally it will allow
        //us to store the state of more than object that uses the
        //same character sheet.
        CurrentStateNode* newAnimation( string sheet );

        //This just removes a single node.
        void removeAnimation( CurrentStateNode* animationId );

        //This is what we use to change the state of a specific object.
        //For example we have an instance of snotch loaded and we want to
        //change his state from running to walking or have him switch
        //direction. This is what we will use to accomplish the task.
        //animation type can be:
        //  loop: Use this to continue an animation until the state is changed.
        //  loopFromCurState: Use this just as you would use loop. The only
        //                    difference is that this one will start at the
        //                    current frame rather resetting the frame to 0.
        //  single: This will run an animation only once however you can
        //          interrupt the animation by changing the state.
        //  singleFull: This works just as the single however this one
        //              cannot be interrupted.
        void setAnimation( CurrentStateNode* animationId, string state, string animationType );

        //Used to update the current state and frame number
        bool update( CurrentStateNode* animationId );

        void setScale( CurrentStateNode* animationId, double xScale, double yScale );

};

#endif
