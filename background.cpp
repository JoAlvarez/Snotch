#include "background.h"

#define MAX_NUMBER_OF_LAYERS 6

void Background::drawLayer( unsigned int layer )
{
    //Draw each background of the specific layer
        for( unsigned int i = 0; i < bgLayers.size(); ++i )
        {
            if( bgLayers[ i ].layer == layer )
            {
                drawBg( i );
            }
        }
}

void Background::drawBg( unsigned int index )
{
    //Window
    double winLeftX     = window->leftCoord();
    double winRightX    = window->rightCoord();
    double winUpperY    = window->topCoord();
    double winLowerY    = window->bottomCoord();

    double winWidth     = window->getWidth();
    double winHeight    = window->getHeight();

    //Bg
    double bgWidth      = bgLayers[ index ].width;
    double bgHeight     = bgLayers[ index ].height;

    double bgXOffset    = winLeftX * bgLayers[ index ].xSpeed;
    double bgYOffset    = winLowerY * bgLayers[ index ].ySpeed;

    double bgLeft       = bgLayers[ index ].leftX + bgXOffset;
    double bgRight      = bgLeft + bgLayers[ index ].width;

    double bgUpper      = bgLayers[ index ].upperY + bgYOffset;
    double bgLower      = bgUpper - bgLayers[ index ].height;

    double bgLeftRatio  = ( winLeftX - bgLeft ) / bgWidth;
    double bgRightRatio = bgLeftRatio + ( winWidth / bgWidth );

    double bgLowerRatio = ( winLowerY - bgLower ) / bgHeight;
    double bgUpperRatio = bgLowerRatio + ( winHeight / bgHeight );

    //Use different draws depending on whether the BG should repeat
    if( bgLayers[ index ].xRepeat )
    {
        if( bgLayers[ index ].yRepeat == "none" )
            resourceMgr->drawImage( bgLayers[ index ].bgAlias, winLeftX, winRightX, bgLower , bgUpper, bgLeftRatio, bgRightRatio , 0.0, 1.0 );
        else if( bgLayers[ index ].yRepeat == "up" )
        {
            bgUpperRatio = ( bgLower - winUpperY ) / bgHeight;
            resourceMgr->drawImage( bgLayers[ index ].bgAlias, winLeftX, winRightX, bgLower , winUpperY, bgLeftRatio, bgRightRatio , 0.0, bgUpperRatio );
        }
        else if( bgLayers[ index ].yRepeat == "upDown" )
            resourceMgr->drawImage( bgLayers[ index ].bgAlias, winLeftX, winRightX, winLowerY , winUpperY, bgLeftRatio, bgRightRatio , bgLowerRatio, bgUpperRatio );
    }
    else
    {
        if( bgLayers[ index ].yRepeat == "none" )
            resourceMgr->drawImage( bgLayers[ index ].bgAlias, bgLeft, bgRight, bgLower , bgUpper, 0.0, 1.0 , 0.0, 1.0 );
        else if( bgLayers[ index ].yRepeat == "up" )
        {
            bgUpperRatio = ( bgLower - winUpperY ) / bgHeight;
            resourceMgr->drawImage( bgLayers[ index ].bgAlias, winLeftX, winRightX, bgLower, winUpperY, bgLeftRatio, bgRightRatio , 0.0, bgUpperRatio );
        }
        else if( bgLayers[ index ].yRepeat == "upDown" )
            resourceMgr->drawImage( bgLayers[ index ].bgAlias, winLeftX, winRightX, winLowerY , winUpperY, bgLeftRatio, bgRightRatio , bgLowerRatio, bgUpperRatio );
    }
}

void Background::skipLine( ifstream & input )
{
    string junk;
    getline( input, junk );
}

