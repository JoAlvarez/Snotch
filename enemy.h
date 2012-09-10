
#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "filenames.h"
#include "ai.h"

class Turtle : public AI
{
    public:
        Turtle();
        void            runAI();
        void            draw();
        void            init();

    private:
        void            calcState();

};

#endif
