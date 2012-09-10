#include "animationmgr.h"
#include "image.h"
#include "filenames.h"
#include <fstream>
#include <sstream>
#include <iostream>

AnimationMgr* AnimationMgr::instance = NULL;
int AnimationMgr::referenceCount = 0;


/////////////////////////////////////
//Constructors/Destructors
/////////////////////////////////////
AnimationMgr::AnimationMgr()
{
    head = NULL;
    tail = NULL;
    tail = NULL;
    resourceMgr = ResourceMgr::getInstance();
    window      = Window::getInstance();
}

AnimationMgr::~AnimationMgr()
{
    //Remove all animation nodes
    while( head )
        removeNode( head );

    //Release all singletons
    resourceMgr->release();
    window->release();
}

/////////////////////////////////////
//Accessors
/////////////////////////////////////
bool AnimationMgr::draw( CurrentStateNode* animationId, bool facingRight, Point ul )
{
    //Find the sheet index
    int sheetIndex = getSheetIndex( animationId->getSheetName() );
    //Check to see if the sheet exists
    if( sheetIndex < 0 )
        return false;

    //Find state index
    int stateIndex = sheets[sheetIndex].getStateIndex( animationId->getState() );
    //Check if state exists
    if( stateIndex < 0 )
        return false;

    double xBeginForState = sheets[sheetIndex].getXBegin(stateIndex);
    double yBeginForState = sheets[sheetIndex].getYBegin(stateIndex);
    double stateFrameWidth = sheets[sheetIndex].getFrameWidth(stateIndex);
    double stateFrameHeight = sheets[sheetIndex].getFrameHeight(stateIndex);
    double totalSheetWidth = sheets[sheetIndex].getSheetWidth();
    double totalSheetHeight = sheets[sheetIndex].getSheetHeight();

    //FIND ROW NUMBER
    double row   = 0.0;
    int framesPerRow = 0.0;
    if( ( animationId->getFrame() + 1 ) * stateFrameWidth  > totalSheetWidth )
    {
        for( int i = 0; i <= animationId->getFrame(); ++i )
        {
            if( ( i * stateFrameWidth ) + stateFrameWidth - 1 > totalSheetWidth )
            {
                framesPerRow = i;
                break;
            }
        }
        row = animationId->getFrame() / framesPerRow;
    }

    //Find position coords
    double upper = ul.getY();
    double lower = ul.getY() - ( stateFrameHeight * animationId->getYScale() );
    double left  = ul.getX();
    double right = ul.getX() + ( stateFrameWidth * animationId->getXScale() );

    //Find texture coords x and ys
    double texLeftX     = xBeginForState + ( stateFrameWidth * ( animationId->getFrame() ) );
    double texRightX    = texLeftX + stateFrameWidth - 1 ;
    double texUpperY    = yBeginForState;
    double texLowerY    = yBeginForState + stateFrameHeight;

    if( row > 0 )
    {
        texLeftX  -= ( framesPerRow ) * row * stateFrameWidth;
        texRightX -= ( framesPerRow ) * row * stateFrameWidth;
        texUpperY += stateFrameHeight * row;
        texLowerY += stateFrameHeight * row;
    }


    //Find texture coords percentages
    double upperTex = texUpperY / totalSheetHeight;
    double lowerTex = texLowerY / totalSheetHeight;
    double leftTex  = texLeftX / ( totalSheetWidth );
    double rightTex = texRightX  / ( totalSheetWidth );

    //Draw in the proper direction
    if( facingRight )
        resourceMgr->drawImage( sheets[sheetIndex].getSheetName(), left, right, upper, lower, leftTex, rightTex, lowerTex, upperTex );
    else
        resourceMgr->drawImage( sheets[sheetIndex].getSheetName(), right, left, upper, lower, leftTex, rightTex, lowerTex, upperTex );

    //Draw was successful
    return true;
}

int AnimationMgr::getSheetIndex( string sheet )
{
    for( unsigned int i = 0; i < sheets.size(); ++i )
    {
        if( sheets[i].getSheetName() == sheet )
            return i;
    }
    return -1;
}

bool AnimationMgr::isAnimationOver( CurrentStateNode* animationId )
{
    if( ( animationId->getAnimationType() == "singleFull" ) or ( animationId->getAnimationType() == "single" ) )
        return false;
    else
        return true;
}

