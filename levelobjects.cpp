
#include "levelobjects.h"
#include "door.h"
#include "ingamebutton.h"


LevelObjects:: LevelObjects()
{
    resourceMgr = ResourceMgr::getInstance();
}

LevelObjects:: ~LevelObjects()
{
    resourceMgr->release();
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void LevelObjects:: insert( Detectable* o )
{
    objectBin.push_back( o );
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void LevelObjects:: remove( Detectable* o )
{
    for ( unsigned int i = 0; i < objectBin.size(); i++ )
    {
        if ( *objectBin[i] == *o )
        {
            for ( unsigned int j = i; j < objectBin.size(); j++ )
            {
                objectBin[j] = objectBin[j + i];
            }

            objectBin.pop_back();
            return;
        }
    }
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void LevelObjects:: clear()
{
    while ( 0 < objectBin.size() )
    {
        objectBin.pop_back();
    }
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void LevelObjects:: didDetect( Physics* o )
{
    if ( o->getYVel() <= 0 and o->getXVel() > 0 )
    {
        objectsFromTopAndLeft( o );
    }
    else if ( o->getYVel() <= 0 and o->getXVel() < 0 )
    {
        objectsFromTopAndRight( o );
    }

    else if ( o->getYVel() > 0 and o->getXVel() > 0 )
    {
        objectsFromBottomAndLeft( o );
    }
    else if ( o->getYVel() > 0 and o->getXVel() < 0 )
    {
        objectsFromBottomAndRight( o );
    }

    else if( o->getXVel() >  0 and o->getYVel() == 0 )
    {
        objectsFromLeft  ( o );
    }

    else if ( o->getXVel() < 0 and o->getYVel() == 0 )
    {
        objectsFromRight ( o );
    }

    else if ( o->getYVel() <= 0 and o->getXVel() == 0 )
    {
        objectsFromTop( o );
    }
    else if ( o->getYVel() >  0 and o->getXVel() == 0)
    {
        objectsFromBottom( o );
    }
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void LevelObjects:: objectsFromLeft  ( Physics* o )
{
    for ( unsigned int i = 0; i < objectBin.size(); i++ )
    {
        if ( objectBin[i]->getType() == "BLOCK" || objectBin[i]->getType() == "BOX" )
        {
            if (  o->detectFromLeft( *objectBin[i] ) )
            {
                o->setPosition( Point ( objectBin[i]->uLeft.getX() - o->width , o->uLeft.getY() ) ) ;
                o->setXVel( -(o->getXVel()) * o->getElasticity() );
            }
        }
    }
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void LevelObjects:: objectsFromRight ( Physics* o )
{
    for ( unsigned int i = 0; i < objectBin.size(); i++ )
    {
        if ( objectBin[i]->getType() == "BLOCK" || objectBin[i]->getType() == "BOX" )
        {
            if ( o->detectFromRight( *objectBin[i] ) )
            {
                o->setPosition( Point ( objectBin[i]->uRight.getX() , o->uLeft.getY() ) ) ;
                o->setXVel( -(o->getXVel()) * o->getElasticity() );
            }
        }
    }
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void LevelObjects:: objectsFromTop( Physics* o )
{
    bool touched = false;
    for ( unsigned int i = 0; i < objectBin.size(); i++ )
    {
        if ( objectBin[i]->getType() == "BLOCK" ||
             objectBin[i]->getType() == "BOX" )
        {
            if (  o->detectFromTop( *objectBin[i] ) )
            {
                if(o->getYVel() < 0)
                {
                    o->setPosition( Point ( o->uLeft.getX() , objectBin[i]->uLeft.getY() + o->height ) );
                    o->setYVel( 0 );
                    o->setInAir(false);
                }
                touched = true;
            }
        }
        else if(  objectBin[i]->getType() == "PLATFORM" && !o->canGoThroughPlatform() )
        {
            if (  o->detectFromTop( *objectBin[i] ) )
            {
                if(o->getYVel() < 0)
                {
                    o->setPosition( Point ( o->uLeft.getX() , objectBin[i]->uLeft.getY() + o->height ) );
                    o->setYVel( 0 );
                    o->setInAir(false);
                }
                touched = true;
            }
        }
    }
    if( !touched )
        o->setInAir(true);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void LevelObjects:: objectsFromBottom( Physics* o )
{
    for ( unsigned int i = 0; i < objectBin.size(); i++ )
    {
        if ( objectBin[i]->getType() == "BLOCK" ||
             objectBin[i]->getType() == "BOX" )
        {
            if ( o->detectFromBottom( *objectBin[i] ) )
            {
                o->setPosition( Point ( o->uLeft.getX() , objectBin[i]->lLeft.getY() ) );
                o->setYVel( 0 );
            }
        }
    }
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void LevelObjects:: objectsFromTopAndLeft( Physics* o )
{
    bool touched = false;
    for ( unsigned int i = 0; i < objectBin.size(); i++ )
    {
        if ( objectBin[i]->getType() == "BLOCK" ||
             objectBin[i]->getType() == "BOX")
        {
            int d = o->detectFromTopAndLeft( *objectBin[i] );
            if ( d == TOP_DETECTED )
            {
                if( o->getInAir() || o->getYVel() < 0)
                {
                    o->setYVel( 0 );
                    o->setInAir(false);
                    o->setPosition( Point ( o->uLeft.getX() , objectBin[i]->uLeft.getY() + o->height) );
                }
                touched = true;
            }
            else if ( d == LEFT_DETECTED )
            {
                o->setXVel( -(o->getXVel()) * o->getElasticity() );
                o->setPosition( Point ( objectBin[i]->uLeft.getX() - o->width, o->uLeft.getY() ) );
            }
        }

        else if(objectBin[i]->getType() == "PLATFORM")
        {
            if(o->detectFromTop( *objectBin[i] ) && !o->canGoThroughPlatform() )
            {
                if( o->getInAir() || o->getYVel() < 0 )
                {
                    o->setYVel( 0 );
                    o->setInAir(false);
                    o->setPosition( Point ( o->uLeft.getX() , objectBin[i]->uLeft.getY() + o->height) );
                }
                touched = true;
            }
        }
    }
    if(!touched)
        o->setInAir(true);
}


void LevelObjects:: objectsFromTopAndRight( Physics* o )
{
    bool touched = false;
    for ( unsigned int i = 0; i < objectBin.size(); i++ )
    {
        if ( objectBin[i]->getType() == "BLOCK" ||
             objectBin[i]->getType() == "BOX")
        {
            int d = o->detectFromTopAndRight( *objectBin[i] );
            if ( d == TOP_DETECTED )
            {
                if( o->getInAir() || o->getYVel() < 0 )
                {
                    o->setYVel( 0 );
                    o->setInAir(false);
                    o->setPosition( Point ( o->uLeft.getX() , objectBin[i]->uLeft.getY() + o->height ) );
                }
                touched = true;
            }
            else if ( d == RIGHT_DETECTED )
            {
                o->setXVel( -(o->getXVel()) * o->getElasticity() );
                o->setPosition( Point ( objectBin[i]->uRight.getX() , o->uLeft.getY() ) ) ;
            }
        }

        else if(objectBin[i]->getType() == "PLATFORM" )
        {
             if(o->detectFromTop( *objectBin[i] ) && !o->canGoThroughPlatform() )
            {
                if( o->getInAir() || o->getYVel() < 0 )
                {
                    o->setYVel( 0 );
                    o->setInAir(false);
                    o->setPosition( Point ( o->uLeft.getX() , objectBin[i]->uLeft.getY() + o->height ) );
                }
                touched = true;
            }
        }
    }

    if(!touched)
        o->setInAir(true);

}

void LevelObjects:: objectsFromBottomAndLeft( Physics* o )
{
    for ( unsigned int i = 0; i < objectBin.size(); i++ )
    {
        if ( objectBin[i]->getType() == "BLOCK" ||
             objectBin[i]->getType() == "BOX")
        {
                int d = o->detectFromBottomAndLeft( *objectBin[i] );
                if ( d == BOTTOM_DETECTED )
                {
                    o->setYVel( 0 );
                    o->setPosition( Point ( o->uLeft.getX() , objectBin[i]->lLeft.getY() ) );
                }
                else if ( d == LEFT_DETECTED )
                {
                    o->setXVel( -(o->getXVel()) * o->getElasticity() );
                    o->setPosition( Point ( objectBin[i]->uLeft.getX() - o->width , o->uLeft.getY() ) ) ;
                }
        }
    }
}

void LevelObjects:: objectsFromBottomAndRight( Physics* o )
{
    for ( unsigned int i = 0; i < objectBin.size(); i++ )
    {
        if ( objectBin[i]->getType() == "BLOCK" ||
             objectBin[i]->getType() == "BOX" )
        {
                int d = o->detectFromBottomAndRight( *objectBin[i] );
                if ( d == BOTTOM_DETECTED )
                {
                    o->setYVel( 0 );
                    o->setPosition( Point ( o->uLeft.getX() , objectBin[i]->lLeft.getY() ) );
                }
                else if ( d == RIGHT_DETECTED )
                {
                    o->setXVel( -(o->getXVel()) * o->getElasticity() );
                    o->setPosition( Point ( objectBin[i]->uRight.getX() , o->uLeft.getY() ) ) ;
                }
        }
    }
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void LevelObjects:: openFile( const string fileName )
{
    // Open file
    objectLoader.open( fileName.c_str() );

    // Check if file opened correctly
    if ( not objectLoader.is_open() )
    {
        //"FATAL ERROR: THE LEVEL FILE WAS NOT FOUND!"
    }
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void LevelObjects:: readIn()
{
    string type;
    double uLX, uLY, lRX, lRY;
    Point upperLeft;
    Point lowerRight;
    string texture;
    string name;
    string target;

    // Read in level data from the file
    while ( ! objectLoader.eof() )
    {
        objectLoader >> type;
        objectLoader >> uLX;
        objectLoader >> uLY;
        if( type != "BUTTON" )
        {
            objectLoader >> lRX;
            objectLoader >> lRY;
            objectLoader >> texture;
        }

        upperLeft  = Point( uLX, uLY );

        if( type != "BUTTON" )
            lowerRight = Point( lRX, lRY );

        LevelEntities* newEntity;

        //Handle door paramaters
        if( type == "DOOR" )
            objectLoader >> name;

        //Handle foor paramaters
        if( type == "BUTTON" )
            objectLoader >> target;

        if( type == "DOOR" )
            newEntity = new Door( upperLeft, lowerRight, texture, name );
        else
            newEntity = new LevelEntities( type, upperLeft, lowerRight, texture );

        insert( newEntity );
    }
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void LevelObjects:: doneLoading()
{
    // clear the buffer
    objectLoader.clear();

    //close the file
    objectLoader.close();
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void LevelObjects:: loadObjects( const string filename )
{
    openFile( filename );
    readIn();
    loadImages();
    doneLoading();
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void LevelObjects:: draw()
{
    for ( unsigned int i = 0; i < objectBin.size(); i++ )
    {
        /*if(objectBin[i]->getType() != "BOX")
        {
            resourceMgr->drawImage((static_cast<LevelEntities*>( objectBin[i] ))->texture() ,
                                objectBin[i]->uLeft.getX(), objectBin[i]->uRight.getX(),
                                objectBin[i]->lLeft.getY(), objectBin[i]->uRight.getY(),
                                0.0, objectBin[i]->width/TEXTURE_SIZE, 1.0 - objectBin[i]->height/TEXTURE_SIZE, 1.0);
        }
        else
        {
            (static_cast < Object* >( objectBin[i] ))->draw();
        }*/
        objectBin[i]->draw();

    }
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void LevelObjects:: loadImages()
{
    for ( int i = 0; i < objectBin.size(); i++ )
    {
        resourceMgr->loadImage( IMAGES_DIR + ( ( LevelEntities* )( objectBin[i] ) )->texture() + ".png" ,
                                ( ( LevelEntities* )( objectBin[i] ) )->texture() );
    }
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
