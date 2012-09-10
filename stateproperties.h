#ifndef __STATE_PROPERTIES__
#define __STATE_PROPERTIES__

#include <vector>
#include <string>

using namespace std;

class StateProperties
{
    public:
        double       xBeginForState;
        double       yBeginForState;
        double       stateFrameWidth;
        double       stateFrameHeight;
        unsigned int numFramesForState;
        unsigned int fpsForState;
        string       stateName;
};

#endif
