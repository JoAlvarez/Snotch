#ifndef _LEVELENTITIES_H_
#define _LEVELENTITIES_H_

#include "detectable.h"
#include "resourcemgr.h"

class LevelEntities
    :public Detectable
{
    public:
        ResourceMgr* resourceMgr;

        // Constructors
        // Possible Types Passed In

        // WALL
        // LEDGE
        // PLATFORM
        // BLOCK
        // PILLAR

        // More Will Be Added as
        // The Detection Class Is expanded
        LevelEntities( string type, Point uL, Point lR, string texture );

        string type();
        string texture();
        void draw();

    private:
        // String that holds the type
        string typeOfEntity;

        string textureType;

};
#endif
