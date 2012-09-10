#include "actionbar.h"

ActionBar::ActionBar()
{
    startPushCd = false;
    cdTimer = new Cooldown();
}

void ActionBar::init()
{
    resourceMgr  = ResourceMgr::getInstance();
    input        = Input::getInstance();
    window       = Window::getInstance();
    resourceMgr->loadImage( FILE_PUSH_SPELL, "PUSH" );
    cdTimer->init();
}

void ActionBar::checkInput()
{
    if( input->getKeyInput() == "1" )
    {
        if( startPushCd == false )
        {
            startPushCd = true;
            cdTimer->start( 1.0, percentLeftX, percentRightX, percentLowerY, percentUpperY );
        }
    }
}

void ActionBar::update()
{
    cdTimer->update();
    if(startPushCd == true && cdTimer->isEnd())
        startPushCd = false;
}

void ActionBar::draw()
{
    resourceMgr->drawImageOverlay( "PUSH",
                                    percentLeftX,
                                    percentRightX,
                                    percentLowerY,
                                    percentUpperY );

    //Start cooldown when certain spell has been used.
    if( startPushCd == true )
    {
        cdTimer->draw();
    }
}

ActionBar::~ActionBar()
{
    input->release();
    window->release();
    resourceMgr->release();
}
