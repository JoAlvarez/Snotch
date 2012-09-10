#ifndef __TRIGGERABLE_H__
#define __TRIGGERABLE_H__

#include "triggerablelist.h"
#include <string>

using namespace std;

class TriggerableList;
class Triggerable
{
    protected:
        bool                triggered;
        string              triggerableName;
        TriggerableList*    triggerableList;

    public:
        Triggerable();
        ~Triggerable();
        void            init( string triggerableName );
        virtual void    trigger() = 0;
        virtual void    unTrigger() = 0;
};
#endif
