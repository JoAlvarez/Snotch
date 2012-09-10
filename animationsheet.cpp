#include "animationsheet.h"

/////////////////////////////////////
//Constructors
/////////////////////////////////////
AnimationSheet::AnimationSheet()
{
    totalSheetWidth  = 0;
    totalSheetHeight = 0;
}

/////////////////////////////////////
//Mutators
/////////////////////////////////////
void AnimationSheet::insertSheetName( string sheetName )
{
    this->sheetName = sheetName;
}

void AnimationSheet::insertDefaultState( string defaultState )
{
    this->defaultState = defaultState;
}
void AnimationSheet::insertSheetWidth( double totalSheetWidth )
{
    this->totalSheetWidth = totalSheetWidth;
}

void AnimationSheet::insertSheetHeight( double totalSheetHeight )
{
    this->totalSheetHeight = totalSheetHeight;
}

void AnimationSheet::insertState( string stateName )
{
    stateProperties.push_back( StateProperties() );
    stateProperties[ stateProperties.size() - 1 ].stateName = stateName;
}

void AnimationSheet::insertXBegin( double xBeginForState )
{
    stateProperties[ stateProperties.size() - 1 ].xBeginForState = xBeginForState;
}

void AnimationSheet::insertYBegin( double yBeginForState )
{
    stateProperties[ stateProperties.size() - 1 ].yBeginForState = yBeginForState;
}

void AnimationSheet::insertFrameWidth( double stateFrameWidth )
{
    stateProperties[ stateProperties.size() - 1 ].stateFrameWidth = stateFrameWidth;
}

void AnimationSheet::insertFrameHeight( double stateFrameHeight )
{
    stateProperties[ stateProperties.size() - 1 ].stateFrameHeight = stateFrameHeight;
}

void AnimationSheet::insertNumFrames( unsigned int numFramesForState )
{
    stateProperties[ stateProperties.size() - 1 ].numFramesForState = numFramesForState;
}

void AnimationSheet::insertFps( unsigned int fpsForState )
{
    stateProperties[ stateProperties.size() - 1 ].fpsForState = fpsForState;
}

/////////////////////////////////////
//Accessors
/////////////////////////////////////
int AnimationSheet::getStateIndex( string stateName )
{
    for( unsigned int i = 0; i < stateProperties.size(); ++i )
    {
        if( stateProperties[ i ].stateName == stateName  )
            return i;
    }
    return -1;
}

double AnimationSheet::getXBegin( int stateIndex )
{
    return stateProperties[ stateIndex ].xBeginForState;
}

double AnimationSheet::getYBegin( int stateIndex )
{
    return stateProperties[ stateIndex ].yBeginForState;
}

double AnimationSheet::getFrameWidth( int stateIndex )
{
    return stateProperties[ stateIndex ].stateFrameWidth;
}

double AnimationSheet::getFrameHeight( int stateIndex )
{
    return stateProperties[ stateIndex ].stateFrameHeight;
}

unsigned int AnimationSheet::getNumFrames( int stateIndex )
{
    return stateProperties[ stateIndex ].numFramesForState;
}

unsigned int AnimationSheet::getFps( int stateIndex )
{
    return stateProperties[ stateIndex ].fpsForState;
}

double AnimationSheet::getSheetWidth( )
{
    return totalSheetWidth;
}

double AnimationSheet::getSheetHeight( )
{
    return totalSheetHeight;
}

string AnimationSheet::getSheetName()
{
    return sheetName;
}

string AnimationSheet::getDefaultState()
{
    return defaultState;
}
