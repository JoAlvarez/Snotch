#ifndef __ANIMATION_SHEET__
#define __ANIMATION_SHEET__

#include <vector>
#include <string>
#include "stateproperties.h"

using namespace std;

class AnimationSheet
{
    private:
        vector<StateProperties> stateProperties;
        string                  sheetName;
        string                  defaultState;
        double                  totalSheetWidth;
        double                  totalSheetHeight;

    public:
        /////////////////////////////////////
        //Constructors
        /////////////////////////////////////
        AnimationSheet();

        /////////////////////////////////////
        //Mutators
        /////////////////////////////////////
        void insertSheetName( string sheetName );
        void insertDefaultState( string defaultState );
        void insertSheetWidth( double totalSheetWidth );
        void insertSheetHeight( double totalSheetHeight );
        void insertState( string stateName );
        void insertXBegin( double xBeginForState );
        void insertYBegin( double yBeginForState );
        void insertFrameWidth( double stateFrameWidth );
        void insertFrameHeight( double stateFrameHeight );
        void insertNumFrames( unsigned int numFramesForState );
        void insertFps( unsigned int fpsForState );


        /////////////////////////////////////
        //Accessors
        /////////////////////////////////////
        int             getStateIndex( string stateName );
        double          getXBegin( int stateIndex );
        double          getYBegin( int stateIndex );
        double          getFrameWidth( int stateIndex );
        double          getFrameHeight( int stateIndex );
        unsigned int    getNumFrames( int stateIndex );
        unsigned int    getFps( int stateIndex );
        double          getSheetWidth( );
        double          getSheetHeight( );

        string getSheetName();
        string getDefaultState();
};

#endif

