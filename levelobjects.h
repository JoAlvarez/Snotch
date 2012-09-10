#ifndef _LEVELOBJECTS_H_
#define _LEVELOBJECTS_H_

#include <fstream>
#include <string>
#include "levelentities.h"
#include <vector>
#include "point.h"
#include "resourcemgr.h"
#include "physics.h"
#include "filenames.h"
#include "object.h"

using namespace std;

class LevelObjects
{
    public:
        // Constructor and Deconstructor
        LevelObjects();
        ~LevelObjects();

        ResourceMgr* resourceMgr;

        // Memeber Functions
        void insert( Detectable* o );
        void remove( Detectable* o );
        void clear();

        // Load object types and locations from a file
        void loadObjects( const string filename );

        // Master detection function
        void didDetect( Physics* o );

        // Draw function
        void draw();

    protected:
        //Vectors hold all the Level Entities objects
        vector < Detectable* > objectBin;

        // To read in objects from file
        ifstream objectLoader;

        // Functions to access the object file
        void openFile( const string fileName );
        void readIn();

        // To clear ifstreams buffer and close the file.
        void doneLoading();

        // Load level object images for current level
        void loadImages();

        //detection functions
        void objectsFromLeft  ( Physics* o );
        void objectsFromRight ( Physics* o );
        void objectsFromTop   ( Physics* o );
        void objectsFromBottom( Physics* o );

        void objectsFromTopAndLeft    ( Physics* o );
        void objectsFromTopAndRight   ( Physics* o );
        void objectsFromBottomAndLeft ( Physics* o );
        void objectsFromBottomAndRight( Physics* o );

        //Seperate draw functions
        void drawWall    ( LevelEntities* );
        void drawLedge   ( LevelEntities* );
        void drawPlatform( LevelEntities* );
        void drawBlock   ( LevelEntities* );
        void drawPillar  ( LevelEntities* );

};

#endif
