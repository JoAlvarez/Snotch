#ifndef __ABILITIES_H__
#define __ABILITIES_H__

#include "powers.h"
#include <vector>

using namespace std;
class Abilities
{
    private:

        static   Abilities* instance;
        static   int referenceCount;

    public:

        vector <Powers*> power;
        Window* window;

        Abilities();

        void init();
        void update();
        void draw();
        void release();

        void checkHit(Physics*);
        void usePower(string, Point, int, bool);

        static Abilities* getInstance();
};

#endif