Point AnimationMgr::getLowerRight( CurrentStateNode* animationId, Point ul )
{
    //Find the sheet index
    int sheetIndex = getSheetIndex( animationId->getSheetName() );
    //Check to see if the sheet exists
    if( sheetIndex < 0 )
        return Point( 0.0, 0.0 );

    //Find state index
    int stateIndex = sheets[sheetIndex].getStateIndex( animationId->getState() );
    //Check if state exists
    if( stateIndex < 0 )
        return Point( 0.0, 0.0 );

    //Obtain frame default size.
    double stateFrameWidth = sheets[sheetIndex].getFrameWidth(stateIndex);
    double stateFrameHeight = sheets[sheetIndex].getFrameHeight(stateIndex);

    double xScale = animationId->getXScale();
    double yScale = animationId->getYScale();

    return Point( ul.getX() + ( stateFrameWidth * xScale ),
                  ul.getY() - ( stateFrameHeight * yScale ) );
}

Point AnimationMgr::getUpperRight( CurrentStateNode* animationId, Point ll )
{
    //Find the sheet index
    int sheetIndex = getSheetIndex( animationId->getSheetName() );
    //Check to see if the sheet exists
    if( sheetIndex < 0 )
        return Point( 0.0, 0.0 );

    //Find state index
    int stateIndex = sheets[sheetIndex].getStateIndex( animationId->getState() );
    //Check if state exists
    if( stateIndex < 0 )
        return Point( 0.0, 0.0 );

    //Obtain frame default size.
    double stateFrameWidth = sheets[sheetIndex].getFrameWidth(stateIndex);
    double stateFrameHeight = sheets[sheetIndex].getFrameHeight(stateIndex);

    double xScale = animationId->getXScale();
    double yScale = animationId->getYScale();

    return Point( ll.getX() + ( stateFrameWidth * xScale ),
                  ll.getY() + ( stateFrameHeight * yScale ) );
}

/////////////////////////////////////
//Mutators
/////////////////////////////////////
AnimationMgr* AnimationMgr::getInstance()
{
    if(instance == NULL)
    {
        instance = new AnimationMgr();
        instance->init();
    }
    ++referenceCount;
    return instance;
}

void AnimationMgr::release()
{
    if( --referenceCount < 1 )
    {
        destroy();
    }
    if(referenceCount < 0)
        referenceCount = 0;
}

void AnimationMgr::destroy()
{
    if(instance)
    {
        while( head != NULL )
            removeNode( head );
        resourceMgr->release();
        delete instance;
        instance = NULL;
    }
}

int AnimationMgr::stringToInt( string toConvert )
{
    int converted;
    stringstream converter;
    converter << toConvert;
    converter >> converted;
    return converted;
}

double AnimationMgr::stringToDouble( string toConvert )
{
    double converted;
    stringstream converter;
    converter << toConvert;
    converter >> converted;
    return converted;
}

void AnimationMgr::handleInput( string type, string input )
{
    if( type == "sheet=" )
    {
        sheets.push_back( AnimationSheet() );
        sheets[ sheets.size() - 1 ].insertSheetName( input );
    }
    else if( type == "sheetWidth=" )
        sheets[ sheets.size() - 1 ].insertSheetWidth( stringToDouble( input ) );
    else if( type == "sheetHeight=" )
        sheets[ sheets.size() - 1 ].insertSheetHeight( stringToDouble( input ) );
    else if( type == "state=" )
        sheets[ sheets.size() - 1 ].insertState( input );
    else if( type == "frames=" )
        sheets[ sheets.size() - 1 ].insertNumFrames( stringToInt( input ) );
    else if( type == "xBegin=" )
        sheets[ sheets.size() - 1 ].insertXBegin( stringToDouble( input ) );
    else if( type == "yBegin=" )
        sheets[ sheets.size() - 1 ].insertYBegin( stringToDouble( input ) );
    else if( type == "width=" )
        sheets[ sheets.size() - 1 ].insertFrameWidth( stringToDouble( input ) );
    else if( type == "height=" )
        sheets[ sheets.size() - 1 ].insertFrameHeight( stringToDouble( input ) );
    else if( type == "fps=" )
        sheets[ sheets.size() - 1 ].insertFps( stringToInt( input ) );
    else if( type == "defaultState" )
        sheets[ sheets.size() - 1 ].insertDefaultState( input );

}

