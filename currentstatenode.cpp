#include "currentstatenode.h"

/////////////////////////////////////
//Constructors
/////////////////////////////////////
CurrentStateNode::CurrentStateNode()
{
    nextNode = NULL;
    prevNode = NULL;
    currentFrame = 0;
    lastFrameUpdate = 0.0;
    xScale = 1.0;
    yScale = 1.0;
}

CurrentStateNode::CurrentStateNode( CurrentStateNode* prev, string sheetName )
{
    nextNode = NULL;
    prevNode = prev;
    this->sheetName = sheetName;
    currentFrame = 0;
    lastFrameUpdate = 0.0;
    xScale = 1.0;
    yScale = 1.0;
}


/////////////////////////////////////
//Accessors
/////////////////////////////////////
CurrentStateNode* CurrentStateNode::getNext()
{
    return nextNode;
}

CurrentStateNode* CurrentStateNode::getPrev()
{
    return prevNode;
}

string CurrentStateNode::getSheetName()
{
    return sheetName;
}

string CurrentStateNode::getState()
{
    return currentState;
}

string CurrentStateNode::getAnimationType()
{
    return animationType;
}

unsigned int CurrentStateNode::getFrame()
{
    return currentFrame;
}

double CurrentStateNode::getLastFrameUpdate()
{
    return lastFrameUpdate;
}

double CurrentStateNode::getXScale()
{
    return xScale;
}

double CurrentStateNode::getYScale()
{
    return yScale;
}

/////////////////////////////////////
//Mutators
/////////////////////////////////////
void CurrentStateNode::setNextNode( CurrentStateNode* next )
{
    nextNode = next;
}

void CurrentStateNode::setPrevNode( CurrentStateNode* prev )
{
    prevNode = prev;
}

void CurrentStateNode::resetFrame()
{
    currentFrame = 0;
}

void CurrentStateNode::incrementFrame()
{
    currentFrame++;
}

void CurrentStateNode::setState( string stateName )
{
    if( currentState != stateName )
    {
        currentFrame = 0;
        currentState = stateName;
    }
}

void CurrentStateNode::setStateAndFrame( string stateName, unsigned int frameNumber )
{
    currentState = stateName;
    currentFrame = frameNumber;
}


void CurrentStateNode::setFrameUpdate( double lastFrameUpdate )
{
    this->lastFrameUpdate = lastFrameUpdate;
}

void CurrentStateNode::setAnimationType( string animationType )
{
    //Check to make sure the type being set is a valid otherwise
    // set it to the default loop type
    if( animationType == "singleFull" or animationType == "single" )
        this->animationType = animationType;
    else
        this->animationType = "loop";
}

void CurrentStateNode::setScale( double xScale, double yScale )
{
    this->xScale = xScale;
    this->yScale = yScale;
}
