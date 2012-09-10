#include "cursor.h"

Cursor::Cursor()
{
    shown = true;
}

void Cursor::init()
{
    resourceMgr = ResourceMgr::getInstance();
    input = Input::getInstance();
    window = Window::getInstance();
    resourceMgr->loadImage( "./data/images/cursor.png", "cursor" );
}

void Cursor::draw()
{
    window->showCursor( false );
    if( shown )
        resourceMgr->drawImage( "cursor",
                                input->getMouseXloc() - 16,
                                input->getMouseXloc() + 48,
                                input->getMouseYloc() - 48,
                                input->getMouseYloc() + 16 );
}

void Cursor::setShown( bool shown )
{
    this->shown = shown;
}

bool Cursor::isShown()
{
    return shown;
}

Cursor::~Cursor()
{
    input->release();
    window->release();
    resourceMgr->release();
}
