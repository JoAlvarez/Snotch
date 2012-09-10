#ifndef __TRIGGER_H__
#define __TRIGGER_H__

#include "triggerablelist.h"
class Trigger
{
    private:
        TriggerableList* triggerableList;
    public:
        Trigger();
        ~Trigger();
        void trigger( string triggerableName );
        void unTrigger( string triggerableName );
};

#endif