CurrentStateNode* AnimationMgr::insertNode( string sheetName )
{
    CurrentStateNode* newAnimationId = new CurrentStateNode( tail, sheetName );

    //Check to see if the list is empty
    if( head == NULL )
        head = tail = newAnimationId;
    else
    {
        tail->setNextNode( newAnimationId );
        newAnimationId->setPrevNode( tail );
        tail = newAnimationId;
    }
    return newAnimationId;
}

void AnimationMgr::removeNode( CurrentStateNode* animationId )
{
    //Do nothing if NULL
    if( animationId == NULL )
        return;

    //Check to see if the node is at the front of the list
    if( animationId == head )
    {
        //Check to see if there is only 1 element
        if( head == tail )
            head = tail = NULL;

        head = animationId->getNext();
    }

    //Check to see if the node is at the end of the list
    else if( animationId == tail )
        tail = animationId->getPrev();

    //Otherwise the node is in the middle
    else
    {
        CurrentStateNode* prev = animationId->getPrev();
        CurrentStateNode* next = animationId->getNext();
        prev->setNextNode( next );
        next->setPrevNode( prev );
    }

    delete animationId;
}

void AnimationMgr::init()
{
    ifstream inputFile;
    inputFile.open( FILE_CHAR_SHEET_INFO );

    string type;
    string input;

    //Cycle through each line of the sheet file and input the data into
    // the AnimationSheet vector.
    while( inputFile.is_open() && !inputFile.eof() )
    {
        inputFile >> type;
        if( inputFile.eof() )
            break;

        inputFile >> input;
        handleInput( type, input );
    }
    inputFile.close();
}

CurrentStateNode* AnimationMgr::newAnimation( string sheet )
{
    return insertNode( sheet );
}

void AnimationMgr::removeAnimation( CurrentStateNode* animationId )
{
    return removeNode( animationId );
}

void AnimationMgr::setAnimation( CurrentStateNode* animationId, string state, string animationType )
{
    //Only alter the state and animationtype if the current animation type
    // isn't a singleFull type since a single full should run until it is over.
    if( animationId->getAnimationType() != "singleFull" )
    {
        if( animationType == "loopFromCurFrame" )
        {
            animationId->setStateAndFrame( state, animationId->getFrame() );
            animationId->setAnimationType( animationType );
        }
        else
        {
            animationId->setState( state );
            animationId->setAnimationType( animationType );
        }
    }
}

bool AnimationMgr::update( CurrentStateNode* animationId )
{
    //Find the sheet index
    int sheetIndex = getSheetIndex( animationId->getSheetName() );
    //Check to see if the sheet exists
    if( sheetIndex < 0 )
        return false;

    //Find state index
    int stateIndex = sheets[sheetIndex].getStateIndex( animationId->getState() );
    //Check if state exists
    if( stateIndex < 0 )
        return false;

    //Get frame information
    unsigned int numFramesForState = sheets[sheetIndex].getNumFrames(stateIndex);
    unsigned int fpsForState = sheets[sheetIndex].getFps(stateIndex);

    //Find update times
    double lastDraw = window->timeSinceLastFrame();
    double lastFrameUpdate = animationId->getLastFrameUpdate() + lastDraw;
    double timePerFrameUpdate = 1.0 / fpsForState;

    //Handles updating and reseting the frame
    if( lastFrameUpdate > timePerFrameUpdate )
    {
        animationId->incrementFrame();
        if( animationId->getFrame() >= numFramesForState )
        {
            animationId->resetFrame();
            if( ( animationId->getAnimationType() == "singleFull" ) or ( animationId->getAnimationType() == "single" ) )
            {
                animationId->setAnimationType( "loop" );
                animationId->setState( sheets[sheetIndex].getDefaultState() );
            }
        }

        animationId->setFrameUpdate( lastFrameUpdate - timePerFrameUpdate );
    }
    else
        animationId->setFrameUpdate( lastFrameUpdate );

    //Update was successful
    return true;
}

void AnimationMgr::setScale( CurrentStateNode* animationId, double xScale, double yScale )
{
    animationId->setScale( xScale, yScale );
}
