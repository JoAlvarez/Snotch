#include "levelentities.h"

#define TEXTURE_SIZE 128.0

LevelEntities:: LevelEntities( string t, Point uL, Point lR, string texture )
    : Detectable( uL, lR, t)
{
    typeOfEntity = t;
    textureType = texture;
    resourceMgr = ResourceMgr::getInstance();
}

string LevelEntities:: type()
{
    return typeOfEntity;
}

string LevelEntities:: texture()
{
    return textureType;
}

void LevelEntities::draw()
{
    resourceMgr->drawImage(     texture() ,
                                uLeft.getX(), uRight.getX(),
                                lLeft.getY(), uRight.getY(),
                                0.0, width/TEXTURE_SIZE, 1.0 - height/TEXTURE_SIZE, 1.0);
}
