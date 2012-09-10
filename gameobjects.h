#ifndef __GAMEOBJECTS_H__
#define __GAMEOBJECTS_H__

#include "object.h"
#include <vector>

using namespace std;

class GameObjects
{
    private:

        vector<Object*> objects;

    public:

        GameObjects();

        void update();
        void draw();
        void release();

        void setObject(string,Point);
        void checkHit(Physics*);
};


#endif
