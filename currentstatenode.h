#ifndef __CURRENT_STATE_NODE_H__
#define __CURRENT_STATE_NODE_H__

#include "timer.h"
#include <string>

using namespace std;

class CurrentStateNode
{
    private:
        CurrentStateNode*   nextNode;
        CurrentStateNode*   prevNode;
        string              sheetName;
        string              currentState;
        string              animationType;
        unsigned int        currentFrame;
        double              lastFrameUpdate;
        double              xScale;
        double              yScale;

    public:
        /////////////////////////////////////
        //Constructors
        /////////////////////////////////////
        CurrentStateNode();
        CurrentStateNode( CurrentStateNode* prev, string sheetName );

        /////////////////////////////////////
        //Accessors
        /////////////////////////////////////
        CurrentStateNode*   getNext();
        CurrentStateNode*   getPrev();
        string              getSheetName();
        string              getState();
        string              getAnimationType();
        unsigned int        getFrame();
        double              getLastFrameUpdate();
        double              getXScale();
        double              getYScale();


        /////////////////////////////////////
        //Mutators
        /////////////////////////////////////
        void setNextNode( CurrentStateNode* next );
        void setPrevNode( CurrentStateNode* prev );
        void resetFrame();
        void incrementFrame();
        void setState( string stateName );
        void setStateAndFrame( string stateName, unsigned int frameNumber );
        void setFrameUpdate( double lastFrameUpdate );
        void setAnimationType( string animationType );
        void CurrentStateNode::setScale( double xScale, double yScale );
};

#endif