void Background::handleInput( ifstream& inputFile )
{
    string type;
    inputFile >> type;

    //Make sure we havent reached the end of the file
    if( inputFile.eof() )
        return;

    //Skip commented lines
    if( type == "#" )
    {
        skipLine( inputFile );
        return;
    }

    //Add a new layer
    if( type == "begin" )
    {
        newLayer();
        return;
    }

    string input;
    inputFile >> input;

    //Handle all the different types of data input
    if( type == "texture=" )
    {
        resourceMgr->loadImage( input, input );
        bgLayers[ bgLayers.size() - 1 ].bgAlias = input;
    }
    else if( type == "xSpeed=" )
        bgLayers[ bgLayers.size() - 1 ].xSpeed = stringToDouble( input );
    else if( type == "layer=" )
        bgLayers[ bgLayers.size() - 1 ].layer = stringToInt( input );
    else if( type == "width=" )
        bgLayers[ bgLayers.size() - 1 ].width = stringToDouble( input );
    else if( type == "height=" )
        bgLayers[ bgLayers.size() - 1 ].height = stringToDouble( input );
    else if( type == "leftX=" )
        bgLayers[ bgLayers.size() - 1 ].leftX = stringToDouble( input );
    else if( type == "upperY=" )
        bgLayers[ bgLayers.size() - 1 ].upperY = stringToDouble( input );
    else if( type == "xRepeat=" )
        bgLayers[ bgLayers.size() - 1 ].xRepeat = stringToBool( input );
    else if( type == "xNatSpeed=" )
        bgLayers[ bgLayers.size() - 1 ].xNatSpeed = stringToDouble( input );
    else if( type == "yNatSpeed=" )
        bgLayers[ bgLayers.size() - 1 ].yNatSpeed = stringToDouble( input );
    else if( type == "yRepeat=" )
        bgLayers[ bgLayers.size() - 1 ].yRepeat = input;
    else if( type == "ySpeed=" )
        bgLayers[ bgLayers.size() - 1 ].ySpeed = stringToDouble( input );
}

int Background::stringToInt( string toConvert )
{
    int converted;
    stringstream converter( toConvert );
    converter >> converted;
    return converted;
}

double Background::stringToDouble( string toConvert )
{
    double converted;
    stringstream converter( toConvert );
    converter >> converted;
    return converted;
}

bool Background::stringToBool( string toConvert )
{
    if( toConvert == "true" )
        return true;
    return false;
}

void Background::newLayer()
{
    addLayer( "", 0.0, 0, 0.0, 0.0, 0.0, 0.0, false, 0.0, 0.0, "none", 0.0 );
}

Background::Background()
{
    resourceMgr = ResourceMgr::getInstance();
    window = Window::getInstance();
}

void Background::addLayer( string bgAlias, double xSpeed, unsigned int layer, double width, double height,
                           double leftX, double upperY, bool xRepeat, double xNatSpeed, double yNatSpeed, string yRepeat, double ySpeed )
{
    if( layer > MAX_NUMBER_OF_LAYERS )
        layer = MAX_NUMBER_OF_LAYERS;

    BgLayer tempLayer;
    tempLayer.bgAlias   = bgAlias;
    tempLayer.layer     = layer;
    tempLayer.xSpeed    = xSpeed;
    tempLayer.width     = width;
    tempLayer.height    = height;
    tempLayer.leftX     = leftX;
    tempLayer.upperY    = upperY;
    tempLayer.xRepeat   = xRepeat;
    tempLayer.xNatSpeed = xNatSpeed;
    tempLayer.yNatSpeed = yNatSpeed;
    tempLayer.yRepeat   = yRepeat;
    tempLayer.ySpeed    = ySpeed;
    bgLayers.push_back( tempLayer );
}

void Background::update()
{
    for( unsigned int i = 0; i < bgLayers.size(); ++i )
    {
        double xMovement = bgLayers[ i ].xNatSpeed * window->timeSinceLastFrame();
        double yMovement = bgLayers[ i ].yNatSpeed * window->timeSinceLastFrame();
        bgLayers[ i ].leftX += xMovement;
        bgLayers[ i ].upperY += yMovement;
    }
}

void Background::clear()
{
    bgLayers.clear();
}

void Background::draw( )
{
    //Draw each layer
    for( unsigned int layer = 0; layer <= MAX_NUMBER_OF_LAYERS; ++layer )
    {
        drawLayer( layer );
    }

}

void Background::load( string bgFile )
{
    ifstream inputFile;
    inputFile.open( bgFile.c_str() );

    //Traverse the lines of the file
    while( inputFile.is_open() && !inputFile.eof() )
        handleInput( inputFile );

    inputFile.close();
}

Background::~Background()
{
    clear();
    resourceMgr->release();
    window->release();
}
